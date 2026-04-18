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
					dialog.text = StringFromKey("ZhilBaru_1", GetFullName(npchar));
					link.l1 = StringFromKey("ZhilBaru_2", GetFullName(pchar));
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = StringFromKey("ZhilBaru_3", GetFullName(npchar));
					link.l1 = StringFromKey("ZhilBaru_4", GetFullName(pchar));
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("ZhilBaru_5", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("ZhilBaru_6");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("ZhilBaru_7");
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("ZhilBaru_11", LinkRandPhrase(
							StringFromKey("ZhilBaru_8"),
							StringFromKey("ZhilBaru_9"),
							StringFromKey("ZhilBaru_10", pchar)));
				link.l3.go = "rumours_LSC";
				//освобождение мужа Элис Тейлор
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toZhilBaru")
				{
					link.l5 = StringFromKey("ZhilBaru_12");
					link.l5.go = "ELTHusb_SF";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (pchar.questTemp.LSC == "toSeekCrewInTavern") dialog.text = StringFromKey("ZhilBaru_13"); //сбор в таверне
					link.l8 = StringFromKey("ZhilBaru_14");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("ZhilBaru_15");
				link.l10.go = "exit";
			}
		break;
		case "FS_1":
			dialog.text = StringFromKey("ZhilBaru_16");
			link.l1 = StringFromKey("ZhilBaru_17", pchar);
			link.l1.go = "FS_2";
		break;
		case "FS_2":
			dialog.text = StringFromKey("ZhilBaru_18");
			link.l1 = StringFromKey("ZhilBaru_19");
			link.l1.go = "FT_1";
		break;
		case "FT_1":
			dialog.text = StringFromKey("ZhilBaru_20");
			link.l1 = StringFromKey("ZhilBaru_21", pchar);
			link.l1.go = "FT_2";
			link.l2 = StringFromKey("ZhilBaru_22");
			link.l2.go = "FT_4";
		break;
		case "FT_2":
			dialog.text = StringFromKey("ZhilBaru_23");
			link.l1 = StringFromKey("ZhilBaru_24");
			link.l1.go = "FT_3_1";
			link.l2 = StringFromKey("ZhilBaru_25");
			link.l2.go = "FT_3_2";
		break;
		case "FT_3_1":
			dialog.text = StringFromKey("ZhilBaru_26");
			link.l1 = StringFromKey("ZhilBaru_27");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -2);
		break;
		case "FT_3_2":
			dialog.text = StringFromKey("ZhilBaru_28");
			link.l1 = StringFromKey("ZhilBaru_29");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 2);
		break;
		case "FT_4":
			dialog.text = StringFromKey("ZhilBaru_30");
			link.l1 = StringFromKey("ZhilBaru_31");
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
			dialog.text = StringFromKey("ZhilBaru_35", LinkRandPhrase(
						StringFromKey("ZhilBaru_32", pchar),
						StringFromKey("ZhilBaru_33", pchar),
						StringFromKey("ZhilBaru_34", pchar)));
			link.l1 = StringFromKey("ZhilBaru_36");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("ZhilBaru_37", pchar);
			link.l1 = StringFromKey("ZhilBaru_38");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("ZhilBaru_42", LinkRandPhrase(
						StringFromKey("ZhilBaru_39", pchar),
						StringFromKey("ZhilBaru_40"),
						StringFromKey("ZhilBaru_41", pchar)));
			link.l1 = StringFromKey("ZhilBaru_46", LinkRandPhrase(
						StringFromKey("ZhilBaru_43"),
						StringFromKey("ZhilBaru_44"),
						StringFromKey("ZhilBaru_45")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("ZhilBaru_47", npchar);
				link.l1 = StringFromKey("ZhilBaru_51", LinkRandPhrase(
							StringFromKey("ZhilBaru_48"),
							StringFromKey("ZhilBaru_49"),
							StringFromKey("ZhilBaru_50")));
			}
			else
			{
				dialog.text = StringFromKey("ZhilBaru_52", npchar);
				link.l1 = StringFromKey("ZhilBaru_55", RandPhraseSimple(
							StringFromKey("ZhilBaru_53", pchar),
							StringFromKey("ZhilBaru_54")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("ZhilBaru_56");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("ZhilBaru_57");
				Link.l1 = StringFromKey("ZhilBaru_58");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("ZhilBaru_59", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("ZhilBaru_60");
					link.l1 = StringFromKey("ZhilBaru_61", pchar);
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("ZhilBaru_62", GetFullName(sld));
					Link.l1 = StringFromKey("ZhilBaru_63");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("ZhilBaru_64");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("ZhilBaru_65", GetFullName(sld));
					Link.l1 = StringFromKey("ZhilBaru_66");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("ZhilBaru_67");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("ZhilBaru_68");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("ZhilBaru_69");
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
					dialog.text = StringFromKey("ZhilBaru_73", LinkRandPhrase(
								StringFromKey("ZhilBaru_70"),
								StringFromKey("ZhilBaru_71"),
								StringFromKey("ZhilBaru_72")));
					link.l1 = StringFromKey("ZhilBaru_76", RandPhraseSimple(
								StringFromKey("ZhilBaru_74"),
								StringFromKey("ZhilBaru_75")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("ZhilBaru_80", LinkRandPhrase(
								StringFromKey("ZhilBaru_77"),
								StringFromKey("ZhilBaru_78"),
								StringFromKey("ZhilBaru_79")));
					link.l1 = StringFromKey("ZhilBaru_83", RandPhraseSimple(
								StringFromKey("ZhilBaru_81"),
								StringFromKey("ZhilBaru_82")));
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
							dialog.text = StringFromKey("ZhilBaru_87", LinkRandPhrase(
										StringFromKey("ZhilBaru_84"),
										StringFromKey("ZhilBaru_85"),
										StringFromKey("ZhilBaru_86")));
						}
						else
						{
							dialog.text = StringFromKey("ZhilBaru_91", LinkRandPhrase(
										StringFromKey("ZhilBaru_88", npchar.quest.seekIdx.where),
										StringFromKey("ZhilBaru_89", npchar.quest.seekIdx.where),
										StringFromKey("ZhilBaru_90", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("ZhilBaru_95", LinkRandPhrase(
										StringFromKey("ZhilBaru_92", npchar.quest.seekIdx.where),
										StringFromKey("ZhilBaru_93"),
										StringFromKey("ZhilBaru_94")));
						}
						else
						{
							dialog.text = StringFromKey("ZhilBaru_99", LinkRandPhrase(
										StringFromKey("ZhilBaru_96", npchar.quest.seekIdx.where),
										StringFromKey("ZhilBaru_97", npchar.quest.seekIdx.where),
										StringFromKey("ZhilBaru_98", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("ZhilBaru_102", RandPhraseSimple(
								StringFromKey("ZhilBaru_100"),
								StringFromKey("ZhilBaru_101")));
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
							dialog.text = StringFromKey("ZhilBaru_106", LinkRandPhrase(
										StringFromKey("ZhilBaru_103"),
										StringFromKey("ZhilBaru_104"),
										StringFromKey("ZhilBaru_105")));
						}
						else
						{
							dialog.text = StringFromKey("ZhilBaru_110", LinkRandPhrase(
										StringFromKey("ZhilBaru_107", npchar.quest.seekIdx.where),
										StringFromKey("ZhilBaru_108", npchar.quest.seekIdx.where),
										StringFromKey("ZhilBaru_109", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("ZhilBaru_114", LinkRandPhrase(
										StringFromKey("ZhilBaru_111", npchar.quest.seekIdx.where),
										StringFromKey("ZhilBaru_112"),
										StringFromKey("ZhilBaru_113")));
						}
						else
						{
							dialog.text = StringFromKey("ZhilBaru_118", LinkRandPhrase(
										StringFromKey("ZhilBaru_115", npchar.quest.seekIdx.where),
										StringFromKey("ZhilBaru_116", npchar.quest.seekIdx.where),
										StringFromKey("ZhilBaru_117", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("ZhilBaru_121", RandPhraseSimple(
								StringFromKey("ZhilBaru_119", GetAddress_FormToNPC(NPChar)),
								StringFromKey("ZhilBaru_120")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("ZhilBaru_122", pchar);
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("ZhilBaru_123");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("ZhilBaru_124");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = StringFromKey("ZhilBaru_125");
				link.l3.go = "ansewer_3";
			}
			link.l10 = StringFromKey("ZhilBaru_126");
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("ZhilBaru_127", pchar);
			link.l1 = StringFromKey("ZhilBaru_128");
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = StringFromKey("ZhilBaru_129");
			link.l1 = StringFromKey("ZhilBaru_130");
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("ZhilBaru_131");
			link.l1 = StringFromKey("ZhilBaru_132");
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = StringFromKey("ZhilBaru_133");
			link.l1 = StringFromKey("ZhilBaru_134");
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("ZhilBaru_135");
			link.l1 = StringFromKey("ZhilBaru_136");
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = StringFromKey("ZhilBaru_137");
			link.l1 = StringFromKey("ZhilBaru_138");
			link.l1.go = "ansewer_3_2";
		break;
		case "ansewer_3_2":
			dialog.text = StringFromKey("ZhilBaru_139");
			link.l1 = StringFromKey("ZhilBaru_140");
			link.l1.go = "int_quests";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = StringFromKey("ZhilBaru_141");
			link.l1 = StringFromKey("ZhilBaru_142");
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("ZhilBaru_143");
			link.l1 = StringFromKey("ZhilBaru_144");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("ZhilBaru_145");
			link.l1 = StringFromKey("ZhilBaru_146");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("ZhilBaru_147");
			link.l1 = StringFromKey("ZhilBaru_148");
			link.l1.go = "SeekCrew_all";
		break;
		//освобождение мужа Элис Тейлор Максима
		case "ELTHusb_SF":
			dialog.text = StringFromKey("ZhilBaru_149");
			link.l1 = StringFromKey("ZhilBaru_150", pchar);
			link.l1.go = "ELTHusb_SF_1";
		break;
		case "ELTHusb_SF_1":
			dialog.text = StringFromKey("ZhilBaru_151");
			link.l1 = StringFromKey("ZhilBaru_152");
			link.l1.go = "ELTHusb_SF_2";
		break;
		case "ELTHusb_SF_2":
			dialog.text = StringFromKey("ZhilBaru_153");
			link.l1 = StringFromKey("ZhilBaru_154");
			link.l1.go = "ELTHusb_SF_3";
		break;
		case "ELTHusb_SF_3":
			dialog.text = StringFromKey("ZhilBaru_155");
			link.l1 = StringFromKey("ZhilBaru_156");
			link.l1.go = "ELTHusb_SF_4";
		break;
		case "ELTHusb_SF_4":
			dialog.text = StringFromKey("ZhilBaru_157");
			link.l1 = StringFromKey("ZhilBaru_158");
			link.l1.go = "ELTHusb_SF_5";
		break;
		case "ELTHusb_SF_5":
			dialog.text = StringFromKey("ZhilBaru_159");
			link.l1 = StringFromKey("ZhilBaru_160");
			link.l1.go = "ELTHusb_SF_6";
		break;
		case "ELTHusb_SF_6":
			dialog.text = StringFromKey("ZhilBaru_161");
			link.l1 = StringFromKey("ZhilBaru_162");
			link.l1.go = "ELTHusb_SF_7";
		break;
		case "ELTHusb_SF_7":
			dialog.text = StringFromKey("ZhilBaru_163");
			link.l1 = StringFromKey("ZhilBaru_164");
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "9");
			pchar.questTemp.LSC.ElisHusband = "toAdmiralGood";
			RemoveLandQuestMark_Main(npchar, "ISS_ElisHusband");
			AddLandQuestMark_Main(CharacterFromID("LSCMayor"), "ISS_ElisHusband");
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("ZhilBaru_165", GetFullName(pchar));
			link.l1 = StringFromKey("ZhilBaru_166");
			link.l1.go = "Exit_GoodBye";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
