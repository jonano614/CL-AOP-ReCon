// README -->
// Rosarak. Пофиксил безобразие с пропажей слухов. Надо следить за каждым числом в каждой строчке!
// Длина стека слухов (55): уникальные + одноразовые + для нищих + небольшой резерв под AddRumorR
// Резерв из пустых элементов нужен, чтобы не исчезали слухи из конца массива при добавлении новых
// <-- README

#define MAX_RUMOURS 55
#include "scripts\Rumour_templates.c"
#include "scripts\Rumour_func.c"
#include "scripts\Rumour_generate.c"
#include "scripts\Rumour_Data.h"
#include "scripts\GoldFleet.c"

object Rumour[MAX_RUMOURS]; // стек слухов

int id_counter;

void SetRumourDefaults() // заполняем стек начальными - простыми слухами
{
	int i;
	ref CurrentRumour;
	id_counter = 3;
	
	// Rosarak. Уникальные в начало, требующие атрибуты/функции тоже лучше сюда
	// Если хотим использовать атрибут NPC, то нужно пометить слух "special"
	// и по значению атрибута подбирать текст в функциях SelectRumour/Ex/ExSpecial
	
	// УНИКАЛЬНЫЕ
	// Дуглас
	makeref(CurrentRumour, Rumour[0]);
	CurrentRumour.id = 0; // Обязан быть числом!
	CurrentRumour.text = StringFromKey("Common_rumours_154");
	CurrentRumour.state = "1";
	CurrentRumour.tip = "citizen";
	CurrentRumour.City = "PortSpein";
	CurrentRumour.rep = "none";
	CurrentRumour.starttime = (DateToInt(0));
	CurrentRumour.actualtime = (DateToInt(500));
	CurrentRumour.event = "none";
	CurrentRumour.next = "none";
	
	// Аскольд
	makeref(CurrentRumour, Rumour[1]);
	CurrentRumour.id = 1;
	CurrentRumour.text = "TEXT"; //Добавим в самой функции, пустым оставлять нельзя, чтобы не считался просроченым.
	CurrentRumour.special = "Ascold";
	CurrentRumour.state = "3";
	CurrentRumour.tip = "citizen";
	CurrentRumour.rep = "none";
	CurrentRumour.starttime = (DateToInt(0));
	CurrentRumour.actualtime = (DateToInt(100));
	CurrentRumour.event = "none";
	CurrentRumour.next = "none";
	
	// Работорговец
	makeref(CurrentRumour, Rumour[2]);
	CurrentRumour.id = 2;
	CurrentRumour.text = "TEXT"; //Добавим в самой функции, пустым оставлять нельзя
	CurrentRumour.special = "Slavetrader";
	CurrentRumour.state = "3";
	CurrentRumour.tip = "citizen";
	CurrentRumour.rep = "none";
	CurrentRumour.starttime = (DateToInt(0));
	CurrentRumour.actualtime = (DateToInt(100));
	CurrentRumour.event = "none";
	CurrentRumour.next = "none";
	
	// СТАРТОВЫЕ ОДНОРАЗОВЫЕ
	for(i = 3; i < 34; i++)
	{
		makeref(CurrentRumour, Rumour[i]);
		CurrentRumour.id = id_counter;  // ID слуха
		CurrentRumour.text = DefaultText(i-3);// Подгружаем начальные слухи в очередь
		CurrentRumour.state = "1"; // Сколько раз может повторяться один и тот же слух
		CurrentRumour.tip = "citizen,capitan"; // типаж
		CurrentRumour.rep = "none"; // репутация
		CurrentRumour.starttime = (DateToInt(0));// через сколько дней активировать слух
		CurrentRumour.actualtime = (DateToInt(40));// Как долго могут ходить слухи = 40 дней
		CurrentRumour.event = "none"; // Действие - нет
		CurrentRumour.next = "none"; // Продолжение - нет
		id_counter++; // счетчик слухов
		
		//Раздаём группы (см. Rumour_Data.h)
		if(i < 5)  {CurrentRumour.group = "siege_group"; continue;}
		if(i < 11) {CurrentRumour.group = "xebek_group"; continue;}
		if(i < 14) {CurrentRumour.group = "sharp_group"; continue;}
		if(i < 16) CurrentRumour.group = "aztec_group";
	}
	
	// НИЩИЕ
	for(i = 34; i < 44; i++)
	{
		makeref(CurrentRumour, Rumour[i]);
		CurrentRumour.id = id_counter;  // ID слуха
		CurrentRumour.text = PoorRumourText(i-34);// Подгружаем начальные слухи в очередь
		CurrentRumour.state = "5"; // Сколько раз может повторяться один и тот же слух
		CurrentRumour.tip = "poor"; // типаж
		CurrentRumour.rep = "none"; // репутация
		CurrentRumour.starttime = (DateToInt(0));// через сколько дней активировать слух
		CurrentRumour.actualtime = (DateToInt(300));// Как долго могут ходить слухи = 300 дней
		CurrentRumour.event = "none"; // Действие - нет
		CurrentRumour.next = "none"; // Продолжение - нет
		id_counter++; // счетчик слухов
	}
	
	// ПУСТЫЕ ЯЧЕЙКИ
	for(i = 44; i < 55; i++)
	{
		makeref(CurrentRumour, Rumour[i]);
		CurrentRumour.id = "";
		CurrentRumour.text = "";
		CurrentRumour.state = "";
		CurrentRumour.tip = "";
		CurrentRumour.rep = "";
		CurrentRumour.starttime = "";
		CurrentRumour.actualtime = "";
		CurrentRumour.event = "none";
		CurrentRumour.next = "none";
	}
}

void RumourInit()
{
	//Log_SetStringToLog("Слухи!");
	trace("RumourInit!");
	TemplateLoad();
	SetRumourDefaults();
	// ==> отметка времени для осад homo 05/11/06
	SaveCurrentQuestDateParam("Siege_DailyUpdate");
}
