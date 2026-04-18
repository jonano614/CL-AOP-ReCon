#include "DIALOGS\Rumours\Simple_rumors.c"

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	int iTemp;
	float locx, locy, locz;
	string sIndex;

	switch (Dialog.CurrentNode)
	{
		case "prisonerHead":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = StringFromKey("Prisoner_1", pchar);
				link.l1 = StringFromKey("Prisoner_2", GetFullName(pchar));
				link.l1.go = "FTH_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = StringFromKey("Prisoner_3");
				link.l1 = StringFromKey("Prisoner_4", pchar);
				link.l1.go = "Exit";
				//квест со скелетом Декстера
				if (CheckAttribute(pchar, "questTemp.LSC.lostDecster") && !CheckAttribute(npchar, "quest.decster"))
				{
					if (pchar.questTemp.LSC.lostDecster == "seekBox" || pchar.questTemp.LSC.lostDecster == "toAdmiral")
					{
						link.l6 = StringFromKey("Prisoner_5");
						link.l6.go = "LostDecsterHead";
					}
				}
				//муж Элис Тейлор
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toElis")
				{
					link.l7 = StringFromKey("Prisoner_6");
					link.l7.go = "ELTHusb_begin";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "seekFreeMotod")
				{
					link.l7 = StringFromKey("Prisoner_7");
					link.l7.go = "ELTHusb_SF";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toAdmiral")
				{
					link.l7 = StringFromKey("Prisoner_8");
					link.l7.go = "ELTHusb_SF";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					link.l8 = StringFromKey("Prisoner_9");
					link.l8.go = "SeekCrew";
				}
			}
			NextDiag.TempNode = "prisonerHead";
		break;
		case "FTH_1":
			dialog.text = StringFromKey("Prisoner_10");
			link.l1 = StringFromKey("Prisoner_11");
			link.l1.go = "FTH_2";
		break;
		case "FTH_2":
			dialog.text = StringFromKey("Prisoner_12");
			link.l1 = StringFromKey("Prisoner_13");
			link.l1.go = "FTH_3";
		break;
		case "FTH_3":
			dialog.text = StringFromKey("Prisoner_14");
			link.l1 = StringFromKey("Prisoner_15");
			link.l1.go = "Exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "prisoner":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = StringFromKey("Prisoner_16", pchar, GetFullName(npchar));
				link.l1 = StringFromKey("Prisoner_17", GetFullName(pchar));
				link.l1.go = "FTP_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = StringFromKey("Prisoner_18");
				//квест со скелетом Декстера
				if (CheckAttribute(pchar, "questTemp.LSC.lostDecster") && !CheckAttribute(npchar, "quest.decster"))
				{
					if (npchar.chr_ai.type == LAI_TYPE_SIT && or(pchar.questTemp.LSC.lostDecster == "seekBox", pchar.questTemp.LSC.lostDecster == "toAdmiral"))
					{
						link.l1 = StringFromKey("Prisoner_19");
						link.l1.go = "LostDecster";
					}
					if (pchar.questTemp.LSC.lostDecster == "fromMentos")
					{
						link.l1 = StringFromKey("Prisoner_20");
						link.l1.go = "LostDecsterFromMentos";
					}
				}
				//квест с вином от Доминика Легро
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toTomasBoil" && CheckCharacterItem(pchar, "potionwine"))
				{
					link.l2 = StringFromKey("Prisoner_21", pchar);
					link.l2.go = "WineLogro";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "toSecondToPrison")
				{
					link.l2 = StringFromKey("Prisoner_22");
					link.l2.go = "SecondLogro";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "to3ToPrison")
				{
					link.l2 = StringFromKey("Prisoner_23");
					link.l2.go = "LastLegro";
				}
				//помощь тюремщика в наезде на касперов, если Армо жива
				if (CheckAttribute(pchar, "questTemp.LSC.Armo") && pchar.questTemp.LSC.Armo == 16 && !CheckAttribute(pchar, "questTemp.LSC.suicideSquad"))
				{
					link.l3 = StringFromKey("Prisoner_24");
					link.l3.go = "ArmoIsLife";
				}
				//помощь тюремщика в наезде на касперов, если Армо убита
				iTemp = GetCharacterIndex("LSCwaitress");
				if (iTemp != -1 && characters[iTemp].name != FindPersonalName("LSCwaitress_name") && pchar.questTemp.LSC == "toSeekMechanik")
				{
					link.l3 = StringFromKey("Prisoner_25");
					link.l3.go = "ArmoIsDead";
				}
				//сбор отряда самоубийц
				if (CheckAttribute(pchar, "questTemp.LSC.suicideSquad") && !CheckAttribute(pchar, "questTemp.LSC.suicideSquad." + GetCharacterIndex(npchar.id)) &&
				!CheckAttribute(npchar, "LSC_SuicideSquad_NotHelpUs"))
				{
					aref aSuicideSquad;
					int index;
					makearef(aSuicideSquad, pchar.questTemp.LSC.suicideSquad);
					dialog.text = StringFromKey("Prisoner_26");
					if (GetAttributesNum(aSuicideSquad) > 1)
					{
						string sNames = "";
						for (int i = 0; i < GetAttributesNum(aSuicideSquad); i++)
						{
							index = sti(GetAttributeName(GetAttributeN(aSuicideSquad, i)));
							if (sNames == "") sNames = GetFullName(&characters[index]);
							else sNames = sNames + ", " + GetFullName(&characters[index]);
						}
						link.l3 = StringFromKey("Prisoner_27", sNames);
						link.l3.go = "SuicideSquad";
					}
					else
					{
						link.l3 = StringFromKey("Prisoner_28");
						link.l3.go = "exit";

						if (CheckAttribute(pchar, "questTemp.LSC.suicideSquad_TalkCounter") && sti(pchar.questTemp.LSC.suicideSquad_TalkCounter) >= 3)
						{
							if (GetAttributesNum(aSuicideSquad) == 1)
							{
								index = sti(GetAttributeName(GetAttributeN(aSuicideSquad, 0)));
								link.l3 = StringFromKey("Prisoner_29", GetFullName(&characters[index]));
							}
							else
							{
								link.l3 = StringFromKey("Prisoner_30");
							}
							link.l3.go = "SuicideSquad_ArmoDecision";
						}
					}
					NextDiag.TempNode = "prisoner";
					break;
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
					link.l3 = StringFromKey("Prisoner_31");
					if (checkStateOne || checkStateTwo || checkStateThree) link.l3.go = "StormCaspers_1";
					else link.l3.go = "RefusalToGo";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					link.l3 = StringFromKey("Prisoner_32");
					link.l3.go = "SeekCrew_Tomas";
				}
				link.l10 = StringFromKey("Prisoner_33", pchar);
				link.l10.go = "Exit";
			}
			NextDiag.TempNode = "prisoner";
		break;
		case "FTP_1":
			dialog.text = StringFromKey("Prisoner_34");
			link.l1 = StringFromKey("Prisoner_35");
			link.l1.go = "exit";
		break;

		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Prisoner_36"),
						StringFromKey("Prisoner_37"),
						StringFromKey("Prisoner_38"),
						StringFromKey("Prisoner_39", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Prisoner_40"),
						StringFromKey("Prisoner_41", pchar),
						StringFromKey("Prisoner_42"),
						StringFromKey("Prisoner_43"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("Prisoner_44");
			link.l1 = StringFromKey("Prisoner_45");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("Prisoner_46");
			link.l1 = StringFromKey("Prisoner_47");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("Prisoner_48", pchar);
			link.l1 = StringFromKey("Prisoner_49");
			link.l1.go = "exit";
		break;

		//освободить мужа Элис Тейлор
		case "ELTHusb_begin":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Prisoner_50"),
						StringFromKey("Prisoner_51"),
						StringFromKey("Prisoner_52"),
						StringFromKey("Prisoner_53"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Prisoner_54"),
						StringFromKey("Prisoner_55"),
						StringFromKey("Prisoner_56"),
						StringFromKey("Prisoner_57"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("ELTHusb_begin_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "ELTHusb_begin_1":
			dialog.text = StringFromKey("Prisoner_58");
			link.l1 = StringFromKey("Prisoner_59");
			link.l1.go = "ELTHusb_begin_2";
		break;
		case "ELTHusb_begin_2":
			dialog.text = StringFromKey("Prisoner_60");
			link.l1 = StringFromKey("Prisoner_61");
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "3");
			RemoveLandQuestMark_Main(npchar, "ISS_ElisHusband");
		break;

		case "ELTHusb_SF":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Prisoner_62"),
						StringFromKey("Prisoner_63"),
						StringFromKey("Prisoner_64"),
						StringFromKey("Prisoner_65"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Prisoner_66"),
						StringFromKey("Prisoner_67", pchar),
						StringFromKey("Prisoner_68", pchar),
						StringFromKey("Prisoner_69"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("ELTHusb_SF_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "ELTHusb_SF_1":
			dialog.text = StringFromKey("Prisoner_70");
			link.l1 = StringFromKey("Prisoner_71");
			link.l1.go = "exit";
			AddQuestRecord("ISS_ElisHusband", "4");
			pchar.questTemp.LSC.ElisHusband = "toAdmiral";
			RemoveLandQuestMark_Main(npchar, "ISS_ElisHusband");
			AddLandQuestMark_Main(CharacterFromId("LSCMayor"), "ISS_ElisHusband");
		break;

		case "LostDecsterHead":
			dialog.text = StringFromKey("Prisoner_72");
			link.l1 = StringFromKey("Prisoner_73");
			link.l1.go = "LostDecsterHead_1";
		break;
		case "LostDecsterHead_1":
			dialog.text = StringFromKey("Prisoner_74");
			link.l1 = StringFromKey("Prisoner_75");
			link.l1.go = "LostDecsterHead_2";
		break;
		case "LostDecsterHead_2":
			dialog.text = StringFromKey("Prisoner_76");
			link.l1 = StringFromKey("Prisoner_77");
			link.l1.go = "LostDecsterHead_3";
		break;
		case "LostDecsterHead_3":
			dialog.text = StringFromKey("Prisoner_78");
			link.l1 = StringFromKey("Prisoner_79");
			link.l1.go = "exit";
			npchar.quest.decster = true; //не повторять базар
			RemoveLandQuestMark_Main(npchar, "LSC_findDekster");
		break;

		case "LostDecster":
			dialog.text = StringFromKey("Prisoner_80");
			link.l1 = StringFromKey("Prisoner_81");
			link.l1.go = "LostDecster_1";
		break;
		case "LostDecster_1":
			dialog.text = StringFromKey("Prisoner_82");
			link.l1 = StringFromKey("Prisoner_83");
			link.l1.go = "exit";
			AddQuestRecord("LSC_findDekster", "4");
			npchar.quest.decster = true; //не повторять базар
			RemoveLandQuestMark_Main(npchar, "LSC_findDekster");
		break;

		case "LostDecsterFromMentos":
			dialog.text = StringFromKey("Prisoner_84");
			link.l1 = StringFromKey("Prisoner_85");
			link.l1.go = "LostDecsterFromMentos_1";
		break;
		case "LostDecsterFromMentos_1":
			dialog.text = StringFromKey("Prisoner_86");
			link.l1 = StringFromKey("Prisoner_87");
			link.l1.go = "LostDecsterFromMentos_2";
		break;
		case "LostDecsterFromMentos_2":
			dialog.text = StringFromKey("Prisoner_88");
			link.l1 = StringFromKey("Prisoner_89");
			link.l1.go = "LostDecsterFromMentos_3";
		break;
		case "LostDecsterFromMentos_3":
			dialog.text = StringFromKey("Prisoner_90");
			link.l1 = StringFromKey("Prisoner_91");
			link.l1.go = "exit";
			AddQuestRecord("LSC_findDekster", "14");
			npchar.quest.decster = true; //не повторять базар
			RemoveLandQuestMark_Main(npchar, "LSC_findDekster");
		break;
		//вино от Доминика Легро
		case "WineLogro":
			dialog.text = StringFromKey("Prisoner_92");
			link.l1 = StringFromKey("Prisoner_93", pchar);
			link.l1.go = "WineLogro_1";
		break;
		case "WineLogro_1":
			dialog.text = StringFromKey("Prisoner_94");
			link.l1 = StringFromKey("Prisoner_95");
			link.l1.go = "WineLogro_2";
			TakeItemFromCharacter(pchar, "potionwine");
		break;
		case "WineLogro_2":
			dialog.text = StringFromKey("Prisoner_96");
			link.l1 = StringFromKey("Prisoner_97");
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toFackDominic";
			Log_Info(StringFromKey("InfoMessages_211"));
			AddQuestRecord("TakeVineToPrisoner", "2");
			AddQuestUserData("TakeVineToPrisoner", "sSex", GetSexPhrase("ёс", "есла"));
			RemoveLandQuestMark_Main(npchar, "TakeVineToPrisoner");
			RemoveLandQuestMark_Main(CharacterFromID("LSC_Trader"), "TakeVineToPrisoner");
			AddLandQuestMark_Main(CharacterFromId("DominicLegro"), "TakeVineToPrisoner");
		break;

		case "SecondLogro":
			dialog.text = StringFromKey("Prisoner_98");
			link.l1 = StringFromKey("Prisoner_99", pchar);
			link.l1.go = "SecondLogro_1";
		break;
		case "SecondLogro_1":
			dialog.text = StringFromKey("Prisoner_100");
			link.l1 = StringFromKey("Prisoner_101");
			link.l1.go = "SecondLogro_2";
		break;
		case "SecondLogro_2":
			iTemp = GetCharacterIndex("LSCwaitress");
			if (iTemp != -1 && characters[iTemp].name == FindPersonalName("LSCwaitress_name"))
			{
				dialog.text = StringFromKey("Prisoner_102");
				link.l1 = StringFromKey("Prisoner_103");
				link.l1.go = "SecondLogro_3";
				pchar.questTemp.LSC.LegroHelp.Armo = true; //флаг на то, что квест пошёл с участием Армо
			}
			else
			{
				dialog.text = StringFromKey("Prisoner_104");
				link.l1 = StringFromKey("Prisoner_105");
				link.l1.go = "LastLegroAdd";
			}
		break;
		case "SecondLogro_3":
			dialog.text = StringFromKey("Prisoner_106");
			link.l1 = StringFromKey("Prisoner_107");
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toArmoDominic";
			AddQuestRecord("TakeVineToPrisoner", "4");
			RemoveLandQuestMark_Main(npchar, "TakeVineToPrisoner");
			AddLandQuestMark_Main(CharacterFromId("DominicLegro"), "TakeVineToPrisoner");
		break;

		case "LastLegro":
			dialog.text = StringFromKey("Prisoner_108");
			link.l1 = StringFromKey("Prisoner_109");
			link.l1.go = "LastLegro_1";
		break;
		case "LastLegro_1":
			dialog.text = StringFromKey("Prisoner_110");
			link.l1 = StringFromKey("Prisoner_111");
			link.l1.go = "LastLegro_2";
		break;
		case "LastLegro_2":
			dialog.text = StringFromKey("Prisoner_112", pchar);
			link.l1 = StringFromKey("Prisoner_113");
			link.l1.go = "LastLegro_3";
		break;
		case "LastLegro_3":
			dialog.text = StringFromKey("Prisoner_114");
			link.l1 = StringFromKey("Prisoner_115", pchar);
			link.l1.go = "exit";
			pchar.questTemp.LSC.LegroHelp = "toKeyDominic";
			AddQuestRecord("TakeVineToPrisoner", "6");
			RemoveLandQuestMark_Main(npchar, "TakeVineToPrisoner");
			AddLandQuestMark_Main(CharacterFromId("DominicLegro"), "TakeVineToPrisoner");
		break;

		case "LastLegroAdd":
			dialog.text = StringFromKey("Prisoner_116", pchar);
			link.l1 = StringFromKey("Prisoner_117");
			link.l1.go = "LastLegro_3";
		break;
		//помощь Томаса пока Армо жива
		case "ArmoIsLife":
			dialog.text = StringFromKey("Prisoner_118");
			link.l1 = StringFromKey("Prisoner_119");
			link.l1.go = "ArmoIsLife_1";
		break;
		case "ArmoIsLife_1":
			dialog.text = StringFromKey("Prisoner_120");
			link.l1 = StringFromKey("Prisoner_121");
			link.l1.go = "ArmoIsLife_2";
		break;
		case "ArmoIsLife_2":
			dialog.text = StringFromKey("Prisoner_122");
			link.l1 = StringFromKey("Prisoner_123");
			link.l1.go = "ArmoIsLife_3";
		break;
		case "ArmoIsLife_3":
			dialog.text = StringFromKey("Prisoner_124");
			link.l1 = StringFromKey("Prisoner_125");
			link.l1.go = "ArmoIsLife_4";
		break;
		case "ArmoIsLife_4":
			dialog.text = StringFromKey("Prisoner_126");
			link.l1 = StringFromKey("Prisoner_127", pchar);
			link.l1.go = "ArmoIsLife_5";
		break;
		case "ArmoIsLife_5":
			dialog.text = StringFromKey("Prisoner_128");
			link.l1 = StringFromKey("Prisoner_129");
			link.l1.go = "ArmoIsLife_6";
			link.l2 = StringFromKey("Prisoner_130");
			link.l2.go = "ArmoIsLife_7";
		break;
		case "ArmoIsLife_6":
			dialog.text = StringFromKey("Prisoner_131");
			link.l1 = StringFromKey("Prisoner_132");
			link.l1.go = "ArmoIsLife_7";
		break;
		case "ArmoIsLife_7":
			dialog.text = StringFromKey("Prisoner_133");
			link.l1 = StringFromKey("Prisoner_134");
			link.l1.go = "SuicideSquadBegin";
		break;
		//если Армо убита, то тюремщик может помочь в наезде на касперов
		case "ArmoIsDead":
			dialog.text = StringFromKey("Prisoner_135");
			link.l1 = StringFromKey("Prisoner_136");
			link.l1.go = "ArmoIsDead_1";
		break;
		case "ArmoIsDead_1":
			dialog.text = StringFromKey("Prisoner_137");
			link.l1 = StringFromKey("Prisoner_138");
			link.l1.go = "ArmoIsDead_2";
		break;
		case "ArmoIsDead_2":
			dialog.text = StringFromKey("Prisoner_139");
			link.l1 = StringFromKey("Prisoner_140", pchar);
			link.l1.go = "ArmoIsDead_3";
		break;
		case "ArmoIsDead_3":
			dialog.text = StringFromKey("Prisoner_141");
			link.l1 = StringFromKey("Prisoner_142", pchar);
			link.l1.go = "ArmoIsDead_4";
		break;
		case "ArmoIsDead_4":
			dialog.text = StringFromKey("Prisoner_143");
			link.l1 = StringFromKey("Prisoner_144");
			link.l1.go = "ArmoIsDead_5";
		break;
		case "ArmoIsDead_5":
			dialog.text = StringFromKey("Prisoner_145");
			link.l1 = StringFromKey("Prisoner_146");
			link.l1.go = "ArmoIsDead_6";
		break;
		case "ArmoIsDead_6":
			dialog.text = StringFromKey("Prisoner_147");
			link.l1 = StringFromKey("Prisoner_148");
			link.l1.go = "ArmoIsLife_5";
			link.l2 = StringFromKey("Prisoner_149");
			link.l2.go = "ArmoIsDead_7";
		break;
		case "ArmoIsDead_7":
			if (npchar.chr_ai.type == LAI_TYPE_SIT)
			{
				GetCharacterPos(npchar, &locx, &locy, &locz);
				ChangeCharacterAddressGroup(npchar, npchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			}
			npchar.dialog.currentnode = "AfterFightCasper";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_CharacterDisableDialog(npchar);
			LAi_warrior_SetCommander(npchar, pchar);
			LAi_SetRolyPoly(npchar, true);
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");

			SetFunctionLocationCondition("LSC_TempTomasWarrior", "LostShipsCity_town", true);

			AddQuestRecord("ISS_DefeatCasperClan", "12");
			AddQuestUserData("ISS_DefeatCasperClan", "sSex", GetSexPhrase("", "а"));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "SuicideSquadBegin":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddQuestRecord("ISS_DefeatCasperClan", "10");
			pchar.questTemp.LSC.suicideSquad = true;
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");
			AddLandQuestMark_Main(CharacterFromID("MalcolmFawn"), "ISS_DefeatCasperClan");
			AddLandQuestMark_Main(CharacterFromID("Ment_6"), "ISS_DefeatCasperClan");
			AddLandQuestMark_Main(CharacterFromID("MaximTailor"), "ISS_DefeatCasperClan");

			iTemp = GetCharacterIndex("LSCStBandit3");
			if (iTemp != -1 && !LAi_IsDead(&Characters[iTemp]))
			{
				AddQuestRecord("ISS_DefeatCasperClan", "11");
				AddLandQuestMark_Main(&Characters[iTemp], "ISS_DefeatCasperClan");
			}
		break;

		case "AfterFightCasper":
			dialog.text = StringFromKey("Prisoner_150");
			link.l1 = StringFromKey("Prisoner_151");
			link.l1.go = "AfterFightCasper_1";
		break;
		case "AfterFightCasper_1":
			dialog.text = StringFromKey("Prisoner_152");
			link.l1 = StringFromKey("Prisoner_153");
			link.l1.go = "AfterFightCasper_2";
		break;
		case "AfterFightCasper_2":
			dialog.text = StringFromKey("Prisoner_154");
			link.l1 = StringFromKey("Prisoner_155");
			link.l1.go = "AfterFightCasper_3";
		break;
		case "AfterFightCasper_3":
			AddDialogExitQuest("LSC_AfterFightCasperNoSuicideSquad_OpenTheDoors");

			LAi_SetActorTypeNoGroup(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 10.0);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//сбор отряда самоубийц
		case "SuicideSquad":
			dialog.text = StringFromKey("Prisoner_156");
			link.l1 = StringFromKey("Prisoner_157");
			link.l1.go = "exit";
			AddQuestRecord("ISS_DefeatCasperClan", "18");
			AddQuestUserData("ISS_DefeatCasperClan", "sName", GetFullName(npchar));
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");
			npchar.help_us = true;
			sIndex = its(GetCharacterIndex(npchar.id));
			pchar.questTemp.LSC.suicideSquad.(sIndex) = true;
			//с этого момента Бойл исполнять обязанности тюремщика больше не будет
			npchar.location.baseShip = "03"; //базовый корабль в ГПК
			npchar.location.baseLocator = "goto8";
			npchar.location.baseLocation = "CeresSmithy"; //базовая внутреняя локация
			npchar.location.baseShip.going = false; //перемещаться между кораблями в городе
			npchar.location = "CeresSmithy";
			npchar.location.group = "goto";
			npchar.location.locator = "goto8";
		break;
		case "SuicideSquad_ArmoDecision":
			iTemp = GetCharacterIndex("LSCwaitress");
			if (iTemp != -1 && characters[iTemp].name != FindPersonalName("LSCwaitress_name"))
			{
				dialog.text = StringFromKey("Prisoner_158");
				link.l1 = StringFromKey("Prisoner_159");
				link.l1.go = "exit";

				AddQuestRecord("ISS_DefeatCasperClan", "12");
				AddQuestUserData("ISS_DefeatCasperClan", "sSex", GetSexPhrase("", "а"));
				npchar.help_us = true;
				sIndex = its(GetCharacterIndex(npchar.id));
				pchar.questTemp.LSC.suicideSquad.(sIndex) = true;
				//с этого момента Бойл исполнять обязанности тюремщика больше не будет
				npchar.location.baseShip = "03"; //базовый корабль в ГПК
				npchar.location.baseLocator = "goto8";
				npchar.location.baseLocation = "CeresSmithy"; //базовая внутреняя локация
				npchar.location.baseShip.going = false; //перемещаться между кораблями в городе
				npchar.location = "CeresSmithy";
				npchar.location.group = "goto";
				npchar.location.locator = "goto8";
			}
			else
			{
				dialog.text = StringFromKey("Prisoner_160");
				link.l1 = StringFromKey("Prisoner_161");
				link.l1.go = "exit";

				npchar.LSC_SuicideSquad_NotHelpUs = true;

				AddQuestRecord("ISS_DefeatCasperClan", "24");
			}
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");
		break;
		case "RefusalToGo":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Prisoner_162"),
						StringFromKey("Prisoner_163"),
						StringFromKey("Prisoner_164"),
						StringFromKey("Prisoner_165"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Prisoner_166"),
						StringFromKey("Prisoner_167", pchar),
						StringFromKey("Prisoner_168"),
						StringFromKey("Prisoner_169", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;

		// найм команды - Томас Бойл
		case "SeekCrew_Tomas":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Prisoner_170"),
						StringFromKey("Prisoner_171"),
						StringFromKey("Prisoner_172"),
						StringFromKey("Prisoner_173", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Prisoner_174"),
						StringFromKey("Prisoner_175", pchar),
						StringFromKey("Prisoner_176"),
						StringFromKey("Prisoner_177"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_Tomas_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_Tomas_1":
			dialog.text = StringFromKey("Prisoner_178");
			link.l1 = StringFromKey("Prisoner_179");
			link.l1.go = "SeekCrew_Tomas_2";
		break;
		case "SeekCrew_Tomas_2":
			iTemp = GetCharacterIndex("LSCwaitress");
			if (iTemp != -1 && characters[iTemp].name != FindPersonalName("LSCwaitress_name"))
			{
				dialog.text = StringFromKey("Prisoner_180");
				link.l1 = StringFromKey("Prisoner_181");
				link.l1.go = "SeekCrew_Tomas_3";
			}
			else
			{
				npchar.LSC_seekCrew_Agree = true;

				dialog.text = StringFromKey("Prisoner_182");
				if (CheckAttribute(&characters[GetCharacterIndex("LSCwaitress")], "LSC_seekCrew_waitTomas"))
				{
					link.l1 = StringFromKey("Prisoner_183", pchar);
					link.l1.go = "SeekCrew_Tomas_4";
				}
				else
				{
					link.l1 = StringFromKey("Prisoner_184");
					link.l1.go = "SeekCrew_Tomas_5";
				}
			}
		break;
		case "SeekCrew_Tomas_3":
			dialog.text = StringFromKey("Prisoner_185");
			link.l1 = StringFromKey("Prisoner_186");
			link.l1.go = "exit";
		break;
		case "SeekCrew_Tomas_4":
			dialog.text = StringFromKey("Prisoner_187");
			link.l1 = StringFromKey("Prisoner_188");
			link.l1.go = "exit";
			AddLandQuestMark_Main(CharacterFromID("LSCwaitress"), "ISS_MainLine");
		break;
		case "SeekCrew_Tomas_5":
			dialog.text = StringFromKey("Prisoner_189");
			link.l1 = StringFromKey("Prisoner_190");
			link.l1.go = "exit";
			AddLandQuestMark_Main(CharacterFromID("LSCwaitress"), "ISS_MainLine");
		break;

		//финальная реплика - Томас Бойл
		case "GoodBye":
			dialog.text = StringFromKey("Prisoner_191");
			link.l1 = StringFromKey("Prisoner_192");
			link.l1.go = "GoodBye_1";
		break;
		case "GoodBye_1":
			dialog.text = StringFromKey("Prisoner_193");
			link.l1 = StringFromKey("Prisoner_194");
			link.l1.go = "GoodBye_2";
		break;
		case "GoodBye_2":
			dialog.text = StringFromKey("Prisoner_195");
			link.l1 = StringFromKey("Prisoner_196");
			link.l1.go = "GoodBye_3";
		break;
		case "GoodBye_3":
			dialog.text = StringFromKey("Prisoner_197");
			link.l1 = StringFromKey("Prisoner_198");
			link.l1.go = "GoodBye_4";
			link.l2 = StringFromKey("Prisoner_199");
			link.l2.go = "GoodBye_4";
			link.l3 = StringFromKey("Prisoner_200");
			link.l3.go = "GoodBye_4";
		break;
		case "GoodBye_4":
			dialog.text = StringFromKey("Prisoner_201");
			link.l1 = StringFromKey("Prisoner_202");
			link.l1.go = "Exit_GoodBye";
		break;
	}
}
