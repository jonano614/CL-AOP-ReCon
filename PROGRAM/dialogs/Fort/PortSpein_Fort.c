// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortSpein_Fort_3", RandPhraseSimple(
								StringFromKey("PortSpein_Fort_1"),
								StringFromKey("PortSpein_Fort_2", GetAddress_Form(NPChar)))),
						StringFromKey("PortSpein_Fort_4", GetAddress_Form(NPChar)),
						StringFromKey("PortSpein_Fort_5"),
						StringFromKey("PortSpein_Fort_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortSpein_Fort_9", RandPhraseSimple(
								StringFromKey("PortSpein_Fort_7", pchar),
								StringFromKey("PortSpein_Fort_8"))),
						StringFromKey("PortSpein_Fort_10"),
						StringFromKey("PortSpein_Fort_11"),
						StringFromKey("PortSpein_Fort_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


