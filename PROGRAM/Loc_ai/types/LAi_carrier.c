#define LAI_TYPE_CARRY	"carrier"

//Инициализация
void LAi_type_carrier_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	//Установим анимацию персонажу
	string sTemp = chr.model;
	if (StrStartsWith(sTemp, "Slave")) sTemp = StrReplaceFirst(sTemp, "Slave", "");
	sTemp =	strcut(sTemp, 0, strlen(sTemp)-2);
	BeginChangeCharacterActions(chr);
	chr.actions.idle.i1 = "Stay_" + sTemp; //заглушка для корректной смены анимации
	chr.actions.nfhit	= sTemp;
	chr.actions.swim	= sTemp;
	chr.actions.forward_walk = sTemp;
	chr.actions.forward_walk_stairs_up = "Stairs_" + sTemp;
	chr.actions.forward_walk_stairs_down = "Stairs_" + sTemp;
	chr.actions.turnLeft = sTemp;
	chr.actions.turnRight = sTemp;
	EndChangeCharacterActions(chr);
	//Установим шаблон идти
	chr.chr_ai.type = LAI_TYPE_CARRY;
	chr.chr_ai.type.checkFight = rand(5)+2;
	//определим маршрут и отправим в путь	
	if (CheckAttribute(chr, "gotoGroup") && CheckAttribute(chr, "gotoLocator"))
	{
		LAi_tmpl_goto_InitTemplate(chr);
		LAi_tmpl_goto_SetLocator(chr, chr.gotoGroup, chr.gotoLocator, -1);
	}
	else
	{
	    chr.firstLoc = LAi_type_carrier_SetPath(chr);
	    ChangeCharacterAddressGroup(chr, Locations[FindLoadedLocation()].id, "reload", chr.firstLoc);
		LAi_tmpl_stay_InitTemplate(chr);
	}
	chr.chr_ai.tmpl.wait = 0;  //таймер ожидания
	chr.chr_ai.tmpl.time = 0;
	chr.chr_ai.tmpl.baseLocator = "";  //откуда идем
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//Процессирование типа персонажа
void LAi_type_carrier_CharacterUpdate(aref chr, float dltTime)
{
	float time;
	float locx, locy, locz;
	if(chr.chr_ai.tmpl == LAI_TMPL_GOTO)
	{
		if (chr.chr_ai.tmpl.state == "goto" && CheckAttribute(chr, "checkMove"))
		{
			time = stf(chr.chr_ai.tmpl.time) + dltTime;
			chr.chr_ai.tmpl.time = time;
			if (time > 1.0)
			{
				GetCharacterPos(chr, &locx, &locy, &locz);
				if (locx == stf(chr.checkMove.locx) && locy == stf(chr.checkMove.locy) && locz == stf(chr.checkMove.locz))
				{
                    LAi_tmpl_goto_Complite(chr);
                    DeleteAttribute(chr, "checkMove");
                    ChangeCharacterAddressGroup(chr, chr.location, "reload", LAi_type_carrier_SetPath(chr));
                    LAi_SetCarrierType(chr); //если совсем застряли даём носильщику вторую жизнь
				}
				else
				{
					if (!CheckAttribute(chr, "chr_ai.tmpl.time.time"))
					{
						chr.chr_ai.tmpl.time = 0;
						chr.chr_ai.tmpl.time.time = 1;
						GetCharacterPos(chr, &locx, &locy, &locz);
						chr.checkMove.locx = locx;
						chr.checkMove.locy = locy;
						chr.checkMove.locz = locz;
					}
					else
					{
						chr.chr_ai.tmpl.time = 0;
						DeleteAttribute(chr, "checkMove");
						DeleteAttribute(chr, "chr_ai.tmpl.time.time");
					}
				}
			}
		}
		if (CheckAttribute(chr, "chr_ai.tmpl.state") && chr.chr_ai.tmpl.state == "falure")
		{
		    time = stf(chr.chr_ai.tmpl.time) + dltTime;
            chr.chr_ai.tmpl.time = time;
            //проверка на "совсем застряли идти не можем" (телепортируемся из этого гиблого места)
            if (CheckAttribute(chr, "checkFalure") && chr.checkFalure == "2")
            {
                LAi_tmpl_goto_Complite(chr);
                DeleteAttribute(chr, "checkFalure");
                DeleteAttribute(chr, "checkMove");
                ChangeCharacterAddressGroup(chr, chr.location, "reload", LAi_type_carrier_SetPath(chr));
                LAi_SetCarrierType(chr); //если совсем застряли даём носильщику вторую жизнь

            }
            //проверка на "споткнулись, потерялись, нужна новая цель, до старой точно не дойдём" (переопределение маршрута)
			else if (time > 1.0)
			{
                LAi_tmpl_goto_Complite(chr);
                LAi_tmpl_goto_InitTemplate(chr);
                LAi_type_carrier_GoTo(chr);
                GetCharacterPos(chr, &locx, &locy, &locz);
                chr.checkMove.locx = locx;
                chr.checkMove.locy = locy;
                chr.checkMove.locz = locz;
                chr.checkFalure = sti(chr.checkFalure) + 1;
			}
		}
		if (CheckAttribute(chr, "chr_ai.tmpl.state") && chr.chr_ai.tmpl.state == "stay")
		{
			time = stf(chr.chr_ai.tmpl.wait) + dltTime;
			chr.chr_ai.tmpl.wait = time;
			//проверка на выход из домика. если время еще не подошло или в городе тревога, то сидим не высовываемся
			if (time > 30 + rand(10) && !LAi_grp_alarmactive)
			{
				if(CheckAttribute(chr, "chr_ai.tmpl.baseLocator")) // Warship fix. Могло не быть
					ChangeCharacterAddressGroup(chr, chr.location, "reload", chr.chr_ai.tmpl.baseLocator);
				else
				    ChangeCharacterAddressGroup(chr, chr.location, "reload", LAi_type_carrier_SetPath(chr));

				LAi_tmpl_goto_InitTemplate(chr);
				LAi_type_carrier_GoTo(chr);
			}
		}
		//--> проверяем не врагов, но дерущихся.
		if (stf(chr.chr_ai.type.checkFight) < 0.0)
		{
			int num = FindNearCharacters(chr, 15.0, -1.0, -1.0, 0.001, false, true);
			for(int i = 0; i < num; i++)
			{
				int idx = sti(chrFindNearCharacters[i].index);
				ref by = &Characters[idx];
				chr.chr_ai.type.checkFight = 4.0;
				if (by.chr_ai.tmpl == LAI_TMPL_FIGHT)
				{
					LAi_type_carrier_HideIntoFaultLines(chr);
				}
			}
		}
		else
		{
			chr.chr_ai.type.checkFight = stf(chr.chr_ai.type.checkFight) - dltTime;
		}
		//<-- проверяем не врагов, но дерущихся.
	}
	//не должно быть, но мало ли..
	//говорили предки, а спустя века это "мало ли" стало целевым способом использования носильщиеов... (22.07.2024)
	if(chr.chr_ai.tmpl == LAI_TMPL_STAY)
	{
        chr.checkFalure = sti(chr.checkFalure) + 1;
        //если нас судьба кинула на локатор из которого мы не в состоянии выбраться, то пробуем тогда другой локатор
        if (sti(chr.checkFalure) > 1)
        {
            ChangeCharacterAddressGroup(chr, chr.location, "reload", LAi_type_carrier_SetPath(chr));
            DeleteAttribute(chr, "checkFalure");
        }
        LAi_tmpl_goto_InitTemplate(chr);
        LAi_type_carrier_GoTo(chr);
	}
}

//Загрузка персонажа в локацию
bool LAi_type_carrier_CharacterLogin(aref chr)
{
	return true;
}

//Выгрузка персонажа из локацию
bool LAi_type_carrier_CharacterLogoff(aref chr)
{
	return true;
}

//Завершение работы темплейта
void LAi_type_carrier_TemplateComplite(aref chr, string tmpl)
{

}

//Сообщить о желании завести диалог
void LAi_type_carrier_NeedDialog(aref chr, aref by)
{
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_type_carrier_CanDialog(aref chr, aref by)
{
	return false;
}

//Начать диалог
void LAi_type_carrier_StartDialog(aref chr, aref by)
{

}

//Закончить диалог
void LAi_type_carrier_EndDialog(aref chr, aref by)
{

}

//Персонаж выстрелил
void LAi_type_carrier_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}

//Персонаж атакован
void LAi_type_carrier_Attacked(aref chr, aref by)
{
}

int LAi_type_carrier_FindNearEnemy(aref chr)
{
	if(LAi_grp_alarmactive == true)
	{
		int num = FindNearCharacters(chr, 15.0, -1.0, -1.0, 0.001, false, true);
		if(num <= 0)
		{
			chrFindNearCharacters[0].index = "-1";
			return -1;
		}
		for(int i = 0; i < num; i++)
		{
			int idx = sti(chrFindNearCharacters[i].index);
			if(LAi_group_IsEnemy(chr, &Characters[idx])) return idx;
		}
	}
	return -1;
}

void LAi_type_carrier_GoTo(aref chr)
{
	if (!LAi_grp_alarmactive)
	{
		float locx, locy, locz;
		GetCharacterPos(chr, &locx, &locy, &locz);
		chr.chr_ai.tmpl.wait = 0;
		chr.checkMove.locx = locx;
		chr.checkMove.locy = locy;
		chr.checkMove.locz = locz;
		chr.chr_ai.tmpl.baseLocator = LAi_type_carrier_SetPath(chr);
		LAi_tmpl_goto_InitTemplate(chr);
		LAi_tmpl_goto_SetLocator(chr, "reload", chr.chr_ai.tmpl.baseLocator, -1.0);
	}
}

string LAi_type_carrier_SetPath(aref chr)
{
	//определим маршрут
	string possibleLocators = "";
    aref aReloads;
    int idxloc = FindLoadedLocation();
	string targetLocator = "Prison,Brothel,Residence,PortOffice,Usurer House,Church,Store,Shipyard,Tavern,Plantation,Townhall,Street,Packhouse,MinentownOL";
	if (CheckAttribute(&locations[idxloc], "type") && locations[idxloc].type != "town") targetLocator += ",House,Mines";

    makearef(aReloads, locations[idxloc].reload);
	int iNum = GetAttributesNum(aReloads);

	for (int i = 0; i < iNum; i++)
	{
	    aref aLoc = GetAttributeN(aReloads, i);
	    if (!CheckAttribute(aLoc, "label")) continue; //скипаем локации без названий
	    if (HasStrEx(aLoc.label, targetLocator, "|") && aLoc.name != chr.location.locator)
	    {
	        if (possibleLocators == "") possibleLocators = aLoc.name;
	        else possibleLocators += "," + aLoc.name;
	    }
	}
	return GetRandStr(possibleLocators, ",");
}

//прячем НПС пока он в "домике" что бы никто не увидел
void LAi_type_carrier_HideIntoFaultLines(aref chr)
{
    float locx, locy, locz;
    GetCharacterPos(chr, &locx, &locy, &locz);
    TeleportCharacterToPos(chr, locx-1000.0, locy, locz);
}
