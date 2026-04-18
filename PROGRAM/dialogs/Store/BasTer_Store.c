// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("BasTer_Store_1"),
						StringFromKey("BasTer_Store_2"),
						StringFromKey("BasTer_Store_3"),
						StringFromKey("BasTer_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("BasTer_Store_5", NPChar.name),
						StringFromKey("BasTer_Store_6", pchar),
						StringFromKey("BasTer_Store_7"),
						StringFromKey("BasTer_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
