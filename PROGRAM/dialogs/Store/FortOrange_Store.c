// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortOrange_Store_3", RandPhraseSimple(
								StringFromKey("FortOrange_Store_1"),
								StringFromKey("FortOrange_Store_2"))),
						StringFromKey("FortOrange_Store_4"),
						StringFromKey("FortOrange_Store_5"),
						StringFromKey("FortOrange_Store_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortOrange_Store_9", RandPhraseSimple(
								StringFromKey("FortOrange_Store_7", pchar),
								StringFromKey("FortOrange_Store_8"))),
						StringFromKey("FortOrange_Store_10", pchar),
						StringFromKey("FortOrange_Store_11"),
						StringFromKey("FortOrange_Store_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			switch (pchar.questTemp.State)
			{
				case "TakeFoodCuracao_toOrangeStore": //Голландская линейка, квест №2, доставка продовольствия из форта Оранж.
					link.l2 = StringFromKey("FortOrange_Store_13");
					link.l2.go = "Step_H2_1";
				break;

			}
		// <== Проверяем поле состояния квестов.
		break;

		case "Step_H2_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortOrange_Store_14", GetAddress_Form(NPChar)),
						StringFromKey("FortOrange_Store_15"),
						StringFromKey("FortOrange_Store_16", pchar),
						StringFromKey("FortOrange_Store_17"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortOrange_Store_18"),
						StringFromKey("FortOrange_Store_19"),
						StringFromKey("FortOrange_Store_20"),
						StringFromKey("FortOrange_Store_21", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "DefenceOrange": //Голландская линейка, квест №4, защита форта Оранж.
			dialog.text = StringFromKey("FortOrange_Store_22");
			link.l2 = StringFromKey("FortOrange_Store_23");
			link.l2.go = "Step_H4_1";
		break;

		case "Step_H4_1":
			dialog.text = StringFromKey("FortOrange_Store_24", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("FortOrange_Store_25");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);
}
