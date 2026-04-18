#include "achievements.h"

void Achievment_Set(int achievNum)
{
	if (ACH_Korsary_akhoy == achievNum)
		return; // временно (постоянно?) уберём её

	string achID = GetAchievementId(achievNum);
	if(achID == "") return;

	SetAchievement(achID);
}

string GetAchievementId(int achievNum)
{
	string prefix = "ach_";
    if (achievNum < 0) return "";
    if (achievNum < 10) return prefix + "0" + achievNum;
    else return prefix + achievNum;
}

void Achievment_SetStat(int achievNum, int _add)
{
	string statID = Stat_GetID(achievNum);
	if(statID == "")
	{
		trace("Achievments: No ID for Stat - " + achievNum);
		return;
	}
	int curState = GetStat(statID);
	int maxState = GetMaxState(achievNum);
	if(curState + _add > maxState) SetStat(statID, maxState);
	else SetStat(statID, curState + _add);
	StoreStats();
}

string Stat_GetID(int achievNum)
{
	string prefix = "stat_";
    if (achievNum < 0) return "";
    if (achievNum < 10) return prefix + "0" + achievNum;
    else return prefix + achievNum;
}

int GetMaxState(int StateNum)
{
	int curState = 0;
	switch (StateNum)
	{
		// Ценитель прекрасного : посетить бордель 50 раз
		case ACH_Tsenitel_prekrasnogo:
			curState = 50;
		break;

		// Кладоискатель I : Найти 10 кладов
		case ACH_Kladoiskatel_I:
			curState = 10;
		break;
		// Кладоискатель II : Найти 25 кладов
		case ACH_Kladoiskatel_II:
			curState = 25;
		break;
		// Кладоискатель III : Найти 50 кладов
		case ACH_Kladoiskatel_III:
			curState = 50;
		break;

		// Захватчик I : Захватить абордажем 10 кораблей
		case ACH_Zakhvatchik_I:
			curState = 10;
		break;
		// Захватчик II : Захватить абордажем 25 кораблей
		case ACH_Zakhvatchik_II:
			curState = 25;
		break;
		// Захватчик III : Захватить абордажем 50 кораблей
		case ACH_Zakhvatchik_III:
			curState = 50;
		break;

		// На штурм I : Взять штурмом 5 колоний
		case ACH_Na_shturm_I:
			curState = 5;
		break;
		// На штурм II : Взять штурмом 10 колоний
		case ACH_Na_shturm_II:
			curState = 10;
		break;
		// На штурм III : Взять штурмом 20 колоний
		case ACH_Na_shturm_III:
			curState = 20;
		break;

		// Дарящий смерть I : Убить 500 противников
		case ACH_Daryashchiy_smert_I:
			curState = 500;
		break;
		// Дарящий смерть II : Убить 2000 противников
		case ACH_Daryashchiy_smert_II:
			curState = 2000;
		break;
		// Дарящий смерть III : Убить 5000 противников
		case ACH_Daryashchiy_smert_III:
			curState = 5000;
		break;

		// Жнец таверн I : Нанять в таверне 5 000 человек
		case ACH_Zhnets_tavern_I:
			curState = 5000;
		break;
		// Жнец таверн II : Нанять в таверне 10 000 человек
		case ACH_Zhnets_tavern_II:
			curState = 10000;
		break;
		// Жнец таверн III : Нанять в таверне 20 000 человек
		case ACH_Zhnets_tavern_III:
			curState = 20000;
		break;

		// Потопить (орудиями или абордажем) 100 кораблей
		case ACH_Pustit_ko_dnu_I:
			curState = 100;
		break;
		// Потопить (орудиями или абордажем) 250 кораблей
		case ACH_Pustit_ko_dnu_II:
			curState = 250;
		break;
		// Потопить (орудиями или абордажем) 500 кораблей
		case ACH_Pustit_ko_dnu_III:
			curState = 500;
		break;
	}

	return curState;
}

void CheckAchievments()
{
	// Герой : Получить максимально высокую репутацию
	if(sti(pchar.reputation) >= 81) Achievment_Set(ACH_Geroy);
	// Кровавый убийца : Получить максимально низкую репутацию
	if(sti(pchar.reputation) < 11) Achievment_Set(ACH_Krovavyy_ubiytsa);

	if (!CheckAttribute(&TEV, "BlockMoneyAchievements"))
	{
		// Делец I : сколотить капитал >= 1 000 000
		if(sti(pchar.money) >= 1000000) Achievment_Set(ACH_Delets_I);
		// Делец II : сколотить капитал >= 10 000 000
		if(sti(pchar.money) >= 10000000) Achievment_Set(ACH_Delets_II);
		// Делец III : сколотить капитал >= 25 000 000
		if(sti(pchar.money) >= 25000000) Achievment_Set(ACH_Delets_III);
		// Скрудж : сколотить капитал >= 50 000 000
		if(sti(pchar.money) >= 50000000) Achievment_Set(ACH_Skrudzh);
	}

	if (CheckAttribute(&TEV, "AchievementData.HireTavernCrew"))
	{
		Achievement_AddStats_HireTavernCrew(sti(TEV.AchievementData.HireTavernCrew));
		DeleteAttribute(&TEV, "AchievementData.HireTavernCrew");
	}
}

void CheckAchievments_CheckTuning()
{
	aref aData;
	if (CheckAttribute(&TEV, "AchievementData"))
	{
	    makearef(aData, TEV.AchievementData);
	}

	// Приобрести все доступные улучшения корабля у мастера Алексуса
	if(CheckAttribute(aData, "Tuning.SpeedRate") && CheckAttribute(aData, "Tuning.TurnRate") &&
		CheckAttribute(aData, "Tuning.HP") && CheckAttribute(aData, "Tuning.WindAgainst") &&
		CheckAttribute(aData, "Tuning.Capacity") && CheckAttribute(aData, "Tuning.MaxCrew") &&
		CheckAttribute(aData, "Tuning.Cannon"))
		Achievment_Set(ACH_Korabel);
}

// статы для ачивок
void Achievement_AddStats_Treasure()
{
	Achievment_SetStat(ACH_Kladoiskatel_I, 1);
	Achievment_SetStat(ACH_Kladoiskatel_II, 1);
	Achievment_SetStat(ACH_Kladoiskatel_III, 1);
}

void Achievement_AddStats_AbordShip()
{
	Achievment_SetStat(ACH_Zakhvatchik_I, 1);
	Achievment_SetStat(ACH_Zakhvatchik_II, 1);
	Achievment_SetStat(ACH_Zakhvatchik_III, 1);
}

void Achievement_AddStats_KillShip()
{
	Achievment_SetStat(ACH_Pustit_ko_dnu_I, 1);
	Achievment_SetStat(ACH_Pustit_ko_dnu_II, 1);
	Achievment_SetStat(ACH_Pustit_ko_dnu_III, 1);
}

void Achievement_AddStats_SturmColonies()
{
	Achievment_SetStat(ACH_Na_shturm_I, 1);
	Achievment_SetStat(ACH_Na_shturm_II, 1);
	Achievment_SetStat(ACH_Na_shturm_III, 1);
}

void Achievement_AddStats_KillCharEnemies()
{
	Achievment_SetStat(ACH_Daryashchiy_smert_I, 1);
	Achievment_SetStat(ACH_Daryashchiy_smert_II, 1);
	Achievment_SetStat(ACH_Daryashchiy_smert_III, 1);
}

void Achievement_AddStats_HireTavernCrew(int add)
{
	if (add < 1)
		return;

	Achievment_SetStat(ACH_Zhnets_tavern_I, add);
	Achievment_SetStat(ACH_Zhnets_tavern_II, add);
	Achievment_SetStat(ACH_Zhnets_tavern_III, add);
}