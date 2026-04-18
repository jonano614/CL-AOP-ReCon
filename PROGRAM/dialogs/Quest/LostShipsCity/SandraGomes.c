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
					dialog.text = StringFromKey("SandraGomes_1", pchar, GetAddress_Form(NPChar));
					link.l1 = StringFromKey("SandraGomes_2", GetFullName(pchar));
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = StringFromKey("SandraGomes_3", pchar, GetAddress_Form(NPChar));
					link.l1 = StringFromKey("SandraGomes_4", GetFullName(pchar));
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("SandraGomes_5", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("SandraGomes_6");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("SandraGomes_7", pchar);
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("SandraGomes_11", LinkRandPhrase(
							StringFromKey("SandraGomes_8"),
							StringFromKey("SandraGomes_9"),
							StringFromKey("SandraGomes_10", pchar)));
				link.l3.go = "rumours_LSC";
				//квест покупка карты
				sld = characterFromId("LSC_Trader");
				if (CheckAttribute(sld, "quest.takeMap") && sld.quest.takeMap == "notTrade" &&
				!CheckAttribute(pchar, "questTemp.FindMapLSC.toMonika") && !CheckCharacterItem(pchar, "map_LSC"))
				{
					link.l4 = StringFromKey("SandraGomes_12");
					link.l4.go = "takeMap";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (pchar.questTemp.LSC == "toSeekCrewInTavern") dialog.text = StringFromKey("SandraGomes_13"); //сбор в таверне
					link.l8 = StringFromKey("SandraGomes_14");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("SandraGomes_15");
				link.l10.go = "exit";
			}
		break;
		case "FS_1":
			dialog.text = StringFromKey("SandraGomes_16", GetFullName(npchar));
			link.l1 = StringFromKey("SandraGomes_17");
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = StringFromKey("SandraGomes_18", GetFullName(npchar));
			link.l1 = StringFromKey("SandraGomes_19");
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
			dialog.text = StringFromKey("SandraGomes_23", LinkRandPhrase(
						StringFromKey("SandraGomes_20", pchar),
						StringFromKey("SandraGomes_21", pchar),
						StringFromKey("SandraGomes_22", pchar)));
			link.l1 = StringFromKey("SandraGomes_24");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("SandraGomes_25");
			link.l1 = StringFromKey("SandraGomes_26");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("SandraGomes_30", LinkRandPhrase(
						StringFromKey("SandraGomes_27", pchar),
						StringFromKey("SandraGomes_28"),
						StringFromKey("SandraGomes_29", pchar)));
			link.l1 = StringFromKey("SandraGomes_34", LinkRandPhrase(
						StringFromKey("SandraGomes_31"),
						StringFromKey("SandraGomes_32"),
						StringFromKey("SandraGomes_33")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("SandraGomes_35", npchar);
				link.l1 = StringFromKey("SandraGomes_39", LinkRandPhrase(
							StringFromKey("SandraGomes_36"),
							StringFromKey("SandraGomes_37"),
							StringFromKey("SandraGomes_38")));
			}
			else
			{
				dialog.text = StringFromKey("SandraGomes_40", npchar);
				link.l1 = StringFromKey("SandraGomes_43", RandPhraseSimple(
							StringFromKey("SandraGomes_41", pchar),
							StringFromKey("SandraGomes_42")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("SandraGomes_44");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("SandraGomes_45");
				Link.l1 = StringFromKey("SandraGomes_46");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("SandraGomes_47", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("SandraGomes_48");
					link.l1 = StringFromKey("SandraGomes_49");
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("SandraGomes_50", GetFullName(sld));
					Link.l1 = StringFromKey("SandraGomes_51");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("SandraGomes_52", pchar);
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("SandraGomes_53", GetFullName(sld));
					Link.l1 = StringFromKey("SandraGomes_54");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("SandraGomes_55");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("SandraGomes_56", pchar);
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("SandraGomes_57");
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
					dialog.text = StringFromKey("SandraGomes_61", LinkRandPhrase(
								StringFromKey("SandraGomes_58"),
								StringFromKey("SandraGomes_59"),
								StringFromKey("SandraGomes_60")));
					link.l1 = StringFromKey("SandraGomes_64", RandPhraseSimple(
								StringFromKey("SandraGomes_62"),
								StringFromKey("SandraGomes_63")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("SandraGomes_68", LinkRandPhrase(
								StringFromKey("SandraGomes_65"),
								StringFromKey("SandraGomes_66"),
								StringFromKey("SandraGomes_67")));
					link.l1 = StringFromKey("SandraGomes_71", RandPhraseSimple(
								StringFromKey("SandraGomes_69"),
								StringFromKey("SandraGomes_70")));
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
							dialog.text = StringFromKey("SandraGomes_75", LinkRandPhrase(
										StringFromKey("SandraGomes_72"),
										StringFromKey("SandraGomes_73"),
										StringFromKey("SandraGomes_74")));
						}
						else
						{
							dialog.text = StringFromKey("SandraGomes_79", LinkRandPhrase(
										StringFromKey("SandraGomes_76", npchar.quest.seekIdx.where),
										StringFromKey("SandraGomes_77", npchar.quest.seekIdx.where),
										StringFromKey("SandraGomes_78", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("SandraGomes_83", LinkRandPhrase(
										StringFromKey("SandraGomes_80", pchar, npchar.quest.seekIdx.where),
										StringFromKey("SandraGomes_81"),
										StringFromKey("SandraGomes_82")));
						}
						else
						{
							dialog.text = StringFromKey("SandraGomes_87", LinkRandPhrase(
										StringFromKey("SandraGomes_84", npchar.quest.seekIdx.where),
										StringFromKey("SandraGomes_85", npchar.quest.seekIdx.where),
										StringFromKey("SandraGomes_86", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("SandraGomes_90", RandPhraseSimple(
								StringFromKey("SandraGomes_88"),
								StringFromKey("SandraGomes_89")));
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
							dialog.text = StringFromKey("SandraGomes_94", LinkRandPhrase(
										StringFromKey("SandraGomes_91"),
										StringFromKey("SandraGomes_92"),
										StringFromKey("SandraGomes_93")));
						}
						else
						{
							dialog.text = StringFromKey("SandraGomes_98", LinkRandPhrase(
										StringFromKey("SandraGomes_95", npchar.quest.seekIdx.where),
										StringFromKey("SandraGomes_96", npchar.quest.seekIdx.where),
										StringFromKey("SandraGomes_97", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("SandraGomes_102", LinkRandPhrase(
										StringFromKey("SandraGomes_99", pchar, npchar.quest.seekIdx.where),
										StringFromKey("SandraGomes_100"),
										StringFromKey("SandraGomes_101")));
						}
						else
						{
							dialog.text = StringFromKey("SandraGomes_106", LinkRandPhrase(
										StringFromKey("SandraGomes_103", npchar.quest.seekIdx.where),
										StringFromKey("SandraGomes_104", npchar.quest.seekIdx.where),
										StringFromKey("SandraGomes_105", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("SandraGomes_109", RandPhraseSimple(
								StringFromKey("SandraGomes_107"),
								StringFromKey("SandraGomes_108")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("SandraGomes_110");
			if (!CheckAttribute(NextDiag, NodeName + ".l4"))
			{
				link.l4 = StringFromKey("SandraGomes_111");
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("SandraGomes_112");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("SandraGomes_113", GetAddress_FormToNPC(NPChar));
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l3"))
			{
				link.l3 = StringFromKey("SandraGomes_114");
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l5") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l5 = StringFromKey("SandraGomes_115");
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l6"))
			{
				link.l6 = StringFromKey("SandraGomes_116");
				link.l6.go = "ansewer_6";
			}
			link.l10 = StringFromKey("SandraGomes_117");
			link.l10.go = "exit";
		break;
		case "ansewer_4":
			dialog.text = StringFromKey("SandraGomes_118");
			link.l1 = StringFromKey("SandraGomes_119");
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = StringFromKey("SandraGomes_120", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("SandraGomes_121");
			link.l1.go = "int_quests";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("SandraGomes_122");
			link.l1 = StringFromKey("SandraGomes_123", pchar);
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = StringFromKey("SandraGomes_124");
			link.l1 = StringFromKey("SandraGomes_125");
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("SandraGomes_126");
			link.l1 = StringFromKey("SandraGomes_127");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("SandraGomes_128");
			link.l1 = StringFromKey("SandraGomes_129");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_5":
			dialog.text = StringFromKey("SandraGomes_130");
			link.l1 = StringFromKey("SandraGomes_131");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_6":
			dialog.text = StringFromKey("SandraGomes_132");
			link.l1 = StringFromKey("SandraGomes_133");
			link.l1.go = "ansewer_6_1";
			NextDiag.(NodePrevName).l6 = true;
		break;
		case "ansewer_6_1":
			dialog.text = StringFromKey("SandraGomes_134");
			link.l1 = StringFromKey("SandraGomes_135");
			link.l1.go = "int_quests";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = StringFromKey("SandraGomes_136");
			link.l1 = StringFromKey("SandraGomes_137");
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("SandraGomes_138");
			link.l1 = StringFromKey("SandraGomes_139");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("SandraGomes_140");
			link.l1 = StringFromKey("SandraGomes_141");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("SandraGomes_142");
			link.l1 = StringFromKey("SandraGomes_143");
			link.l1.go = "SeekCrew_4";
		break;
		case "SeekCrew_4":
			dialog.text = StringFromKey("SandraGomes_144");
			link.l1 = StringFromKey("SandraGomes_145");
			link.l1.go = "SeekCrew_all";
		break;
		//квест получения карты
		case "TakeMap":
			dialog.text = StringFromKey("SandraGomes_146");
			link.l1 = StringFromKey("SandraGomes_147");
			link.l1.go = "TakeMap_1";
		break;
		case "TakeMap_1":
			dialog.text = StringFromKey("SandraGomes_148");
			link.l1 = StringFromKey("SandraGomes_149");
			link.l1.go = "TakeMap_2";
		break;
		case "TakeMap_2":
			dialog.text = StringFromKey("SandraGomes_150");
			link.l1 = StringFromKey("SandraGomes_151");
			link.l1.go = "TakeMap_3";
		break;
		case "TakeMap_3":
			dialog.text = StringFromKey("SandraGomes_152");
			link.l1 = StringFromKey("SandraGomes_153");
			link.l1.go = "TakeMap_4";
		break;
		case "TakeMap_4":
			dialog.text = StringFromKey("SandraGomes_154");
			link.l1 = StringFromKey("SandraGomes_155");
			link.l1.go = "TakeMap_5";
		break;
		case "TakeMap_5":
			dialog.text = StringFromKey("SandraGomes_156");
			link.l1 = StringFromKey("SandraGomes_157");
			link.l1.go = "exit";
			AddQuestRecord("FindMapLSC", "5");
			pchar.questTemp.FindMapLSC.toMonika = true; //навешиваю, чтобы повторки не было.
			LSC_FindMapLSC_RemoveQuestMarksToWoman();
			AddLandQuestMark_Main(CharacterFromID("MonikaRight"), "FindMapLSC");
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("SandraGomes_158");
			link.l1 = StringFromKey("SandraGomes_159");
			link.l1.go = "GoodBye_1";
		break;

		case "GoodBye_1":
			dialog.text = StringFromKey("SandraGomes_160");
			link.l1 = StringFromKey("SandraGomes_161");
			link.l1.go = "GoodBye_2";
		break;

		case "GoodBye_2":
			dialog.text = StringFromKey("SandraGomes_162");
			link.l1 = StringFromKey("SandraGomes_163");
			link.l1.go = "Exit_GoodBye";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
