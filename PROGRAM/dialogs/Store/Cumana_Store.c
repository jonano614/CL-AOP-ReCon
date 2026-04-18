// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Cumana_Store_1"),
						StringFromKey("Cumana_Store_2"),
						StringFromKey("Cumana_Store_3"),
						StringFromKey("Cumana_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Cumana_Store_5", NPChar.name),
						StringFromKey("Cumana_Store_6", pchar),
						StringFromKey("Cumana_Store_7"),
						StringFromKey("Cumana_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
