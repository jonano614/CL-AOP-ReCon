// EvgAnat - энциклопедия

string CurRow;
int iSelected = 1; // курсор в таблице
string curTome;

void InitInterface(string iniName)
{		
	curTome = "";

	GameInterface.title = "titleEncyclopedia";
	
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

//	SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
//	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
//	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	
	SetNodeUsing("PAGE_1",false);
	SetNodeUsing("PAGE_2",false);
	SetNodeUsing("PAGE_3",false);
	SetNodeUsing("PAGE_4",false);
	SetNodeUsing("PAGE_5",false);
	SetNodeUsing("PAGES_TEXT",false);

	FillTomesTable();

}

void ProcessCancelExit()
{
	IDoExit(-1);
}

void IDoExit(int exitCode)
{	
//	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("TableSelectChange", "TableSelectChange");
//	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
//	DelEventHandler("MouseRClickUp","HideInfoWindow");

	if(CheckAttribute(PChar, "ShowEncyclopedia"))
	{
		DeleteAttribute(PChar, "ShowEncyclopedia");
		interfaceResultCommand = RC_INTERFACE_TO_ITEMS;
	}
	else
	{
		interfaceResultCommand = exitCode;
	}
	
	EndCancelInterface(true);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();
		
	switch(nodName)
	{
		case "TABLE_PAGES":
			if(comName == "click")
			{
				FillTextPage(curTome, 0);
			}
		break;
		case "PAGE_1":
			if(comName == "click")
			{
				FillPages(curTome);
				SendMessage(&GameInterface,"lslss",MSG_INTERFACE_MSG_TO_NODE,"PAGE_1", 6, "PERK_ENABLE", GetPerkPage(curTome, 1));
				FillTextPage(curTome, 1);
			}
		break;
		case "PAGE_2":
			if(comName == "click")
			{
				FillPages(curTome);
				SendMessage(&GameInterface,"lslss",MSG_INTERFACE_MSG_TO_NODE,"PAGE_2", 6, "PERK_ENABLE", GetPerkPage(curTome, 2));
				FillTextPage(curTome, 2);
			}
		break;
		case "PAGE_3":
			if(comName == "click")
			{
				FillPages(curTome);
				SendMessage(&GameInterface,"lslss",MSG_INTERFACE_MSG_TO_NODE,"PAGE_3", 6, "PERK_ENABLE", GetPerkPage(curTome, 3));
				FillTextPage(curTome, 3);
			}
		break;
		case "PAGE_4":
			if(comName == "click")
			{
				FillPages(curTome);
				SendMessage(&GameInterface,"lslss",MSG_INTERFACE_MSG_TO_NODE,"PAGE_4", 6, "PERK_ENABLE", GetPerkPage(curTome, 4));
				FillTextPage(curTome, 4);
			}
		break;
		case "PAGE_5":
			if(comName == "click")
			{
				FillPages(curTome);
				SendMessage(&GameInterface,"lslss",MSG_INTERFACE_MSG_TO_NODE,"PAGE_5", 6, "PERK_ENABLE", GetPerkPage(curTome, 5));
				FillTextPage(curTome, 5);
			}
		break;
	}
}

void FillTomesTable()
{
	int m, n, i, j, qPages;
	string row, sTome, sAttr, sPages, sPage;
	aref arTomes, arTome;
	
	GameInterface.TABLE_PAGES.hr.td1.icon.group = "RECON_ICONS";
	GameInterface.TABLE_PAGES.hr.td1.icon.image = "frame caption red short";
	GameInterface.TABLE_PAGES.hr.td1.icon.width = 163;
	GameInterface.TABLE_PAGES.hr.td1.icon.height = 24;
	GameInterface.TABLE_PAGES.hr.td1.icon.offset = "-2, 0";
	GameInterface.TABLE_PAGES.hr.td1.scale = 0.9;
	GameInterface.TABLE_PAGES.hr.td1.str = XI_ConvertString("FoundToms");
	GameInterface.TABLE_PAGES.hr.td1.align = "left";
	GameInterface.TABLE_PAGES.hr.td1.fontidx = 0;
	GameInterface.TABLE_PAGES.hr.td1.textoffset = "25, 0";
	
	makearef(arTomes, pchar.encyclopedia.tomes);
	n = 1;
	m = GetAttributesNum(arTomes);
	for(i=0; i<m; i++)
	{
		arTome = GetAttributeN(arTomes, i);
		sTome = GetAttributeName(arTome);
		
		row = "tr"+n;
	
		GameInterface.TABLE_PAGES.(row).tome = sTome;				
		GameInterface.TABLE_PAGES.(row).td1.icon.group = "ICONS_SPEC";
		GameInterface.TABLE_PAGES.(row).td1.icon.image = sTome + " skill icon";
		GameInterface.TABLE_PAGES.(row).td1.icon.offset = "0, 0";
		GameInterface.TABLE_PAGES.(row).td1.icon.width = 25;
		GameInterface.TABLE_PAGES.(row).td1.icon.height = 25;
		GameInterface.TABLE_PAGES.(row).td1.textoffset = "31,0";
		GameInterface.TABLE_PAGES.(row).td1.str = GetConvertStr(sTome, "Encyclopedia.txt");
		GameInterface.TABLE_PAGES.(row).td1.scale = 0.8;		
		
		n++;
	}
	
	Table_UpdateWindow("TABLE_PAGES");
}

void FillPages(string sTome)
{
	SetNodeUsing("PAGE_1",true);
	SetNodeUsing("PAGE_2",true);
	SetNodeUsing("PAGE_3",true);
	SetNodeUsing("PAGE_4",true);
	SetNodeUsing("PAGE_5",true);
	SetNodeUsing("PAGES_TEXT",true);
	
	string sTemp, sPerk;
	string sPages;
	for(int i=1; i<=5; i++)
	{
		sTemp = "PAGE_NUM_"+i;
		SetFormatedText(sTemp, "");
		sTemp = "p"+i;
		if(CheckAttribute(pchar,"encyclopedia.tomes."+sTome+"."+sTemp))
		{
			sPages = pchar.encyclopedia.tomes.(sTome).(sTemp);
			sTemp = "PAGE_"+i;
			sPerk = GetPerkPage(sTome, i);
			SendMessage(&GameInterface,"lslss",MSG_INTERFACE_MSG_TO_NODE,sTemp, 6, "PERK_DISABLE", sPerk);
			SetSelectable(sTemp, true);
			sTemp = "PAGE_NUM_"+i;
			if(sti(sPages) > 1)
				SetFormatedText(sTemp, sPages);
		}
		else
		{
			sTemp = "PAGE_"+i;
			SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE,sTemp, 2, 0, "interfaces\perks\NotAvailable.tga" );
			SetSelectable(sTemp, false);
		}
	}
}

string GetPerkPage(string sTome, int i)
{
	switch(sTome)
	{
		case "Leadership":
			switch(i)
			{
				case 1:		return "SailsMan";		break;
				case 2:		return "Tireless";		break;
				case 3:		return "Grus";			break;
				case 4:		return "Sliding";		break;
				case 5:		return "Rush";			break;
			}
		break;
		case "FencingLight":
			switch(i)
			{
				case 1:		return "Tireless";		break;
				case 2:		return "Sliding";		break;
				case 3:		return "BladeDancer";		break;
				case 4:		return "SwordplayProfessional";		break;
				case 5:		return "SwordplayProfessional";		break;
			}
		break;
		case "Fencing":
			switch(i)
			{
				case 1:		return "Tireless";		break;
				case 2:		return "Sliding";		break;
				case 3:		return "BladeDancer";		break;
				case 4:		return "SwordplayProfessional";		break;
				case 5:		return "SwordplayProfessional";		break;
			}
		break;
		case "FencingHeavy":
			switch(i)
			{
				case 1:		return "Tireless";		break;
				case 2:		return "Sliding";		break;
				case 3:		return "BladeDancer";		break;
				case 4:		return "SwordplayProfessional";		break;
				case 5:		return "SwordplayProfessional";		break;
			}
		break;
		case "Pistol":
			switch(i)
			{
				case 1:		return "Gunman";		break;
				case 2:		return "Gunman";		break;
				case 3:		return "Grus";		break;
				case 4:		return "HawkEye";		break;
				case 5:		return "MusketsShoot";		break;
			}
		break;
		case "Sneak":
			switch(i)
			{
				case 1:		return "Grus";		break;
				case 2:		return "Gunman";		break;
				case 3:		return "SwordplayProfessional";		break;
				case 4:		return "SwordplayProfessional";		break;
				case 5:		return "Sliding";		break;
			}
		break;
		case "Fortune":
			switch(i)
			{
				case 1:		return "CannonProfessional";		break;
				case 2:		return "SwordplayProfessional";		break;
				case 3:		return "WildCaribbean";		break;
				case 4:		return "Sliding";		break;
				case 5:		return "Gunman";		break;
			}
		break;
		case "Sailing":
			switch(i)
			{
				case 1:		return "SailingProfessional";		break;
				case 2:		return "SailingProfessional";		break;
				case 3:		return "SailsMan";		break;
				case 4:		return "WindCatcher";		break;
				case 5:		return "StormProfessional";		break;
			}
		break;
		case "Accuracy":
			switch(i)
			{
				case 1:		return "Gunman";		break;
				case 2:		return "MusketsShoot";		break;
				case 3:		return "CannonProfessional";		break;
				case 4:		return "LongRangeShoot";		break;
				case 5:		return "GrapplingProfessional";		break;
			}
		break;
		case "Cannons":
			switch(i)
			{
				case 1:		return "LongRangeShoot";		break;
				case 2:		return "CannonProfessional";		break;
				case 3:		return "CannonProfessional";		break;
				case 4:		return "FastReload";		break;
				case 5:		return "ImmediateReload";		break;
			}
		break;
		case "Defence":
			switch(i)
			{
				case 1:		return "ShipDefenseProfessional";		break;
				case 2:		return "ShipDefenseProfessional";		break;
				case 3:		return "Doctor3";		break;
				case 4:		return "StormProfessional";		break;
				case 5:		return "SwordplayProfessional";		break;
			}
		break;
		case "Repair":
			switch(i)
			{
				case 1:		return "Carpenter";		break;
				case 2:		return "Shipbuilder";		break;
				case 3:		return "InstantRepair";		break;
				case 4:		return "WindCatcher";		break;
				case 5:		return "ProfessionalCommerce";		break;
			}
		break;
	}
}

void FillTextPage(string sTome, int iPage)
{
	if(iPage == 0)
	{
		SetFormatedText("PAGE_DESCRIBE", "");
		return;
	}
	SetFormatedText("PAGE_DESCRIBE", GetConvertStr(sTome+"_"+iPage, "Encyclopedia.txt"));
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurRow   =  "tr" + (iSelected);    
	string sTome;
	if(CheckAttribute(&GameInterface, "TABLE_PAGES."+CurRow+".tome"))
	{
		sTome = GameInterface.TABLE_PAGES.(CurRow).tome;
		curTome = sTome;
		FillPages(sTome);
	}
}