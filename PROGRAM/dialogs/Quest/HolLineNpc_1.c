// диалоговый файл №1 на голландку
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	float locx, locy, locz;

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("HolLineNpc_1_1");
			link.l1 = StringFromKey("HolLineNpc_1_2");
			link.l1.go = "exit";

			//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
			if (npchar.id == "Bandit2" && pchar.questTemp.State == "SeekChumakeiro_ToAaronHouse")// перехват на бандитов, грябящих Аарона
			{
				dialog.text = StringFromKey("HolLineNpc_1_3", pchar);
				link.l1 = StringFromKey("HolLineNpc_1_4", GetFullName(pchar));
				link.l1.go = "Step_H1_1";
			}// Аарон собственной персоной, после драки с грабителями
			if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekChumakeiro_ToAaronHouse")
			{
				dialog.text = StringFromKey("HolLineNpc_1_5");
				link.l1 = StringFromKey("HolLineNpc_1_6", GetFullName(pchar));
				link.l1.go = "Step_H1_3";
			}
			if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekChumakeiro_GoToVillemstad")
			{
				dialog.text = StringFromKey("HolLineNpc_1_7");
				link.l1 = StringFromKey("HolLineNpc_1_8");
				link.l1.go = "Step_H1_6";
			}// Квест №3, лейтенант в тюрьме.
			if (npchar.id == "Alan_MacLine" && pchar.questTemp.State == "WormEnglPlans_SaveOfficer")
			{
				dialog.text = StringFromKey("HolLineNpc_1_9");
				link.l1 = StringFromKey("HolLineNpc_1_10", pchar);
				link.l1.go = "Step_H3_1";
			} // Квест №5, базар в Ла Веге о гибели Мэнсфилда
			if (npchar.id == "Talker" && pchar.questTemp.State == "ThreeFleutes_toLaVega")
			{
				dialog.text = StringFromKey("HolLineNpc_1_11", pchar);
				link.l1 = StringFromKey("HolLineNpc_1_12");
				link.l1.go = "Step_H5_1";
			} // Квест №7, незнакомец на Тортуге
			if (npchar.id == "Stranger_HL7" && pchar.questTemp.State == "DelivLettTortuga_SnapMeeting")
			{
				dialog.text = StringFromKey("HolLineNpc_1_13", pchar);
				link.l1 = StringFromKey("HolLineNpc_1_14");
				link.l1.go = "Step_H7_1";
			} // Квест №7, Антонио в комнате таверны
			if (npchar.id == "AntonioDeBarras" && pchar.questTemp.State == "DelivLettTortuga_toStranger")
			{
				dialog.text = StringFromKey("HolLineNpc_1_15");
				link.l1 = StringFromKey("HolLineNpc_1_16");
				link.l1.go = "Step_H7_4";
			}
			if (pchar.questTemp.State == "DelivLettTortuga_NotFoundLetter")
			{
				dialog.text = StringFromKey("HolLineNpc_1_17");
				link.l1 = StringFromKey("HolLineNpc_1_18");
				link.l1.go = "Step_H7_6";
			} // Квест №8, Аарон даёт задание
			if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_toAaron")
			{
				dialog.text = StringFromKey("HolLineNpc_1_19");
				link.l1 = StringFromKey("HolLineNpc_1_20", pchar);
				link.l1.go = "Step_H8_1";
			}
			if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_toBermudes")
			{
				dialog.text = StringFromKey("HolLineNpc_1_21");
				link.l1 = StringFromKey("HolLineNpc_1_22");
				link.l1.go = "exit";
			}
			if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_DeGrafIsDead")
			{
				dialog.text = StringFromKey("HolLineNpc_1_23");
				link.l1 = StringFromKey("HolLineNpc_1_24", pchar);
				link.l1.go = "Step_H8_12";
			}
			if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_DeGrafDieHard")
			{
				dialog.text = StringFromKey("HolLineNpc_1_25");
				link.l1 = StringFromKey("HolLineNpc_1_26", pchar);
				link.l1.go = "Step_H8_12";
			}
			if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_BadResult")
			{
				dialog.text = StringFromKey("HolLineNpc_1_27");
				link.l1 = StringFromKey("HolLineNpc_1_28");
				link.l1.go = "exit";
			}
			if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_WeWon")
			{
				dialog.text = StringFromKey("HolLineNpc_1_29");
				link.l1 = StringFromKey("HolLineNpc_1_30", pchar);
				link.l1.go = "Step_H8_12";
				link.l2 = StringFromKey("HolLineNpc_1_31", pchar);
				link.l2.go = "exit";
			}
			if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_IHaveMap")
			{
				dialog.text = StringFromKey("HolLineNpc_1_32");
				link.l1 = StringFromKey("HolLineNpc_1_33", pchar);
				link.l1.go = "Step_H8_12";
				if (CheckCharacterItem(pchar, "Bible"))
				{
					link.l2 = StringFromKey("HolLineNpc_1_34");
					link.l2.go = "Step_H8_13";
				}
				else
				{
					link.l2 = StringFromKey("HolLineNpc_1_35", pchar);
					link.l2.go = "exit";
				}
			}
			if (npchar.id == "Chumakeiro" && pchar.questTemp.State == "SeekBible_GoodResult")
			{
				dialog.text = StringFromKey("HolLineNpc_1_36");
				link.l1 = StringFromKey("HolLineNpc_1_37");
				link.l1.go = "exit";
			}

		break;

		//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//********************************* Дилоги бандитов, грабящих Аарона. Квест №1 **********************************
		case "Step_H1_1":
			dialog.text = StringFromKey("HolLineNpc_1_38");
			link.l1 = StringFromKey("HolLineNpc_1_39");
			link.l1.go = "Step_H1_2";
		break;
		case "Step_H1_2":
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "Step_H1_3":
			dialog.text = StringFromKey("HolLineNpc_1_40");
			link.l1 = StringFromKey("HolLineNpc_1_41", pchar);
			link.l1.go = "Step_H1_4";
		break;
		case "Step_H1_4":
			dialog.text = StringFromKey("HolLineNpc_1_42");
			link.l1 = StringFromKey("HolLineNpc_1_43");
			link.l1.go = "Step_H1_5";
		break;
		case "Step_H1_5":
			AddQuestRecord("Hol_Line_1_Chumakeiro", "2");
			AddQuestUserData("Hol_Line_1_Chumakeiro", "sSex", GetSexPhrase("ёл", "ла"));
			AddQuestUserData("Hol_Line_1_Chumakeiro", "sSex1", GetSexPhrase("", "а"));
			pchar.questTemp.State = "SeekChumakeiro_GoToVillemstad";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
			//ChangeCharacterReputation(pchar, 5); TODO eddy
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			Pchar.quest.SeekChumakeiro_intoResidence.win_condition.l1 = "location";
			Pchar.quest.SeekChumakeiro_intoResidence.win_condition.l1.location = "Villemstad_townhall2";
			Pchar.quest.SeekChumakeiro_intoResidence.win_condition = "SeekChumakeiro_intoResidence";
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			RemoveLandQuestmark_Main(characterFromID("Marigo_tavernkeeper"), "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("hol_guber"), "Hol_Line");
		break;
		case "Step_H1_6":
			dialog.text = StringFromKey("HolLineNpc_1_44");
			link.l1 = StringFromKey("HolLineNpc_1_45");
			link.l1.go = "Step_H1_7";
		break;
		case "Step_H1_7":
			LAi_SetPlayerType(pchar);
			AddMoneyToCharacter(pchar, 30000);
			RemovePassenger(pchar, npchar);
			AddQuestRecord("Hol_Line_1_Chumakeiro", "3");
			AddQuestUserData("Hol_Line_1_Chumakeiro", "sSex", GetSexPhrase("", "а"));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			DialogExit();
		break;

		//********************************* Дилоги лейтенанта в тюрьме. Квест №3 **********************************
		case "Step_H3_1":
			dialog.text = StringFromKey("HolLineNpc_1_46");
			link.l1 = StringFromKey("HolLineNpc_1_47");
			link.l1.go = "Step_H3_2";
		break;
		case "Step_H3_2":
			dialog.text = StringFromKey("HolLineNpc_1_48");
			link.l1 = StringFromKey("HolLineNpc_1_49", pchar);
			link.l1.go = "Step_H3_3";
		break;
		case "Step_H3_3":
			dialog.text = StringFromKey("HolLineNpc_1_50");
			link.l1 = StringFromKey("HolLineNpc_1_51");
			link.l1.go = "Step_H3_4";
		break;
		case "Step_H3_4":
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "PortRoyal_houseS1", "sit", "sit2");
			LAi_SetHuberType(characterFromId("Henry Morgan"));
			AddQuestRecord("Hol_Line_3_WormEnglishPlans", "14");
			AddQuestUserData("Hol_Line_3_WormEnglishPlans", "sSex", GetSexPhrase("", "а"));
			pchar.questTemp.State = "WormEnglPlans_GoodRusultWorm";
			ChangeCharacterAddressGroup(npchar, "SentJons_prison", "goto", "goto23");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			RemoveLandQuestmarkToFantoms_Main("JailOff", "Hol_Line");
		break;

		//********************************* Базар в Ла Веге о гибели Мэнсфилда. Квест №5 **********************************
		case "Step_H5_1":
			dialog.text = StringFromKey("HolLineNpc_1_52");
			link.l1 = StringFromKey("HolLineNpc_1_53");
			link.l1.go = "Step_H5_2";
		break;
		case "Step_H5_2":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Hol_Line_5_ThreeFleutes", "2");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
			Pchar.quest.ThreeFleutes_BackToCuracao.win_condition.l1 = "location";
			Pchar.quest.ThreeFleutes_BackToCuracao.win_condition.l1.location = "Hispaniola1";
			Pchar.quest.ThreeFleutes_BackToCuracao.win_condition = "ThreeFleutes_BackToCuracao";
			DialogExit();
		break;

		//********************************* Базар с незнакомцем на Тортуге. Квест №7 **********************************
		case "Step_H7_1":
			dialog.text = StringFromKey("HolLineNpc_1_54");
			link.l1 = StringFromKey("HolLineNpc_1_55");
			link.l1.go = "Step_H7_2";
		break;
		case "Step_H7_2":
			dialog.text = StringFromKey("HolLineNpc_1_56");
			link.l1 = StringFromKey("HolLineNpc_1_57");
			link.l1.go = "Step_H7_3";
		break;
		case "Step_H7_3":
			chrDisableReloadToLocation = false;
			pchar.questTemp.State = "DelivLettTortuga_toStranger";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 40.0);
			LAi_SetPlayerType(pchar);
			sld = GetCharacter(NPC_GenerateCharacter("AntonioDeBarras", "officer_13", "man", "man", 40, SPAIN, -1, true)); //watch_quest_moment
			sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
			sld.name = FindPersonalName("AntonioDeBarras_name");
			sld.lastname = FindPersonalName("AntonioDeBarras_lastname");
			LAi_SetStayTypeNoGroup(sld);
			FantomMakeCoolSailor(sld, SHIP_WARSHIP, FindPersonalName("AntonioDeBarras_ship"), CANNON_TYPE_CULVERINE_LBS32, 100, 100, 100);
			FantomMakeCoolFighter(sld, 40, 100, 100, "blade32", "pistol5", 150);
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "goto", "goto1");
			DialogExit();
			AddLandQuestmark_Main(sld, "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("Tortuga_tavernkeeper"), "Hol_Line");
		break;

		case "Step_H7_4":
			dialog.text = StringFromKey("HolLineNpc_1_58");
			link.l1 = StringFromKey("HolLineNpc_1_59");
			link.l1.go = "Step_H7_5";
		break;
		case "Step_H7_5":
			LocatorReloadEnterDisable("Tortuga_town", "gate_back", false);
			LocatorReloadEnterDisable("Tortuga_town", "reload1_back", false);
			LocatorReloadEnterDisable("Tortuga_town", "reload2_back", false);
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", true);
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1_back");
			DoQuestFunctionDelay("DelivLettTortuga_Digress", 1.0);
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;

		case "Step_H7_6":
			dialog.text = StringFromKey("HolLineNpc_1_60");
			link.l1 = StringFromKey("HolLineNpc_1_61");
			link.l1.go = "Step_H7_7";
		break;
		case "Step_H7_7":
			dialog.text = StringFromKey("HolLineNpc_1_62");
			link.l1 = StringFromKey("HolLineNpc_1_63");
			link.l1.go = "Step_H7_8";
		break;
		case "Step_H7_8":
			dialog.text = StringFromKey("HolLineNpc_1_64", pchar);
			link.l1 = StringFromKey("HolLineNpc_1_65");
			link.l1.go = "Step_H7_9";
		break;
		case "Step_H7_9":
			dialog.text = StringFromKey("HolLineNpc_1_66");
			link.l1 = StringFromKey("HolLineNpc_1_67", pchar);
			link.l1.go = "Step_H7_10";
			GiveItem2Character(pchar, "letter_HolLineQ7_1");
		break;
		case "Step_H7_10":
			dialog.text = StringFromKey("HolLineNpc_1_68");
			link.l1 = StringFromKey("HolLineNpc_1_69");
			link.l1.go = "Step_H7_11";
		break;
		case "Step_H7_11":
			AddQuestRecord("Hol_Line_7_DelivLettTortuga", "11");
			pchar.questTemp.State = "DelivLettTortuga_LetterFound";
			pchar.quest.DelivLettTortuga_WarshipDieHard.over = "yes";
			pchar.quest.DelivLettTortuga_AfterWarshipSunk.over = "yes";
			Island_SetReloadEnableGlobal("SantaCatalina", true);
			QuestAboardCabinDialogSurrender();
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;

		//********************************* Поиски Библии. Квест №8 **********************************
		case "Step_H8_1":
			dialog.text = StringFromKey("HolLineNpc_1_70");
			link.l1 = StringFromKey("HolLineNpc_1_71");
			link.l1.go = "Step_H8_2";
		break;
		case "Step_H8_2":
			dialog.text = StringFromKey("HolLineNpc_1_72", pchar);
			link.l1 = StringFromKey("HolLineNpc_1_73");
			link.l1.go = "Step_H8_3";
		break;
		case "Step_H8_3":
			dialog.text = StringFromKey("HolLineNpc_1_74");
			link.l1 = StringFromKey("HolLineNpc_1_75");
			link.l1.go = "Step_H8_4";
		break;
		case "Step_H8_4":
			dialog.text = StringFromKey("HolLineNpc_1_76");
			link.l1 = StringFromKey("HolLineNpc_1_77");
			link.l1.go = "Step_H8_5";
		break;
		case "Step_H8_5":
			dialog.text = StringFromKey("HolLineNpc_1_78", pchar);
			link.l1 = StringFromKey("HolLineNpc_1_79", pchar);
			link.l1.go = "Step_H8_6";
		break;
		case "Step_H8_6":
			dialog.text = StringFromKey("HolLineNpc_1_80");
			link.l1 = StringFromKey("HolLineNpc_1_81");
			link.l1.go = "Step_H8_7";
		break;
		case "Step_H8_7":
			dialog.text = StringFromKey("HolLineNpc_1_82");
			link.l1 = StringFromKey("HolLineNpc_1_83");
			link.l1.go = "Step_H8_8";
		break;
		case "Step_H8_8":
			dialog.text = StringFromKey("HolLineNpc_1_84");
			link.l1 = StringFromKey("HolLineNpc_1_85");
			link.l1.go = "Step_H8_9";
		break;
		case "Step_H8_9":
			dialog.text = StringFromKey("HolLineNpc_1_86");
			link.l1 = StringFromKey("HolLineNpc_1_87");
			link.l1.go = "Step_H8_10";
		break;
		case "Step_H8_10":
			dialog.text = StringFromKey("HolLineNpc_1_88");
			link.l1 = StringFromKey("HolLineNpc_1_89");
			link.l1.go = "Step_H8_11";
		break;
		case "Step_H8_11":
			dialog.text = StringFromKey("HolLineNpc_1_90", GetFullName(pchar));
			link.l1 = StringFromKey("HolLineNpc_1_91");
			link.l1.go = "exit";
			pchar.questTemp.State = "SeekBible_toBermudes";
			AddQuestRecord("Hol_Line_8_SeekBible", "2");
			//HardCoffee ref Jackman's dialogue
			//QuestSetCurrentNode("Jackman", "HolLine8_quest");
			pchar.QuestTemp.HolLine_quests_task = "HolLine8_quest";
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("Pirates_tavernkeeper"), "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("Jackman"), "Hol_Line");
		break;
		case "Step_H8_12":
			dialog.text = StringFromKey("HolLineNpc_1_92");
			link.l1 = StringFromKey("HolLineNpc_1_93");
			link.l1.go = "exit";
			pchar.questTemp.State = "SeekBible_BadResult";
			NPChar.LifeDay = 0;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("hol_guber"), "Hol_Line");
		break;
		case "Step_H8_13":
			dialog.text = StringFromKey("HolLineNpc_1_94");
			link.l1 = StringFromKey("HolLineNpc_1_95");
			link.l1.go = "Step_H8_14";
			TakeItemFromCharacter(pchar, "Bible");
		break;
		case "Step_H8_14":
			dialog.text = StringFromKey("HolLineNpc_1_96", GetFullName(pchar));
			link.l1 = StringFromKey("HolLineNpc_1_97", pchar);
			link.l1.go = "Step_H8_15";
		break;
		case "Step_H8_15":
			dialog.text = StringFromKey("HolLineNpc_1_98");
			link.l1 = StringFromKey("HolLineNpc_1_99");
			link.l1.go = "Step_H8_16";
		break;
		case "Step_H8_16":
			dialog.text = StringFromKey("HolLineNpc_1_100");
			link.l1 = StringFromKey("HolLineNpc_1_101");
			link.l1.go = "Step_H8_17";
		break;
		case "Step_H8_17":
			dialog.text = StringFromKey("HolLineNpc_1_102");
			link.l1 = StringFromKey("HolLineNpc_1_103");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 1235000);
			pchar.questTemp.State = "SeekBible_GoodResult";
			AddQuestRecord("Hol_Line_8_SeekBible", "10");
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("", "а"));
			NPChar.LifeDay = 0;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("hol_guber"), "Hol_Line");
		break;
	}
}
