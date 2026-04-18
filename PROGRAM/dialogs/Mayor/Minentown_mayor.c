#include "DIALOGS\Slavery\Common_Slavery.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sLoc;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonSlavery(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = StringFromKey("Minentown_mayor_1", pchar, TimeGreeting(), GetFullName(npchar), NationKingsName(npchar), GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Minentown_mayor_2", pchar);
				link.l1.go = "info";
				link.l2 = StringFromKey("Minentown_mayor_3", pchar);
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				break;
			}
			dialog.text = StringFromKey("Minentown_mayor_4", pchar);
			link.l1 = StringFromKey("Minentown_mayor_5");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			//поиск Тизера в рудниках
			if (CheckAttribute(pchar, "questTemp.LSC") && pchar.questTemp.LSC == "SearchSlavesLSC")
			{
				link.l3 = StringFromKey("Minentown_mayor_6");
				link.l3.go = "SearchSlavesLSC_1";
			}
			//возволение Тизера
			if (CheckAttribute(pchar, "questTemp.LSC") && pchar.questTemp.LSC == "SaveTizerDen")
			{
				dialog.text = StringFromKey("Minentown_mayor_28");
				link.l1 = StringFromKey("Minentown_mayor_29");
				link.l1.go = "SaveTizerDen_1";
			}
		break;

		case "info":
			dialog.text = StringFromKey("Minentown_mayor_7"); //\nТак что если вы сможете привезти нам рабов - мы купим их у вас в обмен на самородки. По этому вопросу вам нужно будет обратиться непосредственно к старшему горному инженеру, его всегда можно найти в шахте
			link.l1 = StringFromKey("Minentown_mayor_8");
			link.l1.go = "exit";
		break;

		//поиск Тизера в рудниках
		case "SearchSlavesLSC_1":
			dialog.text = StringFromKey("Minentown_mayor_9");
			link.l1 = StringFromKey("Minentown_mayor_10");
			link.l1.go = "SearchSlavesLSC_2";
		break;
		case "SearchSlavesLSC_2":
			dialog.text = StringFromKey("Minentown_mayor_11");
			link.l1 = StringFromKey("Minentown_mayor_12");
			link.l1.go = "SearchSlavesLSC_3";
		break;
		case "SearchSlavesLSC_3":
			dialog.text = StringFromKey("Minentown_mayor_13");
			link.l1 = "...";
			link.l1.go = "SearchSlavesLSC_4";
		break;
		case "SearchSlavesLSC_4":
			dialog.text = StringFromKey("Minentown_mayor_14");
			link.l1 = StringFromKey("Minentown_mayor_15");
			link.l1.go = "SearchSlavesLSC_5";
		break;
		case "SearchSlavesLSC_5":
			dialog.text = StringFromKey("Minentown_mayor_16");
			link.l1 = StringFromKey("Minentown_mayor_17");
			link.l1.go = "SearchSlavesLSC_6";
		break;
		case "SearchSlavesLSC_6":
			dialog.text = StringFromKey("Minentown_mayor_18");
			link.l1 = StringFromKey("Minentown_mayor_19", GetFullName(npchar));
			link.l1.go = "exit";
			pchar.questTemp.LSC = "GoToTizerLSC";
			AddQuestRecord("ISS_PoorsMurder", "32");
			sld = GetCharacter(NPC_GenerateCharacter("TizerDenLSC", "Tither_monk", "man", "man", 7, PIRATE, -1, false)); //TODO отдельная моделька для Тизера
			sld.dialog.filename = "Quest\LostShipsCity\TizerDen.c";
			sld.name = FindPersonalName("Tizer_name");
			sld.lastname = FindPersonalName("Tizer_lastname");
			sld.greeting = "monk";
			LAi_SetImmortal(sld, true);
			sld.TizerBadRep = 0; //счетчик ошибок
			sld.TizerGoodRep = 0; //счетчик для крит. успеха
			sld.talker = 10;
			AddLandQuestMark_Main(sld, "ISS_PoorsMurder");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SmallHouse_Jungle", "barmen", "stay");
		break;

		//возволение Тизера
		case "SaveTizerDen_1":
			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
			AddLandQuestMark_Main(CharacterFromID("TizerDenLSC"), "ISS_PoorsMurder");
			bool bCheck = PlayerRPGCheck_SPECIAL(SPECIAL_C, 4) && CheckCharacterItem(pchar, "HolFakeLicence");
			dialog.text = StringFromKey("Minentown_mayor_30");
			if (bCheck || PlayerRPGCheck_SPECIAL(SPECIAL_C, 8))
			{
				link.l1 = StringFromKey("Minentown_mayor_31");
				link.l1.go = "SaveTizerDen_3";
			}
			else
			{
				link.l1 = StringFromKey("Minentown_mayor_32");
				link.l1.go = "SaveTizerDen_2";
			}
		break;
		case "SaveTizerDen_2":
			dialog.text = StringFromKey("Minentown_mayor_33");
			link.l1 = StringFromKey("Minentown_mayor_34");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "MayorFiledLSC";
			AddLandQuestMark_Main(CharacterFromID("TizerDenLSC"), "ISS_PoorsMurder");
		break;
		case "SaveTizerDen_3":
			dialog.text = StringFromKey("Minentown_mayor_35");
			link.l1 = StringFromKey("Minentown_mayor_36");
			link.l1.go = "SaveTizerDen_4";
		break;
		case "SaveTizerDen_4":
			dialog.text = StringFromKey("Minentown_mayor_37");
			link.l1 = StringFromKey("Minentown_mayor_38");
			link.l1.go = "SaveTizerDen_5";
		break;
		case "SaveTizerDen_5":
			dialog.text = StringFromKey("Minentown_mayor_39");
			link.l1 = StringFromKey("Minentown_mayor_40");
			link.l1.go = "SaveTizerDen_6";
		break;
		case "SaveTizerDen_6":
			dialog.text = StringFromKey("Minentown_mayor_41");
			link.l1 = StringFromKey("Minentown_mayor_42");
			link.l1.go = "SaveTizerDen_7";
		break;
		case "SaveTizerDen_7":
			dialog.text = StringFromKey("Minentown_mayor_43");
			link.l1 = StringFromKey("Minentown_mayor_44");
			link.l1.go = "SaveTizerDen_8";
		break;
		case "SaveTizerDen_8":
			dialog.text = StringFromKey("Minentown_mayor_45");
			link.l1 = StringFromKey("Minentown_mayor_46");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "MayorApprovedLSC";
			RemoveCharacterGoods(pchar, GOOD_POWDER, -100);
			AddLandQuestMark_Main(CharacterFromID("TizerDenLSC"), "ISS_PoorsMurder");
		break;

		case "AhtungMinetown":
			dialog.text = StringFromKey("Minentown_mayor_47", GetFullName(pchar));
			link.l1 = StringFromKey("Minentown_mayor_48");
			link.l1.go = "AhtungMinetown_1";
		break;
		case "AhtungMinetown_1":
			dialog.text = StringFromKey("Minentown_mayor_49");
			link.l1 = StringFromKey("Minentown_mayor_50");
			link.l1.go = "AhtungMinetown_2";
		break;
		case "AhtungMinetown_2":
			dialog.text = StringFromKey("Minentown_mayor_51");
			link.l1 = StringFromKey("Minentown_mayor_52");
			link.l1.go = "AhtungMinetown_3";
		break;
		case "AhtungMinetown_3":
			dialog.text = StringFromKey("Minentown_mayor_53");
			link.l1 = StringFromKey("Minentown_mayor_54");
			link.l1.go = "AhtungMinetown_4";
		break;
		case "AhtungMinetown_4":
			dialog.text = StringFromKey("Minentown_mayor_55");
			link.l1 = StringFromKey("Minentown_mayor_56");
			link.l1.go = "AhtungMinetown_6";
			link.l2 = StringFromKey("Minentown_mayor_57");
			link.l2.go = "AhtungMinetown_5";
		break;
		case "AhtungMinetown_5":
			dialog.text = StringFromKey("Minentown_mayor_58");
			link.l1 = StringFromKey("Minentown_mayor_59");
			link.l1.go = "AhtungMinetown_6";
		break;
		case "AhtungMinetown_6":
			dialog.text = StringFromKey("Minentown_mayor_60");
			link.l1 = StringFromKey("Minentown_mayor_61");
			link.l1.go = "AhtungMinetown_7";
		break;
		case "AhtungMinetown_7":
			dialog.text = StringFromKey("Minentown_mayor_62");
			link.l1 = StringFromKey("Minentown_mayor_63");
			link.l1.go = "AhtungMinetown_8";
		break;
		case "AhtungMinetown_8":
			dialog.text = StringFromKey("Minentown_mayor_64");
			link.l1 = StringFromKey("Minentown_mayor_65");
			link.l1.go = "exit";
			AddDialogExitQuest("AhtungMinetown");
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = StringFromKey("Minentown_mayor_23", LinkRandPhrase(
						StringFromKey("Minentown_mayor_20", pchar),
						StringFromKey("Minentown_mayor_21", pchar),
						StringFromKey("Minentown_mayor_22", pchar)));
			link.l1 = StringFromKey("Minentown_mayor_27", LinkRandPhrase(
						StringFromKey("Minentown_mayor_24"),
						StringFromKey("Minentown_mayor_25"),
						StringFromKey("Minentown_mayor_26")));
			link.l1.go = "fight";
		break;

		case "fight":
			Pchar.quest.ArestInResidenceEnd.win_condition.l1 = "ExitFromLocation";
			Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
			Pchar.quest.ArestInResidenceEnd.win_condition = "ArestInResidenceEnd";
			Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
				LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
