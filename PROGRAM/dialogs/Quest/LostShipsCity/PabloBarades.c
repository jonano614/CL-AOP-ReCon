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
	ProcessDialog_SeekLSCCitizenCN(NPChar, Link, NextDiag);

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
					dialog.text = StringFromKey("PabloBarades_1", GetFullName(npchar));
					link.l1 = StringFromKey("PabloBarades_2", GetFullName(pchar));
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = StringFromKey("PabloBarades_3", GetFullName(npchar));
					link.l1 = StringFromKey("PabloBarades_4", GetFullName(pchar));
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("PabloBarades_5", pchar);
				link.l1 = StringFromKey("PabloBarades_6");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("PabloBarades_7");
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("PabloBarades_11", LinkRandPhrase(
							StringFromKey("PabloBarades_8"),
							StringFromKey("PabloBarades_9"),
							StringFromKey("PabloBarades_10", pchar)));
				link.l3.go = "rumours_LSC";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(pchar, "questTemp.LSC.additional.knippels"))
				{
					link.l8 = StringFromKey("PabloBarades_12", pchar);
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (pchar.questTemp.LSC == "toSeekCrewInTavern") dialog.text = StringFromKey("PabloBarades_13"); //сбор в таверне
					link.l8 = StringFromKey("PabloBarades_14");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("PabloBarades_15");
				link.l10.go = "exit";
			}
		break;
		case "FS_1":
			dialog.text = StringFromKey("PabloBarades_16");
			link.l1 = StringFromKey("PabloBarades_17");
			link.l1.go = "FT_3";
		break;
		case "FT_1":
			dialog.text = StringFromKey("PabloBarades_18");
			link.l1 = StringFromKey("PabloBarades_19");
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = StringFromKey("PabloBarades_20");
			link.l1 = StringFromKey("PabloBarades_21");
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = StringFromKey("PabloBarades_22", pchar);
			link.l1 = StringFromKey("PabloBarades_23");
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = StringFromKey("PabloBarades_24");
			link.l1 = StringFromKey("PabloBarades_25");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
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
			dialog.text = StringFromKey("PabloBarades_29", LinkRandPhrase(
						StringFromKey("PabloBarades_26", pchar),
						StringFromKey("PabloBarades_27", pchar),
						StringFromKey("PabloBarades_28", pchar)));
			link.l1 = StringFromKey("PabloBarades_30");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("PabloBarades_31");
			link.l1 = StringFromKey("PabloBarades_32");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("PabloBarades_36", LinkRandPhrase(
						StringFromKey("PabloBarades_33"),
						StringFromKey("PabloBarades_34"),
						StringFromKey("PabloBarades_35", pchar)));
			link.l1 = StringFromKey("PabloBarades_40", LinkRandPhrase(
						StringFromKey("PabloBarades_37"),
						StringFromKey("PabloBarades_38"),
						StringFromKey("PabloBarades_39")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("PabloBarades_41", npchar);
				link.l1 = StringFromKey("PabloBarades_45", LinkRandPhrase(
							StringFromKey("PabloBarades_42"),
							StringFromKey("PabloBarades_43"),
							StringFromKey("PabloBarades_44")));
			}
			else
			{
				dialog.text = StringFromKey("PabloBarades_46", npchar);
				link.l1 = StringFromKey("PabloBarades_49", RandPhraseSimple(
							StringFromKey("PabloBarades_47", pchar),
							StringFromKey("PabloBarades_48")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("PabloBarades_50");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("PabloBarades_51");
				Link.l1 = StringFromKey("PabloBarades_52");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("PabloBarades_53", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("PabloBarades_54");
					link.l1 = StringFromKey("PabloBarades_55", pchar);
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("PabloBarades_56", GetFullName(sld));
					Link.l1 = StringFromKey("PabloBarades_57");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("PabloBarades_58");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("PabloBarades_59", GetFullName(sld));
					Link.l1 = StringFromKey("PabloBarades_60");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("PabloBarades_61");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("PabloBarades_62");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("PabloBarades_63");
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
					dialog.text = StringFromKey("PabloBarades_67", LinkRandPhrase(
								StringFromKey("PabloBarades_64"),
								StringFromKey("PabloBarades_65"),
								StringFromKey("PabloBarades_66")));
					link.l1 = StringFromKey("PabloBarades_70", RandPhraseSimple(
								StringFromKey("PabloBarades_68"),
								StringFromKey("PabloBarades_69")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("PabloBarades_74", LinkRandPhrase(
								StringFromKey("PabloBarades_71"),
								StringFromKey("PabloBarades_72"),
								StringFromKey("PabloBarades_73")));
					link.l1 = StringFromKey("PabloBarades_77", RandPhraseSimple(
								StringFromKey("PabloBarades_75"),
								StringFromKey("PabloBarades_76")));
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
							dialog.text = StringFromKey("PabloBarades_81", LinkRandPhrase(
										StringFromKey("PabloBarades_78"),
										StringFromKey("PabloBarades_79"),
										StringFromKey("PabloBarades_80")));
						}
						else
						{
							dialog.text = StringFromKey("PabloBarades_85", LinkRandPhrase(
										StringFromKey("PabloBarades_82", npchar.quest.seekIdx.where),
										StringFromKey("PabloBarades_83", npchar.quest.seekIdx.where),
										StringFromKey("PabloBarades_84", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("PabloBarades_89", LinkRandPhrase(
										StringFromKey("PabloBarades_86", npchar.quest.seekIdx.where),
										StringFromKey("PabloBarades_87"),
										StringFromKey("PabloBarades_88")));
						}
						else
						{
							dialog.text = StringFromKey("PabloBarades_93", LinkRandPhrase(
										StringFromKey("PabloBarades_90", npchar.quest.seekIdx.where),
										StringFromKey("PabloBarades_91", npchar.quest.seekIdx.where),
										StringFromKey("PabloBarades_92", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("PabloBarades_96", RandPhraseSimple(
								StringFromKey("PabloBarades_94"),
								StringFromKey("PabloBarades_95")));
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
							dialog.text = StringFromKey("PabloBarades_100", LinkRandPhrase(
										StringFromKey("PabloBarades_97"),
										StringFromKey("PabloBarades_98"),
										StringFromKey("PabloBarades_99")));
						}
						else
						{
							dialog.text = StringFromKey("PabloBarades_104", LinkRandPhrase(
										StringFromKey("PabloBarades_101", npchar.quest.seekIdx.where),
										StringFromKey("PabloBarades_102", npchar.quest.seekIdx.where),
										StringFromKey("PabloBarades_103", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("PabloBarades_108", LinkRandPhrase(
										StringFromKey("PabloBarades_105", npchar.quest.seekIdx.where),
										StringFromKey("PabloBarades_106"),
										StringFromKey("PabloBarades_107")));
						}
						else
						{
							dialog.text = StringFromKey("PabloBarades_112", LinkRandPhrase(
										StringFromKey("PabloBarades_109", npchar.quest.seekIdx.where),
										StringFromKey("PabloBarades_110", npchar.quest.seekIdx.where),
										StringFromKey("PabloBarades_111", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("PabloBarades_115", RandPhraseSimple(
								StringFromKey("PabloBarades_113"),
								StringFromKey("PabloBarades_114")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("PabloBarades_116");
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("PabloBarades_117");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l2 = StringFromKey("PabloBarades_118");
				link.l2.go = "ansewer_2";
			}
			link.l10 = StringFromKey("PabloBarades_119");
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("PabloBarades_120", pchar);
			link.l1 = StringFromKey("PabloBarades_121");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("PabloBarades_122");
			link.l1 = StringFromKey("PabloBarades_123");
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = StringFromKey("PabloBarades_124");
			link.l1 = StringFromKey("PabloBarades_125");
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PabloBarades_126"),
						StringFromKey("PabloBarades_127"),
						StringFromKey("PabloBarades_128"),
						StringFromKey("PabloBarades_129"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PabloBarades_130"),
						StringFromKey("PabloBarades_131"),
						StringFromKey("PabloBarades_132"),
						StringFromKey("PabloBarades_133"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("PabloBarades_134");
			link.l1 = StringFromKey("PabloBarades_135");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = StringFromKey("PabloBarades_136");
			link.l1 = StringFromKey("PabloBarades_137");
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			AddQuestRecord("ISS_MainLine", "47");
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = StringFromKey("PabloBarades_138");
			link.l1 = StringFromKey("PabloBarades_139");
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("PabloBarades_140");
			link.l1 = StringFromKey("PabloBarades_141");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("PabloBarades_142");
			link.l1 = StringFromKey("PabloBarades_143");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("PabloBarades_144");
			link.l1 = StringFromKey("PabloBarades_145");
			link.l1.go = "SeekCrew_4";
		break;
		case "SeekCrew_4":
			dialog.text = StringFromKey("PabloBarades_146");
			link.l1 = StringFromKey("PabloBarades_147");
			link.l1.go = "SeekCrew_5";
		break;
		case "SeekCrew_5":
			dialog.text = StringFromKey("PabloBarades_148");
			link.l1 = StringFromKey("PabloBarades_149");
			link.l1.go = "SeekCrew_all";
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("PabloBarades_150");
			link.l1 = StringFromKey("PabloBarades_151");
			link.l1.go = "GoodBye_1";
		break;
		case "GoodBye_1":
			dialog.text = StringFromKey("PabloBarades_152");
			link.l1 = StringFromKey("PabloBarades_153");
			link.l1.go = "GoodBye_2";
		break;
		case "GoodBye_2":
			dialog.text = StringFromKey("PabloBarades_154");
			link.l1 = StringFromKey("PabloBarades_155");
			link.l1.go = "Exit_GoodBye";
			AddItems(pchar, "jewelry11", 30); // Добавляем 30 кораллов в инвентарь героя
		break;
	}
	NextDiag.PrevNode = NodeName;
}
