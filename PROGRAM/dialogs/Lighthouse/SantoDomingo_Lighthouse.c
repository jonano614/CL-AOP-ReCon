// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SantoDomingo_Lighthouse_3", RandPhraseSimple(
								StringFromKey("SantoDomingo_Lighthouse_1"),
								StringFromKey("SantoDomingo_Lighthouse_2"))),
						StringFromKey("SantoDomingo_Lighthouse_4", GetAddress_Form(NPChar)),
						StringFromKey("SantoDomingo_Lighthouse_5"),
						StringFromKey("SantoDomingo_Lighthouse_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SantoDomingo_Lighthouse_9", RandPhraseSimple(
								StringFromKey("SantoDomingo_Lighthouse_7", pchar),
								StringFromKey("SantoDomingo_Lighthouse_8"))),
						StringFromKey("SantoDomingo_Lighthouse_10", pchar),
						StringFromKey("SantoDomingo_Lighthouse_11"),
						StringFromKey("SantoDomingo_Lighthouse_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

