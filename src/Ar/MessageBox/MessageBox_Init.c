/*
 * File: MessageBox_Init.c
 * Copyright (c) 2023 Loupe
 * https://loupe.team
 * 
 * This file is part of MessageBox, licensed under the MIT License.
 * 
 */

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

MessageBox_typ *MessageBoxList[MESSAGEBOX_MAX + 1];
UDINT CurrentMessageID;

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
