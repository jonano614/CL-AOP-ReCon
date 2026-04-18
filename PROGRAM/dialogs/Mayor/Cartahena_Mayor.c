// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Cartahena_Mayor_3", RandPhraseSimple(
								StringFromKey("Cartahena_Mayor_1"),
								StringFromKey("Cartahena_Mayor_2"))),
						StringFromKey("Cartahena_Mayor_4"),
						StringFromKey("Cartahena_Mayor_5"),
						StringFromKey("Cartahena_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Cartahena_Mayor_9", RandPhraseSimple(
								StringFromKey("Cartahena_Mayor_7", pchar),
								StringFromKey("Cartahena_Mayor_8"))),
						StringFromKey("Cartahena_Mayor_10"),
						StringFromKey("Cartahena_Mayor_11"),
						StringFromKey("Cartahena_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

