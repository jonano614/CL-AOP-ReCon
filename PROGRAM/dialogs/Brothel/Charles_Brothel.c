// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Charles_Brothel_3", RandPhraseSimple(
								StringFromKey("Charles_Brothel_1", pchar),
								StringFromKey("Charles_Brothel_2", pchar))),
						StringFromKey("Charles_Brothel_4"),
						StringFromKey("Charles_Brothel_5"),
						StringFromKey("Charles_Brothel_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Charles_Brothel_9", RandPhraseSimple(
								StringFromKey("Charles_Brothel_7", pchar),
								StringFromKey("Charles_Brothel_8"))),
						StringFromKey("Charles_Brothel_10"),
						StringFromKey("Charles_Brothel_11"),
						StringFromKey("Charles_Brothel_12"), npchar, Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
