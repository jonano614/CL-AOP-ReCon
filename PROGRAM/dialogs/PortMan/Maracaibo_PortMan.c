// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Maracaibo_PortMan_3", RandPhraseSimple(
								StringFromKey("Maracaibo_PortMan_1"),
								StringFromKey("Maracaibo_PortMan_2", GetAddress_Form(NPChar)))),
						StringFromKey("Maracaibo_PortMan_4", GetAddress_Form(NPChar)),
						StringFromKey("Maracaibo_PortMan_5"),
						StringFromKey("Maracaibo_PortMan_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Maracaibo_PortMan_9", RandPhraseSimple(
								StringFromKey("Maracaibo_PortMan_7", pchar),
								StringFromKey("Maracaibo_PortMan_8"))),
						StringFromKey("Maracaibo_PortMan_10"),
						StringFromKey("Maracaibo_PortMan_11"),
						StringFromKey("Maracaibo_PortMan_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
