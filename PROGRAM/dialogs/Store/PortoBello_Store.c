// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortoBello_Store_1"),
						StringFromKey("PortoBello_Store_2"),
						StringFromKey("PortoBello_Store_3"),
						StringFromKey("PortoBello_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortoBello_Store_5", NPChar.name),
						StringFromKey("PortoBello_Store_6", pchar),
						StringFromKey("PortoBello_Store_7"),
						StringFromKey("PortoBello_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
