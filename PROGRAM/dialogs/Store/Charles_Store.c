// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Charles_Store_1"),
						StringFromKey("Charles_Store_2"),
						StringFromKey("Charles_Store_3"),
						StringFromKey("Charles_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Charles_Store_5", NPChar.name),
						StringFromKey("Charles_Store_6", pchar),
						StringFromKey("Charles_Store_7"),
						StringFromKey("Charles_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
