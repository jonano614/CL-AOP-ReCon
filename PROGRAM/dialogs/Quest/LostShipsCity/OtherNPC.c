//Диалоговый файл НПС квеста-подводки ГПК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string attrL, sRep;
	int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "StarsAlignedCompanion":
			dialog.text = StringFromKey("OtherNPC_1");
			link.l1 = StringFromKey("OtherNPC_2");
			link.l1.go = "StarsAlignedCompanion_1";
		break;
		case "StarsAlignedCompanion_1":
			dialog.text = StringFromKey("OtherNPC_3");
			link.l1 = StringFromKey("OtherNPC_4");
			link.l1.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_3");
		break;

		case "StarsAlignedAhtung":
			dialog.text = StringFromKey("OtherNPC_5");
			link.l1 = StringFromKey("OtherNPC_6");
			link.l1.go = "StarsAlignedAhtung_1";
		break;
		case "StarsAlignedAhtung_1":
			dialog.text = StringFromKey("OtherNPC_7");
			link.l1 = StringFromKey("OtherNPC_8");
			link.l1.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_8");
		break;

		case "JungleManDialog":
			dialog.text = StringFromKey("OtherNPC_9");
			link.l1 = StringFromKey("OtherNPC_10");
			link.l1.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_10");
		break;

		case "JungleManDialog2":
			LAi_ActorTurnToCharacter(CharacterFromID("John_CoxonLSC"), pchar);
			sld = CharacterFromID("Henry Morgan");
			if (sld.Dialog.TempNode == "I_know_you_good")
			{
				dialog.text = StringFromKey("OtherNPC_11", GetFullName(pchar));
				link.l1 = StringFromKey("OtherNPC_12", npchar.name);
			}
			else
			{
				dialog.text = StringFromKey("OtherNPC_13");
				link.l1 = StringFromKey("OtherNPC_14", GetFullName(pchar));
			}
			link.l1.go = "JungleManDialog2_1";
		break;
		case "JungleManDialog2_1":
			dialog.text = StringFromKey("OtherNPC_15");
			link.l1 = StringFromKey("OtherNPC_16");
			link.l1.go = "JungleManDialog2_2";
		break;
		case "JungleManDialog2_2":
			dialog.text = StringFromKey("OtherNPC_17");
			link.l1 = StringFromKey("OtherNPC_18");
			link.l1.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_12");
		break;

		case "JungleManDialog3":
			dialog.text = StringFromKey("OtherNPC_19");
			link.l1 = StringFromKey("OtherNPC_20", npchar.lastname);
			link.l1.go = "JungleManDialog3_1";
		break;
		case "JungleManDialog3_1":
			dialog.text = StringFromKey("OtherNPC_21");
			link.l1 = StringFromKey("OtherNPC_22");
			link.l1.go = "JungleManDialog3_2";
		break;
		case "JungleManDialog3_2":
			dialog.text = StringFromKey("OtherNPC_23", pchar.name);
			link.l1 = StringFromKey("OtherNPC_24");
			link.l1.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_14");
		break;

		case "JungleManDialog4":
			dialog.text = StringFromKey("OtherNPC_25", GetFullName(pchar));
			link.l1 = StringFromKey("OtherNPC_26");
			link.l1.go = "JungleManDialog4_1";
		break;
		case "JungleManDialog4_1":
			dialog.text = StringFromKey("OtherNPC_27");
			link.l1 = StringFromKey("OtherNPC_28");
			link.l1.go = "JungleManDialog4_2";
		break;
		case "JungleManDialog4_2":
			dialog.text = StringFromKey("OtherNPC_29");
			link.l1 = StringFromKey("OtherNPC_30");
			link.l1.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_16");
		break;

		case "StarsAlignedAhtung2":
			dialog.text = StringFromKey("OtherNPC_31");
			link.l1 = StringFromKey("OtherNPC_32");
			link.l1.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_20");
		break;

		case "ReturnJungleMan":
			dialog.text = StringFromKey("OtherNPC_33");
			link.l1 = StringFromKey("OtherNPC_34", npchar.name);
			link.l1.go = "ReturnJungleMan_1";
		break;
		case "ReturnJungleMan_1":
			dialog.text = StringFromKey("OtherNPC_35");
			link.l1 = StringFromKey("OtherNPC_36");
			link.l1.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_44");
		break;

		case "GoodByeOrangeBeach":
			dialog.text = StringFromKey("OtherNPC_37");
			link.l1 = StringFromKey("OtherNPC_38", pchar, npchar.name);
			link.l1.go = "exit";
			AddQuestRecord("TheStarsAlignedISS", "4");
			AddDialogExitQuest("TheStarsAlignedLSC_48");
		break;

	}
	NextDiag.PrevNode = NodeName;
}

