// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("LaVega_Mayor_3", RandPhraseSimple(
								StringFromKey("LaVega_Mayor_1"),
								StringFromKey("LaVega_Mayor_2"))),
						StringFromKey("LaVega_Mayor_4"),
						StringFromKey("LaVega_Mayor_5"),
						StringFromKey("LaVega_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("LaVega_Mayor_9", RandPhraseSimple(
								StringFromKey("LaVega_Mayor_7", pchar),
								StringFromKey("LaVega_Mayor_8"))),
						StringFromKey("LaVega_Mayor_10"),
						StringFromKey("LaVega_Mayor_11"),
						StringFromKey("LaVega_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
