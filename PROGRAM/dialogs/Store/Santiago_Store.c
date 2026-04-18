// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Santiago_Store_1"),
						StringFromKey("Santiago_Store_2"),
						StringFromKey("Santiago_Store_3"),
						StringFromKey("Santiago_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Santiago_Store_5", NPChar.name),
						StringFromKey("Santiago_Store_6", pchar),
						StringFromKey("Santiago_Store_7"),
						StringFromKey("Santiago_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
