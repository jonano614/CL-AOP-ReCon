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
					dialog.text = StringFromKey("DiminicLegro_1", pchar, GetFullName(npchar));
					link.l1 = StringFromKey("DiminicLegro_2", npchar.name, GetFullName(pchar));
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = StringFromKey("DiminicLegro_3", pchar, GetFullName(npchar));
					link.l1 = StringFromKey("DiminicLegro_4", npchar.name, GetFullName(pchar));
					link.l1.go = "FT_1";
				}
			}
			else
			{
				//квест отнести бутылочку вина тюремщику. дача квеста
				if (!CheckAttribute(pchar, "questTemp.LSC.LegroHelp"))
				{
					dialog.text = StringFromKey("DiminicLegro_5", pchar);
					link.l1 = StringFromKey("DiminicLegro_6");
					link.l1.go = "GiveVineBottle";
					break;
				}
				dialog.text = StringFromKey("DiminicLegro_7", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("DiminicLegro_8");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("DiminicLegro_9");
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("DiminicLegro_13", LinkRandPhrase(
							StringFromKey("DiminicLegro_10"),
							StringFromKey("DiminicLegro_11"),
							StringFromKey("DiminicLegro_12", pchar)));
				link.l3.go = "rumours_LSC";
				//квест доставки вина тюремщику. после разговора с Бойлом
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toFackDominic")
				{
					link.l7 = StringFromKey("DiminicLegro_14", pchar);
					link.l7.go = "FackDominic";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toArmoDominic")
				{
					link.l7 = StringFromKey("DiminicLegro_15");
					link.l7.go = "ArmoDominic";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toKeyDominic")
				{
					link.l7 = StringFromKey("DiminicLegro_16", pchar);
					link.l7.go = "KeyDominic";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = StringFromKey("DiminicLegro_17");
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (pchar.questTemp.LSC == "toSeekCrewInTavern") dialog.text = StringFromKey("DiminicLegro_18"); //сбор в таверне
					link.l8 = StringFromKey("DiminicLegro_19");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("DiminicLegro_20");
				link.l10.go = "exit";
			}
		break;
		case "FS_1":
			dialog.text = StringFromKey("DiminicLegro_21");
			link.l1 = StringFromKey("DiminicLegro_22");
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = StringFromKey("DiminicLegro_23");
			link.l1 = StringFromKey("DiminicLegro_24");
			link.l1.go = "FT_3";
		break;
		case "FT_1":
			dialog.text = StringFromKey("DiminicLegro_25");
			link.l1 = StringFromKey("DiminicLegro_26");
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = StringFromKey("DiminicLegro_27");
			link.l1 = StringFromKey("DiminicLegro_28");
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = StringFromKey("DiminicLegro_29");
			link.l1 = StringFromKey("DiminicLegro_30");
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = StringFromKey("DiminicLegro_31");
			if (pchar.questTemp.LSC == "AdmiralIsWaiting")
			{
				link.l1 = StringFromKey("DiminicLegro_32");
				link.l1.go = "FT_5";
			}
			else
			{
				link.l1 = StringFromKey("DiminicLegro_33");
				link.l1.go = "exit";
			}
		break;
		case "FT_5":
			dialog.text = StringFromKey("DiminicLegro_34", pchar.name);
			link.l1 = StringFromKey("DiminicLegro_35");
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = StringFromKey("DiminicLegro_36");
			link.l1 = StringFromKey("DiminicLegro_37");
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = StringFromKey("DiminicLegro_38", pchar.name);
			link.l1 = StringFromKey("DiminicLegro_39");
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
			dialog.text = StringFromKey("DiminicLegro_43", LinkRandPhrase(
						StringFromKey("DiminicLegro_40", pchar),
						StringFromKey("DiminicLegro_41", pchar),
						StringFromKey("DiminicLegro_42", pchar)));
			link.l1 = StringFromKey("DiminicLegro_44");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("DiminicLegro_45");
			link.l1 = StringFromKey("DiminicLegro_46");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("DiminicLegro_50", LinkRandPhrase(
						StringFromKey("DiminicLegro_47"),
						StringFromKey("DiminicLegro_48"),
						StringFromKey("DiminicLegro_49", pchar)));
			link.l1 = StringFromKey("DiminicLegro_54", LinkRandPhrase(
						StringFromKey("DiminicLegro_51"),
						StringFromKey("DiminicLegro_52"),
						StringFromKey("DiminicLegro_53")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("DiminicLegro_55", npchar);
				link.l1 = StringFromKey("DiminicLegro_59", LinkRandPhrase(
							StringFromKey("DiminicLegro_56"),
							StringFromKey("DiminicLegro_57"),
							StringFromKey("DiminicLegro_58")));
			}
			else
			{
				dialog.text = StringFromKey("DiminicLegro_60", npchar);
				link.l1 = StringFromKey("DiminicLegro_63", RandPhraseSimple(
							StringFromKey("DiminicLegro_61", pchar),
							StringFromKey("DiminicLegro_62")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("DiminicLegro_64");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("DiminicLegro_65");
				Link.l1 = StringFromKey("DiminicLegro_66");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("DiminicLegro_67", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("DiminicLegro_68");
					link.l1 = StringFromKey("DiminicLegro_69", pchar);
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("DiminicLegro_70", GetFullName(sld));
					Link.l1 = StringFromKey("DiminicLegro_71");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("DiminicLegro_72");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("DiminicLegro_73", GetFullName(sld));
					Link.l1 = StringFromKey("DiminicLegro_74");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("DiminicLegro_75");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("DiminicLegro_76");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("DiminicLegro_77");
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
					dialog.text = StringFromKey("DiminicLegro_81", LinkRandPhrase(
								StringFromKey("DiminicLegro_78"),
								StringFromKey("DiminicLegro_79"),
								StringFromKey("DiminicLegro_80")));
					link.l1 = StringFromKey("DiminicLegro_84", RandPhraseSimple(
								StringFromKey("DiminicLegro_82"),
								StringFromKey("DiminicLegro_83")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("DiminicLegro_88", LinkRandPhrase(
								StringFromKey("DiminicLegro_85"),
								StringFromKey("DiminicLegro_86"),
								StringFromKey("DiminicLegro_87")));
					link.l1 = StringFromKey("DiminicLegro_91", RandPhraseSimple(
								StringFromKey("DiminicLegro_89"),
								StringFromKey("DiminicLegro_90")));
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
							dialog.text = StringFromKey("DiminicLegro_95", LinkRandPhrase(
										StringFromKey("DiminicLegro_92"),
										StringFromKey("DiminicLegro_93"),
										StringFromKey("DiminicLegro_94")));
						}
						else
						{
							dialog.text = StringFromKey("DiminicLegro_99", LinkRandPhrase(
										StringFromKey("DiminicLegro_96", npchar.quest.seekIdx.where),
										StringFromKey("DiminicLegro_97", npchar.quest.seekIdx.where),
										StringFromKey("DiminicLegro_98", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("DiminicLegro_103", LinkRandPhrase(
										StringFromKey("DiminicLegro_100", npchar.quest.seekIdx.where),
										StringFromKey("DiminicLegro_101"),
										StringFromKey("DiminicLegro_102")));
						}
						else
						{
							dialog.text = StringFromKey("DiminicLegro_107", LinkRandPhrase(
										StringFromKey("DiminicLegro_104", npchar.quest.seekIdx.where),
										StringFromKey("DiminicLegro_105", npchar.quest.seekIdx.where),
										StringFromKey("DiminicLegro_106", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("DiminicLegro_110", RandPhraseSimple(
								StringFromKey("DiminicLegro_108"),
								StringFromKey("DiminicLegro_109")));
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
							dialog.text = StringFromKey("DiminicLegro_114", LinkRandPhrase(
										StringFromKey("DiminicLegro_111"),
										StringFromKey("DiminicLegro_112"),
										StringFromKey("DiminicLegro_113")));
						}
						else
						{
							dialog.text = StringFromKey("DiminicLegro_118", LinkRandPhrase(
										StringFromKey("DiminicLegro_115", npchar.quest.seekIdx.where),
										StringFromKey("DiminicLegro_116", npchar.quest.seekIdx.where),
										StringFromKey("DiminicLegro_117", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("DiminicLegro_122", LinkRandPhrase(
										StringFromKey("DiminicLegro_119", npchar.quest.seekIdx.where),
										StringFromKey("DiminicLegro_120"),
										StringFromKey("DiminicLegro_121")));
						}
						else
						{
							dialog.text = StringFromKey("DiminicLegro_126", LinkRandPhrase(
										StringFromKey("DiminicLegro_123", npchar.quest.seekIdx.where),
										StringFromKey("DiminicLegro_124", npchar.quest.seekIdx.where),
										StringFromKey("DiminicLegro_125", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("DiminicLegro_129", RandPhraseSimple(
								StringFromKey("DiminicLegro_127", GetAddress_FormToNPC(NPChar)),
								StringFromKey("DiminicLegro_128")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("DiminicLegro_130", pchar);
			if (!CheckAttribute(NextDiag, NodeName + ".l4"))
			{
				link.l4 = StringFromKey("DiminicLegro_131");
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("DiminicLegro_132");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("DiminicLegro_133");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l3"))
			{
				link.l3 = StringFromKey("DiminicLegro_134");
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l5") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l5 = StringFromKey("DiminicLegro_135");
				link.l5.go = "ansewer_5";
			}
			link.l10 = StringFromKey("DiminicLegro_136");
			link.l10.go = "exit";
		break;
		case "ansewer_4":
			dialog.text = StringFromKey("DiminicLegro_137");
			link.l1 = StringFromKey("DiminicLegro_138");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("DiminicLegro_139");
			link.l1 = StringFromKey("DiminicLegro_140");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("DiminicLegro_141");
			link.l1 = StringFromKey("DiminicLegro_142");
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = StringFromKey("DiminicLegro_143");
			link.l1 = StringFromKey("DiminicLegro_144");
			link.l1.go = "ansewer_2_2";
		break;
		case "ansewer_2_2":
			dialog.text = StringFromKey("DiminicLegro_145");
			link.l1 = StringFromKey("DiminicLegro_146");
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("DiminicLegro_147", pchar);
			link.l1 = StringFromKey("DiminicLegro_148");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_5":
			dialog.text = StringFromKey("DiminicLegro_149");
			link.l1 = StringFromKey("DiminicLegro_150");
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = StringFromKey("DiminicLegro_151");
			link.l1 = StringFromKey("DiminicLegro_152");
			link.l1.go = "ansewer_5_2";
		break;
		case "ansewer_5_2":
			dialog.text = StringFromKey("DiminicLegro_153");
			link.l1 = StringFromKey("DiminicLegro_154");
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("DiminicLegro_155"),
						StringFromKey("DiminicLegro_156", pchar),
						StringFromKey("DiminicLegro_157", pchar),
						StringFromKey("DiminicLegro_158", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("DiminicLegro_159"),
						StringFromKey("DiminicLegro_160", pchar),
						StringFromKey("DiminicLegro_161"),
						StringFromKey("DiminicLegro_162", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("DiminicLegro_163");
			link.l1 = StringFromKey("DiminicLegro_164");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = StringFromKey("DiminicLegro_165");
			link.l1 = StringFromKey("DiminicLegro_166", pchar);
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = StringFromKey("DiminicLegro_167", pchar);
			link.l1 = StringFromKey("DiminicLegro_168");
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("DiminicLegro_169");
			link.l1 = StringFromKey("DiminicLegro_170");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("DiminicLegro_171");
			link.l1 = StringFromKey("DiminicLegro_172");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("DiminicLegro_173");
			link.l1 = StringFromKey("DiminicLegro_174");
			link.l1.go = "SeekCrew_all";
		break;
		//отнести бутылку вина тюремщику
		case "GiveVineBottle":
			dialog.text = StringFromKey("DiminicLegro_175");
			link.l1 = StringFromKey("DiminicLegro_176");
			link.l1.go = "GiveVineBottle_1";
		break;
		case "GiveVineBottle_1":
			dialog.text = StringFromKey("DiminicLegro_177");
			link.l1 = StringFromKey("DiminicLegro_178");
			link.l1.go = "GiveVineBottle_2";
			link.l2 = StringFromKey("DiminicLegro_179", pchar);
			link.l2.go = "GiveVineBottle_not";
		break;
		case "GiveVineBottle_not":
			dialog.text = StringFromKey("DiminicLegro_180");
			link.l1 = StringFromKey("DiminicLegro_181");
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "over";
			CloseQuestHeader("TakeVineToPrisoner");
			LSC_CheckReadyMainLine(); //проверка все ли готово для продолжения основной линейки
			RemoveLandQuestMark_Main(npchar, "TakeVineToPrisoner");
		break;
		case "GiveVineBottle_2":
			dialog.text = StringFromKey("DiminicLegro_182", pchar.name);
			link.l1 = StringFromKey("DiminicLegro_183");
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toTomasBoil";
			AddQuestRecord("TakeVineToPrisoner", "1");
			RemoveLandQuestMark_Main(npchar, "TakeVineToPrisoner");
			AddLandQuestMark_Main(CharacterFromID("LSC_Prisoner1"), "TakeVineToPrisoner");
			AddLandQuestMark_Main(CharacterFromID("LSC_Trader"), "TakeVineToPrisoner");
		break;

		case "FackDominic":
			dialog.text = StringFromKey("DiminicLegro_184");
			link.l1 = StringFromKey("DiminicLegro_185");
			link.l1.go = "FackDominic_1";
		break;
		case "FackDominic_1":
			dialog.text = StringFromKey("DiminicLegro_186");
			link.l1 = StringFromKey("DiminicLegro_187");
			link.l1.go = "FackDominic_2";
		break;
		case "FackDominic_2":
			dialog.text = StringFromKey("DiminicLegro_188");
			link.l1 = StringFromKey("DiminicLegro_189");
			link.l1.go = "FackDominic_3";
		break;
		case "FackDominic_3":
			dialog.text = StringFromKey("DiminicLegro_190");
			link.l1 = StringFromKey("DiminicLegro_191");
			link.l1.go = "FackDominic_4";
			link.l2 = StringFromKey("DiminicLegro_192", pchar);
			link.l2.go = "GiveVineBottle_not";
		break;
		case "FackDominic_4":
			dialog.text = StringFromKey("DiminicLegro_193", pchar);
			link.l1 = StringFromKey("DiminicLegro_194");
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toSecondToPrison";
			AddQuestRecord("TakeVineToPrisoner", "3");
			RemoveLandQuestMark_Main(npchar, "TakeVineToPrisoner");
			AddLandQuestMark_Main(CharacterFromID("LSC_Prisoner1"), "TakeVineToPrisoner");
		break;

		case "ArmoDominic":
			dialog.text = StringFromKey("DiminicLegro_195");
			link.l1 = StringFromKey("DiminicLegro_196");
			link.l1.go = "ArmoDominic_1";
		break;
		case "ArmoDominic_1":
			dialog.text = StringFromKey("DiminicLegro_197");
			link.l1 = StringFromKey("DiminicLegro_198");
			link.l1.go = "ArmoDominic_2";
		break;
		case "ArmoDominic_2":
			dialog.text = StringFromKey("DiminicLegro_199", pchar);
			link.l1 = StringFromKey("DiminicLegro_200");
			link.l1.go = "ArmoDominic_3";
		break;
		case "ArmoDominic_3":
			dialog.text = StringFromKey("DiminicLegro_201");
			link.l1 = StringFromKey("DiminicLegro_202");
			link.l1.go = "ArmoDominic_4";
		break;
		case "ArmoDominic_4":
			dialog.text = StringFromKey("DiminicLegro_203");
			link.l1 = StringFromKey("DiminicLegro_204");
			link.l1.go = "ArmoDominic_5";
		break;
		case "ArmoDominic_5":
			dialog.text = StringFromKey("DiminicLegro_205", pchar);
			link.l1 = StringFromKey("DiminicLegro_206");
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toArmoTalk";
			AddQuestRecord("TakeVineToPrisoner", "5");
			RemoveLandQuestMark_Main(npchar, "TakeVineToPrisoner");
			AddLandQuestMark_Main(CharacterFromID("LSCwaitress"), "TakeVineToPrisoner");
		break;

		case "KeyDominic":
			dialog.text = StringFromKey("DiminicLegro_207");
			link.l1 = StringFromKey("DiminicLegro_208");
			link.l1.go = "KeyDominic_1";
		break;
		case "KeyDominic_1":
			dialog.text = StringFromKey("DiminicLegro_209", pchar.name);
			link.l1 = StringFromKey("DiminicLegro_210");
			link.l1.go = "KeyDominic_2";
		break;
		case "KeyDominic_2":
			dialog.text = StringFromKey("DiminicLegro_211");
			link.l1 = StringFromKey("DiminicLegro_212");
			link.l1.go = "KeyDominic_3";
		break;
		case "KeyDominic_3":
			dialog.text = StringFromKey("DiminicLegro_213");
			link.l1 = StringFromKey("DiminicLegro_214");
			link.l1.go = "exit";
			GiveItem2Character(pchar, "key1");
			pchar.questTemp.LSC.LegroHelp = "over";
			AddQuestRecord("TakeVineToPrisoner", "7");
			AddQuestUserData("TakeVineToPrisoner", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("TakeVineToPrisoner");
			LSC_CheckReadyMainLine(); //проверка все ли готово для продолжения основной линейки
			RemoveLandQuestMark_Main(npchar, "TakeVineToPrisoner");
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("DiminicLegro_215");
			link.l1 = StringFromKey("DiminicLegro_216");
			link.l1.go = "Exit_GoodBye";
			GiveItem2Character(pchar, "potionwine");
		break;
	}
	NextDiag.PrevNode = NodeName;
}
