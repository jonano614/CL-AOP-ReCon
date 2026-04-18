// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SanJuan_PortMan_3", RandPhraseSimple(
								StringFromKey("SanJuan_PortMan_1"),
								StringFromKey("SanJuan_PortMan_2", GetAddress_Form(NPChar)))),
						StringFromKey("SanJuan_PortMan_4", GetAddress_Form(NPChar)),
						StringFromKey("SanJuan_PortMan_5"),
						StringFromKey("SanJuan_PortMan_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SanJuan_PortMan_9", RandPhraseSimple(
								StringFromKey("SanJuan_PortMan_7", pchar),
								StringFromKey("SanJuan_PortMan_8"))),
						StringFromKey("SanJuan_PortMan_10"),
						StringFromKey("SanJuan_PortMan_11"),
						StringFromKey("SanJuan_PortMan_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
