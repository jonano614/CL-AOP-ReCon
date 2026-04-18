// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortSpein_Store_1"),
						StringFromKey("PortSpein_Store_2"),
						StringFromKey("PortSpein_Store_3"),
						StringFromKey("PortSpein_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortSpein_Store_5", NPChar.name),
						StringFromKey("PortSpein_Store_6", pchar),
						StringFromKey("PortSpein_Store_7"),
						StringFromKey("PortSpein_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
