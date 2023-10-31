 /*
 * File: MessageBox_MsgHandling.c
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

unsigned long MessageBox_NewID(){
	CurrentMessageID++;	
	if(CurrentMessageID <=  MESSAGE_ERR_ + 1){
		CurrentMessageID= MESSAGE_ERR_ + 1;
	}
	return CurrentMessageID;
}

//This is the main working function to add a structure. 
//All of the add functions eventually call this one.
unsigned long MessageBox_AddMsgStructure(unsigned long Message , BOOL Priority  ){

	MessageBox_typ *pMessageBox= MessageBoxList[0];
	
	if(pMessageBox == 0 || Message == 0){
		return MESSAGE_ERR_UNINITIALIZED;
	}

	((MessageBox_Message_typ*)Message)->MessageID=	MessageBox_NewID();
	
	
	if(Priority){
		BufferAddToTop( (UDINT)&(pMessageBox->Internal.Buffer), Message );		
	}else{
		if( pMessageBox->Internal.Buffer.NumberValues == pMessageBox->Internal.Buffer.MaxValues){		
			return MESSAGE_ERR_BUFFER_FULL;	
		}		
		BufferAddToBottom( (UDINT)&(pMessageBox->Internal.Buffer), Message );	
	}
	return ((MessageBox_Message_typ*)Message)->MessageID;
}

//This function adds a normal priority message to the bottom of the list
//This function handles multiplexing inputs.
unsigned long MessageBox_AddMsg(unsigned long Message, unsigned long Button1Text, unsigned long pCommand1, unsigned long Button2Text, unsigned long pCommand2)
{
	MessageBox_Message_typ temp_message;
	
	memset(&temp_message, 0, sizeof(temp_message));
		
	if(Message>255){
		temp_message.Prompt.pText=	Message;
		temp_message.Prompt.Index=	0;
	}
	else{
		temp_message.Prompt.pText=	0;
		temp_message.Prompt.Index=	Message;	
	}
	if(Button1Text>255){
		temp_message.Buttons[0].pText=	Button1Text;
		temp_message.Buttons[0].Index=	0;
	}
	else{
		temp_message.Buttons[0].pText=	0;		
		temp_message.Buttons[0].Index=	Button1Text;		
	}
	if(Button2Text>255){
		temp_message.Buttons[1].pText=	Button2Text;
		temp_message.Buttons[1].Index=	0;		
	}
	else{
		temp_message.Buttons[1].pText=	0;
		temp_message.Buttons[1].Index=	Button2Text;				
	}
	
	temp_message.Buttons[0].pCmd = pCommand1;
	temp_message.Buttons[1].pCmd = pCommand2;
	
	return MessageBox_AddMsg_full(0,
		temp_message.Prompt.pText,
		temp_message.Prompt.Index,
		(UDINT)temp_message.Buttons,
		0);

}

//This function adds a high priority message to the top of the list.
//It will possible bump off the last one in the buffer
//This function handles multiplexing inputs.
unsigned long MessageBox_AddMsgTop(unsigned long Message, unsigned long Button1Text, unsigned long pCommand1, unsigned long Button2Text, unsigned long pCommand2)
{
	MessageBox_Message_typ temp_message;
	memset(&temp_message, 0, sizeof(temp_message));
	
	if(Message>255){
		temp_message.Prompt.pText=	Message;
		temp_message.Prompt.Index=	0;
	}
	else{
		temp_message.Prompt.pText=	0;
		temp_message.Prompt.Index=	Message;	
	}
	if(Button1Text>255){
		temp_message.Buttons[0].pText=	Button1Text;
		temp_message.Buttons[0].Index=	0;
	}
	else{
		temp_message.Buttons[0].pText=	0;		
		temp_message.Buttons[0].Index=	Button1Text;		
	}
	if(Button2Text>255){
		temp_message.Buttons[1].pText=	Button2Text;
		temp_message.Buttons[1].Index=	0;		
	}
	else{
		temp_message.Buttons[1].pText=	0;
		temp_message.Buttons[1].Index=	Button2Text;				
	}
	
	temp_message.Buttons[0].pCmd = pCommand1;
	temp_message.Buttons[1].pCmd = pCommand2;
	
	return MessageBox_AddMsg_full(0,
		temp_message.Prompt.pText,
		temp_message.Prompt.Index,
		(UDINT)temp_message.Buttons,
		1);

}

// This function adds a normal priority 3-button message to the bottom of the list
// This function handles sparsely-populated button inputs (0 for unused)
unsigned long MessageBox_Add3BtnMsg(unsigned long Message, unsigned long Button1Text, unsigned long pCommand1, unsigned long Button2Text, unsigned long pCommand2, unsigned long Button3Text, unsigned long pCommand3)
{
	MessageBox_Message_typ temp_message;
	memset( &temp_message, 0, sizeof(temp_message));
		
	if(Message>255){
		temp_message.Prompt.pText=	Message;
		temp_message.Prompt.Index=	0;
	}
	else{
		temp_message.Prompt.pText=	0;
		temp_message.Prompt.Index=	Message;	
	}
	if(Button1Text>255){
		temp_message.Buttons[0].pText=	Button1Text;
		temp_message.Buttons[0].Index=	0;
	}
	else{
		temp_message.Buttons[0].pText=	0;		
		temp_message.Buttons[0].Index=	Button1Text;		
	}
	if(Button2Text>255){
		temp_message.Buttons[1].pText=	Button2Text;
		temp_message.Buttons[1].Index=	0;		
	}
	else{
		temp_message.Buttons[1].pText=	0;
		temp_message.Buttons[1].Index=	Button2Text;				
	}
	if(Button3Text>255){
		temp_message.Buttons[2].pText=	Button3Text;
		temp_message.Buttons[2].Index=	0;		
	}
	else{
		temp_message.Buttons[2].pText=	0;
		temp_message.Buttons[2].Index=	Button3Text;				
	}
	
	temp_message.Buttons[0].pCmd = pCommand1;
	temp_message.Buttons[1].pCmd = pCommand2;
	temp_message.Buttons[2].pCmd = pCommand3;

	return MessageBox_AddMsg_full(0,
		temp_message.Prompt.pText,
		temp_message.Prompt.Index,
		(UDINT)temp_message.Buttons,
		0);

}

// This function adds a high priority 3-button message to the top of the list.
// It will possible bump off the last one in the buffer
// This function handles sparsely-populated button inputs (0 for unused)
unsigned long MessageBox_Add3BtnMsgTop(unsigned long Message, unsigned long Button1Text, unsigned long pCommand1, unsigned long Button2Text, unsigned long pCommand2, unsigned long Button3Text, unsigned long pCommand3)
{
	MessageBox_Message_typ temp_message;
	memset( &temp_message, 0, sizeof(temp_message));
	
	if(Message>255){
		temp_message.Prompt.pText=	Message;
		temp_message.Prompt.Index=	0;
	}
	else{
		temp_message.Prompt.pText=	0;
		temp_message.Prompt.Index=	Message;	
	}
	if(Button1Text>255){
		temp_message.Buttons[0].pText=	Button1Text;
		temp_message.Buttons[0].Index=	0;
	}
	else{
		temp_message.Buttons[0].pText=	0;		
		temp_message.Buttons[0].Index=	Button1Text;		
	}
	if(Button2Text>255){
		temp_message.Buttons[1].pText=	Button2Text;
		temp_message.Buttons[1].Index=	0;		
	}
	else{
		temp_message.Buttons[1].pText=	0;
		temp_message.Buttons[1].Index=	Button2Text;				
	}
	if(Button3Text>255){
		temp_message.Buttons[2].pText=	Button3Text;
		temp_message.Buttons[2].Index=	0;		
	}
	else{
		temp_message.Buttons[2].pText=	0;
		temp_message.Buttons[2].Index=	Button3Text;				
	}

	temp_message.Buttons[0].pCmd = pCommand1;
	temp_message.Buttons[1].pCmd = pCommand2;
	temp_message.Buttons[2].pCmd = pCommand3;
	
	return MessageBox_AddMsg_full(0,
		temp_message.Prompt.pText,
		temp_message.Prompt.Index,
		(UDINT)temp_message.Buttons,
		1);

}

// This function adds an N-Button MessageBox (where N <= 5) to the list
// This function handles sparsely-populated button inputs (0 for unused)
unsigned long MessageBox_AddNBtnMsg(unsigned long Message, unsigned long Button1Text, unsigned long pCommand1, unsigned long Button2Text, unsigned long pCommand2, unsigned long Button3Text, unsigned long pCommand3, unsigned long Button4Text, unsigned long  pCommand4, unsigned long Button5Text, unsigned long pCommand5)
{
	MessageBox_Message_typ temp_message;
	memset(&temp_message, 0, sizeof(temp_message));
	
	if(Message>255){
		temp_message.Prompt.pText=	Message;
		temp_message.Prompt.Index=	0;
	}
	else{
		temp_message.Prompt.pText=	0;
		temp_message.Prompt.Index=	Message;	
	}
	if(Button1Text>255){
		temp_message.Buttons[0].pText=	Button1Text;
		temp_message.Buttons[0].Index=	0;
	}
	else{
		temp_message.Buttons[0].pText=	0;		
		temp_message.Buttons[0].Index=	Button1Text;		
	}
	if(Button2Text>255){
		temp_message.Buttons[1].pText=	Button2Text;
		temp_message.Buttons[1].Index=	0;
	}
	else{
		temp_message.Buttons[1].pText=	0;
		temp_message.Buttons[1].Index=	Button2Text;				
	}
	if(Button3Text>255){
		temp_message.Buttons[2].pText=	Button3Text;
		temp_message.Buttons[2].Index=	0;
	}
	else{
		temp_message.Buttons[2].pText=	0;
		temp_message.Buttons[2].Index=	Button3Text;				
	}
	if(Button4Text>255){
		temp_message.Buttons[3].pText=	Button4Text;
		temp_message.Buttons[3].Index=	0;
	}
	else{
		temp_message.Buttons[3].pText=	0;
		temp_message.Buttons[3].Index=	Button4Text;				
	}
	if(Button5Text>255){
		temp_message.Buttons[4].pText=	Button5Text;
		temp_message.Buttons[4].Index=	0;
	}
	else{
		temp_message.Buttons[4].pText=	0;
		temp_message.Buttons[4].Index=	Button5Text;				
	}

	temp_message.Buttons[0].pCmd = pCommand1;
	temp_message.Buttons[1].pCmd = pCommand2;
	temp_message.Buttons[2].pCmd = pCommand3;
	temp_message.Buttons[3].pCmd = pCommand4;
	temp_message.Buttons[4].pCmd = pCommand5;
	
	return MessageBox_AddMsg_full(0,
		temp_message.Prompt.pText,
		temp_message.Prompt.Index,
		(UDINT)temp_message.Buttons,
		0);
	
}


// This function adds an N-Button MessageBox (where N <= 5) to the top of the list
// This function handles sparsely-populated button inputs (0 for unused)
// Might bump last item off buffer
unsigned long MessageBox_AddNBtnMsgTop(unsigned long Message, unsigned long Button1Text, unsigned long pCommand1, unsigned long Button2Text, unsigned long pCommand2, unsigned long Button3Text, unsigned long pCommand3, unsigned long Button4Text, unsigned long  pCommand4, unsigned long Button5Text, unsigned long pCommand5)
{
	MessageBox_Message_typ temp_message;
	memset( &temp_message, 0, sizeof(temp_message));
	
	if(Message>255){
		temp_message.Prompt.pText=	Message;
		temp_message.Prompt.Index=	0;
	}
	else{
		temp_message.Prompt.pText=	0;
		temp_message.Prompt.Index=	Message;	
	}
	if(Button1Text>255){
		temp_message.Buttons[0].pText=	Button1Text;
		temp_message.Buttons[0].Index=	0;
	}
	else{
		temp_message.Buttons[0].pText=	0;		
		temp_message.Buttons[0].Index=	Button1Text;		
	}
	if(Button2Text>255){
		temp_message.Buttons[1].pText=	Button2Text;
		temp_message.Buttons[1].Index=	0;
	}
	else{
		temp_message.Buttons[1].pText=	0;
		temp_message.Buttons[1].Index=	Button2Text;				
	}
	if(Button3Text>255){
		temp_message.Buttons[2].pText=	Button3Text;
		temp_message.Buttons[2].Index=	0;
	}
	else{
		temp_message.Buttons[2].pText=	0;
		temp_message.Buttons[2].Index=	Button3Text;				
	}
	if(Button4Text>255){
		temp_message.Buttons[3].pText=	Button4Text;
		temp_message.Buttons[3].Index=	0;
	}
	else{
		temp_message.Buttons[3].pText=	0;
		temp_message.Buttons[3].Index=	Button4Text;				
	}
	if(Button5Text>255){
		temp_message.Buttons[4].pText=	Button5Text;
		temp_message.Buttons[4].Index=	0;
	}
	else{
		temp_message.Buttons[4].pText=	0;
		temp_message.Buttons[4].Index=	Button5Text;				
	}

	temp_message.Buttons[0].pCmd = pCommand1;
	temp_message.Buttons[1].pCmd = pCommand2;
	temp_message.Buttons[2].pCmd = pCommand3;
	temp_message.Buttons[3].pCmd = pCommand4;
	temp_message.Buttons[4].pCmd = pCommand5;
	
	return MessageBox_AddMsg_full(0,
		temp_message.Prompt.pText,
		temp_message.Prompt.Index,
		(UDINT)temp_message.Buttons,
		1);
	
}


//This function takes all of the parameters, fills a structure and calls the MessageBox_AddMsgStructure function to get it into the buffer
unsigned long MessageBox_AddMsg_full(unsigned short ID , unsigned long Message, unsigned long MessageIndex, unsigned long Buttons, BOOL Priority ){

	unsigned short i;
	MessageBox_Message_typ temp_message;
	MessageBox_typ *pMessageBox= MessageBoxList[ID];
	MessageBox_Button_typ *btn= (MessageBox_Button_typ*) Buttons;
	
	if(pMessageBox == 0){
		return MESSAGE_ERR_UNINITIALIZED;
	}
	
	temp_message.Prompt.pText=	Message;
	temp_message.Prompt.Index=	MessageIndex;	
			
	for(i = 0; i < 5; i++){
		temp_message.Buttons[i].pCmd= btn[i].pCmd;
		temp_message.Buttons[i].pText= btn[i].pText;
		temp_message.Buttons[i].Index= btn[i].Index;
	}
	
	temp_message.pUserString = 0;
	
	return MessageBox_AddMsgStructure( (UDINT)&temp_message, Priority);			
}

//This function adds a normal priority prompt box to the bottom of the list
//This function handles multiplexing inputs.
unsigned long PromptBox_AddMsg(unsigned long Message, unsigned long pInputString,unsigned long Button1Text, unsigned long pCommand1, unsigned long Button2Text, unsigned long pCommand2)
{
	MessageBox_Message_typ temp_message;
	memset( &temp_message, 0, sizeof(temp_message));
		
	if(Message>255){
		temp_message.Prompt.pText=	Message;
		temp_message.Prompt.Index=	0;
	}
	else{
		temp_message.Prompt.pText=	0;
		temp_message.Prompt.Index=	Message;	
	}
	if(Button1Text>255){
		temp_message.Buttons[0].pText=	Button1Text;
		temp_message.Buttons[0].Index=	0;
	}
	else{
		temp_message.Buttons[0].pText=	0;		
		temp_message.Buttons[0].Index=	Button1Text;		
	}
	if(Button2Text>255){
		temp_message.Buttons[1].pText=	Button2Text;
		temp_message.Buttons[1].Index=	0;		
	}
	else{
		temp_message.Buttons[1].pText=	0;
		temp_message.Buttons[1].Index=	Button2Text;				
	}
	
	temp_message.pUserString = pInputString;
	
	temp_message.Buttons[0].pCmd = pCommand1;
	temp_message.Buttons[1].pCmd = pCommand2;

	
	return PromptBox_AddMsg_full(0,
		temp_message.Prompt.pText,
		temp_message.Prompt.Index,
		temp_message.pUserString,
		(UDINT)temp_message.Buttons,
		0);

}


//This function adds a high priority message to the top of the list.
//It will possible bump off the last one in the buffer
//This function handles multiplexing inputs.
unsigned long PromptBox_AddMsgTop(unsigned long Message, unsigned long pInputString, unsigned long Button1Text, unsigned long pCommand1, unsigned long Button2Text, unsigned long pCommand2)
{
	MessageBox_Message_typ temp_message;
	memset( &temp_message, 0, sizeof(temp_message));
		
	if(Message>255){
		temp_message.Prompt.pText=	Message;
		temp_message.Prompt.Index=	0;
	}
	else{
		temp_message.Prompt.pText=	0;
		temp_message.Prompt.Index=	Message;	
	}
	if(Button1Text>255){
		temp_message.Buttons[0].pText=	Button1Text;
		temp_message.Buttons[0].Index=	0;
	}
	else{
		temp_message.Buttons[0].pText=	0;		
		temp_message.Buttons[0].Index=	Button1Text;		
	}
	if(Button2Text>255){
		temp_message.Buttons[1].pText=	Button2Text;
		temp_message.Buttons[1].Index=	0;		
	}
	else{
		temp_message.Buttons[1].pText=	0;
		temp_message.Buttons[1].Index=	Button2Text;				
	}
	
	temp_message.pUserString = pInputString;
	
	temp_message.Buttons[0].pCmd = pCommand1;
	temp_message.Buttons[1].pCmd = pCommand2;
	
	return PromptBox_AddMsg_full(0,
		temp_message.Prompt.pText,
		temp_message.Prompt.Index,
		temp_message.pUserString,
		(UDINT)temp_message.Buttons,
		1);
}

// This function adds a normal priority 3-button prompt box to the bottom of the list
// This function handles sparsely-populated button inputs (0 for unused)
unsigned long PromptBox_Add3BtnMsg(unsigned long Message, unsigned long pInputString,unsigned long Button1Text, unsigned long pCommand1, unsigned long Button2Text, unsigned long pCommand2, unsigned long Button3Text, unsigned long pCommand3)
{
	MessageBox_Message_typ temp_message;
	memset(&temp_message, 0, sizeof(temp_message));
		
	if(Message>255){
		temp_message.Prompt.pText=	Message;
		temp_message.Prompt.Index=	0;
	}
	else{
		temp_message.Prompt.pText=	0;
		temp_message.Prompt.Index=	Message;	
	}
	if(Button1Text>255){
		temp_message.Buttons[0].pText=	Button1Text;
		temp_message.Buttons[0].Index=	0;
	}
	else{
		temp_message.Buttons[0].pText=	0;		
		temp_message.Buttons[0].Index=	Button1Text;		
	}
	if(Button2Text>255){
		temp_message.Buttons[1].pText=	Button2Text;
		temp_message.Buttons[1].Index=	0;		
	}
	else{
		temp_message.Buttons[1].pText=	0;
		temp_message.Buttons[1].Index=	Button2Text;				
	}
	if(Button3Text>255){
		temp_message.Buttons[2].pText=	Button3Text;
		temp_message.Buttons[2].Index=	0;		
	}
	else{
		temp_message.Buttons[2].pText=	0;
		temp_message.Buttons[2].Index=	Button3Text;				
	}
	
	temp_message.pUserString = pInputString;
	
	temp_message.Buttons[0].pCmd = pCommand1;
	temp_message.Buttons[1].pCmd = pCommand2;
	temp_message.Buttons[2].pCmd = pCommand3;
	
	return PromptBox_AddMsg_full(0,
		temp_message.Prompt.pText,
		temp_message.Prompt.Index,
		temp_message.pUserString,
		(UDINT)temp_message.Buttons,
		0);

}


// This function adds a high priority 3-button message to the top of the list.
// It will possible bump off the last one in the buffer
// This function handles sparsely-populated button inputs (0 for unused)
unsigned long PromptBox_Add3BtnMsgTop(unsigned long Message, unsigned long pInputString, unsigned long Button1Text, unsigned long pCommand1, unsigned long Button2Text, unsigned long pCommand2, unsigned long Button3Text, unsigned long pCommand3)
{
	MessageBox_Message_typ temp_message;
	memset( &temp_message, 0, sizeof(temp_message));
		
	if(Message>255){
		temp_message.Prompt.pText=	Message;
		temp_message.Prompt.Index=	0;
	}
	else{
		temp_message.Prompt.pText=	0;
		temp_message.Prompt.Index=	Message;	
	}
	if(Button1Text>255){
		temp_message.Buttons[0].pText=	Button1Text;
		temp_message.Buttons[0].Index=	0;
	}
	else{
		temp_message.Buttons[0].pText=	0;		
		temp_message.Buttons[0].Index=	Button1Text;		
	}
	if(Button2Text>255){
		temp_message.Buttons[1].pText=	Button2Text;
		temp_message.Buttons[1].Index=	0;		
	}
	else{
		temp_message.Buttons[1].pText=	0;
		temp_message.Buttons[1].Index=	Button2Text;				
	}
	if(Button3Text>255){
		temp_message.Buttons[2].pText=	Button3Text;
		temp_message.Buttons[2].Index=	0;		
	}
	else{
		temp_message.Buttons[2].pText=	0;
		temp_message.Buttons[2].Index=	Button3Text;				
	}
	
	temp_message.pUserString = pInputString;
	
	temp_message.Buttons[0].pCmd = pCommand1;
	temp_message.Buttons[1].pCmd = pCommand2;
	temp_message.Buttons[2].pCmd = pCommand3;
	
	return PromptBox_AddMsg_full(0,
		temp_message.Prompt.pText,
		temp_message.Prompt.Index,
		temp_message.pUserString,
		(UDINT)temp_message.Buttons,
		1);
}

// This function adds an N-Button PromptBox (where N <= 5) to the list.
// This function handles sparsely-populated button inputs (0 for unused)
unsigned long PromptBox_AddNBtnMsg(unsigned long Message, unsigned long pInputString, unsigned long Button1Text, unsigned long pCommand1, unsigned long Button2Text, unsigned long pCommand2, unsigned long Button3Text, unsigned long pCommand3, unsigned long Button4Text, unsigned long  pCommand4, unsigned long Button5Text, unsigned long pCommand5)
{
	MessageBox_Message_typ temp_message;
	memset( &temp_message, 0, sizeof(temp_message));
	
	if(Message>255){
		temp_message.Prompt.pText=	Message;
		temp_message.Prompt.Index=	0;
	}
	else{
		temp_message.Prompt.pText=	0;
		temp_message.Prompt.Index=	Message;	
	}
	if(Button1Text>255){
		temp_message.Buttons[0].pText=	Button1Text;
		temp_message.Buttons[0].Index=	0;
	}
	else{
		temp_message.Buttons[0].pText=	0;		
		temp_message.Buttons[0].Index=	Button1Text;		
	}
	if(Button2Text>255){
		temp_message.Buttons[1].pText=	Button2Text;
		temp_message.Buttons[1].Index=	0;
	}
	else{
		temp_message.Buttons[1].pText=	0;
		temp_message.Buttons[1].Index=	Button2Text;				
	}
	if(Button3Text>255){
		temp_message.Buttons[2].pText=	Button3Text;
		temp_message.Buttons[2].Index=	0;
	}
	else{
		temp_message.Buttons[2].pText=	0;
		temp_message.Buttons[2].Index=	Button3Text;				
	}
	if(Button4Text>255){
		temp_message.Buttons[3].pText=	Button4Text;
		temp_message.Buttons[3].Index=	0;
	}
	else{
		temp_message.Buttons[3].pText=	0;
		temp_message.Buttons[3].Index=	Button4Text;				
	}
	if(Button5Text>255){
		temp_message.Buttons[4].pText=	Button5Text;
		temp_message.Buttons[4].Index=	0;
	}
	else{
		temp_message.Buttons[4].pText=	0;
		temp_message.Buttons[4].Index=	Button5Text;				
	}

	temp_message.pUserString = pInputString;	
	
	temp_message.Buttons[0].pCmd = pCommand1;
	temp_message.Buttons[1].pCmd = pCommand2;
	temp_message.Buttons[2].pCmd = pCommand3;
	temp_message.Buttons[3].pCmd = pCommand4;
	temp_message.Buttons[4].pCmd = pCommand5;
	
	return PromptBox_AddMsg_full(0,
		temp_message.Prompt.pText,
		temp_message.Prompt.Index,
		temp_message.pUserString,
		(UDINT)temp_message.Buttons,
		0);
	
}

// This function adds an N-Button PromptBox (where N <= 5) to the top of the list.
// This function handles sparsely-populated button inputs (0 for unused)
// Might bump last item off buffer
unsigned long PromptBox_AddNBtnMsgTop(unsigned long Message, unsigned long pInputString, unsigned long Button1Text, unsigned long pCommand1, unsigned long Button2Text, unsigned long pCommand2, unsigned long Button3Text, unsigned long pCommand3, unsigned long Button4Text, unsigned long  pCommand4, unsigned long Button5Text, unsigned long pCommand5)
{
	MessageBox_Message_typ temp_message;
	memset( &temp_message, 0, sizeof(temp_message));
	
	if(Message>255){
		temp_message.Prompt.pText=	Message;
		temp_message.Prompt.Index=	0;
	}
	else{
		temp_message.Prompt.pText=	0;
		temp_message.Prompt.Index=	Message;	
	}
	if(Button1Text>255){
		temp_message.Buttons[0].pText=	Button1Text;
		temp_message.Buttons[0].Index=	0;
	}
	else{
		temp_message.Buttons[0].pText=	0;		
		temp_message.Buttons[0].Index=	Button1Text;		
	}
	if(Button2Text>255){
		temp_message.Buttons[1].pText=	Button2Text;
		temp_message.Buttons[1].Index=	0;
	}
	else{
		temp_message.Buttons[1].pText=	0;
		temp_message.Buttons[1].Index=	Button2Text;				
	}
	if(Button3Text>255){
		temp_message.Buttons[2].pText=	Button3Text;
		temp_message.Buttons[2].Index=	0;
	}
	else{
		temp_message.Buttons[2].pText=	0;
		temp_message.Buttons[2].Index=	Button3Text;				
	}
	if(Button4Text>255){
		temp_message.Buttons[3].pText=	Button4Text;
		temp_message.Buttons[3].Index=	0;
	}
	else{
		temp_message.Buttons[3].pText=	0;
		temp_message.Buttons[3].Index=	Button4Text;				
	}
	if(Button5Text>255){
		temp_message.Buttons[4].pText=	Button5Text;
		temp_message.Buttons[4].Index=	0;
	}
	else{
		temp_message.Buttons[4].pText=	0;
		temp_message.Buttons[4].Index=	Button5Text;				
	}

	temp_message.pUserString = pInputString;	
	
	temp_message.Buttons[0].pCmd = pCommand1;
	temp_message.Buttons[1].pCmd = pCommand2;
	temp_message.Buttons[2].pCmd = pCommand3;
	temp_message.Buttons[3].pCmd = pCommand4;
	temp_message.Buttons[4].pCmd = pCommand5;
	
	return PromptBox_AddMsg_full(0,
		temp_message.Prompt.pText,
		temp_message.Prompt.Index,
		temp_message.pUserString,
		(UDINT)temp_message.Buttons,
		1);
	
}

//This function takes all of the parameters, fills a structure and calls the MessageBox_AddMsgStructure function to get it into the buffer
unsigned long PromptBox_AddMsg_full(unsigned short ID , unsigned long Message, unsigned long MessageIndex,unsigned long UserString, unsigned long Buttons, BOOL Priority ){

	unsigned short i;
	MessageBox_Message_typ temp_message;
	MessageBox_typ *pMessageBox= MessageBoxList[ID];
	MessageBox_Button_typ *btn= (MessageBox_Button_typ *)Buttons;
	
	if(pMessageBox == 0){
		return MESSAGE_ERR_UNINITIALIZED;
	}
	
	temp_message.pUserString= UserString;
	temp_message.Prompt.pText=	Message;
	temp_message.Prompt.Index=	MessageIndex;	
	
	for(i = 0; i < 5; i++){
		temp_message.Buttons[i].pCmd= btn[i].pCmd;
		temp_message.Buttons[i].pText= btn[i].pText;
		temp_message.Buttons[i].Index= btn[i].Index;
	}	
	
	return MessageBox_AddMsgStructure( (UDINT)&temp_message, Priority);			
}

//This function will mark a message for removal based on the MessageID.
unsigned long MessageBox_RemoveMsg(unsigned long MessageID){

	MessageBox_typ *pMessageBox = MessageBoxList[0];
	
	if(pMessageBox == 0){
		return MESSAGE_ERR_UNINITIALIZED;
	}
	
	int maxIndex = pMessageBox->Internal.Buffer.NumberValues;
	int index;
	for (index = 0; index < maxIndex; index++)
	{
		MessageBox_Message_typ *pMessage = (MessageBox_Message_typ *)BufferGetItemAdr( (UDINT)&(pMessageBox->Internal.Buffer),index,0);		 
		if(pMessage!=0){
			if(pMessage->MessageID == MessageID){
				//remove message;			
				pMessage->MessageID= 0;
				return 0;
			}
		}
		else{
			return 0;		
		}
	}		
	return 0;
}
