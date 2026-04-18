//#include "DIALOGS\convoy_traider.h"
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting;

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
				dialog.text = StringFromKey("convoy_traider_3", RandPhraseSimple(
							StringFromKey("convoy_traider_1", pchar),
							StringFromKey("convoy_traider_2")));
				link.l1 = StringFromKey("convoy_traider_6", RandPhraseSimple(
							StringFromKey("convoy_traider_4"),
							StringFromKey("convoy_traider_5")));
				link.l1.go = "convoy_refused";
			}
			else
			{
				dialog.text = StringFromKey("convoy_traider_7", TimeGreeting(), GetAddress_Form(NPChar), GetFullName(NPChar));
				link.l1 = StringFromKey("convoy_traider_8", pchar);
				link.l1.go = "prepare_convoy_quest_2";
			}
		break;

		case "prepare_convoy_quest_2":
			dialog.text = StringFromKey("convoy_traider_9");
			link.l1 = StringFromKey("convoy_traider_10");
			link.l1.go = "prepare_convoy_quest_3";
		break;

		case "prepare_convoy_quest_3":
			LookShipConvoy();
			GenerateConvoyQuest(npchar);
			dialog.text = StringFromKey("convoy_traider_11", XI_ConvertString("Colony" + pchar.quest.destination + "Gen"), XI_ConvertString(GetIslandNameByCity(pchar.quest.destination) + "Pre"), FindDaysString(sti(pchar.ConvoyQuest.iDay)), FindMoneyString(sti(pchar.ConvoyQuest.convoymoney)));
			link.l1 = StringFromKey("convoy_traider_12", pchar);
			link.l1.go = "convoy_agreeded";
			link.l2 = StringFromKey("convoy_traider_13");
			link.l2.go = "convoy_refused";
		break;

		case "convoy_refused":
			GeneratorConvoy(1);
			chrDisableReloadToLocation = false;
			npchar.LifeDay = 0;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("convoy_refused");
		break;

		case "convoy_agreeded":
			GeneratorConvoy(2);
			chrDisableReloadToLocation = false;
			pchar.convoy_quest = pchar.quest.destination;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("convoy_agreeded");
		break;

		case "complete_convoy_quest":
			dialog.text = StringFromKey("convoy_traider_14");
			Link.l1 = StringFromKey("convoy_traider_15");
			link.l1.go = "exit";
			//слухи
			AddSimpleRumour(
						StringFromKey("convoy_traider_19", LinkRandPhrase(
								StringFromKey("convoy_traider_16", GetFullName(npchar), GetMainCharacterNameDat()),
								StringFromKey("convoy_traider_17", pchar, GetFullName(npchar), GetMainCharacterNameDat(), XI_ConvertString("Colony" + pchar.quest.destination + "Gen")),
								StringFromKey("convoy_traider_18", GetFullName(npchar)))), sti(npchar.nation), 40, 1);
			pchar.quest.generate_convoy_quest_progress = "completed";
			chrDisableReloadToLocation = false;
			npchar.LifeDay = 0;
			AddDialogExitQuest("convoy_refused");
		break;
	}
}

// boal 03.05.04 квест сопроводить торговца -->
void GenerateConvoyQuest(ref npchar)
{
	int iTradeMoney, iNation;

	DeleteAttribute(NPChar, "Ship");
	SetShipToFantom(NPChar, "trade", true);

	iNation = GetRelation2BaseNation(sti(npchar.nation)); //если привезти нужно во вражеский город
	int daysQty = GetMaxDaysFromColony2Colony(pchar.ConvoyQuest.City, pchar.quest.destination);
	if (sti(daysQty) > 14) daysQty = 14;
	pchar.ConvoyQuest.iDay = makeint(sti(daysQty) * (frand(1.3) + 0.7));
	iTradeMoney = (sti(daysQty) * 600 * sti(pchar.GenQuest.Convoy.Shipmod) + rand(100)) * sti(daysQty) / sti(pchar.ConvoyQuest.iDay);
	if (iNation == RELATION_ENEMY && sti(npchar.nation != PIRATE)) iTradeMoney = makeint(iTradeMoney * 1.4); //то размер награды увеличивается
	pchar.ConvoyQuest.convoymoney = iTradeMoney;

	//Log_TestInfo(FindDaysString(sti(daysQty)));
	//Log_TestInfo(pchar.quest.destination);
	//Log_TestInfo(pchar.ConvoyQuest.City);

	SetTimerCondition("generate_convoy_quest_timer", 0, 0, sti(pchar.ConvoyQuest.iDay), false);

	pchar.quest.generate_convoy_quest_progress = "begin";

	pchar.quest.generate_convoy_quest_failed.win_condition.l1 = "NPC_Death";
	pchar.quest.generate_convoy_quest_failed.win_condition.l1.character = "QuestTrader";
	pchar.quest.generate_convoy_quest_failed.win_condition = "generate_convoy_quest_failed";
}

void LookShipConvoy()
{
	switch (makeint(7 - sti(RealShips[sti(Pchar.Ship.Type)].Class)))
	{
		case 0:
			pchar.GenQuest.Convoy.Shipmod = 0.7;
		break;
		case 1:
			pchar.GenQuest.Convoy.Shipmod = 1;
		break;
		case 2:
			pchar.GenQuest.Convoy.Shipmod = 1.2;
		break;
		case 3:
			pchar.GenQuest.Convoy.Shipmod = 1.5;
		break;
		case 4:
			pchar.GenQuest.Convoy.Shipmod = 2.2;
		break;
		case 5:
			pchar.GenQuest.Convoy.Shipmod = 3;
		break;
		case 6:
			pchar.GenQuest.Convoy.Shipmod = 4.5;
		break;
	}
}

void GeneratorConvoy(int n)
{
	ref rLoc = &Locations[FindLocation(pchar.location)];

	if (CheckAttribute(rLoc, "id.label"))
	{
		string str;

		if (HasStr(rLoc.id.label, "Tavern"))
			str = "ArtOfDeals.Tavern.Convoy";

		if (HasStr(rLoc.id.label, "PortOffice"))
			str = "ArtOfDeals.PortOffice.Convoy";

		if (str != "")
		{
			if (!CheckAttribute(&TEV, str))
				TEV.(str) = "0";

			TEV.(str) = sti(TEV.(str)) + n;
		}
	}
}
