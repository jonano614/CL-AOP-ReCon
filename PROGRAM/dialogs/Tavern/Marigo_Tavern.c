// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Marigo_Tavern_1", GetCityName(npchar.city)),
						StringFromKey("Marigo_Tavern_2"),
						StringFromKey("Marigo_Tavern_3"),
						StringFromKey("Marigo_Tavern_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Marigo_Tavern_5", NPChar.name),
						StringFromKey("Marigo_Tavern_6", pchar),
						StringFromKey("Marigo_Tavern_7"),
						StringFromKey("Marigo_Tavern_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			switch (pchar.questTemp.State)
			{
				case "SeekChumakeiro_ToAaronHouse": //Голландская линейка, квест №1. поиски Чумакейро.
					link.l1 = HeroStringReactionRepeat(
								StringFromKey("Marigo_Tavern_9"),
								StringFromKey("Marigo_Tavern_10", pchar),
								StringFromKey("Marigo_Tavern_11"),
								StringFromKey("Marigo_Tavern_12"), npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("Step_H1_1", "", "", "", npchar, Dialog.CurrentNode);
				break;

			}
		// <== Проверяем поле состояния квестов.
		break;
		//============ Голландская линейка, квест №1. поиски Чумакейро.
		case "Step_H1_1":
			dialog.text = StringFromKey("Marigo_Tavern_13");
			link.l1 = StringFromKey("Marigo_Tavern_14");
			link.l1.go = "Step_H1_2";
		break;
		case "Step_H1_2":
			dialog.text = StringFromKey("Marigo_Tavern_15", npchar.name);
			link.l1 = StringFromKey("Marigo_Tavern_16");
			link.l1.go = "Step_H1_3";
		break;
		case "Step_H1_3":
			dialog.text = StringFromKey("Marigo_Tavern_17");
			link.l1 = StringFromKey("Marigo_Tavern_18");
			link.l1.go = "Step_H1_4";
		break;
		case "Step_H1_4":
			dialog.text = StringFromKey("Marigo_Tavern_19");
			link.l1 = StringFromKey("Marigo_Tavern_20");
			link.l1.go = "Step_H1_5";
		break;
		case "Step_H1_5":
			dialog.text = StringFromKey("Marigo_Tavern_21");
			link.l1 = StringFromKey("Marigo_Tavern_22");
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
