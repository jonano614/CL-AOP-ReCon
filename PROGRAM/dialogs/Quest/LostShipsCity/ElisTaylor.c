#include "DIALOGS\Rumours\Simple_rumors.c"
#include "DIALOGS\Quest\LostShipsCity\SeekLSCCitizen_CN.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	ProcessDialog_SeekLSCCitizenCN(NPChar, Link, NextDiag); // для CN языка - поисковик жителей

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;

	switch (Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (npchar.quest.meeting == "0" && pchar.questTemp.LSC != "toSeekCrewInTavern")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = StringFromKey("ElisTaylor_1", GetAddress_Form(NPChar), GetFullName(npchar));
					link.l1 = StringFromKey("ElisTaylor_2", GetFullName(pchar));
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = StringFromKey("ElisTaylor_3", GetAddress_Form(NPChar), GetFullName(npchar));
					link.l1 = StringFromKey("ElisTaylor_4", GetFullName(pchar));
					link.l1.go = "FT_1";
				}
			}
			else
			{
				if (pchar.questTemp.LSC == "AfterAdmiral" && !CheckAttribute(pchar, "questTemp.LSC.ElisHusband"))
				{
					dialog.text = StringFromKey("ElisTaylor_5");
					link.l1 = StringFromKey("ElisTaylor_6");
					link.l1.go = "ELTHusb_begin_1";
					break;
				}
				dialog.text = StringFromKey("ElisTaylor_7");
				link.l1 = StringFromKey("ElisTaylor_8");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("ElisTaylor_9", pchar);
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("ElisTaylor_13", LinkRandPhrase(
							StringFromKey("ElisTaylor_10"),
							StringFromKey("ElisTaylor_11"),
							StringFromKey("ElisTaylor_12", pchar)));
				link.l3.go = "rumours_LSC";
				//квест покупка карты
				sld = characterFromId("LSC_Trader");
				if (CheckAttribute(sld, "quest.takeMap") && sld.quest.takeMap == "notTrade" &&
				!CheckAttribute(pchar, "questTemp.FindMapLSC.toMonika") && !CheckCharacterItem(pchar, "map_LSC"))
				{
					link.l4 = StringFromKey("ElisTaylor_14");
					link.l4.go = "takeMap";
				}
				//муж Элис Тейлор
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "begin")
				{
					link.l7 = StringFromKey("ElisTaylor_15", pchar);
					link.l7.go = "ELTHusb_begin";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toElis")
				{
					link.l7 = StringFromKey("ElisTaylor_16");
					link.l7.go = "ELTHusb_toElis";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toElisGood")
				{
					link.l7 = StringFromKey("ElisTaylor_17");
					link.l7.go = "ELTHusb_good";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = StringFromKey("ElisTaylor_18");
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (pchar.questTemp.LSC == "toSeekCrewInTavern") dialog.text = StringFromKey("ElisTaylor_19"); //сбор в таверне
					link.l8 = StringFromKey("ElisTaylor_20");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("ElisTaylor_21");
				link.l10.go = "exit";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "FS_1":
			dialog.text = StringFromKey("ElisTaylor_22");
			link.l1 = StringFromKey("ElisTaylor_23");
			link.l1.go = "FT_2";
		break;
		case "FT_1":
			dialog.text = StringFromKey("ElisTaylor_24");
			link.l1 = StringFromKey("ElisTaylor_25");
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = StringFromKey("ElisTaylor_26");
			if (pchar.questTemp.LSC == "AdmiralIsWaiting") link.l1 = StringFromKey("ElisTaylor_27");
			else link.l1 = StringFromKey("ElisTaylor_28", pchar);
			link.l1.go = "exit";
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
			dialog.text = StringFromKey("ElisTaylor_32", LinkRandPhrase(
						StringFromKey("ElisTaylor_29", pchar),
						StringFromKey("ElisTaylor_30", pchar),
						StringFromKey("ElisTaylor_31", pchar)));
			link.l1 = StringFromKey("ElisTaylor_33");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("ElisTaylor_34");
			link.l1 = StringFromKey("ElisTaylor_35");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("ElisTaylor_39", LinkRandPhrase(
						StringFromKey("ElisTaylor_36", pchar),
						StringFromKey("ElisTaylor_37"),
						StringFromKey("ElisTaylor_38", pchar)));
			link.l1 = StringFromKey("ElisTaylor_43", LinkRandPhrase(
						StringFromKey("ElisTaylor_40"),
						StringFromKey("ElisTaylor_41"),
						StringFromKey("ElisTaylor_42")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("ElisTaylor_44", npchar);
				link.l1 = StringFromKey("ElisTaylor_48", LinkRandPhrase(
							StringFromKey("ElisTaylor_45"),
							StringFromKey("ElisTaylor_46"),
							StringFromKey("ElisTaylor_47")));
			}
			else
			{
				dialog.text = StringFromKey("ElisTaylor_49", npchar);
				link.l1 = StringFromKey("ElisTaylor_52", RandPhraseSimple(
							StringFromKey("ElisTaylor_50"),
							StringFromKey("ElisTaylor_51")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("ElisTaylor_53");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("ElisTaylor_54");
				Link.l1 = StringFromKey("ElisTaylor_55");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("ElisTaylor_56", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("ElisTaylor_57");
					link.l1 = StringFromKey("ElisTaylor_58");
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("ElisTaylor_59", GetFullName(sld));
					Link.l1 = StringFromKey("ElisTaylor_60");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("ElisTaylor_61");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("ElisTaylor_62", GetFullName(sld));
					Link.l1 = StringFromKey("ElisTaylor_63");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("ElisTaylor_64");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("ElisTaylor_65");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("ElisTaylor_66");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;

		case "SeekCitizen_agree":
			sld = &characters[sti(npchar.quest.seekIdx)];
			npchar.quest.seekIdx.where = WhereLSCCitizen(sld);
			if (npchar.quest.seekIdx.where == "none")
			{
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("ElisTaylor_70", LinkRandPhrase(
								StringFromKey("ElisTaylor_67"),
								StringFromKey("ElisTaylor_68"),
								StringFromKey("ElisTaylor_69")));
					link.l1 = StringFromKey("ElisTaylor_73", RandPhraseSimple(
								StringFromKey("ElisTaylor_71"),
								StringFromKey("ElisTaylor_72")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("ElisTaylor_77", LinkRandPhrase(
								StringFromKey("ElisTaylor_74"),
								StringFromKey("ElisTaylor_75"),
								StringFromKey("ElisTaylor_76")));
					link.l1 = StringFromKey("ElisTaylor_80", RandPhraseSimple(
								StringFromKey("ElisTaylor_78"),
								StringFromKey("ElisTaylor_79")));
					link.l1.go = "exit";
				}
			}
			else
			{
				if (sld.sex == "man")
				{
					if (sld.location == "LostShipsCity_town")
					{
						string Str1 = npchar.location.locator;
						string Str2 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str1, 0, 5) == strcut(Str2, 0, 5))
						{
							dialog.text = StringFromKey("ElisTaylor_84", LinkRandPhrase(
										StringFromKey("ElisTaylor_81"),
										StringFromKey("ElisTaylor_82"),
										StringFromKey("ElisTaylor_83")));
						}
						else
						{
							dialog.text = StringFromKey("ElisTaylor_88", LinkRandPhrase(
										StringFromKey("ElisTaylor_85", npchar.quest.seekIdx.where),
										StringFromKey("ElisTaylor_86", npchar.quest.seekIdx.where),
										StringFromKey("ElisTaylor_87", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("ElisTaylor_92", LinkRandPhrase(
										StringFromKey("ElisTaylor_89", npchar.quest.seekIdx.where),
										StringFromKey("ElisTaylor_90"),
										StringFromKey("ElisTaylor_91")));
						}
						else
						{
							dialog.text = StringFromKey("ElisTaylor_96", LinkRandPhrase(
										StringFromKey("ElisTaylor_93", npchar.quest.seekIdx.where),
										StringFromKey("ElisTaylor_94", npchar.quest.seekIdx.where),
										StringFromKey("ElisTaylor_95", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("ElisTaylor_99", RandPhraseSimple(
								StringFromKey("ElisTaylor_97"),
								StringFromKey("ElisTaylor_98")));
					link.l1.go = "exit";
				}
				else
				{
					if (sld.location == "LostShipsCity_town")
					{
						string Str3 = npchar.location.locator;
						string Str4 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str3, 0, 5) == strcut(Str4, 0, 5))
						{
							dialog.text = StringFromKey("ElisTaylor_103", LinkRandPhrase(
										StringFromKey("ElisTaylor_100"),
										StringFromKey("ElisTaylor_101"),
										StringFromKey("ElisTaylor_102")));
						}
						else
						{
							dialog.text = StringFromKey("ElisTaylor_107", LinkRandPhrase(
										StringFromKey("ElisTaylor_104", npchar.quest.seekIdx.where),
										StringFromKey("ElisTaylor_105", npchar.quest.seekIdx.where),
										StringFromKey("ElisTaylor_106", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("ElisTaylor_111", LinkRandPhrase(
										StringFromKey("ElisTaylor_108", pchar, npchar.quest.seekIdx.where),
										StringFromKey("ElisTaylor_109"),
										StringFromKey("ElisTaylor_110")));
						}
						else
						{
							dialog.text = StringFromKey("ElisTaylor_115", LinkRandPhrase(
										StringFromKey("ElisTaylor_112", npchar.quest.seekIdx.where),
										StringFromKey("ElisTaylor_113", npchar.quest.seekIdx.where),
										StringFromKey("ElisTaylor_114", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("ElisTaylor_118", RandPhraseSimple(
								StringFromKey("ElisTaylor_116"),
								StringFromKey("ElisTaylor_117")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("ElisTaylor_119");
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("ElisTaylor_120");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("ElisTaylor_121");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = StringFromKey("ElisTaylor_122");
				link.l3.go = "ansewer_3";
			}
			link.l10 = StringFromKey("ElisTaylor_123");
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("ElisTaylor_124");
			link.l1 = StringFromKey("ElisTaylor_125");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("ElisTaylor_126");
			link.l1 = StringFromKey("ElisTaylor_127");
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = StringFromKey("ElisTaylor_128");
			link.l1 = StringFromKey("ElisTaylor_129");
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("ElisTaylor_130");
			link.l1 = StringFromKey("ElisTaylor_131");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("ElisTaylor_132"),
						StringFromKey("ElisTaylor_133"),
						StringFromKey("ElisTaylor_134"),
						StringFromKey("ElisTaylor_135"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("ElisTaylor_136"),
						StringFromKey("ElisTaylor_137", pchar),
						StringFromKey("ElisTaylor_138"),
						StringFromKey("ElisTaylor_139", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("ElisTaylor_140");
			link.l1 = StringFromKey("ElisTaylor_141");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = StringFromKey("ElisTaylor_142");
			link.l1 = StringFromKey("ElisTaylor_143");
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = StringFromKey("ElisTaylor_144");
			link.l1 = StringFromKey("ElisTaylor_145");
			link.l1.go = "exit";
			pchar.questTemp.LSC.additional.balls = true;
			AddQuestRecord("ISS_MainLine", "44");
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("FelixMendoza"), "ISS_MainLine");
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = StringFromKey("ElisTaylor_146");
			link.l1 = StringFromKey("ElisTaylor_147");
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("ElisTaylor_148");
			link.l1 = StringFromKey("ElisTaylor_149");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("ElisTaylor_150");
			link.l1 = StringFromKey("ElisTaylor_151");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			sld = CharacterFromId("MaximTailor");
			if (sld.location == "TartarusPrison") // муж в тюрьме
			{
				dialog.text = StringFromKey("ElisTaylor_152");
				link.l1 = StringFromKey("ElisTaylor_153");
			}
			else
			{
				dialog.text = StringFromKey("ElisTaylor_154");
				link.l1 = StringFromKey("ElisTaylor_155");
			}
			link.l1.go = "SeekCrew_all";
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
		//вызволение мужа
		case "ELTHusb_begin":
			dialog.text = StringFromKey("ElisTaylor_156", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("ElisTaylor_157");
			link.l1.go = "ELTHusb_begin_1";
		break;
		case "ELTHusb_begin_1":
			dialog.text = StringFromKey("ElisTaylor_158");
			link.l1 = StringFromKey("ElisTaylor_159");
			link.l1.go = "ELTHusb_begin_2";
		break;
		case "ELTHusb_begin_2":
			dialog.text = StringFromKey("ElisTaylor_160", pchar);
			link.l1 = StringFromKey("ElisTaylor_161");
			link.l1.go = "ELTHusb_begin_3";
		break;
		case "ELTHusb_begin_3":
			dialog.text = StringFromKey("ElisTaylor_162");
			link.l1 = StringFromKey("ElisTaylor_163");
			link.l1.go = "ELTHusb_begin_4";
			link.l2 = StringFromKey("ElisTaylor_164");
			link.l2.go = "ELTHusb_begin_disagree";
		break;
		case "ELTHusb_begin_disagree":
			dialog.text = StringFromKey("ElisTaylor_165");
			link.l1 = StringFromKey("ElisTaylor_166");
			link.l1.go = "exit";
			CloseQuestHeader("ISS_ElisHusband");
			pchar.questTemp.LSC.ElisHusband = "over"; //закончим
			LSC_CheckReadyMainLine(); //проверка все ли готово для продолжения основной линейки
			sld = CharacterFromId("MaximTailor");
			sld.dialog.currentnode = "EternalPrisoner";
			RemoveLandQuestMark_Main(npchar, "ISS_ElisHusband");
			RemoveLandQuestMark_Main(sld, "ISS_ElisHusband");
			RemoveLandQuestMark_Main(CharacterFromId("LSCMayor"), "ISS_ElisHusband");
			RemoveLandQuestMark_Main(CharacterFromID("LSC_PrisonerHead"), "ISS_ElisHusband");
		break;
		case "ELTHusb_begin_4":
			dialog.text = StringFromKey("ElisTaylor_167");
			link.l1 = StringFromKey("ElisTaylor_168");
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "5");
			AddQuestUserData("ISS_ElisHusband", "sSex", GetSexPhrase("", "а"));
			pchar.questTemp.LSC.ElisHusband = "seekFreeMotod";
			sld = characterFromId("MaximTailor");
			sld.dialog.currentnode = "DontRemember";

			RemoveLandQuestMark_Main(npchar, "ISS_ElisHusband");
			AddLandQuestMark_Main(sld, "ISS_ElisHusband");
			AddLandQuestMark_Main(CharacterFromID("LSC_PrisonerHead"), "ISS_ElisHusband");
		break;

		case "ELTHusb_toElis":
			dialog.text = StringFromKey("ElisTaylor_169");
			link.l1 = StringFromKey("ElisTaylor_170");
			link.l1.go = "ELTHusb_toElis_1";
		break;
		case "ELTHusb_toElis_1":
			dialog.text = StringFromKey("ElisTaylor_171");
			link.l1 = StringFromKey("ElisTaylor_172", pchar);
			link.l1.go = "ELTHusb_toElis_2";
		break;
		case "ELTHusb_toElis_2":
			dialog.text = StringFromKey("ElisTaylor_173");
			link.l1 = StringFromKey("ElisTaylor_174");
			link.l1.go = "ELTHusb_toElis_3";
		break;
		case "ELTHusb_toElis_3":
			dialog.text = StringFromKey("ElisTaylor_175");
			link.l1 = StringFromKey("ElisTaylor_176");
			link.l1.go = "ELTHusb_begin_4";
			link.l2 = StringFromKey("ElisTaylor_177");
			link.l2.go = "ELTHusb_begin_disagree";
		break;

		case "ELTHusb_good":
			dialog.text = StringFromKey("ElisTaylor_178");
			link.l1 = StringFromKey("ElisTaylor_179", pchar);
			link.l1.go = "ELTHusb_good_1";
		break;
		case "ELTHusb_good_1":
			dialog.text = StringFromKey("ElisTaylor_180");
			link.l1 = StringFromKey("ElisTaylor_181");
			link.l1.go = "ELTHusb_good_2";
		break;
		case "ELTHusb_good_2":
			dialog.text = StringFromKey("ElisTaylor_182");
			link.l1 = StringFromKey("ElisTaylor_183");
			link.l1.go = "ELTHusb_good_3";
			GiveItem2Character(pchar, "key2");
		break;
		case "ELTHusb_good_3":
			dialog.text = StringFromKey("ElisTaylor_184");
			link.l1 = StringFromKey("ElisTaylor_185");
			link.l1.go = "exit";
			CloseQuestHeader("ISS_ElisHusband");
			pchar.questTemp.LSC.ElisHusband = "over"; //закончим
			SetTimerFunction("LSC_ElisHusbandSet", 0, 0, 1);
			LSC_CheckReadyMainLine(); //проверка все ли готово для продолжения основной линейки
			RemoveLandQuestMark_Main(npchar, "ISS_ElisHusband");
		break;
		//квест получения карты
		case "TakeMap":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("ElisTaylor_186"),
						StringFromKey("ElisTaylor_187"),
						StringFromKey("ElisTaylor_188"),
						StringFromKey("ElisTaylor_189"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("ElisTaylor_190"),
						StringFromKey("ElisTaylor_191", pchar),
						StringFromKey("ElisTaylor_192"),
						StringFromKey("ElisTaylor_193"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("TakeMap_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "TakeMap_1":
			dialog.text = StringFromKey("ElisTaylor_194");
			link.l1 = StringFromKey("ElisTaylor_195");
			link.l1.go = "exit";
			RemoveLandQuestMark_Main(npchar, "FindMapLSC");
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("ElisTaylor_196");
			link.l1 = StringFromKey("ElisTaylor_197");
			link.l1.go = "GoodBye_1";
		break;
		case "GoodBye_1":
			dialog.text = StringFromKey("ElisTaylor_198", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("ElisTaylor_199");
			link.l1.go = "Exit_GoodBye";
			GiveItem2Character(pchar, "recipe_GunEchin");
		break;
	}
	NextDiag.PrevNode = NodeName;
}
