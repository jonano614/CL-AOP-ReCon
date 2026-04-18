//  файл для кораблей в порту, море и сторожевиков
void GenerateIslandShips(string sIslandID)
{
	int i, iChar, iNation, iShipsQuantity, iShipType = FORT_DEFENDER;
	float fChecker;
	ref rChar;

	for (i = 0; i< MAX_COLONIES; i++)
	{
		if (Colonies[i].island == sIslandID)
		{
			if (colonies[i].nation != "none" && !CheckAttribute(&colonies[i], "HasNoFort") && !CheckAttribute(&colonies[i], "DontSetShipInPort"))
			{
				if (!CheckAttribute(&colonies[i], "GenShipDate") || GetNpcQuestPastDayParam(&colonies[i], "GenShipDate") > 0)
				{
                    SaveCurrentNpcQuestDateParam(&colonies[i], "GenShipDate");
                    
					iNation = sti(Colonies[i].nation);
					fChecker = frand(1.0);
					if (fChecker < 0.9)
					{
						iShipsQuantity = makeint(fChecker * 4.0);
						while (iShipsQuantity > 0)
						{
							if (rand(1))
								iShipType = TRADER;
							else
								iShipType = FORT_DEFENDER;

							iChar = GeneratePortCharacter(iNation, WITH_SHIP, "pofficer", MAN, -1, iShipType);
							PlaceCharacterShip(iChar, iNation, sIslandID, i);
							rChar = GetCharacter(iChar);
                            rChar.IslandShips = Colonies[i].id; // номер города, чтоб тереть по захвату города TODO
							
							if (iNation == PIRATE) // наш город; TODO: здесь особый стек капитанов
							{	//TODO: Особая логика пиратских портов не наших городов
								rChar.AlwaysFriend = true;
								SetCharacterRelationBoth(iChar, GetMainCharacterIndex(), RELATION_FRIEND);
							}
							
							if (iShipType == FORT_DEFENDER)
								rChar.Ship.Mode = "war";
							else
								rChar.Ship.Mode = "trade";
							
							if (rand(4) == 1 || GetCharacterShipClass(rChar) == 1) SetRandGeraldSail(rChar, sti(rChar.Nation));
							rChar.AlwaysSandbankManeuver = true;  // тупым запрет тонуть об берег
							rChar.AnalizeShips = true; //анализить вражеские корабли
							rChar.location.from_sea = colonies[i].from_sea;
							SetCaptanModelByEncType(rChar, rChar.Ship.Mode);
							Fantom_SetCannons(rChar, rChar.Ship.Mode);
							Fantom_SetBalls(rChar, rChar.Ship.Mode);
							Fantom_SetGoods(rChar, rChar.Ship.Mode);
							iShipsQuantity = iShipsQuantity - 1;
						}
					}
				}
			}
		}
	}
}

void PlaceCharacterShip(int iChar, int iNation, string sIslandID, int iColonyIdx)
{
	//TODO: проставить корректные num у островов с несколькими портами
	int iColonyNum = sti(colonies[iColonyIdx].num);
	
	string sColonyID = colonies[iColonyIdx].id;
	
	string sGroup = "IslandGroup" + iChar;
	
	Group_AddCharacter(sGroup, characters[iChar].id);
	Group_SetGroupCommander(sGroup, characters[iChar].id);	
	string sLocatorGroup = "IslandShips" + iColonyNum;
	string sLocator = "Ship_"+(rand(5)+1);
	Group_SetAddress(sGroup, sIslandID, sLocatorGroup, sLocator);

	//trace("sLocatorGroup is " + sLocatorGroup + " sLocator is " + sLocator);

	int iTask = rand(1);
	
	float x, z;
	if (iTask == 0)
	{
		x = rand(1000000);
		z = rand(1000000);
		Group_SetTaskMove(sGroup, x, z);
	}
	else
	{
		Ship_SetTaskDrift(SECONDARY_TASK, iChar);
		//Group_SetTaskNone(sGroup);
	}

	if (sti(characters[iChar].nation) != PIRATE && GetNationRelation2Character(iNation, nMainCharacterIndex) == RELATION_ENEMY)
	{
		Group_SetTaskAttack(sGroup, PLAYER_GROUP);
	}
}
// очистить порт
void ClearIslandShips(string _city)
{
	if (!bSeaActive)
	{
		for (int i=GlobalCharacters; i<MAX_CHARACTERS; i++)
		{
			// отдельный код зачистки boal
			if (CheckAttribute(&characters[i], "IslandShips") && characters[i].IslandShips == _city)
			{
				InitCharacter(&characters[i], i);
			}
		}
		// потрем пустые группы
		Group_FreeAllDead();
	}
}