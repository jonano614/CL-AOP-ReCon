// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("LaVega_Usurer_3", RandPhraseSimple(
								StringFromKey("LaVega_Usurer_1"),
								StringFromKey("LaVega_Usurer_2"))),
						StringFromKey("LaVega_Usurer_4"),
						StringFromKey("LaVega_Usurer_5"),
						StringFromKey("LaVega_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("LaVega_Usurer_9", RandPhraseSimple(
								StringFromKey("LaVega_Usurer_7"),
								StringFromKey("LaVega_Usurer_8"))),
						StringFromKey("LaVega_Usurer_10"),
						StringFromKey("LaVega_Usurer_11"),
						StringFromKey("LaVega_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
