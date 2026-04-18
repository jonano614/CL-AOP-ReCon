// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Caracas_Store_1"),
						StringFromKey("Caracas_Store_2"),
						StringFromKey("Caracas_Store_3"),
						StringFromKey("Caracas_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Caracas_Store_5", NPChar.name),
						StringFromKey("Caracas_Store_6", pchar),
						StringFromKey("Caracas_Store_7"),
						StringFromKey("Caracas_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
