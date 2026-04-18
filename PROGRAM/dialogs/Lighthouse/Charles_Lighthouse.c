// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Charles_Lighthouse_3", RandPhraseSimple(
								StringFromKey("Charles_Lighthouse_1"),
								StringFromKey("Charles_Lighthouse_2"))),
						StringFromKey("Charles_Lighthouse_4", GetAddress_Form(NPChar)),
						StringFromKey("Charles_Lighthouse_5"),
						StringFromKey("Charles_Lighthouse_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Charles_Lighthouse_9", RandPhraseSimple(
								StringFromKey("Charles_Lighthouse_7", pchar),
								StringFromKey("Charles_Lighthouse_8"))),
						StringFromKey("Charles_Lighthouse_10", pchar),
						StringFromKey("Charles_Lighthouse_11"),
						StringFromKey("Charles_Lighthouse_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

