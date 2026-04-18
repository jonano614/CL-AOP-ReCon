// диалоговый файл №2 на испанку
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
			dialog.text = StringFromKey("SpaLineNpc_2_1");
			link.l1 = StringFromKey("SpaLineNpc_2_2");
			link.l1.go = "exit";

			//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
			if (npchar.id == "Francisco")// квест №2, базар с Франциско
			{
				dialog.text = StringFromKey("SpaLineNpc_2_3", pchar);
				link.l1 = StringFromKey("SpaLineNpc_2_4");
				link.l1.go = "Step_S2_1";
			}
			if (CheckAttribute(pchar, "questTemp.State.Usurer"))// квест №2, малый де Фонкейсао
			{
				dialog.text = StringFromKey("SpaLineNpc_2_5", pchar);
				link.l1 = StringFromKey("SpaLineNpc_2_6");
				link.l1.go = "Step_S2_6";
			}
			if (npchar.id == "Bandit" && CheckAttribute(pchar, "questTemp.State.Store"))// квест №2, бандит на 1-м этаже
			{
				dialog.text = StringFromKey("SpaLineNpc_2_7");
				link.l1 = StringFromKey("SpaLineNpc_2_8");
				link.l1.go = "Step_S2_11";
			}
			if (npchar.id == "JacowDeFonseka" && CheckAttribute(pchar, "questTemp.State.Store"))
			{
				dialog.text = StringFromKey("SpaLineNpc_2_9");
				link.l1 = StringFromKey("SpaLineNpc_2_10");
				link.l1.go = "Step_S2_14";
			}
			if (npchar.id == "PortMansBoy")  //квест №6, посыльный начальника порта.
			{
				dialog.text = StringFromKey("SpaLineNpc_2_11", UpperFirst(GetAddress_Form(NPChar)));
				link.l1 = StringFromKey("SpaLineNpc_2_12");
				link.l1.go = "Step_S6_1";
			}    //квест №7, Моисей Воклейн.
			if (pchar.questTemp.State == "Sp7SavePardal_toAntigua" || pchar.questTemp.State == "Sp7SavePardal_PardalIsSink")
			{
				dialog.text = StringFromKey("SpaLineNpc_2_13", pchar);
				link.l1 = StringFromKey("SpaLineNpc_2_14", pchar);
				link.l1.go = "Step_S7_1";
			}  //квест №8, капитан Ансель.
			if (pchar.questTemp.State == "Sp8SaveCumana_toCumana")
			{
				dialog.text = StringFromKey("SpaLineNpc_2_15");
				link.l1 = StringFromKey("SpaLineNpc_2_16");
				link.l1.go = "exit";
				LAi_SetCurHPMax(npchar);
				QuestAboardCabinDialogExitWithBattle("");
			}
		break;

		//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//*************************** Квест №2, диалоги с Франциско на выходе из Инквизиии ***************************
		case "Step_S2_1":
			dialog.text = StringFromKey("SpaLineNpc_2_17");
			link.l1 = StringFromKey("SpaLineNpc_2_18");
			link.l1.go = "Step_S2_2";
		break;
		case "Step_S2_2":
			dialog.text = StringFromKey("SpaLineNpc_2_19");
			link.l1 = StringFromKey("SpaLineNpc_2_20");
			link.l1.go = "Step_S2_3";
		break;
		case "Step_S2_3":
			dialog.text = StringFromKey("SpaLineNpc_2_21");
			link.l1 = StringFromKey("SpaLineNpc_2_22", pchar);
			link.l1.go = "Step_S2_4";
		break;
		case "Step_S2_4":
			dialog.text = StringFromKey("SpaLineNpc_2_23");
			link.l1 = StringFromKey("SpaLineNpc_2_24");
			link.l1.go = "Step_S2_5";
		break;
		case "Step_S2_5":
			chrDisableReloadToLocation = false;
			pchar.questTemp.State = "Inquisition_afterFrancisco";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 40.0);
			LAi_SetPlayerType(pchar);
			DialogExit();
		break;
		case "Step_S2_6":
			dialog.text = StringFromKey("SpaLineNpc_2_25");
			link.l1 = StringFromKey("SpaLineNpc_2_26");
			link.l1.go = "Step_S2_7";
		break;
		case "Step_S2_7":
			dialog.text = StringFromKey("SpaLineNpc_2_27");
			link.l1 = StringFromKey("SpaLineNpc_2_28");
			link.l1.go = "Step_S2_8";
		break;
		case "Step_S2_8":
			dialog.text = StringFromKey("SpaLineNpc_2_29");
			link.l1 = StringFromKey("SpaLineNpc_2_30");
			link.l1.go = "Step_S2_9";
		break;
		case "Step_S2_9":
			dialog.text = StringFromKey("SpaLineNpc_2_31", pchar);
			link.l1 = StringFromKey("SpaLineNpc_2_32");
			link.l1.go = "Step_S2_10";
		break;
		case "Step_S2_10":
			AddQuestRecord("Spa_Line_2_Inquisition", "8");
			pchar.quest.Inquisition_DieHard.over = "yes";
			Island_SetReloadEnableGlobal("Jamaica", true);
			QuestAboardCabinDialogQuestSurrender();
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("Villemstad_Usurer"), "Spa_Line");
		break;
		case "Step_S2_11":
			dialog.text = StringFromKey("SpaLineNpc_2_33");
			link.l1 = StringFromKey("SpaLineNpc_2_34");
			link.l1.go = "Step_S2_12";
		break;
		case "Step_S2_12":
			dialog.text = StringFromKey("SpaLineNpc_2_35", pchar);
			link.l1 = StringFromKey("SpaLineNpc_2_36");
			link.l1.go = "Step_S2_13";
		break;
		case "Step_S2_13":
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "Step_S2_14":
			dialog.text = StringFromKey("SpaLineNpc_2_37");
			link.l1 = StringFromKey("SpaLineNpc_2_38", GetFullName(pchar));
			link.l1.go = "Step_S2_15";
		break;
		case "Step_S2_15":
			dialog.text = StringFromKey("SpaLineNpc_2_39", pchar);
			link.l1 = StringFromKey("SpaLineNpc_2_40");
			link.l1.go = "Step_S2_16";
		break;
		case "Step_S2_16":
			dialog.text = StringFromKey("SpaLineNpc_2_41");
			link.l1 = StringFromKey("SpaLineNpc_2_42", pchar);
			link.l1.go = "Step_S2_17";
		break;
		case "Step_S2_17":
			dialog.text = StringFromKey("SpaLineNpc_2_43");
			link.l1 = StringFromKey("SpaLineNpc_2_44");
			link.l1.go = "Step_S2_18";
		break;
		case "Step_S2_18":
			dialog.text = StringFromKey("SpaLineNpc_2_45");
			link.l1 = StringFromKey("SpaLineNpc_2_46");
			link.l1.go = "Step_S2_19";
		break;
		case "Step_S2_19":
			dialog.text = StringFromKey("SpaLineNpc_2_47");
			link.l1 = StringFromKey("SpaLineNpc_2_48", pchar);
			link.l1.go = "Step_S2_20";
		break;
		case "Step_S2_20":
			dialog.text = StringFromKey("SpaLineNpc_2_49");
			link.l1 = StringFromKey("SpaLineNpc_2_50");
			link.l1.go = "Step_S2_21";
		break;
		case "Step_S2_21":
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Spa_Line_2_Inquisition", "12");
			AddQuestRecord("Spa_Line_2_Inquisition", "13");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", 5.0);
			pchar.questTemp.State.SeekBible = 1; //флаг на поиск Евангелие
			LocatorReloadEnterDisable("Shore3", "reload2_back", true); //закрываем для особо хитрых
			DialogExit();
			AddLandQuestmark_Main(CharacterFromID("Villemstad_Trader"), "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("Pirates_shipyarder"), "Spa_Line");
		break;
		//*************************** Квест №6, базар с посыльным начальника порта ***************************
		case "Step_S6_1":
			dialog.text = StringFromKey("SpaLineNpc_2_51");
			link.l1 = StringFromKey("SpaLineNpc_2_52");
			link.l1.go = "Step_S6_2";
		break;
		case "Step_S6_2":
			dialog.text = StringFromKey("SpaLineNpc_2_53");
			link.l1 = StringFromKey("SpaLineNpc_2_54");
			link.l1.go = "Step_S6_3";
		break;
		case "Step_S6_3":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Spa_Line_6_TakeMessangeer", "3");
			bDisableFastReload = true; //закрываем фаст релоад
			SaveCurrentQuestDateParam("questTemp");
			Pchar.quest.Sp6TakeMess_Interception.win_condition.l1 = "location";
			Pchar.quest.Sp6TakeMess_Interception.win_condition.l1.location = "Tortuga_town";
			Pchar.quest.Sp6TakeMess_Interception.win_condition = "Sp6TakeMess_Interception";
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();
		break;
		//*************************** Квест №7, базар с Моисеем Воклейном при абордаже ***************************
		case "Step_S7_1":
			dialog.text = StringFromKey("SpaLineNpc_2_55");
			link.l1 = StringFromKey("SpaLineNpc_2_56");
			link.l1.go = "exit";
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
		break;

	}
}


