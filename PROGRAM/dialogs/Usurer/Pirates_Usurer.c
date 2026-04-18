// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Pirates_Usurer_3", RandPhraseSimple(
								StringFromKey("Pirates_Usurer_1"),
								StringFromKey("Pirates_Usurer_2"))),
						StringFromKey("Pirates_Usurer_4"),
						StringFromKey("Pirates_Usurer_5"),
						StringFromKey("Pirates_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Pirates_Usurer_9", RandPhraseSimple(
								StringFromKey("Pirates_Usurer_7"),
								StringFromKey("Pirates_Usurer_8"))),
						StringFromKey("Pirates_Usurer_10"),
						StringFromKey("Pirates_Usurer_11"),
						StringFromKey("Pirates_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
