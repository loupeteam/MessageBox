/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: Console
 * File: GetConsole.c
 * Author: Josh
 * Created: June 24, 2013
 ********************************************************************
 * Implementation of library Console
 ********************************************************************/

#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif

#include "MessageBox.h"
#include "MessageBox_Global.h"

#ifdef __cplusplus
	};
#endif

/* TODO: Add your comment here */
unsigned short MessageBox_Get(unsigned short ID , unsigned long MessageBox )
{
	if ( MessageBox == 0 ){
		return MESSAGE_ERR_INVALID_POINTER;	
		}
	
	if (ID > MESSAGEBOX_MAX){
		*(UDINT*)MessageBox = 0;
		return MESSAGE_ERR_INVALID_ID;
	}
			
	*(UDINT*)MessageBox = (UDINT)MessageBoxList[ID];
	if( MessageBoxList[ID] != 0 ){
		return ERR_OK;	
	}
	else{
		return MESSAGE_ERR_UNINITIALIZED;	
	}
		
}
