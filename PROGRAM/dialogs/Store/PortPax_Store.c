// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortPax_Store_1"),
						StringFromKey("PortPax_Store_2"),
						StringFromKey("PortPax_Store_3"),
						StringFromKey("PortPax_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortPax_Store_5", NPChar.name),
						StringFromKey("PortPax_Store_6", pchar),
						StringFromKey("PortPax_Store_7"),
						StringFromKey("PortPax_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Azzy.GiveRum"))
			{
				Link.l1 = StringFromKey("PortPax_Store_9");
				Link.l1.go = "Step_Az6";
				if (pchar.questTemp.Azzy.GiveRum == "OK")
				{
					Link.l1 = StringFromKey("PortPax_Store_10");
					Link.l1.go = "Step_Az8";
				}
			}
			if (pchar.questTemp.Azzy == "HowToKnowAzzy")
			{
				Link.l2 = StringFromKey("PortPax_Store_11");
				Link.l2.go = "Step_Az10";
			}
		break;
		//============================== Квест Аззи ===============================
		case "Step_Az6":
			dialog.text = StringFromKey("PortPax_Store_12");
			link.l1 = StringFromKey("PortPax_Store_13");
			link.l1.go = "Step_Az7";
		break;

		case "Step_Az7":
			dialog.text = StringFromKey("PortPax_Store_14");
			link.l1 = StringFromKey("PortPax_Store_15");
			link.l1.go = "Step_Az8";
			pchar.questTemp.Azzy.GiveRum = "OK";
			RemoveLandQuestmark_Main(npchar, "Azzy_Wishes");
		break;

		case "Step_Az8":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortPax_Store_16"),
						StringFromKey("PortPax_Store_17", pchar),
						StringFromKey("PortPax_Store_18", pchar),
						StringFromKey("PortPax_Store_19"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortPax_Store_20"),
						StringFromKey("PortPax_Store_21", pchar),
						StringFromKey("PortPax_Store_22"),
						StringFromKey("PortPax_Store_23"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_Az9", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;

		case "Step_Az9":
			dialog.text = StringFromKey("PortPax_Store_24");
			link.l1 = StringFromKey("PortPax_Store_25");
			link.l1.go = "exit";
			AddCharacterGoods(Pchar, GOOD_RUM, 300);
			AddLandQuestmark_Gen_WithCondition(npchar, "Azzy_Wishes", "AzzyWishes_Rum_QuestMarkCondition");
		break;

		case "Step_Az10":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortPax_Store_26"),
						StringFromKey("PortPax_Store_27"),
						StringFromKey("PortPax_Store_28"),
						StringFromKey("PortPax_Store_29"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortPax_Store_30"),
						StringFromKey("PortPax_Store_31"),
						StringFromKey("PortPax_Store_32"),
						StringFromKey("PortPax_Store_33"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_Az11", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;

		case "Step_Az11":
			dialog.text = StringFromKey("PortPax_Store_34");
			link.l1 = StringFromKey("PortPax_Store_35");
			link.l1.go = "Step_Az12";
		break;

		case "Step_Az12":
			dialog.text = StringFromKey("PortPax_Store_36", pchar);
			link.l1 = StringFromKey("PortPax_Store_37");
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
