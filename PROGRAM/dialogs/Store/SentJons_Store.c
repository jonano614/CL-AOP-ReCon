// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SentJons_Store_1"),
						StringFromKey("SentJons_Store_2"),
						StringFromKey("SentJons_Store_3"),
						StringFromKey("SentJons_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SentJons_Store_5", NPChar.name),
						StringFromKey("SentJons_Store_6", pchar),
						StringFromKey("SentJons_Store_7"),
						StringFromKey("SentJons_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
