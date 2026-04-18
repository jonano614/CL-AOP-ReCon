// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SanJuan_Store_1"),
						StringFromKey("SanJuan_Store_2"),
						StringFromKey("SanJuan_Store_3"),
						StringFromKey("SanJuan_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SanJuan_Store_5", NPChar.name),
						StringFromKey("SanJuan_Store_6", pchar),
						StringFromKey("SanJuan_Store_7"),
						StringFromKey("SanJuan_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Romantic_1":
			dialog.Text = StringFromKey("SanJuan_Store_9");
			Link.l1 = StringFromKey("SanJuan_Store_10");
			Link.l1.go = "exit";
			NextDiag.TempNode = "Second time";
			AddDialogExitQuest("Romantic_TalkInShop_2");
		break;

		case "Romantic_2":
			dialog.Text = StringFromKey("SanJuan_Store_11");
			Link.l1 = StringFromKey("SanJuan_Store_12");
			Link.l1.go = "exit";
			NextDiag.TempNode = "Second time";
			AddDialogExitQuest("Romantic_TalkInShop_2");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);
}
