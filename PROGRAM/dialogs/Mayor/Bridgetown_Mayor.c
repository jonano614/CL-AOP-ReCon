// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Bridgetown_Mayor_3", RandPhraseSimple(
								StringFromKey("Bridgetown_Mayor_1"),
								StringFromKey("Bridgetown_Mayor_2"))),
						StringFromKey("Bridgetown_Mayor_4"),
						StringFromKey("Bridgetown_Mayor_5"),
						StringFromKey("Bridgetown_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Bridgetown_Mayor_9", RandPhraseSimple(
								StringFromKey("Bridgetown_Mayor_7", pchar),
								StringFromKey("Bridgetown_Mayor_8"))),
						StringFromKey("Bridgetown_Mayor_10"),
						StringFromKey("Bridgetown_Mayor_11"),
						StringFromKey("Bridgetown_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

