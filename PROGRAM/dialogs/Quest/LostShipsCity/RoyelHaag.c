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
					dialog.text = StringFromKey("RoyelHaag_1");
					link.l1 = StringFromKey("RoyelHaag_2", pchar);
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = StringFromKey("RoyelHaag_3");
					link.l1 = StringFromKey("RoyelHaag_4", pchar, GetFullName(pchar));
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("RoyelHaag_5", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("RoyelHaag_6");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("RoyelHaag_7");
				link.l3 = StringFromKey("RoyelHaag_11", LinkRandPhrase(
							StringFromKey("RoyelHaag_8"),
							StringFromKey("RoyelHaag_9"),
							StringFromKey("RoyelHaag_10", pchar)));
				link.l3.go = "rumours_LSC";
				link.l2.go = "int_quests";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = StringFromKey("RoyelHaag_12");
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (pchar.questTemp.LSC == "toSeekCrewInTavern") dialog.text = StringFromKey("RoyelHaag_13"); //сбор в таверне
					link.l8 = StringFromKey("RoyelHaag_14");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("RoyelHaag_15");
				link.l10.go = "exit";
			}
		break;
		case "FS_1":
			dialog.text = StringFromKey("RoyelHaag_16");
			link.l1 = StringFromKey("RoyelHaag_17", pchar, GetFullName(pchar));
			link.l1.go = "FT_1";
		break;
		case "FT_1":
			dialog.text = StringFromKey("RoyelHaag_18", GetFullName(npchar));
			link.l1 = StringFromKey("RoyelHaag_19", npchar.lastname);
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = StringFromKey("RoyelHaag_20");
			link.l1 = StringFromKey("RoyelHaag_21", pchar);
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = StringFromKey("RoyelHaag_22");
			link.l1 = StringFromKey("RoyelHaag_23");
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = StringFromKey("RoyelHaag_24");
			link.l1 = StringFromKey("RoyelHaag_25");
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = StringFromKey("RoyelHaag_26");
			link.l1 = StringFromKey("RoyelHaag_27", npchar.lastname);
			link.l1.go = "FT_6";

			if (!CheckAttribute(pchar, "questTemp.LSC.lostDecster"))
			{
				AddQuestRecord("LSC_findDekster", "2");
				AddQuestUserData("LSC_findDekster", "sSex", GetSexPhrase("", "а"));
				AddQuestUserData("LSC_findDekster", "sSex1", GetSexPhrase("ен", "на"));
				AddLandQuestMark_Main(CharacterFromID("LeaToors"), "LSC_findDekster");
				LSC_UpdateQuestMarksToCitizens();
			}
		break;
		case "FT_6":
			dialog.text = StringFromKey("RoyelHaag_28");
			link.l1 = StringFromKey("RoyelHaag_29");
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = StringFromKey("RoyelHaag_30");
			link.l1 = StringFromKey("RoyelHaag_31", npchar.lastname);
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
			dialog.text = StringFromKey("RoyelHaag_35", LinkRandPhrase(
						StringFromKey("RoyelHaag_32", pchar),
						StringFromKey("RoyelHaag_33", pchar),
						StringFromKey("RoyelHaag_34", pchar)));
			link.l1 = StringFromKey("RoyelHaag_36");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("RoyelHaag_37");
			link.l1 = StringFromKey("RoyelHaag_38");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("RoyelHaag_42", LinkRandPhrase(
						StringFromKey("RoyelHaag_39", pchar),
						StringFromKey("RoyelHaag_40"),
						StringFromKey("RoyelHaag_41", pchar)));
			link.l1 = StringFromKey("RoyelHaag_46", LinkRandPhrase(
						StringFromKey("RoyelHaag_43"),
						StringFromKey("RoyelHaag_44"),
						StringFromKey("RoyelHaag_45")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("RoyelHaag_47", npchar);
				link.l1 = StringFromKey("RoyelHaag_51", LinkRandPhrase(
							StringFromKey("RoyelHaag_48"),
							StringFromKey("RoyelHaag_49"),
							StringFromKey("RoyelHaag_50")));
			}
			else
			{
				dialog.text = StringFromKey("RoyelHaag_52", npchar);
				link.l1 = StringFromKey("RoyelHaag_55", RandPhraseSimple(
							StringFromKey("RoyelHaag_53", pchar),
							StringFromKey("RoyelHaag_54")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("RoyelHaag_56");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("RoyelHaag_57");
				Link.l1 = StringFromKey("RoyelHaag_58");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("RoyelHaag_59", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("RoyelHaag_60");
					link.l1 = StringFromKey("RoyelHaag_61", pchar);
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("RoyelHaag_62", GetFullName(sld));
					Link.l1 = StringFromKey("RoyelHaag_63");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("RoyelHaag_64");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("RoyelHaag_65", GetFullName(sld));
					Link.l1 = StringFromKey("RoyelHaag_66");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("RoyelHaag_67");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("RoyelHaag_68");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("RoyelHaag_69");
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
					dialog.text = StringFromKey("RoyelHaag_73", LinkRandPhrase(
								StringFromKey("RoyelHaag_70"),
								StringFromKey("RoyelHaag_71"),
								StringFromKey("RoyelHaag_72")));
					link.l1 = StringFromKey("RoyelHaag_76", RandPhraseSimple(
								StringFromKey("RoyelHaag_74"),
								StringFromKey("RoyelHaag_75")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("RoyelHaag_80", LinkRandPhrase(
								StringFromKey("RoyelHaag_77"),
								StringFromKey("RoyelHaag_78"),
								StringFromKey("RoyelHaag_79")));
					link.l1 = StringFromKey("RoyelHaag_83", RandPhraseSimple(
								StringFromKey("RoyelHaag_81"),
								StringFromKey("RoyelHaag_82")));
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
							dialog.text = StringFromKey("RoyelHaag_87", LinkRandPhrase(
										StringFromKey("RoyelHaag_84"),
										StringFromKey("RoyelHaag_85"),
										StringFromKey("RoyelHaag_86")));
						}
						else
						{
							dialog.text = StringFromKey("RoyelHaag_91", LinkRandPhrase(
										StringFromKey("RoyelHaag_88", npchar.quest.seekIdx.where),
										StringFromKey("RoyelHaag_89", npchar.quest.seekIdx.where),
										StringFromKey("RoyelHaag_90", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("RoyelHaag_95", LinkRandPhrase(
										StringFromKey("RoyelHaag_92", npchar.quest.seekIdx.where),
										StringFromKey("RoyelHaag_93"),
										StringFromKey("RoyelHaag_94")));
						}
						else
						{
							dialog.text = StringFromKey("RoyelHaag_99", LinkRandPhrase(
										StringFromKey("RoyelHaag_96", npchar.quest.seekIdx.where),
										StringFromKey("RoyelHaag_97", npchar.quest.seekIdx.where),
										StringFromKey("RoyelHaag_98", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("RoyelHaag_102", RandPhraseSimple(
								StringFromKey("RoyelHaag_100"),
								StringFromKey("RoyelHaag_101")));
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
							dialog.text = StringFromKey("RoyelHaag_106", LinkRandPhrase(
										StringFromKey("RoyelHaag_103"),
										StringFromKey("RoyelHaag_104"),
										StringFromKey("RoyelHaag_105")));
						}
						else
						{
							dialog.text = StringFromKey("RoyelHaag_110", LinkRandPhrase(
										StringFromKey("RoyelHaag_107", npchar.quest.seekIdx.where),
										StringFromKey("RoyelHaag_108", npchar.quest.seekIdx.where),
										StringFromKey("RoyelHaag_109", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("RoyelHaag_114", LinkRandPhrase(
										StringFromKey("RoyelHaag_111", npchar.quest.seekIdx.where),
										StringFromKey("RoyelHaag_112"),
										StringFromKey("RoyelHaag_113")));
						}
						else
						{
							dialog.text = StringFromKey("RoyelHaag_118", LinkRandPhrase(
										StringFromKey("RoyelHaag_115", npchar.quest.seekIdx.where),
										StringFromKey("RoyelHaag_116", npchar.quest.seekIdx.where),
										StringFromKey("RoyelHaag_117", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("RoyelHaag_121", RandPhraseSimple(
								StringFromKey("RoyelHaag_119", GetAddress_FormToNPC(NPChar)),
								StringFromKey("RoyelHaag_120")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("RoyelHaag_122", pchar);
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("RoyelHaag_123");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("RoyelHaag_124");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l3"))
			{
				link.l3 = StringFromKey("RoyelHaag_125");
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l4") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l4 = StringFromKey("RoyelHaag_126");
				link.l4.go = "ansewer_4";
			}
			link.l10 = StringFromKey("RoyelHaag_127");
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("RoyelHaag_128", pchar);
			link.l1 = StringFromKey("RoyelHaag_129");
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = StringFromKey("RoyelHaag_130");
			link.l1 = StringFromKey("RoyelHaag_131", pchar);
			link.l1.go = "ansewer_1_2";
		break;
		case "ansewer_1_2":
			dialog.text = StringFromKey("RoyelHaag_132");
			link.l1 = StringFromKey("RoyelHaag_133");
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("RoyelHaag_134");
			link.l1 = StringFromKey("RoyelHaag_135");
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = StringFromKey("RoyelHaag_136");
			link.l1 = StringFromKey("RoyelHaag_137");
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("RoyelHaag_138", pchar);
			link.l1 = StringFromKey("RoyelHaag_139");
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = StringFromKey("RoyelHaag_140");
			link.l1 = StringFromKey("RoyelHaag_141");
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = StringFromKey("RoyelHaag_142");
			link.l1 = StringFromKey("RoyelHaag_143");
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = StringFromKey("RoyelHaag_144");
			link.l1 = StringFromKey("RoyelHaag_145");
			link.l1.go = "int_quests";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("RoyelHaag_146"),
						StringFromKey("RoyelHaag_147", pchar),
						StringFromKey("RoyelHaag_148", pchar),
						StringFromKey("RoyelHaag_149", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("RoyelHaag_150"),
						StringFromKey("RoyelHaag_151", pchar),
						StringFromKey("RoyelHaag_152"),
						StringFromKey("RoyelHaag_153", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("RoyelHaag_154");
			link.l1 = StringFromKey("RoyelHaag_155", pchar);
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = StringFromKey("RoyelHaag_156");
			link.l1 = StringFromKey("RoyelHaag_157");
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("RoyelHaag_158");
			link.l1 = StringFromKey("RoyelHaag_159");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("RoyelHaag_160");
			link.l1 = StringFromKey("RoyelHaag_161");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("RoyelHaag_162");
			link.l1 = StringFromKey("RoyelHaag_163");
			link.l1.go = "SeekCrew_all";
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("RoyelHaag_164");
			link.l1 = StringFromKey("RoyelHaag_165");
			link.l1.go = "GoodBye_1";
		break;
		case "GoodBye_1":
			dialog.text = StringFromKey("RoyelHaag_166");
			link.l1 = StringFromKey("RoyelHaag_167");
			link.l1.go = "GoodBye_2";
		break;
		case "GoodBye_2":
			dialog.text = StringFromKey("RoyelHaag_168");
			link.l1 = StringFromKey("RoyelHaag_169");
			link.l1.go = "GoodBye_3";
		break;
		case "GoodBye_3":
			dialog.text = StringFromKey("RoyelHaag_170");
			link.l1 = StringFromKey("RoyelHaag_171");
			link.l1.go = "Exit_GoodBye";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
