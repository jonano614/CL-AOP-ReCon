// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SentJons_Mayor_3", RandPhraseSimple(
								StringFromKey("SentJons_Mayor_1"),
								StringFromKey("SentJons_Mayor_2"))),
						StringFromKey("SentJons_Mayor_4"),
						StringFromKey("SentJons_Mayor_5"),
						StringFromKey("SentJons_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SentJons_Mayor_9", RandPhraseSimple(
								StringFromKey("SentJons_Mayor_7", pchar),
								StringFromKey("SentJons_Mayor_8"))),
						StringFromKey("SentJons_Mayor_10"),
						StringFromKey("SentJons_Mayor_11"),
						StringFromKey("SentJons_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

