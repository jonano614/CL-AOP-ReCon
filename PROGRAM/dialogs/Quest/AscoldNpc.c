void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("AscoldNpc_1");
			link.l1 = StringFromKey("AscoldNpc_2");
			link.l1.go = "exit";
			//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
			if (pchar.questTemp.Ascold == "SeekInformatorHavanna" || pchar.questTemp.Ascold == "2SeekInformatorHavanna")
			{
				dialog.text = StringFromKey("AscoldNpc_3");
				link.l1 = StringFromKey("AscoldNpc_4", pchar, GetFullName(pchar));
				link.l1.go = "Step_1";
			}
			if (pchar.questTemp.Ascold == "ReciveInformationManowar")
			{
				dialog.text = StringFromKey("AscoldNpc_5", pchar);
				link.l1 = StringFromKey("AscoldNpc_6");
				link.l1.go = "exit";
			}
		break;
		//<<<<<<<<<<<<======== Разброс диалогов по персонажам ======================
		case "Step_1":
			dialog.text = StringFromKey("AscoldNpc_7");
			link.l1 = StringFromKey("AscoldNpc_8");
			link.l1.go = "Step_2";
		break;
		case "Step_2":
			dialog.text = StringFromKey("AscoldNpc_9");
			link.l1 = StringFromKey("AscoldNpc_10");
			link.l1.go = "Step_3";
		break;
		case "Step_3":
			dialog.text = StringFromKey("AscoldNpc_11");
			link.l1 = StringFromKey("AscoldNpc_12");
			link.l1.go = "Step_4";
		break;
		case "Step_4":
			dialog.text = StringFromKey("AscoldNpc_13");
			link.l1 = StringFromKey("AscoldNpc_14");
			link.l1.go = "Step_5";
		break;
		case "Step_5":
			dialog.text = StringFromKey("AscoldNpc_15");
			link.l1 = StringFromKey("AscoldNpc_16");
			link.l1.go = "Step_6";
		break;
		case "Step_6":
			dialog.text = StringFromKey("AscoldNpc_17");
			link.l1 = StringFromKey("AscoldNpc_18");
			link.l1.go = "Step_7";
		break;
		case "Step_7":
			dialog.text = StringFromKey("AscoldNpc_19", pchar);
			link.l1 = StringFromKey("AscoldNpc_20");
			link.l1.go = "exit";
			npchar.LifeDay = 5;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			AddQuestRecord("Ascold", "7");
			pchar.questTemp.Ascold = "ReciveInformationManowar";
			Pchar.quest.Ascold_AttackTenManowars.win_condition.l1 = "location";
			Pchar.quest.Ascold_AttackTenManowars.win_condition.l1.location = "Caiman";
			Pchar.quest.Ascold_AttackTenManowars.win_condition = "Ascold_AttackTenManowars";
			RemoveLandQuestmark_Main(npchar, "Ascold");
			AddLandQuestmark_Main(CharacterFromID("Ascold"), "Ascold");
		break;

		case "Step_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Step_";
		break;
		case "Exit":
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
