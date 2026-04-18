void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (CheckAttribute(npchar, "quest.takeMap")) Log_TestInfo("Статус: " + npchar.quest.takeMap);

	switch (Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = StringFromKey("Trader_1", pchar);
					link.l1 = StringFromKey("Trader_2", GetFullName(pchar));
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = StringFromKey("Trader_3", pchar);
					link.l1 = StringFromKey("Trader_4", GetFullName(pchar));
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("Trader_5");
				link.l1 = StringFromKey("Trader_6");
				link.l1.go = "Trade_exit";
				//квест получения карты -->
				if (!CheckAttribute(npchar, "quest.takeMap") && GetCharacterItem(pchar, "map_LSC") <= 0)
				{
					link.l2 = StringFromKey("Trader_7", pchar);
					link.l2.go = "tekeMap_begin";
				}
				if (CheckAttribute(npchar, "quest.takeMap") && npchar.quest.takeMap == "mapIsToken" && !CheckCharacterItem(pchar, "map_LSC"))
				{
					link.l2 = StringFromKey("Trader_8");
					link.l2.go = "tekeMap_off";
				}
				if (CheckAttribute(npchar, "quest.takeMap") && npchar.quest.takeMap == "discount")
				{
					link.l2 = StringFromKey("Trader_9", npchar.quest.takeMap.name);
					link.l2.go = "tekeMap_on";
				}
				//<-- квест получения карты
				link.l3 = StringFromKey("Trader_10");
				link.l3.go = "exit";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && !CheckAttribute(pchar, "questTemp.LSC.goods.trader"))
				{
					link.l8 = StringFromKey("Trader_11");
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(pchar, "questTemp.LSC.goods.trader") && sti(pchar.questTemp.LSC.goods.trader))
				{
					link.l8 = StringFromKey("Trader_12");
					link.l8.go = "SeekGoodsOk";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					link.l8 = StringFromKey("Trader_13");
					link.l8.go = "SeekCrew";
				}
				//бутылка для Бойла
				if (CheckAttribute(npchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toTomasBoil" && !CheckAttribute(npchar, "quest.bottleToTomasBoil"))
				{
					link.l6 = StringFromKey("Trader_14");
					link.l6.go = "bottleToTomasBoil";
				}
				//поиск свечек для падре
				if (CheckAttribute(pchar, "questTemp.LSC.takeCandles") && pchar.questTemp.LSC.takeCandles == "seek")
				{
					link.l7 = StringFromKey("Trader_15");
					link.l7.go = "SeekCandles";
				}
				NextDiag.TempNode = "First time";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "FS_1":
			dialog.text = StringFromKey("Trader_16", GetFullName(npchar));
			link.l1 = StringFromKey("Trader_17");
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = StringFromKey("Trader_18", GetFullName(npchar));
			link.l1 = StringFromKey("Trader_19");
			link.l1.go = "exit";
		break;

		case "Trade_exit":
			if (CheckNPCQuestDate(npchar, "Item_date") || npchar.quest.takeMap == "changePrice")
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar);
		break;

		//обнаружение ГГ в сундуках
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Man_FackYou":
			dialog.text = StringFromKey("Trader_23", LinkRandPhrase(
						StringFromKey("Trader_20"),
						StringFromKey("Trader_21", pchar),
						StringFromKey("Trader_22", pchar)));
			link.l1 = StringFromKey("Trader_27", LinkRandPhrase(
						StringFromKey("Trader_24"),
						StringFromKey("Trader_25"),
						StringFromKey("Trader_26")));
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("Trader_28");
			link.l1 = StringFromKey("Trader_29");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("Trader_33", LinkRandPhrase(
						StringFromKey("Trader_30", pchar),
						StringFromKey("Trader_31"),
						StringFromKey("Trader_32", pchar)));
			link.l1 = StringFromKey("Trader_37", LinkRandPhrase(
						StringFromKey("Trader_34"),
						StringFromKey("Trader_35"),
						StringFromKey("Trader_36")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("Trader_38", npchar);
				link.l1 = StringFromKey("Trader_42", LinkRandPhrase(
							StringFromKey("Trader_39"),
							StringFromKey("Trader_40"),
							StringFromKey("Trader_41")));
			}
			else
			{
				dialog.text = StringFromKey("Trader_43", npchar);
				link.l1 = StringFromKey("Trader_46", RandPhraseSimple(
							StringFromKey("Trader_44", pchar),
							StringFromKey("Trader_45")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = StringFromKey("Trader_47");
			link.l1 = StringFromKey("Trader_48", pchar);
			link.l1.go = "SeekGoods_1";
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("Trader_49", pchar);
			link.l1 = StringFromKey("Trader_50");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = StringFromKey("Trader_51");
			link.l1 = StringFromKey("Trader_52");
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = StringFromKey("Trader_53");
			link.l1 = StringFromKey("Trader_54");
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = StringFromKey("Trader_55");
			if (sti(pchar.money) >= 40000)
			{
				link.l1 = StringFromKey("Trader_56", pchar);
				link.l1.go = "SeekGoods_5";
			}
			else
			{
				link.l1 = StringFromKey("Trader_57");
				link.l1.go = "SeekGoods_notMoney";
			}
		break;
		case "SeekGoods_notMoney":
			dialog.text = StringFromKey("Trader_58");
			link.l1 = StringFromKey("Trader_59");
			link.l1.go = "exit";
			pchar.questTemp.LSC.goods.trader = true;
		break;

		case "SeekGoods_5":
			dialog.text = StringFromKey("Trader_60");
			link.l1 = StringFromKey("Trader_61");
			link.l1.go = "SeekGoods_6";
		break;
		case "SeekGoods_6":
			dialog.text = StringFromKey("Trader_62");
			link.l1 = StringFromKey("Trader_63");
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "41");
			AddMoneyToCharacter(pchar, -40000);
			AddCharacterGoods(pchar, GOOD_FOOD, 200);
			AddCharacterGoods(pchar, GOOD_PLANKS, 50);
			AddCharacterGoods(pchar, GOOD_SAILCLOTH, 50);
			pchar.questTemp.LSC.goods.trader = false;
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;

		case "SeekGoodsOk":
			dialog.text = StringFromKey("Trader_64", pchar);
			if (sti(pchar.money) >= 40000)
			{
				link.l1 = StringFromKey("Trader_65", pchar);
				link.l1.go = "SeekGoods_5";
			}
			else
			{
				link.l1 = StringFromKey("Trader_66");
				link.l1.go = "SeekGoods_notMoney";
			}
		break;
		//поиск свечек
		case "SeekCandles":
			dialog.text = StringFromKey("Trader_67"); //10 * 400
			link.l1 = StringFromKey("Trader_68");
			link.l1.go = "SeekCandles_1";
			if (!CheckAttribute(npchar, "freeCandlesFail"))
			{
				link.l2 = StringFromKey("Trader_69");
				link.l2.go = "SeekCandles_2";
			}
			link.l3 = StringFromKey("Trader_70");
			link.l3.go = "exit";
		break;
		case "SeekCandles_1":
			if (sti(pchar.money) >= 25000)
			{
				dialog.text = StringFromKey("Trader_71");
				link.l1 = StringFromKey("Trader_72");
				link.l1.go = "exit";
				AddMoneyToCharacter(pchar, -25000);
				TakeNItems(pchar, "mineral3", 500);
				pchar.questTemp.LSC.takeCandles = "found";
				RemoveLandQuestMark_Main(npchar, "ISS_takeCandles");
			}
			else
			{
				dialog.text = StringFromKey("Trader_73");
				link.l1 = StringFromKey("Trader_74");
				link.l1.go = "exit";
			}
		break;
		case "SeekCandles_2":
			sld = CharacterFromId("PedroHurtado");
			bool checkRob = CheckAttribute(sld, "quest.store") && sld.quest.store == "over"; //если ограбили, то халявы не будет
			//		    if (!checkRob && GetCharacterSPECIAL(pchar, "Charisma") > 7)
			if (!checkRob && PlayerRPGCheck_SPECIAL(SPECIAL_C, 8))
			{
				dialog.text = StringFromKey("Trader_75");
				link.l1 = StringFromKey("Trader_76");
				link.l1.go = "exit";
				TakeNItems(pchar, "mineral3", 400);
				pchar.questTemp.LSC.takeCandles = "found";
				RemoveLandQuestMark_Main(npchar, "ISS_takeCandles");
			}
			else
			{
				npchar.freeCandlesFail = true; //флаг на провал проверки на обаяние
				dialog.text = StringFromKey("Trader_77");
				link.l1 = StringFromKey("Trader_78");
				link.l1.go = "SeekCandles_1";
				link.l2 = StringFromKey("Trader_79");
				link.l2.go = "exit";
			}
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Trader_80"),
						StringFromKey("Trader_81"),
						StringFromKey("Trader_82"),
						StringFromKey("Trader_83", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Trader_84"),
						StringFromKey("Trader_85", pchar),
						StringFromKey("Trader_86"),
						StringFromKey("Trader_87"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("Trader_88");
			link.l1 = StringFromKey("Trader_89");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("Trader_90");
			link.l1 = StringFromKey("Trader_91");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("Trader_92");
			link.l1 = StringFromKey("Trader_93");
			link.l1.go = "exit";
		break;
		//бутылка для Бойла
		case "bottleToTomasBoil":
			dialog.text = StringFromKey("Trader_94");
			link.l1 = StringFromKey("Trader_95");
			link.l1.go = "First time";
			npchar.quest.bottleToTomasBoil = true;
			AddItems(npchar, "potionwine", 1);
			RemoveLandQuestMark_Main(npchar, "TakeVineToPrisoner");
		break;
		//квест получения карты Города
		case "tekeMap_begin":
			dialog.text = StringFromKey("Trader_96");
			link.l1 = StringFromKey("Trader_97");
			link.l1.go = "tekeMap_begin_1";
		break;
		case "tekeMap_begin_1":
			dialog.text = StringFromKey("Trader_98");
			link.l1 = StringFromKey("Trader_99");
			link.l1.go = "tekeMap_begin_2";
		break;
		case "tekeMap_begin_2":
			dialog.text = StringFromKey("Trader_100");
			link.l1 = StringFromKey("Trader_101", pchar);
			link.l1.go = "First time";
			npchar.quest.takeMap = "firstGiveMap";
			AddQuestRecord("FindMapLSC", "3");
		break;
		case "tekeMap_off":
			dialog.text = StringFromKey("Trader_102", pchar);
			link.l1 = StringFromKey("Trader_103");
			link.l1.go = "tekeMap_off_1";
		break;
		case "tekeMap_off_1":
			dialog.text = StringFromKey("Trader_104", pchar);
			link.l1 = StringFromKey("Trader_105");
			link.l1.go = "tekeMap_off_2";
		break;
		case "tekeMap_off_2":
			dialog.text = StringFromKey("Trader_106", pchar);
			link.l1 = StringFromKey("Trader_107");
			link.l1.go = "exit";
			link.l2 = StringFromKey("Trader_108");
			link.l2.go = "exit";
			npchar.quest.takeMap = "notTrade"; //поговорили о том, что не торгуется
			pchar.questTemp.FindMapLSC = "notTrade";
			AddQuestRecord("FindMapLSC", "4");
			LSC_FindMapLSC_AddQuestMarksToWoman();
		break;
		case "tekeMap_on":
			if (CheckAttribute(npchar, "quest.takeMap.checkDate") && npchar.quest.takeMap.checkDate != LastSpeakDate())
			{
				dialog.text = StringFromKey("Trader_109");
				link.l1 = StringFromKey("Trader_110");
				link.l1.go = "tekeMap_on_1";
			}
			else
			{
				dialog.text = StringFromKey("Trader_111", npchar.quest.takeMap.name);
				link.l1 = StringFromKey("Trader_112");
				link.l1.go = "exit";
			}
		break;
		case "tekeMap_on_1":
			dialog.text = StringFromKey("Trader_113");
			link.l1 = StringFromKey("Trader_114");
			link.l1.go = "exit";
			npchar.quest.takeMap = "changePrice"; //снизить цену
			AddQuestRecord("FindMapLSC", "7");
		break;

	}
}
