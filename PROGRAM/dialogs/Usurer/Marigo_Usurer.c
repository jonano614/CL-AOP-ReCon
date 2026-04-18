// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Marigo_Usurer_3", RandPhraseSimple(
								StringFromKey("Marigo_Usurer_1"),
								StringFromKey("Marigo_Usurer_2"))),
						StringFromKey("Marigo_Usurer_4"),
						StringFromKey("Marigo_Usurer_5"),
						StringFromKey("Marigo_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Marigo_Usurer_9", RandPhraseSimple(
								StringFromKey("Marigo_Usurer_7", pchar),
								StringFromKey("Marigo_Usurer_8"))),
						StringFromKey("Marigo_Usurer_10"),
						StringFromKey("Marigo_Usurer_11"),
						StringFromKey("Marigo_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
