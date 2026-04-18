// Джон Моррис, авторитетный корсар по английской линейке
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			dialog.text = StringFromKey("JohnMorris_1");
			link.l1 = StringFromKey("JohnMorris_2");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.Sharp") && StrStartsWith(pchar.questTemp.Sharp, "takeRumour"))
			{
				link.l1 = StringFromKey("JohnMorris_3", pchar);
				link.l1.go = "SharpPearl_1";
			}
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "I_know_you_good":
			dialog.text = StringFromKey("JohnMorris_7", LinkRandPhrase(
						StringFromKey("JohnMorris_4", pchar, GetFullName(pchar)),
						StringFromKey("JohnMorris_5", RandSwear(), GetFullName(pchar)),
						StringFromKey("JohnMorris_6", pchar, GetFullName(pchar))));
			link.l1 = StringFromKey("JohnMorris_10", RandPhraseSimple(
						StringFromKey("JohnMorris_8", pchar),
						StringFromKey("JohnMorris_9")));
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (CheckAttribute(pchar, "questTemp.Sharp") && StrStartsWith(pchar.questTemp.Sharp, "takeRumour"))
			{
				link.l1 = StringFromKey("JohnMorris_11", pchar);
				link.l1.go = "SharpPearl_1";
			}
		break;

		//********************* капитан Шарп *********************
		case "SharpPearl_1":
			dialog.text = StringFromKey("JohnMorris_12", pchar);
			link.l1 = StringFromKey("JohnMorris_13");
			link.l1.go = "SharpPearl_2";
			pchar.questTemp.Sharp = "seekSharp";
			RemoveLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl");
			SeaPearl_PiratesBaron_DelQuestMarks();
			SeaPearl_Hostess_AddQuestMarks();
		break;
		case "SharpPearl_2":
			AddQuestRecord("SharpPearl", "16");
			AddQuestUserData("SharpPearl", "sName", GetFullName(NPChar));

			dialog.text = StringFromKey("JohnMorris_14");
			link.l1 = StringFromKey("JohnMorris_15");
			link.l1.go = "exit";
		break;
		//********************* Английская линейка *********************
		case "EngLine_quests":
			dialog.text = StringFromKey("JohnMorris_16");
			link.l1 = StringFromKey("JohnMorris_17");
			link.l1.go = "exit";
			switch (pchar.questTemp.State)   // Доступ к квестам
			{
				case "go_talks_with_pirates":
					dialog.text = StringFromKey("JohnMorris_18", pchar);
					link.l1 = StringFromKey("JohnMorris_19", pchar);
					link.l1.go = "Step_1";
				break;
			}
		break;

		case "Step_1":
			dialog.text = StringFromKey("JohnMorris_20", pchar);
			link.l1 = StringFromKey("JohnMorris_21");
			link.l1.go = "Step_2";
		break;

		case "Step_2":
			dialog.text = StringFromKey("JohnMorris_22");
			link.l1 = StringFromKey("JohnMorris_23");
			link.l1.go = "Step_3";
		break;

		case "Step_3":
			dialog.text = StringFromKey("JohnMorris_24");
			link.l1 = StringFromKey("JohnMorris_25");
			link.l1.go = "Step_4";
		break;

		case "Step_4":
			dialog.text = StringFromKey("JohnMorris_26", pchar);
			link.l1 = StringFromKey("JohnMorris_27");
			link.l1.go = "exit";

			AddQuestRecord("Eng_Line_2_Talking", "5");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			pchar.questTemp.Count = makeint(sti(pchar.questTemp.Count) + 1);
			if (pchar.questTemp.Count == "4")
			{
				pchar.questTemp.State = "after_talks_with_pirates";
				AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
			}
			NextDiag.TempNode = "First time";
		break;

		case "Lets_go_bussines":
			dialog.text = StringFromKey("JohnMorris_28");
			link.l1 = StringFromKey("JohnMorris_29");
			link.l1.go = "Step_5";
		break;

		case "Step_5":
			if (GetCompanionQuantity(pchar) != 4)
			{
				dialog.text = StringFromKey("JohnMorris_30");
				link.l1 = StringFromKey("JohnMorris_31");
				link.l1.go = "Step_6";
			}
			else
			{
				dialog.text = StringFromKey("JohnMorris_32");
				link.l1 = StringFromKey("JohnMorris_33");
				link.l1.go = "exit";
				NextDiag.TempNode = "First time";
			}

		break;

		case "Step_6":
			AddQuestRecord("Eng_Line_3_Morgan", "5");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			LAi_SetActorType(NPChar);
			LAi_ActorSetStayMode(NPChar);
			ChangeCharacterAddressGroup(NPChar, "PortSpein_houseF2", "goto", "goto3");
			CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 6, false);
			Fantom_SetBalls(npchar, "pirate");
			npchar.CompanionEnemyEnable = false;  // нет отпора при обстреле
			pchar.questTemp.CompanionQuantity = makeint(sti(pchar.questTemp.CompanionQuantity) + 1);
			pchar.questTemp.CompanionQuantity.Morris = true;
			NextDiag.TempNode = "Have_hot_bussines";
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

		break;

		case "Have_hot_bussines":   // Если геймеру вдруг захочется ещё пообщаться, не знаю, сможет ли. Но на всякий случай.
			dialog.text = StringFromKey("JohnMorris_34");
			link.l1 = StringFromKey("JohnMorris_35");
			link.l1.go = "exit";
			NextDiag.TempNode = "Have_hot_bussines";
		break;

		case "Gold_found_in_fort":    // Нода разговора в форте Куманы
			if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Morris") && !IsCompanion(characterFromID("John Morris")))
			{
				dialog.text = StringFromKey("JohnMorris_36", pchar);
			}
			else
			{
				dialog.text = StringFromKey("JohnMorris_37", pchar);
			}
			link.l1 = StringFromKey("JohnMorris_38", pchar);
			link.l1.go = "Step_7";
		break;

		case "Step_7":
			dialog.text = StringFromKey("JohnMorris_39");
			link.l1 = StringFromKey("JohnMorris_40");
			link.l1.go = "Step_8";
		break;

		case "Step_8":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15.0);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
		break;

		//********************* Французская линейка *********************
		case "FraLine8_talk":
			dialog.text = StringFromKey("JohnMorris_41", pchar);
			link.l1 = StringFromKey("JohnMorris_42", GetFullName(pchar));
			link.l1.go = "Step_F8_1";
		break;
		case "Step_F8_1":
			dialog.text = StringFromKey("JohnMorris_43");
			link.l1 = StringFromKey("JohnMorris_44");
			link.l1.go = "Step_F8_2";
		break;
		case "Step_F8_2":
			dialog.text = StringFromKey("JohnMorris_45");
			link.l1 = StringFromKey("JohnMorris_46");
			link.l1.go = "Step_F8_3";
		break;
		case "Step_F8_3":
			dialog.text = StringFromKey("JohnMorris_47");
			link.l1 = StringFromKey("JohnMorris_48");
			link.l1.go = "Step_F8_4";
		break;
		case "Step_F8_4":
			dialog.text = StringFromKey("JohnMorris_49", pchar);
			link.l1 = StringFromKey("JohnMorris_50");
			link.l1.go = "Step_F8_5";
		break;
		case "Step_F8_5":
			dialog.text = StringFromKey("JohnMorris_51");
			link.l1 = StringFromKey("JohnMorris_52");
			link.l1.go = "Step_F8_6";
		break;
		case "Step_F8_6":
			dialog.text = StringFromKey("JohnMorris_53");
			link.l1 = StringFromKey("JohnMorris_54", pchar);
			link.l1.go = "Step_F8_7";
		break;
		case "Step_F8_7":
			dialog.text = StringFromKey("JohnMorris_55");
			link.l1 = StringFromKey("JohnMorris_56");
			link.l1.go = "exit";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "6");
			AddQuestUserData("Fra_Line_8_ThreeCorsairs", "sSex", GetSexPhrase("ен", "на"));
			NextDiag.TempNode = "Step_F8_Result";
			// ==> открываем дверь таверны Порт-Ройал - там кэп Гей.
			LocatorReloadEnterDisable("PortRoyal_tavern", "reload2_back", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortRoyal_tavern_upstairs")], false);
			ref sld = GetCharacter(NPC_GenerateCharacter("CaptainGay", "bocman", "man", "man", 40, PIRATE, -1, true)); //watch_quest_moment
			FantomMakeCoolFighter(sld, 40, 100, 90, "blade34", "pistol5", 150);
			sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
			sld.name = FindPersonalName("CaptainGay_name");
			sld.lastname = FindPersonalName("CaptainGay_lastname");
			sld.items.ShipsJournal = 1;
			sld.money = 65720;
			sld.items.potion4 = 4;
			sld.items.potionrum = 1;
			sld.items.potionwine = 2;
			sld.items.sculMa2 = 1;
			sld.items.jewelry17 = 30;
			sld.items.jewelry18 = 15;
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			LAi_NoRebirthEnable(sld);
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_tavern_upstairs", "goto", "goto1");
			AddLandQuestmark_Main(sld, "Fra_Line");
			AddLandQuestmark_Main(CharacterFromID("PortRoyal_tavernkeeper"), "Fra_Line");
			AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "FraLine_8_ThreeCorsairs_JohnMorris_QuestMarkCondition");
		break;
		case "Step_F8_Result":
			dialog.text = StringFromKey("JohnMorris_57", pchar);
			if (CheckCharacterItem(pchar, "ShipsJournal"))
			{
				link.l1 = StringFromKey("JohnMorris_58");
				link.l1.go = "Step_F8_8";
			}
			else
			{
				link.l1 = StringFromKey("JohnMorris_59");
				link.l1.go = "exit";
			}
		break;
		case "Step_F8_8":
			dialog.text = StringFromKey("JohnMorris_60");
			link.l1 = StringFromKey("JohnMorris_61");
			link.l1.go = "exit";
			pchar.questTemp.Count = makeint(pchar.questTemp.Count) + 1;
			NextDiag.TempNode = "I_know_you_good";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "7");
			AddQuestUserData("Fra_Line_8_ThreeCorsairs", "sSex", GetSexPhrase("", "а"));
			TakeItemFromCharacter(pchar, "ShipsJournal");
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;

		//********************* Пиратская линейка *********************
		case "PL_Q8_deck":
			dialog.text = StringFromKey("JohnMorris_62");
			link.l1 = StringFromKey("JohnMorris_63");
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;
		case "PL_Q8_deck_1":
			dialog.text = StringFromKey("JohnMorris_64");
			link.l1 = StringFromKey("JohnMorris_65");
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;

	}
}
