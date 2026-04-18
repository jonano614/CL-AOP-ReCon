int CreateOtherCharacters(int n)
{
	ref ch;
	
	////////////////////////////////////////////////////////////////////////////////////////
	/// персонаж для ВАНО
	/// делаем его неписем для корректного отображения флага ГГ на шлюпке
	////////////////////////////////////////////////////////////////////////////////////////
	

	makeref(ch,Characters[n]);		// boat character  // boal
	ch.name 	= FindPersonalName("BoatChar_name");
	ch.lastname = FindPersonalName("BoatChar_name");
	ch.id		= "BoatChar";
	ch.nation	= ENGLAND;
	ch.activity_begin = "0";
	ch.activity_end = "24";
	ch.experience = "0";
	ch.Ship.Name = XI_ConvertString("Boat");
	ch.Ship.Type = GenerateShip(SHIP_BOAT, 1);
	ch.Ship.Stopped = true;
	n = n + 1;

	makeref(ch,Characters[n]);		//скорлупка
    ch.name 	= FindPersonalName("Skorlupka_name");
    ch.lastname = FindPersonalName("Skorlupka_name");
    ch.id		= "Skorlupka";
    ch.nation	= PIRATE;
    ch.activity_begin = "0";
    ch.activity_end = "24";
    ch.experience = "0";
    ch.Ship.Name = XI_ConvertString("Skorlupka");
    ch.Ship.Type = GenerateShip(SHIP_SHELL, 1);
    ch.Ship.Stopped = true;
    n = n + 1;
	
	return n;
}
