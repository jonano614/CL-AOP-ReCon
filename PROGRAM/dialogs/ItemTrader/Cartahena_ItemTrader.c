// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Cartahena_ItemTrader_3", RandPhraseSimple(
								StringFromKey("Cartahena_ItemTrader_1"),
								StringFromKey("Cartahena_ItemTrader_2", GetAddress_Form(NPChar)))),
						StringFromKey("Cartahena_ItemTrader_4", GetAddress_Form(NPChar)),
						StringFromKey("Cartahena_ItemTrader_5", GetAddress_Form(NPChar)),
						StringFromKey("Cartahena_ItemTrader_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Cartahena_ItemTrader_9", RandPhraseSimple(
								StringFromKey("Cartahena_ItemTrader_7"),
								StringFromKey("Cartahena_ItemTrader_8"))),
						StringFromKey("Cartahena_ItemTrader_10"),
						StringFromKey("Cartahena_ItemTrader_11"),
						StringFromKey("Cartahena_ItemTrader_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

