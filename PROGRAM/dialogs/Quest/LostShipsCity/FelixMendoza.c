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
					dialog.text = StringFromKey("FelixMendoza_1", pchar.lastname);
					link.l1 = StringFromKey("FelixMendoza_2", pchar);
					link.l1.go = "FT_1";
				}
				else
				{
					dialog.text = StringFromKey("FelixMendoza_3", pchar.lastname);
					link.l1 = StringFromKey("FelixMendoza_4");
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("FelixMendoza_5", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("FelixMendoza_6");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("FelixMendoza_7");
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("FelixMendoza_11", LinkRandPhrase(
							StringFromKey("FelixMendoza_8"),
							StringFromKey("FelixMendoza_9"),
							StringFromKey("FelixMendoza_10", pchar)));
				link.l3.go = "rumours_LSC";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(pchar, "questTemp.LSC.additional.balls"))
				{
					link.l8 = StringFromKey("FelixMendoza_12");
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (pchar.questTemp.LSC == "toSeekCrewInTavern") dialog.text = StringFromKey("FelixMendoza_13", pchar); //сбор в таверне
					link.l8 = StringFromKey("FelixMendoza_14");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("FelixMendoza_15");
				link.l10.go = "exit";
			}
		break;
		case "FT_1":
			dialog.text = StringFromKey("FelixMendoza_16", GetAddress_Form(NPChar), GetFullName(npchar));
			link.l1 = StringFromKey("FelixMendoza_17");
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = StringFromKey("FelixMendoza_18");
			link.l1 = StringFromKey("FelixMendoza_19");
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = StringFromKey("FelixMendoza_20");
			link.l1 = StringFromKey("FelixMendoza_21");
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = StringFromKey("FelixMendoza_22");
			link.l1 = StringFromKey("FelixMendoza_23");
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = StringFromKey("FelixMendoza_24");
			link.l1 = StringFromKey("FelixMendoza_25");
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = StringFromKey("FelixMendoza_26", pchar);
			link.l1 = StringFromKey("FelixMendoza_27");
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
			dialog.text = StringFromKey("FelixMendoza_31", LinkRandPhrase(
						StringFromKey("FelixMendoza_28", pchar),
						StringFromKey("FelixMendoza_29", pchar),
						StringFromKey("FelixMendoza_30", pchar)));
			link.l1 = StringFromKey("FelixMendoza_32");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("FelixMendoza_33");
			link.l1 = StringFromKey("FelixMendoza_34");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("FelixMendoza_38", LinkRandPhrase(
						StringFromKey("FelixMendoza_35", pchar),
						StringFromKey("FelixMendoza_36"),
						StringFromKey("FelixMendoza_37", pchar)));
			link.l1 = StringFromKey("FelixMendoza_42", LinkRandPhrase(
						StringFromKey("FelixMendoza_39"),
						StringFromKey("FelixMendoza_40"),
						StringFromKey("FelixMendoza_41")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("FelixMendoza_43", npchar);
				link.l1 = StringFromKey("FelixMendoza_47", LinkRandPhrase(
							StringFromKey("FelixMendoza_44"),
							StringFromKey("FelixMendoza_45"),
							StringFromKey("FelixMendoza_46")));
			}
			else
			{
				dialog.text = StringFromKey("FelixMendoza_48", npchar);
				link.l1 = StringFromKey("FelixMendoza_51", RandPhraseSimple(
							StringFromKey("FelixMendoza_49", pchar),
							StringFromKey("FelixMendoza_50")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("FelixMendoza_52");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("FelixMendoza_53");
				Link.l1 = StringFromKey("FelixMendoza_54");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("FelixMendoza_55", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("FelixMendoza_56");
					link.l1 = StringFromKey("FelixMendoza_57", pchar);
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("FelixMendoza_58", GetFullName(sld));
					Link.l1 = StringFromKey("FelixMendoza_59");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("FelixMendoza_60");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("FelixMendoza_61", GetFullName(sld));
					Link.l1 = StringFromKey("FelixMendoza_62");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("FelixMendoza_63");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("FelixMendoza_64");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("FelixMendoza_65");
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
					dialog.text = StringFromKey("FelixMendoza_69", LinkRandPhrase(
								StringFromKey("FelixMendoza_66"),
								StringFromKey("FelixMendoza_67"),
								StringFromKey("FelixMendoza_68")));
					link.l1 = StringFromKey("FelixMendoza_72", RandPhraseSimple(
								StringFromKey("FelixMendoza_70"),
								StringFromKey("FelixMendoza_71")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("FelixMendoza_76", LinkRandPhrase(
								StringFromKey("FelixMendoza_73"),
								StringFromKey("FelixMendoza_74"),
								StringFromKey("FelixMendoza_75")));
					link.l1 = StringFromKey("FelixMendoza_79", RandPhraseSimple(
								StringFromKey("FelixMendoza_77"),
								StringFromKey("FelixMendoza_78")));
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
							dialog.text = StringFromKey("FelixMendoza_83", LinkRandPhrase(
										StringFromKey("FelixMendoza_80"),
										StringFromKey("FelixMendoza_81"),
										StringFromKey("FelixMendoza_82")));
						}
						else
						{
							dialog.text = StringFromKey("FelixMendoza_87", LinkRandPhrase(
										StringFromKey("FelixMendoza_84", npchar.quest.seekIdx.where),
										StringFromKey("FelixMendoza_85", npchar.quest.seekIdx.where),
										StringFromKey("FelixMendoza_86", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("FelixMendoza_91", LinkRandPhrase(
										StringFromKey("FelixMendoza_88", npchar.quest.seekIdx.where),
										StringFromKey("FelixMendoza_89"),
										StringFromKey("FelixMendoza_90")));
						}
						else
						{
							dialog.text = StringFromKey("FelixMendoza_95", LinkRandPhrase(
										StringFromKey("FelixMendoza_92", npchar.quest.seekIdx.where),
										StringFromKey("FelixMendoza_93", npchar.quest.seekIdx.where),
										StringFromKey("FelixMendoza_94", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("FelixMendoza_98", RandPhraseSimple(
								StringFromKey("FelixMendoza_96"),
								StringFromKey("FelixMendoza_97")));
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
							dialog.text = StringFromKey("FelixMendoza_102", LinkRandPhrase(
										StringFromKey("FelixMendoza_99"),
										StringFromKey("FelixMendoza_100"),
										StringFromKey("FelixMendoza_101")));
						}
						else
						{
							dialog.text = StringFromKey("FelixMendoza_106", LinkRandPhrase(
										StringFromKey("FelixMendoza_103", npchar.quest.seekIdx.where),
										StringFromKey("FelixMendoza_104", npchar.quest.seekIdx.where),
										StringFromKey("FelixMendoza_105", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("FelixMendoza_110", LinkRandPhrase(
										StringFromKey("FelixMendoza_107", npchar.quest.seekIdx.where),
										StringFromKey("FelixMendoza_108"),
										StringFromKey("FelixMendoza_109")));
						}
						else
						{
							dialog.text = StringFromKey("FelixMendoza_114", LinkRandPhrase(
										StringFromKey("FelixMendoza_111", npchar.quest.seekIdx.where),
										StringFromKey("FelixMendoza_112", npchar.quest.seekIdx.where),
										StringFromKey("FelixMendoza_113", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("FelixMendoza_117", RandPhraseSimple(
								StringFromKey("FelixMendoza_115", GetAddress_FormToNPC(NPChar)),
								StringFromKey("FelixMendoza_116")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("FelixMendoza_118", pchar);
			if (!CheckAttribute(NextDiag, NodeName + ".l3"))
			{
				link.l3 = StringFromKey("FelixMendoza_119");
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("FelixMendoza_120");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("FelixMendoza_121");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l4") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l4 = StringFromKey("FelixMendoza_122");
				link.l4.go = "ansewer_4";
			}
			link.l10 = StringFromKey("FelixMendoza_123");
			link.l10.go = "exit";
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("FelixMendoza_124");
			link.l1 = StringFromKey("FelixMendoza_125");
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = StringFromKey("FelixMendoza_126", pchar);
			link.l1 = StringFromKey("FelixMendoza_127");
			link.l1.go = "int_quests";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("FelixMendoza_128");
			link.l1 = StringFromKey("FelixMendoza_129");
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = StringFromKey("FelixMendoza_130");
			link.l1 = StringFromKey("FelixMendoza_131");
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("FelixMendoza_132");
			link.l1 = StringFromKey("FelixMendoza_133");
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = StringFromKey("FelixMendoza_134");
			link.l1 = StringFromKey("FelixMendoza_135");
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = StringFromKey("FelixMendoza_136");
			link.l1 = StringFromKey("FelixMendoza_137");
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = StringFromKey("FelixMendoza_138");
			link.l1 = StringFromKey("FelixMendoza_139");
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FelixMendoza_140"),
						StringFromKey("FelixMendoza_141"),
						StringFromKey("FelixMendoza_142"),
						StringFromKey("FelixMendoza_143", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FelixMendoza_144", pchar),
						StringFromKey("FelixMendoza_145"),
						StringFromKey("FelixMendoza_146"),
						StringFromKey("FelixMendoza_147"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("FelixMendoza_148");
			link.l1 = StringFromKey("FelixMendoza_149");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = StringFromKey("FelixMendoza_150");
			link.l1 = StringFromKey("FelixMendoza_151");
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_BALLS, 100);
			AddQuestRecord("ISS_MainLine", "45");
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = StringFromKey("FelixMendoza_152");
			link.l1 = StringFromKey("FelixMendoza_153");
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("FelixMendoza_154");
			link.l1 = StringFromKey("FelixMendoza_155");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("FelixMendoza_156");
			link.l1 = StringFromKey("FelixMendoza_157");
			link.l1.go = "SeekCrew_all";
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("FelixMendoza_158", pchar);
			link.l1 = StringFromKey("FelixMendoza_159");
			link.l1.go = "GoodBye_1";
		break;
		case "GoodBye_1":
			dialog.text = StringFromKey("FelixMendoza_160", pchar);
			link.l1 = StringFromKey("FelixMendoza_161");
			link.l1.go = "Exit_GoodBye";
			GiveItem2Character(pchar, "map_providence");
		break;
	}
	NextDiag.PrevNode = NodeName;
}
