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
			dialog.text = StringFromKey("MaximTailor_1", pchar);
			link.l1 = StringFromKey("MaximTailor_2");
			link.l1.go = "SeekCitizen";
			link.l2 = StringFromKey("MaximTailor_3");
			link.l2.go = "int_quests";
			link.l3 = StringFromKey("MaximTailor_7", LinkRandPhrase(
						StringFromKey("MaximTailor_4"),
						StringFromKey("MaximTailor_5"),
						StringFromKey("MaximTailor_6", pchar)));
			link.l3.go = "rumours_LSC";
			//сбор отряда самоубийц
			if (CheckAttribute(pchar, "questTemp.LSC.suicideSquad") && !CheckAttribute(pchar, "questTemp.LSC.suicideSquad." + GetCharacterIndex(npchar.id)))
			{
				link.l1 = StringFromKey("MaximTailor_8");
				link.l1.go = "SuicideSquad";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.suicideSquad." + GetCharacterIndex(npchar.id)))
			{
				int deceasedCaspers = LSC_CheckDeceasedCaspers();
				//если оба мушкетера живы
				bool checkStateOne = deceasedCaspers == 2 && !LAi_IsDead(CharacterFromId("CasperMush_3")) && !LAi_IsDead(CharacterFromId("CasperMush_4"));
				//если CasperMush_3 жив
				bool checkStateTwo = deceasedCaspers == 1 && !LAi_IsDead(CharacterFromId("CasperMush_3"));
				//если CasperMush_4 жив
				bool checkStateThree = deceasedCaspers == 1 && !LAi_IsDead(CharacterFromId("CasperMush_4"));
				link.l3 = StringFromKey("MaximTailor_9");
				if (checkStateOne || checkStateTwo || checkStateThree) link.l3.go = "StormCaspers_1";
				else link.l3.go = "RefusalToGo";
			}
			//поиски команды на корвет
			if (CheckAttribute(pchar, "questTemp.LSC.crew") && !CheckAttribute(npchar, "SeekCrew"))
			{
				if (pchar.questTemp.LSC == "toSeekCrewInTavern") dialog.text = StringFromKey("MaximTailor_10"); //сбор в таверне
				link.l8 = StringFromKey("MaximTailor_11");
				link.l8.go = "SeekCrew";
			}
			link.l10 = StringFromKey("MaximTailor_12");
			link.l10.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("MaximTailor_13");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("MaximTailor_14");
				Link.l1 = StringFromKey("MaximTailor_15");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("MaximTailor_16", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("MaximTailor_17");
					link.l1 = StringFromKey("MaximTailor_18", pchar);
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("MaximTailor_19", GetFullName(sld));
					Link.l1 = StringFromKey("MaximTailor_20");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("MaximTailor_21");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("MaximTailor_22", GetFullName(sld));
					Link.l1 = StringFromKey("MaximTailor_23");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("MaximTailor_24");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("MaximTailor_25");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("MaximTailor_26");
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
					dialog.text = StringFromKey("MaximTailor_30", LinkRandPhrase(
								StringFromKey("MaximTailor_27"),
								StringFromKey("MaximTailor_28"),
								StringFromKey("MaximTailor_29")));
					link.l1 = StringFromKey("MaximTailor_33", RandPhraseSimple(
								StringFromKey("MaximTailor_31"),
								StringFromKey("MaximTailor_32")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("MaximTailor_37", LinkRandPhrase(
								StringFromKey("MaximTailor_34"),
								StringFromKey("MaximTailor_35"),
								StringFromKey("MaximTailor_36")));
					link.l1 = StringFromKey("MaximTailor_40", RandPhraseSimple(
								StringFromKey("MaximTailor_38"),
								StringFromKey("MaximTailor_39")));
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
							dialog.text = StringFromKey("MaximTailor_44", LinkRandPhrase(
										StringFromKey("MaximTailor_41"),
										StringFromKey("MaximTailor_42"),
										StringFromKey("MaximTailor_43", pchar)));
						}
						else
						{
							dialog.text = StringFromKey("MaximTailor_48", LinkRandPhrase(
										StringFromKey("MaximTailor_45", npchar.quest.seekIdx.where),
										StringFromKey("MaximTailor_46", npchar.quest.seekIdx.where),
										StringFromKey("MaximTailor_47", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("MaximTailor_52", LinkRandPhrase(
										StringFromKey("MaximTailor_49", npchar.quest.seekIdx.where),
										StringFromKey("MaximTailor_50"),
										StringFromKey("MaximTailor_51")));
						}
						else
						{
							dialog.text = StringFromKey("MaximTailor_56", LinkRandPhrase(
										StringFromKey("MaximTailor_53", npchar.quest.seekIdx.where),
										StringFromKey("MaximTailor_54", npchar.quest.seekIdx.where),
										StringFromKey("MaximTailor_55", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("MaximTailor_59", RandPhraseSimple(
								StringFromKey("MaximTailor_57"),
								StringFromKey("MaximTailor_58")));
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
							dialog.text = StringFromKey("MaximTailor_63", LinkRandPhrase(
										StringFromKey("MaximTailor_60"),
										StringFromKey("MaximTailor_61"),
										StringFromKey("MaximTailor_62", pchar)));
						}
						else
						{
							dialog.text = StringFromKey("MaximTailor_67", LinkRandPhrase(
										StringFromKey("MaximTailor_64", npchar.quest.seekIdx.where),
										StringFromKey("MaximTailor_65", npchar.quest.seekIdx.where),
										StringFromKey("MaximTailor_66", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("MaximTailor_71", LinkRandPhrase(
										StringFromKey("MaximTailor_68", npchar.quest.seekIdx.where),
										StringFromKey("MaximTailor_69"),
										StringFromKey("MaximTailor_70")));
						}
						else
						{
							dialog.text = StringFromKey("MaximTailor_75", LinkRandPhrase(
										StringFromKey("MaximTailor_72", npchar.quest.seekIdx.where),
										StringFromKey("MaximTailor_73", npchar.quest.seekIdx.where),
										StringFromKey("MaximTailor_74", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("MaximTailor_78", RandPhraseSimple(
								StringFromKey("MaximTailor_76"),
								StringFromKey("MaximTailor_77")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("MaximTailor_79");
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("MaximTailor_80");
				link.l1.go = "ansewer_1";
			}
			link.l10 = StringFromKey("MaximTailor_81");
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("MaximTailor_82");
			link.l1 = StringFromKey("MaximTailor_83");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		//нерадивый муж Элис Тейлор
		case "InPrison":
			dialog.text = StringFromKey("MaximTailor_84", pchar);
			if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "begin")
			{
				link.l1 = StringFromKey("MaximTailor_85");
				link.l1.go = "exit";
				NextDiag.TempNode = "InPrison_wait";
			}
			else
			{
				link.l1 = StringFromKey("MaximTailor_86");
				link.l1.go = "InPrison_1";
			}
		break;
		case "InPrison_1":
			dialog.text = StringFromKey("MaximTailor_87");
			link.l1 = StringFromKey("MaximTailor_88");
			link.l1.go = "InPrison_2";
		break;
		case "InPrison_2":
			dialog.text = StringFromKey("MaximTailor_89");
			link.l1 = StringFromKey("MaximTailor_90");
			link.l1.go = "InPrison_3";
		break;
		case "InPrison_3":
			dialog.text = StringFromKey("MaximTailor_91");
			link.l1 = StringFromKey("MaximTailor_92");
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "2");
			pchar.questTemp.LSC.ElisHusband = "toElis";
			NextDiag.TempNode = "InPrison_wait";
			AddLandQuestMark_Main(CharacterFromId("ElisTaylor"), "ISS_ElisHusband");
			AddLandQuestMark_Main(CharacterFromId("LSCMayor"), "ISS_ElisHusband");
			AddLandQuestMark_Main(CharacterFromID("LSC_PrisonerHead"), "ISS_ElisHusband");
		break;

		case "InPrison_wait":
			dialog.text = StringFromKey("MaximTailor_93", pchar);
			link.l1 = StringFromKey("MaximTailor_94");
			link.l1.go = "exit";
		break;
		//если не помогли ему
		case "EternalPrisoner":
			NextDiag.TempNode = "EternalPrisoner";

			dialog.text = StringFromKey("MaximTailor_95");
			link.l1 = StringFromKey("MaximTailor_96");
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.LSC.suicideSquad") && !CheckAttribute(npchar, "quest.tired_of_life")) //попытаться завербовать в отряд
			{
				link.l1 = StringFromKey("MaximTailor_97");
				link.l1.go = "EternalPrisoner_1";
			}
		break;
		case "EternalPrisoner_1":
			if (!CheckAttribute(pchar, "questTemp.LSC.suicideSquad_TalkCounter"))
				pchar.questTemp.LSC.suicideSquad_TalkCounter = 0;
			pchar.questTemp.LSC.suicideSquad_TalkCounter = sti(pchar.questTemp.LSC.suicideSquad_TalkCounter) + 1;

			dialog.text = StringFromKey("MaximTailor_98");
			link.l1 = StringFromKey("MaximTailor_99");
			link.l1.go = "exit";
			npchar.quest.tired_of_life = true;
			AddQuestRecord("ISS_DefeatCasperClan", "17");
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");
		break;

		case "DontRemember":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("MaximTailor_100", pchar),
						StringFromKey("MaximTailor_101", pchar),
						StringFromKey("MaximTailor_102"),
						StringFromKey("MaximTailor_103", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("MaximTailor_104"),
						StringFromKey("MaximTailor_105"),
						StringFromKey("MaximTailor_106"),
						StringFromKey("MaximTailor_107"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("DontRemember_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "DontRemember_1":
			dialog.text = StringFromKey("MaximTailor_108");
			link.l1 = StringFromKey("MaximTailor_109");
			link.l1.go = "DontRemember_2";
		break;
		case "DontRemember_2":
			dialog.text = StringFromKey("MaximTailor_110");
			link.l1 = StringFromKey("MaximTailor_111");
			link.l1.go = "DontRemember_3";
		break;
		case "DontRemember_3":
			dialog.text = StringFromKey("MaximTailor_112");
			link.l1 = StringFromKey("MaximTailor_113");
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "6");
			pchar.questTemp.LSC.ElisHusband = "toAdmiral";
			NextDiag.TempNode = "DontRemember";
			RemoveLandQuestMark_Main(npchar, "ISS_ElisHusband");
			AddLandQuestMark_Main(CharacterFromId("LSCMayor"), "ISS_ElisHusband");
		break;
		//сбор отряда самоубийц
		case "SuicideSquad":
			if (!CheckAttribute(pchar, "questTemp.LSC.suicideSquad_TalkCounter"))
				pchar.questTemp.LSC.suicideSquad_TalkCounter = 0;
			pchar.questTemp.LSC.suicideSquad_TalkCounter = sti(pchar.questTemp.LSC.suicideSquad_TalkCounter) + 1;

			dialog.text = StringFromKey("MaximTailor_114");
			link.l1 = StringFromKey("MaximTailor_115");
			link.l1.go = "SuicideSquad_1";
		break;
		case "SuicideSquad_1":
			dialog.text = StringFromKey("MaximTailor_119", LinkRandPhrase(
						StringFromKey("MaximTailor_116"),
						StringFromKey("MaximTailor_117"),
						StringFromKey("MaximTailor_118")));
			link.l1 = StringFromKey("MaximTailor_123", LinkRandPhrase(
						StringFromKey("MaximTailor_120"),
						StringFromKey("MaximTailor_121"),
						StringFromKey("MaximTailor_122")));
			link.l1.go = "SuicideSquad_2";
		break;
		case "SuicideSquad_2":
			dialog.text = StringFromKey("MaximTailor_124");
			link.l1 = StringFromKey("MaximTailor_125");
			link.l1.go = "SuicideSquad_1";
			link.l2 = StringFromKey("MaximTailor_126");
			link.l2.go = "SuicideSquad_3";
		break;
		case "SuicideSquad_3":
			dialog.text = StringFromKey("MaximTailor_127");
			link.l1 = StringFromKey("MaximTailor_128");
			link.l1.go = "SuicideSquad_4";
		break;
		case "SuicideSquad_4":
			dialog.text = StringFromKey("MaximTailor_129");
			link.l1 = StringFromKey("MaximTailor_130");
			link.l1.go = "SuicideSquad_5";
		break;
		case "SuicideSquad_5":
			dialog.text = StringFromKey("MaximTailor_131");
			link.l1 = StringFromKey("MaximTailor_132");
			link.l1.go = "SuicideSquad_6";
		break;
		case "SuicideSquad_6":
			dialog.text = StringFromKey("MaximTailor_133");
			link.l1 = StringFromKey("MaximTailor_134");
			link.l1.go = "SuicideSquad_7";
		break;
		case "SuicideSquad_7":
			dialog.text = StringFromKey("MaximTailor_135");
			link.l1 = StringFromKey("MaximTailor_136");
			link.l1.go = "SuicideSquad_8";
			link.l2 = StringFromKey("MaximTailor_137");
			link.l2.go = "SuicideSquad_9";
			link.l3 = StringFromKey("MaximTailor_138");
			link.l3.go = "SuicideSquad_4";
		break;
		case "SuicideSquad_8":
			dialog.text = StringFromKey("MaximTailor_142", LinkRandPhrase(
						StringFromKey("MaximTailor_139"),
						StringFromKey("MaximTailor_140"),
						StringFromKey("MaximTailor_141")));
			link.l1 = StringFromKey("MaximTailor_143");
			link.l1.go = "SuicideSquad_2";
		break;
		case "SuicideSquad_9":
			dialog.text = StringFromKey("MaximTailor_144");
			link.l1 = StringFromKey("MaximTailor_145");
			link.l1.go = "SuicideSquad_10";
		break;
		case "SuicideSquad_10":
			dialog.text = StringFromKey("MaximTailor_146");
			link.l1 = StringFromKey("MaximTailor_147");
			link.l1.go = "SuicideSquad_11";
			link.l2 = StringFromKey("MaximTailor_148");
			link.l2.go = "SuicideSquad_11";
			link.l3 = StringFromKey("MaximTailor_149");
			link.l3.go = "SuicideSquad_11";
		break;
		case "SuicideSquad_11":
			dialog.text = StringFromKey("MaximTailor_150");
			link.l1 = StringFromKey("MaximTailor_151");
			link.l1.go = "SuicideSquad_12";
		break;
		case "SuicideSquad_12":
			dialog.text = StringFromKey("MaximTailor_152");
			link.l1 = StringFromKey("MaximTailor_153");
			link.l1.go = "SuicideSquad_13";
		break;
		case "SuicideSquad_13":
			dialog.text = StringFromKey("MaximTailor_154");
			link.l1 = StringFromKey("MaximTailor_155");
			link.l1.go = "SuicideSquad_14";
			link.l2 = StringFromKey("MaximTailor_156");
			link.l2.go = "SuicideSquad_14";
			link.l3 = StringFromKey("MaximTailor_157");
			link.l3.go = "SuicideSquad_14";
		break;
		case "SuicideSquad_14":
			dialog.text = StringFromKey("MaximTailor_158");
			link.l1 = StringFromKey("MaximTailor_159");
			link.l1.go = "SuicideSquad_15";
		break;
		case "SuicideSquad_15":
			dialog.text = StringFromKey("MaximTailor_160");
			link.l1 = StringFromKey("MaximTailor_161");
			link.l1.go = "SuicideSquad_16";
		break;
		case "SuicideSquad_16":
			dialog.text = StringFromKey("MaximTailor_162");
			link.l1 = StringFromKey("MaximTailor_163");
			link.l1.go = "exit";
			AddQuestRecord("ISS_DefeatCasperClan", "18");
			AddQuestUserData("ISS_DefeatCasperClan", "sName", GetFullName(npchar));
			string sIndex = its(GetCharacterIndex(npchar.id));
			pchar.questTemp.LSC.suicideSquad.(sIndex) = true;
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");

			LSC_SuicideSquadEnough();
		break;
		case "RefusalToGo":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("MaximTailor_164"),
						StringFromKey("MaximTailor_165"),
						StringFromKey("MaximTailor_166"),
						StringFromKey("MaximTailor_167"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("MaximTailor_168"),
						StringFromKey("MaximTailor_169"),
						StringFromKey("MaximTailor_170"),
						StringFromKey("MaximTailor_171"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = StringFromKey("MaximTailor_172");
			link.l1 = StringFromKey("MaximTailor_173");
			link.l1.go = "exit";
			npchar.SeekCrew = true;
			AddLandQuestMark_Main(CharacterFromId("ElisTaylor"), "ISS_MainLine");
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("MaximTailor_174");
			link.l1 = StringFromKey("MaximTailor_175");
			link.l1.go = "Exit_GoodBye";
			TakeNItems(pchar, "Mineral16", 10);
		break;
	}
	NextDiag.PrevNode = NodeName;
}
