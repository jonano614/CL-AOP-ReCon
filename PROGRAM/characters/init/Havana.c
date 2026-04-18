
int CreateHavanaCharacters(int n)
{
	ref ch;
	
	///////////////////////////////////////////////////////////////////////////////
	// ОСНОВНЫЕ ПЕРСОНАЖИ
	///////////////////////////////////////////////////////////////////////////////

	makeref(ch,Characters[n]);			//Губернатор
	ch.id		= "Havana_Mayor";
	ch.model	= "huber_18";
	ch.sex = "man";
	ch.City = "Havana";
	ch.location	= "Havana_townhall";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Mayor.c";
	ch.greeting = "spa_gov_common";
	ch.nation = SPAIN;
	ch.quest.type = "hovernor";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, BLADE_LONG);
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.watchBoxes = true;
	ch.standUp = true; //вставать и нападать на врага
	LAi_SetHuberType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Священик
	ch.id		= "Havana_Priest";
	ch.model	= "priest_1";
	ch.model.animation = "man_kvl2";
	ch.sex = "man";
	ch.City = "Havana";
	ch.location	= "Havana_church";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Church.c";
	ch.greeting = "Gr_Church";
	ch.nation = SPAIN;
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetPriestType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);		// ОФициантка
	ch.id		= "Havana_waitress";
	ch.model	= "women_7";
	ch.sex = "woman";
	ch.City = "Havana";
	ch.location	= "Havana_tavern";
	ch.location.group = "waitress";
	ch.location.locator = "barmen";
	ch.Dialog.Filename = "Common_Waitress.c";
	ch.greeting = "Gr_officiant";
	ch.nation = SPAIN;
	LAi_SetWaitressType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Трактирщик
	ch.id		= "Havana_tavernkeeper";
	ch.model	= "barmen_15";
	ch.greeting = "Gr_Barmen";
	ch.sex = "man";
	ch.City = "Havana";
	ch.location	= "Havana_Tavern";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Tavern.c";
	ch.TavernMan = true;
	ch.nation = SPAIN;
	LAi_SetBarmanType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;


	makeref(ch,Characters[n]);			//Торговец
	ch.id		= "Havana_trader";
	ch.model	= "trader_9";
	ch.greeting = "tra_common";
	ch.sex = "man";
	ch.City = "Havana";
	ch.location	= "Havana_Store";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Store.c";
	ch.quest.type = "trader";
	ch.nation = SPAIN;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	ch.Merchant = true;
    ch.money = makeint(STORE_TRADER_MIN_MONEY + frand(1.0)*STORE_TRADER_RAND_MONEY);
	n = n + 1;

	makeref(ch,Characters[n]);			//Корабел
	ch.id		= "Havana_shipyarder";
	ch.model	= "shipowner_9";
	ch.greeting = "Gr_shipyarder";
	ch.sex = "man";
	ch.City = "Havana";
	ch.location	= "Havana_Shipyard";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Shipyard.c";
	ch.nation = SPAIN;
	ch.quest.shiping = "0";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, "topor1");
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.watchBoxes = true;
	ch.standUp = true; //вставать и нападать на врага
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Банкир
	ch.id		= "Havana_usurer";
	ch.model	= "usurer_13";
	ch.sex = "man";
	ch.City = "Havana";
	ch.location	= "Havana_Bank";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Usurer.c";
	ch.nation = SPAIN;
	ch.greeting = "Gr_bankeer";
	ch.quest.shiping = "0";
	ch.UsurerDeposit = 10000; // *1000 денег
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
    ch.Merchant = true;
    ch.money = makeint(BANK_TRADER_MIN_MONEY + frand(1.0)*BANK_TRADER_RAND_MONEY);
	n = n + 1;

	makeref(ch,Characters[n]);			//Начальник порта
	ch.id		= "Havana_PortMan";
	ch.model	= "portman_12";
	ch.sex = "man";
	ch.City = "Havana";
	ch.location	= "Havana_PortOffice";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Portman.c";
	ch.nation = SPAIN;
	ch.greeting = "portmans";
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;

    makeref(ch,Characters[n]);
	ch.name 	= UpperFirst(XI_ConvertString("WhoSmuggler"));
	ch.lastname = "";
	ch.id		= "Havana_Smuggler";
	ch.model    = "citiz_25";
	ch.sex      = "man";
	LAi_SetLoginTime(ch, 0.0, 24.0);
	ch.nation = PIRATE;
	GiveItem2Character(ch, BLADE_SABER);
	ch.equip.blade = BLADE_SABER;
	// посадим в генераторе
	ch.Dialog.Filename = "Smuggler_Agent_dialog.c";
	LAi_SetSitType(ch);
	LAi_SetHP(ch, 80.0, 80.0);
	ch.greeting = "Gr_Smuggler Agent";
	n = n + 1;
	
	makeref(ch,Characters[n]);			//Смотритель маяка
	ch.id		= "Havana_Lightman";
	ch.model	= "keeper_2";
	ch.model.animation = "man_B";
	ch.sex = "man";
	ch.City = "Havana";
	ch.location = "Mayak10_Lighthouseroom";
	ch.location.group = "barmen";
	ch.location.locator = "bar2";
	ch.Dialog.Filename = "Common_Lighthouse.c";
	ch.greeting = "lighthouseman_3";
	ch.Merchant = true;
    // ch.Merchant.type = "lightman";
    ch.money = makeint(LIGHT_TRADER_MIN_MONEY + frand(1.0)*LIGHT_TRADER_RAND_MONEY);
	ch.nation = SPAIN;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;
	
	makeref(ch,Characters[n]);			//Смотритель кладбища
	ch.id		= "Havana_Cemeteryman";
	ch.model	= "keeper_2";
	ch.model.animation = "man_B";
	ch.sex = "man";
	ch.City = "Havana";
	ch.location = "Havana_KeepersHouse";
	ch.location.group = "goto";
	ch.location.locator = "goto5";
	ch.Dialog.Filename = "Common_Cemeteryman.c";
	ch.greeting = "lighthouseman_3";
	ch.Merchant = true;
	// ch.Merchant.type = "cemeteryman";
	ch.money = makeint(LIGHT_TRADER_MIN_MONEY + frand(1.0)*LIGHT_TRADER_RAND_MONEY);
	ch.nation = SPAIN;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Заведущий пакгауза
	ch.id		= "Havana_GlavSklad";
	ch.model	= "citiz_18";
	ch.sex = "man";
	ch.City = "Havana";
	ch.location	= "Havana_PackhouseOffice";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "House_dialog.c";
	ch.dialog.currentnode = "GlavSklad";
	ch.nation = SPAIN;
	ch.greeting = "official";
    ch.nonTable = true;
    ch.standUp = true;
    ch.watchBoxes = true;
	LAi_SetSitType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.Storage = true;
	ch.item_date = "";
	n = n + 1;

	makeref(ch,Characters[n]);			//Заведающий хранилища
	ch.id		= "Havana_bankvault";
	ch.model	= "citiz_12";
	ch.sex = "man";
	ch.City = "Havana";
	ch.location	= "Havana_bankvault";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "House_dialog.c";
	ch.dialog.currentnode = "GlavBankVault";
	ch.nation = SPAIN;
	ch.greeting = "official";
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
    ch.watchBoxes = true;
	ch.Storage = true;
	n = n + 1;
	
	return n;
}
