// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("BasTer_Usurer_3", RandPhraseSimple(
								StringFromKey("BasTer_Usurer_1"),
								StringFromKey("BasTer_Usurer_2"))),
						StringFromKey("BasTer_Usurer_4"),
						StringFromKey("BasTer_Usurer_5"),
						StringFromKey("BasTer_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("BasTer_Usurer_9", RandPhraseSimple(
								StringFromKey("BasTer_Usurer_7", pchar),
								StringFromKey("BasTer_Usurer_8"))),
						StringFromKey("BasTer_Usurer_10"),
						StringFromKey("BasTer_Usurer_11"),
						StringFromKey("BasTer_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
