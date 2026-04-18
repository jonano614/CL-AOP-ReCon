// BOAL диалог пленников - в трюме
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref offref;
	int i, cn;
	int qty;
	string attrLoc, sTmp;
	bool Ok = false;

	switch (Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "First time":
			if (sti(NPChar.nation) == PIRATE)
			{
				//				dialog.text = RandSwear() + "Я Ваш пленник, " + GetAddress_Form(NPChar) + ". Но должен сказать, что " + NationNameNominative(sti(NPChar.nation)) + " никогда не выкупает своих - каждый сам за себя.";
				dialog.text = StringFromKey("Capitan_ransack_dialog_1", RandSwear(), GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Capitan_ransack_dialog_2");
				link.l1.go = "offender";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l2 = StringFromKey("Capitan_ransack_dialog_3");
					link.l2.go = "free_to_officer";
				}
			}
			else
			{
				dialog.text = StringFromKey("Capitan_ransack_dialog_4", RandSwear(), GetAddress_Form(NPChar), NationNameNominative(sti(NPChar.nation)));
				if (NPChar.EncType == "trade" && FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
				{
					link.l1 = StringFromKey("Capitan_ransack_dialog_5");
					link.l1.go = "free_to_officer_trader";
				}
			}
			attrLoc = Sea_FindNearColony(true);
			if (attrLoc != "none")
			{
				link.l3 = StringFromKey("Capitan_ransack_dialog_6", pchar, GetConvertStr(attrLoc + " Town", "LocLables.txt"));
				link.l3.go = "free_withoutFee";
			}
			else
			{
				link.l3 = StringFromKey("Capitan_ransack_dialog_7");
				link.l3.go = "free_withoutFee_2";
			}
			link.l4 = StringFromKey("Capitan_ransack_dialog_8");
			link.l4.go = "Slave_1";
			if (CheckAttribute(NPChar, "survivor"))
				link.l5 = StringFromKey("Capitan_ransack_dialog_9");
			else
				link.l5 = StringFromKey("Capitan_ransack_dialog_10");
			link.l5.go = "PunishmentAction";
			link.l6 = StringFromKey("Capitan_ransack_dialog_11");
			link.l6.go = "exit";
			if (Get_My_Cabin() == NPChar.location)
			{
				link.l6 = StringFromKey("Capitan_ransack_dialog_12");
				link.l6.go = "goToExit";
			}
			NextDiag.TempNode = "second time";
		break;

		case "second time":
			if (CheckAttribute(NPChar, "Hold_GenQuest") && !CheckAttribute(pchar, "GenQuest.Hold_GenQuest"))
			{
				switch (sti(NPChar.Hold_GenQuest.variant))
				{
					case 0: // "наводка"
						dialog.text = StringFromKey("Capitan_ransack_dialog_15", RandPhraseSimple(
									StringFromKey("Capitan_ransack_dialog_13"),
									StringFromKey("Capitan_ransack_dialog_14")));
						link.l1 = StringFromKey("Capitan_ransack_dialog_16");
						link.l1.go = "free_tip_off";
					break;

					case 1:
						dialog.text = StringFromKey("Capitan_ransack_dialog_17");
						link.l1 = StringFromKey("Capitan_ransack_dialog_18");
						link.l1.go = "free_by_hoard";
						attrLoc = Sea_FindNearColony(true);
						if (attrLoc != "none")
						{
							if (CheckAttribute(NPChar, "survivor"))
								link.l2 = StringFromKey("Capitan_ransack_dialog_19");
							else
								link.l2 = StringFromKey("Capitan_ransack_dialog_20");
							link.l2.go = "PunishmentAction";
						}
						else
						{
							link.l2 = StringFromKey("Capitan_ransack_dialog_21");
							link.l2.go = "free_in_sea";
						}
						link.l3 = StringFromKey("Capitan_ransack_dialog_25", LinkRandPhrase(
									StringFromKey("Capitan_ransack_dialog_22"),
									StringFromKey("Capitan_ransack_dialog_23"),
									StringFromKey("Capitan_ransack_dialog_24")));
						link.l3.go = "exit";
					break;

					case 2: // "выкуп"
						dialog.text = StringFromKey("Capitan_ransack_dialog_26");
						link.l1 = StringFromKey("Capitan_ransack_dialog_27");
						link.l1.go = "free_buyout";
						link.l2 = StringFromKey("Capitan_ransack_dialog_34", RandPhraseSimple(
									StringFromKey("Capitan_ransack_dialog_30", RandPhraseSimple(
											StringFromKey("Capitan_ransack_dialog_28", pchar),
											StringFromKey("Capitan_ransack_dialog_29"))),
									StringFromKey("Capitan_ransack_dialog_33", RandPhraseSimple(
											StringFromKey("Capitan_ransack_dialog_31"),
											StringFromKey("Capitan_ransack_dialog_32")))));
						link.l2.go = "exit";
					break;
				}
				NextDiag.TempNode = "second time";
			}
			else
			{
				if (sti(NPChar.nation) == PIRATE)
				{
					dialog.text = StringFromKey("Capitan_ransack_dialog_35");
					if (FindFreeRandomOfficer() > 0)
					{
						link.l2 = StringFromKey("Capitan_ransack_dialog_36");
						link.l2.go = "free_to_officer";
					}
					link.l3 = StringFromKey("Capitan_ransack_dialog_40", LinkRandPhrase(
								StringFromKey("Capitan_ransack_dialog_37"),
								StringFromKey("Capitan_ransack_dialog_38"),
								StringFromKey("Capitan_ransack_dialog_39")));
					link.l3.go = "exit";
				}
				else
				{
					if (NPChar.EncType == "trade")
					{
						dialog.text = StringFromKey("Capitan_ransack_dialog_41");
						if (FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
						{
							link.l2 = StringFromKey("Capitan_ransack_dialog_42");
							link.l2.go = "free_to_officer_trader";
						}
						link.l3 = StringFromKey("Capitan_ransack_dialog_46", LinkRandPhrase(
									StringFromKey("Capitan_ransack_dialog_43"),
									StringFromKey("Capitan_ransack_dialog_44"),
									StringFromKey("Capitan_ransack_dialog_45")));
						link.l3.go = "exit";
					}
					else if (NPChar.EncType == "war")
					{
						dialog.text = StringFromKey("Capitan_ransack_dialog_49", RandPhraseSimple(
									StringFromKey("Capitan_ransack_dialog_47"),
									StringFromKey("Capitan_ransack_dialog_48")));
						link.l2 = StringFromKey("Capitan_ransack_dialog_57", LinkRandPhrase(
									StringFromKey("Capitan_ransack_dialog_50"),
									StringFromKey("Capitan_ransack_dialog_53", RandPhraseSimple(
											StringFromKey("Capitan_ransack_dialog_51"),
											StringFromKey("Capitan_ransack_dialog_52"))),
									StringFromKey("Capitan_ransack_dialog_56", RandPhraseSimple(
											StringFromKey("Capitan_ransack_dialog_54"),
											StringFromKey("Capitan_ransack_dialog_55")))));
						link.l2.go = "exit";
						if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 1)
						{
							if (sti(Items[sti(pchar.EquipedPatentId)].Nation) == sti(NPChar.nation) && FindFreeRandomOfficer() > 0)
							{
								link.l3 = StringFromKey("Capitan_ransack_dialog_58");
								link.l3.go = "free_to_officer";
							}
						}
					}
					else
					{
						dialog.text = StringFromKey("Capitan_ransack_dialog_61", RandPhraseSimple(
									StringFromKey("Capitan_ransack_dialog_59"),
									StringFromKey("Capitan_ransack_dialog_60")));
						link.l3 = StringFromKey("Capitan_ransack_dialog_65", LinkRandPhrase(
									StringFromKey("Capitan_ransack_dialog_62"),
									StringFromKey("Capitan_ransack_dialog_63"),
									StringFromKey("Capitan_ransack_dialog_64")));
						link.l3.go = "exit";
					}
				}
				attrLoc = Sea_FindNearColony(true);
				if (attrLoc != "none")
				{
					link.l4 = StringFromKey("Capitan_ransack_dialog_66", pchar, GetConvertStr(attrLoc + " Town", "LocLables.txt"));
					link.l4.go = "free_withoutFee";
				}
				else
				{
					if (NPChar.EncType == "trade" || NPChar.EncType == "pirate")
					{
						link.l4 = StringFromKey("Capitan_ransack_dialog_67");
						link.l4.go = "free_withoutFee_4";
					}
					else
					{
						link.l4 = StringFromKey("Capitan_ransack_dialog_68");
						link.l4.go = "free_withoutFee_4";
					}
				}
				link.l5 = StringFromKey("Capitan_ransack_dialog_69");
				link.l5.go = "Slave_1";
				if (CheckAttribute(NPChar, "survivor"))
					link.l6 = StringFromKey("Capitan_ransack_dialog_70");
				else
					link.l6 = StringFromKey("Capitan_ransack_dialog_71");
				link.l6.go = "PunishmentAction";
			}
			if (Get_My_Cabin() == NPChar.location)
			{
				link.l7 = StringFromKey("Capitan_ransack_dialog_72");
				link.l7.go = "goToExit";
			}
		break;

		case "offender":
			dialog.text = StringFromKey("Capitan_ransack_dialog_73", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Capitan_ransack_dialog_74");
			link.l1.go = "exit";
		break;

		case "free_to_officer":
			if ((GetSummonSkillFromName(pchar, "Leadership") + 20) <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				PlayerRPGCheck_Skill_NotifyFail("Leadership", false);
				dialog.text = StringFromKey("Capitan_ransack_dialog_75");
				link.l1 = StringFromKey("Capitan_ransack_dialog_76");
				link.l1.go = "exit";
			}
			else
			{
				PlayerRPGCheck_Skill_NotifyPass("Leadership");
				dialog.text = StringFromKey("Capitan_ransack_dialog_77", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Capitan_ransack_dialog_78");
				link.l1.go = "free_to_officer_Hire";
				link.l2 = StringFromKey("Capitan_ransack_dialog_79", pchar);
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_trader":
			if (GetSummonSkillFromName(pchar, "Leadership") <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				PlayerRPGCheck_Skill_NotifyFail("Leadership", false);
				dialog.text = StringFromKey("Capitan_ransack_dialog_83", LinkRandPhrase(
							StringFromKey("Capitan_ransack_dialog_80"),
							StringFromKey("Capitan_ransack_dialog_81"),
							StringFromKey("Capitan_ransack_dialog_82")));
				link.l1 = StringFromKey("Capitan_ransack_dialog_84");
				link.l1.go = "exit";
			}
			else
			{
				PlayerRPGCheck_Skill_NotifyPass("Leadership");
				dialog.text = StringFromKey("Capitan_ransack_dialog_85");
				link.l1 = StringFromKey("Capitan_ransack_dialog_86");
				link.l1.go = "free_to_officer_Hire";
				link.l2 = StringFromKey("Capitan_ransack_dialog_87", pchar);
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_Hire":
			NPChar.Dialog.Filename = "Officer_Man.c";
			NPChar.greeting = "Gr_Officer";
			NPChar.loyality = 5 + rand(10);
			if (sti(NPChar.reputation) > 41)
			{
				NPChar.alignment = "good";
				SetCharacterPerk(NPChar, "Honest");
			}
			else
			{
				NPChar.alignment = "bad";
				SetCharacterPerk(NPChar, "Rebel");
			}
			ReleasePrisoner(NPChar); // освободили пленника
			DeleteAttribute(NPChar, "LifeDay"); // постоянный
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			// тут трем накопивщиеся сабли и корабли 290704 BOAL -->
			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
			DeleteAttribute(Npchar, "Fellows"); // его офицеры
			Npchar.Fellows.Passengers.id0 = Npchar.index; // свой пассажир

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1";

			if (CheckAttribute(NPChar, "Hold_GenQuest")) DeleteAttribute(NPChar, "Hold_GenQuest");

			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
		break;
		//базар на счёт рабства --->
		case "Slave_1":
			dialog.text = StringFromKey("Capitan_ransack_dialog_88", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Capitan_ransack_dialog_89");
			link.l1.go = "Slave_2";
			link.l2 = StringFromKey("Capitan_ransack_dialog_90");
			link.l2.go = "exit";
		break;

		case "Slave_2":
			OfficersReaction("bad");
			ChangeCharacterReputation(pchar, -3);
			//HardCoffee ставлю разные шансы на суицид и агрессивность в зависимости от типа пленника
			//можно будет написать разные диалоги, а пока вместо диалогов - универсальные заглушки
			//для различных вариантов событий можно добавить: CheckAttribute(NPChar, "survivor")
			if (sti(NPChar.nation) == PIRATE)
			{
				i = rand(5);
				if (0 == i) FreeInSea4(link, NPChar);
				else if (5 == i) Slave3(link, NPChar);
				else
				{
					if (Number_Group_People("Prisoner", 0) > 1) FreeInSeaBattleAll(link, NPChar);
					else FreeInSeaBattle1(link, NPChar);
				}
			}
			else if (CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "war")
			{
				i = rand(4);
				if (0 == i || 1 == i) FreeInSea4(link, NPChar);
				else if (4 == i) Slave3(link, NPChar);
				else
				{
					if (Number_Group_People("Prisoner", 0) > 1) FreeInSeaBattleAll(link, NPChar);
					else FreeInSeaBattle1(link, NPChar);
				}
			}
			else if (CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
			{
				i = rand(4);
				if (0 == i) FreeInSea4(link, NPChar);
				else if (4 == i)
				{
					if (Number_Group_People("Prisoner", 0) > 1) FreeInSeaBattleAll(link, NPChar);
					else FreeInSeaBattle1(link, NPChar);
				}
				else Slave3(link, NPChar);
			}
			else //это оригинальная процедура
			{
				if (rand(5) == 1) FreeInSea4(link, NPChar);
				else
				{
					if (rand(1) == 1)
					{
						if (Number_Group_People("Prisoner", 0) > 1) FreeInSeaBattleAll(link, NPChar);
						else FreeInSeaBattle1(link, NPChar);
					}
					else Slave3(link, NPChar);
				}
			}
		break;
		//базар на счёт рабства <---
		//базар на счёт казни --->
		case "PunishmentAction":
			if (CheckAttribute(NPChar, "survivor"))
			{
				dialog.text = StringFromKey("Capitan_ransack_dialog_91", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Capitan_ransack_dialog_92", pchar);
			}
			else
			{
				dialog.text = StringFromKey("Capitan_ransack_dialog_93", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Capitan_ransack_dialog_94");
			}
			link.l1.go = "PunishmentAction1";
			link.l2 = StringFromKey("Capitan_ransack_dialog_95");
			link.l2.go = "exit";
		break;

		case "PunishmentAction1":
			OfficersReaction("bad");
			ChangeCharacterReputation(pchar, -3);
			AddCharacterExpToSkill(Pchar, "Leadership", -150);
			cn = Number_Group_People("Prisoner", 0);
			if (rand(3) == 0 && CheckAttribute(NPChar, "survivor") && cn < 4) Ok = true;
			else if (rand(4) == 0 && sti(NPChar.nation) == PIRATE && cn < 3) Ok = true;
			else if (rand(1) == 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade" && cn < 4) Ok = true;
			else if (rand(3) == 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "war" && cn < 3) Ok = true;
			if (oK)
			{
				if (CheckAttribute(pchar, "questTemp.ShipCapellan.Yes"))
					dialog.text = StringFromKey("Capitan_ransack_dialog_96");
				else
					dialog.text = StringFromKey("Capitan_ransack_dialog_97");
				link.l1 = StringFromKey("Capitan_ransack_dialog_98");
				link.l1.go = "PunishmentAction2";
			}
			else if (cn > 1 && rand(4) != 0) FreeInSeaBattleAll(link, NPChar);
			else FreeInSeaBattle1(link, NPChar);
		break;
		/* HardCoffee отключаю для тестов вызова в каюту
		case "PunishmentAction1":
			OfficersReaction("bad");
			ChangeCharacterReputation(pchar, -2);
			AddCharacterExpToSkill(Pchar, "Leadership", -150);
			if (rand(1) == 1)
            {
                if (GetPrisonerQty() > 1)
                {
                    dialog.text = "Ах ты палач! Братцы, двум смертям не бывать, а одной не миновать!";
                    link.l1 = "А вот это вы напрасно. Попытки бунта я пресекаю собственноручно и без проволочек...";
					link.l1.go = "free_in_sea_battle_all";
                }
				else
				{
					dialog.text = "Нет! Уж лучше смерть в бою!";
					link.l1 = "Как вым будет угодно...";
					link.l1.go = "free_in_sea_battle_1";
				}
    		}
			else
    		{
				dialog.text = "Разрешите хоть помолиться перед смертью...";
                link.l1 = "Молитесь...";
        		link.l1.go = "PunishmentAction2";
    		}
		break;
		*/
		//базар на счёт казни <---
		//Базар на счёт мордобоя --->
		case "free_in_sea_battle_pre_punch":
			if (rand(2) == 0 || CheckCharacterPerk(NPChar, "Dignity"))
			{
				if (Number_Group_People("Prisoner", 0) > 1)
				{
					dialog.text = StringFromKey("Capitan_ransack_dialog_99");
					link.l1 = StringFromKey("Capitan_ransack_dialog_100");
					link.l1.go = "free_in_sea_battle_all";
				}
				else
				{
					dialog.text = StringFromKey("Capitan_ransack_dialog_101");
					link.l1 = StringFromKey("Capitan_ransack_dialog_102", npchar);
					link.l1.go = "free_in_sea_battle_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("Capitan_ransack_dialog_105", RandPhraseSimple(
							StringFromKey("Capitan_ransack_dialog_103", npchar),
							StringFromKey("Capitan_ransack_dialog_104")));
				link.l1 = StringFromKey("Capitan_ransack_dialog_106");
				link.l1.go = "free_in_sea_battle_punch";
			}
		break;
		//Базар на счёт мордобоя <---
		// финалы рабства/казни --->
		case "free_in_sea_battle_punch": //драка на кулаках
			ReleasePrisoner(NPChar); //test проверить поведение квестовых пленных
			if (Get_My_Cabin() == pchar.location) //освобождаем локацию от посторонних
			{
				SetOfficersLocationToNone();
				CompanionSaveTasks();
			}
			SetPrisonerLocationToNone();
			Take_Fists(); //запоминаем экипировку гг и выдаём кулаки

			LAi_LocationFightDisable(&Locations[FindLocation(NPChar.location)], false);
			chrDisableReloadToLocation = true; //Закроем локацию, чтобы гг не сбежал
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorType(NPChar);
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_TmpEnemy);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
			LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
			LAi_group_SetRelation(LAI_GROUP_TmpEnemy, "Prisoner", LAI_GROUP_NEITRAL);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "free_in_sea_battle_1": //Драка толпой на 1 арестанта с использованием оружия
			ReleasePrisoner(NPChar);
			SetPrisonerLocationToNone(); //уберём остальных арестантов, не готовых драться, чтобы не мешались
			LAi_LocationFightDisable(&Locations[FindLocation(NPChar.location)], false);  //HardCoffee для битв в каюте
			if (Get_My_Cabin() == NPChar.location) Reset_Officers_InCabin(); //HardCoffee чтобы сидячие офицеры вступили в бой
			chrDisableReloadToLocation = true; //Закроем локацию, чтобы гг не сбежал
			LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_warrior_DialogEnable(NPChar, false);

			if (Rand(1) == 0) sTmp = "blade5";
			else sTmp = "kocherg";
			GiveItem2Character(NPChar, sTmp);
			EquipCharacterByItem(NPChar, sTmp);

			LAi_group_MoveCharacter(NPChar, LAI_GROUP_TmpEnemy);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
			LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
			LAi_group_SetRelation(LAI_GROUP_TmpEnemy, "Prisoner", LAI_GROUP_NEITRAL);
			LAi_group_SetRelation(LAI_GROUP_PLAYER, "Prisoner", LAI_GROUP_NEITRAL);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn"); //чтобы гг выхватил саблю LAi_SetFightMode(Pchar, true); не срабатывает
		break;

		case "free_in_sea_battle_all": //Драка стенка на стенку
		//ugeen --> привет Сиварду !!! после релиза пленников кол-во пассажиров уменьшается и цикл нихрена дальше не срабатывал
		//for (int j = GetPassengersQuantity(pchar) - 1; j > -1; j--) //test не забыть подчистить
			qty = LAi_numloginedcharacters;
			for (int j = 0; j < qty; j++) //только чарактеров на локации, так как часть может быть в каюте, а другая часть - втрюме
			{
				cn = LAi_loginedcharacters[j];
				if (cn < 0) continue;
				offref = GetCharacter(cn); // ставим только фантомов
				if (CheckAttribute(offref, "Capellan")) //убираем капеллана
				{
					ChangeCharacterAddress(offref, "none", "");
					continue;
				}
				if (!CheckAttribute(offref, "prisoned") || sti(offref.prisoned) == false || CheckAttribute(offref, "NonRemovable")) continue;
				ReleasePrisoner(offref); // освободили пленника

				i = rand(2);
				sTmp = "unarmed";
				if (0 == i) sTmp = "blade5"; //так как для кулачные бои выведены отдельно - выдадим зэку заточку
				else if (1 == i) sTmp = "kocherg"; //или кочергу
				GiveItem2Character(offref, sTmp);
				EquipCharacterByItem(offref, sTmp);

				LAi_SetWarriorTypeNoGroup(offref);
				LAi_warrior_DialogEnable(offref, false);
				LAi_group_MoveCharacter(offref, LAI_GROUP_TmpEnemy);
			}
			LAi_LocationFightDisable(&Locations[FindLocation(NPChar.location)], false);
			if (Get_My_Cabin() == NPChar.location) Reset_Officers_InCabin(); //сидячих офицеров то же заставим вступить в бой
			chrDisableReloadToLocation = true; //Закроем локацию, чтобы гг не сбежал
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
			LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "free_in_sea_4": //пленник суициднулся
			ReleasePrisoner(NPChar);
			NPChar.location = "";
			LAi_KillCharacter(NPChar);
			DialogExit();
		break;

		case "PunishmentAction2": // дали помолиться перед смертью
			ReleasePrisoner(NPChar);
			LAi_CharacterDisableDialog(NPChar);
			if (CheckAttribute(pchar, "questTemp.ShipCapellan.Yes")) //Заставим капеллана пройти вместе с пленным
			{
				offref = RefOfficer("capellan");
				if (NPChar.location == offref.location) ok = true;
			}
			if (CheckAttribute(loadedLocation, "locators.reload.reload1") && LAi_IsLocatorFree("reload", "reload1", -0.1))
			{
				LAi_SetActorTypeNoGroup(NPChar);
				LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
				if (ok)
				{
					LAi_SetActorTypeNoGroup(offref);
					LAi_ActorGoToLocation(offref, "reload", "reload1", "none", "", "", "", 4.0);
				}
			}
			else
			{
				ChangeCharacterAddress(NPChar, "none", "");
				if (ok) ChangeCharacterAddress(offref, "none", "");
			}
			NPChar.location = "";
			NPChar.LifeDay = 0;
			DialogExit();
		break;

		case "Slave_3": //арестант согласился пойти в рабы
			ReleasePrisoner(NPChar);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
			DialogExit();
			AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
		break;
		//финалы рабства/казни <---

		case "free_withoutFee":
			dialog.text = StringFromKey("Capitan_ransack_dialog_107", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Capitan_ransack_dialog_108", GetFullName(NPChar));
			link.l1.go = "free_withoutFee_2";
			link.l99 = StringFromKey("Capitan_ransack_dialog_109");
			link.l99.go = "exit";
		break;

		case "free_withoutFee_2":
			dialog.text = StringFromKey("Capitan_ransack_dialog_110", GetFullName(PChar));
			link.l1 = StringFromKey("Capitan_ransack_dialog_111", pchar);
			link.l1.go = "free_withoutFee_3";
			OfficersReaction("good");
		break;

		case "free_withoutFee_3":
			ReleasePrisoner(NPChar); // освободили пленника
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
			ChangeCharacterReputation(pchar, 2);
			DialogExit();
		break;

		case "free_withoutFee_4":
			switch (NPChar.EncType)
			{
				dialog.text = StringFromKey("Capitan_ransack_dialog_112");
				link.l1 = StringFromKey("Capitan_ransack_dialog_113");
				case "pirate":
					dialog.text = StringFromKey("Capitan_ransack_dialog_116", RandPhraseSimple(
								StringFromKey("Capitan_ransack_dialog_114"),
								StringFromKey("Capitan_ransack_dialog_115")));
					link.l1 = StringFromKey("Capitan_ransack_dialog_117");
				break;
				case "trade":
					dialog.text = StringFromKey("Capitan_ransack_dialog_118");
					link.l1 = StringFromKey("Capitan_ransack_dialog_119");
				break;
				case "war":
					dialog.text = StringFromKey("Capitan_ransack_dialog_120");
					link.l1 = StringFromKey("Capitan_ransack_dialog_121", pchar);
				break;
			}
			link.l1.go = "free_withoutFee_3";
		break;

		case "free_tip_off":
			dialog.text = StringFromKey("Capitan_ransack_dialog_122");
			link.l1 = StringFromKey("Capitan_ransack_dialog_123");
			link.l1.go = "free_tip_off_0";
			link.l2 = StringFromKey("Capitan_ransack_dialog_124");
			link.l2.go = "free_tip_off_1";
		break;

		case "free_tip_off_0":
			ChangeCharacterReputation(pchar, -2);
			DeleteAttribute(NPChar, "Hold_GenQuest");
			DialogExit();
		break;

		case "free_tip_off_1":
			switch (NPChar.EncType)
			{
				case "trade":
					sTmp = StringFromKey("Capitan_ransack_dialog_125");
				break;
				case "war":
					sTmp = StringFromKey("Capitan_ransack_dialog_126");
				break;
				case "pirate":
					sTmp = StringFromKey("Capitan_ransack_dialog_127");
				break;
			}
			dialog.text = StringFromKey("Capitan_ransack_dialog_128", XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Pre"), NPChar.Hold_GenQuest.Name, NPChar.Hold_GenQuest.ShipName, GetStrSmallRegister(XI_ConvertString(Goods[sti(NPChar.Hold_GenQuest.Goods)].Name + "Acc")), XI_ConvertString("Colony" + NPChar.Hold_GenQuest.FromCity), XI_ConvertString("Colony" + NPChar.Hold_GenQuest.ToCity), sTmp);
			link.l1 = StringFromKey("Capitan_ransack_dialog_129");
			link.l1.go = "free_tip_off_0";
			link.l2 = StringFromKey("Capitan_ransack_dialog_130");
			link.l2.go = "free_tip_off_2";
		break;

		case "free_tip_off_2":
			dialog.text = StringFromKey("Capitan_ransack_dialog_131");
			link.l1 = StringFromKey("Capitan_ransack_dialog_138", RandPhraseSimple(
						StringFromKey("Capitan_ransack_dialog_134", RandPhraseSimple(
								StringFromKey("Capitan_ransack_dialog_132"),
								StringFromKey("Capitan_ransack_dialog_133"))),
						StringFromKey("Capitan_ransack_dialog_137", RandPhraseSimple(
								StringFromKey("Capitan_ransack_dialog_135", pchar),
								StringFromKey("Capitan_ransack_dialog_136", pchar)))));
			link.l1.go = "free_tip_off_3";
		break;

		case "free_tip_off_3":
			pchar.GenQuest.Hold_GenQuest.Goods = NPChar.Hold_GenQuest.Goods;
			pchar.GenQuest.Hold_GenQuest.Nation = NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name = NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.ToCity = NPChar.Hold_GenQuest.ToCity;
			pchar.GenQuest.Hold_GenQuest.FromCity = NPChar.Hold_GenQuest.FromCity;
			pchar.GenQuest.Hold_GenQuest.ShipName = NPChar.Hold_GenQuest.ShipName;
			pchar.GenQuest.Hold_GenQuest.City = NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.CapName = GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.Island = GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;

			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "1");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Acc")));
			AddQuestUserData("HoldQuest", "sCityFrom", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.FromCity));
			AddQuestUserData("HoldQuest", "sCityTo", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.ToCity));
			AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);

			SetFunctionTimerCondition("Hold_GenQuest_SetMerchant_pre", 0, 0, 1 + rand(2), false);
			SetFunctionTimerCondition("Hold_GenQuest_MerchantOver", 0, 0, 30, false);

			ReleasePrisoner(NPChar); // освободили пленника
			LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
			DialogExit();
		break;

		case "free_buyout":
			dialog.text = StringFromKey("Capitan_ransack_dialog_139", XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Pre"), NPChar.Hold_GenQuest.Name);
			link.l1 = StringFromKey("Capitan_ransack_dialog_140");
			link.l1.go = "free_buyout1";
			link.l2 = StringFromKey("Capitan_ransack_dialog_141");
			link.l2.go = "free_tip_off_0";
		break;

		case "free_buyout1":
			LAi_CharacterDisableDialog(NPChar);

			pchar.GenQuest.Hold_GenQuest.City = NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.Nation = NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name = NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.CapName = GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.CapId = NPChar.Id;
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;

			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "6");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Pre"));
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			DialogExit();
		break;

		case "free_by_hoard":
			dialog.text = StringFromKey("Capitan_ransack_dialog_142");
			link.l1 = StringFromKey("Capitan_ransack_dialog_143");
			link.l1.go = "free_by_hoard1";
			link.l2 = StringFromKey("Capitan_ransack_dialog_144");
			link.l2.go = "free_tip_off_0";
		break;

		case "free_by_hoard1":
			dialog.text = StringFromKey("Capitan_ransack_dialog_145");
			link.l1 = StringFromKey("Capitan_ransack_dialog_146", pchar);
			link.l1.go = "free_tip_off_0";
			link.l2 = StringFromKey("Capitan_ransack_dialog_147");
			link.l2.go = "free_by_hoard2";
		break;

		case "free_by_hoard2":
			dialog.text = StringFromKey("Capitan_ransack_dialog_148", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("Capitan_ransack_dialog_149");
			link.l1.go = "free_by_hoard4";
		break;

		case "free_by_hoard4":
			dialog.text = StringFromKey("Capitan_ransack_dialog_150", XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Pre"), NPChar.Hold_GenQuest.Name, GetName(NAMETYPE_VIP, NPChar.Hold_GenQuest.PirateName, NAME_ACC), GetName(NAMETYPE_VIP, NPChar.Hold_GenQuest.PirateName, NAME_NOM));
			link.l1 = StringFromKey("Capitan_ransack_dialog_151");
			link.l1.go = "free_tip_off_0";
			link.l2 = StringFromKey("Capitan_ransack_dialog_152");
			link.l2.go = "free_by_hoard5";
		break;

		case "free_by_hoard5":
			dialog.text = StringFromKey("Capitan_ransack_dialog_153", pchar);
			link.l1 = StringFromKey("Capitan_ransack_dialog_154", pchar);
			link.l1.go = "free_by_hoard6";
		break;

		case "free_by_hoard6":
			pchar.GenQuest.Hold_GenQuest.City = NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.Nation = NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name = NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.PirateName = NPChar.Hold_GenQuest.PirateName;
			pchar.GenQuest.Hold_GenQuest.CapName = GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1) + 2;
			pchar.GenQuest.Hold_GenQuest.Sum = 10000 + rand(10000);
			pchar.GenQuest.Hold_GenQuest.Treasure = rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;

			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "12");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Pre"));
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sPirateName", GetName(NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));

			ReleasePrisoner(NPChar); // освободили пленника
			LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
			DialogExit();
		break;

		case "free_in_sea":
			dialog.text = StringFromKey("Capitan_ransack_dialog_155", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Capitan_ransack_dialog_156");
			link.l1.go = "PunishmentAction1";
			link.l2 = StringFromKey("Capitan_ransack_dialog_157");
			link.l2.go = "exit";
		break;

		case "goToExit": //HardCoffee выгнать из каюты
			if (CheckAttribute(loadedLocation, "locators.reload.reload1") && LAi_IsLocatorFree("reload", "reload1", 0.05))
			{
				LAi_SetActorTypeNoGroup(NPChar);
				LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
			}
			else ChangeCharacterAddress(NPChar, "none", "");
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

	}
}

void FreeInSea4(aref link, ref NPChar)
{
	dialog.text = StringFromKey("Capitan_ransack_dialog_158");
	link.l1 = StringFromKey("Capitan_ransack_dialog_159");
	link.l1.go = "free_in_sea_4";
}

void FreeInSeaBattleAll(aref link, ref NPChar)
{
	dialog.text = StringFromKey("Capitan_ransack_dialog_160");
	link.l1 = StringFromKey("Capitan_ransack_dialog_161");
	link.l1.go = "free_in_sea_battle_all";

	if (!CheckCharacterPerk(pchar, "Dignity")) //Персонажи без кулачных анимаций не могут махать кулаками
	{
		if (Rand(1) == 0)
			link.l2 = StringFromKey("Capitan_ransack_dialog_162", npchar);
		else
			link.l2 = StringFromKey("Capitan_ransack_dialog_163", npchar);
		link.l2.go = "free_in_sea_battle_pre_punch";
	}
}

void FreeInSeaBattle1(aref link, ref NPChar)
{
	dialog.text = StringFromKey("Capitan_ransack_dialog_164");
	link.l1 = StringFromKey("Capitan_ransack_dialog_165");
	link.l1.go = "free_in_sea_battle_1";
	if (!CheckCharacterPerk(pchar, "Dignity"))
	{
		link.l2 = StringFromKey("Capitan_ransack_dialog_166");
		link.l2.go = "free_in_sea_battle_pre_punch";
	}
}

void Slave3(aref link, ref NPChar)
{
	dialog.text = StringFromKey("Capitan_ransack_dialog_167", npchar);
	link.l1 = StringFromKey("Capitan_ransack_dialog_168");
	link.l1.go = "Slave_3";
}