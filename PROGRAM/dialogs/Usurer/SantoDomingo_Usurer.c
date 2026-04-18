// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SantoDomingo_Usurer_3", RandPhraseSimple(
								StringFromKey("SantoDomingo_Usurer_1"),
								StringFromKey("SantoDomingo_Usurer_2"))),
						StringFromKey("SantoDomingo_Usurer_4"),
						StringFromKey("SantoDomingo_Usurer_5"),
						StringFromKey("SantoDomingo_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SantoDomingo_Usurer_9", RandPhraseSimple(
								StringFromKey("SantoDomingo_Usurer_7", pchar),
								StringFromKey("SantoDomingo_Usurer_8"))),
						StringFromKey("SantoDomingo_Usurer_10"),
						StringFromKey("SantoDomingo_Usurer_11"),
						StringFromKey("SantoDomingo_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
