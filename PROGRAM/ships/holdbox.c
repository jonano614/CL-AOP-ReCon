int CheckHoldBox()
{
	aref itemsARef;
	ref locRef = &locations[FindLocation("My_Deck")];
	int result = 0;

	if (CheckAttribute(locRef, "box1"))
	{
		if (CheckAttribute(locRef, "box1.items"))
		{
			makearef(itemsARef, locRef.box1.items);

			if (GetAttributesNum(itemsARef) > 0)
				result += 1;
		}

		if (CheckAttribute(locRef, "box1.money"))
		{
			if (sti(locRef.box1.money) <= 0) // а вдруг?
				locRef.box1.money = 0;
			else
				result += 2;
		}
	}
	return result;
}

int InternalTakeMoneyFromHoldBox(ref holdBoxRef)	// lets imaging it is private method
{
	int money = sti(holdBoxRef.box1.money);
	holdBoxRef.box1.money = 0;
	return money;
}

int TakeMoneyFromHoldBox()
{
	ref holdBoxRef = &locations[FindLocation("My_Deck")];
	return InternalTakeMoneyFromHoldBox(holdBoxRef);
}

int TakeMoneyFromHoldBoxAndClearContents()
{
	ref holdBoxRef = &locations[FindLocation("My_Deck")];
	int money = InternalTakeMoneyFromHoldBox(holdBoxRef);
	DeleteAttribute(holdBoxRef, "box1.items");
	holdBoxRef.box1.items = "";
	return money;
}