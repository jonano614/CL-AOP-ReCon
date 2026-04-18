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
					if (npchar.location == "SantaFlorentinaShipInside4") dialog.text = StringFromKey("ElizaCalvo_1", GetAddress_Form(NPChar), GetFullName(npchar));
					else dialog.text = StringFromKey("ElizaCalvo_2", GetAddress_Form(NPChar), GetFullName(npchar));
					link.l1 = StringFromKey("ElizaCalvo_3", GetFullName(pchar));
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = StringFromKey("ElizaCalvo_4", pchar);
					link.l1 = StringFromKey("ElizaCalvo_5", GetFullName(pchar));
					link.l1.go = "FT_1";
				}
			}
			else
			{
				if (npchar.location == "SantaFlorentinaShipInside4") dialog.text = StringFromKey("ElizaCalvo_6", GetAddress_Form(NPChar));
				else dialog.text = StringFromKey("ElizaCalvo_7", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("ElizaCalvo_8");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("ElizaCalvo_9", pchar);
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("ElizaCalvo_13", LinkRandPhrase(
							StringFromKey("ElizaCalvo_10"),
							StringFromKey("ElizaCalvo_11"),
							StringFromKey("ElizaCalvo_12", pchar)));
				link.l3.go = "rumours_LSC";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && !CheckAttribute(npchar, "quest.bombs"))
				{
					link.l8 = StringFromKey("ElizaCalvo_14");
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.bombs") && sti(npchar.quest.bombs))
				{
					link.l8 = StringFromKey("ElizaCalvo_15");
					link.l8.go = "TakeBombs";
				}
				//квест покупка карты
				sld = characterFromId("LSC_Trader");
				if (CheckAttribute(sld, "quest.takeMap") && sld.quest.takeMap == "notTrade" &&
				!CheckAttribute(pchar, "questTemp.FindMapLSC.toMonika") && !CheckCharacterItem(pchar, "map_LSC"))
				{
					link.l4 = StringFromKey("ElizaCalvo_16");
					link.l4.go = "takeMap";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (pchar.questTemp.LSC == "toSeekCrewInTavern") dialog.text = StringFromKey("ElizaCalvo_17"); //сбор в таверне
					link.l8 = StringFromKey("ElizaCalvo_18");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("ElizaCalvo_19");
				link.l10.go = "exit";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "FS_1":
			dialog.text = StringFromKey("ElizaCalvo_20");
			link.l1 = StringFromKey("ElizaCalvo_21");
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = StringFromKey("ElizaCalvo_22");
			if (pchar.questTemp.LSC == "AdmiralIsWaiting")
			{
				link.l1 = StringFromKey("ElizaCalvo_23");
				link.l1.go = "FS_3";
			}
			else
			{
				link.l1 = StringFromKey("ElizaCalvo_24", pchar);
				link.l1.go = "exit";
			}
		break;
		case "FS_3":
			dialog.text = StringFromKey("ElizaCalvo_25");
			link.l1 = StringFromKey("ElizaCalvo_26");
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = StringFromKey("ElizaCalvo_27", GetFullName(npchar));
			link.l1 = StringFromKey("ElizaCalvo_28");
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = StringFromKey("ElizaCalvo_29");
			link.l1 = StringFromKey("ElizaCalvo_30");
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
			dialog.text = StringFromKey("ElizaCalvo_34", LinkRandPhrase(
						StringFromKey("ElizaCalvo_31", pchar),
						StringFromKey("ElizaCalvo_32"),
						StringFromKey("ElizaCalvo_33", pchar)));
			link.l1 = StringFromKey("ElizaCalvo_35");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("ElizaCalvo_36");
			link.l1 = StringFromKey("ElizaCalvo_37");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("ElizaCalvo_41", LinkRandPhrase(
						StringFromKey("ElizaCalvo_38", pchar),
						StringFromKey("ElizaCalvo_39"),
						StringFromKey("ElizaCalvo_40", pchar)));
			link.l1 = StringFromKey("ElizaCalvo_45", LinkRandPhrase(
						StringFromKey("ElizaCalvo_42"),
						StringFromKey("ElizaCalvo_43"),
						StringFromKey("ElizaCalvo_44")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("ElizaCalvo_46", npchar);
				link.l1 = StringFromKey("ElizaCalvo_50", LinkRandPhrase(
							StringFromKey("ElizaCalvo_47"),
							StringFromKey("ElizaCalvo_48"),
							StringFromKey("ElizaCalvo_49")));
			}
			else
			{
				dialog.text = StringFromKey("ElizaCalvo_51", npchar);
				link.l1 = StringFromKey("ElizaCalvo_54", RandPhraseSimple(
							StringFromKey("ElizaCalvo_52", pchar),
							StringFromKey("ElizaCalvo_53")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("ElizaCalvo_55");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("ElizaCalvo_56");
				Link.l1 = StringFromKey("ElizaCalvo_57");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("ElizaCalvo_58", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("ElizaCalvo_59");
					link.l1 = StringFromKey("ElizaCalvo_60");
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("ElizaCalvo_61", GetFullName(sld));
					Link.l1 = StringFromKey("ElizaCalvo_62");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("ElizaCalvo_63");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("ElizaCalvo_64", GetFullName(sld));
					Link.l1 = StringFromKey("ElizaCalvo_65");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("ElizaCalvo_66");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("ElizaCalvo_67");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("ElizaCalvo_68");
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
					dialog.text = StringFromKey("ElizaCalvo_72", LinkRandPhrase(
								StringFromKey("ElizaCalvo_69"),
								StringFromKey("ElizaCalvo_70"),
								StringFromKey("ElizaCalvo_71")));
					link.l1 = StringFromKey("ElizaCalvo_75", RandPhraseSimple(
								StringFromKey("ElizaCalvo_73"),
								StringFromKey("ElizaCalvo_74")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("ElizaCalvo_79", LinkRandPhrase(
								StringFromKey("ElizaCalvo_76"),
								StringFromKey("ElizaCalvo_77"),
								StringFromKey("ElizaCalvo_78")));
					link.l1 = StringFromKey("ElizaCalvo_82", RandPhraseSimple(
								StringFromKey("ElizaCalvo_80"),
								StringFromKey("ElizaCalvo_81")));
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
							dialog.text = StringFromKey("ElizaCalvo_86", LinkRandPhrase(
										StringFromKey("ElizaCalvo_83"),
										StringFromKey("ElizaCalvo_84"),
										StringFromKey("ElizaCalvo_85")));
						}
						else
						{
							dialog.text = StringFromKey("ElizaCalvo_90", LinkRandPhrase(
										StringFromKey("ElizaCalvo_87", npchar.quest.seekIdx.where),
										StringFromKey("ElizaCalvo_88", npchar.quest.seekIdx.where),
										StringFromKey("ElizaCalvo_89", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("ElizaCalvo_94", LinkRandPhrase(
										StringFromKey("ElizaCalvo_91", npchar.quest.seekIdx.where),
										StringFromKey("ElizaCalvo_92"),
										StringFromKey("ElizaCalvo_93")));
						}
						else
						{
							dialog.text = StringFromKey("ElizaCalvo_98", LinkRandPhrase(
										StringFromKey("ElizaCalvo_95", npchar.quest.seekIdx.where),
										StringFromKey("ElizaCalvo_96", npchar.quest.seekIdx.where),
										StringFromKey("ElizaCalvo_97", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("ElizaCalvo_101", RandPhraseSimple(
								StringFromKey("ElizaCalvo_99"),
								StringFromKey("ElizaCalvo_100")));
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
							dialog.text = StringFromKey("ElizaCalvo_105", LinkRandPhrase(
										StringFromKey("ElizaCalvo_102"),
										StringFromKey("ElizaCalvo_103"),
										StringFromKey("ElizaCalvo_104")));
						}
						else
						{
							dialog.text = StringFromKey("ElizaCalvo_109", LinkRandPhrase(
										StringFromKey("ElizaCalvo_106", npchar.quest.seekIdx.where),
										StringFromKey("ElizaCalvo_107", npchar.quest.seekIdx.where),
										StringFromKey("ElizaCalvo_108", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("ElizaCalvo_113", LinkRandPhrase(
										StringFromKey("ElizaCalvo_110", npchar.quest.seekIdx.where),
										StringFromKey("ElizaCalvo_111"),
										StringFromKey("ElizaCalvo_112")));
						}
						else
						{
							dialog.text = StringFromKey("ElizaCalvo_117", LinkRandPhrase(
										StringFromKey("ElizaCalvo_114", npchar.quest.seekIdx.where),
										StringFromKey("ElizaCalvo_115", npchar.quest.seekIdx.where),
										StringFromKey("ElizaCalvo_116", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("ElizaCalvo_120", RandPhraseSimple(
								StringFromKey("ElizaCalvo_118"),
								StringFromKey("ElizaCalvo_119")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("ElizaCalvo_121");
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("ElizaCalvo_122");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("ElizaCalvo_123");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = StringFromKey("ElizaCalvo_124");
				link.l3.go = "ansewer_3";
			}
			link.l10 = StringFromKey("ElizaCalvo_125");
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("ElizaCalvo_126");
			link.l1 = StringFromKey("ElizaCalvo_127");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("ElizaCalvo_128");
			link.l1 = StringFromKey("ElizaCalvo_129");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("ElizaCalvo_130");
			link.l1 = StringFromKey("ElizaCalvo_131");
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = StringFromKey("ElizaCalvo_132");
			link.l1 = StringFromKey("ElizaCalvo_133");
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("ElizaCalvo_134"),
						StringFromKey("ElizaCalvo_135"),
						StringFromKey("ElizaCalvo_136"),
						StringFromKey("ElizaCalvo_137"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("ElizaCalvo_138"),
						StringFromKey("ElizaCalvo_139", pchar),
						StringFromKey("ElizaCalvo_140"),
						StringFromKey("ElizaCalvo_141", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("ElizaCalvo_142");
			link.l1 = StringFromKey("ElizaCalvo_143");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = StringFromKey("ElizaCalvo_144");
			link.l1 = StringFromKey("ElizaCalvo_145");
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = StringFromKey("ElizaCalvo_146");
			link.l1 = StringFromKey("ElizaCalvo_147");
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = StringFromKey("ElizaCalvo_148", pchar);
			link.l1 = StringFromKey("ElizaCalvo_149", pchar);
			link.l1.go = "SeekGoods_5";
		break;
		case "SeekGoods_5":
			dialog.text = StringFromKey("ElizaCalvo_150");
			link.l1 = StringFromKey("ElizaCalvo_151");
			link.l1.go = "exit";
			npchar.quest.bombs = true;
			AddQuestRecord("ISS_MainLine", "50");
		break;
		//проверка на соль
		case "TakeBombs":
			dialog.text = StringFromKey("ElizaCalvo_152");
			if (ItemCheck(pchar, "Mineral2,potionwine:3,potion5:10", 1))
			{
				link.l1 = StringFromKey("ElizaCalvo_153");
				link.l1.go = "TakeBombs_yes";
			}
			else
			{
				link.l1 = StringFromKey("ElizaCalvo_154");
				link.l1.go = "TakeBombs_no";
			}
		break;
		case "TakeBombs_no":
			dialog.text = StringFromKey("ElizaCalvo_155");
			link.l1 = StringFromKey("ElizaCalvo_156");
			link.l1.go = "exit";
		break;
		case "TakeBombs_yes":
			dialog.text = StringFromKey("ElizaCalvo_157");
			link.l1 = StringFromKey("ElizaCalvo_158");
			link.l1.go = "TakeBombs_1";
			ItemTakeEx(PChar, "Mineral2,potionwine,potion5", "-1,-3,-10");
		break;
		case "TakeBombs_1":
			dialog.text = StringFromKey("ElizaCalvo_159", pchar);
			link.l1 = StringFromKey("ElizaCalvo_160");
			link.l1.go = "TakeBombs_2";
		break;
		case "TakeBombs_2":
			dialog.text = StringFromKey("ElizaCalvo_161", pchar);
			link.l1 = StringFromKey("ElizaCalvo_162", pchar);
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_BOMBS, 100);
			AddQuestRecord("ISS_MainLine", "51");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
			npchar.quest.Bombs = false;
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = StringFromKey("ElizaCalvo_163");
			link.l1 = StringFromKey("ElizaCalvo_164");
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("ElizaCalvo_165");
			link.l1 = StringFromKey("ElizaCalvo_166");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("ElizaCalvo_167");
			link.l1 = StringFromKey("ElizaCalvo_168");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("ElizaCalvo_169");
			link.l1 = StringFromKey("ElizaCalvo_170");
			link.l1.go = "SeekCrew_all";
		break;
		//квест получения карты
		case "TakeMap":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("ElizaCalvo_171"),
						StringFromKey("ElizaCalvo_172"),
						StringFromKey("ElizaCalvo_173"),
						StringFromKey("ElizaCalvo_174"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("ElizaCalvo_175"),
						StringFromKey("ElizaCalvo_176", pchar),
						StringFromKey("ElizaCalvo_177"),
						StringFromKey("ElizaCalvo_178"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("TakeMap_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "TakeMap_1":
			dialog.text = StringFromKey("ElizaCalvo_179");
			link.l1 = StringFromKey("ElizaCalvo_180");
			link.l1.go = "exit";
			RemoveLandQuestMark_Main(npchar, "FindMapLSC");
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("ElizaCalvo_181", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("ElizaCalvo_182");
			link.l1.go = "GoodBye_1";
		break;
		case "GoodBye_1":
			dialog.text = StringFromKey("ElizaCalvo_183");
			link.l1 = StringFromKey("ElizaCalvo_184");
			link.l1.go = "Exit_GoodBye";
			GiveItem2Character(pchar, "recipe_grenade");
		break;
	}
	NextDiag.PrevNode = NodeName;
}
