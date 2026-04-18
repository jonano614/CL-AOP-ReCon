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
			//после драки, когда Сесил пытаются убить
			if (pchar.questTemp.LSC == "toKnowAboutMechanic")
			{
				dialog.text = StringFromKey("SesilGalard_1");
				link.l1 = StringFromKey("SesilGalard_2");
				link.l1.go = "AfterFight";
				break;
			}

			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					if (npchar.location == "AvaShipInside3") dialog.text = StringFromKey("SesilGalard_3");
					else dialog.text = StringFromKey("SesilGalard_4");
					link.l1 = StringFromKey("SesilGalard_5", GetFullName(pchar));
					link.l1.go = "FT_1";
				}
				else
				{
					if (npchar.location == "AvaShipInside3") dialog.text = StringFromKey("SesilGalard_6");
					else dialog.text = StringFromKey("SesilGalard_7");
					link.l1 = StringFromKey("SesilGalard_8", GetFullName(pchar));
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("SesilGalard_9");
				link.l1 = StringFromKey("SesilGalard_10");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("SesilGalard_11", pchar);
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("SesilGalard_15", LinkRandPhrase(
							StringFromKey("SesilGalard_12"),
							StringFromKey("SesilGalard_13"),
							StringFromKey("SesilGalard_14")));
				link.l3.go = "rumours_LSC";
				//квест покупка карты
				sld = characterFromId("LSC_Trader");
				if (CheckAttribute(sld, "quest.takeMap") && sld.quest.takeMap == "notTrade" &&
				!CheckAttribute(pchar, "questTemp.FindMapLSC.toMonika") && !CheckCharacterItem(pchar, "map_LSC"))
				{
					link.l4 = StringFromKey("SesilGalard_16");
					link.l4.go = "takeMap";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					link.l8 = StringFromKey("SesilGalard_17");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("SesilGalard_18");
				link.l10.go = "exit";
			}
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
			dialog.text = StringFromKey("SesilGalard_22", LinkRandPhrase(
						StringFromKey("SesilGalard_19", pchar),
						StringFromKey("SesilGalard_20", pchar),
						StringFromKey("SesilGalard_21", pchar)));
			link.l1 = StringFromKey("SesilGalard_23");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("SesilGalard_24");
			link.l1 = StringFromKey("SesilGalard_25");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("SesilGalard_29", LinkRandPhrase(
						StringFromKey("SesilGalard_26", pchar),
						StringFromKey("SesilGalard_27"),
						StringFromKey("SesilGalard_28", pchar)));
			link.l1 = StringFromKey("SesilGalard_33", LinkRandPhrase(
						StringFromKey("SesilGalard_30"),
						StringFromKey("SesilGalard_31"),
						StringFromKey("SesilGalard_32")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("SesilGalard_34", npchar);
				link.l1 = StringFromKey("SesilGalard_38", LinkRandPhrase(
							StringFromKey("SesilGalard_35"),
							StringFromKey("SesilGalard_36"),
							StringFromKey("SesilGalard_37")));
			}
			else
			{
				dialog.text = StringFromKey("SesilGalard_39", npchar);
				link.l1 = StringFromKey("SesilGalard_42", RandPhraseSimple(
							StringFromKey("SesilGalard_40", pchar),
							StringFromKey("SesilGalard_41")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		case "FS_1":
			dialog.text = StringFromKey("SesilGalard_43", GetFullName(npchar));
			link.l1 = StringFromKey("SesilGalard_44");
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = StringFromKey("SesilGalard_45");
			link.l1 = StringFromKey("SesilGalard_46");
			link.l1.go = "FS_3";
		break;
		case "FS_3":
			dialog.text = StringFromKey("SesilGalard_47");
			link.l1 = StringFromKey("SesilGalard_48");
			link.l1.go = "FS_4";
		break;
		case "FS_4":
			dialog.text = StringFromKey("SesilGalard_49", pchar);
			link.l1 = StringFromKey("SesilGalard_50");
			link.l1.go = "exit";
		break;

		case "FT_1":
			dialog.text = StringFromKey("SesilGalard_51", GetFullName(npchar));
			link.l1 = StringFromKey("SesilGalard_52");
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = StringFromKey("SesilGalard_53");
			link.l1 = StringFromKey("SesilGalard_54");
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = StringFromKey("SesilGalard_55");
			link.l1 = StringFromKey("SesilGalard_56");
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = StringFromKey("SesilGalard_57");
			link.l1 = StringFromKey("SesilGalard_58");
			link.l1.go = "exit";
		break;
		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("SesilGalard_59");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("SesilGalard_60");
				Link.l1 = StringFromKey("SesilGalard_61");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("SesilGalard_62", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("SesilGalard_63");
					link.l1 = StringFromKey("SesilGalard_64");
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("SesilGalard_65", GetFullName(sld));
					Link.l1 = StringFromKey("SesilGalard_66");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("SesilGalard_67", pchar);
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("SesilGalard_68", GetFullName(sld));
					Link.l1 = StringFromKey("SesilGalard_69");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("SesilGalard_70");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("SesilGalard_71", pchar);
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("SesilGalard_72");
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
					dialog.text = StringFromKey("SesilGalard_76", LinkRandPhrase(
								StringFromKey("SesilGalard_73"),
								StringFromKey("SesilGalard_74"),
								StringFromKey("SesilGalard_75")));
					link.l1 = StringFromKey("SesilGalard_79", RandPhraseSimple(
								StringFromKey("SesilGalard_77"),
								StringFromKey("SesilGalard_78")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("SesilGalard_83", LinkRandPhrase(
								StringFromKey("SesilGalard_80"),
								StringFromKey("SesilGalard_81"),
								StringFromKey("SesilGalard_82")));
					link.l1 = StringFromKey("SesilGalard_86", RandPhraseSimple(
								StringFromKey("SesilGalard_84"),
								StringFromKey("SesilGalard_85")));
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
							dialog.text = StringFromKey("SesilGalard_90", LinkRandPhrase(
										StringFromKey("SesilGalard_87"),
										StringFromKey("SesilGalard_88"),
										StringFromKey("SesilGalard_89")));
						}
						else
						{
							dialog.text = StringFromKey("SesilGalard_94", LinkRandPhrase(
										StringFromKey("SesilGalard_91", npchar.quest.seekIdx.where),
										StringFromKey("SesilGalard_92", npchar.quest.seekIdx.where),
										StringFromKey("SesilGalard_93", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("SesilGalard_98", LinkRandPhrase(
										StringFromKey("SesilGalard_95", pchar, npchar.quest.seekIdx.where),
										StringFromKey("SesilGalard_96"),
										StringFromKey("SesilGalard_97")));
						}
						else
						{
							dialog.text = StringFromKey("SesilGalard_102", LinkRandPhrase(
										StringFromKey("SesilGalard_99", npchar.quest.seekIdx.where),
										StringFromKey("SesilGalard_100", npchar.quest.seekIdx.where),
										StringFromKey("SesilGalard_101", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("SesilGalard_105", RandPhraseSimple(
								StringFromKey("SesilGalard_103"),
								StringFromKey("SesilGalard_104")));
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
							dialog.text = StringFromKey("SesilGalard_109", LinkRandPhrase(
										StringFromKey("SesilGalard_106"),
										StringFromKey("SesilGalard_107"),
										StringFromKey("SesilGalard_108")));
						}
						else
						{
							dialog.text = StringFromKey("SesilGalard_113", LinkRandPhrase(
										StringFromKey("SesilGalard_110", npchar.quest.seekIdx.where),
										StringFromKey("SesilGalard_111", npchar.quest.seekIdx.where),
										StringFromKey("SesilGalard_112", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("SesilGalard_117", LinkRandPhrase(
										StringFromKey("SesilGalard_114", pchar, npchar.quest.seekIdx.where),
										StringFromKey("SesilGalard_115"),
										StringFromKey("SesilGalard_116")));
						}
						else
						{
							dialog.text = StringFromKey("SesilGalard_121", LinkRandPhrase(
										StringFromKey("SesilGalard_118", npchar.quest.seekIdx.where),
										StringFromKey("SesilGalard_119", npchar.quest.seekIdx.where),
										StringFromKey("SesilGalard_120", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("SesilGalard_124", RandPhraseSimple(
								StringFromKey("SesilGalard_122"),
								StringFromKey("SesilGalard_123")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("SesilGalard_125");
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("SesilGalard_126");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("SesilGalard_127");
				link.l2.go = "ansewer_2";
			}
			link.l10 = StringFromKey("SesilGalard_128");
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("SesilGalard_129", pchar);
			link.l1 = StringFromKey("SesilGalard_130", pchar);
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = StringFromKey("SesilGalard_131", pchar);
			link.l1 = StringFromKey("SesilGalard_132");
			link.l1.go = "ansewer_1_2";
		break;
		case "ansewer_1_2":
			dialog.text = StringFromKey("SesilGalard_133", pchar);
			link.l1 = StringFromKey("SesilGalard_134");
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("SesilGalard_135", pchar);
			link.l1 = StringFromKey("SesilGalard_136");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		//квесты
		case "HelpMe":
			dialog.text = StringFromKey("SesilGalard_137");
			link.l1 = StringFromKey("SesilGalard_138");
			link.l1.go = "HelpMe_1";
		break;
		case "HelpMe_1":
			dialog.text = StringFromKey("SesilGalard_139");
			link.l1 = StringFromKey("SesilGalard_140");
			link.l1.go = "exit";
			npchar.quest.meeting = "1";
			AddDialogExitQuestFunction("LSC_SaveSesilGalard_2");
		break;

		case "AfterFight":
			dialog.text = StringFromKey("SesilGalard_141");
			link.l1 = StringFromKey("SesilGalard_142");
			link.l1.go = "AfterFight_1";
		break;
		case "AfterFight_1":
			dialog.text = StringFromKey("SesilGalard_143");
			link.l1 = StringFromKey("SesilGalard_144");
			link.l1.go = "AfterFight_2";
			npchar.greeting = "Gr_Woman_Citizen";
		break;
		case "AfterFight_2":
			dialog.text = StringFromKey("SesilGalard_145", pchar);
			link.l1 = StringFromKey("SesilGalard_146");
			link.l1.go = "AfterFight_3";
		break;
		case "AfterFight_3":
			dialog.text = StringFromKey("SesilGalard_147");
			link.l1 = StringFromKey("SesilGalard_148");
			link.l1.go = "AfterFight_4";
		break;
		case "AfterFight_4":
			dialog.text = StringFromKey("SesilGalard_149");
			link.l1 = StringFromKey("SesilGalard_150");
			link.l1.go = "AfterFight_5";
		break;
		case "AfterFight_5":
			dialog.text = StringFromKey("SesilGalard_151");
			link.l1 = StringFromKey("SesilGalard_152");
			link.l1.go = "AfterFight_6";
		break;
		case "AfterFight_6":
			dialog.text = StringFromKey("SesilGalard_153");
			link.l1 = StringFromKey("SesilGalard_154");
			link.l1.go = "AfterFight_7";
		break;
		case "AfterFight_7":
			dialog.text = StringFromKey("SesilGalard_155");
			link.l1 = StringFromKey("SesilGalard_156");
			link.l1.go = "AfterFight_8";
		break;
		case "AfterFight_8":
			dialog.text = StringFromKey("SesilGalard_157");
			link.l1 = StringFromKey("SesilGalard_158");
			link.l1.go = "AfterFight_9";
		break;
		case "AfterFight_9":
			dialog.text = StringFromKey("SesilGalard_159");
			link.l1 = StringFromKey("SesilGalard_160");
			link.l1.go = "AfterFight_10";
		break;
		case "AfterFight_10":
			dialog.text = StringFromKey("SesilGalard_161");
			link.l1 = StringFromKey("SesilGalard_162");
			link.l1.go = "AfterFight_11";
		break;
		case "AfterFight_11":
			dialog.text = StringFromKey("SesilGalard_163");
			link.l1 = StringFromKey("SesilGalard_164");
			link.l1.go = "AfterFight_12";
		break;
		case "AfterFight_12":
			dialog.text = StringFromKey("SesilGalard_165");
			link.l1 = StringFromKey("SesilGalard_166");
			link.l1.go = "AfterFight_13";
		break;
		case "AfterFight_13":
			dialog.text = StringFromKey("SesilGalard_167");
			link.l1 = StringFromKey("SesilGalard_168");
			link.l1.go = "AfterFight_14";
		break;
		case "AfterFight_14":
			dialog.text = StringFromKey("SesilGalard_169");
			link.l1 = StringFromKey("SesilGalard_170", pchar);
			link.l1.go = "AfterFight_15";
		break;
		case "AfterFight_15":
			dialog.text = StringFromKey("SesilGalard_171");
			link.l1 = StringFromKey("SesilGalard_172");
			link.l1.go = "AfterFight_16";
		break;
		case "AfterFight_16":
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.cityTape = "citizenHome";
			pchar.questTemp.LSC = "toSeekMechanik";
			AddQuestRecord("ISS_MainLine", "32");
			AddLandQuestMark_Main(CharacterFromID("Mechanic"), "ISS_MainLine");
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
			pchar.quest.LSC_enterCasper.win_condition.l1 = "location";
			pchar.quest.LSC_enterCasper.win_condition.l1.location = "SanGabrielMechanic";
			pchar.quest.LSC_enterCasper.function = "LSC_enterCasper";
			sld = characterFromID("Casper_head");
			LAi_SetImmortal(sld, false);
			for (int i = 1; i <= 11; i++)
			{
				sld = characterFromID("Casper_" + i);
				LAi_SetImmortal(sld, false);
			}
			AddQuestRecord("ISS_DefeatCasperClan", "1");
			AddLandQuestMark_Main(CharacterFromID("LSCwaitress"), "ISS_DefeatCasperClan");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SesilGalard_173"),
						StringFromKey("SesilGalard_174"),
						StringFromKey("SesilGalard_175"),
						StringFromKey("SesilGalard_176"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SesilGalard_177"),
						StringFromKey("SesilGalard_178", pchar),
						StringFromKey("SesilGalard_179"),
						StringFromKey("SesilGalard_180"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("SesilGalard_181");
			link.l1 = StringFromKey("SesilGalard_182");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("SesilGalard_183");
			link.l1 = StringFromKey("SesilGalard_184", pchar);
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("SesilGalard_185");
			link.l1 = StringFromKey("SesilGalard_186");
			link.l1.go = "SeekCrew_4";
		break;
		case "SeekCrew_4":
			dialog.text = StringFromKey("SesilGalard_187");
			link.l1 = StringFromKey("SesilGalard_188");
			link.l1.go = "exit";
		break;
		//квест получения карты
		case "TakeMap":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SesilGalard_189"),
						StringFromKey("SesilGalard_190", pchar),
						StringFromKey("SesilGalard_191"),
						StringFromKey("SesilGalard_192"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SesilGalard_193"),
						StringFromKey("SesilGalard_194", pchar),
						StringFromKey("SesilGalard_195"),
						StringFromKey("SesilGalard_196"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("TakeMap_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "TakeMap_1":
			dialog.text = StringFromKey("SesilGalard_197", pchar);
			link.l1 = StringFromKey("SesilGalard_198");
			link.l1.go = "exit";
			RemoveLandQuestMark_Main(npchar, "FindMapLSC");
		break;
	}
	NextDiag.PrevNode = NodeName;
}
