// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("LaVega_Store_1"),
						StringFromKey("LaVega_Store_2"),
						StringFromKey("LaVega_Store_3"),
						StringFromKey("LaVega_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("LaVega_Store_5", NPChar.name),
						StringFromKey("LaVega_Store_6", pchar),
						StringFromKey("LaVega_Store_7"),
						StringFromKey("LaVega_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
