// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Havana_Store_1"),
						StringFromKey("Havana_Store_2"),
						StringFromKey("Havana_Store_3"),
						StringFromKey("Havana_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Havana_Store_5", NPChar.name),
						StringFromKey("Havana_Store_6", pchar),
						StringFromKey("Havana_Store_7"),
						StringFromKey("Havana_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
