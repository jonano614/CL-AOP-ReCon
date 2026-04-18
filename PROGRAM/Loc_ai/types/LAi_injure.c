/*
Тип: раненый. лежит пока вокруг дерутся. потом встает. на диалоги не отвечает, просто отыдхает.
*/

#define LAI_TYPE_INJURE		"injure"

//Инициализация
void LAi_type_injure_Init(aref chr)
{
    CharacterPlayAction(chr, "");
	DeleteAttribute(chr, "chr_ai.poison"); //лечим отраву
    if (chr.chr_ai.type != LAI_TYPE_INJURE)
    {
        aref arBack, arType;
        //сохранение ИИ
        makearef(arBack, chr.chr_ai_back);
        makearef(arType, chr.chr_ai);
        CopyAttributes(arBack, arType);
        //сохранение анимаций
        makearef(arBack, chr.actions_back);
        makearef(arType, chr.actions);
        CopyAttributes(arBack, arType);
        chr.chr_ai.type = LAI_DEFAULT_TYPE;
        DeleteAttribute(chr, "chr_ai.type");
        LAi_group_MoveCharacter(chr, LAI_GROUP_ACTOR); //переводим НПС в нейтральную группу. лежачих бить плохо
        chr.chr_ai.type.time = 0;
        SetCharacterTask_Stay(chr);
        DeleteAttribute(chr, "chr_ai.tmpl");
        chr.chr_ai.tmpl = LAI_TMPL_STAY;
        chr.chr_ai.type.death_ani = 5;
        chr.chr_ai.type = LAI_TYPE_INJURE;
        CharacterPlayAction(chr, "death_2");  //анимация умирания только эта хорошо сочитается с последующим лежанием на животике
	    LAi_SetImmortal(chr, true); //что бы не затоптали лежачего
		string notifyType = "none";
		if (CheckAttribute(chr, "faceId"))
		{
		    notifyType = "face_"+chr.faceId;
		}
	    Notification(StringFromKey("InfoMessages_131", GetFullName(chr)), notifyType); // оповещение - чар без сознания
    }
    else
    {
        LAi_SetDefaultLayAnimation(chr);
        DeleteAttribute(chr, "chr_ai.type.death_ani");
    }
	SetCharacterTask_Stay(chr); //принудительно стоять на месте

	SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "IsIntangible", true); //уменьшаем жопу лежащего нпс
	IgnoreCollision(chr, true); //убираем коллизии что бы не спотыкались о жопу лежащего
}

bool LAi_check_possible_standUp(aref chr)
{
    int num = FindNearCharacters(chr, 200.0, -1.0, -1.0, 0.001, false, true);
    int idx, i;
    if (num > 0)
    {
        for (i = 0; i < num; i++)
        {
            idx = sti(chrFindNearCharacters[i].index);
            if (LAi_group_IsEnemy(pchar, &characters[idx]))
            {
                return false;
            }
        }
    }
    return true;
}

//Процессирование типа персонажа
void LAi_type_injure_CharacterUpdate(aref chr, float dltTime)
{
    //падаем и лежим бревном
    if (CheckAttribute(chr, "chr_ai.type.death_ani"))
    {
        if (chr.sex == "man")
        {
            if (sti(chr.chr_ai.type.death_ani) < 30)
            {
                chr.chr_ai.type.death_ani = sti(chr.chr_ai.type.death_ani) + 1;
            }
            else
            {
                CharacterPlayAction(chr, "");
                LAi_SetDefaultLayAnimation(chr);
                DeleteAttribute(chr, "chr_ai.type.death_ani");
            }
        }
        else
        {
            if (sti(chr.chr_ai.type.death_ani) < 25)
            {
                chr.chr_ai.type.death_ani = sti(chr.chr_ai.type.death_ani) + 1;
            }
            else
            {
                CharacterPlayAction(chr, "");
                LAi_SetDefaultLayAnimation(chr);
                DeleteAttribute(chr, "chr_ai.type.death_ani");
            }
        }
    }
    else
    {
        //проверка пора ли вставать. если никого рядом нет с ГГ и НПС из врагов, то надо подниматься
        bool bStandUp = false;
        if (!CheckAttribute(chr, "chr_ai.type.getup_ani"))
        {
            bStandUp = LAi_check_possible_standUp(pchar);
            if (!bStandUp) bStandUp = LAi_check_possible_standUp(chr);
        }
		else bStandUp = true;
        if (bStandUp)
        {
            if (CheckAttribute(chr, "chr_ai.type.getup_ani"))
            {
                chr.chr_ai.type.getup_ani = sti(chr.chr_ai.type.getup_ani) + 1;
                if (sti(chr.chr_ai.type.getup_ani) > 30)
                {
                    CharacterPlayAction(chr, "");
                    aref arBack, arType;

                    //возвращение ИИ
                    chr.chr_ai.type = LAI_DEFAULT_TYPE;
                    makearef(arBack, chr.chr_ai_back);
                    makearef(arType, chr.chr_ai);
                    CopyAttributes(arType, arBack);

                    //возвращение анимации
                    makearef(arBack, chr.actions_back);
                    makearef(arType, chr.actions);
                    CopyAttributes(arType, arBack);
                    EndChangeCharacterActions(chr);

                    //чистка
                    DeleteAttribute(chr, "chr_ai_back");
                    DeleteAttribute(chr, "actions_back");

                    //возвращение изначальной группы
                    LAi_group_MoveCharacter(chr, chr.chr_ai.group);

                    //возвращение задачи (возможно потом понадобится свич, что бы разные задачи были, пока так)
                    SetCharacterTask_FollowCharacter(chr, pchar);
                }
            }
            else
            {
                chr.chr_ai.type.getup_ani = 1;

                //возвращение материальности телу персонажа
                SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "IsIntangible", false);
                LAi_SetImmortal(chr, false);
				IgnoreCollision(chr, false);

                if (chr.model.animation == "man") //у женщин и мушкетеров анимаций вставания нет, так что встает только у мужчин
                {
                    CharacterPlayAction(chr, "");
                    CharacterPlayAction(chr, "Ground_StandUp");
                }
            }
        }

    }
}

//Загрузка персонажа в локацию
bool LAi_type_injure_CharacterLogin(aref chr)
{
	return true;
}

//Выгрузка персонажа из локации
bool LAi_type_injure_CharacterLogoff(aref chr)
{
	return true;
}

//Завершение работы темплейта
void LAi_type_injure_TemplateComplite(aref chr, string tmpl)
{
}

//Сообщить о желании завести диалог
void LAi_type_injure_NeedDialog(aref chr, aref by)
{
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_type_injure_CanDialog(aref chr, aref by)
{
	return false;
}

//Начать диалог
void LAi_type_injure_StartDialog(aref chr, aref by)
{
}

//Закончить диалог
void LAi_type_injure_EndDialog(aref chr, aref by)
{
}


//Персонаж выстрелил
void LAi_type_injure_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}


//Персонаж атакован
void LAi_type_injure_Attacked(aref chr, aref by)
{
}

