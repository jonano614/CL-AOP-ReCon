// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("BasTer_Tavern_3", RandPhraseSimple(
								StringFromKey("BasTer_Tavern_1"),
								StringFromKey("BasTer_Tavern_2", GetAddress_Form(NPChar)))),
						StringFromKey("BasTer_Tavern_4", GetAddress_Form(NPChar)),
						StringFromKey("BasTer_Tavern_5"),
						StringFromKey("BasTer_Tavern_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("BasTer_Tavern_9", RandPhraseSimple(
								StringFromKey("BasTer_Tavern_7", pchar),
								StringFromKey("BasTer_Tavern_8"))),
						StringFromKey("BasTer_Tavern_10"),
						StringFromKey("BasTer_Tavern_11"),
						StringFromKey("BasTer_Tavern_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
