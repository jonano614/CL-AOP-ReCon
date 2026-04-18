// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortFrance_Shipyard_3", RandPhraseSimple(
								StringFromKey("FortFrance_Shipyard_1"),
								StringFromKey("FortFrance_Shipyard_2"))),
						StringFromKey("FortFrance_Shipyard_4"),
						StringFromKey("FortFrance_Shipyard_5"),
						StringFromKey("FortFrance_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortFrance_Shipyard_9", RandPhraseSimple(
								StringFromKey("FortFrance_Shipyard_7", pchar),
								StringFromKey("FortFrance_Shipyard_8"))),
						StringFromKey("FortFrance_Shipyard_10"),
						StringFromKey("FortFrance_Shipyard_11"),
						StringFromKey("FortFrance_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";

			if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "FL2_s3") // Dolphin Французский сюжет. Поиск Гранье
			{
				link.l1 = StringFromKey("FortFrance_Shipyard_13");
				link.l1.go = "FL2_1";
			}
			if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "FL4_s49" && !CheckAttribute(pchar, "MainQuest.FL4_s49.shipyard"))
			{
				link.l1 = StringFromKey("FortFrance_Shipyard_14");
				link.l1.go = "FL4_1";
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine") && pchar.questTemp.piratesLine == "KillLoy_toSeek")
			{
				link.l1 = StringFromKey("FortFrance_Shipyard_15");
				link.l1.go = "PL_Q3_1";
			}
		break;

		//----------------------------------------------------------------------------------------------
		// Dolphin Французский сюжет. Поиск Гранье ->
		case "FL2_1":
			dialog.text = StringFromKey("FortFrance_Shipyard_16");
			link.l1 = StringFromKey("FortFrance_Shipyard_17");
			link.l1.go = "FL2_2";
		break;

		case "FL2_2":
			dialog.text = StringFromKey("FortFrance_Shipyard_18");
			link.l1 = StringFromKey("FortFrance_Shipyard_19");
			link.l1.go = "FL2_3";
		break;

		case "FL2_3":
			dialog.text = StringFromKey("FortFrance_Shipyard_20");
			link.l1 = StringFromKey("FortFrance_Shipyard_21");
			link.l1.go = "FL2_4";
		break;

		case "FL2_4":
			dialog.text = StringFromKey("FortFrance_Shipyard_22");
			link.l1 = StringFromKey("FortFrance_Shipyard_23");
			link.l1.go = "FL2_5";
		break;

		case "FL2_5":
			dialog.text = StringFromKey("FortFrance_Shipyard_24");
			link.l1 = StringFromKey("FortFrance_Shipyard_25");
			link.l1.go = "FL2_6";
		break;

		case "FL2_6":
			dialog.text = StringFromKey("FortFrance_Shipyard_26");
			link.l1 = StringFromKey("FortFrance_Shipyard_27");
			link.l1.go = "FL2_7";
		break;

		case "FL2_7":
			dialog.text = StringFromKey("FortFrance_Shipyard_28");
			link.l1 = StringFromKey("FortFrance_Shipyard_29");
			link.l1.go = "FL2_8";
		break;

		case "FL2_8":
			dialog.text = StringFromKey("FortFrance_Shipyard_30");
			link.l1 = StringFromKey("FortFrance_Shipyard_31");
			link.l1.go = "FL2_9";
		break;

		case "FL2_9":
			dialog.text = StringFromKey("FortFrance_Shipyard_32");
			link.l1 = StringFromKey("FortFrance_Shipyard_33");
			link.l1.go = "FL2_10";
		break;

		case "FL2_10":
			dialog.text = StringFromKey("FortFrance_Shipyard_34");
			link.l1 = "...";
			link.l1.go = "exit";

			AddDialogExitQuest("FL2_s4");
		break;
		// Dolphin Французский сюжет. Поиск Гранье <-

		//	Фр. сюжет - Разоблачение
		case "FL4_1":
			dialog.text = StringFromKey("FortFrance_Shipyard_35");
			link.l1 = StringFromKey("FortFrance_Shipyard_36");
			link.l1.go = "FL4_2";
		break;

		case "FL4_2":
			dialog.text = StringFromKey("FortFrance_Shipyard_37");
			link.l1 = StringFromKey("FortFrance_Shipyard_38");
			link.l1.go = "exit";

			pchar.MainQuest.FL4_s49.shipyard = 1;
		//AddDialogExitQuest("FL4_s50");
		break;
		//	Фр. сюжет - Разоблачение

		//пиратка, квест №3, поиски Лоу
		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortFrance_Shipyard_39"),
						StringFromKey("FortFrance_Shipyard_40"),
						StringFromKey("FortFrance_Shipyard_41"),
						StringFromKey("FortFrance_Shipyard_42", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortFrance_Shipyard_43"),
						StringFromKey("FortFrance_Shipyard_44"),
						StringFromKey("FortFrance_Shipyard_45"),
						StringFromKey("FortFrance_Shipyard_46"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q3_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q3_2":
			dialog.text = StringFromKey("FortFrance_Shipyard_47");
			link.l1 = StringFromKey("FortFrance_Shipyard_48");
			link.l1.go = "PL_Q3_3";
		break;
		case "PL_Q3_3":
			dialog.text = StringFromKey("FortFrance_Shipyard_49");
			link.l1 = StringFromKey("FortFrance_Shipyard_50");
			link.l1.go = "PL_Q3_4";
		break;
		case "PL_Q3_4":
			dialog.text = StringFromKey("FortFrance_Shipyard_51");
			link.l1 = StringFromKey("FortFrance_Shipyard_52");
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "4");
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

