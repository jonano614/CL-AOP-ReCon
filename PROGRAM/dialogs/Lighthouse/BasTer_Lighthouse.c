// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("BasTer_Lighthouse_3", RandPhraseSimple(
								StringFromKey("BasTer_Lighthouse_1"),
								StringFromKey("BasTer_Lighthouse_2"))),
						StringFromKey("BasTer_Lighthouse_4", GetAddress_Form(NPChar)),
						StringFromKey("BasTer_Lighthouse_5"),
						StringFromKey("BasTer_Lighthouse_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("BasTer_Lighthouse_9", RandPhraseSimple(
								StringFromKey("BasTer_Lighthouse_7", pchar),
								StringFromKey("BasTer_Lighthouse_8"))),
						StringFromKey("BasTer_Lighthouse_10", pchar),
						StringFromKey("BasTer_Lighthouse_11"),
						StringFromKey("BasTer_Lighthouse_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

