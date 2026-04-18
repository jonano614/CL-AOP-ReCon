// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortFrance_Brothel_3", RandPhraseSimple(
								StringFromKey("FortFrance_Brothel_1", pchar),
								StringFromKey("FortFrance_Brothel_2", pchar))),
						StringFromKey("FortFrance_Brothel_4"),
						StringFromKey("FortFrance_Brothel_5"),
						StringFromKey("FortFrance_Brothel_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortFrance_Brothel_9", RandPhraseSimple(
								StringFromKey("FortFrance_Brothel_7", pchar),
								StringFromKey("FortFrance_Brothel_8"))),
						StringFromKey("FortFrance_Brothel_10"),
						StringFromKey("FortFrance_Brothel_11"),
						StringFromKey("FortFrance_Brothel_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			if (pchar.questTemp.State == "SeekBible_toFFBrothel" && npchar.id == "FortFrance_Hostess") //Голландская линейка, квест №8. узнаем о пирате, который о Библии базарил.
			{
				link.l1 = StringFromKey("FortFrance_Brothel_13");
				link.l1.go = "Step_H8_1";
			}
		// <== Проверяем поле состояния квестов.
		break;

		case "Step_H8_1":
			dialog.text = StringFromKey("FortFrance_Brothel_14", pchar);
			link.l1 = StringFromKey("FortFrance_Brothel_15");
			link.l1.go = "Step_H8_2";
		break;
		case "Step_H8_2":
			dialog.text = StringFromKey("FortFrance_Brothel_16");
			link.l1 = StringFromKey("FortFrance_Brothel_17");
			link.l1.go = "Step_H8_3";
		break;
		case "Step_H8_3":
			dialog.text = StringFromKey("FortFrance_Brothel_18");
			link.l1 = StringFromKey("FortFrance_Brothel_19");
			link.l1.go = "Step_H8_4";
		break;
		case "Step_H8_4":
			dialog.text = StringFromKey("FortFrance_Brothel_20");
			link.l1 = StringFromKey("FortFrance_Brothel_21");
			link.l1.go = "Step_H8_5";
		break;
		case "Step_H8_5":
			dialog.text = StringFromKey("FortFrance_Brothel_22", pchar);
			link.l1 = StringFromKey("FortFrance_Brothel_23");
			link.l1.go = "Step_H8_6";
		break;
		case "Step_H8_6":
			dialog.text = StringFromKey("FortFrance_Brothel_24");
			link.l1 = StringFromKey("FortFrance_Brothel_25");
			link.l1.go = "exit";
			pchar.questTemp.State = "SeekBible_toGirl";
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
