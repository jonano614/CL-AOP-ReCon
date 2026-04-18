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
					dialog.text = StringFromKey("MonikaRight_1", GetAddress_Form(NPChar), GetFullName(npchar));
					link.l1 = StringFromKey("MonikaRight_2", pchar, GetFullName(pchar));
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = StringFromKey("MonikaRight_3", pchar, GetAddress_Form(NPChar), GetFullName(npchar));
					link.l1 = StringFromKey("MonikaRight_4", pchar, GetFullName(pchar));
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("MonikaRight_5", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("MonikaRight_6");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("MonikaRight_7", pchar);
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("MonikaRight_11", LinkRandPhrase(
							StringFromKey("MonikaRight_8"),
							StringFromKey("MonikaRight_9"),
							StringFromKey("MonikaRight_10", pchar)));
				link.l3.go = "rumours_LSC";
				//покупка карты
				sld = characterFromId("LSC_Trader");
				if (CheckAttribute(sld, "quest.takeMap") && sld.quest.takeMap == "notTrade" && sld.quest.takeMap != "discount" && !CheckCharacterItem(pchar, "map_LSC"))
				{
					link.l4 = StringFromKey("MonikaRight_12");
					link.l4.go = "takeMap";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (pchar.questTemp.LSC == "toSeekCrewInTavern") dialog.text = StringFromKey("MonikaRight_13"); //сбор в таверне
					link.l8 = StringFromKey("MonikaRight_14");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("MonikaRight_15");
				link.l10.go = "exit";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "FS_1":
			dialog.text = StringFromKey("MonikaRight_16");
			link.l1 = StringFromKey("MonikaRight_17");
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = StringFromKey("MonikaRight_18");
			link.l1 = StringFromKey("MonikaRight_19", pchar);
			link.l1.go = "FT_2";
		break;

		case "FT_1":
			dialog.text = StringFromKey("MonikaRight_20");
			link.l1 = StringFromKey("MonikaRight_21");
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = StringFromKey("MonikaRight_22");
			link.l1 = StringFromKey("MonikaRight_23", pchar);
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = StringFromKey("MonikaRight_24");
			link.l1 = StringFromKey("MonikaRight_25");
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
			dialog.text = StringFromKey("MonikaRight_29", LinkRandPhrase(
						StringFromKey("MonikaRight_26", pchar),
						StringFromKey("MonikaRight_27", pchar),
						StringFromKey("MonikaRight_28", pchar)));
			link.l1 = StringFromKey("MonikaRight_30");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("MonikaRight_31");
			link.l1 = StringFromKey("MonikaRight_32");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("MonikaRight_36", LinkRandPhrase(
						StringFromKey("MonikaRight_33", pchar),
						StringFromKey("MonikaRight_34"),
						StringFromKey("MonikaRight_35", pchar)));
			link.l1 = StringFromKey("MonikaRight_40", LinkRandPhrase(
						StringFromKey("MonikaRight_37"),
						StringFromKey("MonikaRight_38"),
						StringFromKey("MonikaRight_39")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("MonikaRight_41", npchar);
				link.l1 = StringFromKey("MonikaRight_45", LinkRandPhrase(
							StringFromKey("MonikaRight_42"),
							StringFromKey("MonikaRight_43"),
							StringFromKey("MonikaRight_44")));
			}
			else
			{
				dialog.text = StringFromKey("MonikaRight_46", npchar);
				link.l1 = StringFromKey("MonikaRight_49", RandPhraseSimple(
							StringFromKey("MonikaRight_47", pchar),
							StringFromKey("MonikaRight_48")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("MonikaRight_50");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("MonikaRight_51");
				Link.l1 = StringFromKey("MonikaRight_52");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("MonikaRight_53", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("MonikaRight_54");
					link.l1 = StringFromKey("MonikaRight_55");
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("MonikaRight_56", GetFullName(sld));
					Link.l1 = StringFromKey("MonikaRight_57");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("MonikaRight_58");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("MonikaRight_59", GetFullName(sld));
					Link.l1 = StringFromKey("MonikaRight_60");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("MonikaRight_61");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("MonikaRight_62", pchar);
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("MonikaRight_63");
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
					dialog.text = StringFromKey("MonikaRight_67", LinkRandPhrase(
								StringFromKey("MonikaRight_64"),
								StringFromKey("MonikaRight_65"),
								StringFromKey("MonikaRight_66")));
					link.l1 = StringFromKey("MonikaRight_70", RandPhraseSimple(
								StringFromKey("MonikaRight_68"),
								StringFromKey("MonikaRight_69")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("MonikaRight_74", LinkRandPhrase(
								StringFromKey("MonikaRight_71"),
								StringFromKey("MonikaRight_72"),
								StringFromKey("MonikaRight_73")));
					link.l1 = StringFromKey("MonikaRight_77", RandPhraseSimple(
								StringFromKey("MonikaRight_75"),
								StringFromKey("MonikaRight_76")));
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
							dialog.text = StringFromKey("MonikaRight_81", LinkRandPhrase(
										StringFromKey("MonikaRight_78"),
										StringFromKey("MonikaRight_79"),
										StringFromKey("MonikaRight_80")));
						}
						else
						{
							dialog.text = StringFromKey("MonikaRight_85", LinkRandPhrase(
										StringFromKey("MonikaRight_82", npchar.quest.seekIdx.where),
										StringFromKey("MonikaRight_83", npchar.quest.seekIdx.where),
										StringFromKey("MonikaRight_84", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("MonikaRight_89", LinkRandPhrase(
										StringFromKey("MonikaRight_86", pchar, npchar.quest.seekIdx.where),
										StringFromKey("MonikaRight_87"),
										StringFromKey("MonikaRight_88")));
						}
						else
						{
							dialog.text = StringFromKey("MonikaRight_93", LinkRandPhrase(
										StringFromKey("MonikaRight_90", npchar.quest.seekIdx.where),
										StringFromKey("MonikaRight_91", npchar.quest.seekIdx.where),
										StringFromKey("MonikaRight_92", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("MonikaRight_96", RandPhraseSimple(
								StringFromKey("MonikaRight_94"),
								StringFromKey("MonikaRight_95")));
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
							dialog.text = StringFromKey("MonikaRight_100", LinkRandPhrase(
										StringFromKey("MonikaRight_97"),
										StringFromKey("MonikaRight_98"),
										StringFromKey("MonikaRight_99")));
						}
						else
						{
							dialog.text = StringFromKey("MonikaRight_104", LinkRandPhrase(
										StringFromKey("MonikaRight_101", npchar.quest.seekIdx.where),
										StringFromKey("MonikaRight_102", npchar.quest.seekIdx.where),
										StringFromKey("MonikaRight_103", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("MonikaRight_108", LinkRandPhrase(
										StringFromKey("MonikaRight_105", npchar.quest.seekIdx.where),
										StringFromKey("MonikaRight_106"),
										StringFromKey("MonikaRight_107")));
						}
						else
						{
							dialog.text = StringFromKey("MonikaRight_112", LinkRandPhrase(
										StringFromKey("MonikaRight_109", npchar.quest.seekIdx.where),
										StringFromKey("MonikaRight_110", npchar.quest.seekIdx.where),
										StringFromKey("MonikaRight_111", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("MonikaRight_115", RandPhraseSimple(
								StringFromKey("MonikaRight_113"),
								StringFromKey("MonikaRight_114")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("MonikaRight_116");
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("MonikaRight_117");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l2 = StringFromKey("MonikaRight_118");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l3"))
			{
				link.l3 = StringFromKey("MonikaRight_119");
				link.l3.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l4"))
			{
				link.l4 = StringFromKey("MonikaRight_120");
				link.l4.go = "ansewer_6";
			}
			link.l10 = StringFromKey("MonikaRight_121");
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("MonikaRight_122");
			link.l1 = StringFromKey("MonikaRight_123");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("MonikaRight_124");
			link.l1 = StringFromKey("MonikaRight_125");
			link.l1.go = "ansewer_3";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("MonikaRight_126");
			link.l1 = StringFromKey("MonikaRight_127");
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = StringFromKey("MonikaRight_128");
			link.l1 = StringFromKey("MonikaRight_129");
			link.l1.go = "ansewer_5";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_5":
			dialog.text = StringFromKey("MonikaRight_130", GetFullName(pchar));
			link.l1 = StringFromKey("MonikaRight_131");
			link.l1.go = "int_quests";
		break;
		case "ansewer_6":
			dialog.text = StringFromKey("MonikaRight_132");
			link.l1 = StringFromKey("MonikaRight_133");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l4 = true;
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = StringFromKey("MonikaRight_134");
			link.l1 = StringFromKey("MonikaRight_135");
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("MonikaRight_136");
			link.l1 = StringFromKey("MonikaRight_137");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("MonikaRight_138");
			link.l1 = StringFromKey("MonikaRight_139");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("MonikaRight_140");
			link.l1 = StringFromKey("MonikaRight_141");
			link.l1.go = "SeekCrew_all";
		break;
		//квест получения карты
		case "TakeMap":
			dialog.text = StringFromKey("MonikaRight_142");
			link.l1 = StringFromKey("MonikaRight_143");
			link.l1.go = "TakeMap_1";
		break;
		case "TakeMap_1":
			dialog.text = StringFromKey("MonikaRight_144");
			link.l1 = StringFromKey("MonikaRight_145");
			link.l1.go = "TakeMap_2";
		break;
		case "TakeMap_2":
			dialog.text = StringFromKey("MonikaRight_146");
			link.l1 = StringFromKey("MonikaRight_147");
			link.l1.go = "TakeMap_3";
		break;
		case "TakeMap_3":
			dialog.text = StringFromKey("MonikaRight_148");
			link.l1 = StringFromKey("MonikaRight_149");
			link.l1.go = "TakeMap_4";
		break;
		case "TakeMap_4":
			dialog.text = StringFromKey("MonikaRight_150");
			link.l1 = StringFromKey("MonikaRight_151");
			link.l1.go = "TakeMap_5";
		break;
		case "TakeMap_5":
			dialog.text = StringFromKey("MonikaRight_152");
			link.l1 = StringFromKey("MonikaRight_153");
			link.l1.go = "exit";
			sld = characterFromId("LSC_Trader");
			sld.quest.takeMap = "discount";
			sld.quest.takeMap.checkDate = LastSpeakDate();
			sld.quest.takeMap.name = GetFullName(npchar);
			AddQuestRecord("FindMapLSC", "6");
			LSC_FindMapLSC_RemoveQuestMarksToWoman();
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("MonikaRight_154", GetFullName(pchar));
			link.l1 = StringFromKey("MonikaRight_155", pchar);
			link.l1.go = "GoodBye_1";
		break;
		case "GoodBye_1":
			dialog.text = StringFromKey("MonikaRight_156");
			link.l1 = StringFromKey("MonikaRight_157");
			link.l1.go = "Exit_GoodBye";
			GiveItem2Character(pchar, "indian17");
		break;
	}
	NextDiag.PrevNode = NodeName;
}
