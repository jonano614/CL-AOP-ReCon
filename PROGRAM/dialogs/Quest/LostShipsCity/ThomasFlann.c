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
					dialog.text = StringFromKey("ThomasFlann_1", pchar, GetFullName(npchar));
					link.l1 = StringFromKey("ThomasFlann_2", pchar, GetFullName(pchar));
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = StringFromKey("ThomasFlann_3", pchar, GetFullName(npchar));
					link.l1 = StringFromKey("ThomasFlann_4", pchar, GetFullName(pchar));
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("ThomasFlann_5", pchar);
				link.l1 = StringFromKey("ThomasFlann_6");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("ThomasFlann_7");
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("ThomasFlann_11", LinkRandPhrase(
							StringFromKey("ThomasFlann_8"),
							StringFromKey("ThomasFlann_9"),
							StringFromKey("ThomasFlann_10", pchar)));
				link.l3.go = "rumours_LSC";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = StringFromKey("ThomasFlann_12");
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (pchar.questTemp.LSC == "toSeekCrewInTavern") dialog.text = StringFromKey("ThomasFlann_13"); //сбор в таверне
					link.l8 = StringFromKey("ThomasFlann_14");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("ThomasFlann_15");
				link.l10.go = "exit";
			}
		break;
		case "FS_1":
			dialog.text = StringFromKey("ThomasFlann_16", pchar);
			if (pchar.questTemp.LSC == "AdmiralIsWaiting") link.l1 = StringFromKey("ThomasFlann_17", pchar);
			else link.l1 = StringFromKey("ThomasFlann_18", pchar);
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = StringFromKey("ThomasFlann_19", pchar);
			link.l1 = StringFromKey("ThomasFlann_20", pchar);
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
			dialog.text = StringFromKey("ThomasFlann_24", LinkRandPhrase(
						StringFromKey("ThomasFlann_21", pchar),
						StringFromKey("ThomasFlann_22", pchar),
						StringFromKey("ThomasFlann_23", pchar)));
			link.l1 = StringFromKey("ThomasFlann_25");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("ThomasFlann_26");
			link.l1 = StringFromKey("ThomasFlann_27");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("ThomasFlann_31", LinkRandPhrase(
						StringFromKey("ThomasFlann_28", pchar),
						StringFromKey("ThomasFlann_29"),
						StringFromKey("ThomasFlann_30", pchar)));
			link.l1 = StringFromKey("ThomasFlann_35", LinkRandPhrase(
						StringFromKey("ThomasFlann_32"),
						StringFromKey("ThomasFlann_33"),
						StringFromKey("ThomasFlann_34")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("ThomasFlann_36", npchar);
				link.l1 = StringFromKey("ThomasFlann_40", LinkRandPhrase(
							StringFromKey("ThomasFlann_37"),
							StringFromKey("ThomasFlann_38"),
							StringFromKey("ThomasFlann_39")));
			}
			else
			{
				dialog.text = StringFromKey("ThomasFlann_41", npchar);
				link.l1 = StringFromKey("ThomasFlann_44", RandPhraseSimple(
							StringFromKey("ThomasFlann_42", pchar),
							StringFromKey("ThomasFlann_43")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("ThomasFlann_45");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("ThomasFlann_46");
				Link.l1 = StringFromKey("ThomasFlann_47");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("ThomasFlann_48", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("ThomasFlann_49");
					link.l1 = StringFromKey("ThomasFlann_50", pchar);
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("ThomasFlann_51", GetFullName(sld));
					Link.l1 = StringFromKey("ThomasFlann_52");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("ThomasFlann_53");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("ThomasFlann_54", GetFullName(sld));
					Link.l1 = StringFromKey("ThomasFlann_55");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("ThomasFlann_56");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("ThomasFlann_57");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("ThomasFlann_58");
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
					dialog.text = StringFromKey("ThomasFlann_62", LinkRandPhrase(
								StringFromKey("ThomasFlann_59"),
								StringFromKey("ThomasFlann_60"),
								StringFromKey("ThomasFlann_61")));
					link.l1 = StringFromKey("ThomasFlann_65", RandPhraseSimple(
								StringFromKey("ThomasFlann_63"),
								StringFromKey("ThomasFlann_64")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("ThomasFlann_69", LinkRandPhrase(
								StringFromKey("ThomasFlann_66"),
								StringFromKey("ThomasFlann_67"),
								StringFromKey("ThomasFlann_68")));
					link.l1 = StringFromKey("ThomasFlann_72", RandPhraseSimple(
								StringFromKey("ThomasFlann_70"),
								StringFromKey("ThomasFlann_71")));
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
							dialog.text = StringFromKey("ThomasFlann_76", LinkRandPhrase(
										StringFromKey("ThomasFlann_73"),
										StringFromKey("ThomasFlann_74"),
										StringFromKey("ThomasFlann_75")));
						}
						else
						{
							dialog.text = StringFromKey("ThomasFlann_80", LinkRandPhrase(
										StringFromKey("ThomasFlann_77", npchar.quest.seekIdx.where),
										StringFromKey("ThomasFlann_78", npchar.quest.seekIdx.where),
										StringFromKey("ThomasFlann_79", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("ThomasFlann_84", LinkRandPhrase(
										StringFromKey("ThomasFlann_81", npchar.quest.seekIdx.where),
										StringFromKey("ThomasFlann_82"),
										StringFromKey("ThomasFlann_83")));
						}
						else
						{
							dialog.text = StringFromKey("ThomasFlann_88", LinkRandPhrase(
										StringFromKey("ThomasFlann_85", npchar.quest.seekIdx.where),
										StringFromKey("ThomasFlann_86", npchar.quest.seekIdx.where),
										StringFromKey("ThomasFlann_87", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("ThomasFlann_91", RandPhraseSimple(
								StringFromKey("ThomasFlann_89"),
								StringFromKey("ThomasFlann_90")));
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
							dialog.text = StringFromKey("ThomasFlann_95", LinkRandPhrase(
										StringFromKey("ThomasFlann_92"),
										StringFromKey("ThomasFlann_93"),
										StringFromKey("ThomasFlann_94")));
						}
						else
						{
							dialog.text = StringFromKey("ThomasFlann_99", LinkRandPhrase(
										StringFromKey("ThomasFlann_96", npchar.quest.seekIdx.where),
										StringFromKey("ThomasFlann_97", npchar.quest.seekIdx.where),
										StringFromKey("ThomasFlann_98", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("ThomasFlann_103", LinkRandPhrase(
										StringFromKey("ThomasFlann_100", npchar.quest.seekIdx.where),
										StringFromKey("ThomasFlann_101"),
										StringFromKey("ThomasFlann_102")));
						}
						else
						{
							dialog.text = StringFromKey("ThomasFlann_107", LinkRandPhrase(
										StringFromKey("ThomasFlann_104", npchar.quest.seekIdx.where),
										StringFromKey("ThomasFlann_105", npchar.quest.seekIdx.where),
										StringFromKey("ThomasFlann_106", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("ThomasFlann_110", RandPhraseSimple(
								StringFromKey("ThomasFlann_108", GetAddress_FormToNPC(NPChar)),
								StringFromKey("ThomasFlann_109")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("ThomasFlann_111");
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("ThomasFlann_112");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("ThomasFlann_113");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l3"))
			{
				link.l3 = StringFromKey("ThomasFlann_114");
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l4"))
			{
				link.l4 = StringFromKey("ThomasFlann_115");
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l5") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l5 = StringFromKey("ThomasFlann_116");
				link.l5.go = "ansewer_5";
			}
			link.l10 = StringFromKey("ThomasFlann_117");
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("ThomasFlann_118", pchar);
			link.l1 = StringFromKey("ThomasFlann_119");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("ThomasFlann_120");
			link.l1 = StringFromKey("ThomasFlann_121");
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = StringFromKey("ThomasFlann_122");
			link.l1 = StringFromKey("ThomasFlann_123");
			link.l1.go = "ansewer_2_2";
		break;
		case "ansewer_2_2":
			dialog.text = StringFromKey("ThomasFlann_124");
			link.l1 = StringFromKey("ThomasFlann_125");
			link.l1.go = "ansewer_2_3";
		break;
		case "ansewer_2_3":
			dialog.text = StringFromKey("ThomasFlann_126");
			link.l1 = StringFromKey("ThomasFlann_127");
			link.l1.go = "ansewer_2_4";
		break;
		case "ansewer_2_4":
			dialog.text = StringFromKey("ThomasFlann_128");
			link.l1 = StringFromKey("ThomasFlann_129");
			link.l1.go = "ansewer_2_5";
		break;
		case "ansewer_2_5":
			dialog.text = StringFromKey("ThomasFlann_130");
			link.l1 = StringFromKey("ThomasFlann_131");
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("ThomasFlann_132");
			link.l1 = StringFromKey("ThomasFlann_133");
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = StringFromKey("ThomasFlann_134");
			link.l1 = StringFromKey("ThomasFlann_135");
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = StringFromKey("ThomasFlann_136");
			link.l1 = StringFromKey("ThomasFlann_137");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_5":
			dialog.text = StringFromKey("ThomasFlann_138");
			link.l1 = StringFromKey("ThomasFlann_139");
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = StringFromKey("ThomasFlann_140");
			link.l1 = StringFromKey("ThomasFlann_141");
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("ThomasFlann_142"),
						StringFromKey("ThomasFlann_143", pchar),
						StringFromKey("ThomasFlann_144", pchar),
						StringFromKey("ThomasFlann_145", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("ThomasFlann_146"),
						StringFromKey("ThomasFlann_147", pchar),
						StringFromKey("ThomasFlann_148"),
						StringFromKey("ThomasFlann_149", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("ThomasFlann_150");
			link.l1 = StringFromKey("ThomasFlann_151");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = StringFromKey("ThomasFlann_152");
			link.l1 = StringFromKey("ThomasFlann_153");
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = StringFromKey("ThomasFlann_154", pchar);
			link.l1 = StringFromKey("ThomasFlann_155");
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("ThomasFlann_156");
			link.l1 = StringFromKey("ThomasFlann_157");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("ThomasFlann_158");
			link.l1 = StringFromKey("ThomasFlann_159");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("ThomasFlann_160");
			link.l1 = StringFromKey("ThomasFlann_161");
			link.l1.go = "SeekCrew_all";
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("ThomasFlann_162");
			link.l1 = StringFromKey("ThomasFlann_163");
			link.l1.go = "Exit_GoodBye";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
