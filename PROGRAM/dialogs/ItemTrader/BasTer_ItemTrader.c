// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("BasTer_ItemTrader_3", RandPhraseSimple(
								StringFromKey("BasTer_ItemTrader_1"),
								StringFromKey("BasTer_ItemTrader_2", GetAddress_Form(NPChar)))),
						StringFromKey("BasTer_ItemTrader_4", GetAddress_Form(NPChar)),
						StringFromKey("BasTer_ItemTrader_5", GetAddress_Form(NPChar)),
						StringFromKey("BasTer_ItemTrader_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("BasTer_ItemTrader_9", RandPhraseSimple(
								StringFromKey("BasTer_ItemTrader_7"),
								StringFromKey("BasTer_ItemTrader_8"))),
						StringFromKey("BasTer_ItemTrader_10"),
						StringFromKey("BasTer_ItemTrader_11"),
						StringFromKey("BasTer_ItemTrader_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

