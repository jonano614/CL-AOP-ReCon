/*
Тип: обезьяна, если обычная, то ходит и убегает при приближении,
	 если обезьяна-мертвяк, то нападает

	Используемые шаблоны:
		walk
		fight
		afraid

*/

#define LAI_TYPE_MONKEY		"monkey"

//Инициализация
void LAi_type_monkey_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
    chr.sex = "monkey";
	chr.chr_ai.type = LAI_TYPE_MONKEY;
	LAi_tmpl_walk_InitTemplate(chr);

	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", true);
}

//Процессирование типа персонажа
void LAi_type_monkey_CharacterUpdate(aref chr, float dltTime)
{
	if (LAi_IsDead(chr)) return;
    if (chr.model == "monkey")
    {
        int trg = -1;
        if(chr.chr_ai.tmpl == LAI_TMPL_FIGHT)
        {
            //Воюем
            bool isValidate = false;
            trg = LAi_tmpl_fight_GetTarget(chr);
            if(trg >= 0)
            {
                if(LAi_group_ValidateTarget(chr, &Characters[trg]))
                {
                    if(!LAi_tmpl_fight_LostTarget(chr))
                    {
                        isValidate = true;
                    }
                }
            }
            if(!isValidate)
            {
                //Ищем новую цель
                trg = LAi_group_GetTarget(chr);
                if(trg < 0)
                {
                    //Переходим в режим ожидания
                    LAi_type_monkey_Return(chr);
                }else{
                    //Натравливаем на новую цель
                    LAi_tmpl_SetFight(chr, &Characters[trg]);
                    if(rand(100) < 50)
                    {
                        PlaySpeech(chr, "MonkeyScream");
                    }
                }
            }else{
                if(rand(4000) == 1224)
                {
                    PlaySpeech(chr, "MonkeyScream");
                }
            }
        }
        else
        {
            //Ищем новую цель
            trg = LAi_group_GetTarget(chr);
            if(trg >= 0)
            {
                //Нападаем на новую цель
                LAi_tmpl_SetFight(chr, &Characters[trg]);
                if(rand(100) < 90)
                {
                    PlaySpeech(chr, "MonkeyScream");
                }
            }
        }
    }
    else
    {
        int num = FindNearCharacters(chr, 10, -1.0, -1.0, 0.001, true, true);
        //бояться некого, гуляем
        if (num <= 0 && chr.chr_ai.tmpl == LAI_TMPL_AFRAID)
        {
            LAi_tmpl_walk_InitTemplate(chr);
        }
        //убегаем от противных
        else
        {
            if (chr.chr_ai.tmpl == LAI_TYPE_ACTOR) return; //убегаем в закат, думать уже поздно
            if (chr.chr_ai.tmpl == LAI_TMPL_AFRAID) return; //уже боимся, нужна стабилизация
            for (int i = 0; i < num; i++)
            {
                int idx = sti(chrFindNearCharacters[i].index);
                ref byChr = &characters[idx];
                //от своих не убегаем
                if (chr.chr_ai.group != byChr.chr_ai.group)
                {
                    float locx, locy, locz;
                    GetCharacterPos(byChr, &locx, &locy, &locz);
                    if (IsEntity(loadedLocation) == true)
                    {
                        string at = "locators.reload";
                        if (CheckAttribute(loadedLocation, at))
                        {
                            aref grp;
                            makearef(grp, loadedLocation.(at));
                            int iNum = GetAttributesNum(grp);
                            int j = -1;
                            float dist = -1;
                            for (int k = 0; k < iNum; k++)
                            {
                                aref loc = GetAttributeN(grp, k);
                                float dx = locx - stf(loc.x);
                                float dy = locy - stf(loc.y);
                                float dz = locz - stf(loc.z);
                                float d = dx*dx + dy*dy + dz*dz;
                                if (j >= 0)
                                {
                                    if (d >= dist)
                                    {
                                        dist = d;
                                        j = k;
                                    }
                                }
                                else
                                {
                                    j = k;
                                    dist = d;
                                }
                            }
                            //локация слишком мала для убегашек, надо сваливать в закат
                            if (dist < 600.0)
                            {
                                LAi_SetActorType(chr);
                                LAi_ActorGoToLocation(chr, "reload", GetAttributeName(GetAttributeN(grp, j)), "none", "", "", "", 15.0);
                                PlaySpeech(chr, "MonkeyScream");
                                break;
                            }
                        }
                    }
                    //если лока большая то "боимся"
                    PlaySpeech(chr, "MonkeyScream");
                    LAi_tmpl_afraid_SetAfraidCharacter(chr, byChr, true);
                    break;
                }
            }
        }
    }
}

//Загрузка персонажа в локацию
bool LAi_type_monkey_CharacterLogin(aref chr)
{
	return true;
}

//Выгрузка персонажа из локацию
bool LAi_type_monkey_CharacterLogoff(aref chr)
{
	return true;
}

//Завершение работы темплейта
void LAi_type_monkey_TemplateComplite(aref chr, string tmpl)
{
	if (tmpl == "goto")
	{
		LAi_tmpl_stay_InitTemplate(chr);
		if (CheckAttribute(chr, "location.group"))
		{
			if( CheckAttribute(chr, "location.locator"))
			{
				CharacterTurnByLoc(chr, chr.location.group, chr.location.locator);
			}
		}
	}
}

//Сообщить о желании завести диалог
void LAi_type_monkey_NeedDialog(aref chr, aref by)
{
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_type_monkey_CanDialog(aref chr, aref by)
{
	return false;
}

//Начать диалог
void LAi_type_monkey_StartDialog(aref chr, aref by)
{
}

//Закончить диалог
void LAi_type_monkey_EndDialog(aref chr, aref by)
{
}

//Персонаж атаковал другого персонажа
void LAi_type_monkey_Attack(aref attack, aref enemy, float attackDmg, float hitDmg)
{
	if(rand(1000) < 100)
	{
		//Отравляем персонажа
		MakePoisonAttack(attack, enemy);
	}
}

//Персонаж атоковал заблокировавшегося персонажа
void LAi_type_monkey_Block(aref attack, aref enemy, float attackDmg, float hitDmg)
{
}

//Персонаж выстрелил
void LAi_type_monkey_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}


//Персонаж атакован
void LAi_type_monkey_Attacked(aref chr, aref by)
{
    LAi_type_monkey_GoAway(chr);
}

void LAi_type_monkey_Return(aref chr)
{
	bool isSet = false;
	if(CheckAttribute(chr, "location.group"))
	{
		if(CheckAttribute(chr, "location.locator"))
		{
			isSet = true;
			CharacterTurnByLoc(chr, chr.location.group, chr.location.locator);
		}
	}
	if (isSet)
	{
		LAi_tmpl_goto_InitTemplate(chr);
		LAi_tmpl_goto_SetLocator(chr, chr.location.group, chr.location.locator, -1.0);
	}
	else
	{
		LAi_tmpl_stay_InitTemplate(chr);
	}
}

//напали на мирных обезьян, все в кусты!
void LAi_type_monkey_GoAway(aref chr)
{
    if (chr.model == "koata1")
    {
        string loc;
        float locx, locy, locz;
        int num = FindNearCharacters(chr, 200, -1.0, -1.0, 0.001, false, true);
        for (int i = 0; i < num; i++)
        {
            int idx = sti(chrFindNearCharacters[i].index);
            ref rMonkey = &characters[idx];
            GetCharacterPos(rMonkey, &locx, &locy, &locz);
            loc = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
            if (rMonkey.model == "koata1")
            {
                LAi_SetActorType(rMonkey);
                LAi_ActorRunToLocation(rMonkey, "reload", loc, "none", "", "", "", 15.0);
                PlaySpeech(rMonkey, "MonkeyScream");
            }
        }
        if (stf(chr.chr_ai.hp) > 1.0)
        {
            GetCharacterPos(chr, &locx, &locy, &locz);
            loc = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
            LAi_SetActorType(chr);
            LAi_ActorRunToLocation(chr, "reload", loc, "none", "", "", "", 15.0);
            PlaySpeech(chr, "MonkeyScream");
        }
    }
}