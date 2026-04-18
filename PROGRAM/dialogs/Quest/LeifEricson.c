// Квестовые атакующий кэпа, 10 штук в комплекте.
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sModelTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			if (pchar.questTemp.Ascold == "Ascold_MummyIsLive")
			{
				dialog.text = StringFromKey("LeifEricson_1", pchar);
				link.l1 = StringFromKey("LeifEricson_2", environment.date.year);
				link.l1.go = "Step_8";
			}
			if (pchar.questTemp.Ascold == "Ascold_BodyChange")
			{
				dialog.text = StringFromKey("LeifEricson_3", pchar);
				link.l1 = StringFromKey("LeifEricson_4");
				link.l1.go = "Step_25";
			}
			if (pchar.questTemp.Ascold == "Ascold_SkelSlave")
			{
				dialog.text = StringFromKey("LeifEricson_5", pchar);
				link.l1 = StringFromKey("LeifEricson_6");
				link.l1.go = "Step_27";
			}
			if (pchar.questTemp.Ascold == "Ascold_ImMummy")
			{
				dialog.text = StringFromKey("LeifEricson_7");
				link.l1 = StringFromKey("LeifEricson_8");
				link.l1.go = "exit";
			}
			if (pchar.questTemp.Ascold == "Ascold_MummyFoundItems")
			{
				dialog.text = StringFromKey("LeifEricson_9");
				if (CheckCharacterItem(pchar, "sculMa1") && CheckCharacterItem(pchar, "sculMa2") && CheckCharacterItem(pchar, "sculMa3") && CheckCharacterItem(pchar, "indian22"))
				{
					link.l1 = StringFromKey("LeifEricson_10");
					link.l1.go = "Step_29";
				}
				else
				{
					link.l1 = StringFromKey("LeifEricson_11", pchar);
					link.l1.go = "Step_30";
				}
			}
			if (pchar.questTemp.Ascold == "Ascold_BackMyBody")
			{
				dialog.text = StringFromKey("LeifEricson_12");
				link.l1 = StringFromKey("LeifEricson_13");
				link.l1.go = "Step_31";
			}
			if (pchar.questTemp.Ascold == "Ascold_ReturnToAscold")
			{
				dialog.text = StringFromKey("LeifEricson_14");
				link.l1 = StringFromKey("LeifEricson_15");
				link.l1.go = "exit";
			}
			if (pchar.questTemp.Ascold == "Ascold_SaveWorld")
			{
				dialog.text = StringFromKey("LeifEricson_16", pchar);
				link.l1 = StringFromKey("LeifEricson_17", pchar);
				link.l1.go = "Step_32";
			}
		break;

		case "Exit":
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Step_8":
			dialog.text = StringFromKey("LeifEricson_18");
			link.l1 = StringFromKey("LeifEricson_19", pchar);
			link.l1.go = "Step_9";
		break;

		case "Step_9":
			dialog.text = StringFromKey("LeifEricson_20");
			link.l1 = StringFromKey("LeifEricson_21", GetFullName(pchar));
			link.l1.go = "Step_10";
			link.l2 = StringFromKey("LeifEricson_22");
			link.l2.go = "ToDeath";
		break;

		case "ToDeath":
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_Cave")], false);
			LAi_SetFightMode(pchar, true);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Step_10":
			dialog.text = StringFromKey("LeifEricson_23");
			link.l1 = StringFromKey("LeifEricson_24");
			link.l1.go = "Step_11";
		break;

		case "Step_11":
			dialog.text = StringFromKey("LeifEricson_25");
			link.l1 = StringFromKey("LeifEricson_26", pchar);
			link.l1.go = "Step_12";
		break;

		case "Step_12":
			dialog.text = StringFromKey("LeifEricson_27", pchar);
			link.l1 = StringFromKey("LeifEricson_28");
			link.l1.go = "Step_13";
		break;

		case "Step_13":
			dialog.text = StringFromKey("LeifEricson_29");
			link.l1 = StringFromKey("LeifEricson_30");
			link.l1.go = "Step_14";
		break;

		case "Step_14":
			dialog.text = StringFromKey("LeifEricson_31");
			link.l1 = StringFromKey("LeifEricson_32", pchar);
			link.l1.go = "Step_15";
		break;

		case "Step_15":
			dialog.text = StringFromKey("LeifEricson_33");
			link.l1 = StringFromKey("LeifEricson_34");
			link.l1.go = "Step_16";
		break;

		case "Step_16":
			dialog.text = StringFromKey("LeifEricson_35", pchar);
			link.l1 = StringFromKey("LeifEricson_36");
			link.l1.go = "Step_17";
		break;

		case "Step_17":
			dialog.text = StringFromKey("LeifEricson_37", pchar);
			link.l1 = StringFromKey("LeifEricson_38");
			link.l1.go = "Step_18";
		break;

		case "Step_18":
			dialog.text = StringFromKey("LeifEricson_39");
			link.l1 = StringFromKey("LeifEricson_40");
			link.l1.go = "Step_19";
		break;

		case "Step_19":
			dialog.text = StringFromKey("LeifEricson_41");
			link.l1 = StringFromKey("LeifEricson_42", pchar);
			link.l1.go = "Step_20";
		break;

		case "Step_20":
			dialog.text = StringFromKey("LeifEricson_43");
			link.l1 = StringFromKey("LeifEricson_44");
			link.l1.go = "Step_21";
		break;

		case "Step_21":
			dialog.text = StringFromKey("LeifEricson_45");
			link.l1 = StringFromKey("LeifEricson_46", pchar);
			link.l1.go = "Step_22";
		break;

		case "Step_22":
			dialog.text = StringFromKey("LeifEricson_47");
			link.l1 = StringFromKey("LeifEricson_48", pchar);
			link.l1.go = "Step_23";
			link.l2 = StringFromKey("LeifEricson_49");
			link.l2.go = "ToDeath";
		break;

		case "Step_23":
			dialog.text = StringFromKey("LeifEricson_50", pchar);
			link.l1 = StringFromKey("LeifEricson_51");
			link.l1.go = "Step_24";
		break;

		case "Step_24":
			dialog.text = StringFromKey("LeifEricson_52", pchar);
			link.l1 = StringFromKey("LeifEricson_53");
			link.l1.go = "Body_Change";
		break;

		case "Body_Change":
			bDisableCharacterMenu = true; //закрываем Ф2
			// ==> меняем модели
			Pchar.questTemp.Ascold.heroFaceId = pchar.FaceId;
			Pchar.questTemp.Ascold.heroAnimation = pchar.model.animation;
			Pchar.questTemp.Ascold.reputation = pchar.reputation;
			Pchar.questTemp.Ascold.nation = pchar.nation;
			Pchar.questTemp.Ascold.relation = GetNationRelation2MainCharacter(FRANCE);

			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
			sModelTemp = npchar.model;
			npchar.model = pchar.model;
			npchar.model.animation = pchar.model.animation;
			FaceMaker(npchar);
			// Если ГГ одноногий, смена тела снимет этот эффект
			if (CheckCharacterPerk(pchar, "OneLegMan"))
			{
				DeleteTrait(pchar, "OneLegMan");
				SetCharacterPerk(npchar, "OneLegMan");
			}
			SetNewModelToChar(npchar);
			pchar.model = sModelTemp;
			pchar.model.animation = "man";
			FaceMaker(pchar);
			SetNewModelToChar(pchar);
			// LAi_SetPlayerType(pchar); // вернем контроль над ГГ позднее
			pchar.questTemp.Ascold = "Ascold_BodyChange";
			// LAi_SetCitizenType(npchar);

			//==> убираем офицеров
			StoreOfficers_Ascold(pchar);  // запомним офицеров во временном хранилище			
			for (i = 1; i <= 3; i++)
			{
				string officers = "Fellows.Passengers.Officers." + "id" + i;
				if (CheckAttribute(pchar, officers))
				{
					RemoveOfficersIndex(pchar, sti(pchar.(officers)));
				}
			}
			//<== убираем офицеров
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DoQuestFunctionDelay("Ascold_Leif_AfterBodyChange", 3.0); // Продолжим диалог через 3сек
			DialogExit();
		break;

		case "Step_25":
			dialog.text = StringFromKey("LeifEricson_54");
			link.l1 = StringFromKey("LeifEricson_55");
			link.l1.go = "Step_26";
		break;

		case "Step_26":
			dialog.text = StringFromKey("LeifEricson_56");
			link.l1 = "...";
			link.l1.go = "Leif_GiveMeCrew";
		break;

		case "Leif_GiveMeCrew":
			for (i = 1; i <= 13; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MySkel" + i, "Draugr_" + (rand(7) + 1), "skeleton", "man", 30, PIRATE, 0, true));
				sld.Ghost = 0.6;
				FantomMakeCoolFighter(sld, 20, 70, 70, GetRandSubString("vikingAxe,vikingSword"), "", 50);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto" + (rand(2) + 1));
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			pchar.questTemp.Ascold = "Ascold_SkelSlave";

			DoQuestFunctionDelay("Ascold_Leif_AfterBodyChange", 3.0); // Продолжим диалог через 3сек
			DialogExit();
		break;

		case "Step_27":
			dialog.text = StringFromKey("LeifEricson_57");
			link.l1 = StringFromKey("LeifEricson_58");
			link.l1.go = "Step_28";
		break;

		case "Step_28":
			PChar.CrewType.Draugr = true; //команда - драугры
			chrDisableReloadToLocation = false; // открыть выход из локации.
			pchar.questTemp.Ascold = "Ascold_ImMummy";
			//==> потом вернуть
			Pchar.location.from_sea.save = Pchar.location.from_sea;
			Pchar.location.from_sea = "none";
			Pchar.Ship.Crew.Quantity.save = Pchar.Ship.Crew.Quantity;
			Pchar.Ship.Crew.Quantity = 1000;
			Pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			Pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			RemoveCharacterEquip(pchar, PATENT_ITEM_TYPE); //Снимаем патент
			ChangeCharacterAddress(characterFromID("Ascold"), "None", ""); //Прячем Аскольда
			Locations[FindLocation("BasTer_houseSp1")].reload.l2.disable = true;
			//<== потом вернуть
			Pchar.quest.Ascold_MummyFightTown.win_condition.l1 = "location";
			Pchar.quest.Ascold_MummyFightTown.win_condition.l1.location = "BasTer_ExitTown";
			Pchar.quest.Ascold_MummyFightTown.win_condition = "Ascold_MummyFightTown";
			// Ставим туманы
			Ascold_LeifGiveMeFog_Prepare("");

			Pchar.quest.Ascold_LeifGiveMeFog.win_condition.l1 = "location";
			Pchar.quest.Ascold_LeifGiveMeFog.win_condition.l1.location = "Guadeloupe_CaveEntrance";
			Pchar.quest.Ascold_LeifGiveMeFog.function = "Ascold_LeifGiveMeFog";

			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetPlayerType(pchar); // возвращаем контроль над ГГ
			LAi_SetCitizenType(npchar);
			DialogExit();
		break;

		case "Step_29":
		// DeleteAttribute(PChar, "CrewType.Skel"); // команда в нормальное состояние
			DeleteAttribute(PChar, "CrewType"); // Fix > Удаляется только sub-атрибут .Skel
			bDisableCharacterMenu = false; //открываем Ф2
			DeleteAttribute(PChar, "questTemp.Ascold.tmp_disable");
			TakeItemFromCharacter(pchar, "sculMa1");
			TakeItemFromCharacter(pchar, "sculMa2");
			TakeItemFromCharacter(pchar, "sculMa3");
			TakeItemFromCharacter(pchar, "indian22");
			//==> вертаем
			Pchar.location.from_sea = Pchar.location.from_sea.save;
			DeleteAttribute(PChar, "location.from_sea.save");
			Pchar.Ship.Crew.Quantity = Pchar.Ship.Crew.Quantity.save;
			DeleteAttribute(PChar, "Ship.Crew.Quantity.save");

			//Rosarak. Разговор с абордажником
			if (CheckAttribute(pchar, "Fellows.Old.Officers.first_idx"))
			{
				Pchar.quest.Ascold_ExitCave.win_condition.l1 = "location";
				Pchar.quest.Ascold_ExitCave.win_condition.l1.location = "Guadeloupe_CaveEntrance";
				Pchar.quest.Ascold_ExitCave.win_condition = "Ascold_ExitCave";
			}
			RestoreOfficers_Ascold(pchar);
			//Rosarak. А кто мир спасать будет?
			LocatorReloadEnterDisable("Shore28", "boat", true);
			LocatorReloadEnterDisable("Shore29", "boat", true);
			LocatorReloadEnterDisable("Mayak4", "boat", true);
			LocatorReloadEnterDisable("Baster_town", "reload1_back", true);

			DeleteAttribute(&Locations[FindLocation("BasTer_houseSp1")], "reload.l2.disable"); // Возвращаем Аскольда
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Ascold")], "BasTer_houseSp1", "goto", "goto1");
			LAi_SetStayTypeNoGroup(characterFromID("Ascold"));
			SetLocationCapturedState("BasTer_town", false);
			// ==> возвращаем модели
			sModelTemp = pchar.model;
			pchar.model = npchar.model;
			pchar.model.animation = Pchar.questTemp.Ascold.heroAnimation;
			pchar.FaceId = Pchar.questTemp.Ascold.heroFaceId;
			pchar.reputation = Pchar.questTemp.Ascold.reputation;
			pchar.nation = Pchar.questTemp.Ascold.nation;
			SetNationRelation2MainCharacter(FRANCE, sti(Pchar.questTemp.Ascold.relation));
			FaceMaker(pchar);
			// Возвращаем одноногость
			if (CheckCharacterPerk(npchar, "OneLegMan"))
			{
				DeleteTrait(npchar, "OneLegMan");
				SetCharacterPerk(pchar, "OneLegMan");
			}
			SetNewModelToChar(pchar);
			LAi_SetActorType(pchar); // Заберем контроль для переходки
			npchar.model = sModelTemp;
			npchar.model.animation = "man";
			FaceMaker(npchar);
			SetNewModelToChar(npchar);

			DeleteAttribute(PChar, "questTemp.Ascold.heroFaceId");
			DeleteAttribute(PChar, "questTemp.Ascold.heroAnimation");
			DeleteAttribute(PChar, "questTemp.Ascold.reputation");
			DeleteAttribute(PChar, "questTemp.Ascold.relation");
			DeleteAttribute(PChar, "GenQuest.HunterScore2Pause"); //вертаем начисление нзг
			DeleteAttribute(PChar, "GenQuest.ReputationNotChange"); //вертаем смену репы
			if (CheckAttribute(pchar, "PatentNation"))
			{
				EquipCharacterbyItem(pchar, "patent_" + pchar.PatentNation); //вертаем патент
			}
			chrDisableReloadToLocation = true; // закрыть выход из локации.
			pchar.questTemp.Ascold = "Ascold_BackMyBody";
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;

			Ascold_LeifTakeAwayFog("");
			DoQuestFunctionDelay("Ascold_Leif_AfterBodyChange", 2.0); // Продолжим диалог через 2 сек
			DialogExit();
		break;

		case "Step_30":
			dialog.text = StringFromKey("LeifEricson_59");
			link.l1 = StringFromKey("LeifEricson_60");
			link.l1.go = "exit";
		break;

		case "Step_31":
			dialog.text = StringFromKey("LeifEricson_61");
			link.l1 = StringFromKey("LeifEricson_62", pchar);
			link.l1.go = "Step_31_exit";
			chrDisableReloadToLocation = false; // открыть выход из локации.
			bDisableFastReload = false;

			pchar.questTemp.Ascold = "Ascold_ReturnToAscold";
			characters[GetCharacterIndex("Ascold")].dialog.currentnode = "AfterAttackMummy";
			RemoveLandQuestmark_Main(npchar, "Ascold");
			AddLandQuestmark_Main(CharacterFromID("Ascold"), "Ascold");
		break;

		case "Step_31_exit":
			LAi_SetCitizenType(npchar);
			LAi_SetPlayerType(pchar);

			DialogExit();
		break;

		case "Step_32":
			dialog.text = StringFromKey("LeifEricson_63");
			link.l1 = "...";
			link.l1.go = "Step_33";
		break;

		case "Step_33":
			DialogExit();

			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_MONSTERS);
			LAi_group_FightGroups(PLAYER_GROUP, LAI_GROUP_MONSTERS, false);
			pchar.quest.RepairMonsterGroup.win_condition.l1	= "ExitFromLocation";
			pchar.quest.RepairMonsterGroup.win_condition.l1.location = pchar.location;
			pchar.quest.RepairMonsterGroup.function	= "RepairMonsterGroup";

			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);

			RemoveLandQuestmark_Main(npchar, "Ascold");
		break;
	}
}


