// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortPax_Shipyard_3", RandPhraseSimple(
								StringFromKey("PortPax_Shipyard_1"),
								StringFromKey("PortPax_Shipyard_2"))),
						StringFromKey("PortPax_Shipyard_4"),
						StringFromKey("PortPax_Shipyard_5"),
						StringFromKey("PortPax_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortPax_Shipyard_9", RandPhraseSimple(
								StringFromKey("PortPax_Shipyard_7", pchar),
								StringFromKey("PortPax_Shipyard_8"))),
						StringFromKey("PortPax_Shipyard_10"),
						StringFromKey("PortPax_Shipyard_11"),
						StringFromKey("PortPax_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

