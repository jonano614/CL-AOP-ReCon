// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Providencia_Store_1"),
						StringFromKey("Providencia_Store_2"),
						StringFromKey("Providencia_Store_3"),
						StringFromKey("Providencia_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Providencia_Store_5", NPChar.name),
						StringFromKey("Providencia_Store_6", pchar),
						StringFromKey("Providencia_Store_7"),
						StringFromKey("Providencia_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
