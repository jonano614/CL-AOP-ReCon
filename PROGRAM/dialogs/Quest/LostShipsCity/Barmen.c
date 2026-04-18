#include "DIALOGS\Rumours\Simple_rumors.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;

	switch (Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = StringFromKey("Barmen_1", pchar);
				link.l1 = StringFromKey("Barmen_2");
				link.l1.go = "exit";
				break;
			}

			if (NPChar.quest.meeting == "0" && pchar.questTemp.LSC != "toSeekCrewInTavern")
			{
				NPChar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = StringFromKey("Barmen_3", pchar, GetFullName(npchar));
					link.l1 = StringFromKey("Barmen_4", pchar, GetFullName(pchar));
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.Text = StringFromKey("Barmen_5", GetFullName(npchar));
					Link.l1 = StringFromKey("Barmen_6", npchar.name, GetFullName(pchar));
					Link.l1.go = "First time";
				}
			}
			else
			{
				//базар в винном погребе
				if (pchar.questTemp.LSC == "toWineCellarGone" && npchar.location.locator == "stay1")
				{
					dialog.Text = StringFromKey("Barmen_7");
					link.l4 = StringFromKey("Barmen_8");
					link.l4.go = "TizerCellar";
					PChar.quest.LSC_returnBarmen.over = "yes"; //снимаем таймер на опоздание, разговор состоялся
					break;
				}
				//после завала Хилла Брюннера
				if (pchar.questTemp.LSC == "barmenIsDead" && !CheckAttribute(npchar, "quest.HillNB_1"))
				{
					dialog.Text = StringFromKey("Barmen_9");
					link.l4 = StringFromKey("Barmen_10");
					link.l4.go = "NB_1";
					pchar.questTemp.LSC = "barmenIsDeadYouKnow";
					break;
				}
				if (pchar.questTemp.LSC == "barmenIsDeadYouKnow" || pchar.questTemp.LSC == "toAdmiralBarmenDead")
				{
					if (!CheckAttribute(npchar, "quest.HillNBB_1"))
					{
						dialog.Text = StringFromKey("Barmen_11");
						link.l4 = StringFromKey("Barmen_12");
						link.l4.go = "NBB_1";
						break;
					}
				}
				//убийство Армо
				sld = characterFromId("LSCwaitress");
				if (sld.name != FindPersonalName("LSCwaitress_name") && !CheckAttribute(npchar, "quest.Armo"))
				{
					dialog.Text = StringFromKey("Barmen_13");
					link.l4 = StringFromKey("Barmen_14");
					link.l4.go = "ADied_1";
					npchar.quest.Armo = true;
					break;
				}
				//==> штатый диалог
				dialog.Text = StringFromKey("Barmen_18", LinkRandPhrase(
							StringFromKey("Barmen_15", GetAddress_Form(NPChar), PChar.name, TimeGreeting()),
							StringFromKey("Barmen_16", pchar),
							StringFromKey("Barmen_17", pchar)));
				Link.l1 = StringFromKey("Barmen_19");
				Link.l1.go = "int_quests";
				link.l2 = StringFromKey("Barmen_20");
				link.l2.go = "room";
				link.l3 = StringFromKey("Barmen_24", LinkRandPhrase(
							StringFromKey("Barmen_21"),
							StringFromKey("Barmen_22"),
							StringFromKey("Barmen_23", pchar)));
				link.l3.go = "rumours_LSC";
				Link.l4 = StringFromKey("Barmen_25", NPChar.name);
				Link.l4.go = "exit";
				//==>> квесты
				if (pchar.questTemp.LSC == "AfterAdmiral" && GetQuestPastDayParam("questTemp.LSC") > 1 && !CheckActiveQuest("ISS_takeStoreMoney") && !CheckAttribute(pchar, "questTemp.LSC.takeStoreMoney"))
				{
					link.l4 = StringFromKey("Barmen_26");
					link.l4.go = "takeStoreMoney";
				}
				if (pchar.questTemp.LSC == "AfterAdmiral" && IsLSCQuestsProgressCompleted())
				{
					link.l4 = StringFromKey("Barmen_27");
					link.l4.go = "Tizer";
				}
				if (pchar.questTemp.LSC == "toWineCellarLate")
				{
					link.l4 = StringFromKey("Barmen_28", pchar);
					link.l4.go = "TizerCellarLate";
				}
				if (pchar.questTemp.LSC == "toDiffindoor" && CheckCharacterItem(pchar, "letter_LSC_2"))
				{
					link.l4 = StringFromKey("Barmen_29", pchar);
					link.l4.go = "TizerCellarOk_1";
				}
				if (pchar.questTemp.LSC == "afterFightInProtector")
				{
					link.l4 = StringFromKey("Barmen_30");
					link.l4.go = "AfterProtector_1";
				}
				if (pchar.questTemp.LSC == "toAdmNarvalRing" && CheckCharacterItem(pchar, "RingNarval"))
				{
					link.l4 = StringFromKey("Barmen_31", pchar);
					link.l4.go = "NarvalRing_1";
				}
				if (pchar.questTemp.LSC == "toTavernNarvalDestroyed")
				{
					link.l4 = StringFromKey("Barmen_32");
					link.l4.go = "AfterNarvalDesrt_1";
				}
				//базар-вокзал в подсобке
				if (pchar.questTemp.LSC == "waitInterception")
				{
					link.l4 = StringFromKey("Barmen_33");
					if (CheckAttribute(npchar, "quest.doneRing") && CheckAttribute(npchar, "quest.startRing"))
					{
						if (GetHour() < 20) link.l4.go = "Interception";
						else link.l4.go = "InterceptionNext";
					}
					else if (GetQuestPastDayParam("questTemp.LSC") > 2)
					{
						if (GetHour() < 20) link.l4.go = "Interception";
						else link.l4.go = "InterceptionNext";
					}
					else
					{
						if (CheckAttribute(npchar, "quest.startRing")) link.l4.go = "WaitRing";
						else link.l4.go = "Result";
					}
				}
				//Санта-Люсия
				if (!CheckAttribute(npchar, "quest.startRing") && pchar.questTemp.LSC == "waitInterception" && GetQuestPastDayParam("questTemp.LSC") < 2)
				{
					link.l4 = StringFromKey("Barmen_34");
					link.l4.go = "StartRing";
				}
				// --> пей до дна
				if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "fail" && npchar.model != "barmen_2")
				{
					dialog.text = StringFromKey("Barmen_35", pchar.name);
					link.l1 = StringFromKey("Barmen_36", pchar);
					link.l1.go = "drunk_fail";
					break;
				}
				if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "win")
				{
					if (npchar.model == "barmen_2")
					{
						dialog.text = StringFromKey("Barmen_37");
						link.l1 = StringFromKey("Barmen_38", pchar);
					}
					else
					{
						dialog.text = StringFromKey("Barmen_39", pchar, pchar.name);
						link.l1 = StringFromKey("Barmen_40");
					}
					link.l1.go = "drunk_win";
					break;
				}
				// <--
				if (pchar.questTemp.LSC == "InterceptionLate")
				{
					link.l4 = StringFromKey("Barmen_41", pchar);
					link.l4.go = "InterceptionLate";
				}
				if (pchar.questTemp.LSC == "InterceptionYouSeen")
				{
					link.l4 = StringFromKey("Barmen_42", pchar);
					link.l4.go = "InterceptionYouSeen";
				}
				if (pchar.questTemp.LSC == "waitInterceptionResult")
				{
					link.l4 = StringFromKey("Barmen_43");
					link.l4.go = "Result";
					if (!CheckAttribute(npchar, "quest.drink")) link.l4.go = "startDrink";
				}
				if (pchar.questTemp.LSC == "InterceptionOk")
				{
					link.l4 = StringFromKey("Barmen_44", pchar);
					link.l4.go = "InterceptionOk";
				}
				//поиск грузчика на корвет
				if (pchar.questTemp.LSC == "toSeekStevedore")
				{
					link.l8 = StringFromKey("Barmen_45");
					link.l8.go = "SeekStevedore";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = StringFromKey("Barmen_46");
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (!CheckAttribute(npchar, "toSeekCrewInTavern") && pchar.questTemp.LSC == "toSeekCrewInTavern")
						dialog.text = StringFromKey("Barmen_47"); //сбор в таверне
					link.l8 = StringFromKey("Barmen_48");
					link.l8.go = "SeekCrew";
				}
			}
		break;

		case "FS_1":
			dialog.text = StringFromKey("Barmen_49", pchar);
			link.l1 = StringFromKey("Barmen_50", pchar);
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = StringFromKey("Barmen_51");
			link.l1 = StringFromKey("Barmen_52");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//крутим время
		case "room":
			if (chrDisableReloadToLocation) //кто-то должен подойти к ГГ.
			{
				dialog.text = StringFromKey("Barmen_53");
				link.l1 = StringFromKey("Barmen_54");
				link.l1.go = "exit";
				break;
			}
			dialog.text = StringFromKey("Barmen_55");
			if (!isDay())
			{
				link.l1 = StringFromKey("Barmen_56");
				link.l1.go = "hall_day_wait";
			}
			else
			{
				link.l1 = StringFromKey("Barmen_57");
				link.l1.go = "hall_night_wait";
				link.l2 = StringFromKey("Barmen_58");
				link.l2.go = "hall_day_wait";
			}
			link.l3 = StringFromKey("Barmen_59", pchar);
			link.l3.go = "exit";
		break;
		case "hall_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_night");
		break;
		case "hall_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_day");
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("Barmen_60", pchar);
			if (!CheckAttribute(NextDiag, NodeName + ".l5"))
			{
				link.l5 = StringFromKey("Barmen_61");
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("Barmen_62");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("Barmen_63", pchar);
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l3"))
			{
				link.l3 = StringFromKey("Barmen_64");
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l4"))
			{
				link.l4 = StringFromKey("Barmen_65");
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l6"))
			{
				link.l6 = StringFromKey("Barmen_66");
				link.l6.go = "ansewer_6";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l7") && pchar.questTemp.LSC == "AdmiralIsWaiting" && CheckCharacterItem(pchar, "TizerKey"))
			{
				link.l7 = StringFromKey("Barmen_67");
				link.l7.go = "ansewer_7";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l8"))
			{
				link.l8 = StringFromKey("Barmen_68");
				link.l8.go = "ansewer_8";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l9"))
			{
				link.l9 = StringFromKey("Barmen_69");
				link.l9.go = "ansewer_9";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l10"))
			{
				link.l10 = StringFromKey("Barmen_70");
				link.l10.go = "ansewer_10";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l11") && !CheckCharacterItem(pchar, "map_LSC")) //квест получения карты города
			{
				link.l11 = StringFromKey("Barmen_71");
				link.l11.go = "ansewer_11";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l12") && CheckActiveQuest("LSC_findDekster"))
			{
				link.l12 = StringFromKey("Barmen_72");
				link.l12.go = "ansewer_12";
			}
			link.l20 = StringFromKey("Barmen_73");
			link.l20.go = "exit";
		break;
		case "ansewer_5":
			dialog.text = StringFromKey("Barmen_74");
			link.l1 = StringFromKey("Barmen_75");
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = StringFromKey("Barmen_76");
			if (pchar.questTemp.LSC == "AdmiralIsWaiting")
			{
				link.l1 = StringFromKey("Barmen_77");
				link.l1.go = "ansewer_5_2";
			}
			else
			{
				link.l1 = StringFromKey("Barmen_78");
				link.l1.go = "int_quests";
			}
		break;
		case "ansewer_5_2":
			dialog.text = StringFromKey("Barmen_79", pchar.name);
			link.l1 = StringFromKey("Barmen_80");
			link.l1.go = "int_quests";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("Barmen_81", pchar);
			link.l1 = StringFromKey("Barmen_82");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("Barmen_83", pchar);
			link.l1 = StringFromKey("Barmen_84");
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = StringFromKey("Barmen_85");
			link.l1 = StringFromKey("Barmen_86");
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("Barmen_87", pchar);
			link.l1 = StringFromKey("Barmen_88");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_4":
			dialog.text = StringFromKey("Barmen_89");
			link.l1 = StringFromKey("Barmen_90");
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = StringFromKey("Barmen_91", pchar.name);
			link.l1 = StringFromKey("Barmen_92");
			link.l1.go = "ansewer_4_2";
		break;
		case "ansewer_4_2":
			dialog.text = StringFromKey("Barmen_93");
			link.l1 = StringFromKey("Barmen_94");
			link.l1.go = "ansewer_4_3";
		break;
		case "ansewer_4_3":
			dialog.text = StringFromKey("Barmen_95");
			link.l1 = StringFromKey("Barmen_96");
			link.l1.go = "ansewer_4_4";
		break;
		case "ansewer_4_4":
			dialog.text = StringFromKey("Barmen_97");
			link.l1 = StringFromKey("Barmen_98");
			link.l1.go = "int_quests";
		break;
		case "ansewer_6":
			dialog.text = StringFromKey("Barmen_99");
			link.l1 = StringFromKey("Barmen_100");
			link.l1.go = "ansewer_6_1";
			NextDiag.(NodePrevName).l6 = true;
		break;
		case "ansewer_6_1":
			dialog.text = StringFromKey("Barmen_101");
			link.l1 = StringFromKey("Barmen_102");
			link.l1.go = "ansewer_6_2";
		break;
		case "ansewer_6_2":
			dialog.text = StringFromKey("Barmen_103");
			link.l1 = StringFromKey("Barmen_104");
			link.l1.go = "ansewer_6_3";
		break;
		case "ansewer_6_3":
			dialog.text = StringFromKey("Barmen_105");
			link.l1 = StringFromKey("Barmen_106");
			link.l1.go = "ansewer_6_4";
		break;
		case "ansewer_6_4":
			dialog.text = StringFromKey("Barmen_107", pchar.name);
			link.l1 = StringFromKey("Barmen_108");
			link.l1.go = "ansewer_6_5";
		break;
		case "ansewer_6_5":
			dialog.text = StringFromKey("Barmen_109");
			link.l1 = StringFromKey("Barmen_110");
			link.l1.go = "ansewer_6_6";
		break;
		case "ansewer_6_6":
			dialog.text = StringFromKey("Barmen_111");
			link.l1 = StringFromKey("Barmen_112");
			link.l1.go = "int_quests";
			AddQuestRecord("ISS_MainLine", "4");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
			LSC_UpdateQuestMarksToCitizens();
			AddLandQuestMark_Main_WithCondition(npchar, "ISS_MainLine", "LSC_Tizer_Barmen_QuestMarkCondition");
		break;
		case "ansewer_7":
			dialog.text = StringFromKey("Barmen_113");
			link.l1 = StringFromKey("Barmen_114");
			link.l1.go = "ansewer_7_1";
			NextDiag.(NodePrevName).l7 = true;
		break;
		case "ansewer_7_1":
			dialog.text = StringFromKey("Barmen_115");
			link.l1 = StringFromKey("Barmen_116");
			link.l1.go = "ansewer_7_2";
		break;
		case "ansewer_7_2":
			dialog.text = StringFromKey("Barmen_117");
			link.l1 = StringFromKey("Barmen_118");
			link.l1.go = "int_quests";
		break;
		case "ansewer_8":
			dialog.text = StringFromKey("Barmen_119");
			link.l1 = StringFromKey("Barmen_120");
			link.l1.go = "ansewer_8_1";
			NextDiag.(NodePrevName).l8 = true;
		break;
		case "ansewer_8_1":
			dialog.text = StringFromKey("Barmen_121");
			link.l1 = StringFromKey("Barmen_122");
			link.l1.go = "ansewer_8_2";
			link.l2 = StringFromKey("Barmen_123");
			link.l2.go = "ansewer_8_3";
		break;
		case "ansewer_8_2":
			dialog.text = StringFromKey("Barmen_124", pchar);
			link.l1 = StringFromKey("Barmen_125");
			link.l1.go = "ansewer_8_3";
		break;
		case "ansewer_8_3":
			dialog.text = StringFromKey("Barmen_126");
			link.l1 = StringFromKey("Barmen_127");
			link.l1.go = "ansewer_8_4";
		break;
		case "ansewer_8_4":
			dialog.text = StringFromKey("Barmen_128");
			link.l1 = StringFromKey("Barmen_129");
			link.l1.go = "int_quests";
		break;
		case "ansewer_9":
			dialog.text = StringFromKey("Barmen_130");
			link.l1 = StringFromKey("Barmen_131");
			link.l1.go = "ansewer_9_1";
			NextDiag.(NodePrevName).l9 = true;
		break;
		case "ansewer_9_1":
			dialog.text = StringFromKey("Barmen_132");
			link.l1 = StringFromKey("Barmen_133");
			link.l1.go = "int_quests";
		break;
		case "ansewer_10":
			dialog.text = StringFromKey("Barmen_134", pchar.name);
			link.l1 = StringFromKey("Barmen_135");
			link.l1.go = "ansewer_10_1";
			NextDiag.(NodePrevName).l10 = true;
		break;
		case "ansewer_10_1":
			dialog.text = StringFromKey("Barmen_136", pchar.name);
			link.l1 = StringFromKey("Barmen_137", pchar);
			link.l1.go = "int_quests";
		break;
		case "ansewer_11":
			dialog.text = StringFromKey("Barmen_138");
			link.l1 = StringFromKey("Barmen_139");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l11 = true;
			AddQuestRecord("FindMapLSC", "2_1");
			LSC_UpdateQuestMarksToCitizens();
			AddLandQuestMark_Main(CharacterFromID("LSC_Trader"), "FindMapLSC");
		break;
		case "ansewer_12":
			dialog.text = StringFromKey("Barmen_140");
			link.l1 = StringFromKey("Barmen_141");
			link.l1.go = "ansewer_12_1";
			NextDiag.(NodePrevName).l12 = true;
		break;
		case "ansewer_12_1":
			dialog.text = StringFromKey("Barmen_142", pchar.name);
			link.l1 = StringFromKey("Barmen_143");
			link.l1.go = "ansewer_12_2";
		break;
		case "ansewer_12_2":
			dialog.text = StringFromKey("Barmen_144");
			link.l1 = StringFromKey("Barmen_145", npchar.name);
			link.l1.go = "int_quests";
		break;

		// ------------------ квесты ------------------
		//наводка на квест ограбление магазина
		case "takeStoreMoney":
			dialog.text = StringFromKey("Barmen_146");
			link.l1 = StringFromKey("Barmen_147");
			link.l1.go = "exit";
			AddQuestRecord("ISS_takeStoreMoney", "5");
			SetCurrentQuestMark(npchar); // обновим квест метку
		break;
		//бармен забивает стрелу в винном погребе
		case "Tizer":
			dialog.text = StringFromKey("Barmen_148");
			link.l1 = StringFromKey("Barmen_149");
			link.l1.go = "Tizer_1";
		break;
		case "Tizer_1":
			dialog.text = StringFromKey("Barmen_150");
			link.l1 = StringFromKey("Barmen_151");
			link.l1.go = "Tizer_2";
		break;
		case "Tizer_2":
			dialog.text = StringFromKey("Barmen_152");
			link.l1 = StringFromKey("Barmen_153");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toWineCellar";
			AddQuestRecord("ISS_MainLine", "6");
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
		//бармен ругается, что ГГ не пришёл в погреб
		case "TizerCellarLate":
			dialog.text = StringFromKey("Barmen_154", pchar);
			link.l1 = StringFromKey("Barmen_155");
			link.l1.go = "TizerCellarLate_1";
		break;
		case "TizerCellarLate_1":
			dialog.text = StringFromKey("Barmen_156");
			link.l1 = StringFromKey("Barmen_157");
			link.l1.go = "TizerCellarLate_2";
		break;
		case "TizerCellarLate_2":
			dialog.text = StringFromKey("Barmen_158");
			link.l1 = StringFromKey("Barmen_159");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toWineCellar";
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
		//базар с барменом в погребе
		case "TizerCellar":
			dialog.text = StringFromKey("Barmen_160", pchar);
			link.l1 = StringFromKey("Barmen_161");
			link.l1.go = "TizerCellar_1";
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.LSC_returnBarmen_2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_returnBarmen_2.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_returnBarmen_2.function = "LSC_returnBarmen_2";
		break;
		case "TizerCellar_1":
			dialog.text = StringFromKey("Barmen_162");
			link.l1 = StringFromKey("Barmen_163");
			link.l1.go = "TizerCellar_2";
		break;
		case "TizerCellar_2":
			dialog.text = StringFromKey("Barmen_164");
			link.l1 = StringFromKey("Barmen_165", pchar);
			link.l1.go = "TizerCellar_3";
		break;
		case "TizerCellar_3":
			dialog.text = StringFromKey("Barmen_166");
			link.l1 = StringFromKey("Barmen_167");
			link.l1.go = "TizerCellar_4";
		break;
		case "TizerCellar_4":
			dialog.text = StringFromKey("Barmen_168");
			link.l1 = StringFromKey("Barmen_169");
			link.l1.go = "TizerCellar_5";
		break;
		case "TizerCellar_5":
			dialog.text = StringFromKey("Barmen_170", pchar, pchar.name);
			link.l1 = StringFromKey("Barmen_171");
			link.l1.go = "TizerCellar_6";
		break;
		case "TizerCellar_6":
			dialog.text = StringFromKey("Barmen_172", pchar);
			link.l1 = StringFromKey("Barmen_173");
			link.l1.go = "TizerCellar_7";
		break;
		case "TizerCellar_7":
			dialog.text = StringFromKey("Barmen_174");
			if (CheckCharacterItem(pchar, "letter_LSC_2"))
			{
				link.l1 = StringFromKey("Barmen_175", pchar);
				link.l1.go = "TizerCellarOk_1";
			}
			else
			{
				link.l1 = StringFromKey("Barmen_176");
				link.l1.go = "TizerCellar_8";
			}
		break;
		case "TizerCellar_8":
			dialog.text = StringFromKey("Barmen_177", pchar);
			link.l1 = StringFromKey("Barmen_178");
			link.l1.go = "TizerCellar_9";
		break;
		case "TizerCellar_9":
			dialog.text = StringFromKey("Barmen_179");
			link.l1 = StringFromKey("Barmen_180");
			link.l1.go = "TizerCellar_10";
		break;
		case "TizerCellar_10":
			dialog.text = StringFromKey("Barmen_181");
			link.l1 = StringFromKey("Barmen_182");
			link.l1.go = "TizerCellar_11";
		break;
		case "TizerCellar_11":
			dialog.text = StringFromKey("Barmen_183");
			link.l1 = StringFromKey("Barmen_184");
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "7");
			pchar.questTemp.LSC = "toDiffindoor"; //флаг линейки ГПК
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;

		case "TizerCellarOk_1":
			dialog.text = StringFromKey("Barmen_185");
			link.l1 = StringFromKey("Barmen_186");
			link.l1.go = "TizerCellarOk_2";
			TakeItemFromCharacter(pchar, "letter_LSC_2");
		break;
		case "TizerCellarOk_2":
			dialog.text = StringFromKey("Barmen_187");
			link.l1 = StringFromKey("Barmen_188");
			link.l1.go = "TizerCellarOk_3";
		break;
		case "TizerCellarOk_3":
			dialog.text = StringFromKey("Barmen_189", pchar);
			link.l1 = StringFromKey("Barmen_190");
			link.l1.go = "TizerCellarOk_4";
		break;
		case "TizerCellarOk_4":
			dialog.text = StringFromKey("Barmen_191");
			link.l1 = StringFromKey("Barmen_192");
			link.l1.go = "TizerCellarOk_5";
		break;
		case "TizerCellarOk_5":
			dialog.text = StringFromKey("Barmen_193", pchar.name);
			link.l1 = StringFromKey("Barmen_194");
			link.l1.go = "TizerCellarOk_6";
		break;
		case "TizerCellarOk_6":
			dialog.text = StringFromKey("Barmen_195");
			link.l1 = StringFromKey("Barmen_196");
			link.l1.go = "TizerCellarOk_7";
		break;
		case "TizerCellarOk_7":
			dialog.text = StringFromKey("Barmen_197");
			link.l1 = StringFromKey("Barmen_198");
			link.l1.go = "TizerCellarOk_8";
		break;
		case "TizerCellarOk_8":
			dialog.text = StringFromKey("Barmen_199");
			link.l1 = StringFromKey("Barmen_200");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toAndreLabor"; //флаг линейки ГПК
			AddQuestRecord("ISS_MainLine", "8");
			pchar.questTemp.LSC.checkBoxes = true; //шмалять по открытым сундукам ежесуточно
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("AndreLabor"), "ISS_MainLine");
		break;

		case "AfterProtector_1":
			dialog.text = StringFromKey("Barmen_201");
			link.l1 = StringFromKey("Barmen_202", pchar);
			link.l1.go = "AfterProtector_2";
		break;
		case "AfterProtector_2":
			dialog.text = StringFromKey("Barmen_203", pchar);
			link.l1 = StringFromKey("Barmen_204", pchar);
			link.l1.go = "AfterProtector_3";
		break;
		case "AfterProtector_3":
			dialog.text = StringFromKey("Barmen_205", pchar);
			link.l1 = StringFromKey("Barmen_206");
			link.l1.go = "AfterProtector_4";
		break;
		case "AfterProtector_4":
			dialog.text = StringFromKey("Barmen_207");
			link.l1 = StringFromKey("Barmen_208");
			link.l1.go = "AfterProtector_5";
		break;
		case "AfterProtector_5":
			dialog.text = StringFromKey("Barmen_209");
			link.l1 = StringFromKey("Barmen_210");
			link.l1.go = "AfterProtector_6";
		break;
		case "AfterProtector_6":
			dialog.text = StringFromKey("Barmen_211");
			link.l1 = StringFromKey("Barmen_212");
			link.l1.go = "AfterProtector_7";
		break;
		case "AfterProtector_7":
			dialog.text = StringFromKey("Barmen_213", pchar);
			link.l1 = StringFromKey("Barmen_214");
			link.l1.go = "AfterProtector_8";
		break;
		case "AfterProtector_8":
			dialog.text = StringFromKey("Barmen_215");
			link.l1 = StringFromKey("Barmen_216");
			link.l1.go = "AfterProtector_9";
		break;
		case "AfterProtector_9":
			dialog.text = StringFromKey("Barmen_217");
			link.l1 = StringFromKey("Barmen_218");
			link.l1.go = "AfterProtector_10";
		break;
		case "AfterProtector_10":
			dialog.text = StringFromKey("Barmen_219");
			link.l1 = StringFromKey("Barmen_220");
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "11");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ен", "на"));
			pchar.questTemp.LSC = "toKillOneNarval";
			pchar.quest.LSC_KillOneNarval.win_condition.l1 = "locator";
			pchar.quest.LSC_KillOneNarval.win_condition.l1.location = "VelascoShipInside1";
			pchar.quest.LSC_KillOneNarval.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_KillOneNarval.win_condition.l1.locator = "reload2";
			pchar.quest.LSC_KillOneNarval.function = "LSC_KillOneNarval";
			pchar.quest.LSC_KillOneNarval2.win_condition.l1 = "locator";
			pchar.quest.LSC_KillOneNarval2.win_condition.l1.location = "VelascoShipInside1";
			pchar.quest.LSC_KillOneNarval2.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_KillOneNarval2.win_condition.l1.locator = "reload5";
			pchar.quest.LSC_KillOneNarval2.function = "LSC_KillOneNarval";
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("PedroHurtado"), "ISS_MainLine");
		break;

		case "NarvalRing_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Barmen_221", pchar),
						StringFromKey("Barmen_222"),
						StringFromKey("Barmen_223"),
						StringFromKey("Barmen_224", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Barmen_225", pchar),
						StringFromKey("Barmen_226"),
						StringFromKey("Barmen_227"),
						StringFromKey("Barmen_228", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);

			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;

		case "AfterNarvalDesrt_1":
			dialog.text = StringFromKey("Barmen_229");
			link.l1 = StringFromKey("Barmen_230", pchar);
			link.l1.go = "AfterNarvalDesrt_2";
		break;
		case "AfterNarvalDesrt_2":
			dialog.text = StringFromKey("Barmen_231", pchar);
			link.l1 = StringFromKey("Barmen_232");
			link.l1.go = "AfterNarvalDesrt_3";
		break;
		case "AfterNarvalDesrt_3":
			dialog.text = StringFromKey("Barmen_233");
			link.l1 = StringFromKey("Barmen_234");
			link.l1.go = "AfterNarvalDesrt_4";
		break;
		case "AfterNarvalDesrt_4":
			dialog.text = StringFromKey("Barmen_235");
			link.l1 = StringFromKey("Barmen_236");
			link.l1.go = "AfterNarvalDesrt_5";
		break;
		case "AfterNarvalDesrt_5":
			dialog.text = StringFromKey("Barmen_237", pchar);
			link.l1 = StringFromKey("Barmen_238", pchar);
			link.l1.go = "AfterNarvalDesrt_6";
		break;
		case "AfterNarvalDesrt_6":
			dialog.text = StringFromKey("Barmen_239", pchar);
			link.l1 = StringFromKey("Barmen_240");
			link.l1.go = "AfterNarvalDesrt_7";
		break;
		case "AfterNarvalDesrt_7":
			dialog.text = StringFromKey("Barmen_241");
			link.l1 = StringFromKey("Barmen_242");
			link.l1.go = "StartRing";
			pchar.questTemp.LSC = "waitInterception";
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
			AddQuestRecord("ISS_MainLine", "18");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
			AddLandQuestMark_Main_WithCondition(npchar, "ISS_MainLine", "LSC_WaitInterception_Barmen_QuestMarkCondition");
		break;

		case "InterceptionNext":
			dialog.text = StringFromKey("Barmen_243");
			link.l1 = StringFromKey("Barmen_244");
			link.l1.go = "exit";
		break;
		case "Interception":
			dialog.text = StringFromKey("Barmen_245");
			link.l1 = StringFromKey("Barmen_246");
			link.l1.go = "Interception_1";
		break;
		case "Interception_1":
			dialog.text = StringFromKey("Barmen_247");
			link.l1 = StringFromKey("Barmen_248");
			link.l1.go = "Interception_2";
		break;
		case "Interception_2":
			dialog.text = StringFromKey("Barmen_249");
			link.l1 = StringFromKey("Barmen_250");
			link.l1.go = "Interception_3";
		break;
		case "Interception_3":
			dialog.text = StringFromKey("Barmen_251");
			link.l1 = StringFromKey("Barmen_252");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toInterception";
			pchar.questTemp.LSC.itemState = false; //флаг нахождения в локаторе итем в таверне
			AddQuestRecord("ISS_MainLine", "19");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ен", "на"));
			sld = characterFromID("MalcolmFawn");
			sld.quest.startRing = true;
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;

		case "InterceptionLate":
			dialog.text = StringFromKey("Barmen_253");
			link.l1 = StringFromKey("Barmen_254");
			link.l1.go = "InterceptionBadWork_1";
		break;
		case "InterceptionYouSeen":
			dialog.text = StringFromKey("Barmen_255");
			link.l1 = StringFromKey("Barmen_256");
			link.l1.go = "InterceptionBadWork_1";
		break;
		case "InterceptionBadWork_1":
			dialog.text = StringFromKey("Barmen_257");
			link.l1 = StringFromKey("Barmen_258");
			link.l1.go = "InterceptionBadWork_2";
		break;
		case "InterceptionBadWork_2":
			dialog.text = StringFromKey("Barmen_259");
			link.l1 = StringFromKey("Barmen_260");
			link.l1.go = "InterceptionBadWork_3";
		break;
		case "InterceptionBadWork_3":
			dialog.text = StringFromKey("Barmen_261");
			link.l1 = StringFromKey("Barmen_262");
			link.l1.go = "InterceptionBadWork_4";
		break;
		case "InterceptionBadWork_4":
			dialog.text = StringFromKey("Barmen_263");
			link.l1 = StringFromKey("Barmen_264");
			link.l1.go = "StartDrink";
			pchar.questTemp.LSC = "waitInterceptionResult";
			AddQuestRecord("ISS_MainLine", "22");
			SetTimerFunction("LSC_changeBarmen", 0, 0, 15);
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;

		case "StartDrink":
			dialog.text = StringFromKey("Barmen_265");
			link.l1 = StringFromKey("Barmen_266");
			link.l1.go = "exit";
			npchar.quest.drink = "start";
			AddQuestRecord("LSC_Drink", "8");
			AddLandQuestMark_Main(CharacterFromID("PedroHurtado"), "LSC_Drink");
		break;

		case "Result":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Barmen_267"),
						StringFromKey("Barmen_268", pchar),
						StringFromKey("Barmen_269"),
						StringFromKey("Barmen_270"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Barmen_271"),
						StringFromKey("Barmen_272", pchar),
						StringFromKey("Barmen_273", pchar),
						StringFromKey("Barmen_274", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "InterceptionOk":
			sld = characterFromId("LSCMayor");
			if (sld.location == "FleuronTavern")
				dialog.text = StringFromKey("Barmen_275", pchar);
			else
				dialog.text = StringFromKey("Barmen_276", pchar);
			link.l1 = StringFromKey("Barmen_277", pchar);
			link.l1.go = "InterceptionOk_1";
		break;
		case "InterceptionOk_1":
			dialog.text = StringFromKey("Barmen_278");
			link.l1 = StringFromKey("Barmen_279");
			link.l1.go = "InterceptionOk_2";
		break;
		case "InterceptionOk_2":
			dialog.text = StringFromKey("Barmen_280");
			link.l1 = StringFromKey("Barmen_281");
			link.l1.go = "InterceptionOk_4";
		break;
		case "InterceptionOk_4":
			dialog.text = StringFromKey("Barmen_282");
			link.l1 = StringFromKey("Barmen_283");
			link.l1.go = "InterceptionOk_5";
		break;
		case "InterceptionOk_5":
			dialog.text = StringFromKey("Barmen_284");
			link.l1 = StringFromKey("Barmen_285");
			link.l1.go = "InterceptionOk_6";
		break;
		case "InterceptionOk_6":
			dialog.text = StringFromKey("Barmen_286", pchar);
			link.l1 = StringFromKey("Barmen_287");
			link.l1.go = "InterceptionOk_7";
		break;
		case "InterceptionOk_7":
			dialog.text = StringFromKey("Barmen_288");
			link.l1 = StringFromKey("Barmen_289");
			link.l1.go = "InterceptionOk_8";
		break;
		case "InterceptionOk_8":
			dialog.text = StringFromKey("Barmen_290");
			link.l1 = StringFromKey("Barmen_291");
			link.l1.go = "StartDrink";
			pchar.questTemp.LSC = "waitInterceptionResult";
			AddQuestRecord("ISS_MainLine", "24");
			SetTimerFunction("LSC_changeBarmen", 0, 0, 3);
		break;

		case "StartRing":
			dialog.text = StringFromKey("Barmen_292");
			link.l1 = StringFromKey("Barmen_293");
			link.l1.go = "StartRing_1";
		break;
		case "StartRing_1":
			dialog.text = StringFromKey("Barmen_294");
			link.l1 = StringFromKey("Barmen_295", npchar.name);
			link.l1.go = "exit";
			npchar.quest.startRing = true;
			sld = characterFromID("MalcolmFawn");
			sld.quest.startRing = true;
			AddQuestRecord("LSC_Ring", "9");
			AddQuestUserData("LSC_Ring", "sName", GetFullName(npchar));
			AddLandQuestMark_Main(sld, "LSC_Ring");
		break;
		case "WaitRing":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Barmen_296"),
						StringFromKey("Barmen_297", pchar),
						StringFromKey("Barmen_298"),
						StringFromKey("Barmen_299"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Barmen_300"),
						StringFromKey("Barmen_301", pchar),
						StringFromKey("Barmen_302"),
						StringFromKey("Barmen_303", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("WaitRing_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "WaitRing_1":
			dialog.text = StringFromKey("Barmen_304");
			link.l1 = StringFromKey("Barmen_305", npchar.name);
			link.l1.go = "exit";
		break;

		// пей до дна
		case "drunk_fail":
			dialog.text = StringFromKey("Barmen_306", pchar);
			if (sti(pchar.money) >= 500)
			{
				link.l1 = StringFromKey("Barmen_307", pchar, npchar.name);
				AddMoneyToCharacter(pchar, -500);
			}
			else link.l1 = StringFromKey("Barmen_308", npchar.name);
			link.l1.go = "exit";
			npchar.quest.drink = "done";
		break;

		case "drunk_win":
			DialogExit();
			AddMoneyToCharacter(pchar, 100000);
			npchar.quest.drink = "done";
		break;

		//смерть Брюннера
		case "NB_1":
			dialog.text = StringFromKey("Barmen_309");
			link.l1 = StringFromKey("Barmen_310");
			link.l1.go = "NB_2";
			npchar.quest.HillNB_1 = true;
		break;
		case "NB_2":
			dialog.text = StringFromKey("Barmen_311");
			link.l1 = StringFromKey("Barmen_312");
			link.l1.go = "NB_3";
		break;
		case "NB_3":
			dialog.text = StringFromKey("Barmen_313");
			link.l1 = StringFromKey("Barmen_314");
			link.l1.go = "NB_4";
		break;
		case "NB_4":
			dialog.text = StringFromKey("Barmen_315", pchar);
			link.l1 = StringFromKey("Barmen_316");
			link.l1.go = "exit";
			if (pchar.questTemp.LSC == "barmenIsDeadYouKnow")
			{
				pchar.questTemp.LSC = "toArmo_BrunnerDead";
				AddLandQuestMark_Main(CharacterFromID("LSCwaitress"), "ISS_MainLine");
			}
			AddQuestRecord("ISS_MainLine", "25");
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;

		case "NBB_1":
			dialog.text = StringFromKey("Barmen_317", pchar);
			link.l1 = StringFromKey("Barmen_318");
			link.l1.go = "NBB_2";
			npchar.quest.HillNBB_1 = true;
		break;
		case "NBB_2":
			dialog.text = StringFromKey("Barmen_319");
			link.l1 = StringFromKey("Barmen_320");
			link.l1.go = "NB_3";
		break;
		//базар по убийству Армо
		case "ADied_1":
			dialog.text = StringFromKey("Barmen_321");
			link.l1 = StringFromKey("Barmen_322");
			link.l1.go = "ADied_2";
		break;
		case "ADied_2":
			dialog.text = StringFromKey("Barmen_323");
			link.l1 = StringFromKey("Barmen_324");
			link.l1.go = "ADied_3";
		break;
		case "ADied_3":
			dialog.text = StringFromKey("Barmen_325");
			link.l1 = StringFromKey("Barmen_326", pchar);
			link.l1.go = "exit";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Barmen_327"),
						StringFromKey("Barmen_328", pchar),
						StringFromKey("Barmen_329", pchar),
						StringFromKey("Barmen_330", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Barmen_331"),
						StringFromKey("Barmen_332", pchar),
						StringFromKey("Barmen_333"),
						StringFromKey("Barmen_334", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("Barmen_335");
			link.l1 = StringFromKey("Barmen_336", pchar);
			link.l1.go = "exit";
		break;
		//поиск грузчика на корвет
		case "SeekStevedore":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Barmen_337"),
						StringFromKey("Barmen_338", pchar),
						StringFromKey("Barmen_339", pchar),
						StringFromKey("Barmen_340", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Barmen_341"),
						StringFromKey("Barmen_342", pchar),
						StringFromKey("Barmen_343"),
						StringFromKey("Barmen_344", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekStevedore_1", "", "", "", npchar, Dialog.CurrentNode);
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
		case "SeekStevedore_1":
			dialog.text = StringFromKey("Barmen_345");
			link.l1 = StringFromKey("Barmen_346");
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			npchar.toSeekCrewInTavern = true;
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Barmen_347"),
						StringFromKey("Barmen_348"),
						StringFromKey("Barmen_349"),
						StringFromKey("Barmen_350", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Barmen_351"),
						StringFromKey("Barmen_352", pchar),
						StringFromKey("Barmen_353"),
						StringFromKey("Barmen_354"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("Barmen_355");
			link.l1 = StringFromKey("Barmen_356", pchar);
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("Barmen_357");
			link.l1 = StringFromKey("Barmen_358");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("Barmen_359");
			link.l1 = StringFromKey("Barmen_360");
			link.l1.go = "exit";
		break;

	}
	NextDiag.PrevNode = NodeName;
}
