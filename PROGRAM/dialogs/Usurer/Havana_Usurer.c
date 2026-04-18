// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Havana_Usurer_3", RandPhraseSimple(
								StringFromKey("Havana_Usurer_1"),
								StringFromKey("Havana_Usurer_2"))),
						StringFromKey("Havana_Usurer_4"),
						StringFromKey("Havana_Usurer_5"),
						StringFromKey("Havana_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Havana_Usurer_9", RandPhraseSimple(
								StringFromKey("Havana_Usurer_7", pchar),
								StringFromKey("Havana_Usurer_8"))),
						StringFromKey("Havana_Usurer_10"),
						StringFromKey("Havana_Usurer_11"),
						StringFromKey("Havana_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
