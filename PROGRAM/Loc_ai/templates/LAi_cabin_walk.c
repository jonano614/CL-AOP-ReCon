
//HardCoffee шаблон хождения офицеров по каюте, испольщует локаторы rld вместо goto

#define LAI_TMPL_CABIN	"cabin"

bool LAi_tmpl_cabin_InitTemplate(aref chr)
{
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "LockFightMode", false);
	CharacterPlayAction(chr, "");
	bool isNew = false;
	if(CheckAttribute(chr, "chr_ai.tmpl"))
	{
		if(chr.chr_ai.tmpl != LAI_TMPL_CABIN) isNew = true;
	}
	else
	{
		isNew = true;
	}
	if(isNew)
	{
		//Новая установка
		DeleteAttribute(chr, "chr_ai.tmpl");
		chr.chr_ai.tmpl = LAI_TMPL_CABIN;
		chr.chr_ai.tmpl.locator = "";
		chr.chr_ai.tmpl.time = 0;
		float maxtime = 1; //rand(5)
		chr.chr_ai.tmpl.maxtime = maxtime;	
		if(rand(3) != 0)
		{
			chr.chr_ai.tmpl.state = "goto";
			if(LAi_IsInitedAI) LAi_tmpl_cabin_go_notime(chr);
		}
		else
		{
			chr.chr_ai.tmpl.state = "stay";
			if(LAi_IsInitedAI) SetCharacterTask_Stay(chr);
		}
	}
	else
	{
		//Востонавление
		if(!CheckAttribute(chr, "chr_ai.tmpl.state")) chr.chr_ai.tmpl.state = "stay";
		if(CheckAttribute(chr, "chr_ai.tmpl.locator"))
		{
			if(chr.chr_ai.tmpl.locator == "") chr.chr_ai.tmpl.state = "stay";
		}
		else
		{
			chr.chr_ai.tmpl.state = "stay";
		}
		if(!CheckAttribute(chr, "chr_ai.tmpl.time")) chr.chr_ai.tmpl.time = 0;
		if(!CheckAttribute(chr, "chr_ai.tmpl.maxtime")) chr.chr_ai.tmpl.maxtime = 1; //1 + rand(10)
		if(chr.chr_ai.tmpl.state == "goto")
		{
			if(LAi_IsInitedAI)
			{
				if(SetCharacterTask_GotoPoint(chr, "rld", chr.chr_ai.tmpl.locator) == false)
				{
					SetCharacterTask_Stay(chr);
					chr.chr_ai.tmpl.state = "stay";
				}
			}
		}
		if(chr.chr_ai.tmpl.state == "stay")
		{
			if(LAi_IsInitedAI) SetCharacterTask_Stay(chr);
			if(chr.chr_ai.tmpl.locator != "")
			{
				CharacterTurnByLoc(chr, "rld", chr.chr_ai.tmpl.locator);
			}
		}
	}
	return true;
}


//Процессирование шаблона персонажа
void LAi_tmpl_cabin_CharacterUpdate(aref chr, float dltTime)
{
	float time, maxtime, randTime;
	int idx;
	aref tmpl;
	float dist;
	makearef(tmpl, chr.chr_ai.tmpl);
	//Смотрим текущее состояние шаблона
	tmpl.time = stf(tmpl.time) + dltTime;
	if (tmpl.state == "stay")
	{
		//Повышаем желание пойти
		time = stf(tmpl.time);
		maxtime = stf(tmpl.maxtime);
		if (time > maxtime)
		{
			//Пора идти
			LAi_tmpl_cabin_go(chr);
		}
		else if (rand(49) == 0) //Смотрим на проходящих
		{
			idx = FindNearCharacters(chr, 10.0, -1.0, -1.0, 0.01, false, true);
			if (idx > MAX_CHARS_IN_LOC || idx < 0) return;
			idx = sti(chrFindNearCharacters[rand(idx)].index);
			if (idx >= 0)
			{
				//Нашли на кого попялиться
				tmpl.state = "look";
				tmpl.state.time = 0;
				tmpl.state.maxtime = 3 + rand(5);
				tmpl.state.randtime = 0.5;
				tmpl.state.index = idx;
				CharacterTurnByChr(chr, &Characters[idx]);
				if (Characters[idx].id != pchar.id)
					CharacterTurnByChr(&Characters[idx], chr);
			}
		}
	}
	else if (tmpl.state == "look")
	{
		tmpl.time = stf(tmpl.time) + dltTime;
		time = stf(tmpl.state.time);
		maxtime = stf(tmpl.state.maxtime);
		idx = sti(tmpl.state.index);
		randTime = stf(tmpl.state.randtime);
		if (GetCharacterDistByChr(chr, &Characters[idx], &dist) == false)
		{
			time = maxtime;
		}
		if (dist > 10.0 || dist < 0.0)
		{
			time = maxtime;
		}
		if (time < maxtime)
		{
			time += dltTime;
			randTime -= dltTime;
			if (randTime < 0.0)
			{
				randTime = 0.5 + frandSmall(1.0);
				CharacterTurnByChr(chr, &Characters[idx]);
			}
			tmpl.state.randtime = randTime;
			tmpl.state.time = time;
		}
		else
		{
			DeleteAttribute(chr, "chr_ai.tmpl.state");
			tmpl.state = "stay";
		}
	}
}

//Персонаж выполнил команду  go to point
void LAi_tmpl_cabin_EndGoToPoint(aref chr)
{
	LAi_tmpl_cabin_endgo(chr);
}

//Персонаж провалил команду  go to point
void LAi_tmpl_cabin_FailureGoToPoint(aref chr)
{
	LAi_tmpl_cabin_endgo(chr);
}


//Персонаж выполнил команду  run to point
void LAi_tmpl_cabin_EndRunToPoint(aref chr)
{
	LAi_tmpl_cabin_endgo(chr);
}

//Персонаж провалил команду  run to point
void LAi_tmpl_cabin_FailureRunToPoint(aref chr)
{
	LAi_tmpl_cabin_endgo(chr);
}

//Персонаж не может добраться до точки назначения
void LAi_tmpl_cabin_BusyPos(aref chr, float x, float y, float z)
{
	LAi_tmpl_cabin_endgo(chr);
	if(chr.chr_ai.tmpl.state == "stay")
	{
		CharacterTurnByPoint(chr, x, y, z);
	}
}

//Персонаж начал перемещение за другим
void LAi_tmpl_cabin_FollowGo(aref chr)
{
	LAi_tmpl_cabin_endgo(chr);
}

//Персонаж начал дошёл до другого персонажа
void LAi_tmpl_cabin_FollowStay(aref chr)
{
	LAi_tmpl_cabin_endgo(chr);
}

//Персонаж провалил команду  follow character
void LAi_tmpl_cabin_FailureFollow(aref chr)
{
	LAi_tmpl_cabin_endgo(chr);
}


//Персонаж начал перемещение за другим
void LAi_tmpl_cabin_FightGo(aref chr)
{
	LAi_tmpl_cabin_endgo(chr);
}

//Персонаж начал дошёл до другого персонажа
void LAi_tmpl_cabin_FightStay(aref chr)
{
	LAi_tmpl_cabin_endgo(chr);
}

//Персонаж провалил команду  Fight
void LAi_tmpl_cabin_FailureFight(aref chr)
{
	LAi_tmpl_cabin_endgo(chr);
}

//Можно ли стрелять
bool LAi_tmpl_cabin_IsFire(aref chr)
{
	return false;
}

//Можно ли использовать оружие
bool LAi_tmpl_cabin_IsFight(aref chr)
{
	return false;
}


//Персонаж выполнил команду  escape
void LAi_tmpl_cabin_EndEscape(aref chr)
{
	LAi_tmpl_cabin_endgo(chr);
}

//Персонаж скользит вдоль патча
void LAi_tmpl_cabin_EscapeSlide(aref chr)
{
	LAi_tmpl_cabin_endgo(chr);
}

//Персонаж провалил команду  escape
void LAi_tmpl_cabin_FailureEscape(aref chr)
{
	LAi_tmpl_cabin_endgo(chr);
}


//Персонаж толкается с другими персонажами
void LAi_tmpl_cabin_ColThreshold(aref chr)
{
	if(chr.chr_ai.tmpl.state == "stay")
	{
		chr.chr_ai.tmpl.time = 0;
		chr.chr_ai.tmpl.maxtime = 5;
		LAi_tmpl_cabin_go_notime(chr);
	}else{
		if(chr.chr_ai.tmpl.state == "look")
		{
			chr.chr_ai.tmpl.time = 0;
			chr.chr_ai.tmpl.maxtime = 5;
			LAi_tmpl_cabin_go_notime(chr);
		}else{
			if(LAi_tmpl_cabin_neareststaycheck(chr))
			{
				LAi_tmpl_cabin_nowstay(chr);
			}else{
				chr.chr_ai.tmpl.time = 0;
				chr.chr_ai.tmpl.maxtime = 8;
				LAi_tmpl_cabin_go_notime(chr);
			}
		}
	}
}


//Персонаж закончил проигрывать анимацию
void LAi_tmpl_cabin_EndAction(aref chr)
{
	LAi_tmpl_cabin_endgo(chr);
}

//Персонажа просят освободить место
void LAi_tmpl_cabin_FreePos(aref chr, aref who)
{
	LAi_tmpl_cabin_go(chr);
}

//------------------------------------------------------------------------------------------
//Внутреннии функции
//------------------------------------------------------------------------------------------

void LAi_tmpl_cabin_go(aref chr)
{
	chr.chr_ai.tmpl.maxtime = 1;  //HardCoffee 8 +50
	chr.chr_ai.tmpl.time = 0;
	LAi_tmpl_cabin_go_notime(chr);
}

void LAi_tmpl_cabin_go_notime(aref chr)
{
	string loc;
	if(rand(3) == 2)
	{
		loc = LAi_FindRandomLocator("rld");
	}
	else
	{
		loc = FindCharacterOptLocator(chr, "rld");
		if(loc == "")
		{
			loc = LAi_FindRandomLocator("rld");
		}
	}
	if(loc == "")
	{
		//Локатора нет, стоим
		chr.chr_ai.tmpl.maxtime = 60;
		chr.chr_ai.tmpl.time = 0;
		chr.chr_ai.tmpl.state = "stay";
		return;
	}
	if(SetCharacterTask_GotoPoint(chr, "rld", loc) == false)
	{
		//Локатора нет, стоим
		chr.chr_ai.tmpl.maxtime = 1;
		chr.chr_ai.tmpl.time = 0;
		chr.chr_ai.tmpl.state = "stay";
		return;
	}
	chr.chr_ai.tmpl.state = "goto";
	chr.chr_ai.tmpl.locator = loc;
}


void LAi_tmpl_cabin_endgo(aref chr)
{
	if(stf(chr.chr_ai.tmpl.time) > stf(chr.chr_ai.tmpl.maxtime))
	{
		//Проверяем ближних стоячих
		if(LAi_tmpl_cabin_neareststaycheck(chr))
		{
			//Останавливаем
			LAi_tmpl_cabin_nowstay(chr);
		}else{
			//Ищем новую цель
			LAi_tmpl_cabin_go_notime(chr);
		}
	}else{
		//Ищем новую цель
		LAi_tmpl_cabin_go_notime(chr);
	}
}

void LAi_tmpl_cabin_nowstay(aref chr)
{
	//Переходим в режим ожидания
	chr.chr_ai.tmpl.time = 0;
	chr.chr_ai.tmpl.maxtime = 10 + rand(30); //5 + rand(30);
	SetCharacterTask_Stay(chr);
	chr.chr_ai.tmpl.state = "stay";
	if(chr.chr_ai.tmpl.locator != "")
	{
		CharacterTurnByLoc(chr, "rld", chr.chr_ai.tmpl.locator);
	}
}

bool LAi_tmpl_cabin_neareststaycheck(aref chr)
{
	int num = FindNearCharacters(chr, 4.0, -1.0, -1.0, 0.01, false, false);
	if(num <= 0) return true;
	int cnt = 0;
	for(int i = 0; i < num; i++)
	{
		int idx = sti(chrFindNearCharacters[i].index);
		if(CharacterGetTask(&Characters[idx]) == "Stay")
		{
			cnt++;
		}
	}	
	if(cnt > 1) return false;
	return true;
}


