// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SantaCatalina_PortMan_3", RandPhraseSimple(
								StringFromKey("SantaCatalina_PortMan_1"),
								StringFromKey("SantaCatalina_PortMan_2", GetAddress_Form(NPChar)))),
						StringFromKey("SantaCatalina_PortMan_4", GetAddress_Form(NPChar)),
						StringFromKey("SantaCatalina_PortMan_5"),
						StringFromKey("SantaCatalina_PortMan_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SantaCatalina_PortMan_9", RandPhraseSimple(
								StringFromKey("SantaCatalina_PortMan_7", pchar),
								StringFromKey("SantaCatalina_PortMan_8"))),
						StringFromKey("SantaCatalina_PortMan_10"),
						StringFromKey("SantaCatalina_PortMan_11"),
						StringFromKey("SantaCatalina_PortMan_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
