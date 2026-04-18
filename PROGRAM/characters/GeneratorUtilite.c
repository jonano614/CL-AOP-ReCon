
// BOAL методы для генератора НПС

// генерим НПС приблизительного ранга
void SetFantomParamFromRank(ref NPchar, int  rank, bool setEquip)
{
    SetRandSPECIAL(Npchar);
    CalculateSkillsFromRank(Npchar, rank);
    SetFantomHP(NPchar);
    if (setEquip)
    {
	    LAi_NPC_Equip(NPchar, sti(NPchar.rank), true, true);
    }
}


// расчитать скилы заданного ранга, типа как от ГГ в будущем (ранг у НПС будет приблизительно, зависит от сложности)
void CalculateSkillsFromRank(ref NPchar, int  rank)
{
    float  iMiddleK;
    
	// вычислим средний скил к этому рангу
	iMiddleK = 6 + rank*GetCharacterRankRate(GetMainCharacter()) / 14.0;
	
	CalculateAppropriateSkillsParam(Npchar, iMiddleK, 5);
}
// расчёт скилов от среднего скила
void CalculateAppropriateSkillsParam(ref NPchar, float  MiddleK, int _complex)
{
    //trace("CalculateAppropriateSkillsParam " + NPchar.id);
    float  fValue;
    
    fValue = (20 * _complex / 4.0);
    Npchar.skill.FencingLight = makeint(MiddleK + (frandSmall(fValue) + frandSmall((20* _complex / 3.2)) - 24));
    Npchar.skill.Fencing      = makeint(MiddleK + (frandSmall(fValue) + frandSmall((20* _complex / 3.0)) - 20));
    Npchar.skill.FencingHeavy = makeint(MiddleK + (frandSmall(fValue) + frandSmall((20* _complex / 3.5)) - 28));
    Npchar.skill.Pistol       = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Fortune      = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));

    Npchar.skill.Leadership   = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Commerce     = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Sailing      = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Accuracy     = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Cannons      = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Grappling    = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Repair       = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Defence      = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Sneak        = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));

    CorrectSkillParam(Npchar);

    SetRankFromSkill(Npchar);
}
void CalculateAppropriateSkills(ref NPchar)
{
    float   MiddleK;
    bool    ok;
    int     rank, sum;
    string  sTemp = "";
    int rank_bonus = 0;
    int base_rank = 0;
    
    SetRandSPECIAL(Npchar);

	if (CheckAttribute(NPchar, "RankBonus"))
	{
		rank_bonus = sti(NPchar.RankBonus);
		sTemp = "RankBonus: " + rank_bonus;
	}

	if (CheckAttribute(NPchar, "EnemyRank"))
	{
		base_rank = sti(NPchar.EnemyRank);
		sTemp += " EnemyRank: " + base_rank;
	}

	if (sti(Pchar.rank) > base_rank) base_rank = sti(Pchar.rank); //Чтобы в соло сложнее абузить
		
	MiddleK = base_rank;
		
	ok =  (MOD_SKILL_ENEMY_RATE > 5) && (bNewCodeOn);
	if (!ok)
	{
		ok =  (MOD_SKILL_ENEMY_RATE <= 5) && (!bNewCodeOn); // наоборот - есть - сложнее станет
	}
	ok =  (!CheckAttribute(NPchar, "OurMan")) || (ok);

	if (!CheckAttribute(NPchar, "EnemyRank") && ok)// токо Компы и не двойной учет для моря
	{
		MiddleK = MiddleK + (MOD_SKILL_ENEMY_RATE-5) * 1.5;
		sTemp += " ComplexBonus = " + FloatToString((MOD_SKILL_ENEMY_RATE-5) * 1.5, 1);
	}
	rank = MakeInt(MiddleK + frandSmall(4) + frandSmall(4) + frandSmall(4) + frandSmall(4) - 8 + rank_bonus);

	if (rank < 1) rank = 1;
	if (rank > 300) rank = 300;

	NPchar.rank = rank;
	//debug
	if (CheckAttribute(NPchar, "OurMan")) sTemp += " OurNPCRank: " + rank;
	else sTemp += " NPCRank: " + rank;
	if (sTemp != "" && bBettaTestMode) Trace("Fantom_gen: " + sTemp);


	if (rank > (1400 / GetCharacterRankRate(Npchar)))
	{
		SetSelfSkill(Npchar, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX);
		SetShipSkill(Npchar, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX);
		return;
	}
	CalculateSkillsFromRank(Npchar, rank);
}

void SetRankFromSkill(ref Npchar)
{
    Npchar.rank = 1 + makeint( (sti(Npchar.skill.FencingLight) + sti(Npchar.skill.FencingHeavy) + sti(Npchar.skill.Fortune) +
                           sti(Npchar.skill.Pistol) + sti(Npchar.skill.Leadership) + sti(Npchar.skill.Fencing) +
                           sti(Npchar.skill.Sailing) + sti(Npchar.skill.Accuracy) + sti(Npchar.skill.Cannons) +
                           sti(Npchar.skill.Grappling) + sti(Npchar.skill.Repair) + sti(Npchar.skill.Defence) +
                           sti(Npchar.skill.Commerce) + sti(Npchar.skill.Sneak) - 84) / GetCharacterRankRate(Npchar) );
    if (sti(Npchar.rank) < 1)
    {
        Npchar.rank = 1;
    }
}

void CorrectSkillParam(ref Npchar)
{
    int i;
    string  skillName;

    for (i=1; i<15; i++)
    {
        skillName = GetSkillNameByIdx(i);
        if(sti(Npchar.skill.(skillName)) > SKILL_MAX) Npchar.skill.(skillName) = SKILL_MAX;
        if(sti(Npchar.skill.(skillName)) < 1)         Npchar.skill.(skillName) = 1;
    }
}
float GetMiddleMainSkill()
{
    float MiddleK;

    MiddleK = makefloat(GetSkillSum(Pchar) / 14.0) ;

    return  MiddleK;
}
int GetSkillSum(ref Npchar)
{
    int i, sum;
    string  skillName;
    
	sum = 0;
    for (i=1; i<15; i++)
    {
        skillName = GetSkillNameByIdx(i);
        sum += sti(Npchar.skill.(skillName));
    }
    return sum;
}

int GetSPECIALSum(ref Npchar)
{
    int i, sum;
    string  skillName;

	sum = 0;
    for (i=15; i<22; i++)
    {
        skillName = GetSkillNameByIdx(i);
        sum += sti(Npchar.SPECIAL.(skillName));
    }
    return sum;
}
// boal new formula 10.12.03 // очень важная раздача скилов, зависит от сложности <--

void SetFantomParam(ref _pchar)
{
    CalculateAppropriateSkills(_pchar);
    SetFantomHP(_pchar);
    // тут трем накопивщиеся сабли и корабли 290704 BOAL -->
    DeleteAttribute(_pchar, "Items");
    // тут трем накопивщиеся сабли и корабли 290704 BOAL <--
    LAi_NPC_Equip(_pchar, sti(_pchar.rank), true, true);
}

void SetFantomParamEncout(ref _pchar)  // выдача сабель и НР отдельно
{
    CalculateAppropriateSkills(_pchar);
    SetFantomHP(_pchar);
    // тут трем накопивщиеся сабли и корабли 290704 BOAL -->
    DeleteAttribute(_pchar, "Items");
    DeleteAttribute(_pchar, "equip");
    DeleteAttribute(_pchar, "perks.list");
    //LAi_NPC_EquipPerk(_pchar, "fantom");
	//GiveItem2Character(_pchar, "unarmed");
	//EquipCharacterByItem(_pchar, "unarmed");
    // тут трем накопивщиеся сабли и корабли 290704 BOAL <--
}
//крутые парни -->
void SetFantomParamHunter(ref sld)
{
    SetSeaFantomParam(sld, "war");
    LAi_SetHP(sld, LAI_DEFAULT_HP_MAX + sti(sld.chr_ai.hp), LAI_DEFAULT_HP_MAX + sti(sld.chr_ai.hp));
    TakeNItems(sld,"potion2", 2);
}
//крутые парни <--
void SetSeaFantomParam(ref rChr, string type)
{
	if(type == "special")
	{
		// AlexBlade - для кораблекрушнеца ставим прокачку офицера
		SetOfficerParam(rChr, 3); // уклон в навигацию
		return;
	}
	else
	{
		Fantom_SetRandomSkills(rChr, type); // там вызов CalculateAppropriateSkills(_pchar); + бонус от класса корабля
		Fantom_SetRandomMoney(rChr, type);
		Fantom_SetRandomCrewExp(rChr, type);
		DeleteAttribute(rChr, "items");

		LAi_NPC_Equip(rChr, sti(rChr.rank), true, true);
	}
}
/////////////////////////////////////////////////////
// из AIFantom.c
void Fantom_SetRandomSkills(ref rFantom, string sFantomType)
{
	aref aFSkills;
	int iSClass;

	iSClass = GetCharacterShipClass(rFantom);
	makearef(aFSkills, rFantom.Skill);
	CalculateAppropriateSkills(rFantom);
	SetFantomHP(rFantom);

	switch (sFantomType)
	{
		case "trade":
            // умножение на 10 идет внутри метода
            aFSkills.Leadership = Fantom_CalcSkill(rFantom, SKILL_LEADERSHIP,iSClass, 0, 0, 0, 1, 1, 2, 2, 3, 4);
            aFSkills.Accuracy	= Fantom_CalcSkill(rFantom, SKILL_ACCURACY,	iSClass, 0, 0, 0, 1, 1, 2, 3, 4, 5);
			aFSkills.Cannons	= Fantom_CalcSkill(rFantom, SKILL_CANNONS,	iSClass, 0, 0, 0, 1, 1, 2, 3, 4, 5);
			aFSkills.Sailing	= Fantom_CalcSkill(rFantom, SKILL_SAILING,	iSClass, 0, 0, 0, 1, 1, 2, 3, 6, 7);
			aFSkills.Defence	= Fantom_CalcSkill(rFantom, SKILL_DEFENCE,	iSClass, 0, 0, 0, 1, 1, 2, 3, 4, 5);
		break;
		case "war":
            aFSkills.Leadership = Fantom_CalcSkill(rFantom, SKILL_LEADERSHIP,iSClass, 0, 0, 0, 1, 1, 2, 3, 4, 5);
            aFSkills.Accuracy	= Fantom_CalcSkill(rFantom, SKILL_ACCURACY,	iSClass, 0, 0, 0, 1, 2, 3, 4, 6, 7);
			aFSkills.Cannons	= Fantom_CalcSkill(rFantom, SKILL_CANNONS,	iSClass, 0, 0, 0, 1, 2, 3, 4, 7, 8);
			aFSkills.Sailing	= Fantom_CalcSkill(rFantom, SKILL_SAILING,	iSClass, 0, 0, 0, 1, 2, 3, 4, 6, 7);
			aFSkills.Defence	= Fantom_CalcSkill(rFantom, SKILL_DEFENCE,	iSClass, 0, 0, 0, 1, 2, 3, 4, 5, 7);
		break;
		case "pirate":
            aFSkills.Leadership = Fantom_CalcSkill(rFantom, SKILL_LEADERSHIP,iSClass, 0, 0, 0, 1, 1, 2, 3, 4, 4);
            aFSkills.Accuracy	= Fantom_CalcSkill(rFantom, SKILL_ACCURACY,	iSClass, 0, 0, 0, 2, 3, 4, 5, 6, 7);
			aFSkills.Cannons	= Fantom_CalcSkill(rFantom, SKILL_CANNONS,	iSClass, 0, 0, 0, 2, 3, 4, 5, 6, 7);
			aFSkills.Sailing	= Fantom_CalcSkill(rFantom, SKILL_SAILING,	iSClass, 0, 0, 0, 2, 3, 4, 5, 7, 8);
            aFSkills.Defence	= Fantom_CalcSkill(rFantom, SKILL_DEFENCE,	iSClass, 0, 0, 0, 1, 2, 3, 4, 5, 6);
		break;
		// не актуально
//		case "special":
//            aFSkills.Leadership = Fantom_CalcSkill(rFantom, SKILL_LEADERSHIP,iSClass, 0, 0, 0, 1, 1, 2, 3, 4, 4);
//            aFSkills.Accuracy	= Fantom_CalcSkill(rFantom, SKILL_ACCURACY,	iSClass, 0, 0, 0, 2, 3, 4, 5, 6, 7);
//			aFSkills.Cannons	= Fantom_CalcSkill(rFantom, SKILL_CANNONS,	iSClass, 0, 0, 0, 2, 3, 4, 5, 6, 7);
//			aFSkills.Sailing	= Fantom_CalcSkill(rFantom, SKILL_SAILING,	iSClass, 0, 0, 0, 2, 3, 4, 5, 7, 8);
//            aFSkills.Defence	= Fantom_CalcSkill(rFantom, SKILL_DEFENCE,	iSClass, 0, 0, 0, 1, 2, 3, 4, 5, 6);
//		break;
	}

	SetRankFromSkill(rFantom);
}
/////////////////////////////////////////////////////
void SetFantomHP(ref _pchar)
{
	int hp;
	hp = GetCharacterBaseHPValue(_pchar) + (sti(_pchar.rank) * GetCharacterAddHPValue(_pchar));
	LAi_SetHP(_pchar, hp, hp);
	LAi_SetCurHPMax(_pchar);
}

void SetMonsterLoginHP(ref _pchar) // жизнь у монстров больше (рейдеры тоже тут), как и пассажиры - потенциально читовые офицеры!!
{
	int hp;
	if (true)
	{
		int rank = makeint(sti(_pchar.rank) * (1 + MOD_SKILL_ENEMY_RATE / 40.0));
		hp = LAI_DEFAULT_HP_MAX + rank * 5;
		_pchar.rank = rank;
		LAi_SetHP(_pchar, hp, hp);
		LAi_SetCurHPMax(_pchar);
	}
	else
	{
		hp = LAI_DEFAULT_HP_MAX + makeint(sti(_pchar.rank)*(MOD_SKILL_ENEMY_RATE / 2.0 + 5.0)) + 10;
		LAi_SetHP(_pchar, hp, hp);
		LAi_SetCurHPMax(_pchar);
	}
}

/// метод расчёта от опыта солдат, даёт бонус в НР (или пенальти)
bool GetBoardingHP(ref mchr, ref echr, ref float_boarding_player_hp, ref float_boarding_enemy_hp)
{
	float b_p_hp, b_e_hp;
	float moral;
	float exp;
	b_p_hp = LAi_GetCharacterMaxHP(mchr) / 3.0;  // треть от НР кэпа идет в базу бонуса
	
	exp = GetCrewExp(mchr, "Soldiers") / GetCrewExpRate() - 0.7;
	moral = 0;
	if(CheckAttribute(mchr, "ship.crew.morale"))
	{
		moral = (stf(mchr.ship.crew.morale) - MORALE_NORMAL)/(MORALE_MAX - MORALE_MIN);
		if(moral < -0.5) moral = -0.5;
		if(moral > 0.5) moral = 0.5;
	}
	exp = exp + moral;  // может быть минус
	b_p_hp = b_p_hp*exp;
	
	b_e_hp = 0;  // не будем рандом городить рандомом, опыт и ещё скилы кэпа, всё это не зависит от ГГ, а вот ГГ бонус от опыта даем
	/*
	b_e_hp = LAi_GetCharacterMaxHP(echr) / 3.0;
	exp = GetCrewExp(echr, "Soldiers") / GetCrewExpRate();
	moral = 0;
	if(CheckAttribute(echr, "ship.crew.morale"))
	{
		moral = (stf(echr.ship.crew.morale) - MORALE_NORMAL)/(MORALE_MAX - MORALE_MIN);
		if(moral < -0.5) moral = -0.5;
		if(moral > 0.5) moral = 0.5;
	}
	exp = exp + moral;
	b_e_hp = b_e_hp*exp;
	 */
	float_boarding_player_hp   =  b_p_hp;
	float_boarding_enemy_hp    =  b_e_hp;
	
	return true;
}
void AddCharHP(ref _pchar, int _bonus)
{
	int hp = LAi_GetCharacterMaxHP(_pchar) + _bonus;
	if (hp < 1) hp = 1;
	LAi_SetHP(_pchar, hp, hp);
	LAi_SetCurHPMax(_pchar);
}
