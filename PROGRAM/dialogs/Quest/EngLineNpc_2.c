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
			dialog.text = StringFromKey("EngLineNpc_2_1");
			link.l1 = StringFromKey("EngLineNpc_2_2");
			link.l1.go = "exit";

			//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
			// ==> Боцман Морриса Уильямса
			if (pchar.questTemp.State == "MorrisWillams_ModifordGood5000" && npchar.id == "Bocman_Willams")// перехват на посыльного Морриса Уильямса
			{
				dialog.text = StringFromKey("EngLineNpc_2_3", pchar);
				link.l1 = StringFromKey("EngLineNpc_2_4");
				link.l1.go = "Step_E6_1";
			}
			if (pchar.questTemp.State == "MorrisWillams_GoToHimselfBussines" && npchar.id == "Bocman_Willams")// перехват на посыльного Морриса Уильямса второй раз
			{
				dialog.text = StringFromKey("EngLineNpc_2_5");
				link.l1 = StringFromKey("EngLineNpc_2_6");
				link.l1.go = "Step_E6_4";
			}
			// ==> Джилиан Эттербери.
			if (pchar.questTemp.State == "MorrisWillams_ArrestedSeekInfoWomen" && npchar.id == "Gillian Atterbury") // англ.линейка квест №6, разговор с Джиллиан Эттербери
			{
				dialog.text = StringFromKey("EngLineNpc_2_7");
				link.l2 = StringFromKey("EngLineNpc_2_8");
				link.l2.go = "Step_E6_25";
			}
			if (pchar.questTemp.State == "MorrisWillams_SeekHusband" && npchar.id == "Gillian Atterbury") // англ.линейка квест №6, разговор с Джиллиан Эттербери после дачи задания
			{
				dialog.text = StringFromKey("EngLineNpc_2_9", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("EngLineNpc_2_10");
				link.l1.go = "exit";
			}
			if (npchar.id == "Gillian Atterbury" && CheckAttribute(npchar, "TempQuest.SavedHusband")) // разговор с Джиллиан Эттербери, если мы спасли её мужа
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("EngLineNpc_2_11", UpperFirst(GetAddress_Form(NPChar))),
							StringFromKey("EngLineNpc_2_12", GetAddress_Form(NPChar)),
							StringFromKey("EngLineNpc_2_13", UpperFirst(GetAddress_Form(NPChar))),
							StringFromKey("EngLineNpc_2_14", UpperFirst(GetAddress_Form(NPChar))), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("EngLineNpc_2_15"),
							StringFromKey("EngLineNpc_2_16"),
							StringFromKey("EngLineNpc_2_17"),
							StringFromKey("EngLineNpc_2_18"), npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			// ==> Один из бандитов в пещере, удерживающий мужа Джилиан
			if (pchar.questTemp.State == "MorrisWillams_SeekHusband" && npchar.id == "Bandit3")   // базар в пещере перед боевкой
			{
				dialog.text = StringFromKey("EngLineNpc_2_19");
				link.l1 = StringFromKey("EngLineNpc_2_20");
				link.l1.go = "Step_E6_30";
			}
			// ==> Муж Джилиан
			if (pchar.questTemp.State == "MorrisWillams_AfterFight" && npchar.id == "Jillians_Husband")   // базар в пещере с мужем, англ.линейка, квест №6
			{
				dialog.text = StringFromKey("EngLineNpc_2_21");
				link.l1 = StringFromKey("EngLineNpc_2_22");
				link.l1.go = "Step_E6_32";
			}
			// ==> Спасишийся перец в поселении буканьеров
			if (pchar.questTemp.State == "ToMansfield_GoOn")   // разговор со спасшимся перцем, анл.линейка, квест №8
			{
				dialog.text = StringFromKey("EngLineNpc_2_23");
				link.l1 = StringFromKey("EngLineNpc_2_24");
				link.l1.go = "Step_E8_1";
			}
			if (pchar.questTemp.State == "ToMansfield_CatchToPardal")   // остаточный разговор со спасшимся перцем
			{
				dialog.text = StringFromKey("EngLineNpc_2_25");
				link.l1 = StringFromKey("EngLineNpc_2_26");
				link.l1.go = "exit";
			}

		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//*************************************** Диалог боцмана Морриса Уильямса *********************************
		case "Step_E6_1":
			dialog.text = StringFromKey("EngLineNpc_2_27", pchar);
			link.l1 = StringFromKey("EngLineNpc_2_28");
			link.l1.go = "Step_E6_2";
		break;

		case "Step_E6_2":
			dialog.text = StringFromKey("EngLineNpc_2_29");
			link.l1 = StringFromKey("EngLineNpc_2_30");
			link.l1.go = "Step_E6_3";
		break;

		case "Step_E6_3":
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 40.0);
			LAi_SetPlayerType(pchar);
			sld = characterFromID("Morris_Willams");
			LAi_SetHuberTypeNoGroup(sld);
			FreeSitLocator("PortRoyal_tavern", "sit10");
			ChangeCharacterAddressGroup(sld, "PortRoyal_tavern", "sit", "sit10");
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true); //на всякий случай, чтобы геймер не слинял.
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
			LocatorReloadEnterDisable("PortRoyal_town", "boat", true);
			NextDiag.TempNode = "First time";
			DialogExit();
			AddLandQuestmark_Main(sld, "Eng_Line");
		break;

		case "Step_E6_4":
			dialog.text = StringFromKey("EngLineNpc_2_31");
			link.l1 = StringFromKey("EngLineNpc_2_32");
			link.l1.go = "Step_E6_5";
		break;

		case "Step_E6_5":
			dialog.text = StringFromKey("EngLineNpc_2_33");
			link.l1 = StringFromKey("EngLineNpc_2_34");
			link.l1.go = "Step_E6_6";
		break;

		case "Step_E6_6":
			chrDisableReloadToLocation = false;
			npchar.LifeDay = 1; // уберем нпс на след.день.
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			pchar.questTemp.State = "MorrisWillams_ArrestedToPrison";
			AddLandQuestmarkToFantoms_Main("JailOff", "Eng_Line", "PortRoyal_JailOff_QuestMarkCondition");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 40.0);
			AddQuestRecord("Eng_Line_6_MorrisWillams", "15");
			sld = characterFromID("Morris_Willams");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_prison", "goto", "goto9");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			LAi_SetPlayerType(pchar);
			DialogExit();
		break;

		//*********************************** Диалоги Джиллиан Эттербери *************************************
		case "Step_E6_25":
			dialog.text = StringFromKey("EngLineNpc_2_35", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("EngLineNpc_2_36");
			link.l1.go = "Step_E6_26";
		break;

		case "Step_E6_26":
			dialog.text = StringFromKey("EngLineNpc_2_37", UpperFirst(GetAddress_Form(NPChar)));
			link.l1 = StringFromKey("EngLineNpc_2_38");
			link.l1.go = "Step_E6_27";
		break;

		case "Step_E6_27":
			dialog.text = StringFromKey("EngLineNpc_2_39");
			link.l1 = StringFromKey("EngLineNpc_2_40");
			link.l1.go = "Step_E6_28";
		break;

		case "Step_E6_28":
			dialog.text = StringFromKey("EngLineNpc_2_41", UpperFirst(GetAddress_Form(NPChar)));
			link.l1 = StringFromKey("EngLineNpc_2_42");
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_SeekHusband";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "20");
			Pchar.quest.MorrisWillams_HusbandInCave.win_condition.l1 = "location";
			Pchar.quest.MorrisWillams_HusbandInCave.win_condition.l1.location = "Jamaica_Grot";
			Pchar.quest.MorrisWillams_HusbandInCave.win_condition = "MorrisWillams_HusbandInCave";
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
		break;

		//**************************** Диалоги бандита в пещере, поиски мужа Джиллиан ****************************
		case "Step_E6_30":
			dialog.text = StringFromKey("EngLineNpc_2_43", pchar);
			link.l1 = StringFromKey("EngLineNpc_2_44");
			link.l1.go = "Step_E6_31";
		break;

		case "Step_E6_31":
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "MorrisWillams_AftreFightingInCave");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//************************************** Диалоги мужа Джиллиан ***********************************
		case "Step_E6_32":
			dialog.text = StringFromKey("EngLineNpc_2_45");
			link.l1 = StringFromKey("EngLineNpc_2_46");
			link.l1.go = "Step_E6_33";
		break;

		case "Step_E6_33":
			dialog.text = StringFromKey("EngLineNpc_2_47");
			link.l1 = StringFromKey("EngLineNpc_2_48");
			link.l1.go = "Step_E6_34";
		break;

		case "Step_E6_34":
			dialog.text = StringFromKey("EngLineNpc_2_49", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("EngLineNpc_2_50");
			link.l1.go = "Step_E6_35";
		break;

		case "Step_E6_35":
			Characters[GetCharacterIndex("Gillian Atterbury")].TempQuest.SavedHusband = 1; // чтоб Джиллиан помнила об услуге...
			AddQuestRecord("Eng_Line_6_MorrisWillams", "21");
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			//ChangeCharacterReputation(pchar, 5); TODO eddy
			pchar.questTemp.State = "MorrisWillams_AfterFightGoRedmond";
			AddLandQuestmark_Main(characterFromID("PortRoyal_usurer"), "Eng_Line");
			DialogExit();
		break;

		//************************************** Диалоги спасшегося буканьера ***********************************
		case "Step_E8_1":
			dialog.text = StringFromKey("EngLineNpc_2_51");
			link.l1 = StringFromKey("EngLineNpc_2_52");
			link.l1.go = "Step_E8_2";
		break;

		case "Step_E8_2":
			dialog.text = StringFromKey("EngLineNpc_2_53");
			link.l1 = StringFromKey("EngLineNpc_2_54");
			link.l1.go = "Step_E8_3";
		break;

		case "Step_E8_3":
			dialog.text = StringFromKey("EngLineNpc_2_55");
			link.l1 = StringFromKey("EngLineNpc_2_56", pchar);
			link.l1.go = "Step_E8_4";
		break;

		case "Step_E8_4":
			dialog.text = StringFromKey("EngLineNpc_2_57");
			link.l1 = StringFromKey("EngLineNpc_2_58");
			link.l1.go = "Step_E8_5";
		break;

		case "Step_E8_5":
			dialog.text = StringFromKey("EngLineNpc_2_59");
			link.l1 = StringFromKey("EngLineNpc_2_60");
			link.l1.go = "Step_E8_6";
		break;

		case "Step_E8_6":
			dialog.text = StringFromKey("EngLineNpc_2_61");
			link.l1 = StringFromKey("EngLineNpc_2_62");
			link.l1.go = "Step_E8_7";
		break;

		case "Step_E8_7":
			dialog.text = StringFromKey("EngLineNpc_2_63");
			link.l1 = StringFromKey("EngLineNpc_2_64");
			link.l1.go = "exit";
			pchar.questTemp.State = "ToMansfield_CatchToPardal";
			AddQuestRecord("Eng_Line_8_ToMansfield", "2");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");

			Pchar.quest.ToMansfield_OutFromFort.win_condition.l1 = "location";
			Pchar.quest.ToMansfield_OutFromFort.win_condition.l1.location = "LaVega_town";
			Pchar.quest.ToMansfield_OutFromFort.win_condition = "ToMansfield_OutFromFort";
		break;

		case "You_baster":
			dialog.text = StringFromKey("EngLineNpc_2_65");
			link.l1 = StringFromKey("EngLineNpc_2_66");
			link.l1.go = "exit";
			NextDiag.TempNode = "You_baster";
			pchar.questTemp.jailCanMove = true;
		break;
	}
}
