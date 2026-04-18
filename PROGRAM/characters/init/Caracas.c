
int CreateCaracasCharacters(int n)
{
	ref ch;
	
	///////////////////////////////////////////////////////////////////////////////
	// ОСНОВНЫЕ ПЕРСОНАЖИ
	///////////////////////////////////////////////////////////////////////////////

	makeref(ch,Characters[n]);			//Губернатор
	ch.id		= "Caracas_Mayor";
	ch.model	= "huber_21";
	ch.sex = "man";
	ch.City = "Caracas";
	ch.location	= "Caracas_townhall";
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
    LAi_LoginInCaptureTown(ch, true); //TODO eddy, снести
	n = n + 1;

    makeref(ch,Characters[n]);			//Священик
	ch.id		= "Caracas_Priest";
	ch.model	= "priest_1";
	ch.model.animation = "man_kvl2";
	ch.sex = "man";
	ch.City = "Caracas";
	ch.location	= "Caracas_church";
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
	ch.id		= "Caracas_waitress";
	ch.model	= "women_8";
	ch.sex = "woman";
	ch.City = "Caracas";
	ch.location	= "Caracas_tavern";
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
	ch.id		= "Caracas_tavernkeeper";
	ch.model	= "barmen_7";
	ch.greeting = "Gr_Barmen";
	ch.sex = "man";
	ch.City = "Caracas";
	ch.location	= "Caracas_Tavern";
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
	ch.id		= "Caracas_trader";
	ch.model	= "trader_7";
	ch.greeting = "tra_common";
	ch.sex = "man";
	ch.City = "Caracas";
	ch.location	= "Caracas_Store";
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
	ch.id		= "Caracas_shipyarder";
	ch.model	= "shipowner_7";
	ch.greeting = "Gr_shipyarder";
	ch.sex = "man";
	ch.City = "Caracas";
	ch.location	= "Caracas_Shipyard";
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
	ch.id		= "Caracas_usurer";
	ch.model	= "usurer_3";
	ch.sex = "man";
	ch.City = "Caracas";
	ch.location	= "Caracas_Bank";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Usurer.c";
	ch.nation = SPAIN;
	ch.greeting = "Gr_bankeer";
	ch.quest.shiping = "0";
	ch.UsurerDeposit = 8000; // *1000 денег
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
    ch.Merchant = true;
    ch.money = makeint(BANK_TRADER_MIN_MONEY + frand(1.0)*BANK_TRADER_RAND_MONEY);
	n = n + 1;

	makeref(ch,Characters[n]);			//Начальник порта
	ch.id		= "Caracas_PortMan";
	ch.model	= "portman_7";
	ch.sex = "man";
	ch.City = "Caracas";
	ch.location	= "Caracas_PortOffice";
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
	ch.id		= "Caracas_Smuggler";
	ch.model    = "citiz_30";
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
	ch.id		= "Caracas_GlavSklad";
	ch.model	= "citiz_14";
	ch.sex = "man";
	ch.City = "Caracas";
	ch.location	= "Caracas_PackhouseOffice";
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
	ch.id		= "Caracas_bankvault";
	ch.model	= "citiz_17";
	ch.sex = "man";
	ch.City = "Caracas";
	ch.location	= "Caracas_bankvault";
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
