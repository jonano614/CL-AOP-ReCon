
int CreateBermudesCharacters(int n)
{
	ref ch;
	
	///////////////////////////////////////////////////////////////////////////////
	// ОСНОВНЫЕ ПЕРСОНАЖИ
	///////////////////////////////////////////////////////////////////////////////

	makeref(ch,Characters[n]);			//Глава пиратов - Джейкоб Факмен aka Джекмен
	ch.id		= "Jackman";
	ch.name 	= FindPersonalName("Jackman_name");
	ch.lastname = FindPersonalName("Jackman_lastname");
	ch.rank = 30;
	ch.model	= "Jacob_Fackman";
	ch.sex = "man";
	ch.model.animation = "man";
	ch.City = "Pirates";
	ch.location	= "Pirates_townhall";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Mayor\Jackman.c";
	ch.nation = PIRATE;
	ch.quest.type = "hovernor";
	ch.reputation = "35";
    SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 70, 90);
    SetShipSkill(ch, 90, 80, 70, 10, 10, 20, 10, 10, 50);
	GiveItem2Character(ch, GUN_COMMON);
	ch.equip.gun = GUN_COMMON;
	GiveItem2Character(ch, BLADE_LONG);
	ch.equip.blade = BLADE_LONG;
	ch.Ship.Name = FindPersonalName("Jackman_ship");
	ch.Ship.Type = GenerateShipExt(SHIP_CORVETTE, true, ch);
	ch.Ship.Stopped = true;
   	ch.Ship.Cannons.Type = CANNON_TYPE_CULVERINE_LBS24;
    SetCrewQuantityFull(ch);
    Fantom_SetBalls(ch, "pirate");    
	ch.rank 	= 20;
	ch.reputation = "25";
	ch.money = "25000";
	ch.greeting = "Gr_HeadPirates";
	SetCharacterPerk(ch, "FastReload");
	SetCharacterPerk(ch, "HullDamageUp");
	SetCharacterPerk(ch, "SailsDamageUp");
	SetCharacterPerk(ch, "CrewDamageUp");
	SetCharacterPerk(ch, "CriticalShoot");
	SetCharacterPerk(ch, "LongRangeShoot");
	SetCharacterPerk(ch, "CannonProfessional");
	SetCharacterPerk(ch, "ShipDefenseProfessional");
	SetCharacterPerk(ch, "ShipSpeedUp");
	SetCharacterPerk(ch, "ShipTurnRateUp");
	SetCharacterPerk(ch, "SwordplayProfessional");
	SetCharacterPerk(ch, "AdvancedDefense");
	SetCharacterPerk(ch, "CriticalHit");
	SetCharacterPerk(ch, "Sliding");
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
    SetShipSkill(ch, 100, 10, 100, 100, 90, 60, 80, 90, 50);
	LAi_NoRebirthDisable(ch);
	LAi_RebirthOldName(ch);
	LAi_SetHuberType(ch);
    LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 200.0, 200.0);
	LAi_SetImmortal(ch, true);
	ch.watchBoxes = true;
	ch.standUp = true;
	n = n + 1;

	makeref(ch,Characters[n]);		// ОФициантка
	ch.id		= "Pirates_waitress";
	ch.model	= "women_1";
	ch.sex = "woman";
	ch.City = "Pirates";
	ch.location	= "Pirates_tavern";
	ch.location.group = "waitress";
	ch.location.locator = "barmen";
	ch.Dialog.Filename = "Common_Waitress.c";
	ch.greeting = "Gr_officiant";
	ch.nation = PIRATE;
	LAi_SetWaitressType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Трактирщик
	ch.id		= "Pirates_tavernkeeper";
	ch.model	= "barmen_20";
	ch.greeting = "Gr_Barmen";
	ch.name		= FindPersonalName("Pirates_tavernkeeper_name");
	ch.lastname = FindPersonalName("Pirates_tavernkeeper_lastname");
	ch.sex = "man";
	ch.City = "Pirates";
	ch.location	= "Pirates_Tavern";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Tavern.c";
	ch.TavernMan = true;
	ch.nation = PIRATE;
	LAi_SetBarmanType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Торговец Паскаль
	ch.id		= "Pirates_trader";
	ch.name		= FindPersonalName("Pirates_trader_name");
	ch.lastname = FindPersonalName("Pirates_trader_lastname");
	ch.model	= "Pasquale";
	ch.greeting = "tra_common";
	ch.sex = "man";
	ch.City = "Pirates";
	ch.location	= "Pirates_Store";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Store.c";
	ch.quest.type = "trader";
	ch.nation = PIRATE;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	// настройка магазина -->
	ch.Storage 	  = true; // можем завести склад
	ch.StoreNum   = Pirates_STORE;
	ch.from_sea   = "Pirates_town";
	// настройка магазина <--
	ch.Merchant = true;
    ch.money = makeint(STORE_TRADER_MIN_MONEY + frand(1.0)*STORE_TRADER_RAND_MONEY);
	n = n + 1;

	makeref(ch,Characters[n]);			//Мастер Алексус
	ch.id		= "Pirates_shipyarder";
	ch.model	= "Alexus_Reseacher";
	ch.model.animation = "man_B";
	ch.greeting = "Gr_shipyarderA";
	ch.name 	= FindPersonalName("Pirates_shipyarder_name");
    ch.lastname = FindPersonalName("Pirates_shipyarder_lastname");
	ch.sex = "man";
	ch.City = "Pirates";
	ch.location	= "Pirates_Shipyard";
	ch.location.group = "goto";
	ch.location.locator = "goto3";
	ch.Dialog.Filename = "Common_Shipyard.c";
	ch.nation = PIRATE;
	ch.quest.shiping = "0";
	//LAi_SetHuberType(ch);
	LAi_SetCitizenTypeNoGroup(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	return n;
}
