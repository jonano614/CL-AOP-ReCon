
void InitInterface(string iniName)
{
	InitInterface_I(iniName, 0);
}

void InitInterface_I(string iniName, int numMessage)
{
	string str = GetConvertStr("InfoMessage_Text_" + numMessage, "InfoMessage.txt");
	if (str == "")
	{
		trace("Empty info message number " + numMessage);
		IDoExit(RC_INTERFACE_ANY_EXIT);
		return;
	}
	
	StartAboveForm(true);
	
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	
	SetFormatedText("MAIN_CAPTION", GetConvertStr("InfoMessage_Title", "InfoMessage.txt"));
	SetFormatedText("INFO_TEXT", GetConvertStr("InfoMessage_Text_" + numMessage, "InfoMessage.txt"));
	
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
}

void EndView()
{
    IDoExit(RC_INTERFACE_ANY_EXIT);
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	EndAboveForm(true);
	
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("ievnt_command","ProcCommand");
	
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();
    
	switch(nodName)
	{
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}