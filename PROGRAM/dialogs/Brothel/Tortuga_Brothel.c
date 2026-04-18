// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;

	// evganat - пасха
	int i, iTemp;
	string sAttr;
	sAttr = Dialog.CurrentNode;

	if (HasSubStr(sAttr, "BuyPIRATES_choosechr-"))
	{
		i = findsubstr(sAttr, "-", 0);
		pchar.questTemp.Azzy.AddPIRATES_chridx = strcut(sAttr, i + 1, strlen(sAttr) - 1);
		Dialog.CurrentNode = "BuyPIRATES_ok";
	}

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_Brothel_3", RandPhraseSimple(
								StringFromKey("Tortuga_Brothel_1", pchar),
								StringFromKey("Tortuga_Brothel_2", pchar))),
						StringFromKey("Tortuga_Brothel_4"),
						StringFromKey("Tortuga_Brothel_5"),
						StringFromKey("Tortuga_Brothel_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_Brothel_9", RandPhraseSimple(
								StringFromKey("Tortuga_Brothel_7", pchar),
								StringFromKey("Tortuga_Brothel_8"))),
						StringFromKey("Tortuga_Brothel_10"),
						StringFromKey("Tortuga_Brothel_11"),
						StringFromKey("Tortuga_Brothel_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//==> Голл. №3, узнаем о Пеьере Пикардийце.
			if (pchar.questTemp.State == "WormEnglPlans_WormPicarder")
			{
				link.l1 = StringFromKey("Tortuga_Brothel_13");
				link.l1.go = "Step_H3_1";
			}
			// ==> квест Аззи.
			if (CheckAttribute(pchar, "questTemp.Azzy.AddSpecial"))
			{
				dialog.text = StringFromKey("Tortuga_Brothel_14", GetAddress_Form(NPChar));
				Link.l1 = StringFromKey("Tortuga_Brothel_15");
				Link.l1.go = "Step_1";
			}

			// evganat - пасха
			if (CheckAttribute(pchar, "questTemp.Azzy.AddPIRATES_first"))
			{
				dialog.text = StringFromKey("Tortuga_Brothel_16", pchar);
				if (GetCharacterItem(pchar, pchar.questTemp.Azzy.AddPIRATES_jewel) >= 1 && sti(pchar.money) >= 50000 && GetCharacterItem(pchar, "mineral3") >= 6 && GetCharacterItem(pchar, "jewelry11") >= 10)
				{
					Link.l1 = StringFromKey("Tortuga_Brothel_17");
					Link.l1.go = "BuyPIRATES_choosepoints";
				}
				link.l2 = StringFromKey("Tortuga_Brothel_18");
				link.l2.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Azzy.AddPIRATES_again") && !HasStr(pchar.questTemp.State, "WormEnglPlans_WormPicarder"))
			{
				dialog.text = StringFromKey("Tortuga_Brothel_19");
				link.l1 = StringFromKey("Tortuga_Brothel_20");
				link.l1.go = "BuyPIRATES_again";
			}

			if (pchar.questTemp.Azzy == "HowToKnowAzzy" && !CheckAttribute(pchar, "questTemp.Azzy.AddSpecial"))
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("Tortuga_Brothel_21", GetAddress_Form(NPChar)),
							StringFromKey("Tortuga_Brothel_22"),
							StringFromKey("Tortuga_Brothel_23"),
							StringFromKey("Tortuga_Brothel_24"), "block", 0, npchar, Dialog.CurrentNode);
				Link.l1 = HeroStringReactionRepeat(
							StringFromKey("Tortuga_Brothel_25"),
							StringFromKey("Tortuga_Brothel_26"),
							StringFromKey("Tortuga_Brothel_27"),
							StringFromKey("Tortuga_Brothel_28"), npchar, Dialog.CurrentNode);
				Link.l1.go = DialogGoNodeRepeat("Step_15", "none", "none", "none", npchar, Dialog.CurrentNode);
			}
			if (pchar.questTemp.Azzy == "DestrContract")
			{
				dialog.text = StringFromKey("Tortuga_Brothel_29");
				Link.l1 = StringFromKey("Tortuga_Brothel_30");
				Link.l1.go = "Step_17";
			}
			if (pchar.questTemp.Azzy == "2DestrContract")
			{
				dialog.text = StringFromKey("Tortuga_Brothel_31");
				Link.l1 = StringFromKey("Tortuga_Brothel_32");
				Link.l1.go = "Step_20";
			}
		// <== Проверяем поле состояния квестов.
		break;
		//==>Голландская линейка, квест №3.
		case "Step_H3_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_Brothel_33"),
						StringFromKey("Tortuga_Brothel_34", pchar),
						StringFromKey("Tortuga_Brothel_35"),
						StringFromKey("Tortuga_Brothel_36", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_Brothel_37"),
						StringFromKey("Tortuga_Brothel_38"),
						StringFromKey("Tortuga_Brothel_39"),
						StringFromKey("Tortuga_Brothel_40"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H3_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_H3_2":
			dialog.text = StringFromKey("Tortuga_Brothel_41", pchar);
			link.l1 = StringFromKey("Tortuga_Brothel_42");
			link.l1.go = "exit";
			pchar.questTemp.Hol_Line_AboutWorm.Brothel = true;
			AddQuestRecord("Hol_Line_3_WormEnglishPlans", "11");
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;
		//==> Квест Аззи
		case "Step_1":
			dialog.text = StringFromKey("Tortuga_Brothel_43");
			Link.l1 = StringFromKey("Tortuga_Brothel_44", GetFullName(pchar));
			Link.l1.go = "Step_2";
		break;
		case "Step_2":
			dialog.text = StringFromKey("Tortuga_Brothel_45", pchar);
			Link.l1 = StringFromKey("Tortuga_Brothel_46");
			Link.l1.go = "Step_3";
		break;
		case "Step_3":
			dialog.text = StringFromKey("Tortuga_Brothel_47");
			Link.l1 = StringFromKey("Tortuga_Brothel_48");
			Link.l1.go = "Step_4";
		break;
		case "Step_4":
			dialog.text = StringFromKey("Tortuga_Brothel_49");
			Link.l1 = StringFromKey("Tortuga_Brothel_50", pchar);
			Link.l1.go = "Step_5";
		break;
		case "Step_5":
			dialog.text = StringFromKey("Tortuga_Brothel_51", pchar);
			Link.l1 = StringFromKey("Tortuga_Brothel_52", pchar);
			Link.l1.go = "Step_6";
		break;
		case "Step_6":
			dialog.text = StringFromKey("Tortuga_Brothel_53", pchar);
			Link.l1 = StringFromKey("Tortuga_Brothel_54", pchar);
			Link.l1.go = "BuyPIRATES_1"; //"Step_7"; evganat - пасха
		break;
		case "Step_7":
			dialog.text = StringFromKey("Tortuga_Brothel_55");
			Link.l1 = StringFromKey("Tortuga_Brothel_56", pchar);
			Link.l1.go = "Step_8";
		break;
		case "Step_8":
			dialog.text = StringFromKey("Tortuga_Brothel_57", pchar);
			Link.l1 = StringFromKey("Tortuga_Brothel_58", pchar);
			Link.l1.go = "Step_9";
		break;
		case "Step_9":
			dialog.text = StringFromKey("Tortuga_Brothel_59");
			Link.l1 = StringFromKey("Tortuga_Brothel_60");
			Link.l1.go = "Strength";
			Link.l2 = StringFromKey("Tortuga_Brothel_61");
			Link.l2.go = "Perception";
			Link.l3 = StringFromKey("Tortuga_Brothel_62");
			Link.l3.go = "Agility";
			Link.l4 = StringFromKey("Tortuga_Brothel_63");
			Link.l4.go = "Charisma";
			Link.l5 = StringFromKey("Tortuga_Brothel_64");
			Link.l5.go = "Intellect";
			Link.l6 = StringFromKey("Tortuga_Brothel_65");
			Link.l6.go = "Endurance";
			Link.l7 = StringFromKey("Tortuga_Brothel_66");
			Link.l7.go = "Luck";
		break;
		case "Strength":
			dialog.text = StringFromKey("Tortuga_Brothel_67");
			Link.l1 = StringFromKey("Tortuga_Brothel_68");
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_S, 0) == SPECIAL_MAX)
			{
				Link.l1.go = "NotPosblAdd";
			}
			else
			{
				AddSPECIALValue(pchar, SPECIAL_S, 1);
			}
		break;
		case "Perception":
			dialog.text = StringFromKey("Tortuga_Brothel_69");
			Link.l1 = StringFromKey("Tortuga_Brothel_70");
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_P, 0) == SPECIAL_MAX)
			{
				Link.l1.go = "NotPosblAdd";
			}
			else
			{
				AddSPECIALValue(pchar, SPECIAL_P, 1);
			}
		break;
		case "Endurance":
			dialog.text = StringFromKey("Tortuga_Brothel_71");
			Link.l1 = StringFromKey("Tortuga_Brothel_72");
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_E, 0) == SPECIAL_MAX)
			{
				Link.l1.go = "NotPosblAdd";
			}
			else
			{
				AddSPECIALValue(pchar, SPECIAL_E, 1);
			}
		break;
		case "Charisma":
			dialog.text = StringFromKey("Tortuga_Brothel_73", pchar);
			Link.l1 = StringFromKey("Tortuga_Brothel_74");
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_C, 0) == SPECIAL_MAX)
			{
				Link.l1.go = "NotPosblAdd";
			}
			else
			{
				AddSPECIALValue(pchar, SPECIAL_C, 1);
			}
		break;
		case "Intellect":
			dialog.text = StringFromKey("Tortuga_Brothel_75");
			Link.l1 = StringFromKey("Tortuga_Brothel_76");
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_I, 0) == SPECIAL_MAX)
			{
				Link.l1.go = "NotPosblAdd";
			}
			else
			{
				AddSPECIALValue(pchar, SPECIAL_I, 1);
			}
		break;
		case "Agility":
			dialog.text = StringFromKey("Tortuga_Brothel_77");
			Link.l1 = StringFromKey("Tortuga_Brothel_78");
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_A, 0) == SPECIAL_MAX)
			{
				Link.l1.go = "NotPosblAdd";
			}
			else
			{
				AddSPECIALValue(pchar, SPECIAL_A, 1);
			}
		break;
		case "Luck":
			dialog.text = StringFromKey("Tortuga_Brothel_79", pchar);
			Link.l1 = StringFromKey("Tortuga_Brothel_80");
			Link.l1.go = "Step_10";
			if (AddSPECIALValue(pchar, SPECIAL_L, 0) == SPECIAL_MAX)
			{
				Link.l1.go = "NotPosblAdd";
			}
			else
			{
				AddSPECIALValue(pchar, SPECIAL_L, 1);
			}
		break;
		case "Step_10":
			dialog.text = StringFromKey("Tortuga_Brothel_81", pchar);
			Link.l1 = StringFromKey("Tortuga_Brothel_82");
			Link.l1.go = "Step_11";
		break;
		case "Step_11":
			dialog.text = StringFromKey("Tortuga_Brothel_83");
			Link.l1 = StringFromKey("Tortuga_Brothel_84", pchar);
			Link.l1.go = "Step_12";
		break;
		case "Step_12":
			dialog.text = StringFromKey("Tortuga_Brothel_85", pchar);
			Link.l1 = StringFromKey("Tortuga_Brothel_86");
			Link.l1.go = "Step_13";
		break;
		case "Step_13":
			dialog.text = StringFromKey("Tortuga_Brothel_87");
			Link.l1 = StringFromKey("Tortuga_Brothel_88");
			Link.l1.go = "exit";
			AddDialogExitQuest("Azzy_PlusSkill");
		break;
		case "NotPosblAdd":
			dialog.text = StringFromKey("Tortuga_Brothel_89", pchar);
			Link.l1 = StringFromKey("Tortuga_Brothel_90", pchar);
			Link.l1.go = "Step_9";
		break;
		case "Step_15":
			dialog.text = StringFromKey("Tortuga_Brothel_91");
			Link.l1 = StringFromKey("Tortuga_Brothel_92");
			Link.l1.go = "Step_16";
		break;
		case "Step_16":
			dialog.text = StringFromKey("Tortuga_Brothel_93", pchar);
			Link.l1 = StringFromKey("Tortuga_Brothel_94");
			Link.l1.go = "exit";
		break;
		case "Step_17":
			dialog.text = StringFromKey("Tortuga_Brothel_95");
			Link.l1 = StringFromKey("Tortuga_Brothel_96");
			Link.l1.go = "Step_18";
		break;
		case "Step_18":
			dialog.text = StringFromKey("Tortuga_Brothel_97");
			Link.l1 = StringFromKey("Tortuga_Brothel_98");
			Link.l1.go = "Step_19";
		break;
		case "Step_19":
			dialog.text = StringFromKey("Tortuga_Brothel_99");
			Link.l1 = StringFromKey("Tortuga_Brothel_100");
			Link.l1.go = "Step_20";
		break;
		case "Step_20":
			dialog.text = StringFromKey("Tortuga_Brothel_101");
			if (CheckCharacterItem(pchar, "sculMa1") && CheckCharacterItem(pchar, "sculMa2") && CheckCharacterItem(pchar, "sculMa3") && CheckCharacterItem(pchar, "indian22"))
			{
				Link.l1 = StringFromKey("Tortuga_Brothel_102");
				Link.l1.go = "Step_22";
			}
			else
			{
				Link.l1 = StringFromKey("Tortuga_Brothel_103");
				Link.l1.go = "Step_21";
			}
		break;
		case "Step_21":
			dialog.text = StringFromKey("Tortuga_Brothel_104");
			Link.l1 = StringFromKey("Tortuga_Brothel_105", pchar);
			Link.l1.go = "exit";
			pchar.questTemp.Azzy = "2DestrContract";
		break;
		case "Step_22":
			dialog.text = StringFromKey("Tortuga_Brothel_106");
			Link.l1 = StringFromKey("Tortuga_Brothel_107");
			Link.l1.go = "Step_23";
		break;
		case "Step_23":
			TakeItemFromCharacter(pchar, "sculMa1");
			TakeItemFromCharacter(pchar, "sculMa2");
			TakeItemFromCharacter(pchar, "sculMa3");
			TakeItemFromCharacter(pchar, "indian22");
			pchar.questTemp.Azzy = "3DestrContract";
			DeleteAttribute(pchar, "questTemp.Azzy.Oliver");
			ChangeCharacterAddressGroup(characterFromId("Azzy"), pchar.location, "goto", "goto2");
			DoQuestCheckDelay("Azzy_IsFree", 2.0);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Azzy_HellSign");
			RemoveLandQuestmark_Main(CharacterFromID("Oliver_Green"), "Azzy_HellSign");
		break;

		// evganat - пасха
		case "BuyPIRATES_1":
			dialog.text = StringFromKey("Tortuga_Brothel_108", pchar);
			link.l1 = StringFromKey("Tortuga_Brothel_109");
			link.l1.go = "BuyPIRATES_2";
		break;
		case "BuyPIRATES_2":
			dialog.text = StringFromKey("Tortuga_Brothel_110");
			link.l1 = StringFromKey("Tortuga_Brothel_111");
			link.l1.go = "BuyPIRATES_3";
		break;
		case "BuyPIRATES_3":
			dialog.text = StringFromKey("Tortuga_Brothel_112");
			pchar.questTemp.Azzy.AddPIRATES_jewel = "jewelry18";
			link.l1 = StringFromKey("Tortuga_Brothel_113");
			link.l1.go = "BuyPIRATES_4";
		break;
		case "BuyPIRATES_4":
			dialog.text = StringFromKey("Tortuga_Brothel_114");
			link.l1 = StringFromKey("Tortuga_Brothel_115");
			link.l1.go = "exit";
			pchar.questTemp.Azzy.AddPIRATES_first = true;
			DeleteAttribute(pchar, "questTemp.Azzy.AddSpecial");
			RemoveLandQuestmark_Main(npchar, "Azzy_Wishes");
		break;
		case "BuyPIRATES_choosepoints":
			if (CheckAttribute(pchar, "questTemp.Azzy.AddPIRATES_first"))
			{
				TakeNItems(pchar, pchar.questTemp.Azzy.AddPIRATES_jewel, -1);
			}
			TakeNItems(pchar, "mineral3", -6);
			dialog.text = StringFromKey("Tortuga_Brothel_116");
			link.l1 = StringFromKey("Tortuga_Brothel_117");
			link.l1.go = "BuyPIRATES_min";
			if (sti(pchar.money) >= 100000 && GetCharacterItem(pchar, "jewelry11") >= 20)
			{
				link.l2 = StringFromKey("Tortuga_Brothel_118");
				link.l2.go = "BuyPIRATES_light";
			}
			if (sti(pchar.money) >= 150000 && GetCharacterItem(pchar, "jewelry11") >= 30)
			{
				link.l3 = StringFromKey("Tortuga_Brothel_119");
				link.l3.go = "BuyPIRATES_medium";
			}
			if (sti(pchar.money) >= 200000 && GetCharacterItem(pchar, "jewelry11") >= 40)
			{
				link.l4 = StringFromKey("Tortuga_Brothel_120");
				link.l4.go = "BuyPIRATES_hard";
			}
			if (sti(pchar.money) >= 250000 && GetCharacterItem(pchar, "jewelry11") >= 50)
			{
				link.l5 = StringFromKey("Tortuga_Brothel_121");
				link.l5.go = "BuyPIRATES_extra";
			}
			if (sti(pchar.money) >= 500000 && GetCharacterItem(pchar, "jewelry11") >= 100)
			{
				link.l6 = StringFromKey("Tortuga_Brothel_122");
				link.l6.go = "BuyPIRATES_max";
			}
		break;
		case "BuyPIRATES_min":
			TakeNItems(pchar, "jewelry11", -10);
			AddMoneyToCharacter(pchar, -50000);
			pchar.questTemp.Azzy.AddPIRATES_points = 1;
			dialog.text = StringFromKey("Tortuga_Brothel_123");
			link.l1 = StringFromKey("Tortuga_Brothel_124");
			link.l1.go = "BuyPIRATES_choosechr";
		break;
		case "BuyPIRATES_light":
			TakeNItems(pchar, "jewelry11", -20);
			AddMoneyToCharacter(pchar, -100000);
			pchar.questTemp.Azzy.AddPIRATES_points = 2;
			dialog.text = StringFromKey("Tortuga_Brothel_125");
			link.l1 = StringFromKey("Tortuga_Brothel_126");
			link.l1.go = "BuyPIRATES_choosechr";
		break;
		case "BuyPIRATES_medium":
			TakeNItems(pchar, "jewelry11", -30);
			AddMoneyToCharacter(pchar, -150000);
			pchar.questTemp.Azzy.AddPIRATES_points = 3;
			dialog.text = StringFromKey("Tortuga_Brothel_127");
			link.l1 = StringFromKey("Tortuga_Brothel_128");
			link.l1.go = "BuyPIRATES_choosechr";
		break;
		case "BuyPIRATES_hard":
			TakeNItems(pchar, "jewelry11", -40);
			AddMoneyToCharacter(pchar, -200000);
			pchar.questTemp.Azzy.AddPIRATES_points = 4;
			dialog.text = StringFromKey("Tortuga_Brothel_129", pchar);
			link.l1 = "";
			link.l1.go = "BuyPIRATES_choosechr";
		break;
		case "BuyPIRATES_extra":
			TakeNItems(pchar, "jewelry11", -50);
			AddMoneyToCharacter(pchar, -250000);
			pchar.questTemp.Azzy.AddPIRATES_points = 5;
			dialog.text = StringFromKey("Tortuga_Brothel_130", pchar);
			link.l1 = StringFromKey("Tortuga_Brothel_131");
			link.l1.go = "BuyPIRATES_choosechr";
		break;
		case "BuyPIRATES_max":
			TakeNItems(pchar, "jewelry11", -100);
			AddMoneyToCharacter(pchar, -500000);
			pchar.questTemp.Azzy.AddPIRATES_points = 10;
			dialog.text = StringFromKey("Tortuga_Brothel_132");
			link.l1 = "";
			link.l1.go = "BuyPIRATES_choosechr";
		break;
		case "BuyPIRATES_choosechr":
			dialog.text = StringFromKey("Tortuga_Brothel_133");
			link.l1 = StringFromKey("Tortuga_Brothel_134");
			link.l1.go = "BuyPIRATES_choosechr-" + GetMainCharacterIndex();
			for (i = 2; i <= 4; i++)
			{
				iTemp = GetOfficersIndex(pchar, i - 1);
				if (iTemp != -1)
				{
					sld = GetCharacter(iTemp);
					sAttr = "l" + i;
					link.(sAttr) = GetFullName(sld) + ".";
					link.(sAttr).go = "BuyPIRATES_choosechr-" + iTemp;
				}
			}
		break;
		case "BuyPIRATES_ok":
			dialog.text = StringFromKey("Tortuga_Brothel_135");
			link.l1 = "";
			link.l1.go = "BuyPIRATES_launch";
		break;
		case "BuyPIRATES_launch":
			i = rand(6);
			switch (i)
			{
				case 0:        pchar.questTemp.Azzy.AddPIRATES_jewel = "jewelry6";        break;
				case 1:        pchar.questTemp.Azzy.AddPIRATES_jewel = "jewelry7";        break;
				case 2:        pchar.questTemp.Azzy.AddPIRATES_jewel = "jewelry10";    break;
				case 3:        pchar.questTemp.Azzy.AddPIRATES_jewel = "jewelry13";    break;
				case 4:        pchar.questTemp.Azzy.AddPIRATES_jewel = "jewelry14";    break;
				case 5:        pchar.questTemp.Azzy.AddPIRATES_jewel = "jewelry15";    break;
				case 6:        pchar.questTemp.Azzy.AddPIRATES_jewel = "jewelry18";    break;
			}
			iTemp = sti(pchar.questTemp.Azzy.AddPIRATES_chridx);
			sld = GetCharacter(iTemp);
			sld.SystemInfo.AddPIRATES = true;
			sld.questTemp.FreePIRATES = sti(pchar.questTemp.Azzy.AddPIRATES_points);
			DialogExit();
			LaunchCharacter(sld);
			DeleteAttribute(pchar, "questTemp.Azzy.AddPIRATES_points");
			DeleteAttribute(pchar, "questTemp.Azzy.AddPIRATES_chridx");
			if (CheckAttribute(pchar, "questTemp.Azzy.AddPIRATES_first"))
				DeleteAttribute(pchar, "questTemp.Azzy.AddPIRATES_first");
			pchar.questTemp.Azzy.AddPIRATES_again = true;
		break;
		case "BuyPIRATES_again":
			dialog.text = StringFromKey("Tortuga_Brothel_136", pchar);
			link.l1 = StringFromKey("Tortuga_Brothel_137");
			link.l1.go = "BuyPIRATES_jewel";
		break;
		case "BuyPIRATES_jewel":
			switch (pchar.questTemp.Azzy.AddPIRATES_jewel)
			{
				case "jewelry6":    sAttr = StringFromKey("Tortuga_Brothel_138");    break;
				case "jewelry7":    sAttr = StringFromKey("Tortuga_Brothel_139");    break;
				case "jewelry10":    sAttr = StringFromKey("Tortuga_Brothel_140");    break;
				case "jewelry13":    sAttr = StringFromKey("Tortuga_Brothel_141");    break;
				case "jewelry14":    sAttr = StringFromKey("Tortuga_Brothel_142");    break;
				case "jewelry15":    sAttr = StringFromKey("Tortuga_Brothel_143");    break;
				case "jewelry18":    sAttr = StringFromKey("Tortuga_Brothel_144");    break;
			}
			dialog.text = sAttr;
			if (GetCharacterItem(pchar, pchar.questTemp.Azzy.AddPIRATES_jewel) >= 1)
			{
				link.l1 = StringFromKey("Tortuga_Brothel_145");
				link.l1.go = "BuyPIRATES_candles";
			}
			link.l2 = StringFromKey("Tortuga_Brothel_146");
			link.l2.go = "exit";
		break;
		case "BuyPIRATES_candles":
			TakeNItems(pchar, pchar.questTemp.Azzy.AddPIRATES_jewel, -1);

			dialog.text = StringFromKey("Tortuga_Brothel_147", pchar);
			if (sti(pchar.money) >= 50000 && GetCharacterItem(pchar, "mineral3") >= 6 && GetCharacterItem(pchar, "jewelry11") >= 10)
			{
				link.l1 = StringFromKey("Tortuga_Brothel_148", pchar);
				link.l1.go = "BuyPIRATES_choosepoints";
			}
			link.l2 = StringFromKey("Tortuga_Brothel_149");
			link.l2.go = "BuyPIRATES_refusal";
		break;
		case "BuyPIRATES_refusal":
			i = rand(6);
			switch (i)
			{
				case 0:        pchar.questTemp.Azzy.AddPIRATES_jewel = "jewelry6";        break;
				case 1:        pchar.questTemp.Azzy.AddPIRATES_jewel = "jewelry7";        break;
				case 2:        pchar.questTemp.Azzy.AddPIRATES_jewel = "jewelry10";    break;
				case 3:        pchar.questTemp.Azzy.AddPIRATES_jewel = "jewelry13";    break;
				case 4:        pchar.questTemp.Azzy.AddPIRATES_jewel = "jewelry14";    break;
				case 5:        pchar.questTemp.Azzy.AddPIRATES_jewel = "jewelry15";    break;
				case 6:        pchar.questTemp.Azzy.AddPIRATES_jewel = "jewelry18";    break;
			}
			dialog.text = StringFromKey("Tortuga_Brothel_150", pchar);
			link.l1 = StringFromKey("Tortuga_Brothel_151");
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
