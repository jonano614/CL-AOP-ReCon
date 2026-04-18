
int CreateJamaicaCharacters(int n)
{
	ref ch;
	
	///////////////////////////////////////////////////////////////////////////////
	// ОСНОВНЫЕ ПЕРСОНАЖИ
	///////////////////////////////////////////////////////////////////////////////

	makeref(ch,Characters[n]);			//Губернатор
	ch.id		= "PortRoyal_Mayor";
	ch.model	= "huber_9";
	ch.sex = "man";
	//ch.name 	= "Эдвард";
    //ch.lastname = "Дойли";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_townhall";
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
	ch.id		= "PortRoyal_Priest";
	ch.model	= "priest_9";
	ch.model.animation = "man_kvl2";
	ch.sex = "man";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_church";
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
	ch.id		= "PortRoyal_waitress";
	ch.model	= "girl_10";
	ch.sex = "woman";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_tavern";
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
	ch.id		= "PortRoyal_tavernkeeper";
	ch.model	= "barmen_24";
	ch.greeting = "Gr_Barmen";
	ch.sex = "man";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_Tavern";
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
	ch.id		= "PortRoyal_trader";
	ch.model	= "trader_13";
	ch.greeting = "tra_common";
	ch.sex = "man";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_Store";
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
	ch.id		= "PortRoyal_shipyarder";
	ch.model	= "shipowner_13";
	ch.greeting = "Gr_shipyarder";
	ch.sex = "man";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_Shipyard";
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
	ch.id		= "PortRoyal_usurer";
	ch.model	= "usurer_14";
	ch.sex = "man";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_Bank";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Usurer.c";
	ch.nation = ENGLAND;
	ch.greeting = "Gr_bankeer";
	ch.quest.shiping = "0";
	ch.UsurerDeposit = 9000; // *1000 денег
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
    ch.Merchant = true;
    ch.money = makeint(BANK_TRADER_MIN_MONEY + frand(1.0)*BANK_TRADER_RAND_MONEY);
	n = n + 1;

	makeref(ch,Characters[n]);			//Начальник порта
	ch.id		= "PortRoyal_PortMan";
	ch.model	= "portman_10";
	ch.sex = "man";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_PortOffice";
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

	makeref(ch,Characters[n]);			//Хозяйка борделя
	ch.id		= "PortRoyal_Hostess";
	ch.name		= FindPersonalName("PortRoyal_Hostess_name");
	ch.lastname = "";
	ch.model	= "Maman_2";
	ch.model.animation = "woman_B";
	ch.sex = "woman";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_SecBrRoom";
	ch.location.group = "goto";
	ch.location.locator = "goto8";
	ch.Dialog.Filename = "Common_Brothel.c";
	ch.greeting = "hostess";
	ch.nation = ENGLAND;
	ch.questChurch = ""; //флаг для пожертвований
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	n = n + 1;

    makeref(ch,Characters[n]);
	ch.name 	= UpperFirst(XI_ConvertString("WhoSmuggler"));
	ch.lastname = "";
	ch.id		= "PortRoyal_Smuggler";
	ch.model    = "citiz_26";
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
	
	makeref(ch,Characters[n]);			//Смотритель кладбища
	ch.id		= "PortRoyal_Cemeteryman";
	ch.model	= "keeper_6";
	ch.model.animation = "man_B";
	ch.sex = "man";
	ch.City = "PortRoyal";
	ch.location = "PortRoyal_KeepersHouse";
	ch.location.group = "goto";
	ch.location.locator = "goto5";
	ch.Dialog.Filename = "Common_Cemeteryman.c";
	ch.greeting = "lighthouseman_2";
	ch.Merchant = true;
	// ch.Merchant.type = "cemeteryman";
	ch.money = makeint(LIGHT_TRADER_MIN_MONEY + frand(1.0)*LIGHT_TRADER_RAND_MONEY);
	ch.nation = ENGLAND;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "ENGLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Заведущий пакгауза
	ch.id		= "PortRoyal_GlavSklad";
	ch.model	= "citiz_19";
	ch.sex = "man";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_PackhouseOffice";
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
	ch.id		= "PortRoyal_bankvault";
	ch.model	= "citiz_11";
	ch.sex = "man";
	ch.City = "PortRoyal";
	ch.location	= "PortRoyal_bankvault";
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
	
   //=============== форт Оранж ===============

	makeref(ch,Characters[n]);			//Губернатор
	ch.id		= "FortOrange_Mayor";
	ch.model	= "huber_25";
	ch.sex = "man";
	ch.City = "FortOrange";
	ch.location	= "FortOrange_townhall";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Mayor.c";
	ch.nation = HOLLAND;
	ch.quest.type = "hovernor";
	ch.greeting = "eng_gov_common";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, BLADE_LONG);
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.watchBoxes = true;
	ch.standUp = true; //вставать и нападать на врага
	LAi_SetHuberType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;
	
	makeref(ch,Characters[n]);			//Священик
	ch.id		= "FortOrange_Priest";
	ch.model	= "priest_8";
	ch.model.animation = "man";
	ch.sex = "man";
	ch.City = "FortOrange";
	ch.location	= "FortOrange_church";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Church.c";
	ch.greeting = "Gr_Church";
	ch.nation = HOLLAND;
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetPriestType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);		// ОФициантка
	ch.id		= "FortOrange_waitress";
	ch.model	= "women_3";
	ch.sex = "woman";
	ch.City = "FortOrange";
	ch.location	= "FortOrange_tavern";
	ch.location.group = "waitress";
	ch.location.locator = "barmen";
	ch.Dialog.Filename = "Common_Waitress.c";
	ch.greeting = "Gr_officiant";
	ch.nation = HOLLAND;
	LAi_SetWaitressType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Трактирщик
	ch.id		= "FortOrange_tavernkeeper";
	ch.model	= "barmen_8";
	ch.greeting = "Gr_Barmen";
	ch.sex = "man";
	ch.City = "FortOrange";
	ch.location	= "FortOrange_Tavern";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Tavern.c";
	ch.TavernMan = true;
	ch.nation = HOLLAND;
	LAi_SetBarmanType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Торговец
	ch.id		= "FortOrange_trader";
	ch.model	= "trader_10";
	ch.greeting = "tra_common";
	ch.sex = "man";
	ch.City = "FortOrange";
	ch.location	= "FortOrange_Store";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Store.c";
	ch.quest.type = "trader";
	ch.nation = HOLLAND;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	ch.Merchant = true;
    ch.money = makeint(STORE_TRADER_MIN_MONEY + frand(1.0)*STORE_TRADER_RAND_MONEY);
	n = n + 1;

    makeref(ch,Characters[n]);
	ch.name 	= UpperFirst(XI_ConvertString("WhoSmuggler")); //Контрабандист
	ch.lastname = "";
	ch.id		= "FortOrange_Smuggler";
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
	
	//////////////////////////////  Рудник Форт Оранжа /////////////////////////
	
	makeref(ch,Characters[n]);			//Комендант
	ch.id		= "Minetown_Commend";
	ch.model	= "off_hol_1";
	ch.sex = "man";
	ch.name 	= FindPersonalName("Minetown_Commend_name");
    ch.lastname = FindPersonalName("Minetown_Commend_lastname");
	ch.City = "FortOrange_Mine";
	ch.location	= "Mine_residence";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Mayor\Minentown_mayor.c";
	ch.greeting = "eng_gov_common";
	ch.nation = HOLLAND;
	ch.quest.type = "hovernor";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, BLADE_LONG);
	EquipCharacterbyItem(ch, GUN_COMMON);
	EquipCharacterbyItem(ch, BLADE_LONG);
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.watchBoxes = true;
	ch.standUp = true; //вставать и нападать на врага
	LAi_SetHuberType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
    LAi_LoginInCaptureTown(ch, true);
	n = n + 1;
	
	return n;
}
