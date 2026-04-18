// BOAL переделка для SLib 02.07.06
#define DEFAULT_NAME "Player"
#define DEFAULT_PASS ""

bool isOkExit = false;
int idLngFile = -1;
int iVisibleElement = 1;
int iCharModel = 0;
int iModelQty  = 8;
string sLocation_id, sLocation_locator, sLocation_camera, sLocation_turn;
bool bLocationLoaded = false;
string sCharacterName;
float fMus, fSnd;
bool g_bToolTipStarted = false;
int heroQty = 0;
string totalInfo;

void InitInterface(string iniName)
{
	GameInterface.title = "titleCharacterSelect";
	GameInterface.faces.current = 1;

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetNewGroupPicture("ENGLAND", "NATIONS", "England");
	SetNewGroupPicture("FRANCE", "NATIONS", "France");
	SetNewGroupPicture("SPAIN", "NATIONS", "Spain");
	SetNewGroupPicture("HOLLAND", "NATIONS", "Holland");
	SetNewGroupPicture("PIRATE", "NATIONS", "Pirate");

	SetMainCharacterIndex(1);

	sCharacterName = pchar.id;

	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"BLAZE", 5, 1);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"FRANCE", 5, 1);

	GameInterface.PROFILE_NAME.str = DEFAULT_NAME;
	GameInterface.PROFILE_PASS.str = DEFAULT_PASS;

    LoadStartGameParam(); // boal
    MOD_EXP_RATE = 10; // задаем в начале игры (выбор, от 5 до 15, 10 - середина по умолчанию, 15 - медлено)
    GameInterface.nodes.EXP_SLIDE.value = 0.5;
    SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"EXP_SLIDE", 0, 0.5);

	GameInterface.nodes.TURN_SLIDE.value = 0.25;
    SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"TURN_SLIDE", 0, 0.5);

    if (startHeroType < 1) startHeroType = 1; // fix
    else if (startHeroType > sti(GetNewMainCharacterParam("hero_qty"))) startHeroType = sti(GetNewMainCharacterParam("hero_qty")); // fix

	float fM, fS, fD;
	GetMasterVolume(&fS, &fM, &fD);
	fSnd = fS;
	fMus = fM;

	SetEventHandler("exitCancel", "exitCancel", 0);
	SetEventHandler("selectEngland", "selectEngland", 0);
	SetEventHandler("selectFrance", "selectFrance", 0);
	SetEventHandler("selectSpain", "selectSpain", 0);
	SetEventHandler("selectHolland", "selectHolland", 0);
	SetEventHandler("selectPirate", "selectPirate", 0);
	SetEventHandler("confirmChangeProfileName", "confirmChangeProfileName", 0);
	SetEventHandler("MouseRClickUP","HideInfo",0);
	SetEventHandler("ShowInfo","ShowInfo",0);

	SetEventHandler("noteOk","procNoteOk",0);

	SetEventHandler("frame","IProcessFrame",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("VolumeFader", "VolumeFadeOut", 0);

	if (!CheckAttribute(&GameInterface, "SavePath"))
		GameInterface.SavePath = "SAVE";

	EI_CreateFrame("CHARACTER_BIG_PICTURE_BORDER",50,76,300,358); // tak from CHARACTER_BIG_PICTURE
    EI_CreateHLine("CHARACTER_BIG_PICTURE_BORDER", 54,107,296,1, 4);

    heroQty   = sti(GetNewMainCharacterParam("hero_qty"));

    if (!CheckAttribute(&NullCharacter, "HeroParam.HeroType") || !CheckAttribute(&NullCharacter, "HeroParam.nation"))
    {   // иначе уже загружен и выбран гг, смотрим настройки и идем обратно
		SetVariable(true);
	}
	else
	{
	    SetVariable(false);
	}
	TmpI_ShowLevelComplexity();
	SetByDefault();

	DeleteAttribute(pchar, "perks");
	LAi_SetActorTypeNoGroup(PChar);
	SelectOperation();
	SelectCharacter();
	UpdateVisibleElements();
	PostEvent("VolumeFader", 1);
}

void SetByDefault()
{
    CheckButton_SetState("CHECK_ENCOUNTERS", iEncountersRate, true);

	if (iArcadeSails == 1)// 1 0
    {
    	CheckButton_SetState("CHECK_ARCADESAIL", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_ARCADESAIL", 2, true);
    }
    if (bRechargePistolOnLine)// 1 0
    {
    	CheckButton_SetState("CHECK_PISTOL", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_PISTOL", 1, false);
    }
    if (bHardcoreGame)// 1 0
    {
    	CheckButton_SetState("CHECK_HARDCORE", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_HARDCORE", 1, false);
    }
	if (bPartitionSet)// 1 0
    {
    	CheckButton_SetState("CHECK_PARTITION", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_PARTITION", 1, false);
    }
	if (bWildCaribbean)// 1 0
    {
    	CheckButton_SetState("CHECK_WILD", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_WILD", 1, false);
    }
}

void IProcessFrame()
{
	if(GetCurrentNode() == "PROFILE_NAME")
	{
		if(!CheckAttribute(&characters[GetCharacterIndex(sCharacterName)], "profile.name"))
		{
			confirmChangeProfileName();
		}

		if(characters[GetCharacterIndex(sCharacterName)].profile.name!= GameInterface.PROFILE_NAME.str)
		{
			confirmChangeProfileName();
		}
	}
	///
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ENCOUNTERS", 3, 1))
	{
		iEncountersRate = 1;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ENCOUNTERS", 3, 2))
	{
		iEncountersRate = 2;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ENCOUNTERS", 3, 3))
	{
		iEncountersRate = 3;
	}
	////
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ARCADESAIL", 3, 1))
	{
		iArcadeSails = 1;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ARCADESAIL", 3, 2))
	{
		iArcadeSails = 0;
	}
	///
 	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_PISTOL", 3, 1))
	{
		bRechargePistolOnLine = true;
	}
	else
	{
		bRechargePistolOnLine = false;
	}
	///
 	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_HARDCORE", 3, 1))
	{
		bHardcoreGame = true;
	}
	else
	{
		bHardcoreGame = false;
	}
	///
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_PARTITION", 3, 1))
	{
		bPartitionSet = true;
	}
	else
	{
		bPartitionSet = false;
	}
	///
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_WILD", 3, 1))
	{
		bWildCaribbean = true;
	}
	else
	{
		bWildCaribbean = false;
	}
}

void exitCancel()
{
	DeleteAttribute(pchar, "actions");
	if (sLocation_id != "")
	{
		int lindex;
		lindex = FindLocation(sLocation_id);
		UnloadLocation(&Locations[lindex]);
	}
	IDoExit(RC_INTERFACE_CHARACTER_SELECT_EXIT, true);
	TEV.MENUVOLUME.RTM = "1";
	ReturnToMainMenu();
}

bool IsCorrectProfileName()
{
	int n,nLen;
	string str,sCurProfileName;

	sCurProfileName = GameInterface.PROFILE_NAME.str;
	nLen = strlen(sCurProfileName);
	if (nLen==0) return false;

	for (n=0; n<nLen; n++)
	{
		str = GetSymbol(&sCurProfileName,n);
		if( str=="*" ) {return false;}
		if( str=="?" ) {return false;}
		if( str=="\" ) {return false;}
		if( str=="/" ) {return false;}
	}
	return true;
}

void ShowNoteText(bool bShow)
{
	if (bShow)
    {
		XI_WindowDisable("MAIN_WINDOW", true);
		XI_WindowDisable("CONFIRM_WINDOW", true);
		XI_WindowDisable("NOTE_WINDOW", false);
		XI_WindowShow("NOTE_WINDOW", true);
		SetCurrentNode("NOTE_WINDOW_OK");
	}
    else
    {
		XI_WindowDisable("MAIN_WINDOW", false);
		XI_WindowDisable("CONFIRM_WINDOW", false);
		XI_WindowDisable("NOTE_WINDOW", true);
		XI_WindowShow("NOTE_WINDOW", false);
		SetCurrentNode("PROFILE_NAME");
	}
}

void procNoteOk()
{
	ShowNoteText(false);
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
        case "LEFTCHANGE_CHARACTER":
    		if(comName=="click")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    	break;

    	case "RIGHTCHANGE_CHARACTER":
    		if(comName=="click")
    		{
    		    ProcessCommandExecuteRight();
    		}
    	break;

		case "TURN_SLIDE":
			if (comName == "click" || comName == "leftstep" || comName == "rightstep" || comName == "speedleft" || comName == "speedright")
			{
				float rVal = SM_FastRound(stf(GameInterface.nodes.TURN_SLIDE.value), 2);
				if (sLocation_turn != "") CharacterTurnAy(Pchar, stf(sLocation_turn) + ((0.5 - rVal) * 6));
				else CharacterTurnAy(Pchar, 4.42 + ((0.5 - rVal) * 6));
			}
		break;

    	case "LEFTCHANGE_MODEL":
    		if(comName=="click")
    		{
    		    iCharModel--;
                if (iCharModel < 0)
                    iCharModel = iModelQty;
    		    SelectCharacter_Model();
    		}
    	break;
		
    	case "RIGHTCHANGE_MODEL":
    		if(comName=="click")
    		{
				iCharModel++;
                if (iCharModel > iModelQty)
                    iCharModel = 0;
    		    SelectCharacter_Model();
    		}
    	break;
		
		case "BACK_BUTTON1":
    		if(comName=="click")
    		{
    		    ProcessCommandBackButton(1);
    		}
			else if(comName=="leftstep")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    		else if(comName=="rightstep")
    		{
                ProcessCommandExecuteRight();
    		}
    	break;
		
    	case "NEXT_BUTTON1":
    		if(comName=="click")
    		{
    		    ProcessCommandNextButton(1);
    		}
			else if(comName=="leftstep")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    		else if(comName=="rightstep")
    		{
                ProcessCommandExecuteRight();
    		}
    	break;
		
		case "LEFTCHANGE_TYPE":
    		if(comName=="click")
    		{
    		    ProcessCommandExecuteTypeLeft();
    		}
    	break;
		
    	case "RIGHTCHANGE_TYPE":
    		if(comName=="click")
    		{
    		    ProcessCommandExecuteTypeRight();
    		}
    	break;
		
		case "BACK_BUTTON2":
    		if(comName=="click")
    		{
    		    ProcessCommandBackButton(2);
    		}
			else if(comName=="leftstep")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    		else if(comName=="rightstep")
    		{
                ProcessCommandExecuteRight();
    		}
    	break;
		
    	case "NEXT_BUTTON2":
    		if(comName=="click")
    		{
    		    ProcessCommandNextButton(2);
    		}
			else if(comName=="leftstep")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    		else if(comName=="rightstep")
    		{
                ProcessCommandExecuteRight();
    		}
    	break;
		
		case "LEFTCHANGE_COMPLEX":
		if(comName=="click")
		{
		    if (MOD_SKILL_ENEMY_RATE > 1)
		    {
               MOD_SKILL_ENEMY_RATE--;
            }
            TmpI_ShowLevelComplexity();
		}
		break;
		
		case "RIGHTCHANGE_COMPLEX":
			if(comName=="click")
			{
			    if (MOD_SKILL_ENEMY_RATE < 10)
			    {
	               MOD_SKILL_ENEMY_RATE++;
	            }
	            TmpI_ShowLevelComplexity();
			}
		break;
		
		case "BACK_BUTTON3":
    		if(comName=="click")
    		{
    		    ProcessCommandBackButton(3);
    		}
			else if(comName=="leftstep")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    		else if(comName=="rightstep")
    		{
                ProcessCommandExecuteRight();
    		}
    	break;
		
    	case "NEXT_BUTTON3":
    		if(comName=="click")
    		{
    		    ProcessCommandNextButton(3);
    		}
			else if(comName=="leftstep")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    		else if(comName=="rightstep")
    		{
                ProcessCommandExecuteRight();
    		}
    	break;
		
		case "CONFIRM_WINDOW_MB_YES":
			if (comName == "click" || comName == "activate")
			{
				isOkExit = true;
				SaveStartGameParam(); // boal
				IDoExit(RC_INTERFACE_CHARACTER_SELECT_EXIT, true);
			}

			if (comName == "deactivate")
			{
				ShowConfirmWindow(false);
			}
		break;
		
		case "CONFIRM_WINDOW_MB_NO":
			if (comName == "click" || comName == "activate")
			{
				ShowConfirmWindow(false);
			}

			if (comName == "deactivate")
			{
				ShowConfirmWindow(false);
			}
		break;
	}

}

void ShowConfirmWindow(bool show)
{
	if (show)
	{
		SetCurrentNode("CONFIRM_WINDOW_MB_NO");

		XI_WindowDisable("MAIN_WINDOW", true);
		XI_WindowDisable("CONFIRM_WINDOW", false);
		XI_WindowShow("CONFIRM_WINDOW", true);
		EI_CreateFrame("CONFIRM_WINDOW_BORDERS",190,190,610,360);
	} 
	else 
	{
		XI_WindowDisable("CONFIRM_WINDOW", true);
		XI_WindowShow("CONFIRM_WINDOW", false);
		XI_WindowDisable("MAIN_WINDOW", false);
		SetCurrentNode("OK_BUTTON");
	}
}

//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------
void CreateProfileFolders()
{
	string folder = GameInterface.SavePath + "\";
	folder+= pchar.profile.name;

	if (XI_CheckFolder(folder)) return;

	if(!XI_CreateFolder(folder)) 
		trace("Could not create profile folder");
}
//----------------------------------------------------------------------------------------------------
void DeleteProfile()
{
	string folder;

	folder = GameInterface.SavePath + "\"+ pchar.profile.name;

	int nSaveNum= 0;
	string saveName;
	int nSaveSize;

	string path = GameInterface.SavePath;
	GameInterface.SavePath = folder;

    while (SendMessage(&GameInterface,"llee",MSG_INTERFACE_SAVE_FILE_FIND,nSaveNum,&saveName,&nSaveSize)!=0)
    {
		nSaveNum++;
		SendMessage(&GameInterface,"ls",MSG_INTERFACE_DELETE_SAVE_FILE,saveName);
    }

	GameInterface.SavePath = path;
	XI_DeleteFolder(folder);
}
//----------------------------------------------------------------------------------------------------
bool ProfileExists()
{
	string folder = GameInterface.SavePath + "\";

	folder+= pchar.profile.name;

	return (XI_CheckFolder(folder));
}
//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------
void SelectNation(int iNation)
{
	/////////////////////////////////////////////////////
	string sNationPict;
	for (int i=0; i<MAX_NATIONS; i++)
	{
		sNationPict = GetNationNameByType(i);

		SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNationPict, 5, 0);
	}

	sNationPict = GetNationNameByType(iNation);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNationPict, 5, 1);
	/////////////////////////////////////////////////////
	NullCharacter.HeroParam.Nation = iNation;
	totalInfo = GetRPGText(Nations[iNation].Name + "_descr");
	SetInfoNation();
}

void selectEngland()
{
    if (startHeroType == 1) SelectNation(ENGLAND);	// Питер Блад
	//else if (startHeroType == 2) SelectNation(FRANCE);	// Мишель де Граммон (до лучших времен)
	else  SelectNation(ENGLAND);
}

void selectFrance()
{
    if (startHeroType == 1) SelectNation(ENGLAND);	// Питер Блад
	//else if (startHeroType == 2) SelectNation(FRANCE);	// Мишель де Граммон (до лучших времен)
	else SelectNation(FRANCE);
}

void selectSpain()
{
    if (startHeroType == 1) SelectNation(ENGLAND);	// Питер Блад
	//else if (startHeroType == 2) SelectNation(FRANCE);	// Мишель де Граммон (до лучших времен)
	else SelectNation(SPAIN);
}

void selectHolland()
{
    if (startHeroType == 1) SelectNation(ENGLAND);	// Питер Блад
	//else if (startHeroType == 2) SelectNation(FRANCE);	// Мишель де Граммон (до лучших времен)
	else SelectNation(HOLLAND);
}

void selectPirate()
{
    if (startHeroType == 1) SelectNation(ENGLAND);	// Питер Блад
	//else if (startHeroType == 2) SelectNation(FRANCE);	// Мишель де Граммон (до лучших времен)
	else SelectNation(PIRATE);
}

void IDoExit(int exitCode, bool bCode)
{
	DelEventHandler("exitCancel", "exitCancel");
	DelEventHandler("selectEngland", "selectEngland");
	DelEventHandler("selectFrance", "selectFrance");
	DelEventHandler("selectSpain", "selectSpain");
	DelEventHandler("selectHolland", "selectHolland");
	DelEventHandler("selectPirate", "selectPirate");
	DelEventHandler("MouseRClickUP","HideInfo");
	DelEventHandler("ShowInfo","ShowInfo");

	DelEventHandler("noteOk","procNoteOk");
	
	DelEventHandler("frame","IProcessFrame");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("VolumeFader","VolumeFadeOut");

	if(isOkExit == false)
	{
		EndCancelInterface(bCode);
		
		float fM, fS, fD;
		GetMasterVolume(&fS, &fM, &fD);
		
		if (fM < 0.333)
			fM = 0.333;
		
		TEV.MENUVOLUME.MUS = fM;
	}
	else
	{
		DeleteAttributeEx(&TEV, "MAINMENU,MENUVOLUME");
		DelEventHandler("MusicUpdateInterface", "KZ|MusicUpdateInterface");
		StopMusic();
		ResetSound();
        MOD_EXP_RATE = makeint(5 + 10.0 * (1.0 - stf(GameInterface.nodes.EXP_SLIDE.value)));  // 0т 5 до 15
		trace("MOD_EXP_RATE = " + MOD_EXP_RATE);
		interfaceResultCommand = exitCode;
		EndCancelInterface(bCode);
	}
}

void confirmChangeProfileName()
{	
	PlayerProfile.name = GameInterface.PROFILE_NAME.str;
	pchar.profile.name = GameInterface.PROFILE_NAME.str;
}

void confirmChangeProfilePass()
{	
	PlayerProfile.password = GameInterface.PROFILE_PASS.str;
	pchar.profile.pass = GameInterface.PROFILE_PASS.str;
	SetCurrentNode("OK_BUTTON");
}

void ShowInfo()
{
	g_bToolTipStarted = true;
	string sHeader = "TEST";
	string sNode = GetCurrentNode();
	
	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";
	
	switch(sNode)
	{
		case "CHECK_ENCOUNTERS":
			sHeader = XI_ConvertString("EncountersRate");
			sText1 = GetRPGText("EncountersRate_desc");
		break;
		
		case "CHECK_ARCADESAIL":
			sHeader = XI_ConvertString("Sailing Mode");
			sText1 = GetRPGText("ArcadeSailMode_desc");
		break;
		
		case "CHECK_PISTOL":
			sHeader = XI_ConvertString("New Fight Mode");
			sText1 = GetRPGText("RechargePistolOnLine_desc");
		break;
		
		case "CHECK_HARDCORE":
			sHeader = XI_ConvertString("HardcoreGame");
			sText1 = GetRPGText("HardcoreGame_desc");
		break;
		
		case "CHECK_PARTITION":
			sHeader = XI_ConvertString("Partition");
			sText1 = GetRPGText("Partition_hint");
		break;
		
		case "CHECK_WILD":
			sHeader = XI_ConvertString("WildCaribbean");
			sText1 = GetRPGText("WildCaribbean_desc");
		break;
		
		case "EXP_SLIDE":
			sHeader = GetRPGText("EXP_SLIDE");
			sText1 = GetRPGText("EXP_SLIDE_desc");
		break;
		
		case "TABLE_SPECIAL":
		    sHeader = XI_ConvertString("Characteristics");
		    sText1 = GetRPGText("SPECIAL_desc");
		break;
	}
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
}

void HideInfo()
{
	if( g_bToolTipStarted ) {
		g_bToolTipStarted = false;
		CloseTooltip();
		SetCurrentNode("OK_BUTTON");
	}
}

void ProcessCommandExecuteLeft()
{
    if (startHeroType > 1)
    {
       startHeroType--;
    }
    else
    {
       startHeroType = heroQty;
    }
    SetVariable(true);
	SelectOperation();
	SelectCharacter();
}

void ProcessCommandExecuteRight()
{
    if (startHeroType < heroQty)
    {
       startHeroType++;
    }
    else
    {
       startHeroType = 1;
    }
    SetVariable(true);
	SelectOperation();
	SelectCharacter();
}

void ProcessCommandBackButton(int numButton)
{
    if (numButton > 1)
    {
		iVisibleElement--;
		UpdateVisibleElements();
    }
}

void ProcessCommandNextButton(int numButton)
{
    if (numButton < 3)
    {
		iVisibleElement++;
		UpdateVisibleElements();
    }
	else
    {
		if( !IsCorrectProfileName() )
		{
			ShowNoteText(true);
			return;
		}
		confirmChangeProfileName();
		if (!ProfileExists())
		{
			CreateProfileFolders();
			isOkExit = true;
			IDoExit(RC_INTERFACE_CHARACTER_SELECT_EXIT, true);
		} 
		else 
		{
			ShowConfirmWindow(true);
		}
    }
}

void UpdateVisibleElements()
{
	if ( iVisibleElement == 2 )
	{
		XI_WindowShow("TYPES_WINDOW", false);
		XI_WindowShow("NATIONS_WINDOW", true);
		XI_WindowDisable("NATIONS_WINDOW", false);
		XI_WindowShow("OTHERS_WINDOW", false);
		SetCurrentNode("NEXT_BUTTON2");
	}
	else if ( iVisibleElement == 3 )
	{
		XI_WindowShow("TYPES_WINDOW", false);
		XI_WindowShow("NATIONS_WINDOW", false);
		XI_WindowShow("OTHERS_WINDOW", true);
		XI_WindowDisable("OTHERS_WINDOW", false);
		SetCurrentNode("NEXT_BUTTON3");
	}
	else
	{
		XI_WindowShow("TYPES_WINDOW", true);
		XI_WindowDisable("TYPES_WINDOW", false);
		XI_WindowShow("NATIONS_WINDOW", false);
		XI_WindowShow("OTHERS_WINDOW", false);
		SetCurrentNode("NEXT_BUTTON1");
	}
}

void SetVariable(bool _init)
{
    idLngFile = LanguageOpenFile("HeroDescribe.txt");
    SetFormatedText("HERO_NAME", GetNewMainCharacterName());
    if (_init)
    {
    	NullCharacter.HeroParam.HeroType = GetNewMainCharacterType(startHeroType);
    	NullCharacter.HeroParam.nation = GetNewMainCharacterNation(startHeroType);
	}
    SetFormatedText("HERO_TYPE", XI_ConvertString(NullCharacter.HeroParam.HeroType));

    SetNewPicture("FACEPICT", "interfaces\portraits\256\face_" + GetNewMainCharacterFace() + ".tga");
    SelectNation(sti(NullCharacter.HeroParam.nation));
    totalInfo = LanguageConvertString(idLngFile, "hero_" + startHeroType);
	MainChAnim = LanguageConvertString(idLngFile, "animation_" + startHeroType);
	SetInfoText();
	totalInfo = LanguageConvertString(idLngFile, NullCharacter.HeroParam.HeroType);
    SetInfoChar();
    LanguageCloseFile(idLngFile);
}

string GetCharacterType(string type, int direction)
{
    switch (type)
	{
        case "Merchant":
            if (direction > 0)
            {
    	    	type = "Corsair";
    	    }
    	    else
    	    {
    	        type = "Adventurer";
    	    }
	    break;

	    case "Corsair":
            if (direction > 0)
            {
    	    	type = "Adventurer";
    	    }
    	    else
    	    {
    	        type = "Merchant";
    	    }
	    break;

	    case "Adventurer":
            if (direction > 0)
            {
    	    	type = "Merchant";
    	    }
    	    else
    	    {
    	        type = "Corsair";
    	    }
	    break;
	}

	RefreshPIRATES(type);

	return type;
}

void RefreshPIRATES(string sType)
{
	switch (sType)
	{
		case "Adventurer":
			SetSPECIAL(pchar, 5,7,6,4,6,6,8);
		break;
		
		case "Corsair":
			SetSPECIAL(pchar, 7,6,6,3,5,9,6);
		break;
		
		case "Merchant":
			SetSPECIAL(pchar, 4,9,5,8,9,3,4);
		break;
/*
		case "Master":
			SetSPECIAL(pchar, 8,5,7,5,7,5,5);
		break;
		
		case "Inquisitor":
			SetSPECIAL(pchar, 8,5,7,5,7,5,5);
		break;
		
		case "SecretAgent":
			SetSPECIAL(pchar, 8,5,7,5,7,5,5);
		break;
*/
	}
	
	if (iVisibleElement == 1)
	{
		GameInterface.TABLE_SPECIAL.select = 0;
		string col, skillName;
		int skillVal, i;
		for (i=1; i<=7; i++)
		{
			col = "td" + i;
			GameInterface.TABLE_SPECIAL.tr1.(col).fontidx = 0;
			GameInterface.TABLE_SPECIAL.tr1.(col).align = "center";
			GameInterface.TABLE_SPECIAL.tr1.(col).scale = 0.75;
			GameInterface.TABLE_SPECIAL.tr1.(col).textoffset = "-4,-4";
			GameInterface.TABLE_SPECIAL.tr2.(col).fontidx = 1;
			GameInterface.TABLE_SPECIAL.tr2.(col).align = "center";
			GameInterface.TABLE_SPECIAL.tr2.(col).scale = 0.75;
			GameInterface.TABLE_SPECIAL.tr2.(col).textoffset = "-1,-1";
			
			skillName = GetSkillNameByTRIdx("SPECIALType", i);
			GameInterface.TABLE_SPECIAL.tr1.(col).str = XI_ConvertString(skillName + "T");
			skillVal = GetSkillValue(PChar, SPECIAL_TYPE, skillName);
			GameInterface.TABLE_SPECIAL.tr2.(col).str = skillVal;
		}
		Table_UpdateWindow("TABLE_SPECIAL");
	}
}

void ProcessCommandExecuteTypeLeft()
{
    idLngFile = LanguageOpenFile("HeroDescribe.txt");

    NullCharacter.HeroParam.HeroType = GetCharacterType(NullCharacter.HeroParam.HeroType, -1);

    SetFormatedText("HERO_TYPE", XI_ConvertString(NullCharacter.HeroParam.HeroType));

    totalInfo = LanguageConvertString(idLngFile, NullCharacter.HeroParam.HeroType);
	SetInfoChar();
    LanguageCloseFile(idLngFile);
}

void ProcessCommandExecuteTypeRight()
{
    idLngFile = LanguageOpenFile("HeroDescribe.txt");

    NullCharacter.HeroParam.HeroType = GetCharacterType(NullCharacter.HeroParam.HeroType, 1);

    SetFormatedText("HERO_TYPE", XI_ConvertString(NullCharacter.HeroParam.HeroType));

    totalInfo = LanguageConvertString(idLngFile, NullCharacter.HeroParam.HeroType);
	SetInfoChar();
    LanguageCloseFile(idLngFile);
}

void SetInfoText()
{
    SetFormatedText("INFO_CHAR", totalInfo);
    SetVAligmentFormatedText("INFO_CHAR");
}

void SetInfoChar()
{
    SetFormatedText("INFO_TYPE", totalInfo);
    SetVAligmentFormatedText("INFO_TYPE");
}

void SetInfoNation()
{
    SetFormatedText("NATIONS_FRAME_CAPTION", XI_ConvertString(Nations[sti(NullCharacter.HeroParam.Nation)].Name));
    SetFormatedText("INFO_NATION", totalInfo);
    SetVAligmentFormatedText("INFO_NATION");
}

void TmpI_ShowLevelComplexity()
{
    SetFormatedText("COMPLEX_TYPE", GetLevelComplexity(MOD_SKILL_ENEMY_RATE));
	SetFormatedText("INFO_COMPLEX", GetRPGText("LevelComplexity_desc"));
	SetVAligmentFormatedText("INFO_COMPLEX");
}

void SelectOperation()
{
	idLngFile = LanguageOpenFile("HeroDescribe.txt");

	LanguageConvertString(idLngFile, "hero_" + startHeroType);

	string sName = LanguageConvertString(idLngFile, "heroName_" + startHeroType);
	string sLastName = LanguageConvertString(idLngFile, "heroLastname_" + startHeroType);
	string sCharacterName = sName + " " + sLastName;

	string sHeroModel = LanguageConvertString(idLngFile, "heroModel_" + startHeroType);
    iModelQty = GetCountSubString(sHeroModel) - 1;
	PChar.HeroModel = sHeroModel;

	iCharModel = 0;
	string sModel = GetSubStringByNum(PChar.HeroModel, iCharModel);
	PChar.model = sModel;

	string sAni = LanguageConvertString(idLngFile, "animation_" + startHeroType);
	PChar.model.animation = sAni;

    SetFormatedText("MODEL_FRAME_CAPTION", XI_ConvertString("Preview"));
    SetNewModelToChar(PChar);

	RefreshPIRATES(NullCharacter.HeroParam.HeroType);

	sLocation_id = LanguageConvertString(idLngFile, "idLocation_" + startHeroType);
	sLocation_locator = LanguageConvertString(idLngFile, "locatorLocation_" + startHeroType);
	sLocation_camera = LanguageConvertString(idLngFile, "coordinateLocation_" + startHeroType);
	sLocation_turn = LanguageConvertString(idLngFile, "turnLocation_" + startHeroType);

	LanguageCloseFile(idLngFile);
}

void SelectCharacter_Model()
{
    PChar.model = GetSubStringByNum(PChar.HeroModel, iCharModel);
    SendMessage(PChar, "lss", MSG_CHARACTER_SETMODEL, PChar.model, PChar.model.animation);
    SetFormatedText("MODEL_FRAME_CAPTION", XI_ConvertString("Preview"));
}

void SelectCharacter()
{
	int lindex;
	if (bLocationLoaded && PChar.location != "" && sLocation_id == PChar.location) return;
	else if (bLocationLoaded && PChar.location != "" && sLocation_id != PChar.location)
	{
		trace("unloaded");
		lindex = FindLocation(PChar.location);
		UnloadLocation(&Locations[lindex]);
		bLocationLoaded = false;
	}
	
	if (sLocation_id != "" && sLocation_locator != "")
	{
		lindex = FindLocation(sLocation_id);
		PChar.location         = sLocation_id;
		PChar.location.locator = sLocation_locator;
	}
	else
	{
		lindex = FindLocation("Estate");
		PChar.location         = "Estate";
		PChar.location.locator = "goto12";
	}
	PChar.location.group   = "goto";
	LoadLocation(&Locations[lindex]);
	bLocationLoaded = true;
	
	SetCharacterTask_None(PChar);
    LAi_LockFightMode(Pchar, true);
	LAi_LocationFightDisable(loadedLocation, true);
	LAi_SetActorTypeNoGroup(Pchar);

	InterfaceStates.Buttons.Controls.enable = false;
	InterfaceStates.Launched = true;
	InterfaceStates.doUnFreeze = false;
	DoQuestFunctionDelay("SelectCharacter_locCamera", 0.1);
}

void SelectCharacter_locCamera(string _tmp)
{
    if (sLocation_turn != "") CharacterTurnAy(Pchar, stf(sLocation_turn));
	else CharacterTurnAy(Pchar, 4.42);
	
	if (sLocation_camera != "")
	{
		float i1 = stf(GetSubStringByNum(sLocation_camera, 0));
		float i2 = stf(GetSubStringByNum(sLocation_camera, 1));
		float i3 = stf(GetSubStringByNum(sLocation_camera, 2));
		int   i4 = sti(GetSubStringByNum(sLocation_camera, 3));
		float i5 = stf(GetSubStringByNum(sLocation_camera, 4));
		float i6 = stf(GetSubStringByNum(sLocation_camera, 5));
		float i7 = stf(GetSubStringByNum(sLocation_camera, 6));
		locCameraFromToPos(i1, i2, i3, i4, i5, i6, i7);
	}
	else locCameraFromToPos(9.14, 7.83, 0.15, 0, 22.45, 5.67, -4.71);
	ChangeShowIntarface();
}

void VolumeFadeOut()
{
	fMus -= 0.01;
	fSnd -= 0.01;
	
	if (fMus < 0.333)
	{
		fMus = 0.333;
		ResetSoundScheme();
		KZ|Volume(fMus, 0);
		DelEventHandler("VolumeFader","VolumeFadeOut");
		return;
	}
	
	KZ|Volume(fMus, fSnd);
	PostEvent("VolumeFader", 55);
}
