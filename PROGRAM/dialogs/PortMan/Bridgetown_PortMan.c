// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Bridgetown_PortMan_3", RandPhraseSimple(
								StringFromKey("Bridgetown_PortMan_1"),
								StringFromKey("Bridgetown_PortMan_2", GetAddress_Form(NPChar)))),
						StringFromKey("Bridgetown_PortMan_4", GetAddress_Form(NPChar)),
						StringFromKey("Bridgetown_PortMan_5"),
						StringFromKey("Bridgetown_PortMan_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Bridgetown_PortMan_9", RandPhraseSimple(
								StringFromKey("Bridgetown_PortMan_7", pchar),
								StringFromKey("Bridgetown_PortMan_8"))),
						StringFromKey("Bridgetown_PortMan_10"),
						StringFromKey("Bridgetown_PortMan_11"),
						StringFromKey("Bridgetown_PortMan_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


