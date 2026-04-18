// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Maracaibo_Store_1"),
						StringFromKey("Maracaibo_Store_2"),
						StringFromKey("Maracaibo_Store_3"),
						StringFromKey("Maracaibo_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Maracaibo_Store_5", NPChar.name),
						StringFromKey("Maracaibo_Store_6", pchar),
						StringFromKey("Maracaibo_Store_7"),
						StringFromKey("Maracaibo_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
