// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Cartahena_Store_1"),
						StringFromKey("Cartahena_Store_2"),
						StringFromKey("Cartahena_Store_3"),
						StringFromKey("Cartahena_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Cartahena_Store_5", NPChar.name),
						StringFromKey("Cartahena_Store_6", pchar),
						StringFromKey("Cartahena_Store_7"),
						StringFromKey("Cartahena_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
