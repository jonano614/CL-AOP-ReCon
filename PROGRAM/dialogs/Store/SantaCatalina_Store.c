// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SantaCatalina_Store_1"),
						StringFromKey("SantaCatalina_Store_2"),
						StringFromKey("SantaCatalina_Store_3"),
						StringFromKey("SantaCatalina_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SantaCatalina_Store_5", NPChar.name),
						StringFromKey("SantaCatalina_Store_6", pchar),
						StringFromKey("SantaCatalina_Store_7"),
						StringFromKey("SantaCatalina_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
