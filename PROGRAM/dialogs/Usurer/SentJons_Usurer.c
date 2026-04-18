// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SentJons_Usurer_3", RandPhraseSimple(
								StringFromKey("SentJons_Usurer_1"),
								StringFromKey("SentJons_Usurer_2"))),
						StringFromKey("SentJons_Usurer_4"),
						StringFromKey("SentJons_Usurer_5"),
						StringFromKey("SentJons_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SentJons_Usurer_9", RandPhraseSimple(
								StringFromKey("SentJons_Usurer_7", pchar),
								StringFromKey("SentJons_Usurer_8"))),
						StringFromKey("SentJons_Usurer_10"),
						StringFromKey("SentJons_Usurer_11"),
						StringFromKey("SentJons_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
