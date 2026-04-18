// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Beliz_Store_1"),
						StringFromKey("Beliz_Store_2"),
						StringFromKey("Beliz_Store_3"),
						StringFromKey("Beliz_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Beliz_Store_5", NPChar.name),
						StringFromKey("Beliz_Store_6", pchar),
						StringFromKey("Beliz_Store_7"),
						StringFromKey("Beliz_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
