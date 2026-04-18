// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortOrange_Mayor_3", RandPhraseSimple(
								StringFromKey("FortOrange_Mayor_1"),
								StringFromKey("FortOrange_Mayor_2"))),
						StringFromKey("FortOrange_Mayor_4"),
						StringFromKey("FortOrange_Mayor_5"),
						StringFromKey("FortOrange_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortOrange_Mayor_9", RandPhraseSimple(
								StringFromKey("FortOrange_Mayor_7", pchar),
								StringFromKey("FortOrange_Mayor_8"))),
						StringFromKey("FortOrange_Mayor_10"),
						StringFromKey("FortOrange_Mayor_11"),
						StringFromKey("FortOrange_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			switch (pchar.questTemp.State)
			{
				case "TakeFoodCuracao_toOrangeMayor": //Голландская линейка, квест №2, доставка продовольствия из форта Оранж.
					link.l2 = StringFromKey("FortOrange_Mayor_13", pchar);
					link.l2.go = "Step_H2_1";
				break;

			}
		// <== Проверяем поле состояния квестов.
		break;

		case "Step_H2_1":
			dialog.text = StringFromKey("FortOrange_Mayor_14");
			link.l1 = StringFromKey("FortOrange_Mayor_15");
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "Trust_HolLineQ2");
			AddQuestRecord("Hol_Line_2_TakeFoodCuracao", "2");
			pchar.questTemp.State = "TakeFoodCuracao_toOrangeStore";
			pchar.GenQuest.StoreGoods.StoreIdx = FortOrange_STORE;
			pchar.GenQuest.StoreGoods.HL2_DiscountPrices = true;
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(characterFromID("FortOrange_trader"), "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("hol_guber"), "Hol_Line");
		break;

		case "DefenceOrange": //Голландская линейка, квест №4, защита форта Оранж.
			dialog.text = StringFromKey("FortOrange_Mayor_16");
			link.l2 = StringFromKey("FortOrange_Mayor_17");
			link.l2.go = "Step_H4_1";
		break;

		case "Step_H4_1":
			dialog.text = StringFromKey("FortOrange_Mayor_18");
			link.l1 = StringFromKey("FortOrange_Mayor_19");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

