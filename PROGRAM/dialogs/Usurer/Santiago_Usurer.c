// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Santiago_Usurer_3", RandPhraseSimple(
								StringFromKey("Santiago_Usurer_1"),
								StringFromKey("Santiago_Usurer_2"))),
						StringFromKey("Santiago_Usurer_4"),
						StringFromKey("Santiago_Usurer_5"),
						StringFromKey("Santiago_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Santiago_Usurer_9", RandPhraseSimple(
								StringFromKey("Santiago_Usurer_7", pchar),
								StringFromKey("Santiago_Usurer_8"))),
						StringFromKey("Santiago_Usurer_10"),
						StringFromKey("Santiago_Usurer_11"),
						StringFromKey("Santiago_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
