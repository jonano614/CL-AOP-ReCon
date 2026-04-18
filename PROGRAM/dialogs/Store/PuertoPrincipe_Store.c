// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PuertoPrincipe_Store_1"),
						StringFromKey("PuertoPrincipe_Store_2"),
						StringFromKey("PuertoPrincipe_Store_3"),
						StringFromKey("PuertoPrincipe_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PuertoPrincipe_Store_5", NPChar.name),
						StringFromKey("PuertoPrincipe_Store_6", pchar),
						StringFromKey("PuertoPrincipe_Store_7"),
						StringFromKey("PuertoPrincipe_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.BlueBird == "toPuertoPrincipe")
			{
				link.l1 = StringFromKey("PuertoPrincipe_Store_9");
				link.l1.go = "BlueBird_1";
			}
			if (CheckAttribute(npchar, "quest.MalcolmTobacco"))
			{
				link.l1 = StringFromKey("PuertoPrincipe_Store_10", NPChar.name);
				link.l1.go = "MalcolmTobacco_1";
			}
		break;
		case "BlueBird_1":
		//			if (isBadReputation(pchar, 5))
			if (PlayerRPGCheck_BadReputation(5, true))
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("PuertoPrincipe_Store_11"),
							StringFromKey("PuertoPrincipe_Store_12"),
							StringFromKey("PuertoPrincipe_Store_13"),
							StringFromKey("PuertoPrincipe_Store_14"), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("PuertoPrincipe_Store_15"),
							StringFromKey("PuertoPrincipe_Store_16"),
							StringFromKey("PuertoPrincipe_Store_17"),
							StringFromKey("PuertoPrincipe_Store_18"), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("BlueBird_close", "", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = StringFromKey("PuertoPrincipe_Store_19");
				link.l1 = StringFromKey("PuertoPrincipe_Store_20");
				link.l1.go = "BlueBird_2";
			}
		break;

		case "BlueBird_close":
			dialog.text = StringFromKey("PuertoPrincipe_Store_21");
			link.l1 = StringFromKey("PuertoPrincipe_Store_22");
			link.l1.go = "exit";
		break;

		case "BlueBird_2":
			dialog.text = StringFromKey("PuertoPrincipe_Store_23");
			link.l1 = StringFromKey("PuertoPrincipe_Store_24");
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = StringFromKey("PuertoPrincipe_Store_25", pchar);
			link.l1 = StringFromKey("PuertoPrincipe_Store_26");
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = StringFromKey("PuertoPrincipe_Store_27");
			link.l1 = StringFromKey("PuertoPrincipe_Store_28");
			link.l1.go = "BlueBird_5";
		break;
		case "BlueBird_5":
			dialog.text = StringFromKey("PuertoPrincipe_Store_29");
			link.l1 = StringFromKey("PuertoPrincipe_Store_30");
			link.l1.go = "BlueBird_6";
		break;
		case "BlueBird_6":
			dialog.text = StringFromKey("PuertoPrincipe_Store_31");
			link.l1 = StringFromKey("PuertoPrincipe_Store_32");
			link.l1.go = "BlueBird_7";
		break;
		case "BlueBird_7":
			dialog.text = StringFromKey("PuertoPrincipe_Store_33");
			link.l1 = StringFromKey("PuertoPrincipe_Store_34");
			link.l1.go = "BlueBird_8";
		break;
		case "BlueBird_8":
			dialog.text = StringFromKey("PuertoPrincipe_Store_35");
			link.l1 = StringFromKey("PuertoPrincipe_Store_36", pchar);
			link.l1.go = "BlueBird_9";
		break;
		case "BlueBird_9":
			dialog.text = StringFromKey("PuertoPrincipe_Store_37", pchar);
			link.l1 = StringFromKey("PuertoPrincipe_Store_38");
			link.l1.go = "exit";
			pchar.questTemp.BlueBird = "toSeekBermudes";
			AddQuestRecord("Xebeca_BlueBird", "4");
			RemoveLandQuestMark_Main(npchar, "Xebeca_BlueBird");
			AddLandQuestMark_Main(CharacterFromID("Pirates_shipyarder"), "Xebeca_BlueBird");
		break;

		//квест Табак Малькольма
		case "MalcolmTobacco_1":
			ref Colony = GetColonyByIndex(FindColony("PuertoPrincipe"));
			ref trader = &stores[sti(Colony.StoreNum)];
			int iStoreBuy = GetStoreGoodsPrice(trader, GOOD_TOBACCO, PRICE_TYPE_BUY, pchar, 1);
			dialog.text = StringFromKey("PuertoPrincipe_Store_39", FindMoneyString(iStoreBuy));
			link.l1 = StringFromKey("PuertoPrincipe_Store_40");
			link.l1.go = "MalcolmTobacco_2";
		break;
		case "MalcolmTobacco_2":
			pchar.quest.WaitMalcolm.win_condition.l1 = "location";
			pchar.quest.WaitMalcolm.win_condition.l1.location = "PuertoPrincipe_town";
			pchar.quest.WaitMalcolm.function = "MalcolmGoToPchar";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "MalcolmTobacco_GoFromStore", 1);
			DeleteAttribute(npchar, "quest");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			RemoveLandQuestMark_Main(npchar, "MalcolmsTobacco");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
