// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Panama_Store_1"),
						StringFromKey("Panama_Store_2"),
						StringFromKey("Panama_Store_3"),
						StringFromKey("Panama_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Panama_Store_5", NPChar.name),
						StringFromKey("Panama_Store_6", pchar),
						StringFromKey("Panama_Store_7"),
						StringFromKey("Panama_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> проверка на квесты
			if (CheckAttribute(pchar, "questTemp.State.Store"))
			{
				link.l1 = StringFromKey("Panama_Store_9");
				link.l1.go = "Step_S2_1";
			}
		// <== проверка на квесты

		break;
		//*************************** Квест №2 испанки, задание Инквизиции ***************************
		case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Panama_Store_10"),
						StringFromKey("Panama_Store_11", pchar),
						StringFromKey("Panama_Store_12", pchar),
						StringFromKey("Panama_Store_13"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Panama_Store_14"),
						StringFromKey("Panama_Store_15"),
						StringFromKey("Panama_Store_16", pchar),
						StringFromKey("Panama_Store_17", npchar.name), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S2_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_S2_2":
			dialog.text = StringFromKey("Panama_Store_18");
			link.l1 = StringFromKey("Panama_Store_19");
			link.l1.go = "exit";
			AddQuestRecord("Spa_Line_2_Inquisition", "11");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
