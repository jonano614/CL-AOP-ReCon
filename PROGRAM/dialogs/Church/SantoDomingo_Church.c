// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SantoDomingo_Church_3", RandPhraseSimple(
								StringFromKey("SantoDomingo_Church_1", pchar),
								StringFromKey("SantoDomingo_Church_2"))),
						StringFromKey("SantoDomingo_Church_4", pchar),
						StringFromKey("SantoDomingo_Church_5", pchar),
						StringFromKey("SantoDomingo_Church_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SantoDomingo_Church_9", RandPhraseSimple(
								StringFromKey("SantoDomingo_Church_7", pchar),
								StringFromKey("SantoDomingo_Church_8"))),
						StringFromKey("SantoDomingo_Church_10"),
						StringFromKey("SantoDomingo_Church_11"),
						StringFromKey("SantoDomingo_Church_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}



