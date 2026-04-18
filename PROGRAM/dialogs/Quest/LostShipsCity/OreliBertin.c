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
			//если Сесил Галард замочили, то это оставшийся шанс узнать о Механике
			if (pchar.questTemp.LSC == "SessilIsDead")
			{
				dialog.text = StringFromKey("OreliBertin_1");
				link.l1 = StringFromKey("OreliBertin_2");
				link.l1.go = "SessilDead";
				npchar.quest.meeting = "1";
				break;
			}

			if (npchar.quest.meeting == "0" && pchar.questTemp.LSC != "toSeekCrewInTavern")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					if (npchar.location == "FurieShipInside2") dialog.text = StringFromKey("OreliBertin_3", GetFullName(npchar));
					else dialog.text = StringFromKey("OreliBertin_4", GetFullName(npchar));
					link.l1 = StringFromKey("OreliBertin_5", pchar, GetFullName(pchar));
					link.l1.go = "FS_1";
				}
				else
				{
					if (npchar.location == "FurieShipInside2") dialog.text = StringFromKey("OreliBertin_6", GetFullName(npchar));
					else dialog.text = StringFromKey("OreliBertin_7", GetFullName(npchar));
					link.l1 = StringFromKey("OreliBertin_8", pchar, GetFullName(pchar));
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("OreliBertin_9", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("OreliBertin_10");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("OreliBertin_11", pchar);
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("OreliBertin_15", LinkRandPhrase(
							StringFromKey("OreliBertin_12"),
							StringFromKey("OreliBertin_13"),
							StringFromKey("OreliBertin_14", pchar)));
				link.l3.go = "rumours_LSC";
				//квест покупка карты
				sld = characterFromId("LSC_Trader");
				if (CheckAttribute(sld, "quest.takeMap") && sld.quest.takeMap == "notTrade" &&
				!CheckAttribute(pchar, "questTemp.FindMapLSC.toMonika") && !CheckCharacterItem(pchar, "map_LSC"))
				{
					link.l4 = StringFromKey("OreliBertin_16");
					link.l4.go = "takeMap";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = StringFromKey("OreliBertin_17");
					link.l8.go = "SeekGoods";
				}
				//общий сбор в таверне
				if (pchar.questTemp.LSC == "toSeekPeopleInCrew")
				{
					link.l8 = StringFromKey("OreliBertin_18");
					link.l8.go = "CrewCollection";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (pchar.questTemp.LSC == "toSeekCrewInTavern") dialog.text = StringFromKey("OreliBertin_19"); //сбор в таверне
					link.l8 = StringFromKey("OreliBertin_20");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("OreliBertin_21");
				link.l10.go = "exit";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "FS_1":
			dialog.text = StringFromKey("OreliBertin_22");
			link.l1 = StringFromKey("OreliBertin_23");
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = StringFromKey("OreliBertin_24");
			link.l1 = StringFromKey("OreliBertin_25", pchar);
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
			dialog.text = StringFromKey("OreliBertin_29", LinkRandPhrase(
						StringFromKey("OreliBertin_26", pchar),
						StringFromKey("OreliBertin_27", pchar),
						StringFromKey("OreliBertin_28", pchar)));
			link.l1 = StringFromKey("OreliBertin_30");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("OreliBertin_31");
			link.l1 = StringFromKey("OreliBertin_32");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("OreliBertin_36", LinkRandPhrase(
						StringFromKey("OreliBertin_33", pchar),
						StringFromKey("OreliBertin_34"),
						StringFromKey("OreliBertin_35", pchar)));
			link.l1 = StringFromKey("OreliBertin_40", LinkRandPhrase(
						StringFromKey("OreliBertin_37"),
						StringFromKey("OreliBertin_38"),
						StringFromKey("OreliBertin_39")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("OreliBertin_41", npchar);
				link.l1 = StringFromKey("OreliBertin_45", LinkRandPhrase(
							StringFromKey("OreliBertin_42"),
							StringFromKey("OreliBertin_43"),
							StringFromKey("OreliBertin_44")));
			}
			else
			{
				dialog.text = StringFromKey("OreliBertin_46", npchar);
				link.l1 = StringFromKey("OreliBertin_49", RandPhraseSimple(
							StringFromKey("OreliBertin_47", pchar),
							StringFromKey("OreliBertin_48")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("OreliBertin_50");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("OreliBertin_51");
				Link.l1 = StringFromKey("OreliBertin_52");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("OreliBertin_53", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("OreliBertin_54");
					link.l1 = StringFromKey("OreliBertin_55");
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("OreliBertin_56", GetFullName(sld));
					Link.l1 = StringFromKey("OreliBertin_57");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("OreliBertin_58");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("OreliBertin_59", GetFullName(sld));
					Link.l1 = StringFromKey("OreliBertin_60");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("OreliBertin_61");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("OreliBertin_62", pchar);
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("OreliBertin_63");
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
					dialog.text = StringFromKey("OreliBertin_67", LinkRandPhrase(
								StringFromKey("OreliBertin_64"),
								StringFromKey("OreliBertin_65"),
								StringFromKey("OreliBertin_66")));
					link.l1 = StringFromKey("OreliBertin_70", RandPhraseSimple(
								StringFromKey("OreliBertin_68"),
								StringFromKey("OreliBertin_69")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("OreliBertin_74", LinkRandPhrase(
								StringFromKey("OreliBertin_71"),
								StringFromKey("OreliBertin_72"),
								StringFromKey("OreliBertin_73")));
					link.l1 = StringFromKey("OreliBertin_77", RandPhraseSimple(
								StringFromKey("OreliBertin_75"),
								StringFromKey("OreliBertin_76")));
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
							dialog.text = StringFromKey("OreliBertin_81", LinkRandPhrase(
										StringFromKey("OreliBertin_78"),
										StringFromKey("OreliBertin_79"),
										StringFromKey("OreliBertin_80")));
						}
						else
						{
							dialog.text = StringFromKey("OreliBertin_85", LinkRandPhrase(
										StringFromKey("OreliBertin_82", npchar.quest.seekIdx.where),
										StringFromKey("OreliBertin_83", npchar.quest.seekIdx.where),
										StringFromKey("OreliBertin_84", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("OreliBertin_89", LinkRandPhrase(
										StringFromKey("OreliBertin_86", pchar, npchar.quest.seekIdx.where),
										StringFromKey("OreliBertin_87"),
										StringFromKey("OreliBertin_88")));
						}
						else
						{
							dialog.text = StringFromKey("OreliBertin_93", LinkRandPhrase(
										StringFromKey("OreliBertin_90", npchar.quest.seekIdx.where),
										StringFromKey("OreliBertin_91", npchar.quest.seekIdx.where),
										StringFromKey("OreliBertin_92", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("OreliBertin_96", RandPhraseSimple(
								StringFromKey("OreliBertin_94"),
								StringFromKey("OreliBertin_95")));
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
							dialog.text = StringFromKey("OreliBertin_100", LinkRandPhrase(
										StringFromKey("OreliBertin_97"),
										StringFromKey("OreliBertin_98"),
										StringFromKey("OreliBertin_99")));
						}
						else
						{
							dialog.text = StringFromKey("OreliBertin_104", LinkRandPhrase(
										StringFromKey("OreliBertin_101", npchar.quest.seekIdx.where),
										StringFromKey("OreliBertin_102", npchar.quest.seekIdx.where),
										StringFromKey("OreliBertin_103", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("OreliBertin_108", LinkRandPhrase(
										StringFromKey("OreliBertin_105", npchar.quest.seekIdx.where),
										StringFromKey("OreliBertin_106"),
										StringFromKey("OreliBertin_107")));
						}
						else
						{
							dialog.text = StringFromKey("OreliBertin_112", LinkRandPhrase(
										StringFromKey("OreliBertin_109", npchar.quest.seekIdx.where),
										StringFromKey("OreliBertin_110", npchar.quest.seekIdx.where),
										StringFromKey("OreliBertin_111", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("OreliBertin_115", RandPhraseSimple(
								StringFromKey("OreliBertin_113"),
								StringFromKey("OreliBertin_114")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("OreliBertin_116");
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("OreliBertin_117");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("OreliBertin_118");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = StringFromKey("OreliBertin_119");
				link.l3.go = "ansewer_3";
			}
			link.l10 = StringFromKey("OreliBertin_120");
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("OreliBertin_121");
			link.l1 = StringFromKey("OreliBertin_122");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("OreliBertin_123");
			link.l1 = StringFromKey("OreliBertin_124");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("OreliBertin_125");
			link.l1 = StringFromKey("OreliBertin_126");
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = StringFromKey("OreliBertin_127");
			link.l1 = StringFromKey("OreliBertin_128");
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "31");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ся", "ась"));
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
			sld = CharacterFromId("Ment_6");
			if (CheckAttribute(sld, "quest.AngerAtAdmiral") && sti(sld.quest.AngerAtAdmiral) > 0)
			{
				sld.dialog.currentnode = "talkAboutSesil";
				PlaceCharacter(sld, "goto", "random");
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
				chrDisableReloadToLocation = true;
			}
		break;

		case "SessilDead":
			dialog.text = StringFromKey("OreliBertin_129");
			link.l1 = StringFromKey("OreliBertin_130", pchar);
			link.l1.go = "SessilDead_1";
		break;
		case "SessilDead_1":
			dialog.text = StringFromKey("OreliBertin_131");
			link.l1 = StringFromKey("OreliBertin_132");
			link.l1.go = "SessilDead_2";
		break;
		case "SessilDead_2":
			dialog.text = StringFromKey("OreliBertin_133");
			link.l1 = StringFromKey("OreliBertin_134");
			link.l1.go = "SessilDead_3";
		break;
		case "SessilDead_3":
			dialog.text = StringFromKey("OreliBertin_135");
			link.l1 = StringFromKey("OreliBertin_136");
			link.l1.go = "SessilDead_4";
		break;
		case "SessilDead_4":
			dialog.text = StringFromKey("OreliBertin_137");
			link.l1 = StringFromKey("OreliBertin_138");
			link.l1.go = "SessilDead_5";
		break;
		case "SessilDead_5":
			dialog.text = StringFromKey("OreliBertin_139");
			link.l1 = StringFromKey("OreliBertin_140");
			link.l1.go = "SessilDead_6";
		break;
		case "SessilDead_6":
			dialog.text = StringFromKey("OreliBertin_141");
			link.l1 = StringFromKey("OreliBertin_142");
			link.l1.go = "SessilDead_7";
		break;
		case "SessilDead_7":
			dialog.text = StringFromKey("OreliBertin_143");
			link.l1 = StringFromKey("OreliBertin_144");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toSeekMechanik";
			AddQuestRecord("ISS_MainLine", "33");
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
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("OreliBertin_145"),
						StringFromKey("OreliBertin_146"),
						StringFromKey("OreliBertin_147"),
						StringFromKey("OreliBertin_148"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("OreliBertin_149"),
						StringFromKey("OreliBertin_150", pchar),
						StringFromKey("OreliBertin_151"),
						StringFromKey("OreliBertin_152", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("OreliBertin_153");
			link.l1 = StringFromKey("OreliBertin_154");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = StringFromKey("OreliBertin_155");
			link.l1 = StringFromKey("OreliBertin_156", pchar);
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = StringFromKey("OreliBertin_157");
			link.l1 = StringFromKey("OreliBertin_158");
			link.l1.go = "exit";
			pchar.questTemp.LSC.additional.knippels = true;
			AddQuestRecord("ISS_MainLine", "46");
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("PabloBarades"), "ISS_MainLine");
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = StringFromKey("OreliBertin_159");
			link.l1 = StringFromKey("OreliBertin_160");
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("OreliBertin_161");
			link.l1 = StringFromKey("OreliBertin_162");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("OreliBertin_163");
			link.l1 = StringFromKey("OreliBertin_164");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("OreliBertin_165");
			link.l1 = StringFromKey("OreliBertin_166");
			link.l1.go = "SeekCrew_all";
		break;
		//общий сбор
		case "CrewCollection":
			dialog.text = StringFromKey("OreliBertin_167");
			link.l1 = StringFromKey("OreliBertin_168");
			link.l1.go = "CrewCollection_0";
		break;
		case "CrewCollection_0":
			dialog.text = StringFromKey("OreliBertin_169");
			link.l1 = StringFromKey("OreliBertin_170");
			link.l1.go = "CrewCollection_1";
		break;
		case "CrewCollection_1":
			dialog.text = StringFromKey("OreliBertin_171");
			link.l1 = StringFromKey("OreliBertin_172");
			link.l1.go = "CrewCollection_2";
		break;
		case "CrewCollection_2":
			dialog.text = StringFromKey("OreliBertin_173");
			link.l1 = StringFromKey("OreliBertin_174");
			link.l1.go = "CrewCollection_3";
		break;
		case "CrewCollection_3":
			dialog.text = StringFromKey("OreliBertin_175");
			link.l1 = StringFromKey("OreliBertin_176");
			link.l1.go = "CrewCollection_4";
		break;
		case "CrewCollection_4":
			dialog.text = StringFromKey("OreliBertin_177");
			link.l1 = StringFromKey("OreliBertin_178");
			link.l1.go = "CrewCollection_5";
		break;
		case "CrewCollection_5":
			dialog.text = StringFromKey("OreliBertin_179");
			link.l1 = StringFromKey("OreliBertin_180");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toCrewCollection";
			AddQuestRecord("ISS_MainLine", "67");
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("Mechanic"), "ISS_MainLine");
		break;
		//квест получения карты
		case "TakeMap":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("OreliBertin_181"),
						StringFromKey("OreliBertin_182"),
						StringFromKey("OreliBertin_183"),
						StringFromKey("OreliBertin_184"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("OreliBertin_185"),
						StringFromKey("OreliBertin_186", pchar),
						StringFromKey("OreliBertin_187"),
						StringFromKey("OreliBertin_188"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("TakeMap_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "TakeMap_1":
			dialog.text = StringFromKey("OreliBertin_189");
			link.l1 = StringFromKey("OreliBertin_190");
			link.l1.go = "TakeMap_2";
		break;
		case "TakeMap_2":
			dialog.text = StringFromKey("OreliBertin_191");
			link.l1 = StringFromKey("OreliBertin_192");
			link.l1.go = "TakeMap_3";
		break;
		case "TakeMap_3":
			dialog.text = StringFromKey("OreliBertin_193");
			link.l1 = StringFromKey("OreliBertin_194");
			link.l1.go = "TakeMap_4";
		break;
		case "TakeMap_4":
			dialog.text = StringFromKey("OreliBertin_195");
			link.l1 = StringFromKey("OreliBertin_196");
			link.l1.go = "TakeMap_5";
		break;
		case "TakeMap_5":
			dialog.text = StringFromKey("OreliBertin_197");
			link.l1 = StringFromKey("OreliBertin_198");
			link.l1.go = "exit";
			AddQuestRecord("FindMapLSC", "5");
			pchar.questTemp.FindMapLSC.toMonika = true; //навешиваю, чтобы повторки не было.
			LSC_FindMapLSC_RemoveQuestMarksToWoman();
			AddLandQuestMark_Main(CharacterFromID("MonikaRight"), "FindMapLSC");
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("OreliBertin_199");
			link.l1 = StringFromKey("OreliBertin_200");
			link.l1.go = "GoodBye_1";
		break;
		case "GoodBye_1":
			dialog.text = StringFromKey("OreliBertin_201");
			link.l1 = StringFromKey("OreliBertin_202");
			link.l1.go = "GoodBye_2";
		break;
		case "GoodBye_2":
			dialog.text = StringFromKey("OreliBertin_203");
			link.l1 = StringFromKey("OreliBertin_204");
			link.l1.go = "Exit_GoodBye";
			AddItems(pchar, "jewelry4", 20); // Добавляем изумрудов в инвентарь героя
		break;
	}
	NextDiag.PrevNode = NodeName;
}
