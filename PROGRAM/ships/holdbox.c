#include "interface\itemstrade.c"

int CheckHoldBox()
{
	aref itemsARef;
	ref holdBoxRef = &Locations[FindLocation("My_Deck")];
	int result = 0;

	if (CheckAttribute(holdBoxRef, "box1"))
	{
		if (CheckAttribute(holdBoxRef, "box1.items"))
		{
			makearef(itemsARef, holdBoxRef.box1.items);

			if (GetAttributesNum(itemsARef) > 0)
				result += 1;
		}

		if (CheckAttribute(holdBoxRef, "box1.money"))
		{
			if (sti(holdBoxRef.box1.money) <= 0) // а вдруг?
				holdBoxRef.box1.money = 0;
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
	ref holdBoxRef = &Locations[FindLocation("My_Deck")];
	return InternalTakeMoneyFromHoldBox(holdBoxRef);
}

int TakeMoneyFromHoldBoxAndClearContents()
{
	ref holdBoxRef = &Locations[FindLocation("My_Deck")];
	int money = InternalTakeMoneyFromHoldBox(holdBoxRef);
	DeleteAttribute(holdBoxRef, "box1.items");
	holdBoxRef.box1.items = "";
	return money;
}

int SellItemsFromHoldBox(ref traderChar)
{
	ref holdBoxRef = &Locations[FindLocation("My_Deck")];
	int traderMoney = sti(traderChar.money);
	object notSoldItems;
	int totalIncome = 0;
	int tradeQuantity = 0;

	TraceBox(holdBoxRef);

	aref arItems;
	makearef(arItems, holdBoxRef.box1.items);
	int itemsCount = GetAttributesNum(arItems);

	for (int i = 0; i < itemsCount; i++)
	{
		aref itemRef = GetAttributeN(arItems, i);
		string itemId = GetAttributeName(itemRef);
		int itemQuantity = makeint(GetAttributeValue(itemRef));

		ref item = ItemsFromID(itemId);
		int itemPrice = GetTradeItemPrice(item, PRICE_TYPE_SELL);

		int itemsToSell = CountItemToSell(traderMoney, itemPrice, itemQuantity);
		if(itemsToSell < itemQuantity)
		{
			notSoldItems.(itemId) = itemQuantity - itemsToSell;
		}
		if(itemsToSell > 0)
		{
			TakeNItems(traderChar, itemId, itemsToSell);
			int income = itemsToSell * itemPrice;
			traderMoney -= income;
			tradeQuantity += itemsToSell;
			totalIncome += income;

			Trace("Sold Item " + itemId + "  quantity = " + itemsToSell + " for " + income);
		}

		if(traderMoney <= 0)
		{
			traderMoney = 0;
			break;	// trader has no more money
		}
	}

	DeleteAttribute(holdBoxRef, "box1.items");
	holdBoxRef.box1.items = "";
	aref itemsRef;
	makearef(itemsRef, holdBoxRef.box1.items);
	CopyAttributes(itemsRef, &notSoldItems);

	Pchar.money = sti(Pchar.money) + totalIncome;
	traderChar.money = traderMoney;

	Trace("Total selled " + tradeQuantity + " items for " + totalIncome);
	TraceBox(holdBoxRef);

	if(totalIncome > 0)
	{
		AddCharacterExpToSkill(Pchar, SKILL_COMMERCE, totalIncome / SELL_ITEM_EXP_MODIFIER);
		Statistic_AddValue(Pchar, "Money_get", totalIncome);
		WaitTimeAfterTrade(tradeQuantity, Pchar);
	}

	return totalIncome;
}

int CountItemToSell(int traderMoney, int itemPrice, int itemQuantity)
{
    if(itemPrice * itemQuantity <= traderMoney)
	{
		return itemQuantity;
	}
	else
	{
		return traderMoney / itemPrice;
	}
}

void TraceBox(ref holdBoxRef)
{
	aref arItems;

	makearef(arItems, holdBoxRef.box1.items);
	int itemsCount = GetAttributesNum(arItems);
	Trace("Box has " + itemsCount + " items:");

	for (int i = 0; i < itemsCount; i++)
	{
		aref itemRef = GetAttributeN(arItems, i);
		string itemId = GetAttributeName(itemRef);
		string localizedName = GetItemName(itemId);

		ref item = ItemsFromID(itemId);
		int itemPrice = GetTradeItemPrice(item, PRICE_TYPE_SELL);

		int qty = makeint(GetAttributeValue(itemRef));

		Trace("Item: " + itemId + "  name = '" + localizedName + "'  quantity = " + qty + " price = " + itemPrice);
	}
}
