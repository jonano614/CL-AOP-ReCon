
int CreateBelizCharacters(int n)
{
	ref ch;
	
	///////////////////////////////////////////////////////////////////////////////
	// ОСНОВНЫЕ ПЕРСОНАЖИ
	///////////////////////////////////////////////////////////////////////////////

	makeref(ch,Characters[n]);			//Губернатор
	ch.id		= "Beliz_Mayor";
	ch.model	= "huber_17";
	ch.sex = "man";
	ch.City = "Beliz";
	ch.location	= "Beliz_townhall";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.greeting = "spa_gov_common";
	ch.Dialog.Filename = "Common_Mayor.c";
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
	ch.id		= "Beliz_Priest";
	ch.model	= "priest_7";
	ch.model.animation = "man";
	ch.sex = "man";
	ch.City = "Beliz";
	ch.location	= "Beliz_church";
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
	ch.id		= "Beliz_waitress";
	ch.model	= "women_7";
	ch.sex = "woman";
	ch.City = "Beliz";
	ch.location	= "Beliz_tavern";
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
	ch.id		= "Beliz_tavernkeeper";
	ch.model	= "barmen_27";
	ch.greeting = "Gr_Barmen";
	ch.sex = "man";
	ch.City = "Beliz";
	ch.location	= "Beliz_Tavern";
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
	ch.id		= "Beliz_trader";
	ch.model	= "trader_11";
	ch.greeting = "tra_common";
	ch.sex = "man";
	ch.City = "Beliz";
	ch.location	= "Beliz_Store";
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
	ch.id		= "Beliz_shipyarder";
	ch.model	= "shipowner_11";
	ch.greeting = "Gr_shipyarder";
	ch.sex = "man";
	ch.City = "Beliz";
	ch.location	= "Beliz_Shipyard";
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
	ch.id		= "Beliz_usurer";
	ch.model	= "usurer_11";
	ch.sex = "man";
	ch.City = "Beliz";
	ch.location	= "Beliz_Bank";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Usurer.c";
	ch.nation = SPAIN;
	ch.greeting = "Gr_bankeer";
	ch.quest.shiping = "0";
	ch.UsurerDeposit = 9000; // *1000 денег
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
    ch.Merchant = true;
    ch.money = makeint(BANK_TRADER_MIN_MONEY + frand(1.0)*BANK_TRADER_RAND_MONEY);
	n = n + 1;
	
	makeref(ch,Characters[n]);			//Начальник порта
	ch.id		= "Beliz_PortMan";
	ch.model	= "portman_3";
	ch.sex = "man";
	ch.City = "Beliz";
	ch.location	= "Beliz_PortOffice";
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
	ch.id		= "Beliz_Smuggler";
	ch.model    = "citiz_23";
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

	makeref(ch,Characters[n]);			//Заведущий пакгауза
	ch.id		= "Beliz_GlavSklad";
	ch.model	= "citiz_13";
	ch.sex = "man";
	ch.City = "Beliz";
	ch.location	= "Beliz_PackhouseOffice";
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
	ch.id		= "Beliz_bankvault";
	ch.model	= "citiz_18";
	ch.sex = "man";
	ch.City = "Beliz";
	ch.location	= "Beliz_bankvault";
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
