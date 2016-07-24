/******************************************************************/
/*                                                                */
/* Module:       jb_device_info.h                                 */
/*                                                                */
/* Descriptions: Contain information of Altera devices.           */
/*                                                                */
/* Revisions:   1.0 02/22/02                                      */
/*				 .2 10/23/02									  */
/*				 Stratix JTAG ID-Code added						  */
/*				 .3 1/24/03										  */
/*				 Cyclone JTAG ID-Code added						  */
/*				 .4 6/3/03										  */
/*				 Stratix GX JTAG ID-Code added					  */
/*				 1C4 JTAG ID-Code added							  */
/*				 .5 6/1/04										  */
/*				 Stratix II EP2S60 JTAG ID-Code added			  */
/*				 .6 1/28/05										  */
/*				 Stratix II JTAG ID-Code added					  */
/*               Cyclone II EP2C35 JTAG ID-Code added			  */
/*				 .7 11/15/05									  */
/*               Cyclone II JTAG ID-Code added					  */
/*				 .8 05/29/06									  */
/*               BYPASS_DEV10 device info added					  */
/*				 .9 01/24/07									  */
/*				 Stratix II GX JTAG ID-Code added				  */
/*               Cyclone III EP3C25 JTAG ID-Code added			  */
/*		    2.0 	 04/26/07						 	          */
/*			Cyclone III all devices densities and package         */
/*			support added										  */
/*			2.1		 06/11/07									  */
/*			Arria GX all devices densities and package            */
/*			support added	                                      */
/*			Stratix III all devices densities and package         */
/*			support added										  */
/*			2.2		03/12/2009									  */
/*			Cyclone II EP2C15F256 JTAG ID-Code added			  */
/*			Cyclone II EP2C15F484 JTAG ID-Code added			  */	
/*			Stratix IV GX,E,GT all device densities and package   */
/*			support added										  */	
/*			2.3		 06/01/09									  */
/*			Cyclone III LS all devices densities and package      */
/*			support added	                                      */
/*			2.4		03/24/2010									  */
/*			Arria II GX and Cyclone IV all devices				  */
/*			densities and package support added					  */
/*			2.5		08/01/2012									  */
/*			Stratix V all devices densities	and package			  */
/*			support added			                    		  */
/*			Arria V GT and GX devices densities	and package		  */
/*			support added			                    		  */
/*			2.6		11/15/2012									  */
/*			Updated Stratix V, Arria V GT & GX devices, added	  */
/*			Arria V GZ, Arria V SoC devices, Cyclone V and		  */
/*			Cyclone V SoC devices.								  */
/******************************************************************/

#ifndef JB_DEVICE_INFO_H
#define JB_DEVICE_INFO_H


#define MAX_DEV_FAMILY 2		/*how many device family listed? */
#define MAX_DEV_LIST   3

int start_of_device_family[MAX_DEV_FAMILY] = {
	191, /* NON ALTR */
	335 /* CYCLONE IV */
};

int MAX_JTAG_INIT_CLOCK[MAX_DEV_FAMILY] = {
	300,  /* NON ALTR */
	3192  /* CYCLONE IV */
};

char family_name[MAX_DEV_FAMILY][11] = {
	{"BYPASS DEV"},
	{"CYCLONE IV"}
};

char device_name[MAX_DEV_LIST][13] = {
	{"BYPASS_DEV10"},//		191		//Bypass device on the JTAG chain	
/* Cyclone IV */
	{"EP4CE6E22"},//		335
	{"EP4CE22F17"}//		343
	};


unsigned int device_info[MAX_DEV_LIST][4] = {
/* Device,        Idcode,   Max      Conf_done Instruction */
/*                          JTAG     JTAG      Length      */
/*                          Sequence,Sequence,             */ 
/* BYPASS_DEVICE */
/* BYPASS_DEV10  */	 {0x0000000, 000, 000, 10},		//191		//Bypass device with 10-bit Instruction Length
/* Cyclone IV */
	/*EP4CE6E22*/  {0x20F10DD, 201, 126, 10},		//335
	/*EP4CE22F17*/ {0x20F30DD, 244, 149, 10}		//343
	};

#endif
