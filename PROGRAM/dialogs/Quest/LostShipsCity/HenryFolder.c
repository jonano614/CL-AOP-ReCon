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
					dialog.text = StringFromKey("HenryFolder_1", TimeGreeting(), pchar.lastname);
					link.l1 = StringFromKey("HenryFolder_2");
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = StringFromKey("HenryFolder_3", TimeGreeting(), pchar.lastname);
					link.l1 = StringFromKey("HenryFolder_4");
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("HenryFolder_5", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("HenryFolder_6");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("HenryFolder_7");
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("HenryFolder_11", LinkRandPhrase(
							StringFromKey("HenryFolder_8"),
							StringFromKey("HenryFolder_9"),
							StringFromKey("HenryFolder_10", pchar)));
				link.l3.go = "rumours_LSC";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = StringFromKey("HenryFolder_12");
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (!CheckAttribute(npchar, "toSeekCrewInTavern") && pchar.questTemp.LSC == "toSeekCrewInTavern")
						dialog.text = StringFromKey("HenryFolder_13"); //сбор в таверне
					link.l8 = StringFromKey("HenryFolder_14");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("HenryFolder_15");
				link.l10.go = "exit";
			}
		break;
		case "FS_1":
			dialog.text = StringFromKey("HenryFolder_16", GetFullName(npchar));
			link.l1 = StringFromKey("HenryFolder_17");
			link.l1.go = "FT_5";
		break;
		case "FT_1":
			dialog.text = StringFromKey("HenryFolder_18");
			link.l1 = StringFromKey("HenryFolder_19");
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = StringFromKey("HenryFolder_20", GetFullName(npchar));
			link.l1 = StringFromKey("HenryFolder_21");
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = StringFromKey("HenryFolder_22");
			link.l1 = StringFromKey("HenryFolder_23");
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = StringFromKey("HenryFolder_24");
			link.l1 = StringFromKey("HenryFolder_25");
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = StringFromKey("HenryFolder_26");
			link.l1 = StringFromKey("HenryFolder_27");
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = StringFromKey("HenryFolder_28");
			link.l1 = StringFromKey("HenryFolder_29");
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = StringFromKey("HenryFolder_30");
			link.l1 = StringFromKey("HenryFolder_31");
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = StringFromKey("HenryFolder_32");
			link.l1 = StringFromKey("HenryFolder_33", pchar);
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = StringFromKey("HenryFolder_34");
			link.l1 = StringFromKey("HenryFolder_35", pchar);
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			dialog.text = StringFromKey("HenryFolder_36");
			link.l1 = StringFromKey("HenryFolder_37");
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
			dialog.text = StringFromKey("HenryFolder_41", LinkRandPhrase(
						StringFromKey("HenryFolder_38", pchar),
						StringFromKey("HenryFolder_39", pchar),
						StringFromKey("HenryFolder_40", pchar)));
			link.l1 = StringFromKey("HenryFolder_42");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("HenryFolder_43");
			link.l1 = StringFromKey("HenryFolder_44");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("HenryFolder_48", LinkRandPhrase(
						StringFromKey("HenryFolder_45", pchar),
						StringFromKey("HenryFolder_46"),
						StringFromKey("HenryFolder_47", pchar)));
			link.l1 = StringFromKey("HenryFolder_52", LinkRandPhrase(
						StringFromKey("HenryFolder_49"),
						StringFromKey("HenryFolder_50"),
						StringFromKey("HenryFolder_51")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("HenryFolder_53", npchar);
				link.l1 = StringFromKey("HenryFolder_57", LinkRandPhrase(
							StringFromKey("HenryFolder_54"),
							StringFromKey("HenryFolder_55"),
							StringFromKey("HenryFolder_56")));
			}
			else
			{
				dialog.text = StringFromKey("HenryFolder_58", npchar);
				link.l1 = StringFromKey("HenryFolder_61", RandPhraseSimple(
							StringFromKey("HenryFolder_59", pchar),
							StringFromKey("HenryFolder_60")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("HenryFolder_62");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("HenryFolder_63");
				Link.l1 = StringFromKey("HenryFolder_64");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("HenryFolder_65", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("HenryFolder_66");
					link.l1 = StringFromKey("HenryFolder_67", pchar);
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("HenryFolder_68", GetFullName(sld));
					Link.l1 = StringFromKey("HenryFolder_69");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("HenryFolder_70");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("HenryFolder_71", GetFullName(sld));
					Link.l1 = StringFromKey("HenryFolder_72");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("HenryFolder_73");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("HenryFolder_74");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("HenryFolder_75");
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
					dialog.text = StringFromKey("HenryFolder_79", LinkRandPhrase(
								StringFromKey("HenryFolder_76"),
								StringFromKey("HenryFolder_77"),
								StringFromKey("HenryFolder_78")));
					link.l1 = StringFromKey("HenryFolder_82", RandPhraseSimple(
								StringFromKey("HenryFolder_80"),
								StringFromKey("HenryFolder_81")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("HenryFolder_86", LinkRandPhrase(
								StringFromKey("HenryFolder_83"),
								StringFromKey("HenryFolder_84"),
								StringFromKey("HenryFolder_85")));
					link.l1 = StringFromKey("HenryFolder_89", RandPhraseSimple(
								StringFromKey("HenryFolder_87"),
								StringFromKey("HenryFolder_88")));
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
							dialog.text = StringFromKey("HenryFolder_93", LinkRandPhrase(
										StringFromKey("HenryFolder_90"),
										StringFromKey("HenryFolder_91"),
										StringFromKey("HenryFolder_92")));
						}
						else
						{
							dialog.text = StringFromKey("HenryFolder_97", LinkRandPhrase(
										StringFromKey("HenryFolder_94", npchar.quest.seekIdx.where),
										StringFromKey("HenryFolder_95", npchar.quest.seekIdx.where),
										StringFromKey("HenryFolder_96", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("HenryFolder_101", LinkRandPhrase(
										StringFromKey("HenryFolder_98", npchar.quest.seekIdx.where),
										StringFromKey("HenryFolder_99"),
										StringFromKey("HenryFolder_100")));
						}
						else
						{
							dialog.text = StringFromKey("HenryFolder_105", LinkRandPhrase(
										StringFromKey("HenryFolder_102", npchar.quest.seekIdx.where),
										StringFromKey("HenryFolder_103", npchar.quest.seekIdx.where),
										StringFromKey("HenryFolder_104", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("HenryFolder_108", RandPhraseSimple(
								StringFromKey("HenryFolder_106"),
								StringFromKey("HenryFolder_107")));
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
							dialog.text = StringFromKey("HenryFolder_112", LinkRandPhrase(
										StringFromKey("HenryFolder_109"),
										StringFromKey("HenryFolder_110"),
										StringFromKey("HenryFolder_111")));
						}
						else
						{
							dialog.text = StringFromKey("HenryFolder_116", LinkRandPhrase(
										StringFromKey("HenryFolder_113", npchar.quest.seekIdx.where),
										StringFromKey("HenryFolder_114", npchar.quest.seekIdx.where),
										StringFromKey("HenryFolder_115", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("HenryFolder_120", LinkRandPhrase(
										StringFromKey("HenryFolder_117", npchar.quest.seekIdx.where),
										StringFromKey("HenryFolder_118"),
										StringFromKey("HenryFolder_119")));
						}
						else
						{
							dialog.text = StringFromKey("HenryFolder_124", LinkRandPhrase(
										StringFromKey("HenryFolder_121", npchar.quest.seekIdx.where),
										StringFromKey("HenryFolder_122", npchar.quest.seekIdx.where),
										StringFromKey("HenryFolder_123", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("HenryFolder_127", RandPhraseSimple(
								StringFromKey("HenryFolder_125", GetAddress_FormToNPC(NPChar)),
								StringFromKey("HenryFolder_126")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("HenryFolder_128", pchar);
			if (!CheckAttribute(NextDiag, NodeName + ".l4"))
			{
				link.l4 = StringFromKey("HenryFolder_129");
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("HenryFolder_130");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("HenryFolder_131");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l3"))
			{
				link.l3 = StringFromKey("HenryFolder_132");
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l5") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l5 = StringFromKey("HenryFolder_133");
				link.l5.go = "ansewer_5";
			}
			link.l10 = StringFromKey("HenryFolder_134");
			link.l10.go = "exit";
		break;
		case "ansewer_4":
			dialog.text = StringFromKey("HenryFolder_135");
			link.l1 = StringFromKey("HenryFolder_136");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("HenryFolder_137");
			link.l1 = StringFromKey("HenryFolder_138");
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = StringFromKey("HenryFolder_139");
			link.l1 = StringFromKey("HenryFolder_140");
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("HenryFolder_141", pchar);
			link.l1 = StringFromKey("HenryFolder_142");
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = StringFromKey("HenryFolder_143");
			link.l1 = StringFromKey("HenryFolder_144");
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("HenryFolder_145");
			link.l1 = StringFromKey("HenryFolder_146", pchar);
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_5":
			dialog.text = StringFromKey("HenryFolder_147");
			link.l1 = StringFromKey("HenryFolder_148");
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = StringFromKey("HenryFolder_149");
			link.l1 = StringFromKey("HenryFolder_150");
			link.l1.go = "ansewer_5_2";
		break;
		case "ansewer_5_2":
			dialog.text = StringFromKey("HenryFolder_151");
			link.l1 = StringFromKey("HenryFolder_152");
			link.l1.go = "ansewer_5_3";
		break;
		case "ansewer_5_3":
			dialog.text = StringFromKey("HenryFolder_153");
			link.l1 = StringFromKey("HenryFolder_154");
			link.l1.go = "ansewer_5_4";
		break;
		case "ansewer_5_4":
			dialog.text = StringFromKey("HenryFolder_155");
			link.l1 = StringFromKey("HenryFolder_156");
			link.l1.go = "ansewer_5_5";
		break;
		case "ansewer_5_5":
			dialog.text = StringFromKey("HenryFolder_157");
			link.l1 = StringFromKey("HenryFolder_158");
			link.l1.go = "int_quests";
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("HenryFolder_159"),
						StringFromKey("HenryFolder_160"),
						StringFromKey("HenryFolder_161"),
						StringFromKey("HenryFolder_162"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("HenryFolder_163"),
						StringFromKey("HenryFolder_164", pchar),
						StringFromKey("HenryFolder_165"),
						StringFromKey("HenryFolder_166"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("HenryFolder_167");
			link.l1 = StringFromKey("HenryFolder_168");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = StringFromKey("HenryFolder_169");
			link.l1 = StringFromKey("HenryFolder_170");
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = StringFromKey("HenryFolder_171");
			link.l1 = StringFromKey("HenryFolder_172");
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("HenryFolder_173");
			link.l1 = StringFromKey("HenryFolder_174");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("HenryFolder_175");
			link.l1 = StringFromKey("HenryFolder_176");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("HenryFolder_177");
			link.l1 = StringFromKey("HenryFolder_178");
			link.l1.go = "SeekCrew_all";
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("HenryFolder_179");
			link.l1 = StringFromKey("HenryFolder_180");
			link.l1.go = "GoodBye_1";
		break;
		case "GoodBye_1":
			dialog.text = StringFromKey("HenryFolder_181");
			link.l1 = StringFromKey("HenryFolder_182");
			link.l1.go = "Exit_GoodBye";
			GiveItem2Character(pchar, "jewelry9");
			GiveItem2Character(pchar, "jewelry8");
		break;
	}
	NextDiag.PrevNode = NodeName;
}
