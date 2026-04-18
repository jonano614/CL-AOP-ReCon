// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Bridgetown_Usurer_3", RandPhraseSimple(
								StringFromKey("Bridgetown_Usurer_1"),
								StringFromKey("Bridgetown_Usurer_2"))),
						StringFromKey("Bridgetown_Usurer_4"),
						StringFromKey("Bridgetown_Usurer_5"),
						StringFromKey("Bridgetown_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Bridgetown_Usurer_9", RandPhraseSimple(
								StringFromKey("Bridgetown_Usurer_7", pchar),
								StringFromKey("Bridgetown_Usurer_8"))),
						StringFromKey("Bridgetown_Usurer_10"),
						StringFromKey("Bridgetown_Usurer_11"),
						StringFromKey("Bridgetown_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
