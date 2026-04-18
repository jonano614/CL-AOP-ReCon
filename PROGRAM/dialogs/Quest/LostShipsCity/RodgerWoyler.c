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
					dialog.text = StringFromKey("RodgerWoyler_1");
					link.l1 = StringFromKey("RodgerWoyler_2");
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = StringFromKey("RodgerWoyler_3");
					link.l1 = StringFromKey("RodgerWoyler_4");
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("RodgerWoyler_5", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("RodgerWoyler_6");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("RodgerWoyler_7");
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("RodgerWoyler_11", LinkRandPhrase(
							StringFromKey("RodgerWoyler_8"),
							StringFromKey("RodgerWoyler_9"),
							StringFromKey("RodgerWoyler_10", pchar)));
				link.l3.go = "rumours_LSC";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = StringFromKey("RodgerWoyler_12");
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (pchar.questTemp.LSC == "toSeekCrewInTavern") dialog.text = StringFromKey("RodgerWoyler_13"); //сбор в таверне
					link.l8 = StringFromKey("RodgerWoyler_14");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("RodgerWoyler_15");
				link.l10.go = "exit";
			}
		break;
		case "FS_1":
			dialog.text = StringFromKey("RodgerWoyler_16");
			link.l1 = StringFromKey("RodgerWoyler_17", pchar);
			link.l1.go = "FT_2";
		break;
		case "FT_1":
			dialog.text = StringFromKey("RodgerWoyler_18");
			link.l1 = StringFromKey("RodgerWoyler_19");
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = GetFullName(npchar) + ", " + GetAddress_Form(NPChar) + ".";
			link.l1 = StringFromKey("RodgerWoyler_20", pchar, GetFullName(pchar));
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = StringFromKey("RodgerWoyler_21");
			link.l1 = StringFromKey("RodgerWoyler_22");
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = StringFromKey("RodgerWoyler_23", pchar);
			link.l1 = StringFromKey("RodgerWoyler_24");
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = StringFromKey("RodgerWoyler_25");
			link.l1 = StringFromKey("RodgerWoyler_26");
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = StringFromKey("RodgerWoyler_27");
			link.l1 = StringFromKey("RodgerWoyler_28");
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = StringFromKey("RodgerWoyler_29", pchar);
			link.l1 = StringFromKey("RodgerWoyler_30");
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = StringFromKey("RodgerWoyler_31");
			link.l1 = StringFromKey("RodgerWoyler_32");
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = StringFromKey("RodgerWoyler_33");
			link.l1 = StringFromKey("RodgerWoyler_34");
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			dialog.text = StringFromKey("RodgerWoyler_35");
			link.l1 = StringFromKey("RodgerWoyler_36");
			link.l1.go = "FT_11";
		break;
		case "FT_11":
			dialog.text = StringFromKey("RodgerWoyler_37");
			link.l1 = StringFromKey("RodgerWoyler_38");
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
			dialog.text = StringFromKey("RodgerWoyler_42", LinkRandPhrase(
						StringFromKey("RodgerWoyler_39", pchar),
						StringFromKey("RodgerWoyler_40", pchar),
						StringFromKey("RodgerWoyler_41", pchar)));
			link.l1 = StringFromKey("RodgerWoyler_43");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("RodgerWoyler_44");
			link.l1 = StringFromKey("RodgerWoyler_45");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("RodgerWoyler_49", LinkRandPhrase(
						StringFromKey("RodgerWoyler_46", pchar),
						StringFromKey("RodgerWoyler_47"),
						StringFromKey("RodgerWoyler_48", pchar)));
			link.l1 = StringFromKey("RodgerWoyler_53", LinkRandPhrase(
						StringFromKey("RodgerWoyler_50"),
						StringFromKey("RodgerWoyler_51"),
						StringFromKey("RodgerWoyler_52")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("RodgerWoyler_54", npchar);
				link.l1 = StringFromKey("RodgerWoyler_58", LinkRandPhrase(
							StringFromKey("RodgerWoyler_55"),
							StringFromKey("RodgerWoyler_56"),
							StringFromKey("RodgerWoyler_57")));
			}
			else
			{
				dialog.text = StringFromKey("RodgerWoyler_59", npchar);
				link.l1 = StringFromKey("RodgerWoyler_62", RandPhraseSimple(
							StringFromKey("RodgerWoyler_60", pchar),
							StringFromKey("RodgerWoyler_61")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("RodgerWoyler_63");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("RodgerWoyler_64");
				Link.l1 = StringFromKey("RodgerWoyler_65");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("RodgerWoyler_66", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("RodgerWoyler_67");
					link.l1 = StringFromKey("RodgerWoyler_68", pchar);
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("RodgerWoyler_69", GetFullName(sld));
					Link.l1 = StringFromKey("RodgerWoyler_70");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("RodgerWoyler_71");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("RodgerWoyler_72", GetFullName(sld));
					Link.l1 = StringFromKey("RodgerWoyler_73");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("RodgerWoyler_74");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("RodgerWoyler_75");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("RodgerWoyler_76");
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
					dialog.text = StringFromKey("RodgerWoyler_80", LinkRandPhrase(
								StringFromKey("RodgerWoyler_77"),
								StringFromKey("RodgerWoyler_78"),
								StringFromKey("RodgerWoyler_79")));
					link.l1 = StringFromKey("RodgerWoyler_83", RandPhraseSimple(
								StringFromKey("RodgerWoyler_81"),
								StringFromKey("RodgerWoyler_82")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("RodgerWoyler_87", LinkRandPhrase(
								StringFromKey("RodgerWoyler_84"),
								StringFromKey("RodgerWoyler_85"),
								StringFromKey("RodgerWoyler_86")));
					link.l1 = StringFromKey("RodgerWoyler_90", RandPhraseSimple(
								StringFromKey("RodgerWoyler_88"),
								StringFromKey("RodgerWoyler_89")));
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
							dialog.text = StringFromKey("RodgerWoyler_94", LinkRandPhrase(
										StringFromKey("RodgerWoyler_91"),
										StringFromKey("RodgerWoyler_92"),
										StringFromKey("RodgerWoyler_93")));
						}
						else
						{
							dialog.text = StringFromKey("RodgerWoyler_98", LinkRandPhrase(
										StringFromKey("RodgerWoyler_95", npchar.quest.seekIdx.where),
										StringFromKey("RodgerWoyler_96", npchar.quest.seekIdx.where),
										StringFromKey("RodgerWoyler_97", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("RodgerWoyler_102", LinkRandPhrase(
										StringFromKey("RodgerWoyler_99", npchar.quest.seekIdx.where),
										StringFromKey("RodgerWoyler_100"),
										StringFromKey("RodgerWoyler_101")));
						}
						else
						{
							dialog.text = StringFromKey("RodgerWoyler_106", LinkRandPhrase(
										StringFromKey("RodgerWoyler_103", npchar.quest.seekIdx.where),
										StringFromKey("RodgerWoyler_104", npchar.quest.seekIdx.where),
										StringFromKey("RodgerWoyler_105", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("RodgerWoyler_109", RandPhraseSimple(
								StringFromKey("RodgerWoyler_107"),
								StringFromKey("RodgerWoyler_108")));
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
							dialog.text = StringFromKey("RodgerWoyler_113", LinkRandPhrase(
										StringFromKey("RodgerWoyler_110"),
										StringFromKey("RodgerWoyler_111"),
										StringFromKey("RodgerWoyler_112")));
						}
						else
						{
							dialog.text = StringFromKey("RodgerWoyler_117", LinkRandPhrase(
										StringFromKey("RodgerWoyler_114", npchar.quest.seekIdx.where),
										StringFromKey("RodgerWoyler_115", npchar.quest.seekIdx.where),
										StringFromKey("RodgerWoyler_116", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("RodgerWoyler_121", LinkRandPhrase(
										StringFromKey("RodgerWoyler_118", npchar.quest.seekIdx.where),
										StringFromKey("RodgerWoyler_119"),
										StringFromKey("RodgerWoyler_120")));
						}
						else
						{
							dialog.text = StringFromKey("RodgerWoyler_125", LinkRandPhrase(
										StringFromKey("RodgerWoyler_122", npchar.quest.seekIdx.where),
										StringFromKey("RodgerWoyler_123", npchar.quest.seekIdx.where),
										StringFromKey("RodgerWoyler_124", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("RodgerWoyler_128", RandPhraseSimple(
								StringFromKey("RodgerWoyler_126", GetAddress_FormToNPC(NPChar)),
								StringFromKey("RodgerWoyler_127")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("RodgerWoyler_129", pchar);
			if (!CheckAttribute(NextDiag, NodeName + ".l3"))
			{
				link.l3 = StringFromKey("RodgerWoyler_130");
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("RodgerWoyler_131");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("RodgerWoyler_132");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l4") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l4 = StringFromKey("RodgerWoyler_133");
				link.l4.go = "ansewer_4";
			}
			link.l10 = StringFromKey("RodgerWoyler_134");
			link.l10.go = "exit";
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("RodgerWoyler_135");
			link.l1 = StringFromKey("RodgerWoyler_136");
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = StringFromKey("RodgerWoyler_137");
			link.l1 = StringFromKey("RodgerWoyler_138", pchar);
			link.l1.go = "int_quests";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("RodgerWoyler_139");
			link.l1 = StringFromKey("RodgerWoyler_140");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("RodgerWoyler_141");
			link.l1 = StringFromKey("RodgerWoyler_142");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_4":
			dialog.text = StringFromKey("RodgerWoyler_143");
			link.l1 = StringFromKey("RodgerWoyler_144");
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = StringFromKey("RodgerWoyler_145");
			link.l1 = StringFromKey("RodgerWoyler_146");
			link.l1.go = "ansewer_4_2";
		break;
		case "ansewer_4_2":
			dialog.text = StringFromKey("RodgerWoyler_147");
			link.l1 = StringFromKey("RodgerWoyler_148");
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("RodgerWoyler_149"),
						StringFromKey("RodgerWoyler_150"),
						StringFromKey("RodgerWoyler_151"),
						StringFromKey("RodgerWoyler_152"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("RodgerWoyler_153"),
						StringFromKey("RodgerWoyler_154", pchar),
						StringFromKey("RodgerWoyler_155"),
						StringFromKey("RodgerWoyler_156", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("RodgerWoyler_157");
			link.l1 = StringFromKey("RodgerWoyler_158");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = StringFromKey("RodgerWoyler_159");
			link.l1 = StringFromKey("RodgerWoyler_160");
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = StringFromKey("RodgerWoyler_161");
			link.l1 = StringFromKey("RodgerWoyler_162");
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("RodgerWoyler_163");
			link.l1 = StringFromKey("RodgerWoyler_164");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("RodgerWoyler_165");
			link.l1 = StringFromKey("RodgerWoyler_166");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("RodgerWoyler_167");
			link.l1 = StringFromKey("RodgerWoyler_168");
			link.l1.go = "SeekCrew_all";
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("RodgerWoyler_169");
			link.l1 = StringFromKey("RodgerWoyler_170");
			link.l1.go = "Exit_GoodBye";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
