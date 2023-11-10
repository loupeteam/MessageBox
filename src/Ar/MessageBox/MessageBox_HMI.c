/*
 * File: MessageBox_HMI.c
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

unsigned long MessageBox_HMI(struct MessageBox_HMI_typ* MessageBox)
{

	unsigned short i;
	MessageBox_typ *pMsgBox;

	//Latch commands
	if( !MessageBox->Buttons1.CMD )
		MessageBox->Internal._CMD[0]= 0;
	if( !MessageBox->Buttons2.CMD )
		MessageBox->Internal._CMD[1]= 0;
	if( !MessageBox->Buttons3.CMD )
		MessageBox->Internal._CMD[2]= 0;
	if( !MessageBox->Buttons4.CMD )
		MessageBox->Internal._CMD[3]= 0;
	if( !MessageBox->Buttons5.CMD )
		MessageBox->Internal._CMD[4]= 0;
		
	//Get the Message box that we want
	if(MessageBox_Get(0,(UDINT)&pMsgBox)==ERR_OK){

		//If there are messages get it
		if(pMsgBox->Internal.Buffer.NumberValues>0){
				
			//Read message
			BufferCopyItems((UDINT)&(pMsgBox->Internal.Buffer),0,1,(UDINT)&MessageBox->Internal.Message,0);		
				
			//Show the message
			MessageBox->Internal._Show = 1;
		}
	}		
					
	//Handle the commands
	if(MessageBox->Buttons5.CMD && !MessageBox->Internal._CMD[4]){
		if(MessageBox->Internal.Message.pUserString!=0){
			strcpy((char*)MessageBox->Internal.Message.pUserString,MessageBox->TextSnippets.UserString);
		}
		
		if(MessageBox->Internal.Message.Buttons[4].pCmd)
			*((BOOL*)MessageBox->Internal.Message.Buttons[4].pCmd) = 1;
		MessageBox->Internal._CMD[4]= 1;
		MessageBox->Internal._Show = 0;

		//Remove the message from the buffer
		BufferRemoveTop((UDINT)&(pMsgBox->Internal.Buffer));		
	
		MessageBox->Buttons1.CMD=	0;
		MessageBox->Buttons2.CMD=	0;
		MessageBox->Buttons3.CMD=	0;
		MessageBox->Buttons4.CMD=	0;
		MessageBox->Buttons5.CMD=	0;
			
	}else if(MessageBox->Buttons4.CMD && !MessageBox->Internal._CMD[3]){
		if(MessageBox->Internal.Message.pUserString!=0){
			strcpy((char*)MessageBox->Internal.Message.pUserString,MessageBox->TextSnippets.UserString);
		}
		
		if(MessageBox->Internal.Message.Buttons[3].pCmd)
			*((BOOL*)MessageBox->Internal.Message.Buttons[3].pCmd) = 1;
		MessageBox->Internal._CMD[3]= 1;
		MessageBox->Internal._Show = 0;

		//Remove the message from the buffer
		BufferRemoveTop((UDINT)&(pMsgBox->Internal.Buffer));		
	
		MessageBox->Buttons1.CMD=	0;
		MessageBox->Buttons2.CMD=	0;
		MessageBox->Buttons3.CMD=	0;
		MessageBox->Buttons4.CMD=	0;
		MessageBox->Buttons5.CMD=	0;
			
	}else if(MessageBox->Buttons3.CMD && !MessageBox->Internal._CMD[2]){
		if(MessageBox->Internal.Message.pUserString!=0){
			strcpy((char*)MessageBox->Internal.Message.pUserString,MessageBox->TextSnippets.UserString);
		}
		
		if(MessageBox->Internal.Message.Buttons[2].pCmd)
			*((BOOL*)MessageBox->Internal.Message.Buttons[2].pCmd) = 1;
		MessageBox->Internal._CMD[2]= 1;
		MessageBox->Internal._Show = 0;

		//Remove the message from the buffer
		BufferRemoveTop((UDINT)&(pMsgBox->Internal.Buffer));		
	
		MessageBox->Buttons1.CMD=	0;
		MessageBox->Buttons2.CMD=	0;
		MessageBox->Buttons3.CMD=	0;
		MessageBox->Buttons4.CMD=	0;
		MessageBox->Buttons5.CMD=	0;
			
	}else if(MessageBox->Buttons2.CMD && !MessageBox->Internal._CMD[1]){
		if(MessageBox->Internal.Message.pUserString!=0){
			strcpy((char*)MessageBox->Internal.Message.pUserString,MessageBox->TextSnippets.UserString);
		}
		if(MessageBox->Internal.Message.Buttons[1].pCmd)
			*((BOOL*)MessageBox->Internal.Message.Buttons[1].pCmd) = 1;
		MessageBox->Internal._CMD[1]= 1;
		MessageBox->Internal._Show = 0;

		//Remove the message from the buffer
		BufferRemoveTop((UDINT)&(pMsgBox->Internal.Buffer));

		MessageBox->Buttons1.CMD=	0;
		MessageBox->Buttons2.CMD=	0;
		MessageBox->Buttons3.CMD=	0;
		MessageBox->Buttons4.CMD=	0;
		MessageBox->Buttons5.CMD=	0;
				
	}else if(MessageBox->Buttons1.CMD && !MessageBox->Internal._CMD[0]){
		if(MessageBox->Internal.Message.pUserString!=0){
			strcpy((char*)MessageBox->Internal.Message.pUserString,MessageBox->TextSnippets.UserString);
		}
		
		if(MessageBox->Internal.Message.Buttons[0].pCmd)
			*((BOOL*)MessageBox->Internal.Message.Buttons[0].pCmd) = 1;
		MessageBox->Internal._CMD[0]= 1;
		MessageBox->Internal._Show = 0;

		//Remove the message from the buffer
		BufferRemoveTop((UDINT)&(pMsgBox->Internal.Buffer));		
	
		MessageBox->Buttons1.CMD=	0;
		MessageBox->Buttons2.CMD=	0;
		MessageBox->Buttons3.CMD=	0;
		MessageBox->Buttons4.CMD=	0;
		MessageBox->Buttons5.CMD=	0;
			
	}else if( MessageBox->Internal.Message.MessageID == 0){

		MessageBox->Internal._Show = 0;			

		//Remove the message from the buffer
		BufferRemoveTop((UDINT)&(pMsgBox->Internal.Buffer));	

		MessageBox->Buttons1.CMD=	0;
		MessageBox->Buttons2.CMD=	0;
		MessageBox->Buttons3.CMD=	0;
		MessageBox->Buttons4.CMD=	0;
		MessageBox->Buttons5.CMD=	0;
	}
	
	//Force a delay between showing message boxes.
	// Detect this with a negative edge of the show bit and if the messageID changes while the layer is active
	if( MessageBox->Internal._ShowEdge && !MessageBox->Internal._Show 
	|| ((MessageBox->Internal._MessageID != MessageBox->Internal.Message.MessageID) && MessageBox->Layer.Active)
	){
		MessageBox->Internal._ShowDelay.IN= 0;	
	}
	MessageBox->Internal._MessageID = MessageBox->Internal.Message.MessageID;
	MessageBox->Internal._ShowEdge = MessageBox->Internal._Show;	

	MessageBox->Internal._ShowDelay.PT= 500;
	TON(&MessageBox->Internal._ShowDelay);
	MessageBox->Internal._ShowDelay.IN= 1;
	
	
	//If we aren't showing, get the next one
	// Assuming the minimum delay is met
	if(MessageBox->Internal._Show == 0 || !MessageBox->Internal._ShowDelay.Q){	
		
		//Clear old data
		memset( &(MessageBox->Buttons1),0,sizeof(MessageBox->Buttons1));
		memset( &(MessageBox->Buttons2),0,sizeof(MessageBox->Buttons2));
		memset( &(MessageBox->Buttons3),0,sizeof(MessageBox->Buttons3));
		memset( &(MessageBox->Buttons4),0,sizeof(MessageBox->Buttons4));
		memset( &(MessageBox->Buttons5),0,sizeof(MessageBox->Buttons5));
		memset( &(MessageBox->Prompt),0,sizeof(MessageBox->Prompt));
		memset( &(MessageBox->TextSnippets),0,sizeof(MessageBox->TextSnippets));
		memset( &(MessageBox->Internal.Message),0,sizeof(MessageBox->Internal.Message));
		
		MessageBox->Layer.Status=		1;
		MessageBox->Layer.Active=		0;
		MessageBox->Buttons1.StatusDP=	1;
		MessageBox->Buttons2.StatusDP=	1;
		MessageBox->Buttons3.StatusDP=	1;
		MessageBox->Buttons4.StatusDP=	1;
		MessageBox->Buttons5.StatusDP=	1;
		MessageBox->UserInput.StatusDP= 1;			
		return 0;
	}
	else{		
		//Show the message box
		MessageBox->Layer.Status=		0;
		MessageBox->Layer.Active=		1;
		MessageBox->Buttons1.StatusDP = MessageBox->Internal.Message.Buttons[0].pCmd == 0 && (MessageBox->Internal.Message.Buttons[0].Index == 0) && (MessageBox->Internal.Message.Buttons[0].pText==0);	
		MessageBox->Buttons2.StatusDP = MessageBox->Internal.Message.Buttons[1].pCmd == 0 && (MessageBox->Internal.Message.Buttons[1].Index == 0) && (MessageBox->Internal.Message.Buttons[1].pText==0);
		MessageBox->Buttons3.StatusDP = MessageBox->Internal.Message.Buttons[2].pCmd == 0 && (MessageBox->Internal.Message.Buttons[2].Index == 0) && (MessageBox->Internal.Message.Buttons[2].pText==0);	
		MessageBox->Buttons4.StatusDP = MessageBox->Internal.Message.Buttons[3].pCmd == 0 && (MessageBox->Internal.Message.Buttons[3].Index == 0) && (MessageBox->Internal.Message.Buttons[3].pText==0);	
		MessageBox->Buttons5.StatusDP = MessageBox->Internal.Message.Buttons[4].pCmd == 0 && (MessageBox->Internal.Message.Buttons[4].Index == 0) && (MessageBox->Internal.Message.Buttons[4].pText==0);

		//If the box isn't showing yet we should grab the starting text
		if((MessageBox->UserInput.StatusDP & 1) != 0){
			if(MessageBox->Internal.Message.pUserString!=0){
				strcpy(MessageBox->TextSnippets.UserString  ,(void *)MessageBox->Internal.Message.pUserString);
			}
			else{
				strcpy(MessageBox->TextSnippets.UserString  ,"");		
			}		
		}

		//Set the status here to ensure we get a startup text
		MessageBox->UserInput.StatusDP= MessageBox->Internal.Message.pUserString == 0;			

		//Get the text
		if(MessageBox->Internal.Message.Prompt.pText!=0){
			strcpy(MessageBox->TextSnippets.Message  ,(void *)MessageBox->Internal.Message.Prompt.pText);
		}
		else{
			strcpy(MessageBox->TextSnippets.Message  ,"");		
		}
		if(MessageBox->Internal.Message.Buttons[0].pText!=0){
			strcpy(MessageBox->TextSnippets.Buttons1 ,(void*)MessageBox->Internal.Message.Buttons[0].pText);
		}
		else{
			strcpy(MessageBox->TextSnippets.Buttons1 ,"");		
		}
		if(MessageBox->Internal.Message.Buttons[1].pText!=0){
			strcpy(MessageBox->TextSnippets.Buttons2 ,(void*)MessageBox->Internal.Message.Buttons[1].pText);
		}
		else{
			strcpy(MessageBox->TextSnippets.Buttons2 ,"");		
		}
		if(MessageBox->Internal.Message.Buttons[2].pText!=0){
			strcpy(MessageBox->TextSnippets.Buttons3 ,(void*)MessageBox->Internal.Message.Buttons[2].pText);
		}
		else{
			strcpy(MessageBox->TextSnippets.Buttons3 ,"");		
		}
		if(MessageBox->Internal.Message.Buttons[3].pText!=0){
			strcpy(MessageBox->TextSnippets.Buttons4 ,(void*)MessageBox->Internal.Message.Buttons[3].pText);
		}
		else{
			strcpy(MessageBox->TextSnippets.Buttons4 ,"");		
		}
		if(MessageBox->Internal.Message.Buttons[4].pText!=0){
			strcpy(MessageBox->TextSnippets.Buttons5 ,(void*)MessageBox->Internal.Message.Buttons[4].pText);
		}
		else{
			strcpy(MessageBox->TextSnippets.Buttons5 ,"");		
		}
		//Get text indexes
		MessageBox->Prompt.IndexDP=		MessageBox->Internal.Message.Prompt.Index;
		MessageBox->Buttons1.IndexDP=	MessageBox->Internal.Message.Buttons[0].Index;
		MessageBox->Buttons2.IndexDP=	MessageBox->Internal.Message.Buttons[1].Index;
		MessageBox->Buttons3.IndexDP=	MessageBox->Internal.Message.Buttons[2].Index;
		MessageBox->Buttons4.IndexDP=	MessageBox->Internal.Message.Buttons[3].Index;
		MessageBox->Buttons5.IndexDP=	MessageBox->Internal.Message.Buttons[4].Index;
		
		if(MessageBox->Buttons1.StatusDP && MessageBox->Buttons2.StatusDP && MessageBox->Buttons3.StatusDP && MessageBox->Buttons4.StatusDP && MessageBox->Buttons5.StatusDP){
			strcpy(MessageBox->TextSnippets.Buttons1 ,"Dismiss");
			MessageBox->Buttons1.StatusDP=	0;
		}	

		return MessageBox->Internal.Message.MessageID;
		
	}	
}
