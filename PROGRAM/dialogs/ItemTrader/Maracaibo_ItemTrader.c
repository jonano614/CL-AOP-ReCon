// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Maracaibo_ItemTrader_3", RandPhraseSimple(
								StringFromKey("Maracaibo_ItemTrader_1"),
								StringFromKey("Maracaibo_ItemTrader_2", GetAddress_Form(NPChar)))),
						StringFromKey("Maracaibo_ItemTrader_4", GetAddress_Form(NPChar)),
						StringFromKey("Maracaibo_ItemTrader_5", GetAddress_Form(NPChar)),
						StringFromKey("Maracaibo_ItemTrader_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Maracaibo_ItemTrader_9", RandPhraseSimple(
								StringFromKey("Maracaibo_ItemTrader_7"),
								StringFromKey("Maracaibo_ItemTrader_8"))),
						StringFromKey("Maracaibo_ItemTrader_10"),
						StringFromKey("Maracaibo_ItemTrader_11"),
						StringFromKey("Maracaibo_ItemTrader_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

