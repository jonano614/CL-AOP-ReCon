// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Marigo_Brothel_3", RandPhraseSimple(
								StringFromKey("Marigo_Brothel_1", pchar),
								StringFromKey("Marigo_Brothel_2", pchar))),
						StringFromKey("Marigo_Brothel_4"),
						StringFromKey("Marigo_Brothel_5"),
						StringFromKey("Marigo_Brothel_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Marigo_Brothel_9", RandPhraseSimple(
								StringFromKey("Marigo_Brothel_7", pchar),
								StringFromKey("Marigo_Brothel_8"))),
						StringFromKey("Marigo_Brothel_10"),
						StringFromKey("Marigo_Brothel_11"),
						StringFromKey("Marigo_Brothel_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
