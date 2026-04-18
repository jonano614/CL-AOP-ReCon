// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Charles_Mayor_3", RandPhraseSimple(
								StringFromKey("Charles_Mayor_1"),
								StringFromKey("Charles_Mayor_2"))),
						StringFromKey("Charles_Mayor_4"),
						StringFromKey("Charles_Mayor_5"),
						StringFromKey("Charles_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Charles_Mayor_9", RandPhraseSimple(
								StringFromKey("Charles_Mayor_7", pchar),
								StringFromKey("Charles_Mayor_8"))),
						StringFromKey("Charles_Mayor_10"),
						StringFromKey("Charles_Mayor_11"),
						StringFromKey("Charles_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

