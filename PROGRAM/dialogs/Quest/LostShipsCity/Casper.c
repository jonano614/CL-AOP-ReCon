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
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fightQuest":
			pchar.questTemp.LSC.Armo.checkCasper = npchar.index; //для обработки в АИ
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//первый каспер на разводе Армо
		case "Casper_1":
			dialog.text = StringFromKey("Casper_1", pchar);
			link.l1 = StringFromKey("Casper_2");
			link.l1.go = "Casper_1_1";
			NextDiag.TempNode = "Casper_12";
			DeleteAttribute(npchar, "checkChrDistance.node");
		break;
		case "Casper_1_1":
			dialog.text = StringFromKey("Casper_3", pchar);
			link.l1 = StringFromKey("Casper_4");
			link.l1.go = "Casper_1_2";
			link.l2 = StringFromKey("Casper_5");
			link.l2.go = "exit";
		break;
		case "Casper_1_2":
			dialog.text = StringFromKey("Casper_6");
			link.l1 = StringFromKey("Casper_7");
			link.l1.go = "fightQuest";
		break;

		case "Casper_12":
			dialog.text = StringFromKey("Casper_8", pchar);
			link.l1 = StringFromKey("Casper_9");
			link.l1.go = "Casper_12_1";
			link.l2 = StringFromKey("Casper_10");
			link.l2.go = "exit";
			NextDiag.TempNode = "Casper_13";
		break;
		case "Casper_12_1":
			dialog.text = StringFromKey("Casper_11");
			link.l1 = StringFromKey("Casper_12");
			link.l1.go = "fightQuest";
		break;

		case "Casper_13":
			dialog.text = StringFromKey("Casper_13", pchar);
			link.l1 = StringFromKey("Casper_14", pchar);
			link.l1.go = "fightQuest";
		break;
		//второй каспер на разводе Армо
		case "Casper_3":
			dialog.text = StringFromKey("Casper_15", pchar);
			link.l1 = StringFromKey("Casper_16");
			link.l1.go = "Casper_3_1";
			NextDiag.TempNode = "Casper_32";
			DeleteAttribute(npchar, "checkChrDistance.node");
		break;
		case "Casper_3_1":
			dialog.text = StringFromKey("Casper_17");
			link.l1 = StringFromKey("Casper_18");
			link.l1.go = "Casper_3_2";
			link.l2 = StringFromKey("Casper_19");
			link.l2.go = "exit";
		break;
		case "Casper_3_2":
			dialog.text = StringFromKey("Casper_20");
			link.l1 = StringFromKey("Casper_21");
			link.l1.go = "fightQuest";
		break;

		case "Casper_32":
			dialog.text = StringFromKey("Casper_22", pchar);
			link.l1 = StringFromKey("Casper_23");
			link.l1.go = "Casper_32_1";
			link.l2 = StringFromKey("Casper_24");
			link.l2.go = "exit";
			NextDiag.TempNode = "Casper_33";
		break;
		case "Casper_32_1":
			dialog.text = StringFromKey("Casper_25");
			link.l1 = StringFromKey("Casper_26");
			link.l1.go = "fightQuest";
		break;

		case "Casper_33":
			dialog.text = StringFromKey("Casper_27", pchar);
			link.l1 = StringFromKey("Casper_28", pchar);
			link.l1.go = "fightQuest";
		break;
		//третий каспер на разводе Армо
		case "Casper_5":
			dialog.text = StringFromKey("Casper_29", pchar);
			link.l1 = StringFromKey("Casper_30");
			link.l1.go = "Casper_5_1";
			NextDiag.TempNode = "Casper_52";
			DeleteAttribute(npchar, "checkChrDistance.node");
		break;
		case "Casper_5_1":
			dialog.text = StringFromKey("Casper_31", pchar);
			link.l1 = StringFromKey("Casper_32");
			link.l1.go = "Casper_5_2";
			link.l2 = StringFromKey("Casper_33", pchar);
			link.l2.go = "exit";
		break;
		case "Casper_5_2":
			dialog.text = StringFromKey("Casper_34");
			link.l1 = StringFromKey("Casper_35", pchar);
			link.l1.go = "fightQuest";
		break;

		case "Casper_52":
			dialog.text = StringFromKey("Casper_36", pchar);
			link.l1 = StringFromKey("Casper_37");
			link.l1.go = "Casper_52_1";
			link.l2 = StringFromKey("Casper_38");
			link.l2.go = "exit";
			NextDiag.TempNode = "Casper_53";
		break;
		case "Casper_52_1":
			dialog.text = StringFromKey("Casper_39");
			link.l1 = StringFromKey("Casper_40");
			link.l1.go = "fightQuest";
		break;

		case "Casper_53":
			dialog.text = StringFromKey("Casper_41");
			link.l1 = StringFromKey("Casper_42");
			link.l1.go = "fightQuest";
		break;
		//ГГ застукали за первым
		case "FackYou":
			dialog.text = StringFromKey("Casper_43");
			link.l1 = StringFromKey("Casper_44", pchar);
			link.l1.go = "FackYou_1";
		break;
		case "FackYou_1":
			dialog.text = StringFromKey("Casper_45", pchar);
			link.l1 = StringFromKey("Casper_46", pchar);
			link.l1.go = "FackYou_2";
		break;
		case "FackYou_2":
			dialog.text = StringFromKey("Casper_47");
			link.l1 = StringFromKey("Casper_48");
			link.l1.go = "FackYou_3";
		break;
		case "FackYou_3":
			dialog.text = StringFromKey("Casper_49", pchar);
			link.l1 = StringFromKey("Casper_50", pchar);
			link.l1.go = "FackYou_4";
		break;
		case "FackYou_4":
			dialog.text = StringFromKey("Casper_51");
			link.l1 = StringFromKey("Casper_52", pchar);
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_3CarperAttackArmo");
		break;
	}
}
