// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SantoDomingo_Store_1"),
						StringFromKey("SantoDomingo_Store_2"),
						StringFromKey("SantoDomingo_Store_3"),
						StringFromKey("SantoDomingo_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SantoDomingo_Store_5", NPChar.name),
						StringFromKey("SantoDomingo_Store_6", pchar),
						StringFromKey("SantoDomingo_Store_7"),
						StringFromKey("SantoDomingo_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
