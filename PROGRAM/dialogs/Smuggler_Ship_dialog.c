void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref PChar;
	PChar = GetMainCharacter();

	string ret;

	switch (Dialog.CurrentNode)
	{
		case "exit":
			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
		break;

		case "First time":
			dialog.text = "";
			Link.l1 = StringFromKey("Smuggler_Ship_dialog_1");
			Link.l1.go = "exit";
		break;

		////////////////////////////////////////////////////////////////////////////////
		//	Корсарское метро
		////////////////////////////////////////////////////////////////////////////////
		case "Travel_talkStart":
			NPChar.location = "none"; // чтоб на палубе не болтался
			//Шанс на то что продадут на рудники.
			int iRnd = (rand(100) == 30);
			if (iRnd)
			{
				dialog.text = StringFromKey("Smuggler_Ship_dialog_2");
				link.l1 = StringFromKey("Smuggler_Ship_dialog_3");
				link.l1.go = "Travel_fight_NoRep"; //TODO: заглушка, пока нет рудников
				//"Travel_mine"; //Собственно тоже можно боевку организовать, ГГ сопротивляется.
			}
			else
			{
				dialog.text = StringFromKey("Smuggler_Ship_dialog_4");
				link.l1 = StringFromKey("Smuggler_Ship_dialog_5");
				link.l1.go = "Travel_end";
				link.l2 = StringFromKey("Smuggler_Ship_dialog_6");
				link.l2.go = "Travel_fight";
			}
		break;

		case "Travel_fight_NoRep":
			LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_SetCheck("TmpEnemy", "Travel_AfterDeckFight");
			LAi_group_FightGroups(LAI_GROUP_PLAYER, "TmpEnemy", true);
			LAi_SetPlayerType(PChar);

			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
			LAi_SetFightMode(Pchar, true);
			LAi_SetWarriorTypeNoGroup(NPChar);
		break;

		case "Travel_fight":
			ChangeContrabandRelation(pchar, -60);

			LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_SetCheck("TmpEnemy", "Travel_AfterDeckFight");
			LAi_group_FightGroups(LAI_GROUP_PLAYER, "TmpEnemy", true);
			LAi_SetPlayerType(PChar);

			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
			LAi_SetFightMode(Pchar, true);
			LAi_SetWarriorTypeNoGroup(NPChar);
		break;

		case "Travel_end":
			NextDiag.CurrentNode = NextDiag.Tempnode;
			DialogExit();
			//Квест бук
			AddQuestRecord("Gen_ContrabandTravel", "4");
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt"));

			LAi_SetPlayerType(PChar);
			//грузим ГГ куда нужно.... 
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc,
					pchar.GenQuest.contraTravel.destination.group,
					pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
			chrDisableReloadToLocation = false;
			CloseQuestHeader("Gen_ContrabandTravel");
			//трем аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
		break;
	}
}
