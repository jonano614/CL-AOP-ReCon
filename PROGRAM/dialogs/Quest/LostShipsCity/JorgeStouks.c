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
				dialog.text = StringFromKey("JorgeStouks_1", GetFullName(npchar));
				link.l1 = StringFromKey("JorgeStouks_2", GetFullName(pchar));
				link.l1.go = "FT_1";
			}
			else
			{
				dialog.text = StringFromKey("JorgeStouks_3", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("JorgeStouks_4");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("JorgeStouks_5");
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("JorgeStouks_9", LinkRandPhrase(
							StringFromKey("JorgeStouks_6"),
							StringFromKey("JorgeStouks_7"),
							StringFromKey("JorgeStouks_8", pchar)));
				link.l3.go = "rumours_LSC";
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = StringFromKey("JorgeStouks_10");
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (pchar.questTemp.LSC == "toSeekCrewInTavern") dialog.text = StringFromKey("JorgeStouks_11"); //сбор в таверне
					link.l8 = StringFromKey("JorgeStouks_12");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("JorgeStouks_13");
				link.l10.go = "exit";
			}
		break;
		case "FT_1":
			dialog.text = StringFromKey("JorgeStouks_14", pchar);
			link.l1 = StringFromKey("JorgeStouks_15");
			link.l1.go = "FT_2";
			LSC_GettingToKnowLSC_9();
		break;
		case "FT_2":
			dialog.text = StringFromKey("JorgeStouks_16");
			link.l1 = StringFromKey("JorgeStouks_17");
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = StringFromKey("JorgeStouks_18");
			link.l1 = StringFromKey("JorgeStouks_19");
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = StringFromKey("JorgeStouks_20");
			link.l1 = StringFromKey("JorgeStouks_21");
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = StringFromKey("JorgeStouks_22");
			link.l1 = StringFromKey("JorgeStouks_23");
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = StringFromKey("JorgeStouks_24");
			link.l1 = StringFromKey("JorgeStouks_25");
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = StringFromKey("JorgeStouks_26");
			link.l1 = StringFromKey("JorgeStouks_27");
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = StringFromKey("JorgeStouks_28");
			link.l1 = StringFromKey("JorgeStouks_29", pchar);
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = StringFromKey("JorgeStouks_30");
			link.l1 = StringFromKey("JorgeStouks_31");
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			dialog.text = StringFromKey("JorgeStouks_32");
			link.l1 = StringFromKey("JorgeStouks_33");
			link.l1.go = "FT_11";
		break;
		case "FT_11":
			dialog.text = StringFromKey("JorgeStouks_34");
			link.l1 = StringFromKey("JorgeStouks_35");
			link.l1.go = "FT_12";
		break;
		case "FT_12":
			dialog.text = StringFromKey("JorgeStouks_36");
			link.l1 = StringFromKey("JorgeStouks_37");
			link.l1.go = "FT_13";
		break;
		case "FT_13":
			dialog.text = StringFromKey("JorgeStouks_38");
			link.l1 = StringFromKey("JorgeStouks_39");
			link.l1.go = "FT_14";
		break;
		case "FT_14":
			dialog.text = StringFromKey("JorgeStouks_40");
			link.l1 = StringFromKey("JorgeStouks_41");
			link.l1.go = "FT_15";
		break;
		case "FT_15":
			dialog.text = StringFromKey("JorgeStouks_42", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("JorgeStouks_43");
			link.l1.go = "FT_16";
		break;
		case "FT_16":
			dialog.text = StringFromKey("JorgeStouks_44");
			link.l1 = StringFromKey("JorgeStouks_45");
			link.l1.go = "FT_17";
		break;
		case "FT_17":
			dialog.text = StringFromKey("JorgeStouks_46");
			link.l1 = StringFromKey("JorgeStouks_47");
			link.l1.go = "FT_18";
		break;
		case "FT_18":
			EndQuestMovie();
			npchar.location.group = "goto";
			npchar.location.locator = "goto08_1";
			AddQuestRecord("ISS_MainLine", "1");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("", "ла"));
			LAi_SetLSCoutTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
//			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("LSCMayor"), "ISS_MainLine");

			LAi_SetPlayerType(pchar);
			DialogExit();
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
			dialog.text = StringFromKey("JorgeStouks_51", LinkRandPhrase(
						StringFromKey("JorgeStouks_48", pchar),
						StringFromKey("JorgeStouks_49", pchar),
						StringFromKey("JorgeStouks_50", pchar)));
			link.l1 = StringFromKey("JorgeStouks_52");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("JorgeStouks_53");
			link.l1 = StringFromKey("JorgeStouks_54");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("JorgeStouks_58", LinkRandPhrase(
						StringFromKey("JorgeStouks_55", pchar),
						StringFromKey("JorgeStouks_56"),
						StringFromKey("JorgeStouks_57", pchar)));
			link.l1 = StringFromKey("JorgeStouks_62", LinkRandPhrase(
						StringFromKey("JorgeStouks_59"),
						StringFromKey("JorgeStouks_60"),
						StringFromKey("JorgeStouks_61")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("JorgeStouks_63", npchar);
				link.l1 = StringFromKey("JorgeStouks_67", LinkRandPhrase(
							StringFromKey("JorgeStouks_64"),
							StringFromKey("JorgeStouks_65"),
							StringFromKey("JorgeStouks_66")));
			}
			else
			{
				dialog.text = StringFromKey("JorgeStouks_68", npchar);
				link.l1 = StringFromKey("JorgeStouks_71", RandPhraseSimple(
							StringFromKey("JorgeStouks_69", pchar),
							StringFromKey("JorgeStouks_70")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("JorgeStouks_72");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("JorgeStouks_73");
				Link.l1 = StringFromKey("JorgeStouks_74");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("JorgeStouks_75", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("JorgeStouks_76");
					link.l1 = StringFromKey("JorgeStouks_77", pchar);
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("JorgeStouks_78", GetFullName(sld));
					Link.l1 = StringFromKey("JorgeStouks_79");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("JorgeStouks_80");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("JorgeStouks_81", GetFullName(sld));
					Link.l1 = StringFromKey("JorgeStouks_82");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("JorgeStouks_83");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("JorgeStouks_84");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("JorgeStouks_85");
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
					dialog.text = StringFromKey("JorgeStouks_89", LinkRandPhrase(
								StringFromKey("JorgeStouks_86"),
								StringFromKey("JorgeStouks_87"),
								StringFromKey("JorgeStouks_88")));
					link.l1 = StringFromKey("JorgeStouks_92", RandPhraseSimple(
								StringFromKey("JorgeStouks_90"),
								StringFromKey("JorgeStouks_91")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("JorgeStouks_96", LinkRandPhrase(
								StringFromKey("JorgeStouks_93"),
								StringFromKey("JorgeStouks_94"),
								StringFromKey("JorgeStouks_95")));
					link.l1 = StringFromKey("JorgeStouks_99", RandPhraseSimple(
								StringFromKey("JorgeStouks_97"),
								StringFromKey("JorgeStouks_98")));
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
							dialog.text = StringFromKey("JorgeStouks_103", LinkRandPhrase(
										StringFromKey("JorgeStouks_100"),
										StringFromKey("JorgeStouks_101"),
										StringFromKey("JorgeStouks_102")));
						}
						else
						{
							dialog.text = StringFromKey("JorgeStouks_107", LinkRandPhrase(
										StringFromKey("JorgeStouks_104", npchar.quest.seekIdx.where),
										StringFromKey("JorgeStouks_105", npchar.quest.seekIdx.where),
										StringFromKey("JorgeStouks_106", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("JorgeStouks_111", LinkRandPhrase(
										StringFromKey("JorgeStouks_108", npchar.quest.seekIdx.where),
										StringFromKey("JorgeStouks_109"),
										StringFromKey("JorgeStouks_110")));
						}
						else
						{
							dialog.text = StringFromKey("JorgeStouks_115", LinkRandPhrase(
										StringFromKey("JorgeStouks_112", npchar.quest.seekIdx.where),
										StringFromKey("JorgeStouks_113", npchar.quest.seekIdx.where),
										StringFromKey("JorgeStouks_114", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("JorgeStouks_118", RandPhraseSimple(
								StringFromKey("JorgeStouks_116"),
								StringFromKey("JorgeStouks_117")));
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
							dialog.text = StringFromKey("JorgeStouks_122", LinkRandPhrase(
										StringFromKey("JorgeStouks_119"),
										StringFromKey("JorgeStouks_120"),
										StringFromKey("JorgeStouks_121")));
						}
						else
						{
							dialog.text = StringFromKey("JorgeStouks_126", LinkRandPhrase(
										StringFromKey("JorgeStouks_123", npchar.quest.seekIdx.where),
										StringFromKey("JorgeStouks_124", npchar.quest.seekIdx.where),
										StringFromKey("JorgeStouks_125", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("JorgeStouks_130", LinkRandPhrase(
										StringFromKey("JorgeStouks_127", npchar.quest.seekIdx.where),
										StringFromKey("JorgeStouks_128"),
										StringFromKey("JorgeStouks_129")));
						}
						else
						{
							dialog.text = StringFromKey("JorgeStouks_134", LinkRandPhrase(
										StringFromKey("JorgeStouks_131", npchar.quest.seekIdx.where),
										StringFromKey("JorgeStouks_132", npchar.quest.seekIdx.where),
										StringFromKey("JorgeStouks_133", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("JorgeStouks_137", RandPhraseSimple(
								StringFromKey("JorgeStouks_135", GetAddress_FormToNPC(NPChar)),
								StringFromKey("JorgeStouks_136")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("JorgeStouks_138", pchar);
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("JorgeStouks_139");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("JorgeStouks_140");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l3"))
			{
				link.l3 = StringFromKey("JorgeStouks_141");
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l4") && CheckCharacterItem(pchar, "TizerKey"))
			{
				link.l4 = StringFromKey("JorgeStouks_142");
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l5"))
			{
				link.l5 = StringFromKey("JorgeStouks_143");
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l6") && !CheckCharacterItem(pchar, "map_LSC"))
			{
				link.l6 = StringFromKey("JorgeStouks_144");
				link.l6.go = "ansewer_6";
			}
			link.l10 = StringFromKey("JorgeStouks_145");
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("JorgeStouks_146");
			link.l1 = StringFromKey("JorgeStouks_147");
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = StringFromKey("JorgeStouks_148");
			link.l1 = StringFromKey("JorgeStouks_149");
			link.l1.go = "ansewer_1_2";
		break;
		case "ansewer_1_2":
			dialog.text = StringFromKey("JorgeStouks_150");
			link.l1 = StringFromKey("JorgeStouks_151");
			link.l1.go = "ansewer_1_3";
		break;
		case "ansewer_1_3":
			dialog.text = StringFromKey("JorgeStouks_152");
			link.l1 = StringFromKey("JorgeStouks_153", pchar);
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("JorgeStouks_154");
			link.l1 = StringFromKey("JorgeStouks_155");
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = StringFromKey("JorgeStouks_156");
			link.l1 = StringFromKey("JorgeStouks_157");
			link.l1.go = "ansewer_2_2";
		break;
		case "ansewer_2_2":
			dialog.text = StringFromKey("JorgeStouks_158");
			link.l1 = StringFromKey("JorgeStouks_159", pchar);
			link.l1.go = "ansewer_2_3";
		break;
		case "ansewer_2_3":
			dialog.text = StringFromKey("JorgeStouks_160");
			link.l1 = StringFromKey("JorgeStouks_161", npchar.lastname);
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("JorgeStouks_162");
			link.l1 = StringFromKey("JorgeStouks_163");
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = StringFromKey("JorgeStouks_164");
			link.l1 = StringFromKey("JorgeStouks_165");
			link.l1.go = "ansewer_3_2";
		break;
		case "ansewer_3_2":
			dialog.text = StringFromKey("JorgeStouks_166");
			link.l1 = StringFromKey("JorgeStouks_167");
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = StringFromKey("JorgeStouks_168");
			link.l1 = StringFromKey("JorgeStouks_169");
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_4_1":
			dialog.text = StringFromKey("JorgeStouks_170");
			link.l1 = StringFromKey("JorgeStouks_171");
			link.l1.go = "ansewer_4_2";
		break;
		case "ansewer_4_2":
			dialog.text = StringFromKey("JorgeStouks_172", pchar);
			link.l1 = StringFromKey("JorgeStouks_173");
			link.l1.go = "ansewer_4_3";
		break;
		case "ansewer_4_3":
			dialog.text = StringFromKey("JorgeStouks_174");
			link.l1 = StringFromKey("JorgeStouks_175");
			link.l1.go = "int_quests";
			AddQuestRecord("ISS_MainLine", "2");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
			LSC_UpdateQuestMarksToCitizens();
		break;
		case "ansewer_5":
			dialog.text = StringFromKey("JorgeStouks_176");
			link.l1 = StringFromKey("JorgeStouks_177");
			link.l1.go = "ansewer_5_1";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_5_1":
			dialog.text = StringFromKey("JorgeStouks_178");
			link.l1 = StringFromKey("JorgeStouks_179");
			link.l1.go = "ansewer_5_2";
		break;
		case "ansewer_5_2":
			dialog.text = StringFromKey("JorgeStouks_180");
			link.l1 = StringFromKey("JorgeStouks_181");
			link.l1.go = "int_quests";
		break;
		case "ansewer_6":
			dialog.text = StringFromKey("JorgeStouks_182");
			link.l1 = StringFromKey("JorgeStouks_183");
			link.l1.go = "ansewer_6_1";
			NextDiag.(NodePrevName).l6 = true;
		break;
		case "ansewer_6_1":
			dialog.text = StringFromKey("JorgeStouks_184");
			link.l1 = StringFromKey("JorgeStouks_185");
			link.l1.go = "ansewer_6_2";
		break;
		case "ansewer_6_2":
			dialog.text = StringFromKey("JorgeStouks_186");
			link.l1 = StringFromKey("JorgeStouks_187", pchar);
			link.l1.go = "int_quests";
			AddQuestRecord("FindMapLSC", "1");
			LSC_UpdateQuestMarksToCitizens();
			AddLandQuestMark_Main(CharacterFromID("LSC_Trader"), "FindMapLSC");
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("JorgeStouks_188"),
						StringFromKey("JorgeStouks_189"),
						StringFromKey("JorgeStouks_190"),
						StringFromKey("JorgeStouks_191"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("JorgeStouks_192"),
						StringFromKey("JorgeStouks_193", pchar),
						StringFromKey("JorgeStouks_194"),
						StringFromKey("JorgeStouks_195", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("JorgeStouks_196");
			link.l1 = StringFromKey("JorgeStouks_197");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = StringFromKey("JorgeStouks_198");
			link.l1 = StringFromKey("JorgeStouks_199");
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			npchar.toSeekCrewInTavern = true;
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("JorgeStouks_200"),
						StringFromKey("JorgeStouks_201"),
						StringFromKey("JorgeStouks_202"),
						StringFromKey("JorgeStouks_203", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("JorgeStouks_204"),
						StringFromKey("JorgeStouks_205", pchar),
						StringFromKey("JorgeStouks_206"),
						StringFromKey("JorgeStouks_207"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("JorgeStouks_208");
			link.l1 = StringFromKey("JorgeStouks_209");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("JorgeStouks_210");
			link.l1 = StringFromKey("JorgeStouks_211");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("JorgeStouks_212");
			link.l1 = StringFromKey("JorgeStouks_213");
			link.l1.go = "SeekCrew_4";
		break;
		case "SeekCrew_4":
			dialog.text = StringFromKey("JorgeStouks_214");
			link.l1 = StringFromKey("JorgeStouks_215");
			link.l1.go = "exit";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
