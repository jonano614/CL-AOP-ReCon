void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;

	switch (Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = StringFromKey("Usurer_1", pchar);
				link.l1 = StringFromKey("Usurer_2", GetFullName(pchar));
				link.l1.go = "FT_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = StringFromKey("Usurer_3");
				link.l1 = StringFromKey("Usurer_4");
				link.l1.go = "GiveMoney";
				if (!CheckAttribute(pchar, "questTemp.LSC.NarvalDestroyed") || !CheckAttribute(pchar, "questTemp.LSC.CasperDestroyed"))
				{
					link.l2 = StringFromKey("Usurer_5");
					link.l2.go = "parol_choice";
				}
				link.l10 = StringFromKey("Usurer_6", pchar);
				link.l10.go = "Exit";
				//путь чернокнижника
				if (pchar.questTemp.LSC == "toSeekMechanik" && !CheckAttribute(npchar, "quest.loan.WarlocksWayStop"))
				{
					sld = CharacterFromId("Ment_6");
					if (CheckAttribute(sld, "quest.NoSuicideSquad"))
					{
						if (GetCharacterIndex("LSCStBandit3") == -1 || LAi_IsDead(CharacterFromId("LSCStBandit3")))
						{
							link.l3 = StringFromKey("Usurer_7", pchar);
							link.l3.go = "WarlocksWay";
						}
					}
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					link.l8 = StringFromKey("Usurer_8");
					link.l8.go = "SeekCrew";
				}
			}

			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "FT_1":
			dialog.text = StringFromKey("Usurer_9");
			link.l1 = StringFromKey("Usurer_10");
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = StringFromKey("Usurer_11");
			link.l1 = StringFromKey("Usurer_12");
			link.l1.go = "Exit";
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
			dialog.text = StringFromKey("Usurer_13", pchar);
			link.l1 = StringFromKey("Usurer_14");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("Usurer_15");
			link.l1 = StringFromKey("Usurer_16");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("Usurer_17");
			link.l1 = StringFromKey("Usurer_21", LinkRandPhrase(
						StringFromKey("Usurer_18"),
						StringFromKey("Usurer_19"),
						StringFromKey("Usurer_20")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("Usurer_22", npchar);
				link.l1 = StringFromKey("Usurer_26", LinkRandPhrase(
							StringFromKey("Usurer_23"),
							StringFromKey("Usurer_24"),
							StringFromKey("Usurer_25")));
			}
			else
			{
				dialog.text = StringFromKey("Usurer_27", npchar);
				link.l1 = StringFromKey("Usurer_30", RandPhraseSimple(
							StringFromKey("Usurer_28", pchar),
							StringFromKey("Usurer_29")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		// пароли
		case "parol_choice":
			dialog.text = StringFromKey("Usurer_31");
			if (!CheckAttribute(pchar, "questTemp.LSC.NarvalDestroyed"))
			{
				link.l1 = StringFromKey("Usurer_32");
				link.l1.go = "parol_nrv";
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.CasperDestroyed"))
			{
				link.l2 = StringFromKey("Usurer_33");
				link.l2.go = "parol_crp";
			}
		break;
		case "parol_nrv":
			dialog.text = StringFromKey("Usurer_34");
			link.l1 = StringFromKey("Usurer_35");
			link.l1.go = "parol";
			npchar.sParolTemp = pchar.questTemp.LSC.NarvalParol;
			npchar.sClanTemp = StringFromKey("Usurer_36");
		break;

		case "parol_crp":
			dialog.text = StringFromKey("Usurer_37");
			link.l1 = StringFromKey("Usurer_38");
			link.l1.go = "parol";
			npchar.sParolTemp = pchar.questTemp.LSC.CasperParol;
			npchar.sClanTemp = StringFromKey("Usurer_39");
		break;

		case "parol":
			if (!CheckAttribute(npchar, "quest.parolrules"))
			{
				dialog.text = StringFromKey("Usurer_40");
				link.l1 = StringFromKey("Usurer_41");
				link.l1.go = "parol_1";
			}
			else
			{
				dialog.text = StringFromKey("Usurer_42");
				if (sti(pchar.money) >= 50000)
				{
					link.l1 = StringFromKey("Usurer_43");
					link.l1.go = "parol_pay";
				}
				link.l2 = StringFromKey("Usurer_44");
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "parol_1":
			dialog.text = StringFromKey("Usurer_45");
			if (sti(pchar.money) >= 50000)
			{
				link.l1 = StringFromKey("Usurer_46");
				link.l1.go = "parol_pay";
			}
			link.l2 = StringFromKey("Usurer_47");
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
			npchar.quest.parolrules = true;
		break;

		case "parol_pay":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = StringFromKey("Usurer_48", npchar.sClanTemp, npchar.sParolTemp);
			link.l1 = StringFromKey("Usurer_49");
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "parol");
			AddQuestUserData("ISS_MainLine", "sText", npchar.sClanTemp);
			AddQuestUserData("ISS_MainLine", "sParol", npchar.sParolTemp);
			if (pchar.questTemp.LSC.CasperParol == npchar.sParolTemp) pchar.questTemp.LSC.CParol_bye = true;
			else pchar.questTemp.LSC.NParol_bye = true;
		break;

		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Usurer_50"),
						StringFromKey("Usurer_51"),
						StringFromKey("Usurer_52"),
						StringFromKey("Usurer_53"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Usurer_54"),
						StringFromKey("Usurer_55", pchar),
						StringFromKey("Usurer_56"),
						StringFromKey("Usurer_57"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("Usurer_58");
			link.l1 = StringFromKey("Usurer_59");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("Usurer_60");
			link.l1 = StringFromKey("Usurer_61");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("Usurer_62");
			link.l1 = StringFromKey("Usurer_63");
			link.l1.go = "exit";
		break;

		//занять бабла
		case "GiveMoney":
			if (CheckAttribute(npchar, "quest.loan"))
			{
				if (sti(npchar.quest.loan.qtyMoney) >= 1000000)
				{
					dialog.text = StringFromKey("Usurer_64");
					link.l1 = StringFromKey("Usurer_65");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("Usurer_66");
					link.l1 = StringFromKey("Usurer_67");
					link.l1.go = "GiveMoney_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("Usurer_68");
				link.l1 = StringFromKey("Usurer_69");
				link.l1.go = "GiveMoneyKn_1";
				npchar.quest.loan = true;
				npchar.quest.loan.qtyMoney = 0; //кол-во взятых денег
			}
		break;

		case "GiveMoneyKn_1":
			dialog.text = StringFromKey("Usurer_70");
			link.l1 = StringFromKey("Usurer_71");
			link.l1.go = "GiveMoneyKn_2";
		break;
		case "GiveMoneyKn_2":
			dialog.text = StringFromKey("Usurer_72");
			link.l1 = StringFromKey("Usurer_73");
			link.l1.go = "GiveMoneyKn_3";
		break;
		case "GiveMoneyKn_3":
			dialog.text = StringFromKey("Usurer_74", pchar);
			link.l1 = StringFromKey("Usurer_75", pchar);
			link.l1.go = "GiveMoneyKn_4";
		break;
		case "GiveMoneyKn_4":
			dialog.text = StringFromKey("Usurer_76");
			link.l1 = StringFromKey("Usurer_77");
			link.l1.go = "GiveMoney_1";
		break;

		case "GiveMoney_1":
			dialog.text = StringFromKey("Usurer_78");
			Link.l1.edit = 4;
			Link.l1 = "";
			link.l1.go = "GiveMoney_2";
			Link.l2 = StringFromKey("Usurer_79");
			link.l2.go = "GiveMoney_disAgree";
		break;
		case "GiveMoney_2":
			iTemp = sti(dialogEditStrings[4]);
			if ((iTemp + sti(npchar.quest.loan.qtyMoney)) > 1000000)
			{
				dialog.text = StringFromKey("Usurer_80", FindMoneyString(1000000 - sti(npchar.quest.loan.qtyMoney)));
				link.l1 = StringFromKey("Usurer_81");
				link.l1.go = "exit";
			}
			else
			{
				if (iTemp <= 0)
				{
					dialog.text = StringFromKey("Usurer_82", pchar);
					link.l1 = StringFromKey("Usurer_83");
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("Usurer_84");
					link.l1 = StringFromKey("Usurer_85");
					link.l1.go = "GiveMoney_3";
					AddMoneyToCharacter(pchar, iTemp);
					npchar.quest.loan.qtyMoney = sti(npchar.quest.loan.qtyMoney) + iTemp;
				}
			}
		break;
		case "GiveMoney_3":
			dialog.text = StringFromKey("Usurer_86", FindMoneyString(sti(npchar.quest.loan.qtyMoney) * 5));
			link.l1 = StringFromKey("Usurer_87");
			link.l1.go = "GiveMoney_4";
		break;
		case "GiveMoney_4":
			dialog.text = StringFromKey("Usurer_88", pchar);
			link.l1 = StringFromKey("Usurer_89");
			link.l1.go = "exit";
		break;
		case "GiveMoney_disAgree":
			dialog.text = StringFromKey("Usurer_90", pchar);
			link.l1 = StringFromKey("Usurer_91");
			link.l1.go = "exit";
		break;

		//путь чернокнижника
		case "WarlocksWay":
			dialog.text = StringFromKey("Usurer_94", RandPhraseSimple(
						StringFromKey("Usurer_92"),
						StringFromKey("Usurer_93")));
			link.l1 = StringFromKey("Usurer_95");
			link.l1.go = "WarlocksWay_1";
			link.l2 = StringFromKey("Usurer_96", pchar);
			link.l2.go = "exit";
		break;
		case "WarlocksWay_1":
			dialog.text = StringFromKey("Usurer_97", pchar);
			link.l1 = StringFromKey("Usurer_98");
			link.l1.go = "WarlocksWay_Explain";
			link.l2 = StringFromKey("Usurer_99", pchar);
			link.l2.go = "WarlocksWay_Agree";
			link.l3 = StringFromKey("Usurer_100");
			link.l3.go = "exit";
			if (!CheckAttribute(npchar, "quest.loan.qtyMoney")) npchar.quest.loan.qtyMoney = 0;
		break;
		case "WarlocksWay_Explain":
			dialog.text = StringFromKey("Usurer_101");
			link.l1 = StringFromKey("Usurer_102");
			link.l1.go = "WarlocksWay_Explain_2";
		break;
		case "WarlocksWay_Explain_2":
			dialog.text = StringFromKey("Usurer_103", pchar);
			link.l1 = StringFromKey("Usurer_104");
			link.l1.go = "WarlocksWay_Explain_3";
			link.l2 = StringFromKey("Usurer_105");
			link.l2.go = "WarlocksWay_Explain_6";
		break;
		case "WarlocksWay_Explain_3":
			dialog.text = StringFromKey("Usurer_106");
			link.l1 = StringFromKey("Usurer_107");
			link.l1.go = "WarlocksWay_Explain_5";
			link.l2 = StringFromKey("Usurer_108");
			link.l2.go = "WarlocksWay_Explain_4";
		break;
		case "WarlocksWay_Explain_4":
			dialog.text = StringFromKey("Usurer_109", pchar);
			link.l1 = StringFromKey("Usurer_110");
			link.l1.go = "WarlocksWay_Explain_5";
		break;
		case "WarlocksWay_Explain_5":
			dialog.text = StringFromKey("Usurer_111");
			link.l1 = StringFromKey("Usurer_112");
			link.l1.go = "WarlocksWay_Explain_6";
		break;
		case "WarlocksWay_Explain_6":
			dialog.text = StringFromKey("Usurer_113", pchar);
			link.l1 = StringFromKey("Usurer_114");
			link.l1.go = "WarlocksWay_FinalWarning";
		break;
		case "WarlocksWay_FinalWarning":
			dialog.text = StringFromKey("Usurer_115");
			link.l1 = StringFromKey("Usurer_116");
			link.l1.go = "WarlocksWay_Agree";
			link.l2 = StringFromKey("Usurer_117");
			link.l2.go = "exit";
		break;
		case "WarlocksWay_Agree": //соглашаемся на путь чернокнижника
			dialog.text = StringFromKey("Usurer_118");
			link.l1 = StringFromKey("Usurer_119");
			link.l1.go = "WarlocksWay_Agree_1";
		break;

		case "WarlocksWay_Agree_1":
			if (sti(npchar.quest.loan.qtyMoney) > 0)
			{
				dialog.text = StringFromKey("Usurer_120", FindMoneyString(1000000 - sti(npchar.quest.loan.qtyMoney)));
			}
			else if (sti(npchar.quest.loan.qtyMoney) == 1000000) //уже набрали деньжат
			{
				dialog.text = StringFromKey("Usurer_121");
			}
			else
			{
				dialog.text = StringFromKey("Usurer_122");
			}
			link.l1 = StringFromKey("Usurer_123", pchar);
			link.l1.go = "WarlocksWay_Confirm";
		break;
		case "WarlocksWay_Confirm":
			dialog.text = StringFromKey("Usurer_124");
			link.l1 = StringFromKey("Usurer_125");
			link.l1.go = "exit";

			if (sti(npchar.quest.loan.qtyMoney) < 1000000)
			{
				AddMoneyToCharacter(pchar, 1000000 - sti(npchar.quest.loan.qtyMoney));
				npchar.quest.loan.qtyMoney = 1000000;
			}

			int day = rand(2) + 1; // Рандом от 1 до 3 дней
			npchar.quest.loan.WarlocksWayStop = true;
			pchar.quest.LSC_WarlocksWay.win_condition.l1 = "Timer";
			pchar.quest.LSC_WarlocksWay.win_condition.l1.date.hour = GetHour();
			pchar.quest.LSC_WarlocksWay.win_condition.l1.date.day = GetAddingDataDay(0, 0, day);
			pchar.quest.LSC_WarlocksWay.win_condition.l1.date.month = GetAddingDataMonth(0, 0, day);
			pchar.quest.LSC_WarlocksWay.win_condition.l1.date.year = GetAddingDataYear(0, 0, day);
			pchar.quest.LSC_WarlocksWay.function = "LSC_WarlocksWay";
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");
		break;
	}
}
