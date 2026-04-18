//Диалоговый файл Тизера Дена
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string attrL, sRep;
	int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;

	attrL = Dialog.CurrentNode;

	if (HasSubStr(attrL, "-"))
	{
		i = findsubstr(attrL, "-", 0);
		sRep = strcut(attrL, i + 1, strlen(attrL) - 1);
		if (sRep == "bad") npchar.TizerBadRep = sti(npchar.TizerBadRep) + 1;
		else if (sRep == "good") npchar.TizerGoodRep = sti(npchar.TizerGoodRep) + 1;
		Dialog.CurrentNode = strcut(attrL, 0, i - 1);
	}

	switch (Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (pchar.questTemp.LSC == "GoToTizerLSC")
			{
				RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
				dialog.text = StringFromKey("TizerDen_1");
				link.l1 = StringFromKey("TizerDen_2");
				link.l1.go = "meeting_1";
				link.l2 = StringFromKey("TizerDen_3");
				link.l2.go = "meeting_1-bad";
				if (CheckAttribute(pchar, "questTemp.LSC.bomjSpy"))
				{
					link.l3 = StringFromKey("TizerDen_4");
					link.l3.go = "meeting_1-good";
				}
				break;
			}
			dialog.text = StringFromKey("TizerDen_5");
			link.l1 = StringFromKey("TizerDen_6");
			link.l1.go = "exit";
			if (pchar.questTemp.LSC == "MayorApprovedLSC")
			{
				link.l1 = StringFromKey("TizerDen_7");
				link.l1.go = "MayorApprovedLSC_1";
				RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
			}
			if (pchar.questTemp.LSC == "MayorFiledLSC")
			{
				link.l1 = StringFromKey("TizerDen_8");
				link.l1.go = "MayorFiledLSC_1";
				RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
			}
		break;

		//первый разговор с Тизером
		case "meeting_1":
			dialog.text = StringFromKey("TizerDen_9", pchar);
			link.l1 = StringFromKey("TizerDen_10");
			link.l1.go = "meeting_2";
			link.l2 = StringFromKey("TizerDen_11");
			link.l2.go = "meeting_2";
			link.l3 = StringFromKey("TizerDen_12");
			link.l3.go = "meeting_2-bad";
		break;
		case "meeting_2":
			dialog.text = StringFromKey("TizerDen_13");
			link.l1 = StringFromKey("TizerDen_14");
			link.l1.go = "meeting_3";
		break;
		case "meeting_3":
			dialog.text = StringFromKey("TizerDen_15");
			link.l1 = StringFromKey("TizerDen_16");
			link.l1.go = "meeting_4-bad";
			link.l2 = StringFromKey("TizerDen_17");
			link.l2.go = "meeting_4";
			if (CheckAttribute(pchar, "questTemp.LSC.bomjSpy"))
			{
				link.l3 = StringFromKey("TizerDen_18");
				link.l3.go = "meeting_4-good";
			}
		break;
		case "meeting_4":
			dialog.text = StringFromKey("TizerDen_19");
			link.l1 = StringFromKey("TizerDen_20");
			link.l1.go = "meeting_5";
			link.l2 = StringFromKey("TizerDen_21");
			link.l2.go = "meeting_5-bad";
			if (CheckAttribute(pchar, "questTemp.LSC.bomjSpy"))
			{
				link.l3 = StringFromKey("TizerDen_22", pchar);
				link.l3.go = "meeting_5-good";
			}
		break;
		case "meeting_5":
			dialog.text = "Fallaces sunt rerum species.";
			if (CheckCharacterPerk(pchar, "Nobleman"))
			{
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				link.l1 = StringFromKey("TizerDen_23");
				link.l1.go = "meeting_6";
			}
			else
			{
				link.l1 = StringFromKey("TizerDen_24");
				link.l1.go = "meeting_6";
			}
		break;
		case "meeting_6":
			if (sti(npchar.TizerBadRep) > 1) // допустили 2 ошибки
			{
				dialog.text = StringFromKey("TizerDen_25");
				link.l1 = StringFromKey("TizerDen_26");
				link.l1.go = "meeting_7";
				link.l2 = StringFromKey("TizerDen_27");
				link.l2.go = "meeting_8";
				break;
			}
			dialog.text = StringFromKey("TizerDen_28");
			link.l1 = StringFromKey("TizerDen_29");
			link.l1.go = "meeting_9";
		break;
		case "meeting_7":
			AddQuestRecord("ISS_PoorsMurder", "34");
			CloseQuestHeader("ISS_PoorsMurder");
			EndISS_PoorsMurderLine(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "meeting_8":
			AddQuestRecord("ISS_PoorsMurder", "28");
			AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("ISS_PoorsMurder");
			EndISS_PoorsMurderLine(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "meeting_9":
			dialog.text = StringFromKey("TizerDen_30");
			link.l1 = StringFromKey("TizerDen_31");
			link.l1.go = "meeting_10";
		break;
		case "meeting_10":
			dialog.text = StringFromKey("TizerDen_32");
			link.l1 = StringFromKey("TizerDen_33", pchar);
			link.l1.go = "meeting_11";
		break;
		case "meeting_11":
			dialog.text = StringFromKey("TizerDen_34");
			link.l1 = StringFromKey("TizerDen_35");
			link.l1.go = "meeting_12";
		break;
		case "meeting_12":
			dialog.text = StringFromKey("TizerDen_36");
			if (npchar.TizerGoodRep == "3") // допустили 2 ошибки
			{
				link.l1 = StringFromKey("TizerDen_37");
				link.l1.go = "meeting_14";
			}
			else
			{
				link.l1 = StringFromKey("TizerDen_38");
				link.l1.go = "meeting_13";
			}
			pchar.questTemp.LSC = "SaveTizerDen";
			SetQuestHeader("TheStarsAlignedISS");
			AddQuestRecord("TheStarsAlignedISS", "1");
			AddLandQuestMark_Main(CharacterFromID("Minetown_Commend"), "ISS_PoorsMurder");
		break;
		case "meeting_13":
			dialog.text = StringFromKey("TizerDen_39");
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		case "meeting_14":
			dialog.text = StringFromKey("TizerDen_40");
			link.l1 = StringFromKey("TizerDen_41");
			link.l1.go = "meeting_15";
			AddItemLog(pchar, "HolFakeLicence", "1", StringFromKey("InfoMessages_135", GetItemName("HolFakeLicence")), "Notebook_1");
		break;
		case "meeting_15":
			dialog.text = StringFromKey("TizerDen_42");
			link.l1 = StringFromKey("TizerDen_43");
			link.l1.go = "meeting_16";
		break;
		case "meeting_16":
			dialog.text = StringFromKey("TizerDen_44");
			link.l1 = StringFromKey("TizerDen_45");
			link.l1.go = "meeting_17";
		break;
		case "meeting_17":
			dialog.text = StringFromKey("TizerDen_46");
			link.l1 = StringFromKey("TizerDen_47");
			link.l1.go = "meeting_18";
		break;
		case "meeting_18":
			dialog.text = StringFromKey("TizerDen_48");
			link.l1 = StringFromKey("TizerDen_49");
			link.l1.go = "exit";
		break;

		case "Exit":
			if (CheckAttribute(&TEV, "NoDialogExit")) DeleteAttribute(&TEV, "NoDialogExit");
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
			dialog.text = StringFromKey("House_dialog_43", LinkRandPhrase(
						StringFromKey("House_dialog_40", pchar),
						StringFromKey("House_dialog_41", pchar),
						StringFromKey("House_dialog_42", pchar)));
			link.l1 = StringFromKey("House_dialog_44");
			link.l1.go = "fight";
		break;

		//если команданте нам не поверил
		case "MayorFiledLSC_1":
			dialog.text = StringFromKey("TizerDen_50");
			link.l1 = StringFromKey("TizerDen_51");
			link.l1.go = "MayorFiledLSC_2";
		break;
		case "MayorFiledLSC_2":
			dialog.text = StringFromKey("TizerDen_52");
			link.l1 = StringFromKey("TizerDen_53");
			AddItemLog(pchar, "suit_1", "1", StringFromKey("InfoMessages_171"), "Important_item");
			link.l1.go = "MayorFiledLSC_3";
		break;
		case "MayorFiledLSC_3":
			dialog.text = StringFromKey("TizerDen_54");
			link.l1 = StringFromKey("TizerDen_55");
			link.l1.go = "MayorFiledLSC_4";
		break;
		case "MayorFiledLSC_4":
			dialog.text = StringFromKey("TizerDen_56");
			link.l1 = StringFromKey("TizerDen_57");
			link.l1.go = "MayorFiledLSC_5";
		break;
		case "MayorFiledLSC_5":
			dialog.text = StringFromKey("TizerDen_58");
			link.l1 = StringFromKey("TizerDen_59");
			link.l1.go = "MayorFiledLSC_6";
		break;
		case "MayorFiledLSC_6":
			dialog.text = StringFromKey("TizerDen_60");
			link.l1 = StringFromKey("TizerDen_61");
			link.l1.go = "exit";
			AddDialogExitQuest("NightTimeOutingLSC");
		break;

		//если команданте нам поверил
		case "MayorApprovedLSC_1":
			dialog.text = StringFromKey("TizerDen_62");
			link.l1 = StringFromKey("TizerDen_63");
			link.l1.go = "MayorApprovedLSC_2";
		break;
		case "MayorApprovedLSC_2":
			dialog.text = StringFromKey("TizerDen_64");
			link.l1 = StringFromKey("TizerDen_65");
			link.l1.go = "MayorApprovedLSC_3";
		break;
		case "MayorApprovedLSC_3":
			dialog.text = StringFromKey("TizerDen_66");
			link.l1 = StringFromKey("TizerDen_67");
			link.l1.go = "MayorApprovedLSC_4";
		break;
		case "MayorApprovedLSC_4":
			dialog.text = StringFromKey("TizerDen_68");
			link.l1 = StringFromKey("TizerDen_69");
			link.l1.go = "exit";
			AddDialogExitQuest("DaytimeOutingLSC");
		break;

		case "DaytimeOutingLSC":
			dialog.text = StringFromKey("TizerDen_70");
			link.l1 = StringFromKey("TizerDen_71");
			link.l1.go = "exit";
			AddDialogExitQuest("DaytimeOutingLSC_3");
		break;

		case "DaytimeOutingLSC_1":
			dialog.text = StringFromKey("TizerDen_72");
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("DaytimeOutingLSC_6");
		break;

		case "SlaveDialog":
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("TizerDenLSC"));
			dialog.text = StringFromKey("TizerDen_73");
			link.l1 = StringFromKey("TizerDen_74");
			link.l1.go = "exit";
			AddDialogExitQuest("DaytimeOutingLSC_9");
		break;

		case "FortOrangeAhtung":
			dialog.text = StringFromKey("TizerDen_75");
			link.l1 = StringFromKey("TizerDen_76");
			link.l1.go = "FortOrangeAhtung_1";
		break;
		case "FortOrangeAhtung_1":
			dialog.text = StringFromKey("TizerDen_77");
			link.l1 = StringFromKey("TizerDen_78");
			link.l1.go = "FortOrangeAhtung_2";
		break;
		case "FortOrangeAhtung_2":
			dialog.text = StringFromKey("TizerDen_79");
			link.l1 = StringFromKey("TizerDen_80");
			link.l1.go = "FortOrangeAhtung_3";
		break;
		case "FortOrangeAhtung_3":
			dialog.text = StringFromKey("TizerDen_81");
			link.l1 = StringFromKey("TizerDen_82");
			link.l1.go = "FortOrangeAhtung_4";
		break;
		case "FortOrangeAhtung_4":
			dialog.text = StringFromKey("TizerDen_83");
			link.l1 = StringFromKey("TizerDen_84");
			link.l1.go = "FortOrangeAhtung_5";
		break;
		case "FortOrangeAhtung_5":
			dialog.text = StringFromKey("TizerDen_85");
			link.l1 = StringFromKey("TizerDen_86");
			link.l1.go = "exit";
			AddDialogExitQuest("AhtungMinetown_2");
		break;

		case "NightTimeOutingLSC_1":
			sld = GetCharacter(sti(TEV.NightTimeOutingNPC));
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, npchar);
			LAi_ActorTurnToCharacter(npchar, sld);
			dialog.text = StringFromKey("TizerDen_87");
			link.l1 = StringFromKey("TizerDen_88");
			link.l1.go = "NightTimeOutingLSC_2";
		break;
		case "NightTimeOutingLSC_2":
			dialog.text = StringFromKey("TizerDen_89");
			link.l1 = StringFromKey("TizerDen_90");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("NightTimeOutingLSCFunc_4");
		break;

		case "OutFromMineLSC_1":
			dialog.text = StringFromKey("TizerDen_91");
			link.l1 = StringFromKey("TizerDen_92");
			link.l1.go = "OutFromMineLSC_2";
		break;
		case "OutFromMineLSC_2":
			dialog.text = StringFromKey("TizerDen_93");
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("OutFromMineLSC_2");
		break;

		case "Minetown_Commend":
			dialog.text = StringFromKey("TizerDen_94");
			link.l1 = StringFromKey("TizerDen_95");
			link.l1.go = "exit";
			AddDialogExitQuest("OutFromMineLSC_3");
		break;

		case "OutFromMineEndLSC_1":
			dialog.text = StringFromKey("TizerDen_96");
			link.l1 = StringFromKey("TizerDen_97");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("NightTimeOutingLSCFunc_6");
		break;
		case "OutFromMineEndLSC_2":
			dialog.text = StringFromKey("TizerDen_98");
			link.l1 = StringFromKey("TizerDen_99");
			link.l1.go = "OutFromMineEndLSC_3";
		break;
		case "OutFromMineEndLSC_3":
			dialog.text = StringFromKey("TizerDen_100");
			link.l1 = StringFromKey("TizerDen_101");
			link.l1.go = "OutFromMineEndLSC_4";
		break;
		case "OutFromMineEndLSC_4":
			dialog.text = StringFromKey("TizerDen_102");
			link.l1 = StringFromKey("TizerDen_103");
			link.l1.go = "exit";
			AddDialogExitQuest("OutFromMineLSC_6");
		break;

		case "NightTimeAlcholOutLSC_1":
			dialog.text = StringFromKey("TizerDen_104");
			link.l1 = StringFromKey("TizerDen_105");
			link.l1.go = "NightTimeAlchoOutLSC_2";
		break;
		case "NightTimeAlchoOutLSC_2":
			dialog.text = StringFromKey("TizerDen_106");
			link.l1 = StringFromKey("TizerDen_107");
			link.l1.go = "exit";
			AddDialogExitQuest("OutFromMineLSC_8");
		break;
		case "NightTimeAlcholOutLSC_3":
			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
			dialog.text = StringFromKey("TizerDen_108");
			link.l1 = StringFromKey("TizerDen_109");
			link.l1.go = "NightTimeAlcholOutLSC_4";
		break;
		case "NightTimeAlcholOutLSC_4":
			dialog.text = StringFromKey("TizerDen_110");
			link.l1 = StringFromKey("TizerDen_111");
			link.l1.go = "NightTimeAlcholOutLSC_5";
		break;
		case "NightTimeAlcholOutLSC_5":
			dialog.text = StringFromKey("TizerDen_112");
			link.l1 = StringFromKey("TizerDen_113");
			link.l1.go = "NightTimeAlcholOutLSC_6";
		break;
		case "NightTimeAlcholOutLSC_6":
			dialog.text = StringFromKey("TizerDen_114");
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("OutFromMineLSC_9");
		break;

		case "TheStarsAligned":
			dialog.text = StringFromKey("TizerDen_115");
			link.l1 = StringFromKey("TizerDen_116");
			link.l1.go = "TheStarsAligned_1";
		break;
		case "TheStarsAligned_1":
			dialog.text = StringFromKey("TizerDen_117");
			link.l1 = StringFromKey("TizerDen_118");
			link.l1.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_2");
		break;

		case "JungleManAndTitherDialog":
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("JungleManLSC"));
			dialog.text = StringFromKey("TizerDen_119");
			link.l1 = StringFromKey("TizerDen_120");
			link.l1.go = "JungleManAndTitherDialog_1";
		break;
		case "JungleManAndTitherDialog_1":
			dialog.text = StringFromKey("TizerDen_121");
			link.l1 = StringFromKey("TizerDen_122");
			link.l1.go = "JungleManAndTitherDialog_2";
		break;
		case "JungleManAndTitherDialog_2":
			dialog.text = StringFromKey("TizerDen_123");
			link.l1 = StringFromKey("TizerDen_124");
			link.l1.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_17");
		break;

		case "JungleDialog":
			dialog.text = StringFromKey("TizerDen_125");
			link.l1 = StringFromKey("TizerDen_126");
			link.l1.go = "JungleDialog_1";
		break;
		case "JungleDialog_1":
			dialog.text = StringFromKey("TizerDen_127");
			link.l1 = StringFromKey("TizerDen_128");
			link.l1.go = "exit";
			link.l2 = StringFromKey("TizerDen_129");
			link.l2.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_19");
		break;

		case "ThirdWaves":
			dialog.text = StringFromKey("TizerDen_130");
			link.l1 = StringFromKey("TizerDen_131");
			link.l1.go = "ThirdWaves_1";
		break;
		case "ThirdWaves_1":
			dialog.text = StringFromKey("TizerDen_132");
			link.l1 = StringFromKey("TizerDen_133");
			sRep = GetCharacterEquipByGroup(npchar, BLADE_ITEM_TYPE);
			if (sRep == "")
				link.l1.go = "ThirdWaves_2";
			else
				link.l1.go = "ThirdWaves_3";
		break;
		case "ThirdWaves_2":
			AddItemLog(pchar, "pistol3", "1", StringFromKey("InfoMessages_135", GetItemName("pistol3")), "Important_item");
			EquipCharacterbyItem(pchar, "pistol3");
			dialog.text = StringFromKey("TizerDen_134");
			link.l1 = StringFromKey("TizerDen_135");
			link.l1.go = "ThirdWaves_4";
		break;
		case "ThirdWaves_3":
			dialog.text = StringFromKey("TizerDen_136");
			link.l1 = StringFromKey("TizerDen_137");
			link.l1.go = "ThirdWaves_4";
		break;
		case "ThirdWaves_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("TheStarsAlignedLSC_34");
		break;

	}
	NextDiag.PrevNode = NodeName;
}

void EndISS_PoorsMurderLine(ref npchar)
{
	TakeItemFromCharacter(pchar, "letter_LSC_1");
	LAi_CharacterDisableDialog(npchar);
	npchar.lifeday = 1;
	pchar.questTemp.LSC = "GoToLSC";
	AddDialogExitQuest("ReloadEnableLSC");
}
