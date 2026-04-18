// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Charles_Church_3", RandPhraseSimple(
								StringFromKey("Charles_Church_1", pchar),
								StringFromKey("Charles_Church_2"))),
						StringFromKey("Charles_Church_4", pchar),
						StringFromKey("Charles_Church_5", pchar),
						StringFromKey("Charles_Church_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Charles_Church_9", RandPhraseSimple(
								StringFromKey("Charles_Church_7", pchar),
								StringFromKey("Charles_Church_8"))),
						StringFromKey("Charles_Church_10"),
						StringFromKey("Charles_Church_11"),
						StringFromKey("Charles_Church_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}



