void ProcessDialogEvent()
{
	ref NPChar, sld;
	ref arItem;
	aref Link, Diag;
	int i, iShipType, iShipGoods;
	int jewelType;
	string sItemName = "";
	string sItem;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Patrol" + locations[FindLocation(npchar.location)].index + "_";
	string sGroup = "PatrolGroup_" + locations[FindLocation(npchar.location)].index;
	string sTemp1, sTemp2;

	switch (Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "exit_fight":
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			Diag.TempNode = "GoodBye";
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();
		break;

		case "First Time":
			LAi_LockFightMode(pchar, false);
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if (pchar.nation == npchar.nation)
				{
					dialog.text = StringFromKey("Patrol_3", RandPhraseSimple(
								StringFromKey("Patrol_1", pchar, XI_ConvertString("Colony" + npchar.city + "Pre")),
								StringFromKey("Patrol_2", pchar, NationNamePeople(sti(pchar.nation)), NationNameInstrumental(sti(npchar.nation)))));
				}
				else
				{
					dialog.text = StringFromKey("Patrol_6", RandPhraseSimple(
								StringFromKey("Patrol_4", pchar, XI_ConvertString("Colony" + npchar.city + "Gen")),
								StringFromKey("Patrol_5", NationNamePeople(sti(pchar.nation)), XI_ConvertString("Colony" + npchar.city + "Pre"))));
				}
				link.l1 = StringFromKey("Patrol_9", RandPhraseSimple(
							StringFromKey("Patrol_7"),
							StringFromKey("Patrol_8")));
				link.l1.go = "exit_fight";
			}
			else
			{
				// проверяем, не казачок ли
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = StringFromKey("Patrol_12", RandPhraseSimple(
								StringFromKey("Patrol_10"),
								StringFromKey("Patrol_11")));
					//==> по лицензии
					if (CheckNationLicence(sti(npchar.nation)))
					{
						link.l1 = StringFromKey("Patrol_13", GetRusNameNationLicence(sti(npchar.nation)));
						link.l1.go = "LicenceOk";
						link.l2 = StringFromKey("Patrol_14", NationNameGenitive(sti(pchar.nation)));
						link.l2.go = CheckSneakByGuards(sti(npchar.nation));
						link.l2 = DeceptionChance_TextWrapper(link.l2);
					}
					else
					{
						//==> по флагу
						link.l1 = StringFromKey("Patrol_15", NationNameGenitive(sti(pchar.nation)));
						link.l1.go = CheckSneakByGuards(sti(npchar.nation));
						link.l1 = DeceptionChance_TextWrapper(link.l1);
					}
				}
				else
				{
					//если негодяй, имеющий НЗГ к дружественной или нейтральной нации
					if (GetCharacterReputation_WithNation(pchar, sti(NPChar.nation)) <= -15)
					{
						PlayerRPGCheck_NationReputation_NotifyFail(sti(NPChar.nation));
						dialog.text = StringFromKey("Patrol_18", RandPhraseSimple(
									StringFromKey("Patrol_16", pchar),
									StringFromKey("Patrol_17", pchar)));
						link.l1 = StringFromKey("Patrol_21", RandPhraseSimple(
									StringFromKey("Patrol_19"),
									StringFromKey("Patrol_20")));
						link.l1.go = "exit_fight";
						break;
					}
					//все проверки прошли, можно и поприветствовать
					dialog.text = StringFromKey("Patrol_25", LinkRandPhrase(
								StringFromKey("Patrol_22", XI_ConvertString("Colony" + npchar.city + "Gen")),
								StringFromKey("Patrol_23", XI_ConvertString("Colony" + npchar.city + "Gen")),
								StringFromKey("Patrol_24", GetAddress_Form(NPChar), XI_ConvertString("Colony" + npchar.city + "Gen"))));
					Link.l1 = StringFromKey("Patrol_29", LinkRandPhrase(
								StringFromKey("Patrol_26"),
								StringFromKey("Patrol_27", pchar, GetAddress_FormToNPC(NPChar)),
								StringFromKey("Patrol_28")));
					Link.l1.go = "Node_2";
				}
			}
		break;

		case "Node_2":
			dialog.text = StringFromKey("Patrol_32", RandPhraseSimple(
						StringFromKey("Patrol_30"),
						StringFromKey("Patrol_31", GetAddress_Form(NPChar))));
			Link.l1 = StringFromKey("Patrol_35", RandPhraseSimple(
						StringFromKey("Patrol_33"),
						StringFromKey("Patrol_34")));
			Link.l1.go = "Node_3";
		break;

		case "Node_3":
			dialog.text = StringFromKey("Patrol_38", RandPhraseSimple(
						StringFromKey("Patrol_36", GetAddress_Form(NPChar)),
						StringFromKey("Patrol_37")));
			Link.l1 = StringFromKey("Patrol_39");
			Link.l1.go = "exit_noFight";
		break;

		case "GoodBye":
			Diag.TempNode = "GoodBye";
			dialog.text = StringFromKey("Patrol_43", LinkRandPhrase(
						StringFromKey("Patrol_40"),
						StringFromKey("Patrol_41"),
						StringFromKey("Patrol_42")));
			Link.l1 = StringFromKey("Patrol_44");
			Link.l1.go = "Exit";
		break;

		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = StringFromKey("Patrol_47", RandPhraseSimple(
						StringFromKey("Patrol_45", pchar),
						StringFromKey("Patrol_46", pchar, GetAddress_Form(npchar))));
			link.l1 = StringFromKey("Patrol_50", RandPhraseSimple(
						StringFromKey("Patrol_48"),
						StringFromKey("Patrol_49")));
			link.l1.go = "exit_fight";
			if (!CheckAttribute(pchar, "questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		case "NotPegYou":
			dialog.text = StringFromKey("Patrol_53", RandPhraseSimple(
						StringFromKey("Patrol_51", GetAddress_Form(NPChar)),
						StringFromKey("Patrol_52")));
			Link.l1 = StringFromKey("Patrol_54");
			Link.l1.go = "exit_noFight";
			if (!CheckAttribute(pchar, "questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(sti(npchar.nation));
			if (iTemp == -1)
			{
				dialog.text = StringFromKey("Patrol_55");
				link.l1 = StringFromKey("Patrol_58", RandPhraseSimple(
							StringFromKey("Patrol_56"),
							StringFromKey("Patrol_57")));
				link.l1.go = "exit_fight";
				TakeNationLicence(sti(npchar.nation));
			}
			if (iTemp == 0)
			{
				dialog.text = StringFromKey("Patrol_59");
				link.l1 = StringFromKey("Patrol_60");
				link.l1.go = "exit_noFight";
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = StringFromKey("Patrol_61", FindDaysString(iTemp), GetAddress_Form(npchar));
				link.l1 = StringFromKey("Patrol_62");
				link.l1.go = "exit_noFight";
			}
			if (iTemp > 10)
			{
				dialog.text = StringFromKey("Patrol_66", LinkRandPhrase(
							StringFromKey("Patrol_63", FindDaysString(iTemp)),
							StringFromKey("Patrol_64", GetAddress_Form(npchar), FindDaysString(iTemp)),
							StringFromKey("Patrol_65", GetAddress_Form(npchar))));
				link.l1 = StringFromKey("Patrol_69", RandPhraseSimple(
							StringFromKey("Patrol_67"),
							StringFromKey("Patrol_68")));
				link.l1.go = "exit_noFight";
			}
		break;

		// генератор "Повод для спешки"
		case "Reason_To_Fast_1":
			LAi_LockFightMode(pchar, false);
			if (Pchar.Location == Pchar.location.from_sea)
			{
				dialog.text = StringFromKey("Patrol_70", pchar);
				link.l1 = StringFromKey("Patrol_71", pchar);
				link.l1.go = "Reason_To_Fast_11";
				link.l2 = StringFromKey("Patrol_72", GetFullName(pchar));
				link.l2.go = "Reason_To_Fast_21";
				link.l3 = StringFromKey("Patrol_73", GetFullName(pchar));
				link.l3.go = "Reason_To_Fast_31";
			}
			else
			{
				Diag.TempNode = "GoodBye";
				dialog.text = StringFromKey("Patrol_74", pchar);
				link.l1 = StringFromKey("Patrol_75");
				link.l1.go = "Reason_To_Fast_Hunter";
			}
		break;

		case "Reason_To_Fast_Hunter":
			DialogExit();
			AddDialogExitQuest("ReasonToFast_MeetHunter");
		break;

		case "Reason_To_Fast_11":
			dialog.text = StringFromKey("Patrol_76", pchar, GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			if (!CheckCharacterItem(pchar, "mapQuest"))
			{
				link.l1 = StringFromKey("Patrol_77");
				link.l1.go = "Reason_To_Fast_12";
			}
			link.l2 = StringFromKey("Patrol_78", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			link.l2.go = "Reason_To_Fast_13";
		break;

		case "Reason_To_Fast_21":
			dialog.text = StringFromKey("Patrol_79");
			link.l1 = StringFromKey("Patrol_80");
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";
		break;

		case "Reason_To_Fast_31":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = StringFromKey("Patrol_81");
			link.l1 = StringFromKey("Patrol_82");
			link.l1.go = "Reason_To_Fast_GoodBye_0";
			pchar.questTemp.ReasonToFast = "MeetPatrolFail";
		break;

		case "Reason_To_Fast_12":
			jewelType = sti(pchar.questTemp.ReasonToFast.p4);
			pchar.questTemp.ReasonToFast.item = "jewelry" + jewelType;
			sItem = "jewelry" + jewelType;
			switch (jewelType)
			{
				case 1:
					sItemName = StringFromKey("Patrol_83");
				break;
				case 2:
					sItemName = StringFromKey("Patrol_84");
				break;
				case 3:
					sItemName = StringFromKey("Patrol_85");
				break;
				case 4:
					sItemName = StringFromKey("Patrol_86");
				break;
			}
			pchar.questTemp.ReasonToFast.jewType = sItemName;
			dialog.text = StringFromKey("Patrol_87", sItemName);
			link.l1 = StringFromKey("Patrol_88", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			link.l1.go = "Reason_To_Fast_14";
			if (GetCharacterItem(pchar, pchar.questTemp.ReasonToFast.item) >= 30)
			{
				link.l2 = StringFromKey("Patrol_89");
				link.l2.go = "Reason_To_Fast_15";
			}
		break;

		case "Reason_To_Fast_13":
			dialog.text = StringFromKey("Patrol_90");
			link.l1 = StringFromKey("Patrol_91");
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";
		break;

		case "Reason_To_Fast_14":
			dialog.text = StringFromKey("Patrol_92", FindMoneyString(sti(pchar.questTemp.ReasonToFast.p5)));
			link.l1 = StringFromKey("Patrol_93");
			link.l1.go = "Reason_To_Fast_16";
			if (makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				link.l2 = StringFromKey("Patrol_94");
				link.l2.go = "Reason_To_Fast_17";
			}
			link.l3 = StringFromKey("Patrol_95");
			link.l3.go = "Reason_To_Fast_18";
			AddQuestRecord("ReasonToFast", "9");
			AddQuestUserData("ReasonToFast", "sText", pchar.questTemp.ReasonToFast.jewType);
		break;

		case "Reason_To_Fast_15":
			TakeNItems(pchar, pchar.questTemp.ReasonToFast.item, -30);
			dialog.text = StringFromKey("Patrol_96", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			link.l1 = StringFromKey("Patrol_97");
			link.l1.go = "Reason_To_Fast_15_1";
		break;

		case "Reason_To_Fast_15_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//fix
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			DialogExit();
			AddQuestRecord("ReasonToFast", "10");
			AddQuestUserData("ReasonToFast", "sName", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			pchar.questTemp.ReasonToFast = "PatrolSuccess_2";
			GiveItem2Character(pchar, "mapQuest");
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером 
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Reason_To_Fast_16":
			dialog.text = StringFromKey("Patrol_98", pchar, GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_INS));
			link.l1 = StringFromKey("Patrol_99");
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";
		break;

		case "Reason_To_Fast_17":
			pchar.questTemp.ReasonToFast = "PatrolSuccess_1";
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.questTemp.ReasonToFast.p5)));
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха
			if (CheckAttribute(pchar, "questTemp.ReasonToFast.chain")) DeleteAttribute(pchar, "questTemp.ReasonToFast.chain");
			if (CheckAttribute(pchar, "questTemp.ReasonToFast.ShipName")) DeleteAttribute(pchar, "questTemp.ReasonToFast.ShipName");
			if (CheckAttribute(pchar, "questTemp.ReasonToFast.ShipTypeName")) DeleteAttribute(pchar, "questTemp.ReasonToFast.TypeName");
			switch (sti(pchar.questTemp.ReasonToFast.target))
			{
				case 0: // корабль с товаром
					sTemp1 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					iShipType = ReasonToFast_GetVictimShipType();
					iShipGoods = ReasonToFast_GetVictimShipGoods();
					dialog.text = StringFromKey("Patrol_100", GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipTypeName), sTemp1, GetGoodsNameAlt(iShipGoods));
					link.l1 = StringFromKey("Patrol_101", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT));
					link.l1.go = "Reason_To_Fast_GoodBye_0";
					pchar.questTemp.ReasonToFast.chain = "A0";
					pchar.questTemp.ReasonToFast.ShipName = sTemp1;
					DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером
					AddQuestRecord("ReasonToFast", "11");
					AddQuestUserData("ReasonToFast", "sShipType", pchar.questTemp.ReasonToFast.ShipTypeName);
					AddQuestUserData("ReasonToFast", "sShipName", sTemp1);
					AddQuestUserData("ReasonToFast", "sGoodsName", GetGoodsNameAlt(iShipGoods));
					ReasonToFast_GenerateVictimShip(iShipType, iShipGoods);
				break;

				case 1: // сокровища губернатора
					switch (rand(3))
					{
						case 0:
							sTemp1 = StringFromKey("Patrol_102");
						break;
						case 1:
							sTemp1 = StringFromKey("Patrol_103");
						break;
						case 2:
							sTemp1 = StringFromKey("Patrol_104");
						break;
						case 3:
							sTemp1 = StringFromKey("Patrol_105");
						break;
					}
					switch (rand(3))
					{
						case 0:
							sTemp2 = StringFromKey("Patrol_106");
						break;
						case 1:
							sTemp2 = StringFromKey("Patrol_107");
						break;
						case 2:
							sTemp2 = StringFromKey("Patrol_108");
						break;
						case 3:
							sTemp2 = StringFromKey("Patrol_109");
						break;
					}
					pchar.questTemp.ReasonToFast.password = sTemp2;
					sTemp2 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					dialog.text = StringFromKey("Patrol_110", sTemp1, pchar.questTemp.ReasonToFast.password, sTemp2);
					link.l1 = StringFromKey("Patrol_111", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT));
					link.l1.go = "Reason_To_Fast_GoodBye_0";
					pchar.questTemp.ReasonToFast.chain = "A1";
					AddQuestRecord("ReasonToFast", "12");
					pchar.questTemp.ReasonToFast.ShipName = sTemp2;
					DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером

					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1 = "Timer";
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.function = "ReasonToFast_ClearLakey";
				break;
			}
		break;

		case "Reason_To_Fast_18":
			if (makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				dialog.text = StringFromKey("Patrol_112");
				link.l1 = StringFromKey("Patrol_113");
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";
			}
			else
			{
				dialog.text = StringFromKey("Patrol_114", pchar);
				link.l1 = StringFromKey("Patrol_115");
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";
			}
		break;

		case "Reason_To_Fast_GoodBye_0":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//fix
			LAi_SetPlayerType(pchar);
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "Reason_To_Fast_GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			pchar.quest.RemovePatrolFromShore.win_condition.l1 = "ExitFromLocation";
			pchar.quest.RemovePatrolFromShore.win_condition.l1.location = pchar.location;
			pchar.quest.RemovePatrolFromShore.function = "ReasonToFast_DeletePatrolFromShore";
			DialogExit();
		break;

		case "Reason_To_Fast_GoodBye":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = StringFromKey("Patrol_116");
			link.l1 = StringFromKey("Patrol_117");
			link.l1.go = "Exit";
		break;

		case "Reason_To_Fast_ExitFight":
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY);

			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять

			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			if (pchar.questTemp.ReasonToFast == "PatrolAngry")
			{
				sld = CharacterFromID("ReasonToFast_Hunter");
				if (sld != -1)
				{
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, sGroup);
				}
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors");
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Reason_To_Fast_AfterHunter1":
			dialog.text = StringFromKey("Patrol_118");
			link.l1 = StringFromKey("Patrol_119");
			link.l1.go = "Reason_To_Fast_11";
			link.l2 = StringFromKey("Patrol_120", pchar);
			link.l2.go = "Reason_To_Fast_AfterHunter2";
		break;

		case "Reason_To_Fast_AfterHunter2":
			dialog.text = StringFromKey("Patrol_121", pchar);
			link.l1 = StringFromKey("Patrol_122");
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfterHunter";
		break;

		case "Reason_To_Fast_AfterHunter3":
			dialog.text = StringFromKey("Patrol_123", pchar);
			link.l1 = StringFromKey("Patrol_124");
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAngry";
		break;
		// генератор "Повод для спешки"
	}
}
