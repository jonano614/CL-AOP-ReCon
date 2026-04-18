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
					dialog.text = StringFromKey("TristanBorcher_1", pchar, GetFullName(npchar));
					link.l1 = StringFromKey("TristanBorcher_2", GetFullName(pchar));
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = StringFromKey("TristanBorcher_3", pchar, GetFullName(npchar));
					link.l1 = StringFromKey("TristanBorcher_4", GetFullName(pchar));
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("TristanBorcher_5", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("TristanBorcher_6");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("TristanBorcher_7");
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("TristanBorcher_11", LinkRandPhrase(
							StringFromKey("TristanBorcher_8"),
							StringFromKey("TristanBorcher_9"),
							StringFromKey("TristanBorcher_10", pchar)));
				link.l3.go = "rumours_LSC";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = StringFromKey("TristanBorcher_12");
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (pchar.questTemp.LSC == "toSeekCrewInTavern") dialog.text = StringFromKey("TristanBorcher_13"); //сбор в таверне
					link.l8 = StringFromKey("TristanBorcher_14");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("TristanBorcher_15");
				link.l10.go = "exit";
			}
		break;
		case "FS_1":
			dialog.text = StringFromKey("TristanBorcher_16");
			link.l1 = StringFromKey("TristanBorcher_17");
			link.l1.go = "FT_2";
		break;
		case "FT_1":
			dialog.text = StringFromKey("TristanBorcher_18");
			link.l1 = StringFromKey("TristanBorcher_19", pchar);
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = StringFromKey("TristanBorcher_20");
			link.l1 = StringFromKey("TristanBorcher_21");
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
			dialog.text = StringFromKey("TristanBorcher_25", LinkRandPhrase(
						StringFromKey("TristanBorcher_22", pchar),
						StringFromKey("TristanBorcher_23", pchar),
						StringFromKey("TristanBorcher_24", pchar)));
			link.l1 = StringFromKey("TristanBorcher_26");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("TristanBorcher_27");
			link.l1 = StringFromKey("TristanBorcher_28");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("TristanBorcher_32", LinkRandPhrase(
						StringFromKey("TristanBorcher_29", pchar),
						StringFromKey("TristanBorcher_30"),
						StringFromKey("TristanBorcher_31", pchar)));
			link.l1 = StringFromKey("TristanBorcher_36", LinkRandPhrase(
						StringFromKey("TristanBorcher_33"),
						StringFromKey("TristanBorcher_34"),
						StringFromKey("TristanBorcher_35")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("TristanBorcher_37", npchar);
				link.l1 = StringFromKey("TristanBorcher_41", LinkRandPhrase(
							StringFromKey("TristanBorcher_38"),
							StringFromKey("TristanBorcher_39"),
							StringFromKey("TristanBorcher_40")));
			}
			else
			{
				dialog.text = StringFromKey("TristanBorcher_42", npchar);
				link.l1 = StringFromKey("TristanBorcher_45", RandPhraseSimple(
							StringFromKey("TristanBorcher_43", pchar),
							StringFromKey("TristanBorcher_44")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("TristanBorcher_46");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("TristanBorcher_47");
				Link.l1 = StringFromKey("TristanBorcher_48");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("TristanBorcher_49", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("TristanBorcher_50");
					link.l1 = StringFromKey("TristanBorcher_51", pchar);
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("TristanBorcher_52", GetFullName(sld));
					Link.l1 = StringFromKey("TristanBorcher_53");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("TristanBorcher_54");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("TristanBorcher_55", GetFullName(sld));
					Link.l1 = StringFromKey("TristanBorcher_56");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("TristanBorcher_57");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("TristanBorcher_58");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("TristanBorcher_59");
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
					dialog.text = StringFromKey("TristanBorcher_63", LinkRandPhrase(
								StringFromKey("TristanBorcher_60"),
								StringFromKey("TristanBorcher_61"),
								StringFromKey("TristanBorcher_62")));
					link.l1 = StringFromKey("TristanBorcher_66", RandPhraseSimple(
								StringFromKey("TristanBorcher_64"),
								StringFromKey("TristanBorcher_65")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("TristanBorcher_70", LinkRandPhrase(
								StringFromKey("TristanBorcher_67"),
								StringFromKey("TristanBorcher_68"),
								StringFromKey("TristanBorcher_69")));
					link.l1 = StringFromKey("TristanBorcher_73", RandPhraseSimple(
								StringFromKey("TristanBorcher_71"),
								StringFromKey("TristanBorcher_72")));
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
							dialog.text = StringFromKey("TristanBorcher_77", LinkRandPhrase(
										StringFromKey("TristanBorcher_74"),
										StringFromKey("TristanBorcher_75"),
										StringFromKey("TristanBorcher_76")));
						}
						else
						{
							dialog.text = StringFromKey("TristanBorcher_81", LinkRandPhrase(
										StringFromKey("TristanBorcher_78", npchar.quest.seekIdx.where),
										StringFromKey("TristanBorcher_79", npchar.quest.seekIdx.where),
										StringFromKey("TristanBorcher_80", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("TristanBorcher_85", LinkRandPhrase(
										StringFromKey("TristanBorcher_82", npchar.quest.seekIdx.where),
										StringFromKey("TristanBorcher_83"),
										StringFromKey("TristanBorcher_84")));
						}
						else
						{
							dialog.text = StringFromKey("TristanBorcher_89", LinkRandPhrase(
										StringFromKey("TristanBorcher_86", npchar.quest.seekIdx.where),
										StringFromKey("TristanBorcher_87", npchar.quest.seekIdx.where),
										StringFromKey("TristanBorcher_88", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("TristanBorcher_92", RandPhraseSimple(
								StringFromKey("TristanBorcher_90"),
								StringFromKey("TristanBorcher_91")));
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
							dialog.text = StringFromKey("TristanBorcher_96", LinkRandPhrase(
										StringFromKey("TristanBorcher_93"),
										StringFromKey("TristanBorcher_94"),
										StringFromKey("TristanBorcher_95")));
						}
						else
						{
							dialog.text = StringFromKey("TristanBorcher_100", LinkRandPhrase(
										StringFromKey("TristanBorcher_97", npchar.quest.seekIdx.where),
										StringFromKey("TristanBorcher_98", npchar.quest.seekIdx.where),
										StringFromKey("TristanBorcher_99", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("TristanBorcher_104", LinkRandPhrase(
										StringFromKey("TristanBorcher_101", npchar.quest.seekIdx.where),
										StringFromKey("TristanBorcher_102"),
										StringFromKey("TristanBorcher_103")));
						}
						else
						{
							dialog.text = StringFromKey("TristanBorcher_108", LinkRandPhrase(
										StringFromKey("TristanBorcher_105", npchar.quest.seekIdx.where),
										StringFromKey("TristanBorcher_106", npchar.quest.seekIdx.where),
										StringFromKey("TristanBorcher_107", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("TristanBorcher_111", RandPhraseSimple(
								StringFromKey("TristanBorcher_109", GetAddress_FormToNPC(NPChar)),
								StringFromKey("TristanBorcher_110")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("TristanBorcher_112", pchar);
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("TristanBorcher_113");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("TristanBorcher_114");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l3"))
			{
				link.l3 = StringFromKey("TristanBorcher_115");
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l4") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l4 = StringFromKey("TristanBorcher_116");
				link.l4.go = "ansewer_4";
			}
			link.l10 = StringFromKey("TristanBorcher_117");
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("TristanBorcher_118", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("TristanBorcher_119");
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = StringFromKey("TristanBorcher_120");
			link.l1 = StringFromKey("TristanBorcher_121");
			link.l1.go = "ansewer_1_2";
		break;
		case "ansewer_1_2":
			dialog.text = StringFromKey("TristanBorcher_122");
			link.l1 = StringFromKey("TristanBorcher_123");
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("TristanBorcher_124");
			link.l1 = StringFromKey("TristanBorcher_125");
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = StringFromKey("TristanBorcher_126");
			link.l1 = StringFromKey("TristanBorcher_127");
			link.l1.go = "ansewer_2_2";
		break;
		case "ansewer_2_2":
			dialog.text = StringFromKey("TristanBorcher_128");
			link.l1 = StringFromKey("TristanBorcher_129");
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("TristanBorcher_130");
			link.l1 = StringFromKey("TristanBorcher_131");
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = StringFromKey("TristanBorcher_132");
			link.l1 = StringFromKey("TristanBorcher_133");
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = StringFromKey("TristanBorcher_134");
			link.l1 = StringFromKey("TristanBorcher_135");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l4 = true;
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("TristanBorcher_136"),
						StringFromKey("TristanBorcher_137"),
						StringFromKey("TristanBorcher_138"),
						StringFromKey("TristanBorcher_139"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("TristanBorcher_140"),
						StringFromKey("TristanBorcher_141", pchar),
						StringFromKey("TristanBorcher_142"),
						StringFromKey("TristanBorcher_143", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("TristanBorcher_144");
			link.l1 = StringFromKey("TristanBorcher_145");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = StringFromKey("TristanBorcher_146");
			link.l1 = StringFromKey("TristanBorcher_147");
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = StringFromKey("TristanBorcher_148");
			link.l1 = StringFromKey("TristanBorcher_149");
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("TristanBorcher_150");
			link.l1 = StringFromKey("TristanBorcher_151");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("TristanBorcher_152");
			link.l1 = StringFromKey("TristanBorcher_153");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("TristanBorcher_154");
			link.l1 = StringFromKey("TristanBorcher_155");
			link.l1.go = "SeekCrew_all";
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("TristanBorcher_156");
			link.l1 = StringFromKey("TristanBorcher_157");
			link.l1.go = "GoodBye_1";
		break;
		case "GoodBye_1":
			dialog.text = StringFromKey("TristanBorcher_158");
			link.l1 = StringFromKey("TristanBorcher_159");
			link.l1.go = "Exit_GoodBye";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
