#include "DIALOGS\Rumours\Simple_rumors.c"

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = StringFromKey("Waitress_1", pchar);
				link.l1 = StringFromKey("Waitress_2");
				link.l1.go = "exit";
				break;
			}
			//после завала Хилла Брюннера
			if (pchar.questTemp.LSC == "barmenIsDead")
			{
				dialog.Text = StringFromKey("Waitress_3", GetAddress_Form(NPChar));
				link.l4 = StringFromKey("Waitress_4");
				link.l4.go = "NB_1";
				pchar.questTemp.LSC = "barmenIsDeadYouKnow";
				break;
			}
			if (pchar.questTemp.LSC == "barmenIsDeadYouKnow" || pchar.questTemp.LSC == "toArmo_BrunnerDead")
			{
				dialog.Text = StringFromKey("Waitress_5", GetAddress_Form(NPChar));
				link.l4 = StringFromKey("Waitress_6");
				link.l4.go = "NBB_1";
				break;
			}
			if (NPChar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.Text = StringFromKey("Waitress_7");
					Link.l1 = StringFromKey("Waitress_8", pchar);
					link.l1.go = "FT_1";
				}
				else
				{
					dialog.Text = StringFromKey("Waitress_9");
					Link.l1 = StringFromKey("Waitress_10", pchar);
					Link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("Waitress_11", GetAddress_Form(NPChar));
				Link.l1 = StringFromKey("Waitress_12", npchar.name);
				Link.l1.go = "int_quests";
				link.l10 = StringFromKey("Waitress_13");
				link.l10.go = "exit";
				//рассказываем ей о том, что, возможно, за убийством Хилла стоят касперы
				if (pchar.questTemp.LSC == "toSeekMechanik" && !CheckAttribute(pchar, "questTemp.LSC.Armo"))
				{
					link.l4 = StringFromKey("Waitress_14");
					link.l4.go = "AboutCasper_1";
				}
				//наводка на первого
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 0)
				{
					link.l4 = StringFromKey("Waitress_15");
					link.l4.go = "Casper1";
				}
				//ждём втогого
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 2 && CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = StringFromKey("Waitress_16");
					link.l4.go = "WaitCasper1";
				}
				//наводка на второго
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 2 && !CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = StringFromKey("Waitress_17");
					link.l4.go = "Casper2";
				}
				//ждём третьего
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 4 && CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = StringFromKey("Waitress_18");
					link.l4.go = "WaitCasper2";
				}
				//наводка на третьего
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 4 && !CheckAttribute(pchar, "questTemp.LSC.Armo.waiting"))
				{
					link.l4 = StringFromKey("Waitress_19");
					link.l4.go = "Casper3";
				}
				//опоздал или упустил вызванного каспера
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 11 && npchar.name == FindPersonalName("LSCwaitress_name"))
				{
					link.l4 = StringFromKey("Waitress_20", pchar);
					link.l4.go = "CasperLate";
				}
				//опоздал или упустил вызванного каспера
				if (pchar.questTemp.LSC == "toSeekMechanik" && CheckAttribute(pchar, "questTemp.LSC.Armo") && sti(pchar.questTemp.LSC.Armo) == 15 && npchar.name == FindPersonalName("LSCwaitress_name"))
				{
					link.l4 = StringFromKey("Waitress_21");
					link.l4.go = "CasperAllFight";
				}
				if (pchar.questTemp.LSC == "seekMillionAndHalf" && npchar.name == FindPersonalName("LSCwaitress_name") && !CheckAttribute(npchar, "quest.giveMoney"))
				{
					link.l4 = StringFromKey("Waitress_22");
					link.l4.go = "askMoney";
				}
				//освобождение мужа Элис Тейлор
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toWaitress")
				{
					link.l5 = StringFromKey("Waitress_23", npchar.name);
					link.l5.go = "ELTHusb_SF";
				}
				//разговор о Легро
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toArmoTalk")
				{
					link.l6 = StringFromKey("Waitress_24");
					link.l6.go = "toArmoTalk";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = StringFromKey("Waitress_25");
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					iTemp = GetCharacterIndex("LSC_Prisoner1");
					if (CheckAttribute(npchar, "LSC_seekCrew_waitTomas") && iTemp != -1 && CheckAttribute(&characters[iTemp], "LSC_seekCrew_Agree"))
					{
						link.l8 = StringFromKey("Waitress_26", pchar);
						link.l8.go = "SeekCrew_7";
					}
					else
					{
						link.l8 = StringFromKey("Waitress_27");
						link.l8.go = "SeekCrew";
					}
				}
			}
		break;
		case "FT_1":
			dialog.text = StringFromKey("Waitress_28", GetFullName(npchar));
			link.l1 = StringFromKey("Waitress_29", GetFullName(pchar));
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = StringFromKey("Waitress_30");
			link.l1 = StringFromKey("Waitress_31");
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = StringFromKey("Waitress_32", pchar);
			link.l1 = StringFromKey("Waitress_33", npchar.name);
			link.l1.go = "exit";
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("Waitress_34");
			if (!CheckAttribute(NextDiag, NodeName + ".l3"))
			{
				link.l3 = StringFromKey("Waitress_35");
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("Waitress_36");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("Waitress_37");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l4"))
			{
				link.l4 = StringFromKey("Waitress_38");
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l5") && !CheckCharacterItem(pchar, "map_LSC")) //квест получения карты города
			{
				link.l5 = StringFromKey("Waitress_39");
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l6") && CheckActiveQuest("LSC_findDekster"))
			{
				link.l6 = StringFromKey("Waitress_40", npchar.name);
				link.l6.go = "ansewer_6";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l7") && CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "over" && npchar.name == FindPersonalName("LSCwaitress_name"))
			{
				link.l7 = StringFromKey("Waitress_41", pchar);
				link.l7.go = "ansewer_7";
			}
			link.l10 = StringFromKey("Waitress_42", pchar);
			link.l10.go = "exit";
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("Waitress_43", pchar);
			link.l1 = StringFromKey("Waitress_44");
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = StringFromKey("Waitress_45");
			link.l1 = StringFromKey("Waitress_46");
			link.l1.go = "ansewer_3_2";
		break;
		case "ansewer_3_2":
			dialog.text = StringFromKey("Waitress_47");
			link.l1 = StringFromKey("Waitress_48");
			link.l1.go = "int_quests";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("Waitress_49");
			link.l1 = StringFromKey("Waitress_50");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("Waitress_51");
			link.l1 = StringFromKey("Waitress_52");
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = StringFromKey("Waitress_53");
			link.l1 = StringFromKey("Waitress_54");
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = StringFromKey("Waitress_55");
			link.l1 = StringFromKey("Waitress_56");
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = StringFromKey("Waitress_57");
			link.l1 = StringFromKey("Waitress_58");
			link.l1.go = "int_quests";
		break;
		case "ansewer_5":
			dialog.text = StringFromKey("Waitress_59");
			link.l1 = StringFromKey("Waitress_60");
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = StringFromKey("Waitress_61", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_62", pchar, npchar.name);
			link.l1.go = "int_quests";
			AddQuestRecord("FindMapLSC", "2");
			LSC_UpdateQuestMarksToCitizens();
			AddLandQuestMark_Main(CharacterFromID("LSC_Trader"), "FindMapLSC");
		break;
		case "ansewer_6":
			dialog.text = StringFromKey("Waitress_63", UpperFirst(GetAddress_Form(NPChar)));
			link.l1 = StringFromKey("Waitress_64");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l6 = true;
		break;
		case "ansewer_7":
			dialog.text = StringFromKey("Waitress_65", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_66", pchar);
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l7 = true;
		break;
		//смерть Брюннера
		case "NB_1":
			dialog.text = StringFromKey("Waitress_67");
			link.l1 = StringFromKey("Waitress_68");
			link.l1.go = "NB_2";
		break;
		case "NB_2":
			dialog.text = StringFromKey("Waitress_69");
			link.l1 = StringFromKey("Waitress_70");
			link.l1.go = "NB_3";
		break;
		case "NBB_1":
			dialog.text = StringFromKey("Waitress_71");
			link.l1 = StringFromKey("Waitress_72");
			link.l1.go = "NB_3";
		break;
		case "NB_3":
			dialog.text = StringFromKey("Waitress_73");
			link.l1 = StringFromKey("Waitress_74");
			link.l1.go = "NB_4";
		break;
		case "NB_4":
			dialog.text = StringFromKey("Waitress_75");
			link.l1 = StringFromKey("Waitress_76");
			link.l1.go = "NB_5";
		break;
		case "NB_5":
			dialog.text = StringFromKey("Waitress_77");
			link.l1 = StringFromKey("Waitress_78");
			link.l1.go = "NB_6";
		break;
		case "NB_6":
			dialog.text = StringFromKey("Waitress_79");
			link.l1 = StringFromKey("Waitress_80");
			link.l1.go = "NB_7";
		break;
		case "NB_7":
			dialog.text = StringFromKey("Waitress_81");
			link.l1 = StringFromKey("Waitress_82");
			link.l1.go = "NB_8";
		break;
		case "NB_8":
			dialog.text = StringFromKey("Waitress_83");
			link.l1 = StringFromKey("Waitress_84");
			link.l1.go = "NB_9";
		break;
		case "NB_9":
			dialog.text = StringFromKey("Waitress_85");
			link.l1 = StringFromKey("Waitress_86");
			link.l1.go = "NB_10";
		break;
		case "NB_10":
			dialog.text = StringFromKey("Waitress_87");
			link.l1 = StringFromKey("Waitress_88");
			link.l1.go = "NB_11";
		break;
		case "NB_11":
			dialog.text = StringFromKey("Waitress_89");
			link.l1 = StringFromKey("Waitress_90");
			link.l1.go = "NB_12";
		break;
		case "NB_12":
			dialog.text = StringFromKey("Waitress_91", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_92");
			link.l1.go = "NB_13";
		break;
		case "NB_13":
			dialog.text = StringFromKey("Waitress_93", UpperFirst(GetAddress_Form(NPChar)));
			link.l1 = StringFromKey("Waitress_94");
			link.l1.go = "NB_14";
		break;
		case "NB_14":
			dialog.text = StringFromKey("Waitress_95");
			link.l1 = StringFromKey("Waitress_96", pchar);
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toAdmiralBarmenDead";
			npchar.quest.meeting = "1";
			if (CheckAttribute(pchar, "questTemp.LSC.knowMechanic"))
			{
				AddQuestRecord("ISS_MainLine", "27");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
				AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("ому", "ой"));
				DeleteAttribute(pchar, "questTemp.LSC.knowMechanic");
			}
			else
			{
				AddQuestRecord("ISS_MainLine", "26");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ся", "ась"));
				AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("му", "ой"));
			}
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("LSCMayor"), "ISS_MainLine");
		break;

		case "AboutCasper_1":
			dialog.text = StringFromKey("Waitress_97", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_98");
			link.l1.go = "AboutCasper_2";
		break;
		case "AboutCasper_2":
			dialog.text = StringFromKey("Waitress_99");
			link.l1 = StringFromKey("Waitress_100", pchar);
			link.l1.go = "AboutCasper_3";
		break;
		case "AboutCasper_3":
			dialog.text = StringFromKey("Waitress_101");
			link.l1 = StringFromKey("Waitress_102");
			link.l1.go = "AboutCasper_4";
		break;
		case "AboutCasper_4":
			dialog.text = StringFromKey("Waitress_103");
			link.l1 = StringFromKey("Waitress_104");
			link.l1.go = "AboutCasper_5";
		break;
		case "AboutCasper_5":
			dialog.text = StringFromKey("Waitress_105", pchar);
			link.l1 = StringFromKey("Waitress_106");
			link.l1.go = "AboutCasper_6";
		break;
		case "AboutCasper_6":
			dialog.text = StringFromKey("Waitress_107", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_108");
			link.l1.go = "AboutCasper_7";
		break;
		case "AboutCasper_7":
			dialog.text = StringFromKey("Waitress_109");
			link.l1 = StringFromKey("Waitress_110");
			link.l1.go = "AboutCasper_8";
			link.l2 = StringFromKey("Waitress_111");
			link.l2.go = "CasperEndFight";
		break;
		case "AboutCasper_8":
			dialog.text = StringFromKey("Waitress_112");
			link.l1 = StringFromKey("Waitress_113");
			link.l1.go = "AboutCasper_9";
		break;
		case "AboutCasper_9":
			dialog.text = StringFromKey("Waitress_114");
			link.l1 = StringFromKey("Waitress_115");
			link.l1.go = "exit";
			AddQuestRecord("ISS_DefeatCasperClan", "2");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "ла"));
			pchar.questTemp.LSC.Armo = 0; //флаг на мочилово касперов. четные - готовность Армо, нечетные - флаг questAction 
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
		break;
		//первый каспер
		case "Casper1":
			if (GetQuestPastDayParam("questTemp.LSC") > 0 && GetHour() < 20)
			{
				dialog.text = StringFromKey("Waitress_116", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Waitress_117", pchar);
				link.l1.go = "Casper1_1";
			}
			else
			{
				dialog.text = StringFromKey("Waitress_118");
				link.l1 = StringFromKey("Waitress_119", pchar);
				link.l1.go = "exit";
			}
		break;
		case "Casper1_1":
			dialog.text = StringFromKey("Waitress_120");
			link.l1 = StringFromKey("Waitress_121", pchar);
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 1; //чтобы сработал questAction на полночь
			AddQuestRecord("ISS_DefeatCasperClan", "3");
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");
		break;

		case "WaitCasper1":
			dialog.text = StringFromKey("Waitress_122", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_123");
			link.l1.go = "WaitCasper1_1";
			link.l2 = StringFromKey("Waitress_124");
			link.l2.go = "CasperEndFight";
		break;
		case "WaitCasper1_1":
			dialog.text = StringFromKey("Waitress_125");
			link.l1 = StringFromKey("Waitress_126", pchar);
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Armo.waiting");
			DeleteAttribute(pchar, "questTemp.LSC.Armo.Interrapt");
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
		break;
		//второй каспер
		case "Casper2":
			if (GetQuestPastDayParam("questTemp.LSC") > 0 && GetHour() < 20)
			{
				dialog.text = StringFromKey("Waitress_127");
				link.l1 = StringFromKey("Waitress_128");
				link.l1.go = "Casper2_1";
			}
			else
			{
				dialog.text = StringFromKey("Waitress_129", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Waitress_130");
				link.l1.go = "exit";
			}
		break;
		case "Casper2_1":
			dialog.text = StringFromKey("Waitress_131", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_132");
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 3; //чтобы сработал questAction на полночь
			AddQuestRecord("ISS_DefeatCasperClan", "6");
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");
		break;

		case "WaitCasper2":
			dialog.text = StringFromKey("Waitress_133", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_134");
			link.l1.go = "WaitCasper2_1";
			link.l2 = StringFromKey("Waitress_135");
			link.l2.go = "CasperEndFight";
		break;
		case "WaitCasper2_1":
			dialog.text = StringFromKey("Waitress_136");
			link.l1 = StringFromKey("Waitress_137");
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Armo.waiting");
			DeleteAttribute(pchar, "questTemp.LSC.Armo.Interrapt");
			SaveCurrentQuestDateParam("questTemp.LSC"); //запомним дату базара
		break;
		//третий каспер
		case "Casper3":
			if (GetQuestPastDayParam("questTemp.LSC") > 0 && GetHour() < 20)
			{
				dialog.text = StringFromKey("Waitress_138");
				link.l1 = StringFromKey("Waitress_139");
				link.l1.go = "Casper3_1";
			}
			else
			{
				dialog.text = StringFromKey("Waitress_140", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Waitress_141");
				link.l1.go = "exit";
			}
		break;
		case "Casper3_1":
			dialog.text = StringFromKey("Waitress_142", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_143");
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 5; //чтобы сработал questAction на полночь
			AddQuestRecord("ISS_DefeatCasperClan", "7");
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");
		break;
		//прерывания хода квеста Армо
		case "CasperLate":
			dialog.text = StringFromKey("Waitress_144", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_145");
			link.l1.go = "CasperLateEndFight";
			//pchar.questTemp.LSC.Armo = 12; //Отмазала девка
			AddQuestRecord("ISS_DefeatCasperClan", "4");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
		break;
		case "CasperAllFight":
			dialog.text = StringFromKey("Waitress_146", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_147");
			link.l1.go = "exit";
			pchar.questTemp.LSC.Armo = 16; //чтобы диалога больше не было
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");
			AddLandQuestMark_Main(CharacterFromID("LSC_Prisoner1"), "ISS_DefeatCasperClan");
		break;
		case "CasperLateEndFight":
			dialog.text = StringFromKey("Waitress_148");
			link.l1 = StringFromKey("Waitress_149");
			AddQuestRecord("ISS_DefeatCasperClan", "9_1");
			pchar.questTemp.LSC.Armo = 16; //чтобы диалога больше не было
			link.l1.go = "exit";
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");
			AddLandQuestMark_Main(CharacterFromID("LSC_Prisoner1"), "ISS_DefeatCasperClan");
		break;
		case "CasperEndFight":
			dialog.text = StringFromKey("Waitress_150");
			link.l1 = StringFromKey("Waitress_151");
			link.l1.go = "exit";
			AddQuestRecord("ISS_DefeatCasperClan", "9");
			pchar.questTemp.LSC.Armo = 16; //чтобы диалога больше не было
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");
			AddLandQuestMark_Main(CharacterFromID("LSC_Prisoner1"), "ISS_DefeatCasperClan");
		break;
		//Армо мертва
		case "ArmoIsDead":
			dialog.text = StringFromKey("Waitress_152");
			link.l1 = StringFromKey("Waitress_153");
			link.l1.go = "ArmoIsDead_1";
		break;
		case "ArmoIsDead_1":
			dialog.text = StringFromKey("Waitress_154");
			link.l1 = StringFromKey("Waitress_155");
			link.l1.go = "ArmoIsDead_2";
		break;
		case "ArmoIsDead_2":
			dialog.text = StringFromKey("Waitress_156", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_157");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		//Если Армо жива, то даёт денег
		case "askMoney":
			dialog.text = StringFromKey("Waitress_158", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_159");
			link.l1.go = "askMoney_1";
		break;
		case "askMoney_1":
			dialog.text = StringFromKey("Waitress_160", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_161");
			link.l1.go = "askMoney_2";
		break;
		case "askMoney_2":
			dialog.text = StringFromKey("Waitress_162");
			link.l1 = StringFromKey("Waitress_163");
			link.l1.go = "askMoney_3";
		break;
		case "askMoney_3":
			dialog.text = StringFromKey("Waitress_164");
			link.l1 = StringFromKey("Waitress_165");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			npchar.quest.giveMoney = true;
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
		//Легро и Томас решаем конфликт
		case "toArmoTalk":
			dialog.text = StringFromKey("Waitress_166");
			link.l1 = StringFromKey("Waitress_167");
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "to3ToPrison";
			AddQuestRecord("TakeVineToPrisoner", "9");
			RemoveLandQuestMark_Main(npchar, "TakeVineToPrisoner");
			AddLandQuestMark_Main(CharacterFromID("LSC_Prisoner1"), "TakeVineToPrisoner");
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Waitress_168", GetAddress_Form(NPChar)),
						StringFromKey("Waitress_169"),
						StringFromKey("Waitress_170"),
						StringFromKey("Waitress_171"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Waitress_172"),
						StringFromKey("Waitress_173", pchar),
						StringFromKey("Waitress_174"),
						StringFromKey("Waitress_175", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("Waitress_176");
			link.l1 = StringFromKey("Waitress_177");
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "43");
			AddQuestUserData("ISS_MainLine", "sName", GetFullName(npchar));
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Waitress_178"),
						StringFromKey("Waitress_179"),
						StringFromKey("Waitress_180"),
						StringFromKey("Waitress_181"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Waitress_182"),
						StringFromKey("Waitress_183", pchar),
						StringFromKey("Waitress_184"),
						StringFromKey("Waitress_185"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			if (npchar.name == FindPersonalName("LSCwaitress_name"))
			{
				iTemp = GetCharacterIndex("LSC_Prisoner1");
				if (iTemp != -1 && CheckAttribute(&characters[iTemp], "help_us"))
				{
					dialog.text = StringFromKey("Waitress_186");
					link.l1 = StringFromKey("Waitress_187");
					link.l1.go = "SeekCrew_4";
				}
				else
				{
					dialog.text = StringFromKey("Waitress_188", GetAddress_Form(NPChar));
					link.l1 = StringFromKey("Waitress_189");
					link.l1.go = "SeekCrew_2";
				}
			}
			else
			{
				dialog.text = StringFromKey("Waitress_190", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Waitress_191");
				link.l1.go = "SeekCrew_2";
			}
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("Waitress_192");
			link.l1 = StringFromKey("Waitress_193");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("Waitress_194");
			link.l1 = StringFromKey("Waitress_195");
			link.l1.go = "exit";
		break;
		case "SeekCrew_4":
			dialog.text = StringFromKey("Waitress_196");
			link.l1 = StringFromKey("Waitress_197");
			link.l1.go = "SeekCrew_5";
		break;
		case "SeekCrew_5":
			dialog.text = StringFromKey("Waitress_198");
			link.l1 = StringFromKey("Waitress_199");
			link.l1.go = "SeekCrew_6";
			link.l2 = StringFromKey("Waitress_200");
			link.l2.go = "SeekCrew_6";
			link.l3 = StringFromKey("Waitress_201");
			link.l3.go = "SeekCrew_6";
		break;
		case "SeekCrew_6":
			dialog.text = StringFromKey("Waitress_202");
			iTemp = GetCharacterIndex("LSC_Prisoner1");
			if (iTemp != -1 && CheckAttribute(&characters[iTemp], "LSC_seekCrew_Agree"))
			{
				link.l1 = StringFromKey("Waitress_203");
				link.l1.go = "SeekCrew_7";
			}
			else
			{
				npchar.LSC_seekCrew_waitTomas = true;
				link.l1 = StringFromKey("Waitress_204");
				link.l1.go = "exit";
				AddLandQuestMark_Main(&Characters[iTemp], "ISS_MainLine");
			}
		break;
		case "SeekCrew_7":
			dialog.text = StringFromKey("Waitress_205", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_206");
			link.l1.go = "SeekCrew_all";

			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
		//освобождение мужа Элис Тейлор
		case "ELTHusb_SF":
			dialog.text = StringFromKey("Waitress_207", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_208");
			link.l1.go = "ELTHusb_SF_1";
		break;
		case "ELTHusb_SF_1":
			dialog.text = StringFromKey("Waitress_209");
			link.l1 = StringFromKey("Waitress_210");
			link.l1.go = "ELTHusb_SF_2";
		break;
		case "ELTHusb_SF_2":
			dialog.text = StringFromKey("Waitress_211");
			link.l1 = StringFromKey("Waitress_212");
			link.l1.go = "ELTHusb_SF_3";
		break;
		case "ELTHusb_SF_3":
			dialog.text = StringFromKey("Waitress_213");
			link.l1 = StringFromKey("Waitress_214");
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "8");
			pchar.questTemp.LSC.ElisHusband = "toZhilBaru";
			RemoveLandQuestMark_Main(npchar, "ISS_ElisHusband");
			AddLandQuestMark_Main(CharacterFromID("ZhilBaru"), "ISS_ElisHusband");
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("Waitress_215");
			link.l1 = StringFromKey("Waitress_216");
			link.l1.go = "GoodBye_1";
			link.l2 = StringFromKey("Waitress_217");
			link.l2.go = "GoodBye_7";
		break;
		case "GoodBye_1":
			dialog.text = StringFromKey("Waitress_218", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_219");
			link.l1.go = "GoodBye_2";
		break;
		case "GoodBye_2":
			dialog.text = StringFromKey("Waitress_220");
			link.l1 = StringFromKey("Waitress_221");
			link.l1.go = "GoodBye_3";
			link.l2 = StringFromKey("Waitress_222");
			link.l2.go = "GoodBye_7";
		break;
		case "GoodBye_3":
			dialog.text = StringFromKey("Waitress_223");
			link.l1 = StringFromKey("Waitress_224");
			link.l1.go = "GoodBye_4";
		break;
		case "GoodBye_4":
			dialog.text = StringFromKey("Waitress_225");
			link.l1 = StringFromKey("Waitress_226");
			link.l1.go = "GoodBye_5";
		break;
		case "GoodBye_5":
			dialog.text = StringFromKey("Waitress_227", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_228");
			link.l1.go = "GoodBye_6";
		break;
		case "GoodBye_6":
			dialog.text = StringFromKey("Waitress_229");
			link.l1 = StringFromKey("Waitress_230");
			link.l1.go = "GoodBye_7";
		break;
		case "GoodBye_7":
			dialog.text = StringFromKey("Waitress_231", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Waitress_232");
			link.l1.go = "GoodBye_8";
		break;
		//финальная реплика с передачей амулета
		case "GoodBye_8":
			dialog.text = StringFromKey("Waitress_233");
			link.l1 = StringFromKey("Waitress_234");
			link.l1.go = "About_Rats";
			link.l2 = StringFromKey("Waitress_235");
			link.l2.go = "GoodBye_9";
			link.l3 = StringFromKey("Waitress_236");
			link.l3.go = "Final_Goodbye";
		break;
		case "About_Rats":
			dialog.text = StringFromKey("Waitress_237");
			link.l1 = StringFromKey("Waitress_238");
			link.l1.go = "GoodBye_9";
		break;
		case "GoodBye_9":
			dialog.text = StringFromKey("Waitress_239");
			link.l1 = StringFromKey("Waitress_240");
			link.l1.go = "Final_Goodbye";
		break;
		case "Final_Goodbye":
			dialog.text = StringFromKey("Waitress_241");
			link.l1 = StringFromKey("Waitress_242");
			link.l1.go = "Exit_GoodBye";
			GiveItem2Character(pchar, "Indian11"); // Выдача амулета крысобога
		break;
	}
	NextDiag.PrevNode = NodeName;
}
 
