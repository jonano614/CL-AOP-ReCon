// SLiB Новый файл для ВМЛ, все от К3 потерто

int ChangeContrabandRelation(ref pchar, int _val)
{
   pchar.questTemp.Contraband.relation = makeint(pchar.questTemp.Contraband.relation) + _val;
   if (makeint(pchar.questTemp.Contraband.relation) > 100) pchar.questTemp.Contraband.relation = 100;
   if (makeint(pchar.questTemp.Contraband.relation) < 0) pchar.questTemp.Contraband.relation = 0;

   	if (_val>0)
   	{
   		notification(StringFromKey("InfoMessages_223")+" ("+FloatToString(stf(pchar.questTemp.Contraband.relation),1)+")", "Smugglers");
   	}
   	if (_val<0)
   	{
   		notification(StringFromKey("InfoMessages_224")+" ("+FloatToString(stf(pchar.questTemp.Contraband.relation),1)+")", "Smugglers");
   	}

   return makeint(pchar.questTemp.Contraband.relation);
}

int GetPlayerContrabandRelation()
{
    return ChangeContrabandRelation(pchar, 0);
}

// Работа с контрабандой
bool HaveContrabandGoods(ref _refCharacter)
{
	int i;
	int curStoreIdx = GetCharacterCurrentStore(_refCharacter);
	if (curStoreIdx == -1) return false;

	_refCharacter.FindContrabandGoods.StoreIdx = curStoreIdx;
	
	for(i=0; i<GOODS_QUANTITY; i++)
	{
		if(GetStoreGoodsType(&Stores[curStoreIdx],i) == TRADE_TYPE_CONTRABAND_NAME)
		{
			if(GetSquadronGoods(_refCharacter,i) > 0)
			{
				_refCharacter.FindContrabandGoods.GoodsIdx = i;
				return true;
			}
		}
	}
	
	DeleteAttribute(_refCharacter,"FindContrabandGoods");
	return false;
}

int GetCharacterCurrentStore(ref _refCharacter)
{
	bool bOk = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true); // в сделке, значит магазин уже ясен
	if (bOk && CheckAttribute(Pchar, "GenQuest.Contraband.StoreIdx"))
	{
		return sti(Pchar.GenQuest.Contraband.StoreIdx);
	}
	
	int i, idx;
	int curLocNum = FindLocation(_refCharacter.location);
	if(curLocNum<0) return -1;

    idx = -1;
	if (CheckAttribute(&Locations[curLocNum], "fastreload")) // в таверне должно быть всегда
	{
		string locGroupId = Locations[curLocNum].fastreload;
		for (i=0; i<STORE_QUANTITY; i++)
		{
			if (Stores[i].group == locGroupId)
			{
				idx = i;
				break;
			}
		}
	}

    Pchar.GenQuest.Contraband.StoreIdx = idx; // запомним, для бухты, когда в сделку пойдём
	return  idx;
}

// выбор куда идти
string SelectSmugglingLocation()
{
    ref CurIsland;
	int n;
	string TargetLocation;
	
	n = GetCharacterCurrentIsland(Pchar);
	if (n < 0) 
	{
		TargetLocation = "None";
	}
	else
	{
		CurIsland = GetIslandByIndex(n);
		TargetLocation = GetIslandRandomFreeShoreId(CurIsland.id);
    }
    if (TargetLocation == "") TargetLocation = "None";
    Pchar.Quest.SelectedSmugglingLocation = TargetLocation;
    return TargetLocation;
}

////////////////////////////////////////////////////////////////////////////////
//                Контрабандисты НАЧАЛО
////////////////////////////////////////////////////////////////////////////////
void PlaceSmugglersOnShore(string LocationId)
{
	ref Smuggler, player;
	int RandCounter;
	int i;
	
	player = GetMainCharacter();

	string Model;
	
	player.GenQuest.Smugglers_Group = "Smugglers_1";
    LAi_group_Register(player.GenQuest.Smugglers_Group);
    arrayNPCModelHow = 0;
	for (i = 1; i <= 3; i++)
    {
        Model = "citiz_" + (rand(9)+21);
		Smuggler = GetCharacter(NPC_GenerateCharacter("Rand_Smug0" + i, Model, "man", "man", 5, PIRATE, 4, true)); // 4 дня, потом сами пропадут
		SetNPCModelUniq(Smuggler, "smuggler", MAN);
		SetFantomParam(Smuggler);
		LAi_SetWarriorTypeNoGroup(Smuggler);
		LAi_warrior_DialogEnable(Smuggler, true);
		LAi_warrior_SetStay(Smuggler, true);
		Smuggler.Dialog.Filename = "Smuggler_OnShore_dialog.c";
		Smuggler.Dialog.CurrentNode = "First time";
		Smuggler.greeting = "Gr_Smuggler_OnShore";
		LAi_group_MoveCharacter(Smuggler, player.GenQuest.Smugglers_Group);
		ChangeCharacterAddressGroup(Smuggler, LocationID, "Smugglers", "Smuggler0" + i);
    }
	
	AddGeometryToLocation(LocationID, "smg");
	
	LAi_group_SetRelation(LAI_GROUP_PLAYER, player.GenQuest.Smugglers_Group, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation(player.GenQuest.Smugglers_Group, "CoastalGuards", LAI_GROUP_NEITRAL); // патруль на берегу

	SetTimerCondition("Rand_Smuggling", 0, 0, 4, false);  // через 4 дня всех убрать
	// задание на завал контры
	if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GetArealByLocation(&locations[FindLocation(pchar.location)]))
	{
		pchar.quest.KillSmugglers.win_condition.l1 = "NPC_Death";
		pchar.quest.KillSmugglers.win_condition.l1.character = "Rand_Smug01";
		pchar.quest.KillSmugglers.win_condition.l2 = "NPC_Death";
		pchar.quest.KillSmugglers.win_condition.l2.character = "Rand_Smug02";
		pchar.quest.KillSmugglers.win_condition.l3 = "NPC_Death";
		pchar.quest.KillSmugglers.win_condition.l3.character = "Rand_Smug03";
		pchar.quest.KillSmugglers.win_condition = "KillSmugglers_after";
	}
}


void RemoveSmugglersFromShore()
{
	ref Smuggler;
	int RandCounter, i, cn;
	string sLoc;

	DeleteAttribute(pchar, "quest.Contraband.Active");
	CloseQuestHeader("Gen_Contraband");

	if (CheckAttribute(pchar, "Quest.SelectedSmugglingLocation"))
	{
		sLoc = pchar.Quest.SelectedSmugglingLocation;
	}
//navy --> PGG
	else
	{
		if (CheckAttribute(pchar, "questTemp.PGGContra"))
		{
			sLoc = pchar.questTemp.PGGContra.Loc;
			Smuggler = &Characters[sti(pchar.questTemp.PGGContra)];
			ChangeCharacterAddressGroup(Smuggler, "None", "", "");
			Smuggler.location.from_sea = "";
			Smuggler.PGGAi.location.town = Smuggler.PGGAi.location.town.back;
			DeleteAttribute(pchar, "questTemp.PGGContra");
			DeleteAttribute(Smuggler, "PGGAi.location.town.back");
			CloseQuestHeader("Gen_StrangeInfo");
			//LAi_group_Delete("PGGTmp");
			pchar.Quest.PGG_WithSmugglers_Dead.Over = "yes";
			CloseQuestHeader("Gen_StrangeInfo");
		}
	}
//navy <--
	RemoveGeometryFromLocation(sLoc, "smg");

	pchar.quest.KillSmugglers_outShore.win_condition.l1 = "ExitFromLocation";
	pchar.quest.KillSmugglers_outShore.win_condition.l1.location = pchar.location;
	pchar.quest.KillSmugglers_outShore.win_condition = "KillSmugglers_outShore";
	for (i=1; i<=3; i++) //eddy
	{
		cn = GetCharacterIndex("Rand_Smug0"+i);
		if (cn != -1)
		{
			characters[cn].lifeDay = 0;
		}
	}
	LAi_group_SetRelation(LAI_GROUP_PLAYER, "CoastalGuards", LAI_GROUP_NEITRAL);
}

void SetCoastalGuardPursuit()
{
	ref Smuggler;
	int i;
	int iNation = sti(pchar.GenQuest.Contraband.GuardNation);// Нация патруля
	string Model;
	
	for (i = 1; i <= 3; i++)
    {
        Model = "off_" + NationShortName(iNation) + "_" + (rand(1) + 1);
		Smuggler = GetCharacter(NPC_GenerateCharacter("Coastal_Captain0" + i, Model, "man", "man", 5, iNation, 3, true)); // 3 дня, потом сами пропадут
		SetFantomParam(Smuggler);
		SelectCoastalGuardShip(Smuggler);
		// 1.2.3 хардкор! Smuggler.Coastal_Captain = true; // если по нему палить, НЗГ не будет
		Smuggler.AlwaysEnemy = true;
		Smuggler.DontRansackCaptain = true;
		Smuggler.AlwaysSandbankManeuver = true;
		Group_addCharacter("Coastal_Guards", Smuggler.id);
		SetCharacterRelationBoth(sti(Smuggler.index), GetMainCharacterIndex(), RELATION_ENEMY);
		if (makeint(Pchar.rank) < 6 && i == 1 && GetCompanionQuantity(Pchar) == 1) break;
		if (makeint(Pchar.rank) < 9 && i == 2 && GetCompanionQuantity(Pchar) < 3) break;
    }
	Group_SetGroupCommander("Coastal_Guards", "Coastal_Captain01");

	Group_SetPursuitGroup("Coastal_Guards", PLAYER_GROUP);
	Group_SetAddress("Coastal_Guards", Islands[GetCharacterCurrentIsland(Pchar)].id, "", "");
	Group_SetTaskAttack("Coastal_Guards", PLAYER_GROUP);
	Group_LockTask("Coastal_Guards");
}

void StopCoastalGuardPursuit()
{
	ref rCap;
	int i, cn;
	
	for (i = 1; i <= 3; i++)
	{
		cn = GetCharacterIndex("Coastal_Captain0" + i);
		if (cn != -1)
		{
			rCap = GetCharacter(cn);
			if (rCap.location == Pchar.location && bSeaActive) return; // если в море погоня, то не трем, только на выход на карту.
			ChangeCharacterAddressGroup(rCap, "None", "", "");
			setCharacterShipLocation(rCap, "None");
		}
	}
	group_DeleteGroup("Coastal_Guards");
}

void SelectCoastalGuardShip(ref rCharacter)
{
	SetShipHunter(rCharacter);
}

bool CanSquadronContraband()
{
	if (bBettaTestMode) return true;

	if (GetCompanionQuantity(pchar) > 1 && !CheckCharacterPerk(pchar, "Schemer"))
	{
		return false;
	}

	return true;
}

bool CanShipclassContraband()
{
	if (bBettaTestMode) return true;

	int iClass = 7;
	int iTemp;
	for (int i = 0; i < COMPANION_MAX; i++) //HardCoffee ref
	{
		iTemp = GetCompanionIndex(pchar, i);
		if (iTemp < 0) continue;
		iTemp = GetCharacterShipClass(&characters[iTemp]);
		if (iTemp < iClass) iClass = iTemp;
	}

	if (iClass < 4 - makeint(CheckCharacterPerk(pchar, "Schemer")))
	{
	    	return false;
	}

	return true;
}
