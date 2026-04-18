// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Panama_Tavern_1", GetCityName(npchar.city)),
						StringFromKey("Panama_Tavern_2"),
						StringFromKey("Panama_Tavern_3"),
						StringFromKey("Panama_Tavern_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Panama_Tavern_5", NPChar.name),
						StringFromKey("Panama_Tavern_6", pchar),
						StringFromKey("Panama_Tavern_7"),
						StringFromKey("Panama_Tavern_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> проверка на квесты
			if (CheckAttribute(pchar, "questTemp.State.Store"))
			{
				link.l1 = StringFromKey("Panama_Tavern_9");
				link.l1.go = "Step_S2_1";
			}
			if (pchar.questTemp.Slavetrader == "FindRatPanama")
			{
				link.l1 = StringFromKey("Panama_Tavern_10");
				link.l1.go = "Panama_rat_1";
			}
		// <== проверка на квесты
		break;
		//*************************** Квест №2 испанки, задание Инквизиции ***************************
		case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Panama_Tavern_11"),
						StringFromKey("Panama_Tavern_12", pchar),
						StringFromKey("Panama_Tavern_13", pchar),
						StringFromKey("Panama_Tavern_14"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Panama_Tavern_15"),
						StringFromKey("Panama_Tavern_16"),
						StringFromKey("Panama_Tavern_17", pchar),
						StringFromKey("Panama_Tavern_18", npchar.name), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		//-->работорговец
		case "Panama_rat_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Panama_Tavern_19"),
						StringFromKey("Panama_Tavern_20", pchar),
						StringFromKey("Panama_Tavern_21", pchar),
						StringFromKey("Panama_Tavern_22"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Panama_Tavern_23"),
						StringFromKey("Panama_Tavern_24"),
						StringFromKey("Panama_Tavern_25", pchar),
						StringFromKey("Panama_Tavern_26", npchar.name), npchar, Dialog.CurrentNode);
			link.l1.go = "Panama_rat_2";
		break;

		case "Panama_rat_2":
			dialog.text = StringFromKey("Panama_Tavern_27");
			link.l1 = StringFromKey("Panama_Tavern_28");
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello";
			AddQuestRecord("Slavetrader", "21_1");
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			AddLandQuestmark_Main(CharacterFromID("PortoBello_tavernkeeper"), "Slavetrader");
			AddLandQuestmark_Main(CharacterFromID("PortoBello_shipyarder"), "Slavetrader");
		break;
		//<--работорговец
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
