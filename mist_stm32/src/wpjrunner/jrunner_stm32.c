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
#include <string.h>
#include "jb_io.h"
#include "jb_jtag.h"
#include "jb_const.h"
#include "jb_device.h"
#include "hardware.h"

/* JRunner Controller Functions */
void SetAltDev        (int, char*);
int GetDevIdCode      (int);
int  VerifyChain      (void);
void DriveSignal      (int signal,int data,int clk,int buffer_enable);
int  CheckStatus      (int dev_seq);
void Startup          (int dev_seq);

/* JTAG instruction lengths of all devices */
int  ji_info[MAX_DEVICE_ALLOW];


/******************************************************************/
/* Name:         SetAltDev                                        */
/*                                                                */
/* Parameters:   dev_seq                                          */
/*               -dev_seq is the device sequence in JTAG chain.   */
/*                                                                */
/* Return Value: None.                                            */
/*                                                                */
/* Descriptions: The function stubs reading of CDF file           */
/******************************************************************/
void SetAltDev(int dev_seq, char*dev_name){
    strcpy(device_list[0].partname, dev_name);
}

/******************************************************************/
/* Name:         CheckAltDev                                      */
/*                                                                */
/* Parameters:   dev_seq                                          */
/*               -dev_seq is the device sequence in JTAG chain.   */
/*                                                                */
/* Return Value: None.                                            */
/*               		                                          */
/* Descriptions: The function matches the partname specified in   */
/*               CDF with Altera devices list. If matches, the    */
/*               JTAG chain information will be updated in device */
/*               _list. The action code is updated by ActionCode. */
/*               If the partname is not recognized, the device    */
/*               will be bypassed.                                */
/*                                                                */
/******************************************************************/
void CheckAltDev(int dev_seq)
{
	int i,j,altera=0;
	dev_seq--;

	for(i=0;i<MAX_DEV_LIST;i++)
	{
		if(!strcmp(device_list[dev_seq].partname,device_name[i]))
		{
			if(!(device_info[i][0] && device_info[i][1] && device_info[i][2]))
			{
				device_list[dev_seq].inst_len = device_info[i][3];
				ji_info[dev_seq]                    = device_list[dev_seq].inst_len;
				iprintf("Warning: Device #%d not supported! Bypassed!\n",dev_seq+1);
			}
			else
			{
				device_list[dev_seq].idcode         = device_info[i][0];
				device_list[dev_seq].jseq_max       = device_info[i][1];
				device_list[dev_seq].jseq_conf_done = device_info[i][2];
				device_list[dev_seq].inst_len       = device_info[i][3];
				ji_info[dev_seq]                    = device_list[dev_seq].inst_len;
				altera = 1;

				break;
			}
		}
	}

/* [chtong,1/6/03,jrunner.c,ver 1.3] The following section has been modified*/
/* [chtong,6/2/03,jrunner.c,ver 1.4] The following section has been modified*/
/* Source code before version 1.2 cannot print family device if the device to be configured is the last family member*/
	for(j=0;j<MAX_DEV_FAMILY;j++)
	{
		if(i<start_of_device_family[j])
		{
			device_family = j-1;
			iprintf("family: %s(%d)\n",family_name[j-1],j);
			break;
		}
		/* Source code before version 1.2 cannot print family device if the device to be configured is the last family member*/
		/* add-in && altera ==1 in version 1.4*/
		else if (j==MAX_DEV_FAMILY-1 && i>=start_of_device_family[MAX_DEV_FAMILY-1] && altera ==1)
		{
			device_family = MAX_DEV_FAMILY-1;
			iprintf("family: %s(%d)\n",family_name[MAX_DEV_FAMILY-1],MAX_DEV_FAMILY);
		}
	}

	if(!altera)
	{
		device_list[dev_seq].idcode=0;
		device_list[dev_seq].jseq_max=0;
		device_list[dev_seq].jseq_conf_done=0;
		device_list[dev_seq].action='B';
	}
}


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

        /* initialize ji_info[MAX_DEVICE_ALLOW] */
        for(i=0; i < MAX_DEVICE_ALLOW; i++)
          ji_info[i] = 10;
	
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

/******************************************************************/
/* Name:         GetDevIdCode                                     */
/*                                                                */
/******************************************************************/
int GetDevIdCode(int dev_idx){
  return device_list[dev_idx].idcode;
}
