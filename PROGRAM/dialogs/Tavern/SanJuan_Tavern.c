// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SanJuan_Tavern_1", GetCityName(npchar.city)),
						StringFromKey("SanJuan_Tavern_2"),
						StringFromKey("SanJuan_Tavern_3"),
						StringFromKey("SanJuan_Tavern_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SanJuan_Tavern_5", NPChar.name),
						StringFromKey("SanJuan_Tavern_6", pchar),
						StringFromKey("SanJuan_Tavern_7"),
						StringFromKey("SanJuan_Tavern_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов. Эдди.
			switch (pchar.questTemp.State)
			{
				case "MorrisWillams_PinnaceNotFound":
					link.l2 = StringFromKey("SanJuan_Tavern_9", pchar);
					link.l2.go = "Step_E6_1";
				break;
			}
		break;
		//---------------- квесты --------------------
		case "Step_E6_1":
			dialog.text = StringFromKey("SanJuan_Tavern_10");
			link.l1 = StringFromKey("SanJuan_Tavern_11");
			link.l1.go = "Step_E6_2";
		break;
		case "Step_E6_2":
			dialog.text = StringFromKey("SanJuan_Tavern_12");
			link.l1 = StringFromKey("SanJuan_Tavern_13");
			link.l1.go = "Step_E6_3";
		break;
		case "Step_E6_3":
			dialog.text = StringFromKey("SanJuan_Tavern_14");
			link.l1 = StringFromKey("SanJuan_Tavern_15");
			link.l1.go = "Step_E6_4";
		break;
		case "Step_E6_4":
			dialog.text = StringFromKey("SanJuan_Tavern_16");
			link.l1 = StringFromKey("SanJuan_Tavern_17");
			link.l1.go = "Step_E6_5";
		break;
		case "Step_E6_5":
			dialog.text = StringFromKey("SanJuan_Tavern_18");
			link.l1 = StringFromKey("SanJuan_Tavern_19", pchar);
			link.l1.go = "Step_E6_6";
		break;
		case "Step_E6_6":
			dialog.text = StringFromKey("SanJuan_Tavern_20");
			link.l1 = StringFromKey("SanJuan_Tavern_21");
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_2PinnaceNotFound";
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
