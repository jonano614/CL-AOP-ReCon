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
					dialog.text = StringFromKey("StefanKleyn_1", pchar);
					link.l1 = StringFromKey("StefanKleyn_2", pchar, pchar.name, GetFullName(pchar));
					link.l1.go = "FT_1";
				}
				else
				{
					dialog.text = StringFromKey("StefanKleyn_3", pchar);
					link.l1 = StringFromKey("StefanKleyn_4", pchar, pchar.name, GetFullName(pchar));
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("StefanKleyn_5", pchar);
				link.l1 = StringFromKey("StefanKleyn_6");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("StefanKleyn_7");
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("StefanKleyn_11", LinkRandPhrase(
							StringFromKey("StefanKleyn_8"),
							StringFromKey("StefanKleyn_9"),
							StringFromKey("StefanKleyn_10", pchar)));
				link.l3.go = "rumours_LSC";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = StringFromKey("StefanKleyn_12");
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (pchar.questTemp.LSC == "toSeekCrewInTavern") dialog.text = StringFromKey("StefanKleyn_13"); //сбор в таверне
					link.l8 = StringFromKey("StefanKleyn_14");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("StefanKleyn_15");
				link.l10.go = "exit";
			}
		break;
		case "FT_1":
			dialog.text = StringFromKey("StefanKleyn_16");
			link.l1 = StringFromKey("StefanKleyn_17");
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = StringFromKey("StefanKleyn_18");
			link.l1 = StringFromKey("StefanKleyn_19");
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = StringFromKey("StefanKleyn_20");
			link.l1 = StringFromKey("StefanKleyn_21");
			link.l1.go = "FT_4";
			link.l2 = StringFromKey("StefanKleyn_22");
			link.l2.go = "exit";
		break;
		case "FT_4":
			dialog.text = StringFromKey("StefanKleyn_23");
			link.l1 = StringFromKey("StefanKleyn_24");
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = StringFromKey("StefanKleyn_25");
			link.l1 = StringFromKey("StefanKleyn_26", pchar);
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = StringFromKey("StefanKleyn_27", pchar.lastname);
			link.l1 = StringFromKey("StefanKleyn_28");
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
			dialog.text = StringFromKey("StefanKleyn_32", LinkRandPhrase(
						StringFromKey("StefanKleyn_29", pchar),
						StringFromKey("StefanKleyn_30", pchar),
						StringFromKey("StefanKleyn_31", pchar)));
			link.l1 = StringFromKey("StefanKleyn_33");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("StefanKleyn_34");
			link.l1 = StringFromKey("StefanKleyn_35");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("StefanKleyn_39", LinkRandPhrase(
						StringFromKey("StefanKleyn_36", pchar),
						StringFromKey("StefanKleyn_37"),
						StringFromKey("StefanKleyn_38", pchar)));
			link.l1 = StringFromKey("StefanKleyn_43", LinkRandPhrase(
						StringFromKey("StefanKleyn_40"),
						StringFromKey("StefanKleyn_41"),
						StringFromKey("StefanKleyn_42")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("StefanKleyn_44", npchar);
				link.l1 = StringFromKey("StefanKleyn_48", LinkRandPhrase(
							StringFromKey("StefanKleyn_45"),
							StringFromKey("StefanKleyn_46"),
							StringFromKey("StefanKleyn_47")));
			}
			else
			{
				dialog.text = StringFromKey("StefanKleyn_49", npchar);
				link.l1 = StringFromKey("StefanKleyn_52", RandPhraseSimple(
							StringFromKey("StefanKleyn_50", pchar),
							StringFromKey("StefanKleyn_51")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("StefanKleyn_53");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("StefanKleyn_54");
				Link.l1 = StringFromKey("StefanKleyn_55");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("StefanKleyn_56", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("StefanKleyn_57");
					link.l1 = StringFromKey("StefanKleyn_58", pchar);
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("StefanKleyn_59", GetFullName(sld));
					Link.l1 = StringFromKey("StefanKleyn_60");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("StefanKleyn_61");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("StefanKleyn_62", GetFullName(sld));
					Link.l1 = StringFromKey("StefanKleyn_63");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("StefanKleyn_64");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("StefanKleyn_65");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("StefanKleyn_66");
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
					dialog.text = StringFromKey("StefanKleyn_70", LinkRandPhrase(
								StringFromKey("StefanKleyn_67"),
								StringFromKey("StefanKleyn_68"),
								StringFromKey("StefanKleyn_69")));
					link.l1 = StringFromKey("StefanKleyn_73", RandPhraseSimple(
								StringFromKey("StefanKleyn_71"),
								StringFromKey("StefanKleyn_72")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("StefanKleyn_77", LinkRandPhrase(
								StringFromKey("StefanKleyn_74"),
								StringFromKey("StefanKleyn_75"),
								StringFromKey("StefanKleyn_76")));
					link.l1 = StringFromKey("StefanKleyn_80", RandPhraseSimple(
								StringFromKey("StefanKleyn_78"),
								StringFromKey("StefanKleyn_79")));
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
							dialog.text = StringFromKey("StefanKleyn_84", LinkRandPhrase(
										StringFromKey("StefanKleyn_81"),
										StringFromKey("StefanKleyn_82"),
										StringFromKey("StefanKleyn_83")));
						}
						else
						{
							dialog.text = StringFromKey("StefanKleyn_88", LinkRandPhrase(
										StringFromKey("StefanKleyn_85", npchar.quest.seekIdx.where),
										StringFromKey("StefanKleyn_86", npchar.quest.seekIdx.where),
										StringFromKey("StefanKleyn_87", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("StefanKleyn_92", LinkRandPhrase(
										StringFromKey("StefanKleyn_89", npchar.quest.seekIdx.where),
										StringFromKey("StefanKleyn_90"),
										StringFromKey("StefanKleyn_91")));
						}
						else
						{
							dialog.text = StringFromKey("StefanKleyn_96", LinkRandPhrase(
										StringFromKey("StefanKleyn_93", npchar.quest.seekIdx.where),
										StringFromKey("StefanKleyn_94", npchar.quest.seekIdx.where),
										StringFromKey("StefanKleyn_95", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("StefanKleyn_99", RandPhraseSimple(
								StringFromKey("StefanKleyn_97"),
								StringFromKey("StefanKleyn_98")));
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
							dialog.text = StringFromKey("StefanKleyn_103", LinkRandPhrase(
										StringFromKey("StefanKleyn_100"),
										StringFromKey("StefanKleyn_101"),
										StringFromKey("StefanKleyn_102")));
						}
						else
						{
							dialog.text = StringFromKey("StefanKleyn_107", LinkRandPhrase(
										StringFromKey("StefanKleyn_104", npchar.quest.seekIdx.where),
										StringFromKey("StefanKleyn_105", npchar.quest.seekIdx.where),
										StringFromKey("StefanKleyn_106", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("StefanKleyn_111", LinkRandPhrase(
										StringFromKey("StefanKleyn_108", npchar.quest.seekIdx.where),
										StringFromKey("StefanKleyn_109"),
										StringFromKey("StefanKleyn_110")));
						}
						else
						{
							dialog.text = StringFromKey("StefanKleyn_115", LinkRandPhrase(
										StringFromKey("StefanKleyn_112", npchar.quest.seekIdx.where),
										StringFromKey("StefanKleyn_113", npchar.quest.seekIdx.where),
										StringFromKey("StefanKleyn_114", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("StefanKleyn_118", RandPhraseSimple(
								StringFromKey("StefanKleyn_116", GetAddress_FormToNPC(NPChar)),
								StringFromKey("StefanKleyn_117")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("StefanKleyn_119");
			if (!CheckAttribute(NextDiag, NodeName + ".l3"))
			{
				link.l3 = StringFromKey("StefanKleyn_120");
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("StefanKleyn_121");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("StefanKleyn_122");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l4") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l4 = StringFromKey("StefanKleyn_123");
				link.l4.go = "ansewer_4";
			}
			link.l10 = StringFromKey("StefanKleyn_124");
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("StefanKleyn_125", pchar, pchar.lastname);
			link.l1 = StringFromKey("StefanKleyn_126");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("StefanKleyn_127");
			link.l1 = StringFromKey("StefanKleyn_128");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("StefanKleyn_129");
			link.l1 = StringFromKey("StefanKleyn_130");
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = StringFromKey("StefanKleyn_131", pchar);
			link.l1 = StringFromKey("StefanKleyn_132");
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = StringFromKey("StefanKleyn_133");
			link.l1 = StringFromKey("StefanKleyn_134");
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = StringFromKey("StefanKleyn_135");
			link.l1 = StringFromKey("StefanKleyn_136");
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("StefanKleyn_137"),
						StringFromKey("StefanKleyn_138", pchar),
						StringFromKey("StefanKleyn_139", pchar),
						StringFromKey("StefanKleyn_140", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("StefanKleyn_141"),
						StringFromKey("StefanKleyn_142", pchar),
						StringFromKey("StefanKleyn_143"),
						StringFromKey("StefanKleyn_144", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("StefanKleyn_145");
			link.l1 = StringFromKey("StefanKleyn_146");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = StringFromKey("StefanKleyn_147");
			link.l1 = StringFromKey("StefanKleyn_148");
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = StringFromKey("StefanKleyn_149");
			link.l1 = StringFromKey("StefanKleyn_150");
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("StefanKleyn_151");
			link.l1 = StringFromKey("StefanKleyn_152");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("StefanKleyn_153", pchar);
			link.l1 = StringFromKey("StefanKleyn_154");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("StefanKleyn_155");
			link.l1 = StringFromKey("StefanKleyn_156");
			link.l1.go = "SeekCrew_4";
		break;
		case "SeekCrew_4":
			dialog.text = StringFromKey("StefanKleyn_157");
			link.l1 = StringFromKey("StefanKleyn_158");
			link.l1.go = "SeekCrew_all";
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("StefanKleyn_159");
			link.l1 = StringFromKey("StefanKleyn_160");
			link.l1.go = "GoodBye_1";
		break;
		case "GoodBye_1":
			dialog.text = StringFromKey("StefanKleyn_161");
			link.l1 = StringFromKey("StefanKleyn_162");
			link.l1.go = "Exit_GoodBye";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
