// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortoBello_Tavern_3", RandPhraseSimple(
								StringFromKey("PortoBello_Tavern_1"),
								StringFromKey("PortoBello_Tavern_2", GetAddress_Form(NPChar)))),
						StringFromKey("PortoBello_Tavern_4", GetAddress_Form(NPChar)),
						StringFromKey("PortoBello_Tavern_5"),
						StringFromKey("PortoBello_Tavern_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortoBello_Tavern_9", RandPhraseSimple(
								StringFromKey("PortoBello_Tavern_7", pchar),
								StringFromKey("PortoBello_Tavern_8"))),
						StringFromKey("PortoBello_Tavern_10"),
						StringFromKey("PortoBello_Tavern_11"),
						StringFromKey("PortoBello_Tavern_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.RomanticQuest == "SeekInPortoBello")
			{
				link.l1 = StringFromKey("PortoBello_Tavern_13");
				link.l1.go = "Romantic_1";
			}

			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
			{
				link.l1 = StringFromKey("PortoBello_Tavern_14");
				link.l1.go = "Portobello_rat_1";
			}

			if (CheckAttribute(pchar, "questTemp.mushket2x2_stid") && !CheckCharacterItem(pchar, "mushket2x2"))
			{
				link.l1 = StringFromKey("PortoBello_Tavern_15");
				if (GetQuestPastDayParam("questTemp.mushket2x2_stid") < 11)
				{
					link.l1.go = "Mushket_stid";
				}
				else
				{
					link.l1.go = "Mushket_late";
				}
			}
		break;

		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortoBello_Tavern_16"),
						StringFromKey("PortoBello_Tavern_17", pchar),
						StringFromKey("PortoBello_Tavern_18", pchar),
						StringFromKey("PortoBello_Tavern_19"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortoBello_Tavern_20"),
						StringFromKey("PortoBello_Tavern_21"),
						StringFromKey("PortoBello_Tavern_22", pchar),
						StringFromKey("PortoBello_Tavern_23", npchar.name), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";

			RemoveLandQuestmark_Main(npchar, "Slavetrader");
		break;

		case "Mushket_stid":
			dialog.text = StringFromKey("PortoBello_Tavern_24");
			link.l1 = StringFromKey("PortoBello_Tavern_25");
			link.l1.go = "Mushket_stid_1";
			DeleteAttribute(pchar, "questTemp.mushket2x2_stid");

			RemoveLandQuestMark_Main(npchar, "SeekDoubleMushket");
		break;

		case "Mushket_stid_1":
			dialog.text = StringFromKey("PortoBello_Tavern_26");
			link.l1 = StringFromKey("PortoBello_Tavern_27");
			link.l1.go = "Mushket_stid_2";
		break;

		case "Mushket_stid_2":
			dialog.text = StringFromKey("PortoBello_Tavern_28", pchar);
			link.l1 = StringFromKey("PortoBello_Tavern_29");
			link.l1.go = "Mushket_stid_3";
		break;

		case "Mushket_stid_3":
			dialog.text = StringFromKey("PortoBello_Tavern_30", pchar);
			link.l1 = StringFromKey("PortoBello_Tavern_31");
			link.l1.go = "Mushket_stid_4";
		break;

		case "Mushket_stid_4":
			dialog.text = StringFromKey("PortoBello_Tavern_32");
			if (makeint(Pchar.money) >= 100000)
			{
				link.l1 = StringFromKey("PortoBello_Tavern_33");
				link.l1.go = "Mushket_stid_nopay";
				link.l2 = StringFromKey("PortoBello_Tavern_34");
				link.l2.go = "Mushket_stid_paymoney";
			}
			link.l3 = StringFromKey("PortoBello_Tavern_35");
			link.l3.go = "Mushket_stid_nomoney";
		break;

		case "Mushket_stid_nopay":
			dialog.text = StringFromKey("PortoBello_Tavern_36");
			link.l1 = StringFromKey("PortoBello_Tavern_37");
			link.l1.go = "Mushket_stid_paymoney";
			link.l2 = StringFromKey("PortoBello_Tavern_38", pchar);
			link.l2.go = "Mushket_stid_goaway";
		break;

		case "Mushket_stid_nomoney":
			dialog.text = StringFromKey("PortoBello_Tavern_39");
			link.l1 = StringFromKey("PortoBello_Tavern_40");
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "5");
			DeleteAttribute(pchar, "questTemp.Mushket.Shore");
		break;

		case "Mushket_stid_goaway":
			dialog.text = StringFromKey("PortoBello_Tavern_41");
			link.l1 = StringFromKey("PortoBello_Tavern_42");
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "6");
			AddQuestUserData("SeekDoubleMushket", "sSex", GetSexPhrase("ся", "ась"));
			DeleteAttribute(pchar, "questTemp.Mushket.Shore");
		break;

		case "Mushket_stid_paymoney":
			AddMoneyToCharacter(Pchar, -100000);
			dialog.text = StringFromKey("PortoBello_Tavern_43", pchar, XI_ConvertString(pchar.questTemp.Mushket.Shore));
			link.l1 = StringFromKey("PortoBello_Tavern_44");
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "4");
			AddQuestUserData("SeekDoubleMushket", "sShore", XI_ConvertString(pchar.questTemp.Mushket.Shore));
			DeleteAttribute(pchar, "questTemp.Mushket.Shore");
		break;

		case "Mushket_late":
			dialog.text = StringFromKey("PortoBello_Tavern_45");
			link.l1 = StringFromKey("PortoBello_Tavern_46");
			link.l1.go = "Mushket_late_1";
			DeleteAttribute(pchar, "questTemp.mushket2x2_stid");

			RemoveLandQuestMark_Main(npchar, "SeekDoubleMushket");
		break;

		case "Mushket_late_1":
			dialog.text = StringFromKey("PortoBello_Tavern_47", pchar);
			link.l1 = StringFromKey("PortoBello_Tavern_48");
			link.l1.go = "exit";
			AddQuestRecord("SeekDoubleMushket", "7");
			AddQuestUserData("SeekDoubleMushket", "sSex", GetSexPhrase("ся", "ась"));
		break;

		case "Romantic_1":
			dialog.text = StringFromKey("PortoBello_Tavern_49");
			link.l1 = StringFromKey("PortoBello_Tavern_50");
			link.l1.go = "Romantic_2";
		break;
		case "Romantic_2":
			dialog.text = StringFromKey("PortoBello_Tavern_51", GetAddress_Form(pchar));
			link.l1 = StringFromKey("PortoBello_Tavern_52");
			link.l1.go = "exit";
			pchar.RomanticQuest = "ToRositaInBeliz";
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
