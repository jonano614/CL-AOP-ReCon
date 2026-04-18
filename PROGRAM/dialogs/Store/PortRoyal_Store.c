// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortRoyal_Store_1"),
						StringFromKey("PortRoyal_Store_2"),
						StringFromKey("PortRoyal_Store_3"),
						StringFromKey("PortRoyal_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortRoyal_Store_5", NPChar.name),
						StringFromKey("PortRoyal_Store_6", pchar),
						StringFromKey("PortRoyal_Store_7"),
						StringFromKey("PortRoyal_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
