// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortSpein_Shipyard_3", RandPhraseSimple(
								StringFromKey("PortSpein_Shipyard_1"),
								StringFromKey("PortSpein_Shipyard_2"))),
						StringFromKey("PortSpein_Shipyard_4"),
						StringFromKey("PortSpein_Shipyard_5"),
						StringFromKey("PortSpein_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortSpein_Shipyard_9", RandPhraseSimple(
								StringFromKey("PortSpein_Shipyard_7", pchar),
								StringFromKey("PortSpein_Shipyard_8"))),
						StringFromKey("PortSpein_Shipyard_10"),
						StringFromKey("PortSpein_Shipyard_11"),
						StringFromKey("PortSpein_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

