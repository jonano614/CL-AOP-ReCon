// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Bridgetown_Lighthouse_3", RandPhraseSimple(
								StringFromKey("Bridgetown_Lighthouse_1"),
								StringFromKey("Bridgetown_Lighthouse_2"))),
						StringFromKey("Bridgetown_Lighthouse_4", GetAddress_Form(NPChar)),
						StringFromKey("Bridgetown_Lighthouse_5"),
						StringFromKey("Bridgetown_Lighthouse_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Bridgetown_Lighthouse_9", RandPhraseSimple(
								StringFromKey("Bridgetown_Lighthouse_7", pchar),
								StringFromKey("Bridgetown_Lighthouse_8"))),
						StringFromKey("Bridgetown_Lighthouse_10", pchar),
						StringFromKey("Bridgetown_Lighthouse_11"),
						StringFromKey("Bridgetown_Lighthouse_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
