//======================================================================================================================
//                      функции для взаимодействия с массивами
//======================================================================================================================

//слияние массивов. к массиву 1 добавляется массив 2
void ArrayAddAll(ref array_1, ref array_2)
{
    string newValue;
    int i;
    if (ArrayIsEmpty(array_1))
    {
        if (!ArrayIsEmpty(array_2)) //если оба массива пустые то можно ничего не делать
        {
            int arraySize = GetArraySize(array_2);
            SetArraySize(array_1, arraySize);
            for (i = 0; i < arraySize; i++)
            {
                newValue = array_2[i];
                array_1[i] = newValue;
            }
        }
    }
    else
    {
        if (!ArrayIsEmpty(array_2)) //если второй массив пустой, то можно ничего не делать
        {
            int arraySize_1 = GetArraySize(array_1);
            int arraySize_2 = GetArraySize(array_2);
            int newArraySize = arraySize_1 + arraySize_2;
            SetArraySize(array_1, newArraySize);
            int j = 0;
            for (i = 0; i < newArraySize; i++)
            {
                if (i >= arraySize_1)
                {
                    newValue = array_2[j];
                    array_1[i] = newValue;
                    j++;
                }
            }
        }
    }
}

//добавление значения в массив с увеличением размера
void ArrayAddValue(ref array, string value)
{
    if (ArrayIsEmpty(array))
    {
        array[0] = value;
    }
    else
    {
        int newArraySize = GetArraySize(array) + 1;
        SetArraySize(array, newArraySize);
        array[newArraySize-1] = value;
    }
}
//получение случайного значения с удалением и уменьшением размера массива
//если массив пустой возвращается пустая строка
string ArrayCutRandomValue(ref array)
{
    string result = ArrayGetRandomValue(array);
    if (result != "") ArrayRemoveValue(array, result);
    return result;
}

//получение случайного значения из найденных по неполному соответвтвию
//если значение не найдено, то возвращается пустая строка
string ArrayFindRandomValue(ref array, string value)
{
    string result = "";
    if (ArrayIsEmpty(array)) return result;
    string sTemp;
    string temp[2]; //если создать массив [1] то оно считается просто стрингой, а не массивом.

    int arraySize = GetArraySize(array);

    for (int i = 0; i < arraySize; i++)
    {
        if (HasStr(array[i], value))
        {
            sTemp = array[i];
            ArrayAddValue(&temp, sTemp);
        }
    }
    if (ArrayIsEmpty(&temp)) return result;
    result = array[rand(GetArraySize(&temp) - 1)];
    return result;
}

//получение случайного значения из найденных по строковому списку
//если значение не найдено, то возвращается -1
int ArrayFindRandomIndex(ref array, string value)
{
    int result = -1;
    if (ArrayIsEmpty(array)) return result;
    string sTemp;
    string temp[2]; //если создать массив [1] то оно считается просто стрингой, а не массивом.

    int arraySize = GetArraySize(array);

    for (int i = 0; i < arraySize; i++)
    {
        sTemp = array[i];
        if (HasStrEx(sTemp, value, "|"))
		{
            ArrayAddValue(&temp, i);
		}
    }

    if (ArrayIsEmpty(&temp)) return result;
    result = sti(temp[rand(GetArraySize(&temp) - 1)]);
    return result;
}

//получение случайного значения из массива
//если значение не найдено, то возвращается пустая строка
string ArrayGetRandomValue(ref array)
{
    string result = "";
    if (ArrayIsEmpty(array)) return result;
    result = array[rand(GetArraySize(array) - 1)];
    return result;
}

//проверка содержет ли массив переданное значение
bool ArrayIsContainValue(ref array, string value)
{
    if (ArrayIsEmpty(array)) return false;
    int arraySize = GetArraySize(array);

    for (int i = 0; i < arraySize; i++)
    {
        if (HasStr(array[i], value)) return true;
    }
    return false;
}

//поиск в массиве значения по жесткому соответствию
bool ArrayIsEqualValue(ref array, string value)
{
    if (ArrayIsEmpty(array)) return false;
    int arraySize = GetArraySize(array);

    for (int i = 0; i < arraySize; i++)
    {
        if (array[i] == value) return true;
    }
    return false;
}

//определение пустой ли массив
bool ArrayIsEmpty(ref array)
{
    int arraySize = GetArraySize(array);
    //массива с размером равным 0 быть не может, потому проверяем на пустоту значения.
    if (arraySize == 1)
    {
        if (array[0] == "") return true;
    }
    //это условие нужно для удобства работы с массивами когда надо заполнить его с нуля.
    //т.к. создать новый массив в скриптах можно только с размером 2 и больше, если указать размер 1, то оно считается просто строкой
    if (arraySize == 2)
    {
        if (array[0] == "" && array[1] == "")
        {
            ArrayClear(array);
            return true;
        }
    }
    return false;
}

//очистка массива
void ArrayClear(ref array)
{
    SetArraySize(array, 1);
    array[0] = "";
}

//удаление значения из массива с уменьшением размера
void ArrayRemoveValue(ref array, string value)
{
    if (ArrayIsEmpty(array)) return;
    int arraySize = GetArraySize(array);

    bool bSort = false;
    string newValue;
    for (int i = 0; i < arraySize; i++)
    {
        if (array[i] == value) bSort = true;
        if (bSort && i != arraySize - 1)
        {
            newValue = array[i+1];
            array[i] = newValue;
        }
    }
    if (arraySize == 1) array[0] = "";
    else SetArraySize(array, arraySize - 1);
}

//удаление значения из массива по индексу с уменьшением размера
void ArrayRemoveValueByIndex(ref array, int index)
{
    if (ArrayIsEmpty(array)) return;
    int arraySize = GetArraySize(array);

    string newValue;
    for (int i = index; i < arraySize; i++)
    {
        if (i != arraySize - 1)
        {
            newValue = array[i+1];
            array[i] = newValue;
        }
    }
    if (arraySize == 1) array[0] = "";
    else SetArraySize(array, arraySize - 1);
}