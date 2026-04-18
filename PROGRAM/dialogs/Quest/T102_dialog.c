//мумия в алькове
void ProcessDialogEvent()
{
	ref NPChar, PChar, d;
	PChar = GetMainCharacter();
	aref Link, Diag;
	string NPC_Meeting;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = StringFromKey("T102_dialog_1");
			link.l1 = StringFromKey("T102_dialog_2");
			link.l1.go = "Term_1";
			TakeNItems(Pchar, "term_arm", -1);
		break;

		case "Term_1":
			dialog.text = StringFromKey("T102_dialog_3");
			link.l1 = StringFromKey("T102_dialog_4");
			link.l1.go = "Term_2";
		break;

		case "Term_2":
			dialog.text = StringFromKey("T102_dialog_5", GetFullName(pchar));
			link.l1 = StringFromKey("T102_dialog_6", pchar);
			link.l1.go = "Term_3";
		break;

		case "Term_3":
			dialog.text = "Error. Main power too low. Critical error - restarting....";
			link.l1 = StringFromKey("T102_dialog_7");
			link.l1.go = "Term_4";
		break;

		case "Term_4":
			dialog.text = "Loading from backup store....";
			link.l1 = StringFromKey("T102_dialog_8");
			link.l1.go = "Term_5";
		break;

		case "Term_5":
			dialog.text = StringFromKey("T102_dialog_9");
			link.l1 = StringFromKey("T102_dialog_10", pchar);
			link.l1.go = "Term_6";
		break;

		case "Term_6":
			dialog.text = StringFromKey("T102_dialog_11");
			link.l1 = StringFromKey("T102_dialog_12", GetDataYear());
			link.l1.go = "Term_7";
		break;

		case "Term_7":
			dialog.text = StringFromKey("T102_dialog_13");
			link.l1 = StringFromKey("T102_dialog_14");
			link.l1.go = "Term_8";
		break;

		case "Term_8":
			dialog.text = StringFromKey("T102_dialog_15", pchar);
			link.l1 = StringFromKey("T102_dialog_16", pchar);
			link.l1.go = "Term_9";
		break;

		case "Term_9":
			dialog.text = StringFromKey("T102_dialog_17");
			link.l1 = StringFromKey("T102_dialog_18");
			link.l1.go = "Term_9_1";
		break;

		case "Term_9_1":
			dialog.text = StringFromKey("T102_dialog_19");
			link.l1 = StringFromKey("T102_dialog_20");
			link.l1.go = "Term_9_2";
		break;

		case "Term_9_2":
			dialog.text = StringFromKey("T102_dialog_21", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("T102_dialog_22", pchar);
			link.l1.go = "Term_10";
		break;

		case "Term_10":
			dialog.text = StringFromKey("T102_dialog_23");
			link.l1 = StringFromKey("T102_dialog_24");
			link.l1.go = "Term_10_exit";
		//PChar.GenQuest.GhostShip.TakeShotgun = true;
		break;

		case "Term_10_exit":
			LAi_SetPlayerType(PChar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4.0);
			//ChangeCharacterAddressGroup(NPChar, "none", "", "");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		/*case "Term_11":
			dialog.text = "Scanning in process... complite... Твой фенотип на 68%% схож с Сарой о'Конер. Ты потенциальный предок. Миссия должна быть выполнена. Приступить немедленно.";
			link.l1 = "Первый раз так замысловато мне говорят, что хотят меня убить. Хорошо, железяка, я не посмотрю на твою древность и пыль из тебя счас повыколочу.";
			link.l1.go = "Term_11_exit";
		break;
		
		case "Term_11_exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            NPChar.location = "none";
            LAi_SetWarriorType(NPChar);

			LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_SetCheck("TmpEnemy", "Kill_T102");
			LAi_group_FightGroups(LAI_GROUP_PLAYER, "TmpEnemy", true);
			LAi_SetPlayerType(PChar);
			//Вытащим саблю
   			LAi_SetFightMode(Pchar, true);
   			chrDisableReloadToLocation = true;
		break;
		*/
	}
} 
