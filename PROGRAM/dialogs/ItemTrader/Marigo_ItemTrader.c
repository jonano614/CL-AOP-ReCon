// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Marigo_ItemTrader_3", RandPhraseSimple(
								StringFromKey("Marigo_ItemTrader_1"),
								StringFromKey("Marigo_ItemTrader_2", GetAddress_Form(NPChar)))),
						StringFromKey("Marigo_ItemTrader_4", GetAddress_Form(NPChar)),
						StringFromKey("Marigo_ItemTrader_5", GetAddress_Form(NPChar)),
						StringFromKey("Marigo_ItemTrader_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Marigo_ItemTrader_9", RandPhraseSimple(
								StringFromKey("Marigo_ItemTrader_7"),
								StringFromKey("Marigo_ItemTrader_8"))),
						StringFromKey("Marigo_ItemTrader_10"),
						StringFromKey("Marigo_ItemTrader_11"),
						StringFromKey("Marigo_ItemTrader_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

