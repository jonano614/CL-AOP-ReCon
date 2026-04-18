#define DIPLOMAT_SUM 80000

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iSumm = 0;
	string s1;

	if (!CheckAttribute(npchar, "PatentPrice"))
	{
		npchar.PatentPrice = (8000 + rand(6) * 1000);
	}
	int i;
	string attrLoc;
	ref sld;

	attrLoc = Dialog.CurrentNode;

	if (HasSubStr(attrLoc, "SetNationPatent_"))
	{
		i = findsubstr(attrLoc, "_", 0);
		NPChar.nation = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		Dialog.CurrentNode = "patent_2";
	}

	if (HasSubStr(attrLoc, "SetNationLicence_"))
	{
		i = findsubstr(attrLoc, "_", 0);
		NPChar.LicenceNation = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		Dialog.CurrentNode = "NationLicenceType";
	}

	if (HasSubStr(attrLoc, "NationLicenceType_"))
	{
		i = findsubstr(attrLoc, "_", 0);
		NPChar.LicenceType = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		Dialog.CurrentNode = "NationLicenceType2";
	}

	if (HasSubStr(attrLoc, "RelationTo_"))
	{
		i = findsubstr(attrLoc, "_", 0);
		npchar.quest.relation = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
			Dialog.CurrentNode = "RelationYet";
		}
		else
		{
			Dialog.CurrentNode = "RelationAny_Done";
			npchar.quest.relation.summ = CalculateRelationSum(sti(npchar.quest.relation));
		}
	}

	if (HasSubStr(attrLoc, "CityPay_"))
	{
		i = findsubstr(attrLoc, "_", 0);
		NPChar.quest.CityIdx = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		Dialog.CurrentNode = "CityInfo";
	}

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = StringFromKey("Diplomat_dialog_1");
			link.l1 = StringFromKey("Diplomat_dialog_2");
			link.l1.go = "relation";

			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("Diplomat_dialog_6", LinkRandPhrase(
								StringFromKey("Diplomat_dialog_3"),
								StringFromKey("Diplomat_dialog_4"),
								StringFromKey("Diplomat_dialog_5", pchar))),
						StringFromKey("Diplomat_dialog_10", LinkRandPhrase(
								StringFromKey("Diplomat_dialog_7", pchar),
								StringFromKey("Diplomat_dialog_8", pchar),
								StringFromKey("Diplomat_dialog_9", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Diplomat_dialog_13", RandPhraseSimple(
								StringFromKey("Diplomat_dialog_11"),
								StringFromKey("Diplomat_dialog_12"))),
						StringFromKey("Diplomat_dialog_16", RandPhraseSimple(
								StringFromKey("Diplomat_dialog_14"),
								StringFromKey("Diplomat_dialog_15"))));
				link.l1.go = "exit";
				break;
			}

			// evganat - энциклопедия
			if (!ENCYCLOPEDIA_DISABLED && !CheckAttribute(npchar, "encyclopedia.full"))
			{
				link.l2 = StringFromKey("Diplomat_dialog_17");
				link.l2.go = "Encyclopedia_1";
			}

			//линейка ГПК, поиски торгашей -->
			if (pchar.questTemp.LSC == "toLicencer")
			{
				link.l3 = StringFromKey("Diplomat_dialog_18");
				link.l3.go = "SeekHVIC";
			}
			if (pchar.questTemp.LSC == "toLicencer_2")
			{
				link.l3 = StringFromKey("Diplomat_dialog_19");
				link.l3.go = "SeekHVIC_3";
			}
			//<-- линейка ГПК, поиски торгашей
			// ГПК расшифровка документов
			if (pchar.questTemp.LSC == "LogToDiplomatDecryptLSC")
			{
				link.l3 = StringFromKey("Diplomat_dialog_20");
				link.l3.go = "LogToDecrypt_1";
			}
			// генератор  "Найденные документы"
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAgent"))
			{
				link.l4 = StringFromKey("Diplomat_dialog_21");
				link.l4.go = "D_ShipLetters_1";
				pchar.questTemp.different.GiveShipLetters.speakAgent = true;
			}

			link.l9 = StringFromKey("Diplomat_dialog_22");
			link.l9.go = "exit";

			if (npchar.quest.meeting == "0")
			{
				dialog.text = StringFromKey("Diplomat_dialog_23");
				link.l1 = StringFromKey("Diplomat_dialog_24");
				link.l1.go = "relation";
				// evganat - энциклопедия
				if (!ENCYCLOPEDIA_DISABLED)
				{
					link.l2 = StringFromKey("Diplomat_dialog_25");
					link.l2.go = "Encyclopedia_1";
				}
				link.l9 = StringFromKey("Diplomat_dialog_26");
				link.l9.go = "exit";
				npchar.quest.meeting = "1";
			}

			NextDiag.TempNode = "First time";
		break;

		//*************************** Генератор - "Найденные судовые документы" **************		
		case "D_ShipLetters_1":
			dialog.text = StringFromKey("Diplomat_dialog_27");
			s1 = StringFromKey("Diplomat_dialog_28");
			s1 = StringFromKey("Diplomat_dialog_29", s1);
			link.l1 = s1;
			link.l1.go = "D_ShipLetters_2";
		break;
		case "D_ShipLetters_2":
			s1 = StringFromKey("Diplomat_dialog_30", pchar);
			s1 = StringFromKey("Diplomat_dialog_31", s1, sti(pchar.questTemp.different.GiveShipLetters.price5));
			dialog.text = s1;
			link.l1 = StringFromKey("Diplomat_dialog_32", pchar);
			link.l1.go = "D_ShipLetters_3";
			link.l2 = StringFromKey("Diplomat_dialog_33");
			link.l2.go = "exit";
		break;
		case "D_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook");
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5));
			ChangeCharacterReputation(pchar, -1);
			OfficersReaction("bad");
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "9");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "relation":
			dialog.text = StringFromKey("Diplomat_dialog_34");
			if (GetCharacterReputation_WithNation(pchar, ENGLAND) < 0)
			{
				link.l3 = StringFromKey("Diplomat_dialog_35");
				link.l3.go = "RelationTo_0";
			}

			if (GetCharacterReputation_WithNation(pchar, FRANCE) < 0)
			{
				link.l1 = StringFromKey("Diplomat_dialog_36");
				link.l1.go = "RelationTo_1";
			}
			if (GetCharacterReputation_WithNation(pchar, SPAIN) < 0)
			{
				link.l2 = StringFromKey("Diplomat_dialog_37");
				link.l2.go = "RelationTo_2";
			}

			if (GetCharacterReputation_WithNation(pchar, HOLLAND) < 0)
			{
				link.l4 = StringFromKey("Diplomat_dialog_38");
				link.l4.go = "RelationTo_3";
			}
			if (GetPlayerContrabandRelation() <= 5)
			{
				Link.l5 = StringFromKey("Diplomat_dialog_39");
				Link.l5.go = "Contraband";
			}
			Link.l8 = StringFromKey("Diplomat_dialog_40");
			Link.l8.go = "patent_0";

			Link.l9 = StringFromKey("Diplomat_dialog_41");
			Link.l9.go = "Licence";

			if (isHeroOwnCity(true))
			{
				Link.l10 = StringFromKey("Diplomat_dialog_42");
				Link.l10.go = "City_Buy";
			}

			link.l99 = StringFromKey("Diplomat_dialog_43");
			link.l99.go = "exit";
		break;

		case "Licence":
			dialog.text = StringFromKey("Diplomat_dialog_44");
			link.l1 = StringFromKey("Diplomat_dialog_45");
			link.l1.go = "SetNationLicence_0";
			link.l2 = StringFromKey("Diplomat_dialog_46");
			link.l2.go = "SetNationLicence_1";
			link.l3 = StringFromKey("Diplomat_dialog_47");
			link.l3.go = "SetNationLicence_2";
			link.l4 = StringFromKey("Diplomat_dialog_48");
			link.l4.go = "SetNationLicence_3";
			link.l9 = StringFromKey("Diplomat_dialog_49");
			link.l9.go = "exit";
		break;

		case "NationLicenceType":
			dialog.text = StringFromKey("Diplomat_dialog_50");
			link.l1 = StringFromKey("Diplomat_dialog_51");
			link.l1.go = "NationLicenceType_30";
			link.l2 = StringFromKey("Diplomat_dialog_52");
			link.l2.go = "NationLicenceType_60";
			link.l3 = StringFromKey("Diplomat_dialog_53");
			link.l3.go = "NationLicenceType_90";
			link.l9 = StringFromKey("Diplomat_dialog_54", pchar);
			link.l9.go = "exit";
		break;

		case "NationLicenceType2":
			iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE * 500);
			dialog.text = StringFromKey("Diplomat_dialog_55", XI_ConvertString(Nations[sti(npchar.LicenceNation)].Name + "Gen"), sti(npchar.LicenceType), FindMoneyString(iSumm));
			link.l1 = StringFromKey("Diplomat_dialog_56");
			if (makeint(Pchar.money) < iSumm)
			{
				Link.l1.go = "No_money";
			}
			else
			{
				link.l1.go = "NationLicenceType3";
			}
			link.l9 = StringFromKey("Diplomat_dialog_57", pchar);
			link.l9.go = "exit";
		break;

		case "NationLicenceType3":
			iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE * 500);
			dialog.text = StringFromKey("Diplomat_dialog_58");
			link.l9 = StringFromKey("Diplomat_dialog_59");
			link.l9.go = "exit";
			AddMoneyToCharacter(pchar, -iSumm);
			GiveNationLicence(sti(npchar.LicenceNation), sti(npchar.LicenceType));
		break;

		case "No_money":
			dialog.text = StringFromKey("Diplomat_dialog_60");
			link.l1 = StringFromKey("Diplomat_dialog_61");
			link.l1.go = "exit";
		break;

		case "patent_0":
			dialog.text = StringFromKey("Diplomat_dialog_62");
			link.l1 = StringFromKey("Diplomat_dialog_63", GetAddress_FormToNPC(NPChar));
			link.l1.go = "patent_1";
			link.l2 = StringFromKey("Diplomat_dialog_64", GetAddress_FormToNPC(NPChar));
			link.l2.go = "exit";
		break;

		case "patent_1":
			dialog.text = StringFromKey("Diplomat_dialog_65");
			link.l1 = StringFromKey("Diplomat_dialog_66");
			if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) > rand(11) || bBettaTestMode)
			{
				link.l1.go = "patent_2_give";
			}
			else
			{
				link.l1.go = "patent_2_none";
			}
			link.l2 = StringFromKey("Diplomat_dialog_67", GetAddress_FormToNPC(NPChar));
			link.l2.go = "exit";
		break;

		case "patent_2_none":
			dialog.text = StringFromKey("Diplomat_dialog_68");
			link.l1 = StringFromKey("Diplomat_dialog_69", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit";
		break;

		case "patent_2_give":
			dialog.text = StringFromKey("Diplomat_dialog_70");
			if (GetPatentNation() != ENGLAND)
			{
				link.l1 = StringFromKey("Diplomat_dialog_71");
				link.l1.go = "SetNationPatent_0";
			}
			if (GetPatentNation() != FRANCE)
			{
				link.l2 = StringFromKey("Diplomat_dialog_72");
				link.l2.go = "SetNationPatent_1";
			}
			if (GetPatentNation() != SPAIN)
			{
				link.l3 = StringFromKey("Diplomat_dialog_73");
				link.l3.go = "SetNationPatent_2";
			}
			if (GetPatentNation() != HOLLAND)
			{
				link.l4 = StringFromKey("Diplomat_dialog_74");
				link.l4.go = "SetNationPatent_3";
			}
			link.l9 = StringFromKey("Diplomat_dialog_75");
			link.l9.go = "exit";
		break;

		case "patent_2":
		//pchar.PatentPrice = 8000 + (sti(NPChar.PatentPrice) * sti(pchar.rank));
			pchar.PatentPrice = 350000 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) * 100 + (5000 + rand(1000)) * sti(pchar.rank) * MOD_SKILL_ENEMY_RATE;
			switch (sti(NPChar.nation))
			{
				case PIRATE :
					dialog.text = StringFromKey("Diplomat_dialog_76");
					link.l1 = StringFromKey("Diplomat_dialog_77", pchar);
				break;
				case HOLLAND :
					dialog.text = StringFromKey("Diplomat_dialog_78", FindMoneyString(sti(pchar.PatentPrice)));
					link.l1 = StringFromKey("Diplomat_dialog_79", pchar);
				break;
				case FRANCE :
					dialog.text = StringFromKey("Diplomat_dialog_80", FindMoneyString(sti(pchar.PatentPrice)));
					link.l1 = StringFromKey("Diplomat_dialog_81");
				break;
				case SPAIN :
					dialog.text = StringFromKey("Diplomat_dialog_82", FindMoneyString(sti(pchar.PatentPrice)));
					link.l1 = StringFromKey("Diplomat_dialog_83");
				break;
				case ENGLAND :
					dialog.text = StringFromKey("Diplomat_dialog_84", FindMoneyString(sti(pchar.PatentPrice)));
					link.l1 = StringFromKey("Diplomat_dialog_85", pchar);
				break;
			}

			if (makeint(Pchar.money) < makeint(pchar.PatentPrice))
			{
				Link.l1.go = "No_money";
			}
			else
			{
				link.l1.go = "patent_3";
			}

			link.l2 = StringFromKey("Diplomat_dialog_86");
			link.l2.go = "exit";
		break;

		case "patent_3":
			pchar.PatentNation = NationShortName(sti(NPChar.nation));
			dialog.text = StringFromKey("Diplomat_dialog_87");
			link.l1 = StringFromKey("Diplomat_dialog_88", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit";
			AddDialogExitQuest("any_patent_take");
		break;

		case "Contraband":
			Pchar.questTemp.Relations.sum = makeint(0.3 * stf(Pchar.rank) / stf(Pchar.reputation) * DIPLOMAT_SUM);
			dialog.Text = StringFromKey("Diplomat_dialog_89", FindMoneyString(sti(Pchar.questTemp.Relations.sum)));
			Link.l1 = StringFromKey("Diplomat_dialog_90", pchar);
			if (makeint(Pchar.money) < makeint(Pchar.questTemp.Relations.sum))
			{
				Link.l1.go = "No_money";
			}
			else
			{
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = StringFromKey("Diplomat_dialog_91", pchar);
			Link.l2.go = "exit";
		break;

		case "Contraband_Agreed":
			dialog.Text = StringFromKey("Diplomat_dialog_92");
			Link.l99 = StringFromKey("Diplomat_dialog_93");
			Link.l99.go = "exit";
			ChangeContrabandRelation(pchar, 25);
			AddMoneyToCharacter(pchar, -sti(Pchar.questTemp.Relations.sum));
		break;
		// boal <--
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			dialog.text = StringFromKey("Diplomat_dialog_94", XI_ConvertString(Nations[sti(npchar.quest.relation)].Name + "Ins"), FindMoneyString(iSumm));
			if (sti(pchar.money) >= iSumm)
			{
				link.l1 = StringFromKey("Diplomat_dialog_95");
				link.l1.go = "relation3";
			}
			link.l2 = StringFromKey("Diplomat_dialog_96");
			link.l2.go = "exit";
		break;

		case "relation3":
			dialog.text = StringFromKey("Diplomat_dialog_97");
			link.l1 = StringFromKey("Diplomat_dialog_98");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
			Pchar.GenQuest.(attrLoc) = true;
		break;

		case "RelationYet":
			dialog.Text = StringFromKey("Diplomat_dialog_99");
			Link.l99 = StringFromKey("Diplomat_dialog_100");
			Link.l99.go = "exit";
		break;

		case "City_Buy":
			dialog.Text = StringFromKey("Diplomat_dialog_101");
			for (i = 0; i < MAX_COLONIES; i++)
			{
				if (sti(colonies[i].HeroOwn) == true && sti(colonies[i].isBought) == false)
				{
					sld = GetFortCommander(colonies[i].id);
					attrLoc = "l" + i;
					Link.(attrLoc) = GetCityName(colonies[i].id) + " - " + XI_ConvertString(GetNationNameByType(sti(sld.Default.nation)));
					Link.(attrLoc).go = "CityPay_" + i;
				}
			}
			Link.l99 = StringFromKey("Diplomat_dialog_102");
			Link.l99.go = "exit";
		break;

		case "CityInfo":
			i = sti(NPChar.quest.CityIdx);
			sld = GetFortCommander(colonies[i].id);
			iSumm = TWN_CityCost(colonies[i].id);
			dialog.Text = StringFromKey("Diplomat_dialog_103", GetCityName(colonies[i].id), XI_ConvertString(GetNationNameByType(sti(sld.Default.nation)) + "Gen"), FindMoneyString(iSumm));
			if (sti(pchar.money) >= iSumm)
			{
				Link.l1 = StringFromKey("Diplomat_dialog_104");
				Link.l1.go = "City_Buy_End";
			}
			Link.l99 = StringFromKey("Diplomat_dialog_105");
			Link.l99.go = "exit";
		break;

		case "City_Buy_End":
			i = sti(NPChar.quest.CityIdx);
			TWN_RealeseForMoney(colonies[i].id, true);
			dialog.Text = StringFromKey("Diplomat_dialog_106", GetCityName(colonies[i].id));
			Link.l2 = StringFromKey("Diplomat_dialog_107");
			Link.l2.go = "exit";
			Link.l3 = StringFromKey("Diplomat_dialog_108");
			Link.l3.go = "relation";
		break;
		//линейка ГПК
		case "SeekHVIC":
			dialog.text = StringFromKey("Diplomat_dialog_109");
			link.l1 = StringFromKey("Diplomat_dialog_110");
			link.l1.go = "SeekHVIC_1";
		break;
		case "SeekHVIC_1":
			dialog.text = StringFromKey("Diplomat_dialog_111");
			link.l1 = StringFromKey("Diplomat_dialog_112");
			link.l1.go = "SeekHVIC_2";
		break;
		case "SeekHVIC_2":
			dialog.text = StringFromKey("Diplomat_dialog_113");
			Link.l1.edit = 6;
			link.l1 = "";
			link.l1.go = "SeekHVIC_res";
		break;
		case "SeekHVIC_res":
			attrLoc = GetStrSmallRegister(dialogEditStrings[6]);
			if (HasSubStr(attrLoc, GetStrSmallRegister(FindPersonalName("PoorKillSponsor_name"))) && HasSubStr(attrLoc, GetStrSmallRegister(FindPersonalName("PoorKillSponsor_lastname"))))
			{
				dialog.text = StringFromKey("Diplomat_dialog_114");
				link.l1 = StringFromKey("Diplomat_dialog_115");
				link.l1.go = "exit";
				pchar.questTemp.LSC = "toOliverTrast";
				AddQuestRecord("ISS_PoorsMurder", "10");
				RemoveLandQuestMarkToFantoms_Main("diplomat", "ISS_PoorsMurder");
				LocatorReloadEnterDisable("Marigo_town", "houseH2", false);
				sld = GetCharacter(NPC_GenerateCharacter("PoorKillSponsor", "Oliver_Trusts", "man", "man", 30, PIRATE, -1, true));
				sld.name = FindPersonalName("PoorKillSponsor_name");
				sld.lastname = FindPersonalName("PoorKillSponsor_lastname");
				FantomMakeCoolFighter(sld, 40, 90, 90, "blade26", "pistol3", 100);
				sld.SaveItemsForDead = true;
				sld.Dialog.Filename = "Quest\ForAll_dialog.c";
				sld.nation = HOLLAND;
				sld.city = "Marigo_town";
				sld.location = "Marigo_houseH2";
				sld.location.group = "sit";
				sld.location.locator = "sit1";
				sld.dialog.currentnode = "PKInMarigo";
				LAi_CharacterEnableDialog(sld);
				LAi_RemoveLoginTime(sld);
				sld.standUp = true; //вставать и нападать на врага
				LAi_SetHuberType(sld);
				//кладём второе письмо
				sld = ItemsFromID("letter_LSC_1");
				sld.shown = true;
				sld.startLocation = "Marigo_houseH2";
				sld.startLocator = "item1";
			}
			else
			{
				dialog.text = StringFromKey("Diplomat_dialog_116");
				link.l1 = StringFromKey("Diplomat_dialog_117");
				link.l1.go = "exit";
				pchar.questTemp.LSC = "toLicencer_2";
			}
		break;
		case "SeekHVIC_3":
			dialog.text = StringFromKey("Diplomat_dialog_118");
			link.l1 = StringFromKey("Diplomat_dialog_119", pchar);
			link.l1.go = "SeekHVIC_4";
		break;
		case "SeekHVIC_4":
			dialog.text = StringFromKey("Diplomat_dialog_120");
			Link.l1.edit = 6;
			link.l1 = "";
			link.l1.go = "SeekHVIC_res";
		break;
		// evganat - энциклопедия
		case "Encyclopedia_1":
			if (CheckAttribute(npchar, "encyclopedia.cooldown") && GetNpcQuestPastDayParam(npchar, "encyclopedia.last_date") < sti(npchar.encyclopedia.cooldown))
			{
				// рано пришёл, новая ещё не сгенерилась
				dialog.text = StringFromKey("Diplomat_dialog_121");
				link.l1 = StringFromKey("Diplomat_dialog_122");
				link.l1.go = "exit";
				break;
			}
			if (!CheckAttribute(npchar, "encyclopedia.welldone") && idRand(npchar.id + "encyclopedia", 2) != 1)    // 33%
			{
				dialog.text = StringFromKey("Diplomat_dialog_123");
				link.l1 = StringFromKey("Diplomat_dialog_124");
				link.l1.go = "exit";
				break;
			}
			dialog.text = StringFromKey("Diplomat_dialog_125");
			link.l1 = StringFromKey("Diplomat_dialog_126");
			link.l1.go = "Encyclopedia_2";
		break;

		case "Encyclopedia_2":
			string dTome, mTome;
			int dPage, mPage;
			if (!GetRandomMissingPage(&mTome, &mPage))    // есть недостающие
			{
				npchar.encyclopedia.full = true;
				dialog.text = StringFromKey("Diplomat_dialog_127");
				link.l1 = StringFromKey("Diplomat_dialog_128", pchar);
				link.l1.go = "exit";
				break;
			}
			if (!GetRandomDuplicatePage(&dTome, &dPage))
			{
				dialog.text = StringFromKey("Diplomat_dialog_129");
				link.l1 = StringFromKey("Diplomat_dialog_130", pchar);
				link.l1.go = "exit";
				break;
			}
			npchar.encyclopedia.change.dTome = dTome;
			npchar.encyclopedia.change.dPage = dPage;
			npchar.encyclopedia.change.mTome = mTome;
			npchar.encyclopedia.change.mPage = mPage;
			dialog.text = StringFromKey("Diplomat_dialog_131", GetPageString(mPage), GetTomeStringGen(mTome), GetPageString(dPage), GetTomeStringGen(dTome));
			link.l1 = StringFromKey("Diplomat_dialog_132");
			link.l1.go = "Encyclopedia_change";
		break;

		case "Encyclopedia_change":
			string sTome = npchar.encyclopedia.change.dTome;
			string sPage = "p" + npchar.encyclopedia.change.dPage;
			GetPage(npchar.encyclopedia.change.mTome, sti(npchar.encyclopedia.change.mPage));
			pchar.encyclopedia.tomes.(sTome).(sPage) = sti(pchar.encyclopedia.tomes.(sTome).(sPage)) - 1;
			DeleteAttribute(npchar, "encyclopedia.change");
			SaveCurrentNpcQuestDateParam(npchar, "encyclopedia.last_date");
			npchar.encyclopedia.cooldown = 30 + rand(30);
			if (!CheckAttribute(npchar, "encyclopedia.welldone"))
			{
				npchar.encyclopedia.welldone = true;
				dialog.text = StringFromKey("Diplomat_dialog_133");
				link.l1 = StringFromKey("Diplomat_dialog_134");
				link.l1.go = "exit";
				break;
			}
			dialog.text = StringFromKey("Diplomat_dialog_135");
			link.l1 = StringFromKey("Diplomat_dialog_136");
			link.l1.go = "exit";
		break;

		// ГПК расшифровка с помощью дипломата
		case "LogToDecrypt_1":
			dialog.text = StringFromKey("Diplomat_dialog_137");
			link.l1 = StringFromKey("Diplomat_dialog_138");
			link.l1.go = "LogToDecrypt_2";
			PlaySound("Took_item");
		break;
		case "LogToDecrypt_2":
			dialog.text = StringFromKey("Diplomat_dialog_139");
			link.l1 = StringFromKey("Diplomat_dialog_140");
			link.l1.go = "LogToDecrypt_3";
			PlaySound("Important_item");
		break;
		case "LogToDecrypt_3":
			dialog.text = StringFromKey("Diplomat_dialog_141");
			link.l1 = StringFromKey("Diplomat_dialog_142");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "DecryptionWithOliverHelpLSC";
			AddQuestRecord("ISS_PoorsMurder", "26");
			RemoveLandQuestMarkToFantoms_Main("diplomat", "ISS_PoorsMurder");
			AddLandQuestMark_Main(CharacterFromID("Oliver_Green"), "ISS_PoorsMurder");
		break;
	}
}

