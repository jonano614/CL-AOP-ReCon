// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Cumana_Tavern_1", GetCityName(npchar.city)),
						StringFromKey("Cumana_Tavern_2"),
						StringFromKey("Cumana_Tavern_3"),
						StringFromKey("Cumana_Tavern_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Cumana_Tavern_5", NPChar.name),
						StringFromKey("Cumana_Tavern_6", pchar),
						StringFromKey("Cumana_Tavern_7"),
						StringFromKey("Cumana_Tavern_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "RomanticQuest.ShipToCumana"))
			{
				link.l1 = StringFromKey("Cumana_Tavern_9");
				Link.l1.go = "RomanticQuest_1";
			}
			if (CheckAttribute(pchar, "RomanticQuest.ShipToCumanaTavenrn"))
			{
				link.l1 = StringFromKey("Cumana_Tavern_10");
				Link.l1.go = "RomanticQuest_2";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toCumana")
			{
				link.l1 = StringFromKey("Cumana_Tavern_11");
				link.l1.go = "PL_Q3_1";
			}
		break;

		case "RomanticQuest_1":
			dialog.text = StringFromKey("Cumana_Tavern_12");
			link.l1 = StringFromKey("Cumana_Tavern_13");
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;
		case "RomanticQuest_2":
			dialog.text = StringFromKey("Cumana_Tavern_14");
			link.l1 = StringFromKey("Cumana_Tavern_15");
			link.l1.go = "exit";
			DeleteAttribute(pchar, "RomanticQuest.ShipToCumanaTavenrn");
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;

		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Cumana_Tavern_16"),
						StringFromKey("Cumana_Tavern_17"),
						StringFromKey("Cumana_Tavern_18"),
						StringFromKey("Cumana_Tavern_19"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Cumana_Tavern_20"),
						StringFromKey("Cumana_Tavern_21"),
						StringFromKey("Cumana_Tavern_22"),
						StringFromKey("Cumana_Tavern_23", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
