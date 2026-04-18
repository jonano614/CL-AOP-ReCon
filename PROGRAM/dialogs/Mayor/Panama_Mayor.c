// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Panama_Mayor_3", RandPhraseSimple(
								StringFromKey("Panama_Mayor_1"),
								StringFromKey("Panama_Mayor_2"))),
						StringFromKey("Panama_Mayor_4"),
						StringFromKey("Panama_Mayor_5"),
						StringFromKey("Panama_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Panama_Mayor_9", RandPhraseSimple(
								StringFromKey("Panama_Mayor_7", pchar),
								StringFromKey("Panama_Mayor_8"))),
						StringFromKey("Panama_Mayor_10"),
						StringFromKey("Panama_Mayor_11"),
						StringFromKey("Panama_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

