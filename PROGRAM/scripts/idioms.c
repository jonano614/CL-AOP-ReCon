string FindDaysString(int idays)
{
    if (!IsInflectedLanguage()) return FindEnglishIdiomsString(idays, "day");
    return FindRussianIdiomsString(idays, "day");
}

string FindMoneyString(int imoney)
{
    if (!IsInflectedLanguage()) return FindEnglishIdiomsString(imoney, "gold");
	return FindRussianIdiomsString(imoney, "gold");
}
// eddy. такой код, наверное, лучше, чем выше на три экрана
string FindQtyString(int _iQty)
{
    if (!IsInflectedLanguage()) return FindEnglishIdiomsString(_iQty, "qty");
    return FindRussianIdiomsString(_iQty, "qty");
}
//eddy. недели
string FindWeekString(int _Week)
{
    if (!IsInflectedLanguage()) return FindEnglishIdiomsString(_Week, "week");
    return FindRussianIdiomsString(_Week, "week");
}
//eddy. месяцы
string FindMonthString(int _Month)
{
    if (!IsInflectedLanguage()) return FindEnglishIdiomsString(_Month, "month");
    return FindRussianIdiomsString(_Month, "month");
}

string GetTextOnShipsQuantity(int iShips)
{
    if (!IsInflectedLanguage()) return FindEnglishIdiomsString(iShips, "ship");
	return FindRussianIdiomsString(iShips, "ship");
}

string GetTextOnSecondShipsQuantity(int iShips)
{
    if (!IsInflectedLanguage()) return FindEnglishIdiomsString(iShips, "ship");
    return FindRussianIdiomsAccString(iShips, "ship");
}

string FindPeoplesString(int iPeoples, string sCase)
{
    if (!IsInflectedLanguage()) return FindEnglishIdiomsString(iPeoples, "people");
	switch(sCase)
	{
		case "No":
			return FindRussianIdiomsString(iPeoples, "people");
		break;

		case "Acc":
			return FindRussianIdiomsAccString(iPeoples, "people");
		break;
	}
	return FindRussianIdiomsString(iPeoples, "people");
}

string FindSlavesString(int iPeoples)
{
    if (!IsInflectedLanguage()) return FindEnglishIdiomsString(iPeoples, "slaves");
    return FindRussianIdiomsString(iPeoples, "slaves");
}

string FindSlavesWithCaseString(int iPeoples, string sCase)
{
    if (!IsInflectedLanguage()) return FindEnglishIdiomsString(iPeoples, "slaves");
	switch(sCase)
	{
		case "No":
			return FindRussianIdiomsString(iPeoples, "slaves");
		break;

		case "Acc":
			return FindRussianIdiomsAccString(iPeoples, "slaves");
		break;
	}
	return FindRussianIdiomsString(iPeoples, "slaves");
}

string FindSailorString(int iPeoples, string sCase)
{
    if (!IsInflectedLanguage()) return FindEnglishIdiomsString(iPeoples, "sailor");
	switch(sCase)
	{
		case "No":
			return FindRussianIdiomsString(iPeoples, "sailor");
		break;

		case "Acc":
			return FindRussianIdiomsAccString(iPeoples, "sailor");
		break;
	}
	return FindRussianIdiomsString(iPeoples, "sailor");
}

string GetTextChestsQuantity(int iChests)
{
    if (!IsInflectedLanguage()) return FindEnglishIdiomsString(iChests, "chest");
	return FindRussianIdiomsString(iChests, "chest");
}

string FindEnglishIdiomsString(int iCount, string sWord)
{
    string sTemp;
	if (iCount == 1) sTemp = XI_ConvertString(sWord + "1");
	else sTemp = XI_ConvertString(sWord + "2");

    sTemp = MakeMoneyShow(iCount, MONEY_SIGN,MONEY_DELIVER) + " " + sTemp;
    return sTemp;
}

string FindRussianIdiomsString(int iCount, string sWord)
{
    string sTemp, sLenTemp;
    sLenTemp = iCount;
    sTemp = XI_ConvertString(sWord + "3");
    int iLen1 = sti(GetSymbol(&sLenTemp, strlen(&sLenTemp) - 1));
    if (iLen1 == 1) sTemp = XI_ConvertString(sWord + "1");              //1,21,31...101... (1)
    if (iLen1 > 1 && iLen1 < 5) sTemp = XI_ConvertString(sWord + "2");  //2,22,32...102... (2,3,4)
    if (iCount >= 10)
    {
        int iLen2 = sti(GetSymbol(&sLenTemp, strlen(&sLenTemp) - 2));
        if (iLen2 == 1) sTemp = XI_ConvertString(sWord + "3"); //11,111,1111... (11,12,13,14,15,16,17,18,19)
    }
    sTemp = MakeMoneyShow(iCount, MONEY_SIGN,MONEY_DELIVER) + " " + sTemp;
    return sTemp;
}

string FindRussianIdiomsAccString(int iCount, string sWord)
{
    string sTemp, sLenTemp;
    sLenTemp = iCount;
    sTemp = XI_ConvertString(sWord + "3");
    int iLen1 = sti(GetSymbol(&sLenTemp, strlen(&sLenTemp) - 1));
    if (iLen1 == 1) sTemp = XI_ConvertString(sWord + "2");              //1,21,31...101... (1)
    sTemp = MakeMoneyShow(iCount, MONEY_SIGN,MONEY_DELIVER) + " " + sTemp;
    return sTemp;
}

string FindPersonalName(string sKey)
{
    return GetConvertStr(sKey, "characters\\PersonalName.txt");
}

bool IsInflectedLanguage()
{
    return LanguageGetLanguage() == "Russian" || LanguageGetLanguage() == "Polish";
}