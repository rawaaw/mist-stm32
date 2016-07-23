/******************************************************************/
/*                                                                */
/* Module:       jrunner_stm32.c                                  */
/*                                                                */
/* Descriptions: Main source file that manages the configuration  */
/*               processes.                                       */
/*                                                                */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "jb_io.h"
#include "jb_jtag.h"
#include "jb_const.h"
#include "jb_device.h"
#include "hardware.h"

/* JRunner Controller Functions */
int  VerifyChain      (void);
void DriveSignal      (int signal,int data,int clk,int buffer_enable);
void Configure        (int file_id,int dev_seq,int idcode);
void ProcessFileInput (int finputid, int idcode);
int  CheckStatus      (int dev_seq);
int	 SAMPLE_BSC		  (int dev_seq, int jtag_seq_num, int bsc_type);
void Startup          (int dev_seq);

/* JTAG instruction lengths of all devices */
int  ji_info[MAX_DEVICE_ALLOW];



/******************************************************************/
/* Name:         VerifyChain                                      */
/*                                                                */
/* Parameters:   None.                                            */
/*                                                                */
/* Return Value: None.                                            */
/*               		                                          */
/* Descriptions: Putting all devices in BYPASS mode, a 8-bit      */
/*               vector is driven to TDI, the number of '0'       */
/*               detected indicates the number of devices in      */
/*               chain. The 8-bit vector must follows the zeroes. */
/*                                                                */
/******************************************************************/
int VerifyChain()
{
	unsigned int data=0,temp=0,test_vect=0x55;
	int i,num=0,error=0;
	
	Js_Reset();
	/* Load BYPASS instruction and test JTAG chain with a few vectors */
	if(Ji_Bypass(device_count,ji_info))
		return (1);
	Js_Shiftdr();

	/* Drive a 8-bit vector of "10101010" (right to left) to test */
	data = ReadTDO(8+device_count,test_vect,0);
	/* The number of leading '0' detected must equal to the number of devices specified */
	temp = data;
	
	for(i=0;i<device_count;i++)
	{
		temp = temp&1;
		if(temp)
			break;		
		else
			num++;
		temp = data>>(i+1);
	}

	if(temp==test_vect)	
		iprintf("Info: Detected %d device(s) in chain...\n", num);
	else
	{
		iprintf("Error: JTAG chain broken or #device in chain unmatch!\n");
		return (1);
	}

	Js_Updatedr();
	
	/* Read device IDCODE */
	Ji_Idcode(device_count,ji_info);
	Js_Shiftdr();

	for(i=device_count-1;i>=0;i--)
	{
		data = ReadTDO(CDF_IDCODE_LEN,TDI_LOW,0);

		if(device_list[i].idcode)
		{
			/* The partname specified in CDF must match with its ID Code */
			if((unsigned)device_list[i].idcode != data)
			{
				iprintf("Error: Expected 0x%X but detected 0x%X!\n",device_list[i].idcode,data);
				error=1;
			}
			else
				iprintf("Info: Dev%d: Altera: 0x%X\n",i+1,data);
		}
		else
		{
			iprintf("Info: Dev%d: Non-Altera: 0x%X\n",i+1,data);
		}
	}

	Js_Updatedr();
	Js_Runidle();
	
	return error;
}

/******************************************************************/
/* Name:         Configure                                        */
/*                                                                */
/* Parameters:   file_id,dev_seq,action                           */
/*               -file_id is the ID of the file.                  */
/*               -dev_seq is the device sequence in chains.       */
/*               -action is the action to take:BYPASS or PROGRAM  */
/*                                                                */
/* Return Value: None.                                            */
/*               		                                          */
/* Descriptions: Issue PROGRAM instruction to the device to be    */
/*               configured and BYPASS for the rest of the devices*/
/*               Call function that processes the source file.    */
/*                                                                */
/******************************************************************/
void Configure(int file_id,int dev_seq,int idcode)
{
	int i,j,data=0;
	int action = idcode? JI_PROGRAM:JI_BYPASS;

	/* Load PROGRAM instruction */
	SetupChain(device_count,dev_seq,ji_info,action);

	if(action==JI_PROGRAM)
	{
		/* Drive TDI HIGH while moving JSM to SHIFTDR */
		DriveSignal(SIG_TDI,TDI_HIGH,TCK_QUIET,BUFFER_OFF);
		Js_Shiftdr();
		/* Issue MAX_JTAG_INIT_CLOCK clocks in SHIFTDR state */
		for(i=0;i<MAX_JTAG_INIT_CLOCK[device_family];i++)
		{
			DriveSignal(SIG_TDI,TDI_HIGH,TCK_TOGGLE,BUFFER_ON);
		}
		/* Start dumping configuration bits into TDI and clock with TCK */
		ProcessFileInput(file_id,idcode);

			/* AKL (Version1.7): Dump additional 16 bytes of 0xFF at the end of the RBF file */
			for (j=0;j<128;j++ )
			{
				DriveSignal(SIG_TDI,1,TCK_TOGGLE,BUFFER_ON);
			}

		/* Move JSM to RUNIDLE */
		Js_Updatedr();
		Js_Runidle();
	}
}

/******************************************************************/
/* Name:         CheckStatus                                      */
/*                                                                */
/* Parameters:   dev_seq                                          */
/*               -dev_seq is the device sequence in chains.       */
/*                                                                */
/* Return Value: '0' if CONF_DONE is HIGH;'1' if it is LOW.       */
/*               		                                          */
/* Descriptions: Issue CHECK_STATUS instruction to the device to  */
/*               be configured and BYPASS for the rest of the     */
/*               devices.                                         */
/*                                                                */
/*               <conf_done_bit> =                                */
/*                  ((<Maximum JTAG sequence> -                   */
/*                    <JTAG sequence for CONF_DONE pin>)*3) + 1   */
/*                                                                */
/*               The formula calculates the number of bits        */
/*               to be shifted out from the device, excluding the */
/*               1-bit register for each device in BYPASS mode.   */
/*                                                                */
/******************************************************************/
int CheckStatus(int dev_seq)
{
	int bit,data=0,error=0;
	int jseq_max=0,jseq_conf_done=0,conf_done_bit=0;

	iprintf("Info: Checking Status\n" );

	/* Load CHECK_STATUS instruction */
	SetupChain(device_count,dev_seq,ji_info,JI_CHECK_STATUS);

	Js_Shiftdr();

	/* Maximum JTAG sequence of the device in chain */
	jseq_max= device_list[dev_seq-1].jseq_max;

	jseq_conf_done= device_list[dev_seq-1].jseq_conf_done;

	conf_done_bit = ((jseq_max-jseq_conf_done)*3)+1;

	/* Compensate for 1 bit unloaded from every Bypass register */
	conf_done_bit+= (device_count-dev_seq);
	
	for(bit=0;bit<conf_done_bit;bit++)
	{
		DriveSignal(SIG_TDI,TDI_LOW,TCK_TOGGLE,BUFFER_OFF);
	}

	data = ReadTDO(PORT_1,TDI_LOW,0);

	if(!data)
		error++;

	/* Move JSM to RUNIDLE */
	Js_Updatedr();
	Js_Runidle();

	return (error);	
}

/******************************************************************/
/* Name:         Startup                                          */
/*                                                                */
/* Parameters:   dev_seq                                          */
/*               -the device sequence in the chain.               */
/*                                                                */
/* Return Value: None.                                            */
/*               		                                          */
/* Descriptions: Issue STARTUP instruction to the device to       */
/*               be configured and BYPASS for the rest of the     */
/*               devices.                                         */
/*                                                                */
/******************************************************************/
void Startup(int dev_seq)
{
	int i;

	/* Load STARTUP instruction to move the device to USER mode */
	SetupChain(device_count,dev_seq,ji_info,JI_STARTUP);

	Js_Runidle();

	for(i=0;i<INIT_COUNT;i++)
	{
		DriveSignal(SIG_TCK,TCK_LOW,TCK_QUIET,BUFFER_OFF);
		DriveSignal(SIG_TCK,TCK_HIGH,TCK_QUIET,BUFFER_OFF);
	}

	/* Reset JSM after the device is in USER mode */
	Js_Reset();
}

/******************************************************************/
/* Name:         ProcessFileInput                                 */
/*                                                                */
/* Parameters:   finputid                                         */           
/*               -programming file pointer.                       */
/*                                                                */
/* Return Value: None.                                            */
/*                                                                */
/* Descriptions: Get programming file size, parse through every   */
/*               single byte and dump to parallel port.           */
/*                                                                */
/******************************************************************/
void ProcessFileInput(int finputid, int idcode)
{
	int seek_position=0,one_byte=0;
	long int file_size=0,i=0;

	/* Get file size */
	seek_position = jb_fseek(finputid,0,S_END);

	if(seek_position)
	{
		iprintf("Error: End of file could not be located!" );
		return;
	}

	file_size = jb_ftell(finputid);
	iprintf("Info: Programming file size: %ld\n", file_size );		
	/* Start configuration */
	/* Reset file pointer */
	jb_fseek(finputid,0,S_SET);

	iprintf("Info: Start configuration process.\n  Please wait...");

	/* Loop through every single byte */
	for(i=0;i<file_size;i++)
	{
		/*Ignore first 44 bytes in the rbf file for Cyclone device*/
		if(i<44 && ((idcode>0x2080000 && idcode<0x2086000) || (idcode>=0x20B10DD && idcode<=0x20B60DD)))		//AKL5B15: Ignore Cyclone II devices also
			one_byte = jb_fgetc(finputid);
		else
		{
			int	bit = 0,j;

			one_byte = jb_fgetc(finputid);

			/* Progaram a byte,from LSb to MSb */
			for (j=0;j<8;j++ )
			{
				bit = one_byte >> j;
				bit = bit & 0x1;
			
				/* Dump to TDI and drive a positive edge pulse at the same time */
				DriveSignal(SIG_TDI,bit,TCK_TOGGLE,BUFFER_ON);
			}
		}
	}
#if PORT==WINDOWS_NT
	/* Flush out the remaining data in Port0 */
	flush_ports();
#endif /* PORT==WINDOWS_NT */

	iprintf(" done\n");
}

/******************************************************************/
/* Name:         DriveSignal                                      */
/*                                                                */
/* Parameters:   signal,data,clk,buffer_enable                    */
/*               -the name of the signal (SIG_*).                 */
/*               -the value to be dumped to the signal,'1' or '0' */
/*               -driving a LOW to HIGH transition to SIG_TCK     */
/*                together with signal.                           */
/*               -buffer_enable is used by WritePort function.	  */
/*				 -If "buffer_enable"=1,							  */
/*				 -processes in "port_io_buffer" are flushed when  */
/*               -"PORT_IO_BUFFER_SIZE" is reached.				  */	
/*				 -If "buffer_enable"=0,							  */
/*               -"data" is dumped to port 0 at once			  */
/*                                                                */
/* Return Value: None.                                            */
/*                                                                */
/* Descriptions: Dump data to signal. If clk is '1', a clock pulse*/
/*               is driven after the data is dumped to signal.    */
/*                                                                */
/******************************************************************/
void DriveSignal(int signal,int data,int clk,int buffer_enable)
{
	/* Get signal port number */
	int port = sig_port_maskbit[signal][0];

	/* Get signal mask bit*/
	int mask;
	
	/* If clk == 1, drive signal with [data] and drive SIG_TCK with '0' together. Then drive SIG_TCK with '1' */
	/* That is to create a positive edge pulse */
	if(clk)
		mask = sig_port_maskbit[signal][1] | sig_port_maskbit[SIG_TCK][1];
	else
		mask = sig_port_maskbit[signal][1];
	
	/* AND signal bit with '0', then OR with [data] */
	mask = ~mask;
	port_data[port] = (port_data[port]&mask) | (data*sig_port_maskbit[signal][1]);
	
	WritePort(port,port_data[port],buffer_enable);

	if(clk)
	{
		WritePort(port,(port_data[port] | sig_port_maskbit[SIG_TCK][1]),buffer_enable);
		WritePort(port,port_data[port],buffer_enable);
	}
}

/********************************************************************/
/*	Name : SAMPLE_BSC												*/
/*																	*/
/*	Parameter : dev_seq, jtag_seq_num, bsc_type						*/ 
/*				dev_seq:											*/		
/*					-device sequence in JTAG chain, starts from 1	*/
/*					-for the first device in JTAG chain				*/
/*				jtag_seq_num:										*/
/*					-You need to check the jtag_seq_num for the		*/
/*					-targeted IO pin from the targeted device BSDL	*/
/*					-file, which can be downloaded from				*/
/*					-www.altera.com									*/
/*					-For an example, for EP1S10F780, its INIT_DONE	*/
/*					-pin is pin W11. From the EP1S10F780 BSDL file,	*/
/*					-I/O pin W11 is BSC Group 262, so the			*/	
/*					-jtag_seq_num for pin W11 is					*/
/*					- jtag_seq_num = max_seq_num - BSC Group number	*/
/*					- jtag_seq_num = 439 - 262 = 177				*/
/*					-Thus, the jtag_seq_num for I/O pin W11 in		*/
/*					-EP1S10F780 is 177.								*/
/*				bsc_type:											*/
/*					-this parameter specifies which type of boundary*/
/*					-scan register you are interested in, whether	*/
/*					-input register, OE register or output register	*/
/*					-For each BSC, input register value is scanned	*/
/*					-out through TDO first, followed by OE register	*/
/*					-and then output register.						*/
/*																	*/
/*	Return Value: Status of the interested boundary scan register in*/
/*				  the targeted device.								*/
/*																	*/
/*  Description: This function allows you to sample and read out	*/
/*				 the value of any the boundary scan register in the	*/
/*				 scan chain.										*/
/*				 Please read AN039.pdf-IEEE1149.1 (JTAG) Boundary-  */
/*				 Scan Testing in Altera devices for more information*/
/*				 the Boundary-Scan Test (BST) circuitry in Altera	*/
/*				 devices. Don't use this function to check CONF_DONE*/
/*				 status. Instead, use CHECKSTATUS function to check */
/*				 CONF_DONE pin status.								*/
/*																	*/
/********************************************************************/
int SAMPLE_BSC(int dev_seq, int jtag_seq_num, int bsc_type)
{
	int bit,data=0;
	int jseq_max=0,jseq_target_bit=0;

	/* Load SAMPLE/PRELOAD instruction */
	SetupChain(device_count,dev_seq,ji_info,JI_SAMPLE);

	Js_Shiftdr();

	/* Maximum JTAG sequence of the device in chain */
	jseq_max= device_list[dev_seq-1].jseq_max;

	if (bsc_type==0)
		jseq_target_bit = ((jseq_max-jtag_seq_num)*3);
	else if(bsc_type ==1)
		jseq_target_bit = ((jseq_max-jtag_seq_num)*3)+1;
	else
		jseq_target_bit = ((jseq_max-jtag_seq_num)*3)+2;

	/* Compensate for 1 bit unloaded from every Bypass register */
	jseq_target_bit+= (device_count-dev_seq);
	
	for(bit=0;bit<jseq_target_bit;bit++)
	{
		DriveSignal(SIG_TDI,TDI_HIGH,TCK_TOGGLE,BUFFER_OFF);
	}

	data = ReadTDO(PORT_1,TDI_HIGH,0);

	/* Move JSM to RUNIDLE */
	Js_Updatedr();
	Js_Runidle();

	return data;	
}

/******************************************************************/
/* Name:         SetPortMode                                      */
/*                                                                */
/* Parameters:	 mode                                             */
/*				 - The mode of the port (PM_*)                    */
/*                                                                */
/* Return Value: None.                                            */
/*                                                                */
/* Descriptions: Set the parallel port registers to a particular  */
/*               values.                                          */
/*                                                                */
/******************************************************************/
void SetPortMode(int mode)
{
	/* write to Port 0 and Port 2 with predefined values */
	port_data[0] = port_mode_data[mode][0];
	port_data[2] = port_mode_data[mode][2];
	WritePort( PORT_0, port_data[0], BUFFER_OFF );
	WritePort( PORT_2, port_data[2], BUFFER_OFF );
}

