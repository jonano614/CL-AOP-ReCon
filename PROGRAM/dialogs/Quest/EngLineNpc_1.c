// Герцог Альбермаль и другие
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
			dialog.text = StringFromKey("EngLineNpc_1_1");
			link.l1 = StringFromKey("EngLineNpc_1_2");
			link.l1.go = "exit";

			//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
			//Альбермаль, англ.линейка, квест №1
			if (npchar.id == "Albermal")
			{
				dialog.text = StringFromKey("EngLineNpc_1_3");
				link.l1 = StringFromKey("EngLineNpc_1_4", pchar, GetFullName(pchar));
				link.l1.go = "Step_E1_1";
			}
			// тюремщик в Кюрасао, квест №4
			if (npchar.id == "Hoverd_Tantum")
			{
				dialog.text = StringFromKey("EngLineNpc_1_5", pchar);
				link.l1 = StringFromKey("EngLineNpc_1_6");
				link.l1.go = "Step_E4_1";
			}
			// ==> Комендант форта Оранж,  квест №5
			if (npchar.id == "Orange_Comendant")
			{
				dialog.text = StringFromKey("EngLineNpc_1_7", pchar);
				link.l1 = StringFromKey("EngLineNpc_1_8");
				link.l1.go = "Step_E5_1";
			}
			// ==> Квест №6, Моррис Уильямс
			if (npchar.id == "Morris_Willams")
			{
				dialog.text = StringFromKey("EngLineNpc_1_9", pchar);
				link.l1 = StringFromKey("EngLineNpc_1_10");
				link.l1.go = "exit";
			}
			if (pchar.questTemp.State == "MorrisWillams_GoToMorrisBegin" && npchar.id == "Morris_Willams")
			{
				dialog.text = StringFromKey("EngLineNpc_1_11");
				link.l1 = StringFromKey("EngLineNpc_1_12", pchar);
				link.l1.go = "Step_E6_20";
			}
			if (pchar.questTemp.State == "MorrisWillams_AfterFirstTalkingWithMorris" && npchar.id == "Morris_Willams")
			{
				dialog.text = StringFromKey("EngLineNpc_1_13", pchar.name);
				link.l1 = StringFromKey("EngLineNpc_1_14");
				link.l1.go = "exit";
			}
			if (pchar.questTemp.State == "MorrisWillams_ModifordGood5000" && npchar.id == "Morris_Willams")
			{
				LAi_ActorSetSitMode(pchar);
				dialog.text = StringFromKey("EngLineNpc_1_15", pchar);
				link.l1 = StringFromKey("EngLineNpc_1_16");
				link.l1.go = "Step_E6_2";
			}
			if (pchar.questTemp.State == "MorrisWillams_ModifordPolitic" && npchar.id == "Morris_Willams")
			{
				dialog.text = StringFromKey("EngLineNpc_1_17");
				link.l1 = StringFromKey("EngLineNpc_1_18");
				link.l1.go = "Step_E6_6";
			}
			if (pchar.questTemp.State == "MorrisWillams_PinnaceNotFound" || pchar.questTemp.State == "MorrisWillams_2PinnaceNotFound")
			{
				dialog.text = StringFromKey("EngLineNpc_1_19", pchar);
				link.l1 = StringFromKey("EngLineNpc_1_20", pchar);
				link.l1.go = "Step_E6_11";
			}
			if (pchar.questTemp.State == "MorrisWillams_PinnaceBoard" && npchar.id == "Morris_Willams")
			{
				dialog.text = StringFromKey("EngLineNpc_1_21", pchar);
				link.l1 = StringFromKey("EngLineNpc_1_22", pchar);
				link.l1.go = "Step_E6_10";
			}
			if (pchar.questTemp.State == "MorrisWillams_PinnaceBoardNotFoundMoney" && npchar.id == "Morris_Willams")
			{
				dialog.text = StringFromKey("EngLineNpc_1_23", pchar);
				link.l1 = StringFromKey("EngLineNpc_1_24", pchar);
				link.l1.go = "Step_E6_11";
			}
			if (pchar.questTemp.State == "MorrisWillams_DieHard" && npchar.id == "Morris_Willams")
			{
				dialog.text = StringFromKey("EngLineNpc_1_25", pchar);
				link.l1 = StringFromKey("EngLineNpc_1_26", pchar);
				link.l1.go = "Step_E6_11";
			}
			if (pchar.questTemp.State == "MorrisWillams_PinnaceSink" && npchar.id == "Morris_Willams")
			{
				dialog.text = StringFromKey("EngLineNpc_1_27", pchar);
				link.l1 = StringFromKey("EngLineNpc_1_28", pchar);
				link.l1.go = "Step_E6_11";
			}
			// ==> Квест №12, диалоги с полковником Томасом Линчем
			if (pchar.questTemp.State == "ColonelLinch_GoToKingstown")
			{
				dialog.text = StringFromKey("EngLineNpc_1_29");
				link.l1 = StringFromKey("EngLineNpc_1_30", GetFullName(pchar));
				link.l1.go = "Step_E12_1";
			}

			if (pchar.questTemp.State == "ColonelLinch_ArrestModiford")
			{
				dialog.text = StringFromKey("EngLineNpc_1_31");
				link.l1 = StringFromKey("EngLineNpc_1_32");
				link.l1.go = "exit";
			}
		break;

		//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
		case "Step_E1_1":
			if (GetQuestPastDayParam("questTemp") < 2)
			{
				dialog.text = StringFromKey("EngLineNpc_1_33");
				link.l1 = StringFromKey("EngLineNpc_1_34", pchar);
				link.l1.go = "Go_with_Albermal";
				link.l2 = StringFromKey("EngLineNpc_1_35");
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("EngLineNpc_1_36");
				link.l1 = StringFromKey("EngLineNpc_1_37", pchar);
				link.l1.go = "Go_with_Albermal";
				link.l2 = StringFromKey("EngLineNpc_1_38");
				link.l2.go = "exit";
				ChangeCharacterReputation(pchar, -1);
			}
			NextDiag.TempNode = "Step_E1_1";
		break;

		case "Go_with_Albermal":
			AddQuestRecord("Eng_Line_1_Albermal", "2");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.quest.fight_withSpanish_Albermal.win_condition.l1 = "location";
			pchar.quest.fight_withSpanish_Albermal.win_condition.l1.location = "Antigua";
			pchar.quest.fight_withSpanish_Albermal.win_condition = "fight_withSpanish_Albermal";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
		break;

		case "in_the_SentJons":
			if (GetQuestPastDayParam("questTemp") < 14)
			{
				dialog.text = StringFromKey("EngLineNpc_1_39");
				link.l1 = StringFromKey("EngLineNpc_1_40");
				link.l1.go = "Albermal_go_out";
				pchar.questTemp.State = "Albermal_good_time";
			}
			else
			{
				dialog.text = StringFromKey("EngLineNpc_1_41");
				link.l1 = StringFromKey("EngLineNpc_1_42");
				link.l1.go = "Albermal_go_out";
				ChangeCharacterReputation(pchar, -4);
				pchar.questTemp.State = "Albermal_late";
			}
			GiveItem2Character(pchar, "letter_Albermal");
			NextDiag.TempNode = "in_the_SentJons";
		break;

		case "Albermal_go_out":
			AddQuestRecord("Eng_Line_1_Albermal", "4");
			RemovePassenger(pchar, npchar);
			DialogExit();
			// уходит
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload2", "none", "", "", "", 10.0);
			LAi_SetPlayerType(pchar);
			NPChar.LifeDay = 1; // уберем нпс на след.день.
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//********************************* Диалоги тюремщика по четвертому квесту английки **********************************
		case "Step_E4_1":
			dialog.text = StringFromKey("EngLineNpc_1_43", pchar);
			link.l1 = StringFromKey("EngLineNpc_1_44");
			link.l1.go = "Step_E4_2";
		break;

		case "Step_E4_2":
			dialog.text = StringFromKey("EngLineNpc_1_45", pchar);
			link.l1 = StringFromKey("EngLineNpc_1_46", pchar);
			link.l1.go = "Step_E4_3";
		break;

		case "Step_E4_3":
			dialog.text = StringFromKey("EngLineNpc_1_47", pchar);
			link.l1 = StringFromKey("EngLineNpc_1_48");
			link.l1.go = "Step_E4_4";
		break;

		case "Step_E4_4":
			dialog.text = StringFromKey("EngLineNpc_1_49");
			link.l1 = StringFromKey("EngLineNpc_1_50", pchar);
			link.l1.go = "Step_E4_5";
		break;

		case "Step_E4_5":
			dialog.text = StringFromKey("EngLineNpc_1_51", pchar);
			link.l1 = StringFromKey("EngLineNpc_1_52");
			link.l1.go = "Step_E4_6";
		break;

		case "Step_E4_6":
			DoQuestReloadToLocation("Villemstad_prison", "goto", "goto12", "");
			AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "7");
			ChangeCharacterReputation(pchar, -1);  // за обман.
			GiveItem2Character(pchar, "blade1");   // себельку герою; и этого бы не давал, но без оружия солдеры не нападают.
			EquipCharacterbyItem(pchar, "blade1");
			pchar.questTemp.State = "Intelligence_Curacao_OutPrison";
			pchar.questTemp.jailCanMove = false; //на всякий случай
			AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
			//==> делаем солдат поменьше, а то хрен выберешься 
			for (int i = 1; i <= 4; i++)
			{
				sld = characterFromId("VillemstadJailSold_" + i);
				if (sld.location.locator != "soldier3")
				{
					ChangeCharacterAddress(sld, "None", "");
				}
			}
			ChangeCharacterAddress(npchar, "None", "");
			DialogExit();
		break;
		//*************************************** Диалог коменданта форта Оранж *********************************
		case "Step_E5_1":
			LAi_SetPlayerType(pchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "AttackFortOrange_AfterFightWithCommendant");
			ChangeCharacterHunterScore(pchar, "holhunter", 70);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//**************************************** Диалоги Морриса Уильямса **************************************
		case "Step_E6_2":
			dialog.text = StringFromKey("EngLineNpc_1_53");
			link.l1 = StringFromKey("EngLineNpc_1_54");
			link.l1.go = "Step_E6_3";
		break;

		case "Step_E6_3":
			dialog.text = StringFromKey("EngLineNpc_1_55");
			link.l1 = StringFromKey("EngLineNpc_1_56");
			link.l1.go = "Step_E6_4";
		break;

		case "Step_E6_4":
			dialog.text = StringFromKey("EngLineNpc_1_57");
			link.l1 = StringFromKey("EngLineNpc_1_58");
			link.l1.go = "Step_E6_5";
		break;

		case "Step_E6_5":
			AddQuestRecord("Eng_Line_6_MorrisWillams", "4");
			pchar.questTemp.State = "MorrisWillams_ToModifordForCoolTalking";
			NextDiag.CurrentNode = "Willams_waiting";
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
		break;

		case "Willams_waiting": // если ГГ подойдет в таверне к Уильямсу до проведения разговора с Мэдифордом
			dialog.text = StringFromKey("EngLineNpc_1_59", pchar);
			link.l1 = StringFromKey("EngLineNpc_1_60");
			link.l1.go = "exit";
			NextDiag.TempNode = "Willams_waiting";
		break;

		case "Step_E6_6":
			dialog.text = StringFromKey("EngLineNpc_1_61", pchar);
			link.l1 = StringFromKey("EngLineNpc_1_62");
			link.l1.go = "Step_E6_7";
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); //открываем выход из города
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false);
			LocatorReloadEnterDisable("PortRoyal_town", "boat", false);
		break;

		case "Step_E6_7":
			dialog.text = StringFromKey("EngLineNpc_1_63");
			link.l1 = StringFromKey("EngLineNpc_1_64");
			link.l1.go = "Willams_GoogBye";
			link.l2 = StringFromKey("EngLineNpc_1_65", pchar);
			link.l2.go = "Willams_GiveMoney";
			link.l3 = StringFromKey("EngLineNpc_1_66");
			link.l3.go = "Willams_BackGoods";
		break;

		case "Willams_GoogBye":
			dialog.text = StringFromKey("EngLineNpc_1_67");
			link.l1 = StringFromKey("EngLineNpc_1_68");
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "10";
			pchar.questTemp.CurQuestNumber = "7";
			ChangeCharacterReputation(pchar, -100);
			AddCharacterExpToSkill(pchar, "Leadership", -350);
			AddCharacterExpToSkill(pchar, "Accuracy", -50);
			AddCharacterExpToSkill(pchar, "Commerce", -150);
			AddCharacterExpToSkill(pchar, "Sneak ", -150);
			AddCharacterExpToSkill(pchar, "Fencing  ", -100);
			AddQuestRecord("Eng_Line_6_MorrisWillams", "6");
			CloseQuestHeader("Eng_Line_6_MorrisWillams");
			NextDiag.TempNode = "Willams_Fack";
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			RemoveLandQuestmark_Main(CharacterFromID("SanJuan_tavernkeeper"), "Eng_Line");
			AddLandQuestmark_Main_WithCondition(CharacterFromID("eng_guber"), "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("EngLineNpc_1_69"), ENGLAND, 5, 1);
		break;

		case "Willams_Fack":
			dialog.text = StringFromKey("EngLineNpc_1_70", GetFullName(pchar));
			link.l1 = StringFromKey("EngLineNpc_1_71");
			link.l1.go = "exit";
			NextDiag.TempNode = "Willams_Fack";
			//слухи
			AddSimpleRumour(
				StringFromKey("EngLineNpc_1_72", pchar), ENGLAND, 5, 1);
		break;

		case "Willams_GiveMoney":
			dialog.text = StringFromKey("EngLineNpc_1_73");
			link.l1 = StringFromKey("EngLineNpc_1_74", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "Step_E6_7";
			if (sti(pchar.money) >= 140000)
			{
				dialog.text = StringFromKey("EngLineNpc_1_75", pchar);
				link.l1 = StringFromKey("EngLineNpc_1_76");
				link.l1.go = "exit";
				SaveCurrentQuestDateParam("questTemp");
				pchar.questTemp.State = "empty";
				pchar.questTemp.Waiting_time = "5";
				pchar.questTemp.CurQuestNumber = "7";
				ChangeCharacterReputation(pchar, 20);
				AddCharacterExpToSkill(pchar, "Leadership", 150);
				AddCharacterExpToSkill(pchar, "Commerce", 250);
				AddCharacterExpToSkill(pchar, "Sneak ", 50);
				AddCharacterExpToSkill(pchar, "Defence", 150);
				AddQuestRecord("Eng_Line_6_MorrisWillams", "7");
				AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex", GetSexPhrase("", "а"));
				CloseQuestHeader("Eng_Line_6_MorrisWillams");
				AddMoneyToCharacter(pchar, -140000);
				NextDiag.TempNode = "Willams_NiceTalking";
				RemoveLandQuestmark_Main(npchar, "Eng_Line");
				AddLandQuestmark_Main_WithCondition(CharacterFromID("eng_guber"), "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
				AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
				//слухи
				AddSimpleRumour(
					StringFromKey("EngLineNpc_1_77"), ENGLAND, 5, 1);
			}
		break;

		case "Willams_NiceTalking":
			dialog.text = StringFromKey("EngLineNpc_1_78", GetFullName(pchar));
			link.l1 = StringFromKey("EngLineNpc_1_79");
			link.l1.go = "exit";
			NextDiag.TempNode = "Willams_NiceTalking";
		break;

		case "Willams_BackGoods":
			dialog.text = StringFromKey("EngLineNpc_1_80");
			link.l1 = StringFromKey("EngLineNpc_1_81");
			link.l1.go = "Step_E6_8";
		break;

		case "Step_E6_8":
			dialog.text = StringFromKey("EngLineNpc_1_82");
			link.l1 = StringFromKey("EngLineNpc_1_83");
			link.l1.go = "Step_E6_9";
		break;

		case "Step_E6_9":
			dialog.text = StringFromKey("EngLineNpc_1_84");
			link.l1 = StringFromKey("EngLineNpc_1_85");
			link.l1.go = "exit";
			NextDiag.TempNode = "Willams_WaitSeek";
			pchar.questTemp.State = "MorrisWillams_SeekSpanishGoods";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "8");
			AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex", GetSexPhrase("ся", "ась"));
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			AddLandQuestmark_Main(CharacterFromID("PortRoyal_PortMan"), "Eng_Line");
		break;

		case "Willams_WaitSeek":
			dialog.text = StringFromKey("EngLineNpc_1_86", pchar);
			link.l1 = StringFromKey("EngLineNpc_1_87");
			link.l1.go = "exit";
			NextDiag.TempNode = "Willams_WaitSeek";
		break;

		case "Step_E6_10":
			dialog.text = StringFromKey("EngLineNpc_1_88");
			link.l1 = StringFromKey("EngLineNpc_1_89");
			link.l1.go = "MorrisWillams_NotGiveMoney";
			link.l2 = StringFromKey("EngLineNpc_1_90", pchar);
			link.l2.go = "MorrisWillams_GiveMoney";
			NextDiag.TempNode = "Willams_NiceTalking";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.State = "empty";
			pchar.questTemp.CurQuestNumber = "7";
		break;

		case "MorrisWillams_NotGiveMoney":
			dialog.text = StringFromKey("EngLineNpc_1_91", pchar);
			link.l1 = StringFromKey("EngLineNpc_1_92");
			link.l1.go = "MorrisWillams_GoAway";
			pchar.questTemp.Waiting_time = "10";
			ChangeCharacterReputation(pchar, -100);
			AddCharacterExpToSkill(pchar, "Leadership", -150);
			AddCharacterExpToSkill(pchar, "Accuracy", -200);
			AddCharacterExpToSkill(pchar, "Commerce", -250);
			AddCharacterExpToSkill(pchar, "Sneak ", -170);
			AddCharacterExpToSkill(pchar, "Fencing  ", -140);
			AddQuestRecord("Eng_Line_6_MorrisWillams", "13");
			AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("Eng_Line_6_MorrisWillams");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			AddLandQuestmark_Main_WithCondition(CharacterFromID("eng_guber"), "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("EngLineNpc_1_93"), ENGLAND, 5, 1);
		break;

		case "MorrisWillams_GiveMoney":
			if (sti(pchar.money) >= 140000)
			{
				dialog.text = StringFromKey("EngLineNpc_1_94", pchar);
				link.l1 = StringFromKey("EngLineNpc_1_95");
				link.l1.go = "Step_E6_14";
			}
			else
			{
				dialog.text = StringFromKey("EngLineNpc_1_96");
				link.l1 = StringFromKey("EngLineNpc_1_97", pchar);
				link.l1.go = "exit";
				NextDiag.TempNode = "MorrisWillams_GiveMoney";
			}
		break;

		case "Step_E6_14":
			dialog.text = StringFromKey("EngLineNpc_1_98", pchar);
			link.l1 = StringFromKey("EngLineNpc_1_99");
			link.l1.go = "exit";
			pchar.questTemp.Waiting_time = "2";
			ChangeCharacterReputation(pchar, 20);
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Accuracy", 100);
			AddCharacterExpToSkill(pchar, "Commerce", 250);
			AddCharacterExpToSkill(pchar, "Sneak", 70);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "Defence", 150);
			AddQuestRecord("Eng_Line_6_MorrisWillams", "14");
			AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("Eng_Line_6_MorrisWillams");
			AddMoneyToCharacter(pchar, -140000);
			NextDiag.TempNode = "Willams_NiceTalking";
			Pchar.quest.MorrisWillams_SeekCirassa.win_condition.l1 = "location";
			Pchar.quest.MorrisWillams_SeekCirassa.win_condition.l1.location = "Shore_ship2";
			Pchar.quest.MorrisWillams_SeekCirassa.win_condition = "MorrisWillams_SeekCirassa";
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			AddLandQuestmark_Main_WithCondition(CharacterFromID("eng_guber"), "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("EngLineNpc_1_100", pchar), ENGLAND, 5, 1);
		break;

		case "MorrisWillams_GoAway":
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "PortRoyal_tavern", "tables", "stay8");
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;

		case "Step_E6_11":
			dialog.text = StringFromKey("EngLineNpc_1_101", pchar);
			link.l1 = StringFromKey("EngLineNpc_1_102");
			link.l1.go = "Step_E6_12";
			link.l2 = StringFromKey("EngLineNpc_1_103", pchar);
			link.l2.go = "Willams_GoogBye";
		break;

		case "Step_E6_12":
			dialog.text = StringFromKey("EngLineNpc_1_104");
			link.l1 = StringFromKey("EngLineNpc_1_105");
			link.l1.go = "Step_E6_13";
		break;

		case "Step_E6_13":
			dialog.text = StringFromKey("EngLineNpc_1_106", pchar.name);
			link.l1 = StringFromKey("EngLineNpc_1_107");
			link.l1.go = "MorrisWillams_GoAway";
			pchar.questTemp.State = "MorrisWillams_GoToHimselfBussines";
			Pchar.quest.MorrisWillams_Arrest.win_condition.l1 = "ExitFromLocation";
			Pchar.quest.MorrisWillams_Arrest.win_condition.l1.location = "PortRoyal_tavern";
			Pchar.quest.MorrisWillams_Arrest.win_condition = "MorrisWillams_Arrest";
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
		break;

		case "Step_E6_20":
			dialog.text = StringFromKey("EngLineNpc_1_108");
			link.l1 = StringFromKey("EngLineNpc_1_109");
			link.l1.go = "Step_E6_21";
		break;
		case "Step_E6_21":
			dialog.text = StringFromKey("EngLineNpc_1_110");
			link.l1 = StringFromKey("EngLineNpc_1_111");
			link.l1.go = "Step_E6_22";
		break;
		case "Step_E6_22":
			dialog.text = StringFromKey("EngLineNpc_1_112", pchar);
			link.l1 = StringFromKey("EngLineNpc_1_113");
			link.l1.go = "Step_E6_23";
		break;
		case "Step_E6_23":
			dialog.text = StringFromKey("EngLineNpc_1_114");
			link.l1 = StringFromKey("EngLineNpc_1_115");
			link.l1.go = "Step_E6_24";
		break;
		case "Step_E6_24":
			dialog.text = StringFromKey("EngLineNpc_1_116");
			link.l1 = StringFromKey("EngLineNpc_1_117");
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_AfterFirstTalkingWithMorris";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "2");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
		break;

		//**************************************** Диалоги Томаса Линча **************************************
		case "Step_E12_1":
			dialog.text = StringFromKey("EngLineNpc_1_118");
			link.l1 = StringFromKey("EngLineNpc_1_119");
			link.l1.go = "Step_E12_2";
		break;

		case "Step_E12_2":
			dialog.text = StringFromKey("EngLineNpc_1_120");
			link.l1 = StringFromKey("EngLineNpc_1_121");
			link.l1.go = "Step_E12_3";
		break;

		case "Step_E12_3":
			dialog.text = StringFromKey("EngLineNpc_1_122");
			link.l1 = StringFromKey("EngLineNpc_1_123");
			link.l1.go = "Step_E12_4";
		break;

		case "Step_E12_4":
			dialog.text = StringFromKey("EngLineNpc_1_124");
			link.l1 = StringFromKey("EngLineNpc_1_125");
			link.l1.go = "Step_E12_5";
		break;

		case "Step_E12_5":
			dialog.text = StringFromKey("EngLineNpc_1_126");
			link.l1 = StringFromKey("EngLineNpc_1_127");
			link.l1.go = "Step_E12_6";
		break;

		case "Step_E12_6":
			dialog.text = StringFromKey("EngLineNpc_1_128");
			link.l1 = StringFromKey("EngLineNpc_1_129");
			link.l1.go = "Step_E12_7";
		break;

		case "Step_E12_7":
			dialog.text = StringFromKey("EngLineNpc_1_130");
			link.l1 = StringFromKey("EngLineNpc_1_131");
			link.l1.go = "Step_E12_8";
		break;

		case "Step_E12_8":
			dialog.text = StringFromKey("EngLineNpc_1_132");
			link.l1 = StringFromKey("EngLineNpc_1_133");
			link.l1.go = "Step_E12_9";

		break;

		case "Step_E12_9":
			dialog.text = StringFromKey("EngLineNpc_1_134");
			link.l1 = StringFromKey("EngLineNpc_1_135");
			link.l1.go = "Step_E12_10";
		break;

		case "Step_E12_10":
			dialog.text = StringFromKey("EngLineNpc_1_136");
			link.l1 = StringFromKey("EngLineNpc_1_137");
			link.l1.go = "Step_E12_11";
		break;

		case "Step_E12_11":
			dialog.text = StringFromKey("EngLineNpc_1_138");
			link.l1 = StringFromKey("EngLineNpc_1_139", pchar);
			link.l1.go = "Step_E12_12";
		break;

		case "Step_E12_12":
			dialog.text = StringFromKey("EngLineNpc_1_140");
			link.l1 = StringFromKey("EngLineNpc_1_141");
			link.l1.go = "Step_E12_13";
		break;

		case "Step_E12_13":
			dialog.text = StringFromKey("EngLineNpc_1_142", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("EngLineNpc_1_143");
			link.l1.go = "Step_E12_14";
		break;

		case "Step_E12_14":
			dialog.text = StringFromKey("EngLineNpc_1_144");
			link.l1 = StringFromKey("EngLineNpc_1_145");
			link.l1.go = "exit";
			pchar.questTemp.State = "ColonelLinch_ArrestModiford";
			AddQuestRecord("Eng_Line_12_ColonelLinch", "2");
			AddQuestUserData("Eng_Line_12_ColonelLinch", "sSex", GetSexPhrase("", "а"));
			LAi_SetPlayerType(pchar);
			LAi_SetStayType(npchar);
			NextDiag.TempNode = "YouMustGo";
			AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
		break;

		case "YouMustGo":
			dialog.text = StringFromKey("EngLineNpc_1_146");
			link.l1 = StringFromKey("EngLineNpc_1_147");
			link.l1.go = "exit";
			NextDiag.TempNode = "YouMustGo";
		break;
	}
}
