
int CreateTrinidadCharacters(int n)
{
	ref ch;
	
	///////////////////////////////////////////////////////////////////////////////
	// ОСНОВНЫЕ ПЕРСОНАЖИ
	///////////////////////////////////////////////////////////////////////////////
	makeref(ch,Characters[n]);			//Губернатор
	ch.id		= "PortSpein_Mayor";
	ch.model	= "huber_13";
	ch.sex = "man";
	ch.City = "PortSpein";
	ch.location	= "PortSpein_townhall";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Mayor.c";
	ch.greeting = "eng_gov_common";
	ch.nation = ENGLAND;
	ch.quest.type = "hovernor";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, BLADE_LONG);
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.watchBoxes = true;
	ch.standUp = true; //вставать и нападать на врага
	LAi_SetHuberType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Священик
	ch.id		= "PortSpein_Priest";
	ch.model	= "priest_11";
	ch.model.animation	= "man";
	ch.sex = "man";
	ch.City = "PortSpein";
	ch.location	= "PortSpein_church";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Church.c";
	ch.greeting = "Gr_Church";
	ch.nation = ENGLAND;
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetPriestType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);		// ОФициантка
	ch.id		= "PortSpein_waitress";
	ch.model	= "women_11";
	ch.sex = "woman";
	ch.City = "PortSpein";
	ch.location	= "PortSpein_tavern";
	ch.location.group = "waitress";
	ch.location.locator = "barmen";
	ch.Dialog.Filename = "Common_Waitress.c";
	ch.greeting = "Gr_officiant";
	ch.nation = ENGLAND;
	LAi_SetWaitressType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Трактирщик
	ch.id		= "PortSpein_tavernkeeper";
	ch.model	= "barmen_14";
	ch.greeting = "Gr_Barmen";
	ch.sex = "man";
	ch.City = "PortSpein";
	ch.location	= "PortSpein_Tavern";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Tavern.c";
	ch.TavernMan = true;
	ch.nation = ENGLAND;
	LAi_SetBarmanType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;


	makeref(ch,Characters[n]);			//Торговец
	ch.id		= "PortSpein_trader";
	ch.model	= "trader_15";
	ch.greeting = "tra_common";
	ch.sex = "man";
	ch.City = "PortSpein";
	ch.location	= "PortSpein_Store";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Store.c";
	ch.quest.type = "trader";
	ch.nation = ENGLAND;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	ch.Merchant = true;
    ch.money = makeint(STORE_TRADER_MIN_MONEY + frand(1.0)*STORE_TRADER_RAND_MONEY);
	n = n + 1;

	makeref(ch,Characters[n]);			//Корабел
	ch.id		= "PortSpein_shipyarder";
	ch.model	= "shipowner_15";
	ch.sex = "man";
	ch.City = "PortSpein";
	ch.location	= "PortSpein_Shipyard";
	ch.greeting = "Gr_shipyarder";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Shipyard.c";
	ch.nation = ENGLAND;
	ch.quest.shiping = "0";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, "topor1");
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.watchBoxes = true;
	ch.standUp = true; //вставать и нападать на врага
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Банкир
	ch.id		= "PortSpein_usurer";
	ch.model	= "usurer_2";
	ch.sex = "man";
	ch.City = "PortSpein";
	ch.location	= "PortSpein_Bank";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Usurer.c";
	ch.nation = ENGLAND;
	ch.greeting = "Gr_bankeer";
	ch.quest.shiping = "0";
	ch.UsurerDeposit = 5000; // *1000 денег
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
    ch.Merchant = true;
    ch.money = makeint(BANK_TRADER_MIN_MONEY + frand(1.0)*BANK_TRADER_RAND_MONEY);
	n = n + 1;

	makeref(ch,Characters[n]);			//Начальник порта
	ch.id		= "PortSpein_PortMan";
	ch.model	= "portman_14";
	ch.sex = "man";
	ch.City = "PortSpein";
	ch.location	= "PortSpein_PortOffice";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Portman.c";
	ch.nation = ENGLAND;
	ch.greeting = "portmans";
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;

    makeref(ch,Characters[n]);
	ch.name 	= UpperFirst(XI_ConvertString("WhoSmuggler"));
	ch.lastname = "";
	ch.id		= "PortSpein_Smuggler";
	ch.model    = "citiz_21";
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
	ch.id		= "PortSpein_Lightman";
	ch.model	= "keeper_5";
	ch.model.animation = "man_B";
	ch.sex = "man";
	ch.City = "PortSpein";
	ch.location = "Mayak1_Lighthouseroom";
	ch.location.group = "barmen";
	ch.location.locator = "bar2";
	ch.Dialog.Filename = "Common_Lighthouse.c";
	ch.greeting = "lighthouseman_1";
	ch.Merchant = true;
    // ch.Merchant.type = "lightman";
    ch.money = makeint(LIGHT_TRADER_MIN_MONEY + frand(1.0)*LIGHT_TRADER_RAND_MONEY);
	ch.nation = ENGLAND;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Заведущий пакгауза
	ch.id		= "PortSpein_GlavSklad";
	ch.model	= "citiz_19";
	ch.sex = "man";
	ch.City = "PortSpein";
	ch.location	= "PortSpein_PackhouseOffice";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "House_dialog.c";
	ch.dialog.currentnode = "GlavSklad";
	ch.nation = ENGLAND;
	ch.greeting = "official";
    ch.nonTable = true;
    ch.standUp = true;
    ch.watchBoxes = true;
	LAi_SetSitType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.Storage = true;
	ch.item_date = "";
	n = n + 1;

	makeref(ch,Characters[n]);			//Заведающий хранилища
	ch.id		= "PortSpein_bankvault";
	ch.model	= "citiz_14";
	ch.sex = "man";
	ch.City = "PortSpein";
	ch.location	= "PortSpein_bankvault";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "House_dialog.c";
	ch.dialog.currentnode = "GlavBankVault";
	ch.nation = ENGLAND;
	ch.greeting = "official";
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
    ch.watchBoxes = true;
	ch.Storage = true;
	n = n + 1;
	
	return n;
}
