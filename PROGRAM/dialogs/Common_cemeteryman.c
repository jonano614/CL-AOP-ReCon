// Jason общий диалог смотрителей кладбищ
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\Cemetery\" + NPChar.City + "_Cemetery.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--

	int iTemp;
	string sTemp;
	bool ok;

	switch (Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = PCharRepPhrase(
							StringFromKey("Common_cemeteryman_4", LinkRandPhrase(
									StringFromKey("Common_cemeteryman_1"),
									StringFromKey("Common_cemeteryman_2"),
									StringFromKey("Common_cemeteryman_3"))),
							StringFromKey("Common_cemeteryman_8", LinkRandPhrase(
									StringFromKey("Common_cemeteryman_5", pchar),
									StringFromKey("Common_cemeteryman_6", pchar),
									StringFromKey("Common_cemeteryman_7", pchar))));
				link.l1 = PCharRepPhrase(
							StringFromKey("Common_cemeteryman_11", RandPhraseSimple(
									StringFromKey("Common_cemeteryman_9"),
									StringFromKey("Common_cemeteryman_10", XI_ConvertString("Colony" + npchar.city + "Gen")))),
							StringFromKey("Common_cemeteryman_14", RandPhraseSimple(
									StringFromKey("Common_cemeteryman_12"),
									StringFromKey("Common_cemeteryman_13"))));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = StringFromKey("Common_cemeteryman_17", RandPhraseSimple(
							StringFromKey("Common_cemeteryman_15", GetAddress_Form(NPChar), GetFullName(npchar)),
							StringFromKey("Common_cemeteryman_16", GetFullName(npchar))));
				link.l1 = StringFromKey("Common_cemeteryman_18", pchar, npchar.name, GetFullName(pchar));
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = StringFromKey("Common_cemeteryman_19", GetFullName(pchar));
				link.l1 = StringFromKey("Common_cemeteryman_20", pchar);
				link.l1.go = "talk";
			}
			NextDiag.TempNode = "First time";
		break;

		case "meeting":
			dialog.text = StringFromKey("Common_cemeteryman_21");
			link.l1 = StringFromKey("Common_cemeteryman_22");
			link.l1.go = "trade_info";
			link.l2 = StringFromKey("Common_cemeteryman_23", pchar);
			link.l2.go = "quests";
		break;

		case "talk":
			dialog.text = StringFromKey("Common_cemeteryman_24");
			link.l1 = StringFromKey("Common_cemeteryman_25");
			link.l1.go = "trade";
			link.l2 = StringFromKey("Common_cemeteryman_26", pchar);
			link.l2.go = "quests";
			link.l3 = StringFromKey("Common_cemeteryman_27", pchar);
			link.l3.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "trade_info":
			dialog.text = StringFromKey("Common_cemeteryman_28");
			link.l1 = StringFromKey("Common_cemeteryman_29");
			link.l1.go = "trade_info_1";
		break;

		case "trade_info_1":
			dialog.text = StringFromKey("Common_cemeteryman_30");
			link.l1 = StringFromKey("Common_cemeteryman_31");
			link.l1.go = "trade_info_2";
		break;

		case "trade_info_2":
			dialog.text = StringFromKey("Common_cemeteryman_32", npchar.name);
			link.l1 = StringFromKey("Common_cemeteryman_33");
			link.l1.go = "trade";
			link.l2 = StringFromKey("Common_cemeteryman_34");
			link.l2.go = "exit";
		break;

		case "trade":
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}

			NextDiag.TempNode = "First time";
			DialogExit();
			LaunchItemsTrade(npchar);
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1)
				SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Man_FackYou": //реакция на попытку залезть в сундук
			dialog.text = StringFromKey("Common_cemeteryman_38", LinkRandPhrase(
						StringFromKey("Common_cemeteryman_35", pchar),
						StringFromKey("Common_cemeteryman_36", pchar),
						StringFromKey("Common_cemeteryman_37", pchar)));
			link.l1 = StringFromKey("Common_cemeteryman_39");
			link.l1.go = "fight";
		break;
	}
}
