// Секретарь Моргана и актер для сложных диалогов с действиями.
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	sld = characterFromID("Henry Morgan");

	switch (Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			if (sld.location == pchar.location)
			{
				dialog.text = StringFromKey("OliverGreen_1");
				link.l1 = StringFromKey("OliverGreen_2");
			}
			else
			{
				if (pchar.questTemp.piratesLine == "Panama_inEngland" || pchar.questTemp.piratesLine == "Panama_backToShip")
				{
					dialog.text = StringFromKey("OliverGreen_3");
					link.l1 = StringFromKey("OliverGreen_4");
					Achievment_Set(ACH_Ya_uedu_zhit_v_London);
				}
				else
				{
					dialog.text = StringFromKey("OliverGreen_5");
					link.l1 = StringFromKey("OliverGreen_6");
				}
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			if (npchar.quest.meeting == "0")
			{
				dialog.text = StringFromKey("OliverGreen_7", GetFullName(npchar));
				link.l1 = StringFromKey("OliverGreen_8", GetFullName(pchar));
				link.l1.go = "First time";
				npchar.quest.meeting = "1";
			}
			//============>>>>>>>>> перехват квестовых диалогов
			if (pchar.questTemp.State == "WormEnglPlans_toMorgan")  // HolLine_3, переадресовка в Антигуа.
			{
				link.l1 = StringFromKey("OliverGreen_9");
				link.l1.go = "Step_H3_1";
			}
			if (pchar.questTemp.State == "Fr8ThreeCorsairs_toSeek")  // FraLine_8, переадресовка в Антигуа.
			{
				link.l1 = StringFromKey("OliverGreen_10", pchar);
				link.l1.go = "Step_F8_1";
			}
			// квест Аскольда. Пасхалка на получение индейских предметов.
			if (pchar.questTemp.Ascold == "SeekThreeObject" && !CheckAttribute(pchar, "questTemp.Ascold.Oliver"))
			{
				link.l2 = StringFromKey("OliverGreen_11");
				link.l2.go = "Step_As_1";
			}
			if (pchar.questTemp.Ascold == "SeekThreeObject" && CheckAttribute(pchar, "questTemp.Ascold.Oliver"))
			{
				link.l2 = StringFromKey("OliverGreen_12", pchar);
				link.l2.go = "Step_As_7";
			}
			if (pchar.questTemp.Azzy == "DestrContract" || pchar.questTemp.Azzy == "2DestrContract")
			{
				if (!CheckAttribute(pchar, "questTemp.Azzy.Oliver"))
				{
					link.l2 = StringFromKey("OliverGreen_13");
					link.l2.go = "Step_As_9";
				}
			}
			// пришли за расшифровкой к Оливеру ГПК
			if (pchar.questTemp.LSC == "DecryptionWithOliverHelpLSC" && !CheckAttribute(npchar, "decryptLSC"))
			{
				link.l1 = StringFromKey("OliverGreen_14");
				link.l1.go = "OliverHelpLSC_1";
			}
			// не хватило денег ГПК
			if (pchar.questTemp.LSC == "DecryptionWithOliverHelpLSC" && CheckAttribute(npchar, "decryptLSC"))
			{
				dialog.text = StringFromKey("OliverGreen_15");
				if (sti(pchar.money) >= 150000)
				{
					link.l1 = StringFromKey("OliverGreen_16", pchar);
					link.l1.go = "OliverHelpLSC_3";
				}
				else
				{
					link.l1 = StringFromKey("OliverGreen_17");
					link.l1.go = "exit";
				}
			}
			// закончил расшифровку СЖ ГПК
			if (pchar.questTemp.LSC == "DecryptedLogLSC" && pchar.questTemp.LSC.decryptorId == npchar.id)
			{
				dialog.text = StringFromKey("OliverGreen_18");
				link.l1 = StringFromKey("OliverGreen_19");
				link.l1.go = "DecryptedLogLSC_1";
			}
		//============>>>>>>>>> перехват квестовых диалогов
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//********************* Голландская линейка *********************
		case "Step_H3_1":
			dialog.text = StringFromKey("OliverGreen_20", pchar);
			link.l1 = StringFromKey("OliverGreen_21", GetFullName(pchar));
			link.l1.go = "Step_H3_2";
		break;
		case "Step_H3_2":
			dialog.text = StringFromKey("OliverGreen_22", pchar);
			link.l1 = StringFromKey("OliverGreen_23");
			link.l1.go = "Step_H3_3";
		break;
		case "Step_H3_3":
			dialog.text = StringFromKey("OliverGreen_24", pchar, GetAddress_Form(NPChar));
			link.l1 = StringFromKey("OliverGreen_25");
			link.l1.go = "exit";
			pchar.questTemp.State = "WormEnglPlans_toMorganAntigua";
			AddQuestRecord("Hol_Line_3_WormEnglishPlans", "3");
			AddQuestUserData("Hol_Line_3_WormEnglishPlans", "sSex", GetSexPhrase("", "а"));
		break;
		//********************* Французская линейка *********************
		case "Step_F8_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("OliverGreen_26", pchar, GetAddress_Form(NPChar)),
						StringFromKey("OliverGreen_27"),
						StringFromKey("OliverGreen_28"),
						StringFromKey("OliverGreen_29"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("OliverGreen_30", GetFullName(pchar)),
						StringFromKey("OliverGreen_31"),
						StringFromKey("OliverGreen_32"),
						StringFromKey("OliverGreen_33"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F8_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_F8_2":
			dialog.text = StringFromKey("OliverGreen_34");
			link.l1 = StringFromKey("OliverGreen_35");
			link.l1.go = "Step_F8_3";
		break;
		case "Step_F8_3":
			dialog.text = StringFromKey("OliverGreen_36", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("OliverGreen_37");
			link.l1.go = "Step_F8_4";
		break;
		case "Step_F8_4":
			dialog.text = StringFromKey("OliverGreen_38", UpperFirst(GetAddress_Form(NPChar)));
			link.l1 = StringFromKey("OliverGreen_39");
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
		//********************* Квест Асокльда *********************
		case "Step_As_1":
			dialog.text = StringFromKey("OliverGreen_40");
			link.l1 = StringFromKey("OliverGreen_41", pchar);
			link.l1.go = "Step_As_2";
		break;
		case "Step_As_2":
			dialog.text = StringFromKey("OliverGreen_42");
			link.l1 = StringFromKey("OliverGreen_43");
			link.l1.go = "Step_As_3";
		break;
		case "Step_As_3":
			dialog.text = StringFromKey("OliverGreen_44");
			link.l1 = StringFromKey("OliverGreen_45", pchar);
			link.l1.go = "Step_As_4";
		break;
		case "Step_As_4":
			dialog.text = StringFromKey("OliverGreen_46");
			link.l1 = StringFromKey("OliverGreen_47");
			link.l1.go = "Step_As_5";
		break;
		case "Step_As_5":
			dialog.text = StringFromKey("OliverGreen_48");
			link.l1 = StringFromKey("OliverGreen_49");
			link.l1.go = "Step_As_6";
		break;
		case "Step_As_6":
			dialog.text = StringFromKey("OliverGreen_50", pchar);
			link.l1 = StringFromKey("OliverGreen_51");
			link.l1.go = "Step_As_7";
			pchar.questTemp.Ascold.Oliver = 1;
		break;
		case "Step_As_7":
			dialog.text = StringFromKey("OliverGreen_52");
			link.l1 = StringFromKey("OliverGreen_55", RandPhraseSimple(
						StringFromKey("OliverGreen_53"),
						StringFromKey("OliverGreen_54")));
			link.l1.go = "exit";
			if (sti(pchar.money) >= 1000000)
			{
				link.l2 = StringFromKey("OliverGreen_56");
				link.l2.go = "Step_As_8";
			}
			else
			{
				link.l2 = StringFromKey("OliverGreen_57", pchar);
				link.l2.go = "exit";
			}
		break;
		case "Step_As_8":
			dialog.text = StringFromKey("OliverGreen_58", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("OliverGreen_59");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			DeleteAttribute(pchar, "questTemp.Ascold.Oliver");
			pchar.questTemp.Ascold = "SoughtThreeObject";
			GiveItem2Character(pchar, "indian19");
			GiveItem2Character(pchar, "indian20");
			GiveItem2Character(pchar, "indian21");
			RemoveLandQuestmark_Main(npchar, "Ascold");
		break;
		case "Step_As_9":
			dialog.text = StringFromKey("OliverGreen_60");
			link.l1 = StringFromKey("OliverGreen_63", RandPhraseSimple(
						StringFromKey("OliverGreen_61"),
						StringFromKey("OliverGreen_62")));
			link.l1.go = "exit";
			if (sti(pchar.money) >= 5000000)
			{
				link.l2 = StringFromKey("OliverGreen_64");
				link.l2.go = "Step_As_10";
			}
			else
			{
				link.l2 = StringFromKey("OliverGreen_65");
				link.l2.go = "exit";
			}
		break;
		case "Step_As_10":
			dialog.text = StringFromKey("OliverGreen_66", GetFullName(pchar));
			link.l1 = StringFromKey("OliverGreen_67");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000000);
			GiveItem2Character(pchar, "sculMa1");
			GiveItem2Character(pchar, "sculMa2");
			GiveItem2Character(pchar, "sculMa3");
			GiveItem2Character(pchar, "indian22");
			pchar.questTemp.Azzy.Oliver = 1;
		break;

		case "PL_Q8_over":
			dialog.text = StringFromKey("OliverGreen_68", GetFullName(pchar));
			link.l1 = StringFromKey("OliverGreen_69");
			link.l1.go = "PL_Q8_over_1";
		break;
		case "PL_Q8_over_1":
			dialog.text = StringFromKey("OliverGreen_70");
			link.l1 = StringFromKey("OliverGreen_71");
			link.l1.go = "PL_Q8_over_2";
		break;
		case "PL_Q8_over_2":
			dialog.text = StringFromKey("OliverGreen_72", pchar);
			link.l1 = StringFromKey("OliverGreen_73");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		// пришли за расшифровкой к Оливеру
		case "OliverHelpLSC_1":
			dialog.text = StringFromKey("OliverGreen_74");
			link.l1 = StringFromKey("OliverGreen_75");
			link.l1.go = "OliverHelpLSC_2";
			npchar.decryptLSC = 1;
		break;
		case "OliverHelpLSC_2":
			dialog.text = StringFromKey("OliverGreen_76");
			link.l1 = StringFromKey("OliverGreen_77");
			link.l1.go = "exit";
			if (sti(pchar.money) >= 150000)
			{
				link.l2 = StringFromKey("OliverGreen_78");
				link.l2.go = "OliverHelpLSC_3";
			}
		break;
		case "OliverHelpLSC_3":
			dialog.text = StringFromKey("OliverGreen_79");
			link.l1 = StringFromKey("OliverGreen_80");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -150000);
			PlaySound("Took_item");
			RemoveItems(pchar, "LogbookLSC", 1);
			DeleteAttribute(npchar, "decryptLSC");
			pchar.questTemp.LSC = "LogToDecryptLSC";
			pchar.questTemp.LSC.decryptorId = npchar.id;
			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
		break;

		// закончил расшифровку СЖ ГПК
		case "DecryptedLogLSC_1":
			dialog.text = StringFromKey("OliverGreen_81");
			link.l1 = StringFromKey("OliverGreen_82");
			link.l1.go = "DecryptedLogLSC_2";
		break;
		case "DecryptedLogLSC_2":
			dialog.text = StringFromKey("OliverGreen_83");
			link.l1 = StringFromKey("OliverGreen_84");
			link.l1.go = "DecryptedLogLSC_3";
		break;
		case "DecryptedLogLSC_3":
			dialog.text = StringFromKey("OliverGreen_85", GetFullName(pchar));
			link.l1 = StringFromKey("OliverGreen_86");
			link.l1.go = "DecryptedLogLSC_4";
		break;
		case "DecryptedLogLSC_4":
			dialog.text = StringFromKey("OliverGreen_87");
			link.l1 = StringFromKey("OliverGreen_88", pchar);
			link.l1.go = "DecryptedLogLSC_5";
		break;
		case "DecryptedLogLSC_5":
			dialog.text = StringFromKey("OliverGreen_89");
			link.l1 = StringFromKey("OliverGreen_90", pchar);
			link.l1.go = "DecryptedLogLSC_6";
		break;
		case "DecryptedLogLSC_6":
			dialog.text = StringFromKey("OliverGreen_91", GetFullName(pchar));
			link.l1 = StringFromKey("OliverGreen_92", pchar);
			link.l1.go = "DecryptedLogLSC_8";
			//			if ((GetCharacterSPECIAL(pchar, SPECIAL_P) + GetCharacterSPECIAL(pchar, SPECIAL_I)) >= 8)
			if (PlayerRPGCheck_SPECIAL_Sum(SPECIAL_P + "," + SPECIAL_I, 8))
			{
				link.l2 = StringFromKey("OliverGreen_93");
				link.l2.go = "DecryptedLogLSC_7";
			}
		break;
		case "DecryptedLogLSC_7":
			dialog.text = StringFromKey("OliverGreen_94");
			link.l1 = StringFromKey("OliverGreen_95");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "BackToCemeteryLSC";
			sld = ItemsFromID("LogbookLSC");
			sld.read = true;
			sld.blockRead = true;
			sld.describe = "itmdescr_LogbookLSCDecryptedReading";
			AddItemLog(pchar, "LogbookLSC", "1", StringFromKey("InfoMessages_135", GetItemName("LogbookLSC")), "Important_item");
			AddQuestRecord("ISS_PoorsMurder", "27");
			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
			AddLandQuestMark_Main(characterFromId("Villemstad_Cemeteryman"), "ISS_PoorsMurder");
		break;
		case "DecryptedLogLSC_8":
			dialog.text = StringFromKey("OliverGreen_96", GetFullName(pchar));
			link.l1 = StringFromKey("OliverGreen_97", pchar);
			link.l1.go = "DecryptedLogLSC_9";
		break;
		case "DecryptedLogLSC_9":
			dialog.text = StringFromKey("OliverGreen_98");
			link.l1 = StringFromKey("OliverGreen_99");
			link.l1.go = "DecryptedLogLSC_10";
		break;
		case "DecryptedLogLSC_10":
			dialog.text = StringFromKey("OliverGreen_100");
			link.l1 = StringFromKey("OliverGreen_101");
			link.l1.go = "DecryptedLogLSC_11";
		break;
		case "DecryptedLogLSC_11":
			dialog.text = StringFromKey("OliverGreen_102", GetFullName(pchar));
			link.l1 = StringFromKey("OliverGreen_103");
			link.l1.go = "exit";
			AddItemLog(pchar, "bequestLSC", "1", StringFromKey("InfoMessages_135", GetItemName("bequestLSC")), "Important_item");
			ReOpenQuestHeader("PreparationForISS");
			AddQuestRecord("PreparationForISS", "1");

			AddQuestRecord("ISS_PoorsMurder", "28");
			AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("ISS_PoorsMurder");
			pchar.questTemp.LSC = "BequestToProvidenceLSC";
			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
			AddLandQuestMark_Main(characterFromId("Providencia_Mayor"), "PreparationForISS");
		break;
	}
}


