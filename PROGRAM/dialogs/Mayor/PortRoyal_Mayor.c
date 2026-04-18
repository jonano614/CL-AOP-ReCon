// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortRoyal_Mayor_3", RandPhraseSimple(
								StringFromKey("PortRoyal_Mayor_1"),
								StringFromKey("PortRoyal_Mayor_2"))),
						StringFromKey("PortRoyal_Mayor_4"),
						StringFromKey("PortRoyal_Mayor_5"),
						StringFromKey("PortRoyal_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortRoyal_Mayor_9", RandPhraseSimple(
								StringFromKey("PortRoyal_Mayor_7", pchar),
								StringFromKey("PortRoyal_Mayor_8"))),
						StringFromKey("PortRoyal_Mayor_10"),
						StringFromKey("PortRoyal_Mayor_11"),
						StringFromKey("PortRoyal_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

