// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("LaVega_Tavern_1", GetCityName(npchar.city)),
						StringFromKey("LaVega_Tavern_2"),
						StringFromKey("LaVega_Tavern_3"),
						StringFromKey("LaVega_Tavern_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("LaVega_Tavern_5", NPChar.name),
						StringFromKey("LaVega_Tavern_6", pchar),
						StringFromKey("LaVega_Tavern_7"),
						StringFromKey("LaVega_Tavern_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//пиратка, квест №7
			if (pchar.questTemp.piratesLine == "Soukins_toLaVega")
			{
				link.l1 = StringFromKey("LaVega_Tavern_9");
				link.l1.go = "PL_Q7_1";
			}
		break;
		case "PL_Q7_1":
			dialog.text = StringFromKey("LaVega_Tavern_10");
			link.l1 = StringFromKey("LaVega_Tavern_11");
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "Soukins_toLaVegaSea";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			AddQuestRecord("Pir_Line_7_Soukins", "2");
			pchar.quest.PQ7_FriendLinney.win_condition.l1 = "location";
			pchar.quest.PQ7_FriendLinney.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PQ7_FriendLinney.function = "PQ7_FriendLinney";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
