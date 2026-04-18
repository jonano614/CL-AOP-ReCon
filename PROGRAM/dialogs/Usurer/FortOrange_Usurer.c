// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortOrange_Usurer_3", RandPhraseSimple(
								StringFromKey("FortOrange_Usurer_1"),
								StringFromKey("FortOrange_Usurer_2"))),
						StringFromKey("FortOrange_Usurer_4"),
						StringFromKey("FortOrange_Usurer_5"),
						StringFromKey("FortOrange_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortOrange_Usurer_9", RandPhraseSimple(
								StringFromKey("FortOrange_Usurer_7", pchar),
								StringFromKey("FortOrange_Usurer_8"))),
						StringFromKey("FortOrange_Usurer_10"),
						StringFromKey("FortOrange_Usurer_11"),
						StringFromKey("FortOrange_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
