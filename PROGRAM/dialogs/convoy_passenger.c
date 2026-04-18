//пассажир на доставку
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag, arAll;
	string NPC_Meeting, sTemp, sTitle, sTavern;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	dialogDisable = false;

	switch (Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "prepare_convoy_quest":
		//			if (isBadReputation(pchar, 40))
			if (PlayerRPGCheck_BadReputation(40, false))
			{
				dialog.text = StringFromKey("convoy_passenger_3", RandPhraseSimple(
							StringFromKey("convoy_passenger_1", pchar),
							StringFromKey("convoy_passenger_2")));
				link.l1 = StringFromKey("convoy_passenger_6", RandPhraseSimple(
							StringFromKey("convoy_passenger_4"),
							StringFromKey("convoy_passenger_5")));
				link.l1.go = "convoy_refused";
			}
			else
			{
				dialog.text = StringFromKey("convoy_passenger_7", TimeGreeting(), GetAddress_Form(NPChar), GetFullName(NPChar));
				link.l1 = StringFromKey("convoy_passenger_8");
				link.l1.go = "prepare_convoy_quest_3";
			}
		break;

		case "prepare_convoy_quest_3":
			LookShipPassenger();
			GenerateConvoyPassengerQuest(npchar);
			dialog.text = StringFromKey("convoy_passenger_9", XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen"), XI_ConvertString(GetIslandNameByCity(npchar.GenQuest.GetPassenger_Destination) + "Pre"), FindDaysString(sti(npchar.GenQuest.GetPassenger_Time)), FindMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
			link.l1 = StringFromKey("convoy_passenger_10", pchar);
			link.l1.go = "convoy_agreeded";
			link.l2 = StringFromKey("convoy_passenger_11");
			link.l2.go = "convoy_refused";
		break;

		case "convoy_refused":
			GeneratorPassenger(1);
			chrDisableReloadToLocation = false;
			sTemp = npchar.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_dead";
			pchar.quest.(sTemp).over = "yes";
			DeleteAttribute(npchar, "GenQuest.GetPassenger");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocationNoCheck(npchar, "reload", LocatorToSendConvoyNpc(npchar), "none", "", "", "", 5.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "convoy_agreeded":
			GeneratorPassenger(2);
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "1");
			sTemp = StringFromKey("convoy_passenger_12", XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen"), XI_ConvertString(GetIslandNameByCity(npchar.GenQuest.GetPassenger_Destination) + "Pre"));
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sDay", FindDaysString(sti(npchar.GenQuest.GetPassenger_Time)));
			AddQuestUserData(sTitle, "sMoney", FindMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
			// по городу вернём его таверну
			sTavern = npchar.GenQuest.GetPassenger_Destination + "_tavern";
			sTemp = npchar.id + "_complited";
			pchar.quest.(sTemp).win_condition.l1 = "location";
			pchar.quest.(sTemp).win_condition.l1.location = sTavern;
			pchar.quest.(sTemp).win_condition = "AllPassangersComplited";
			pchar.quest.(sTemp).Idx = npchar.index;
			if (rand(2) == 1) TraderHunterOnMap();
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocationNoCheck(npchar, "reload", LocatorToSendConvoyNpc(npchar), "none", "", "", "", 5.0);
			Diag.CurrentNode = "convoy_DeskTalk";
			DialogExit();
		break;

		case "complete_convoy_quest":
			dialog.text = StringFromKey("convoy_passenger_13");
			Link.l1 = StringFromKey("convoy_passenger_14");
			link.l1.go = "complete_convoy_quest_1";
		break;

		case "complete_convoy_quest_1":
		//слухи
			AddSimpleRumour(
						StringFromKey("convoy_passenger_18", LinkRandPhrase(
								StringFromKey("convoy_passenger_15", pchar, GetFullName(npchar), GetMainCharacterNameDat(), XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen")),
								StringFromKey("convoy_passenger_16", pchar, GetFullName(npchar), GetMainCharacterNameDat(), XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen")),
								StringFromKey("convoy_passenger_17", GetFullName(npchar)))), sti(npchar.nation), 40, 1);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			//--> смотрим Deck
			makearef(arAll, pchar.GenQuest.ConvoyPassenger);
			if (GetAttributesNum(arAll) == 0) pchar.quest.ConvoyMapPassenger.over = "yes";
			//<-- смотрим Deck
			AddMoneyToCharacter(pchar, makeint(npchar.GenQuest.GetPassenger_Money));
			ChangeCharacterReputation(pchar, 1);
			RemovePassenger(PChar, npchar);
			OfficersReaction("good");
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "4");
			CloseQuestHeader(sTitle);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocationNoCheck(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "convoy_DeskTalk":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("convoy_passenger_22", LinkRandPhrase(
								StringFromKey("convoy_passenger_19", RandSwear(), XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc")),
								StringFromKey("convoy_passenger_20", RandSwear(), XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen")),
								StringFromKey("convoy_passenger_21", RandSwear(), XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen")))),
						StringFromKey("convoy_passenger_25", RandPhraseSimple(
								StringFromKey("convoy_passenger_23", XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen")),
								StringFromKey("convoy_passenger_24", XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen")))),
						StringFromKey("convoy_passenger_28", RandPhraseSimple(
								StringFromKey("convoy_passenger_26", RandSwear(), XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc")),
								StringFromKey("convoy_passenger_27", XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Acc")))),
						StringFromKey("convoy_passenger_29"), "block", 0, npchar, Dialog.CurrentNode);
			if (sti(npchar.GenQuest.GetPassenger_Money) > 100)
			{
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("convoy_passenger_32", RandPhraseSimple(
									StringFromKey("convoy_passenger_30", pchar),
									StringFromKey("convoy_passenger_31", GetAddress_FormToNPC(NPChar)))),
							StringFromKey("convoy_passenger_35", RandPhraseSimple(
									StringFromKey("convoy_passenger_33", pchar),
									StringFromKey("convoy_passenger_34"))),
							StringFromKey("convoy_passenger_38", RandPhraseSimple(
									StringFromKey("convoy_passenger_36", pchar),
									StringFromKey("convoy_passenger_37"))),
							StringFromKey("convoy_passenger_39", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
				link.l1.go = "convoy_DeskTalk_1";
			}
			link.l2 = HeroStringReactionRepeat(
						StringFromKey("convoy_passenger_42", RandPhraseSimple(
								StringFromKey("convoy_passenger_40", pchar),
								StringFromKey("convoy_passenger_41"))),
						StringFromKey("convoy_passenger_43"),
						StringFromKey("convoy_passenger_44"),
						StringFromKey("convoy_passenger_45", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l2.go = "convoy_Prison_1";
			pchar.quest.Munity = "Deads"; //дверцы откроем
			LAi_LockFightMode(pchar, false);
			Log_SetActiveAction("Nothing");
		break;

		case "convoy_DeskTalk_1":
			dialog.text = StringFromKey("convoy_passenger_49", LinkRandPhrase(
						StringFromKey("convoy_passenger_46"),
						StringFromKey("convoy_passenger_47"),
						StringFromKey("convoy_passenger_48")));
			Link.l1 = StringFromKey("convoy_passenger_53", LinkRandPhrase(
						StringFromKey("convoy_passenger_50"),
						StringFromKey("convoy_passenger_51"),
						StringFromKey("convoy_passenger_52")));
			link.l1.go = "convoy_DeskTalk_2";
		break;

		case "convoy_DeskTalk_2":
			dialog.text = StringFromKey("convoy_passenger_56", RandPhraseSimple(
						StringFromKey("convoy_passenger_54"),
						StringFromKey("convoy_passenger_55")));
			Link.l1 = StringFromKey("convoy_passenger_57");
			link.l1.go = "convoy_DeskTalk_exit";
		break;

		case "convoy_DeskTalk_exit":
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			sTemp = npchar.id + "_TimeOver";
			SetTimerCondition(sTemp, 0, 0, 7, false);
			pchar.quest.(sTemp).win_condition = "AllPassangersTimeOver";
			pchar.quest.(sTemp).Idx = npchar.index;
			npchar.GenQuest.GetPassenger_Money = makeint(sti(npchar.GenQuest.GetPassenger_Money) / 1.5);
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "5");
			AddQuestUserData(sTitle, "sMoney", FindMoneyString(sti(npchar.GenQuest.GetPassenger_Money)));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocationNoCheck(npchar, "reload", "reload1", "none", "", "", "", 5.0);
			Diag.CurrentNode = "convoy_DeskTalk";
			DialogExit();
		break;

		case "convoy_Prison_1":
			dialog.text = StringFromKey("convoy_passenger_58", RandSwear());
			if (GetPrisonerQty() < PRISONER_MAX)
			{
				Link.l1 = StringFromKey("convoy_passenger_59");
				link.l1.go = "convoy_Prison_2";
			}
			Link.l2 = StringFromKey("convoy_passenger_60");
			link.l2.go = "convoy_DeskTalk_1";
		break;

		case "convoy_Prison_2":
			dialog.text = StringFromKey("convoy_passenger_61", pchar, RandSwear());
			Link.l1 = StringFromKey("convoy_passenger_62");
			link.l1.go = "convoy_Prison_3";
		break;

		case "convoy_Prison_3":
			AddSimpleRumour(
						StringFromKey("convoy_passenger_66", LinkRandPhrase(
								StringFromKey("convoy_passenger_63", pchar, GetFullName(pchar), GetFullName(npchar)),
								StringFromKey("convoy_passenger_64", pchar, GetFullName(pchar), GetFullName(npchar)),
								StringFromKey("convoy_passenger_65", pchar, GetFullName(npchar), XI_ConvertString("Colony" + npchar.GenQuest.GetPassenger_Destination + "Gen")))), sti(npchar.nation), 40, 1);
			RemovePassenger(PChar, NPChar);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocationNoCheck(NPChar, "reload", "reload1", "none", "", "", "", 5.0);
			ChangeCharacterReputation(pchar, -5);
			OfficersReaction("bad");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", 10 + rand(10));// награда
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + npchar.id); //извлекаем из структуры недовольных
			sTemp = npchar.id + "_complited";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_dead";
			pchar.quest.(sTemp).over = "yes";
			sTemp = npchar.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTitle = npchar.index + "convoy_passenger";
			AddQuestRecordEx(sTitle, "Gen_convoy_passenger", "6");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader(sTitle);
			AddCharacterExpToSkill(pchar, "COMMERCE", 25);
			SetCharToPrisoner(NPChar);
			DialogExit();
		break;
	}
}

void GenerateConvoyPassengerQuest(ref npchar)
{
	int iTradeMoney, iNation, irank;
	string sTemp, sR;

	iNation = GetRelation2BaseNation(sti(npchar.nation)); //если привезти нужно во вражеский город
	npchar.GenQuest.GetPassenger_Destination = TEV.GenQuest_DestinationCity;
	int daysQty = GetMaxDaysFromColony2Colony(pchar.GenQuest.GetPassenger_City, TEV.GenQuest_DestinationCity);
	if (sti(daysQty) > 14) daysQty = 14;
	npchar.GenQuest.GetPassenger_Time = makeint(sti(daysQty) * (frand(1.3) + 0.7));
	iTradeMoney = (sti(daysQty) * 500 * sti(pchar.GenQuest.GetPassenger.Shipmod) + rand(100)) * sti(daysQty) / sti(npchar.GenQuest.GetPassenger_Time);
	if (iNation == RELATION_ENEMY && sti(npchar.nation != PIRATE)) iTradeMoney = makeint(iTradeMoney * 1.3); //то размер награды увеличивается
	npchar.GenQuest.GetPassenger_Money = iTradeMoney;
	DeleteAttribute(&TEV, "GenQuest_DestinationCity");

	sTemp = npchar.id + "_TimeOver";
	SetTimerCondition(sTemp, 0, 0, sti(npchar.GenQuest.GetPassenger_Time), false);
	pchar.quest.(sTemp).win_condition = "AllPassangersTimeOver";
	pchar.quest.(sTemp).Idx = npchar.index;

	sTemp = npchar.id + "_dead";
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).win_condition = "AllPassangersDead";
	pchar.quest.(sTemp).Idx = npchar.index;
}

void LookShipPassenger()
{
	switch (makeint(7 - sti(RealShips[sti(Pchar.Ship.Type)].Class)))
	{
		case 0:
			pchar.GenQuest.GetPassenger.Shipmod = 0.8;
		break;
		case 1:
			pchar.GenQuest.GetPassenger.Shipmod = 1;
		break;
		case 2:
			pchar.GenQuest.GetPassenger.Shipmod = 1.2;
		break;
		case 3:
			pchar.GenQuest.GetPassenger.Shipmod = 1.5;
		break;
		case 4:
			pchar.GenQuest.GetPassenger.Shipmod = 2.2;
		break;
		case 5:
			pchar.GenQuest.GetPassenger.Shipmod = 3;
		break;
		case 6:
			pchar.GenQuest.GetPassenger.Shipmod = 4.5;
		break;
	}
}

void GeneratorPassenger(int n)
{
	ref rLoc = &Locations[FindLocation(pchar.location)];

	if (CheckAttribute(rLoc, "id.label"))
	{
		string str;

		if (HasStr(rLoc.id.label, "Tavern"))
			str = "ArtOfDeals.Tavern.Passenger";

		if (HasStr(rLoc.id.label, "PortOffice"))
			str = "ArtOfDeals.PortOffice.Passenger";

		if (str != "")
		{
			if (!CheckAttribute(&TEV, str))
				TEV.(str) = "0";

			TEV.(str) = sti(TEV.(str)) + n;
		}
	}
}
