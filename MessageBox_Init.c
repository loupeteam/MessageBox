/********************************************************************
 * COPYRIGHT --  
 ********************************************************************
 * Library: MessageBox
 * File: MessageBox_Init.c
 * Author: Josh
 * Created: Aug 1, 2013
 ********************************************************************
 * Implementation of library MessageBox
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
unsigned long MessageBox_Init( unsigned char QueueSize)
{

	MessageBox_typ * pMessageBox;
		
	pMessageBox = MessageBoxList[0];
	
	if(pMessageBox != 0){
		return MESSAGE_ERR_ALREADY_INIT;
	}
	
	if( TMP_alloc(sizeof(MessageBox_typ),(void**)&pMessageBox) != 0){
		return MESSAGE_ERR_OUT_OF_MEMORY;
	}
	
	memset((void*)pMessageBox, 0 , sizeof(MessageBox_typ));

	BufferInit((UDINT)&(pMessageBox->Internal.Buffer), QueueSize, sizeof(MessageBox_Message_typ) ); 
	
	MessageBoxList[0] = pMessageBox;

	return ERR_OK;
	
}
