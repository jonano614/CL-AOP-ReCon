void InitNations()
{
	ref rNation;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	// АНГЛИЯ
	//////////////////////////////////////////////////////////////////////////////////////////////////
	makeref(rNation,Nations[ENGLAND]);
	rNation.Name = "England";
	rNation.ShortName = "Eng";
	rNation.worldMapShip = "british";
	rNation.fort = 0;  // количество фортов у нации, заполняется само в начале, методом CreateColonyCommanders
	
	//Rosarak: В данный момент в игре нет ни одного использования LAi_CharacterReincarnation
	//с аргументами (sld, true, false), поэтому всё, что написано fantomModel, не используется
	//для перерождения фантомов
	
	//Rosarak: Указкывать ani = "man" нет необходимости, так как она по умолчанию выставляется
	//в соответствующих функциях
	
	//TODO: разделение на ветеранов и обычных с привязкой к снаряжению
	//TODO: методы для раздения офицеров и солдат, чтобы одни не подменяли других в виде фантомов
	//TODO: появление офицеров во время абордажа, когда будет функционал их привязки к капитанам
	
	//Наземные Войска
	//ОФИЦЕРЫ
	rNation.fantomModel_off.m0 = "off_eng_5";
	rNation.fantomModel_off.m1 = "off_eng_6";
	//СОЛДАТЫ
	rNation.fantomModel.m0 = "sold_eng_1";
	rNation.fantomModel.m1 = "sold_eng_2";
	rNation.fantomModel.m2 = "sold_eng_3";
	rNation.fantomModel.m3 = "sold_eng_4";
	rNation.fantomModel.m4 = "sold_eng_5";
	rNation.fantomModel.m5 = "sold_eng_6";
	rNation.fantomModel.m6 = "sold_eng_7";
	rNation.fantomModel.m7 = "sold_eng_8";
	//ВЕТЕРАНЫ
	rNation.fantomModel_elite.m0 = "sold_eng_9";
	rNation.fantomModel_elite.m1 = "sold_eng_10";
	rNation.fantomModel_elite.m2 = "sold_eng_11";
	rNation.fantomModel_elite.m3 = "sold_eng_12";
	rNation.fantomModel_elite.m4 = "sold_eng_13";
	rNation.fantomModel_elite.m5 = "sold_eng_14";
	rNation.fantomModel_elite.m6 = "sold_eng_15";
	rNation.fantomModel_elite.m7 = "sold_eng_16";
	
	//Морская Пехота
	//ОФИЦЕРЫ (МЛАДШИЕ)
	rNation.fantomModel_off.m0 = "navy_off_eng_1";
	rNation.fantomModel_off.m1 = "navy_off_eng_2";
	//СОЛДАТЫ
	rNation.boardingModel.enemy.m0 = "navy_eng_1";
	rNation.boardingModel.enemy.m1 = "navy_eng_2";
	rNation.boardingModel.enemy.m2 = "navy_eng_3";
	rNation.boardingModel.enemy.m3 = "navy_eng_4";
	rNation.boardingModel.enemy.m4 = "navy_eng_5";
	rNation.boardingModel.enemy.m5 = "navy_eng_6";
	rNation.boardingModel.enemy.m6 = "navy_eng_7";
	rNation.boardingModel.enemy.m7 = "navy_eng_8";
	//ВЕТЕРАНЫ
	rNation.boardingModel.enemy_elite.m0 = "navy_eng_9";
	rNation.boardingModel.enemy_elite.m1 = "navy_eng_10";
	rNation.boardingModel.enemy_elite.m2 = "navy_eng_11";
	rNation.boardingModel.enemy_elite.m3 = "navy_eng_12";
	rNation.boardingModel.enemy_elite.m4 = "navy_eng_13";
	rNation.boardingModel.enemy_elite.m5 = "navy_eng_14";
	rNation.boardingModel.enemy_elite.m6 = "navy_eng_15";
	rNation.boardingModel.enemy_elite.m7 = "navy_eng_16";
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	// ФРАНЦИЯ
	//////////////////////////////////////////////////////////////////////////////////////////////////
	makeref(rNation,Nations[FRANCE]);
	rNation.Name = "France";
	rNation.ShortName = "Fra";
	rNation.worldMapShip = "french";
	rNation.fort = 0;
	
	//Наземные Войска
	//ОФИЦЕРЫ
	rNation.fantomModel_off.m0 = "off_fra_5";
	rNation.fantomModel_off.m1 = "off_fra_6";
	//СОЛДАТЫ
	rNation.fantomModel.m0 = "sold_fra_1";
	rNation.fantomModel.m1 = "sold_fra_2";
	rNation.fantomModel.m2 = "sold_fra_3";
	rNation.fantomModel.m3 = "sold_fra_4";
	rNation.fantomModel.m4 = "sold_fra_5";
	rNation.fantomModel.m5 = "sold_fra_6";
	rNation.fantomModel.m6 = "sold_fra_7";
	rNation.fantomModel.m7 = "sold_fra_8";
	//ВЕТЕРАНЫ
	rNation.fantomModel_elite.m0 = "sold_fra_9";
	rNation.fantomModel_elite.m1 = "sold_fra_10";
	rNation.fantomModel_elite.m2 = "sold_fra_11";
	rNation.fantomModel_elite.m3 = "sold_fra_12";
	rNation.fantomModel_elite.m4 = "sold_fra_13";
	rNation.fantomModel_elite.m5 = "sold_fra_14";
	rNation.fantomModel_elite.m6 = "sold_fra_15";
	rNation.fantomModel_elite.m7 = "sold_fra_16";
	
	//Морская Пехота
	//ОФИЦЕРЫ (МЛАДШИЕ)
	rNation.fantomModel_off.m0 = "navy_off_fra_1";
	rNation.fantomModel_off.m1 = "navy_off_fra_2";
	//СОЛДАТЫ
	rNation.boardingModel.enemy.m0 = "navy_fra_1";
	rNation.boardingModel.enemy.m1 = "navy_fra_2";
	rNation.boardingModel.enemy.m2 = "navy_fra_3";
	rNation.boardingModel.enemy.m3 = "navy_fra_4";
	rNation.boardingModel.enemy.m4 = "navy_fra_5";
	rNation.boardingModel.enemy.m5 = "navy_fra_6";
	rNation.boardingModel.enemy.m6 = "navy_fra_7";
	rNation.boardingModel.enemy.m7 = "navy_fra_8";
	//ВЕТЕРАНЫ
	rNation.boardingModel.enemy_elite.m0 = "navy_fra_9";
	rNation.boardingModel.enemy_elite.m1 = "navy_fra_10";
	rNation.boardingModel.enemy_elite.m2 = "navy_fra_11";
	rNation.boardingModel.enemy_elite.m3 = "navy_fra_12";
	rNation.boardingModel.enemy_elite.m4 = "navy_fra_13";
	rNation.boardingModel.enemy_elite.m5 = "navy_fra_14";
	rNation.boardingModel.enemy_elite.m6 = "navy_fra_15";
	rNation.boardingModel.enemy_elite.m7 = "navy_fra_16";
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	// ИСПАНИЯ
	//////////////////////////////////////////////////////////////////////////////////////////////////
	makeref(rNation,Nations[SPAIN]);
	rNation.Name = "Spain";
	rNation.ShortName = "Spa";
	rNation.worldMapShip = "spanish";
	rNation.fort = 0;
	
	//Наземные Войска
	//ОФИЦЕРЫ
	rNation.fantomModel_off.m0 = "off_spa_5";
	rNation.fantomModel_off.m1 = "off_spa_6";
	//СОЛДАТЫ
	rNation.fantomModel.m0 = "sold_spa_1";
	rNation.fantomModel.m1 = "sold_spa_2";
	rNation.fantomModel.m2 = "sold_spa_3";
	rNation.fantomModel.m3 = "sold_spa_4";
	rNation.fantomModel.m4 = "sold_spa_5";
	rNation.fantomModel.m5 = "sold_spa_6";
	rNation.fantomModel.m6 = "sold_spa_7";
	rNation.fantomModel.m7 = "sold_spa_8";
	//ВЕТЕРАНЫ
	rNation.fantomModel_elite.m0 = "sold_spa_9";
	rNation.fantomModel_elite.m1 = "sold_spa_10";
	rNation.fantomModel_elite.m2 = "sold_spa_11";
	rNation.fantomModel_elite.m3 = "sold_spa_12";
	rNation.fantomModel_elite.m4 = "sold_spa_13";
	rNation.fantomModel_elite.m5 = "sold_spa_14";
	rNation.fantomModel_elite.m6 = "sold_spa_15";
	rNation.fantomModel_elite.m7 = "sold_spa_16";
	
	//Морская Пехота
	//ОФИЦЕРЫ (МЛАДШИЕ)
	rNation.fantomModel_off.m0 = "navy_off_spa_1";
	rNation.fantomModel_off.m1 = "navy_off_spa_2";
	//СОЛДАТЫ
	rNation.boardingModel.enemy.m0 = "navy_spa_1";
	rNation.boardingModel.enemy.m1 = "navy_spa_2";
	rNation.boardingModel.enemy.m2 = "navy_spa_3";
	rNation.boardingModel.enemy.m3 = "navy_spa_4";
	rNation.boardingModel.enemy.m4 = "navy_spa_5";
	rNation.boardingModel.enemy.m5 = "navy_spa_6";
	rNation.boardingModel.enemy.m6 = "navy_spa_7";
	rNation.boardingModel.enemy.m7 = "navy_spa_8";
	//ВЕТЕРАНЫ
	rNation.boardingModel.enemy_elite.m0 = "navy_spa_9";
	rNation.boardingModel.enemy_elite.m1 = "navy_spa_10";
	rNation.boardingModel.enemy_elite.m2 = "navy_spa_11";
	rNation.boardingModel.enemy_elite.m3 = "navy_spa_12";
	rNation.boardingModel.enemy_elite.m4 = "navy_spa_13";
	rNation.boardingModel.enemy_elite.m5 = "navy_spa_14";
	rNation.boardingModel.enemy_elite.m6 = "navy_spa_15";
	rNation.boardingModel.enemy_elite.m7 = "navy_spa_16";
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	// ГОЛЛАНДИЯ
	//////////////////////////////////////////////////////////////////////////////////////////////////
	makeref(rNation,Nations[HOLLAND]);
	rNation.Name = "Holland";
	rNation.ShortName = "Hol";
	rNation.worldMapShip = "dutch";
	rNation.fort = 0;
	
	//Наземные Войска
	//ОФИЦЕРЫ
	rNation.fantomModel_off.m0 = "off_hol_5";
	rNation.fantomModel_off.m1 = "off_hol_6";
	//СОЛДАТЫ
	rNation.fantomModel.m0 = "sold_hol_1";
	rNation.fantomModel.m1 = "sold_hol_2";
	rNation.fantomModel.m2 = "sold_hol_3";
	rNation.fantomModel.m3 = "sold_hol_4";
	rNation.fantomModel.m4 = "sold_hol_5";
	rNation.fantomModel.m5 = "sold_hol_6";
	rNation.fantomModel.m6 = "sold_hol_7";
	rNation.fantomModel.m7 = "sold_hol_8";
	//ВЕТЕРАНЫ
	rNation.fantomModel_elite.m0 = "sold_hol_9";
	rNation.fantomModel_elite.m1 = "sold_hol_10";
	rNation.fantomModel_elite.m2 = "sold_hol_11";
	rNation.fantomModel_elite.m3 = "sold_hol_12";
	rNation.fantomModel_elite.m4 = "sold_hol_13";
	rNation.fantomModel_elite.m5 = "sold_hol_14";
	rNation.fantomModel_elite.m6 = "sold_hol_15";
	rNation.fantomModel_elite.m7 = "sold_hol_16";
	
	//Морская Пехота
	//ОФИЦЕРЫ (МЛАДШИЕ)
	rNation.fantomModel_off.m0 = "navy_off_hol_1";
	rNation.fantomModel_off.m1 = "navy_off_hol_2";
	//СОЛДАТЫ
	rNation.boardingModel.enemy.m0 = "navy_hol_1";
	rNation.boardingModel.enemy.m1 = "navy_hol_2";
	rNation.boardingModel.enemy.m2 = "navy_hol_3";
	rNation.boardingModel.enemy.m3 = "navy_hol_4";
	rNation.boardingModel.enemy.m4 = "navy_hol_5";
	rNation.boardingModel.enemy.m5 = "navy_hol_6";
	rNation.boardingModel.enemy.m6 = "navy_hol_7";
	rNation.boardingModel.enemy.m7 = "navy_hol_8";
	//ВЕТЕРАНЫ
	rNation.boardingModel.enemy_elite.m0 = "navy_hol_9";
	rNation.boardingModel.enemy_elite.m1 = "navy_hol_10";
	rNation.boardingModel.enemy_elite.m2 = "navy_hol_11";
	rNation.boardingModel.enemy_elite.m3 = "navy_hol_12";
	rNation.boardingModel.enemy_elite.m4 = "navy_hol_13";
	rNation.boardingModel.enemy_elite.m5 = "navy_hol_14";
	rNation.boardingModel.enemy_elite.m6 = "navy_hol_15";
	rNation.boardingModel.enemy_elite.m7 = "navy_hol_16";
	
	//////////////////////////////////////////////////////////////////////////////////////////////////
	// ПИРАТЫ
	//////////////////////////////////////////////////////////////////////////////////////////////////
	makeref(rNation,Nations[PIRATE]);
	rNation.Name = "Pirate";
	rNation.ShortName = "Pir";
	rNation.worldMapShip = "pirates";
	rNation.fort = 0;
	
	//Наземные Войска
	//ОФИЦЕРЫ
	//...
	//СОЛДАТЫ
	rNation.fantomModel.m0  = "pirate_1";
	rNation.fantomModel.m1  = "pirate_2";
	rNation.fantomModel.m2  = "pirate_3";
	rNation.fantomModel.m3  = "pirate_4";
	rNation.fantomModel.m4  = "pirate_5";
	rNation.fantomModel.m5  = "pirate_6";
	rNation.fantomModel.m6  = "pirate_7";
	rNation.fantomModel.m7  = "pirate_8";
	rNation.fantomModel.m8  = "pirate_9";
	rNation.fantomModel.m9  = "pirate_10";
	rNation.fantomModel.m10 = "pirate_11";
	rNation.fantomModel.m11 = "pirate_12";
	rNation.fantomModel.m12 = "pirate_13";
	rNation.fantomModel.m13 = "pirate_14";
	rNation.fantomModel.m14 = "pirate_15";
	rNation.fantomModel.m15 = "pirate_16";
	//ВЕТЕРАНЫ
	rNation.fantomModel_elite.m0 = "citiz_51";
	rNation.fantomModel_elite.m1 = "citiz_52";
	rNation.fantomModel_elite.m2 = "citiz_53";
	rNation.fantomModel_elite.m3 = "citiz_54";
	rNation.fantomModel_elite.m4 = "citiz_55";
	rNation.fantomModel_elite.m5 = "citiz_56";
	rNation.fantomModel_elite.m6 = "citiz_57";
	rNation.fantomModel_elite.m7 = "citiz_58";
	rNation.fantomModel_elite.m8 = "citiz_59";
	rNation.fantomModel_elite.m9 = "citiz_60";
	
	//Морская пехота
	//ОФИЦЕРЫ
	//...
	//СОЛДАТЫ
	rNation.boardingModel.enemy.m0  = "pirate_1";
	rNation.boardingModel.enemy.m1  = "pirate_2";
	rNation.boardingModel.enemy.m2  = "pirate_3";
	rNation.boardingModel.enemy.m3  = "pirate_4";
	rNation.boardingModel.enemy.m4  = "pirate_5";
	rNation.boardingModel.enemy.m5  = "pirate_6";
	rNation.boardingModel.enemy.m6  = "pirate_7";
	rNation.boardingModel.enemy.m7  = "pirate_8";
	rNation.boardingModel.enemy.m8  = "pirate_9";
	rNation.boardingModel.enemy.m9  = "pirate_10";
	rNation.boardingModel.enemy.m10 = "pirate_11";
	rNation.boardingModel.enemy.m11 = "pirate_12";
	rNation.boardingModel.enemy.m12 = "pirate_13";
	rNation.boardingModel.enemy.m13 = "pirate_14";
	rNation.boardingModel.enemy.m14 = "pirate_15";
	rNation.boardingModel.enemy.m15 = "pirate_16";
	//ВЕТЕРАНЫ
	rNation.boardingModel.enemy_elite.m0 = "citiz_51";
	rNation.boardingModel.enemy_elite.m1 = "citiz_52";
	rNation.boardingModel.enemy_elite.m2 = "citiz_53";
	rNation.boardingModel.enemy_elite.m3 = "citiz_54";
	rNation.boardingModel.enemy_elite.m4 = "citiz_55";
	rNation.boardingModel.enemy_elite.m5 = "citiz_56";
	rNation.boardingModel.enemy_elite.m6 = "citiz_57";
	rNation.boardingModel.enemy_elite.m7 = "citiz_58";
	rNation.boardingModel.enemy_elite.m8 = "citiz_59";
	rNation.boardingModel.enemy_elite.m9 = "citiz_60";
		
	for(int i = 0; i < MAX_NATIONS; i++)
	{
		//МАТРОСЫ ГЛАВНОГО ГЕРОЯ
		makeref(rNation,Nations[i]);
		rNation.boardingModel.player.m0 = "citiz_31";
		rNation.boardingModel.player.m1 = "citiz_32";
		rNation.boardingModel.player.m2 = "citiz_33";
		rNation.boardingModel.player.m3 = "citiz_34";
		rNation.boardingModel.player.m4 = "citiz_35";
		rNation.boardingModel.player.m5 = "citiz_36";
		rNation.boardingModel.player.m6 = "citiz_37";
		rNation.boardingModel.player.m7 = "citiz_38";
		rNation.boardingModel.player.m8 = "citiz_39";
		rNation.boardingModel.player.m9 = "citiz_40";
		//ВЕТЕРАНЫ
		//...
		
		//МАТРОСЫ КУПЦОВ
		rNation.boardingModel.merchant.m0 = "citiz_41";
		rNation.boardingModel.merchant.m1 = "citiz_42";
		rNation.boardingModel.merchant.m2 = "citiz_43";
		rNation.boardingModel.merchant.m3 = "citiz_48";
		rNation.boardingModel.merchant.m4 = "citiz_49";
		rNation.boardingModel.merchant.m5 = "citiz_50";
		rNation.boardingModel.merchant.m6 = "barmen_1";
		rNation.boardingModel.merchant.m7 = "barmen_9";
		//ВЕТЕРАНЫ
		//...
	}
}
