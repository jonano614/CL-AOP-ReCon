// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SanJuan_Usurer_3", RandPhraseSimple(
								StringFromKey("SanJuan_Usurer_1"),
								StringFromKey("SanJuan_Usurer_2"))),
						StringFromKey("SanJuan_Usurer_4"),
						StringFromKey("SanJuan_Usurer_5"),
						StringFromKey("SanJuan_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SanJuan_Usurer_9", RandPhraseSimple(
								StringFromKey("SanJuan_Usurer_7", pchar),
								StringFromKey("SanJuan_Usurer_8"))),
						StringFromKey("SanJuan_Usurer_10"),
						StringFromKey("SanJuan_Usurer_11"),
						StringFromKey("SanJuan_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
