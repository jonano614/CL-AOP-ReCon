// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortRoyal_Shipyard_3", RandPhraseSimple(
								StringFromKey("PortRoyal_Shipyard_1"),
								StringFromKey("PortRoyal_Shipyard_2"))),
						StringFromKey("PortRoyal_Shipyard_4"),
						StringFromKey("PortRoyal_Shipyard_5"),
						StringFromKey("PortRoyal_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortRoyal_Shipyard_9", RandPhraseSimple(
								StringFromKey("PortRoyal_Shipyard_7", pchar),
								StringFromKey("PortRoyal_Shipyard_8"))),
						StringFromKey("PortRoyal_Shipyard_10"),
						StringFromKey("PortRoyal_Shipyard_11"),
						StringFromKey("PortRoyal_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

