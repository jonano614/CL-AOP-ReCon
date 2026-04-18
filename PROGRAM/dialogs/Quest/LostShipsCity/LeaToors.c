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
					if (npchar.location == "PlutoStoreSmall") dialog.text = StringFromKey("LeaToors_1", GetAddress_Form(NPChar), GetFullName(npchar));
					else dialog.text = StringFromKey("LeaToors_2", GetFullName(npchar));
					link.l1 = StringFromKey("LeaToors_3", GetFullName(pchar));
					link.l1.go = "FS_1";
				}
				else
				{
					if (npchar.location == "PlutoStoreSmall") dialog.text = StringFromKey("LeaToors_4", GetAddress_Form(NPChar), GetFullName(npchar));
					else dialog.text = StringFromKey("LeaToors_5", GetAddress_Form(NPChar), GetFullName(npchar));
					link.l1 = StringFromKey("LeaToors_6", pchar, GetFullName(pchar));
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("LeaToors_7", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("LeaToors_8");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("LeaToors_9", pchar);
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("LeaToors_13", LinkRandPhrase(
							StringFromKey("LeaToors_10"),
							StringFromKey("LeaToors_11"),
							StringFromKey("LeaToors_12", pchar)));
				link.l3.go = "rumours_LSC";
				//квест со скелетом Декстера
				if (CheckActiveQuest("LSC_findDekster") && !CheckAttribute(pchar, "questTemp.LSC.lostDecster"))
				{
					link.l4 = StringFromKey("LeaToors_14", pchar);
					link.l4.go = "LostDecster";
				}
				//квест покупка карты
				sld = characterFromId("LSC_Trader");
				if (CheckAttribute(sld, "quest.takeMap") && sld.quest.takeMap == "notTrade" &&
				!CheckAttribute(pchar, "questTemp.FindMapLSC.toMonika") && !CheckCharacterItem(pchar, "map_LSC"))
				{
					link.l5 = StringFromKey("LeaToors_15");
					link.l5.go = "takeMap";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && !CheckAttribute(npchar, "quest.grapes"))
				{
					link.l8 = StringFromKey("LeaToors_16");
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.grapes") && sti(npchar.quest.grapes))
				{
					link.l8 = StringFromKey("LeaToors_17");
					link.l8.go = "TakeGrapes";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (pchar.questTemp.LSC == "toSeekCrewInTavern") dialog.text = StringFromKey("LeaToors_18"); //сбор в таверне
					link.l8 = StringFromKey("LeaToors_19");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("LeaToors_20");
				link.l10.go = "exit";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "FS_1":
			dialog.text = StringFromKey("LeaToors_21");
			link.l1 = StringFromKey("LeaToors_22");
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = StringFromKey("LeaToors_23");
			link.l1 = StringFromKey("LeaToors_24");
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = StringFromKey("LeaToors_25");
			link.l1 = StringFromKey("LeaToors_26");
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
			dialog.text = StringFromKey("LeaToors_30", LinkRandPhrase(
						StringFromKey("LeaToors_27", pchar),
						StringFromKey("LeaToors_28", pchar),
						StringFromKey("LeaToors_29", pchar)));
			link.l1 = StringFromKey("LeaToors_31");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("LeaToors_32");
			link.l1 = StringFromKey("LeaToors_33");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("LeaToors_37", LinkRandPhrase(
						StringFromKey("LeaToors_34", pchar),
						StringFromKey("LeaToors_35"),
						StringFromKey("LeaToors_36", pchar)));
			link.l1 = StringFromKey("LeaToors_41", LinkRandPhrase(
						StringFromKey("LeaToors_38"),
						StringFromKey("LeaToors_39"),
						StringFromKey("LeaToors_40")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("LeaToors_42", npchar);
				link.l1 = StringFromKey("LeaToors_46", LinkRandPhrase(
							StringFromKey("LeaToors_43"),
							StringFromKey("LeaToors_44"),
							StringFromKey("LeaToors_45")));
			}
			else
			{
				dialog.text = StringFromKey("LeaToors_47", npchar);
				link.l1 = StringFromKey("LeaToors_50", RandPhraseSimple(
							StringFromKey("LeaToors_48", pchar),
							StringFromKey("LeaToors_49")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("LeaToors_51");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("LeaToors_52");
				Link.l1 = StringFromKey("LeaToors_53");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("LeaToors_54", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("LeaToors_55");
					link.l1 = StringFromKey("LeaToors_56");
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("LeaToors_57", GetFullName(sld));
					Link.l1 = StringFromKey("LeaToors_58");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("LeaToors_59");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("LeaToors_60", GetFullName(sld));
					Link.l1 = StringFromKey("LeaToors_61");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("LeaToors_62");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("LeaToors_63", pchar);
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("LeaToors_64");
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
					dialog.text = StringFromKey("LeaToors_68", LinkRandPhrase(
								StringFromKey("LeaToors_65"),
								StringFromKey("LeaToors_66"),
								StringFromKey("LeaToors_67")));
					link.l1 = StringFromKey("LeaToors_71", RandPhraseSimple(
								StringFromKey("LeaToors_69"),
								StringFromKey("LeaToors_70")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("LeaToors_75", LinkRandPhrase(
								StringFromKey("LeaToors_72"),
								StringFromKey("LeaToors_73"),
								StringFromKey("LeaToors_74")));
					link.l1 = StringFromKey("LeaToors_78", RandPhraseSimple(
								StringFromKey("LeaToors_76"),
								StringFromKey("LeaToors_77")));
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
							dialog.text = StringFromKey("LeaToors_82", LinkRandPhrase(
										StringFromKey("LeaToors_79"),
										StringFromKey("LeaToors_80"),
										StringFromKey("LeaToors_81")));
						}
						else
						{
							dialog.text = StringFromKey("LeaToors_86", LinkRandPhrase(
										StringFromKey("LeaToors_83", npchar.quest.seekIdx.where),
										StringFromKey("LeaToors_84", npchar.quest.seekIdx.where),
										StringFromKey("LeaToors_85", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("LeaToors_90", LinkRandPhrase(
										StringFromKey("LeaToors_87", pchar, npchar.quest.seekIdx.where),
										StringFromKey("LeaToors_88"),
										StringFromKey("LeaToors_89")));
						}
						else
						{
							dialog.text = StringFromKey("LeaToors_94", LinkRandPhrase(
										StringFromKey("LeaToors_91", npchar.quest.seekIdx.where),
										StringFromKey("LeaToors_92", npchar.quest.seekIdx.where),
										StringFromKey("LeaToors_93", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("LeaToors_97", RandPhraseSimple(
								StringFromKey("LeaToors_95"),
								StringFromKey("LeaToors_96")));
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
							dialog.text = StringFromKey("LeaToors_101", LinkRandPhrase(
										StringFromKey("LeaToors_98"),
										StringFromKey("LeaToors_99"),
										StringFromKey("LeaToors_100")));
						}
						else
						{
							dialog.text = StringFromKey("LeaToors_105", LinkRandPhrase(
										StringFromKey("LeaToors_102", npchar.quest.seekIdx.where),
										StringFromKey("LeaToors_103", npchar.quest.seekIdx.where),
										StringFromKey("LeaToors_104", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("LeaToors_109", LinkRandPhrase(
										StringFromKey("LeaToors_106", pchar, npchar.quest.seekIdx.where),
										StringFromKey("LeaToors_107"),
										StringFromKey("LeaToors_108")));
						}
						else
						{
							dialog.text = StringFromKey("LeaToors_113", LinkRandPhrase(
										StringFromKey("LeaToors_110", npchar.quest.seekIdx.where),
										StringFromKey("LeaToors_111", npchar.quest.seekIdx.where),
										StringFromKey("LeaToors_112", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("LeaToors_116", RandPhraseSimple(
								StringFromKey("LeaToors_114"),
								StringFromKey("LeaToors_115")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("LeaToors_117");
			if (!CheckAttribute(NextDiag, NodeName + ".l1") && npchar.location == "PlutoStoreSmall")
			{
				link.l1 = StringFromKey("LeaToors_118");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l2 = StringFromKey("LeaToors_119");
				link.l2.go = "ansewer_2";
			}
			link.l10 = StringFromKey("LeaToors_120");
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("LeaToors_121");
			link.l1 = StringFromKey("LeaToors_122");
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = StringFromKey("LeaToors_123");
			link.l1 = StringFromKey("LeaToors_124");
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("LeaToors_125");
			link.l1 = StringFromKey("LeaToors_126");
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = StringFromKey("LeaToors_127");
			link.l1 = StringFromKey("LeaToors_128");
			link.l1.go = "ansewer_2_2";
		break;
		case "ansewer_2_2":
			dialog.text = StringFromKey("LeaToors_129");
			link.l1 = StringFromKey("LeaToors_130");
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("LeaToors_131"),
						StringFromKey("LeaToors_132"),
						StringFromKey("LeaToors_133"),
						StringFromKey("LeaToors_134"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("LeaToors_135"),
						StringFromKey("LeaToors_136", pchar),
						StringFromKey("LeaToors_137"),
						StringFromKey("LeaToors_138", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("LeaToors_139");
			link.l1 = StringFromKey("LeaToors_140");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = StringFromKey("LeaToors_141");
			link.l1 = StringFromKey("LeaToors_142");
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = StringFromKey("LeaToors_143");
			link.l1 = StringFromKey("LeaToors_144");
			link.l1.go = "exit";
			npchar.quest.grapes = true;
			AddQuestRecord("ISS_MainLine", "48");
		break;
		//проверка на соль
		case "TakeGrapes":
			dialog.text = StringFromKey("LeaToors_145");
			if (CheckCharacterItem(pchar, "Mineral10") && sti(pchar.items.Mineral10) >= 10)
			{
				link.l1 = StringFromKey("LeaToors_146", pchar);
				link.l1.go = "TakeGrapes_yes";
			}
			else
			{
				link.l1 = StringFromKey("LeaToors_147");
				link.l1.go = "TakeGrapes_no";
			}
		break;
		case "TakeGrapes_no":
			dialog.text = StringFromKey("LeaToors_148");
			link.l1 = StringFromKey("LeaToors_149");
			link.l1.go = "exit";
		break;
		case "TakeGrapes_yes":
			dialog.text = StringFromKey("LeaToors_150");
			link.l1 = StringFromKey("LeaToors_151");
			link.l1.go = "TakeGrapes_1";
			TakeNItems(pchar, "Mineral10", -10);
		break;
		case "TakeGrapes_1":
			dialog.text = StringFromKey("LeaToors_152");
			link.l1 = StringFromKey("LeaToors_153");
			link.l1.go = "TakeGrapes_2";
		break;
		case "TakeGrapes_2":
			dialog.text = StringFromKey("LeaToors_154");
			link.l1 = StringFromKey("LeaToors_155");
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_GRAPES, 100);
			AddQuestRecord("ISS_MainLine", "49");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ёс", "есла"));
			npchar.quest.grapes = false;
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = StringFromKey("LeaToors_156");
			link.l1 = StringFromKey("LeaToors_157");
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("LeaToors_158");
			link.l1 = StringFromKey("LeaToors_159");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("LeaToors_160");
			link.l1 = StringFromKey("LeaToors_161");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("LeaToors_162");
			link.l1 = StringFromKey("LeaToors_163");
			link.l1.go = "SeekCrew_all";
		break;
		//квест со скелетом Лейтона Декстера
		case "LostDecster":
			dialog.text = StringFromKey("LeaToors_164");
			link.l1 = StringFromKey("LeaToors_165");
			link.l1.go = "LostDecster_1";
		break;
		case "LostDecster_1":
			dialog.text = StringFromKey("LeaToors_166");
			link.l1 = StringFromKey("LeaToors_167");
			link.l1.go = "LostDecster_2";
		break;
		case "LostDecster_2":
			dialog.text = StringFromKey("LeaToors_168");
			link.l1 = StringFromKey("LeaToors_169");
			link.l1.go = "LostDecster_3";
		break;
		case "LostDecster_3":
			dialog.text = StringFromKey("LeaToors_170");
			link.l1 = StringFromKey("LeaToors_171");
			link.l1.go = "LostDecster_4";
		break;
		case "LostDecster_4":
			dialog.text = StringFromKey("LeaToors_172");
			link.l1 = StringFromKey("LeaToors_173");
			link.l1.go = "LostDecster_5";
		break;
		case "LostDecster_5":
			dialog.text = StringFromKey("LeaToors_174");
			link.l1 = StringFromKey("LeaToors_175");
			link.l1.go = "LostDecster_6";
		break;
		case "LostDecster_6":
			dialog.text = StringFromKey("LeaToors_176");
			link.l1 = StringFromKey("LeaToors_177");
			link.l1.go = "LostDecster_7";
		break;
		case "LostDecster_7":
			dialog.text = StringFromKey("LeaToors_178");
			link.l1 = StringFromKey("LeaToors_179");
			link.l1.go = "LostDecster_8";
		break;
		case "LostDecster_8":
			dialog.text = StringFromKey("LeaToors_180");
			link.l1 = StringFromKey("LeaToors_181");
			link.l1.go = "exit";
			pchar.questTemp.LSC.lostDecster = "toAdmiral";
			AddQuestRecord("LSC_findDekster", "3");
			RemoveLandQuestMark_Main(npchar, "LSC_findDekster");
			AddLandQuestMark_Main(CharacterFromId("LSCMayor"), "LSC_findDekster");
			AddLandQuestMark_Main(CharacterFromID("LSC_PrisonerHead"), "LSC_findDekster");
			AddLandQuestMark_Main(CharacterFromID("LSC_Prisoner1"), "LSC_findDekster");
		break;
		case "TakeMap":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("LeaToors_182"),
						StringFromKey("LeaToors_183"),
						StringFromKey("LeaToors_184"),
						StringFromKey("LeaToors_185"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("LeaToors_186"),
						StringFromKey("LeaToors_187", pchar),
						StringFromKey("LeaToors_188"),
						StringFromKey("LeaToors_189"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("TakeMap_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "TakeMap_1":
			dialog.text = StringFromKey("LeaToors_190");
			link.l1 = StringFromKey("LeaToors_191");
			link.l1.go = "exit";
			RemoveLandQuestMark_Main(npchar, "FindMapLSC");
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("LeaToors_192");
			link.l1 = StringFromKey("LeaToors_193");
			link.l1.go = "Exit_GoodBye";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
