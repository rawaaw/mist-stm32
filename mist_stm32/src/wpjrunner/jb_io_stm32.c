/******************************************************************/
/*                                                                */
/* Module:       jb_io.c                                          */
/*                                                                */
/* Descriptions: Manages I/O related routines, file and string    */
/*               processing functions.                            */
/*                                                                */
/******************************************************************/

#include <stdio.h>
#include "jb_io.h"
#include "hardware.h"

#define MAX_FILE_LINE_LENGTH            160


/******************************************************************/
/* Name:         ReadPort                                         */
/*                                                                */
/* Parameters:   port                                             */
/*               -the index of port from the parallel port base   */
/*                address.                                        */
/*                                                                */
/* Return Value: Value of the port.                               */
/*               		                                          */
/* Descriptions: Read the value of the port registers.            */
/*                                                                */
/******************************************************************/
int ReadPort(int port)
{
	int data = 0;

	return (data & 0xff);
}

/******************************************************************/
/* Name:         WritePort                                        */
/*                                                                */
/* Parameters:   port,data,buffer_enable                          */
/*               -port is the index from the parallel port base   */
/*                address.                                        */
/*               -data is the value to dump to the port.          */
/*               -purpose of write.                               */
/*                                                                */
/* Return Value: None.                                            */
/*               		                                          */
/* Descriptions: Write "data" to "port" registers. When dump to   */
/*               port 0,if "buffer_enable"=1, processes in		  */
/*				 "port_io_buffer" are flushed when				  */
/*               "PORT_IO_BUFFER_SIZE" is reached			      */
/*               If "buffer_enable"=0,"data" is dumped to port 0  */
/*               at once.                                         */
/*                                                                */
/******************************************************************/
void WritePort(int port,int data,int buffer_enable)
{
	int status = 0;

	/* Put your I/O rountines here */
}

/*****************************/
/*                           */
/* File processing functions */
/*                           */
/*****************************/

int jb_fopen(char* argv,char* mode)
{
	return 0;
}

int	jb_fclose(int file_id)
{
	return 0;
}

int jb_fseek(int finputid,int start,int end)
{
	return 0;
}

int jb_ftell(int finputid)
{
	return 0;
}

int jb_fgetc(int finputid)
{
	return 0;
}

char* jb_fgets(char* buffer, int finputid)
{
	return (char*)0;
}

