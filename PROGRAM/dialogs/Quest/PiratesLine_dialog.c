void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("PiratesLine_dialog_1");
			link.l1 = StringFromKey("PiratesLine_dialog_2");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "exit_hl":
			NextDiag.TempNode = "PiratesManNew1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// -------------------------------------- квест №1 -------------------------------------------------
		//первая встреча с посыльным Моргана в Пуэрто Принсипе
		case "PiratesMan1":
			if (pchar.questTemp.State == "" || sti(pchar.questTemp.CurQuestNumber) > 8 || sti(pchar.questTemp.NationQuest) == SPAIN)
			{
				dialog.text = StringFromKey("PiratesLine_dialog_3", pchar);
				link.l1 = StringFromKey("PiratesLine_dialog_4");
				link.l1.go = "exit_hl";
				link.l2 = StringFromKey("PiratesLine_dialog_5");
				link.l2.go = "PiratesMan1_1";
			}
			else
			{
				dialog.text = StringFromKey("PiratesLine_dialog_6", pchar);
				link.l1 = StringFromKey("PiratesLine_dialog_7", pchar);
				link.l1.go = "PiratesManNot_1";
				npchar.talker = 2; //начать диалог
				NextDiag.TempNode = "PiratesManNew1";
			}
		break;
		case "PiratesMan1_1":
			dialog.text = StringFromKey("PiratesLine_dialog_8");
			link.l1 = StringFromKey("PiratesLine_dialog_9");
			link.l1.go = "PiratesMan1_2";
		break;
		case "PiratesMan1_2":
			DialogExit();
			NextDiag.CurrentNode = "Tavern_1";
			LockQuestLine(characterFromId("eng_guber")); // лочим английскую линейку
			RemoveLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
			RemoveMapQuestMark("PortRoyal_town", "Eng_Line");
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			bDisableLandEncounters = true; //защита от ПГГ
			FreeSitLocator("PuertoPrincipe_tavern", "sit3");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5", "PuertoPrincipe_tavern", "sit", "sit3", "PiratesLine_toTavern", -1);
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			RemoveLandQuestmark_Main(CharacterFromID("Jackman"), "Pir_Line");
			RemoveMapQuestMark("PuertoPrincipe_town", "Pir_Line");
			RemoveMapQuestMark("Pirates_town", "Pir_Line");
		break;

		case "PiratesManNot_1":
			dialog.text = StringFromKey("PiratesLine_dialog_10", pchar, NationNameGenitive(sti(pchar.questTemp.NationQuest)));
			link.l1 = StringFromKey("PiratesLine_dialog_11");
			link.l1.go = "PiratesManNot_2";
		break;
		case "PiratesManNot_2":
			dialog.text = StringFromKey("PiratesLine_dialog_12");
			link.l1 = StringFromKey("PiratesLine_dialog_13");
			link.l1.go = "exit";
			SetQuestHeader("Pir_Line_0_Waiting");
			AddQuestRecord("Pir_Line_0_Waiting", "1");
			AddQuestUserData("Pir_Line_0_Waiting", "sNation", NationNameInstrumental(sti(pchar.questTemp.NationQuest)));
		break;

		case "PiratesManNew1":
			if (pchar.questTemp.State == "" || sti(pchar.questTemp.CurQuestNumber) > 8 || sti(pchar.questTemp.NationQuest) == SPAIN)
			{
				dialog.text = StringFromKey("PiratesLine_dialog_14", pchar);
				link.l1 = StringFromKey("PiratesLine_dialog_15");
				link.l1.go = "exit_hl";
				link.l2 = StringFromKey("PiratesLine_dialog_16");
				link.l2.go = "PiratesMan1_1";
			}
			else
			{
				dialog.text = StringFromKey("PiratesLine_dialog_17", pchar);
				link.l1 = StringFromKey("PiratesLine_dialog_18");
				link.l1.go = "exit";
				npchar.talker = 2; //начать диалог
				NextDiag.TempNode = "PiratesManNew1";
			}
		break;
		//разговор в таверне Пуэрто Принсипе
		case "Tavern_1":
			dialog.text = StringFromKey("PiratesLine_dialog_19", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_20", pchar);
			link.l1.go = "Tavern_2";
			npchar.lifeDay = 0;
		break;
		case "Tavern_2":
			dialog.text = StringFromKey("PiratesLine_dialog_21", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_22");
			link.l1.go = "Tavern_3";
			link.l2 = StringFromKey("PiratesLine_dialog_23", pchar);
			link.l2.go = "Tavern_over";
		break;
		case "Tavern_3":
			dialog.text = StringFromKey("PiratesLine_dialog_24");
			link.l1 = StringFromKey("PiratesLine_dialog_25");
			link.l1.go = "Tavern_4";
		break;
		case "Tavern_4":
			dialog.text = StringFromKey("PiratesLine_dialog_26", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_27", pchar);
			link.l1.go = "Tavern_5";
		break;
		case "Tavern_5":
			dialog.text = StringFromKey("PiratesLine_dialog_28", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_29");
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			NextDiag.TempNode = "Tavern_again";
			SetQuestHeader("Pir_Line_1_JohnBolton");
			AddQuestRecord("Pir_Line_1_JohnBolton", "1");
			CloseQuestHeader("Pir_Line_0_Waiting");
			pchar.questTemp.piratesLine = "toJohnBolton";
			sld = GetCharacter(NPC_GenerateCharacter("QuestPirate2", "officer_20", "man", "man", 20, PIRATE, -1, true)); //watch_quest_moment, полный аналог ванильного officer_4 не лежит у нас
			sld.name = FindPersonalName("QuestPirate2_name");
			sld.lastname = FindPersonalName("QuestPirate2_lastname");
			sld.rank = 20;
			sld.city = "PuertoPrincipe";
			sld.location = "PuertoPrincipe_port";
			sld.location.group = "goto";
			sld.location.locator = "goto14";
			sld.dialog.filename = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode = "JohnBolton";
			sld.greeting = "Gr_MiddPirate";
			sld.talker = 8; //начать диалог
			LAi_SetLoginTime(sld, 6.0, 21.99);
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			AddDialogExitQuestFunction("PiratesLine_q1_tavernEnd");
			AddLandQuestmark_Main(sld, "Pir_Line");
		break;

		case "Tavern_again":
			dialog.text = StringFromKey("PiratesLine_dialog_30");
			link.l1 = StringFromKey("PiratesLine_dialog_31");
			link.l1.go = "exit";
			NextDiag.TempNode = "Tavern_again";
		break;
		case "Tavern_over":
			dialog.text = StringFromKey("PiratesLine_dialog_32", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_33");
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			pchar.questTemp.piratesLine = "over";
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("PiratesLine_q1_tavernEnd");
		break;
		//базар с Джоном Болтоном в порту Пуэрто Принсипе
		case "JohnBolton":
			dialog.text = StringFromKey("PiratesLine_dialog_34", GetFullName(pchar));
			link.l1 = StringFromKey("PiratesLine_dialog_35");
			link.l1.go = "JohnBolton_1";
		break;
		case "JohnBolton_1":
			dialog.text = StringFromKey("PiratesLine_dialog_36");
			link.l1 = StringFromKey("PiratesLine_dialog_37");
			link.l1.go = "JohnBolton_2";
		break;
		case "JohnBolton_2":
			AddQuestRecord("Pir_Line_1_JohnBolton", "2");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1 = "locator";
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1.location = "PortRoyal_town";
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1.locator_group = "quest";
			pchar.quest.PiratesLine_q1_arrest.win_condition.l1.locator = "detector_PQ1";
			pchar.quest.PiratesLine_q1_arrest.function = "PiratesLine_q1_arrest";
			NextDiag.TempNode = "JohnBolton_inWay";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "", 5.0);
			RemoveLandQuestmark_Main(npchar, "Pir_Line");

			QuestPointerToLoc("PortRoyal_town", "quest", "detector_PQ1");
		break;
		case "JohnBolton_inWay":
			dialog.text = StringFromKey("PiratesLine_dialog_38", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_39");
			link.l1.go = "exit";
			NextDiag.TempNode = "JohnBolton_inWay";
		break;
		//базар с арестовывающими солдерами
		case "ArrestInPR":
			dialog.text = StringFromKey("PiratesLine_dialog_40");
			link.l1 = StringFromKey("PiratesLine_dialog_41", pchar);
			link.l1.go = "ArrestInPR_1";
		break;
		case "ArrestInPR_1":
			dialog.text = StringFromKey("PiratesLine_dialog_42");
			link.l1 = StringFromKey("PiratesLine_dialog_43");
			link.l1.go = "ArrestInPR_2";
		break;
		case "ArrestInPR_2":
			bDisableCharacterMenu = true; //Hokkins: закрываем Ф2
			AddQuestRecord("Pir_Line_1_JohnBolton", "3");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Portroyal_town", "houseS1", false); //закроем дом Моргана
			DialogExit();
			AddDialogExitQuestFunction("PiratesLine_q1_toPrison");
		break;
		// -------------------------------------- квест №2 -------------------------------------------------
		case "EdwardLoy":
			dialog.text = StringFromKey("PiratesLine_dialog_44", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_45");
			link.l1.go = "EdwardLoy_1";
		break;
		case "EdwardLoy_1":
			dialog.text = StringFromKey("PiratesLine_dialog_46");
			link.l1 = StringFromKey("PiratesLine_dialog_47");
			link.l1.go = "EdwardLoy_2";
		break;
		case "EdwardLoy_2":
			dialog.text = StringFromKey("PiratesLine_dialog_48");
			link.l1 = StringFromKey("PiratesLine_dialog_49");
			link.l1.go = "EdwardLoy_3";
			RemoveItems(PChar, "BlackLabel", 1);
		break;
		case "EdwardLoy_3":
			dialog.text = StringFromKey("PiratesLine_dialog_50");
			link.l1 = StringFromKey("PiratesLine_dialog_51");
			link.l1.go = "EdwardLoy_4";
		break;
		case "EdwardLoy_4":
			dialog.text = StringFromKey("PiratesLine_dialog_52", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_53");
			link.l1.go = "exit";
			NextDiag.TempNode = "EdwardLoy_again";
			//HardCoffee реф диалогов Моргана
			pchar.QuestTemp.PirLine_quests_task = "PL_Q2_away_1";
			AddQuestRecord("Pir_Line_2_BlackLabel", "3");
			AddQuestUserData("Pir_Line_2_BlackLabel", "sSex", GetSexPhrase("", "а"));
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			RemoveLandQuestmark_Main(CharacterFromID("LeFransua_tavernkeeper"), "Pir_Line");
			AddLandQuestmark_Main(CharacterFromID("Henry Morgan"), "Pir_Line");
		break;
		case "EdwardLoy_again":
			dialog.text = StringFromKey("PiratesLine_dialog_54");
			link.l1 = StringFromKey("PiratesLine_dialog_55");
			link.l1.go = "exit";
			NextDiag.TempNode = "EdwardLoy_again";
		break;
		// -------------------------------------- квест №3 -------------------------------------------------
		case "CapGoodly":
			dialog.text = StringFromKey("PiratesLine_dialog_56", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_57");
			link.l1.go = "CapGoodly_1";
		break;
		case "CapGoodly_1":
			dialog.text = StringFromKey("PiratesLine_dialog_58");
			link.l1 = StringFromKey("PiratesLine_dialog_59");
			link.l1.go = "CapGoodly_2";
		break;
		case "CapGoodly_2":
			dialog.text = StringFromKey("PiratesLine_dialog_60");
			link.l1 = StringFromKey("PiratesLine_dialog_61");
			link.l1.go = "CapGoodly_3";
		break;
		case "CapGoodly_3":
			dialog.text = StringFromKey("PiratesLine_dialog_62");
			link.l1 = StringFromKey("PiratesLine_dialog_63", pchar);
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "13");
			pchar.questTemp.piratesLine = "KillLoy_toCumana";
			npchar.lifeDay = 0;
			pchar.quest.PiratesLine_q3_loginSeaWolf.win_condition.l1 = "location";
			pchar.quest.PiratesLine_q3_loginSeaWolf.win_condition.l1.location = "Cumana";
			pchar.quest.PiratesLine_q3_loginSeaWolf.function = "PiratesLine_q3_loginSeaWolf";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			PiratesLine_q3_AddQuestMarksToTavernkeepers();
		break;
		//Эдвард Лоу в каюте Морского Волка
		case "SeaWolf":
			dialog.text = StringFromKey("PiratesLine_dialog_64", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_65");
			link.l1.go = "SeaWolf_1";
		break;
		case "SeaWolf_1":
			dialog.text = StringFromKey("PiratesLine_dialog_66", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_67");
			link.l1.go = "SeaWolf_2";
		break;
		case "SeaWolf_2":
			dialog.text = StringFromKey("PiratesLine_dialog_68");
			link.l1 = StringFromKey("PiratesLine_dialog_69");
			link.l1.go = "SeaWolf_3";
		break;
		case "SeaWolf_3":
			dialog.text = StringFromKey("PiratesLine_dialog_70", GetFullName(PChar));
			link.l1 = StringFromKey("PiratesLine_dialog_71", pchar);
			link.l1.go = "SeaWolf_4";
		break;
		case "SeaWolf_4":
			dialog.text = StringFromKey("PiratesLine_dialog_72");
			link.l1 = StringFromKey("PiratesLine_dialog_73", pchar);
			link.l1.go = "SeaWolf_5";
		break;
		case "SeaWolf_5":
			dialog.text = StringFromKey("PiratesLine_dialog_74");
			link.l1 = StringFromKey("PiratesLine_dialog_75");
			link.l1.go = "SeaWolf_6";
		break;
		case "SeaWolf_6":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		// -------------------------------------- квест №5 -------------------------------------------------
		case "PQ5CapGoodly":
			dialog.text = StringFromKey("PiratesLine_dialog_76", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_77");
			link.l1.go = "PQ5CapGoodly_1";
		break;
		case "PQ5CapGoodly_1":
			dialog.text = StringFromKey("PiratesLine_dialog_78");
			link.l1 = StringFromKey("PiratesLine_dialog_79");
			link.l1.go = "PQ5CapGoodly_3";
		break;
		// Warship 13.07.09 Нуту этого
		/*case "PQ5CapGoodly_2":
			dialog.text = "Проблема в том, что Моргану я сейчас нужен в Порт-Ройал, и он не хочет меня отпускать. Выполнить заказ нет никакой возможности... Короче, возьмёшь мой заказ?";
			link.l1 = "А отказаться ты не можешь?";
			link.l1.go = "PQ5CapGoodly_3";
		break;*/
		case "PQ5CapGoodly_3":
			dialog.text = StringFromKey("PiratesLine_dialog_80");
			link.l1 = StringFromKey("PiratesLine_dialog_81");
			link.l1.go = "PQ5CapGoodly_4";
		break;
		case "PQ5CapGoodly_4":
			dialog.text = StringFromKey("PiratesLine_dialog_82");
			link.l1 = StringFromKey("PiratesLine_dialog_83");
			link.l1.go = "PQ5CapGoodly_5";
		break;
		case "PQ5CapGoodly_5":
			dialog.text = StringFromKey("PiratesLine_dialog_84", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_85");
			link.l1.go = "PQ5CapGoodly_6";
		break;
		case "PQ5CapGoodly_6":
			dialog.text = StringFromKey("PiratesLine_dialog_86");
			link.l1 = StringFromKey("PiratesLine_dialog_87");
			link.l1.go = "PQ5CapGoodly_7";
		break;
		case "PQ5CapGoodly_7":
			dialog.text = StringFromKey("PiratesLine_dialog_88");
			link.l1 = StringFromKey("PiratesLine_dialog_89", PChar.Name);
			link.l1.go = "PQ5CapGoodly_8";
		break;
		case "PQ5CapGoodly_8":
			chrDisableReloadToLocation = false;
			pchar.questTemp.piratesLine = "PL5Hunter_toVillemstad";
			AddLandQuestmark_Main(CharacterFromID("Villemstad_usurer"), "Pir_Line");
			SetQuestHeader("Pir_Line_5_Hunter");
			AddQuestRecord("Pir_Line_5_Hunter", "1");
			AddQuestUserData("Pir_Line_5_Hunter", "sSex", GetSexPhrase("ик", "ица"));
			LAi_SetActorTypeNoGroup(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", "houseS1", "none", "", "", "", -1.0);
			DialogExit();
		break;
		//Эйвори вместо ГГ
		case "PQ5Hero":
			dialog.text = StringFromKey("PiratesLine_dialog_90");
			link.l1 = StringFromKey("PiratesLine_dialog_91");
			link.l1.go = "PQ5Hero_1";
		break;
		case "PQ5Hero_1":
			DialogExit();
			AddDialogExitQuestFunction("PQ5_afterChangeMainHero");
		break;
		//Эйвори в доме на Бермудах
		case "PQ5Aivory":
			dialog.text = StringFromKey("PiratesLine_dialog_92");
			link.l1 = StringFromKey("PiratesLine_dialog_93");
			link.l1.go = "PQ5Aivory_1";
		break;
		case "PQ5Aivory_1":
			dialog.text = StringFromKey("PiratesLine_dialog_94");
			link.l1 = StringFromKey("PiratesLine_dialog_95");
			link.l1.go = "PQ5Aivory_2";
		break;
		case "PQ5Aivory_2":
			DialogExit();
			AddDialogExitQuestFunction("PQ5_afterChangeMainHero2");
		break;
		//Гудли в таверне Порт-Ройал
		case "PQ5CapGoodlyEnd":
			dialog.text = StringFromKey("PiratesLine_dialog_96", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("PiratesLine_dialog_97", pchar);
			link.l1.go = "PQ5CapGoodlyEnd_1";
		break;
		case "PQ5CapGoodlyEnd_1":
			dialog.text = StringFromKey("PiratesLine_dialog_98", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_99");
			link.l1.go = "PQ5CapGoodlyEnd_2";
			AddMoneyToCharacter(pchar, 15000);
		break;
		case "PQ5CapGoodlyEnd_2":
			dialog.text = StringFromKey("PiratesLine_dialog_100");
			link.l1 = StringFromKey("PiratesLine_dialog_101");
			link.l1.go = "PQ5CapGoodlyEnd_3";
		break;
		case "PQ5CapGoodlyEnd_3":
			dialog.text = StringFromKey("PiratesLine_dialog_102");
			link.l1 = StringFromKey("PiratesLine_dialog_103", pchar);
			link.l1.go = "PQ5CapGoodlyEnd_4";
		break;
		case "PQ5CapGoodlyEnd_4":
			dialog.text = StringFromKey("PiratesLine_dialog_104");
			link.l1 = StringFromKey("PiratesLine_dialog_105");
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "12");
			sld = characterFromId("Henry Morgan");
			LAi_SetHuberTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
			QuestSetCurrentNode("Henry Morgan", "PL_Q5_begin");
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;
		// -------------------------------------- квест №6 -------------------------------------------------
		case "JohnLids":
			dialog.text = StringFromKey("PiratesLine_dialog_106");
			link.l1 = StringFromKey("PiratesLine_dialog_107");
			link.l1.go = "JohnLids_1";
		break;
		case "JohnLids_1":
			dialog.text = StringFromKey("PiratesLine_dialog_108");
			link.l1 = GetFullName(pchar) + ".";
			link.l1.go = "JohnLids_2";
		break;
		case "JohnLids_2":
			dialog.text = StringFromKey("PiratesLine_dialog_109");
			link.l1 = StringFromKey("PiratesLine_dialog_110", GetFullName(PChar));
			link.l1.go = "JohnLids_3";
		break;
		case "JohnLids_3":
			dialog.text = StringFromKey("PiratesLine_dialog_111", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("PiratesLine_dialog_112", pchar);
			link.l1.go = "JohnLids_4";
		break;
		case "JohnLids_4":
			dialog.text = StringFromKey("PiratesLine_dialog_113", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_114");
			link.l1.go = "JohnLids_5";
		break;
		case "JohnLids_5":
			dialog.text = StringFromKey("PiratesLine_dialog_115", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_116");
			link.l1.go = "JohnLids_6";
		break;
		case "JohnLids_6":
			dialog.text = StringFromKey("PiratesLine_dialog_117");
			link.l1 = StringFromKey("PiratesLine_dialog_118", pchar);
			link.l1.go = "JohnLids_7";
		break;
		case "JohnLids_7":
			dialog.text = StringFromKey("PiratesLine_dialog_119", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_120");
			link.l1.go = "exit";
			NextDiag.TempNode = "JohnLids_again";
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "3");
			AddQuestUserData("Pir_Line_6_Jackman", "sSex", GetSexPhrase(StringFromKey("SexPhrase_11"), StringFromKey("SexPhrase_12")));
			AddQuestUserData("Pir_Line_6_Jackman", "sSex1", GetSexPhrase("ий", "ая"));
			Pchar.quest.PQ6_ShoreBattle.win_condition.l1 = "location";
			Pchar.quest.PQ6_ShoreBattle.win_condition.l1.location = "Shore7";
			Pchar.quest.PQ6_ShoreBattle.function = "PQ6_ShoreBattle";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;
		case "JohnLids_again":
			dialog.text = StringFromKey("PiratesLine_dialog_121", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_122", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "JohnLids_again";
		break;
		//двойник ГГ
		case "QuestPirateHead":
			dialog.text = StringFromKey("PiratesLine_dialog_123", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("PiratesLine_dialog_124", pchar);
			link.l1.go = "QuestPirateHead_1";
		break;
		case "QuestPirateHead_1":
			dialog.text = StringFromKey("PiratesLine_dialog_125", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_126");
			link.l1.go = "QuestPirateHead_2";
		break;
		case "QuestPirateHead_2":
			dialog.text = StringFromKey("PiratesLine_dialog_127");
			link.l1 = StringFromKey("PiratesLine_dialog_128", pchar);
			link.l1.go = "QuestPirateHead_3";
		break;
		case "QuestPirateHead_3":
			dialog.text = StringFromKey("PiratesLine_dialog_129", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_130");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PQ6_JungleBattle");
		break;
		// -------------------------------------- квест №7 -------------------------------------------------
		case "FriendLinney":
			dialog.text = StringFromKey("PiratesLine_dialog_131");
			link.l1 = StringFromKey("PiratesLine_dialog_132");
			link.l1.go = "FriendLinney_1";
		break;
		case "FriendLinney_1":
			dialog.text = StringFromKey("PiratesLine_dialog_133");
			link.l1 = StringFromKey("PiratesLine_dialog_134", GetFullName(pchar));
			link.l1.go = "FriendLinney_2";
		break;
		case "FriendLinney_2":
			dialog.text = StringFromKey("PiratesLine_dialog_135", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_136");
			link.l1.go = "FriendLinney_3";
		break;
		case "FriendLinney_3":
			dialog.text = StringFromKey("PiratesLine_dialog_137");
			link.l1 = StringFromKey("PiratesLine_dialog_138", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendLinney_again";
			pchar.questTemp.piratesLine = "Soukins_toSantoDomingo";
			AddQuestRecord("Pir_Line_7_Soukins", "5");
			SetBan("Map", 0);
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			AddLandQuestMark_Main(CharacterFromID("SantoDomingo_shipyarder"), "Pir_Line");
		break;
		case "FriendLinney_again":
			dialog.text = StringFromKey("PiratesLine_dialog_139");
			link.l1 = StringFromKey("PiratesLine_dialog_140");
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendLinney_again";
		break;
		//кэп, продавшие шлюп Ласточку
		case "LeonCapitain":
			dialog.text = StringFromKey("PiratesLine_dialog_141");
			link.l1 = StringFromKey("PiratesLine_dialog_142");
			link.l1.go = "LeonCapitain_1";
		break;
		case "LeonCapitain_1":
			dialog.text = StringFromKey("PiratesLine_dialog_143");
			link.l1 = StringFromKey("PiratesLine_dialog_144");
			link.l1.go = "LeonCapitain_2";
		break;
		case "LeonCapitain_2":
			dialog.text = StringFromKey("PiratesLine_dialog_145");
			link.l1 = StringFromKey("PiratesLine_dialog_146");
			link.l1.go = "LeonCapitain_3";
		break;
		case "LeonCapitain_3":
			dialog.text = StringFromKey("PiratesLine_dialog_147");
			link.l1 = StringFromKey("PiratesLine_dialog_148", pchar);
			link.l1.go = "LeonCapitain_4";
		break;
		case "LeonCapitain_4":
			dialog.text = StringFromKey("PiratesLine_dialog_149");
			link.l1 = StringFromKey("PiratesLine_dialog_150");
			link.l1.go = "LeonCapitain_5";
		break;
		case "LeonCapitain_5":
			dialog.text = StringFromKey("PiratesLine_dialog_151", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_152");
			link.l1.go = "LeonCapitain_6";
		break;
		case "LeonCapitain_6":
			Map_ReleaseQuestEncounter("LeonCapitain");
			pchar.questTemp.piratesLine = "Soukins_toMorgan";
			//HardCoffee ref Morgan's dialogue
			//QuestSetCurrentNode("Henry Morgan", "PL_Q7_afterLeon");
			pchar.QuestTemp.PirLine_quests_task = "PL_Q7_AboutLiney";
			AddQuestRecord("Pir_Line_7_Soukins", "7");
			AddQuestUserData("Pir_Line_7_Soukins", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Pir_Line_7_Soukins", "sSex1", GetSexPhrase("ся", "ась"));
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//поход на Панаму, пираты в городе
		case "PQ8_PirInPan":
			dialog.text = StringFromKey("PiratesLine_dialog_153", pchar.name);
			link.l1 = StringFromKey("PiratesLine_dialog_154");
			link.l1.go = "PQ8_PirInPan_1";
		break;
		case "PQ8_PirInPan_1":
			dialog.text = StringFromKey("PiratesLine_dialog_155");
			link.l1 = StringFromKey("PiratesLine_dialog_156");
			link.l1.go = "exit";
		break;
		case "PQ8_RsPirInPan":
			dialog.text = StringFromKey("PiratesLine_dialog_157");
			link.l1 = StringFromKey("PiratesLine_dialog_158");
			link.l1.go = "PQ8_RsPirInPan_1";
		break;
		case "PQ8_RsPirInPan_1":
			dialog.text = StringFromKey("PiratesLine_dialog_159");
			link.l1 = StringFromKey("PiratesLine_dialog_160");
			link.l1.go = "exit";
		break;
		case "PQ8_MPirInPan":
			dialog.text = StringFromKey("PiratesLine_dialog_161");
			link.l1 = StringFromKey("PiratesLine_dialog_162");
			link.l1.go = "PQ8_MPirInPan_1";
		break;
		case "PQ8_MPirInPan_1":
			dialog.text = StringFromKey("PiratesLine_dialog_163");
			link.l1 = StringFromKey("PiratesLine_dialog_164");
			link.l1.go = "exit";
		break;
		//фантом мэра Панамы
		case "PQ8_Mayor":
			dialog.text = StringFromKey("PiratesLine_dialog_165");
			link.l1 = StringFromKey("PiratesLine_dialog_166");
			link.l1.go = "PQ8_Mayor_1";
		break;
		case "PQ8_Mayor_1":
			dialog.text = StringFromKey("PiratesLine_dialog_167");
			link.l1 = StringFromKey("PiratesLine_dialog_168");
			link.l1.go = "PQ8_Mayor_2";
		break;
		case "PQ8_Mayor_2":
			dialog.text = StringFromKey("PiratesLine_dialog_169");
			link.l1 = StringFromKey("PiratesLine_dialog_170");
			link.l1.go = "PQ8_Mayor_3";
		break;
		case "PQ8_Mayor_3":
			dialog.text = StringFromKey("PiratesLine_dialog_171");
			link.l1 = StringFromKey("PiratesLine_dialog_172");
			link.l1.go = "PQ8_Mayor_4";
		break;
		case "PQ8_Mayor_4":
			dialog.text = StringFromKey("PiratesLine_dialog_173");
			link.l1 = StringFromKey("PiratesLine_dialog_174");
			link.l1.go = "PQ8_Mayor_5";
		break;
		case "PQ8_Mayor_5":
			dialog.text = StringFromKey("PiratesLine_dialog_175");
			link.l1 = StringFromKey("PiratesLine_dialog_176");
			link.l1.go = "PQ8_Mayor_6";
		break;
		case "PQ8_Mayor_6":
			dialog.text = StringFromKey("PiratesLine_dialog_177");
			link.l1 = StringFromKey("PiratesLine_dialog_178");
			link.l1.go = "PQ8_Mayor_7";
		break;
		case "PQ8_Mayor_7":
			dialog.text = StringFromKey("PiratesLine_dialog_179");
			link.l1 = StringFromKey("PiratesLine_dialog_180");
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_8_Panama", "11");
			pchar.quest.PQ8_MorganInPanama_1.win_condition.l1 = "location";
			pchar.quest.PQ8_MorganInPanama_1.win_condition.l1.location = "Panama_town";
			pchar.quest.PQ8_MorganInPanama_1.function = "PQ8_MorganInPanama_1";
		break;
		//обманутые пиратусы в Панаме
		case "PQ8_FackMorgan":
			dialog.text = StringFromKey("PiratesLine_dialog_184", LinkRandPhrase(
						StringFromKey("PiratesLine_dialog_181"),
						StringFromKey("PiratesLine_dialog_182", pchar),
						StringFromKey("PiratesLine_dialog_183")));
			link.l1 = StringFromKey("PiratesLine_dialog_188", LinkRandPhrase(
						StringFromKey("PiratesLine_dialog_185", pchar),
						StringFromKey("PiratesLine_dialog_186"),
						StringFromKey("PiratesLine_dialog_187")));
			link.l1.go = "exit";
		break;
		//первый подбегающий пират
		case "PL_Q8_QFackMorgan":
			dialog.text = StringFromKey("PiratesLine_dialog_189");
			link.l1 = StringFromKey("PiratesLine_dialog_190");
			link.l1.go = "PL_Q8_QFackMorgan_1";
		break;
		case "PL_Q8_QFackMorgan_1":
			dialog.text = StringFromKey("PiratesLine_dialog_191");
			link.l1 = StringFromKey("PiratesLine_dialog_192");
			link.l1.go = "PL_Q8_QFackMorgan_2";
		break;
		case "PL_Q8_QFackMorgan_2":
			dialog.text = StringFromKey("PiratesLine_dialog_193");
			link.l1 = StringFromKey("PiratesLine_dialog_194");
			link.l1.go = "PL_Q8_QFackMorgan_3";
		break;
		case "PL_Q8_QFackMorgan_3":
			dialog.text = StringFromKey("PiratesLine_dialog_195");
			link.l1 = StringFromKey("PiratesLine_dialog_196");
			link.l1.go = "PL_Q8_QFackMorgan_4";
		break;
		case "PL_Q8_QFackMorgan_4":
			dialog.text = StringFromKey("PiratesLine_dialog_197");
			link.l1 = StringFromKey("PiratesLine_dialog_198");
			link.l1.go = "PL_Q8_QFackMorgan_5";
		break;
		case "PL_Q8_QFackMorgan_5":
			dialog.text = StringFromKey("PiratesLine_dialog_199");
			link.l1 = StringFromKey("PiratesLine_dialog_200", pchar);
			link.l1.go = "PL_Q8_QFackMorgan_6";
		break;
		case "PL_Q8_QFackMorgan_6":
			dialog.text = StringFromKey("PiratesLine_dialog_201");
			link.l1 = StringFromKey("PiratesLine_dialog_202");
			link.l1.go = "PL_Q8_QFackMorgan_7";
		break;
		case "PL_Q8_QFackMorgan_7":
			dialog.text = StringFromKey("PiratesLine_dialog_203");
			link.l1 = StringFromKey("PiratesLine_dialog_204");
			link.l1.go = "PL_Q8_QFackMorgan_8";
		break;
		case "PL_Q8_QFackMorgan_8":
			dialog.text = StringFromKey("PiratesLine_dialog_205");
			link.l1 = StringFromKey("PiratesLine_dialog_206");
			link.l1.go = "PL_Q8_QFackMorgan_9";
		break;
		case "PL_Q8_QFackMorgan_9":
			dialog.text = StringFromKey("PiratesLine_dialog_207");
			link.l1 = StringFromKey("PiratesLine_dialog_208");
			link.l1.go = "PL_Q8_QFackMorgan_10";
		break;
		case "PL_Q8_QFackMorgan_10":
			dialog.text = StringFromKey("PiratesLine_dialog_209", pchar);
			link.l1 = StringFromKey("PiratesLine_dialog_210");
			link.l1.go = "PL_Q8_QFackMorgan_11";
		break;
		case "PL_Q8_QFackMorgan_11":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("PortRoyal_houseS1")], true);
			SetTimerFunction("PQ8_openPanama_2", 0, 0, 30);
			pchar.questTemp.piratesLine = "Panama_backToShip";
			AddQuestRecord("Pir_Line_8_Panama", "14");
			Pchar.quest.PL_Q8_backFight_1.win_condition.l1 = "location";
			Pchar.quest.PL_Q8_backFight_1.win_condition.l1.location = "Panama_jungle_04";
			Pchar.quest.PL_Q8_backFight_1.function = "PL_Q8_backFight_1";
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload4", "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			// evganat - пасха
			sld = characterFromID("Providencia_Mayor");
			sld.dialog.currentnode = "BuyMorganFrigate";

			DialogExit();

			DeleteAttribute(&TEV, "BlockMoneyAchievements");
		break;
	}
}
