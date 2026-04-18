// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortPax_PortMan_3", RandPhraseSimple(
								StringFromKey("PortPax_PortMan_1"),
								StringFromKey("PortPax_PortMan_2", GetAddress_Form(NPChar)))),
						StringFromKey("PortPax_PortMan_4", GetAddress_Form(NPChar)),
						StringFromKey("PortPax_PortMan_5"),
						StringFromKey("PortPax_PortMan_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortPax_PortMan_9", RandPhraseSimple(
								StringFromKey("PortPax_PortMan_7", pchar),
								StringFromKey("PortPax_PortMan_8"))),
						StringFromKey("PortPax_PortMan_10"),
						StringFromKey("PortPax_PortMan_11"),
						StringFromKey("PortPax_PortMan_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
