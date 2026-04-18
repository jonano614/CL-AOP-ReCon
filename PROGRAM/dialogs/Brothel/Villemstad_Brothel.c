// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Villemstad_Brothel_3", RandPhraseSimple(
								StringFromKey("Villemstad_Brothel_1", pchar),
								StringFromKey("Villemstad_Brothel_2", pchar))),
						StringFromKey("Villemstad_Brothel_4"),
						StringFromKey("Villemstad_Brothel_5"),
						StringFromKey("Villemstad_Brothel_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Villemstad_Brothel_9", RandPhraseSimple(
								StringFromKey("Villemstad_Brothel_7", pchar),
								StringFromKey("Villemstad_Brothel_8"))),
						StringFromKey("Villemstad_Brothel_10"),
						StringFromKey("Villemstad_Brothel_11"),
						StringFromKey("Villemstad_Brothel_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
