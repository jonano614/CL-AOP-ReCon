// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortRoyal_Usurer_3", RandPhraseSimple(
								StringFromKey("PortRoyal_Usurer_1"),
								StringFromKey("PortRoyal_Usurer_2"))),
						StringFromKey("PortRoyal_Usurer_4"),
						StringFromKey("PortRoyal_Usurer_5"),
						StringFromKey("PortRoyal_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortRoyal_Usurer_9", RandPhraseSimple(
								StringFromKey("PortRoyal_Usurer_7", pchar),
								StringFromKey("PortRoyal_Usurer_8"))),
						StringFromKey("PortRoyal_Usurer_10"),
						StringFromKey("PortRoyal_Usurer_11"),
						StringFromKey("PortRoyal_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "MorrisWillams_ArrestedToUsurer")
			{
				link.l1 = StringFromKey("PortRoyal_Usurer_13");
				link.l1.go = "Step_E6_1";
			}
			if (pchar.questTemp.State == "MorrisWillams_AfterFightGoRedmond")
			{
				link.l1 = StringFromKey("PortRoyal_Usurer_14");
				link.l1.go = "Step_E6_5";
			}
		break;

		case "Step_E6_1":
			dialog.text = StringFromKey("PortRoyal_Usurer_15");
			link.l1 = StringFromKey("PortRoyal_Usurer_16");
			link.l1.go = "Step_E6_2";
		break;
		case "Step_E6_2":
			dialog.text = StringFromKey("PortRoyal_Usurer_17");
			link.l1 = StringFromKey("PortRoyal_Usurer_18");
			link.l1.go = "Step_E6_3";
		break;
		case "Step_E6_3":
			dialog.text = StringFromKey("PortRoyal_Usurer_19");
			link.l1 = StringFromKey("PortRoyal_Usurer_20");
			link.l1.go = "Step_E6_4";
		break;
		case "Step_E6_4":
			dialog.text = StringFromKey("PortRoyal_Usurer_21", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("PortRoyal_Usurer_22");
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_ArrestedSeekInfo";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "18");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			AddLandQuestmark_Main(characterFromID("PortRoyal_tavernkeeper"), "Eng_Line");
			AddLandQuestmark_Main(characterFromID("PortRoyal_Priest"), "Eng_Line");
		break;
		case "Step_E6_5":
			dialog.text = StringFromKey("PortRoyal_Usurer_23");
			link.l1 = StringFromKey("PortRoyal_Usurer_24", pchar);
			link.l1.go = "Step_E6_6";
		break;
		case "Step_E6_6":
			dialog.text = StringFromKey("PortRoyal_Usurer_25");
			link.l1 = StringFromKey("PortRoyal_Usurer_26");
			link.l1.go = "Step_E6_7";
		break;
		case "Step_E6_7":
			dialog.text = StringFromKey("PortRoyal_Usurer_27");
			link.l1 = StringFromKey("PortRoyal_Usurer_28");
			link.l1.go = "Step_E6_8";
		break;
		case "Step_E6_8":
			dialog.text = StringFromKey("PortRoyal_Usurer_29");
			link.l1 = StringFromKey("PortRoyal_Usurer_30");
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.State = "empty";
			pchar.questTemp.CurQuestNumber = "7";
			pchar.questTemp.Waiting_time = "5";
			//ChangeCharacterReputation(pchar, -2); // за попытку шантажа TODO eddy
			AddCharacterExpToSkill(pchar, "Accuracy", 80);
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			AddCharacterExpToSkill(pchar, "Sneak ", 70);
			AddCharacterExpToSkill(pchar, "Fencing  ", 100);
			AddCharacterExpToSkill(pchar, "Defence  ", 50);
			AddQuestRecord("Eng_Line_6_MorrisWillams", "22");
			CloseQuestHeader("Eng_Line_6_MorrisWillams");
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Morris_Willams")], "PortRoyal_tavern", "sit", "sit1");
			characters[GetCharacterIndex("Morris_Willams")].dialog.currentnode = "Willams_NiceTalking";
			LAi_SetSitTypeNoGroup(characterFromID("Morris_Willams"));
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			AddLandQuestmark_Main_WithCondition(CharacterFromID("eng_guber"), "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
