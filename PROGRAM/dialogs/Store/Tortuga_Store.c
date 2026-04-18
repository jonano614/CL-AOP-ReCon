// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_Store_3", RandPhraseSimple(
								StringFromKey("Tortuga_Store_1"),
								StringFromKey("Tortuga_Store_2"))),
						StringFromKey("Tortuga_Store_4"),
						StringFromKey("Tortuga_Store_5"),
						StringFromKey("Tortuga_Store_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_Store_9", RandPhraseSimple(
								StringFromKey("Tortuga_Store_7"),
								StringFromKey("Tortuga_Store_8"))),
						StringFromKey("Tortuga_Store_10"),
						StringFromKey("Tortuga_Store_11"),
						StringFromKey("Tortuga_Store_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			switch (pchar.questTemp.State)
			{
				case "WormEnglPlans_WormPicarder": //Голландская линейка, квест №3. узнаем о Пеьере Пикардийце.
					link.l2 = StringFromKey("Tortuga_Store_13");
					link.l2.go = "Step_H3_1";
				break;

			}
		// <== Проверяем поле состояния квестов.
		break;
		case "Step_H3_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_Store_14"),
						StringFromKey("Tortuga_Store_15", UpperFirst(GetAddress_Form(NPChar))),
						StringFromKey("Tortuga_Store_16"),
						StringFromKey("Tortuga_Store_17"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_Store_18"),
						StringFromKey("Tortuga_Store_19"),
						StringFromKey("Tortuga_Store_20"),
						StringFromKey("Tortuga_Store_21"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H3_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_H3_2":
			dialog.text = StringFromKey("Tortuga_Store_22");
			link.l1 = StringFromKey("Tortuga_Store_23");
			link.l1.go = "exit";
			pchar.questTemp.Hol_Line_AboutWorm.Store = true;
			AddQuestRecord("Hol_Line_3_WormEnglishPlans", "8");
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
