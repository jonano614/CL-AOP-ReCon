// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortPax_Lighthouse_3", RandPhraseSimple(
								StringFromKey("PortPax_Lighthouse_1"),
								StringFromKey("PortPax_Lighthouse_2"))),
						StringFromKey("PortPax_Lighthouse_4", GetAddress_Form(NPChar)),
						StringFromKey("PortPax_Lighthouse_5"),
						StringFromKey("PortPax_Lighthouse_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortPax_Lighthouse_9", RandPhraseSimple(
								StringFromKey("PortPax_Lighthouse_7", pchar),
								StringFromKey("PortPax_Lighthouse_8"))),
						StringFromKey("PortPax_Lighthouse_10", pchar),
						StringFromKey("PortPax_Lighthouse_11"),
						StringFromKey("PortPax_Lighthouse_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}


