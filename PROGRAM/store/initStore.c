extern void StoreInit();

void InitStores()
{
    int i;

    for(i=0; i<STORE_QUANTITY; i++)
    {
		stores[i].index = i;
        StoreVoidFill(&stores[i]);
    }

	if(LoadSegment("store\store_init.c"))
	{
		StoreInit();
		UnloadSegment("store\store_init.c");
	}

   for(i=0; i<STORE_QUANTITY; i++)
   {
       FillStoreGoods(&stores[i]);
   }
}

void SetStoresTradeType(int StoreNum,int GoodsNum,int TradeType)
{
	string tmpstr = Goods[GoodsNum].Name;
	Stores[StoreNum].Goods.(tmpstr).TradeType = TradeType;
}

void FillStoreGoods(ref pRef)
{
	int i,j,nq,n,tt;
	string goodName;
	string goodType;
	//int goodBasePrice;

	int iColony = FindColony(pRef.Colony); // город магазина
	aref arTypes, arCurType;
	if (iColony != -1)
	{
		ref rColony = GetColonyByIndex(iColony);
		int islandIdx = FindIsland(rColony.island); // остров города
		
		if (islandIdx != -1)
		{
			makearef(arTypes, pRef.Trade);
			nq = GetAttributesNum(arTypes);
			
			for(i=0;i<nq;i++)
			{
				arCurType = GetAttributeN(arTypes,i);
				tt=TRADE_TYPE_NORMAL;
				switch(GetAttributeName(arCurType))
				{
					case "Export":		tt=TRADE_TYPE_EXPORT;		break;
					case "Import":		tt=TRADE_TYPE_IMPORT;		break;
					case "Contraband":	tt=TRADE_TYPE_CONTRABAND;	break;
				}
				n = GetAttributesNum(arCurType);
				for(j=0;j<n;j++)
				{
					goodName = Goods[sti(GetAttributeValue(GetAttributeN(arCurType,j)))].name;
					pRef.Goods.(goodName).TradeType = tt;
				}
			}
		}
		else
		{
			if (!HasStr(rColony.island, "Panama"))
				trace("Mistake island id into store:  id="+rColony.island);
		}
	}
	else
	{
		if (pRef.Colony != "none")
			trace("Mistake Colony id into store:  id=" + pRef.Colony);
	}
	
	for (i = 0; i < GOODS_QUANTITY; i++)
	{
	   	goodName = Goods[i].Name;
	   	// boal 22.01.2004 -->
		switch(sti(pRef.Goods.(goodName).TradeType))
		{
			case TRADE_TYPE_NORMAL:
			    pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.5 + rand(sti(sti(Goods[i].Norm)*0.2))); //200 + Rand(2500) + rand(500);
				pRef.Goods.(goodName).RndPriceModify = frnd() * 0.15;//0.2
				break;

			case TRADE_TYPE_EXPORT:
			    pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.9 + rand(sti(sti(Goods[i].Norm)*0.2))); //500 + Rand(4000)+ rand(6000);
				pRef.Goods.(goodName).RndPriceModify = frnd() * 0.15; //0.2
				break;

			case TRADE_TYPE_IMPORT:
			    pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.2 + rand(sti(sti(Goods[i].Norm)*0.15))); //60 + Rand(500) + rand(500);
				pRef.Goods.(goodName).RndPriceModify = frnd() * 0.30; // 0.35
				break;

			case TRADE_TYPE_CONTRABAND:
			    pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.1 + rand(sti(sti(Goods[i].Norm)*0.1))); //1+Rand(50)*sti(goods[i].Units);
				pRef.Goods.(goodName).RndPriceModify = frnd() * 0.35; //0.5
				break;

			case TRADE_TYPE_AMMUNITION:  //делаю все тоже, что и для нормального товара, а тип нужен, чтоб на корабле не скупали лишнее.
			    pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm)*0.5 + rand(sti(sti(Goods[i].Norm)*0.2))); //200 + Rand(2500) + rand(500);
				pRef.Goods.(goodName).RndPriceModify = frnd() * 0.15;//0.2
				break;

			case TRADE_TYPE_CANNONS: 
				pRef.Goods.(goodName).Quantity = sti(sti(Goods[i].Norm) * 0.6 + rand(sti(sti(Goods[i].Norm) * 0.6))); //20 + Rand(50) + rand(50);
				pRef.Goods.(goodName).RndPriceModify = frnd() * 0.3; // 0.4
				break;	
		}
		
		// Размер имеет значение (TODO: можно ставить кастомный множитель при динамической экономике)
		switch(pRef.StoreSize)
		{
			case "large":  n = 1;	break;
			case "medium": n = 1.5;	break;
			case "small":  n = 3;	break;
		}
		pRef.Goods.(goodName).Quantity = makeint(sti(pRef.Goods.(goodName).Quantity) / n);
		
		// 24/01/08
		pRef.Goods.(goodName).Norm            = pRef.Goods.(goodName).Quantity; // колво в начале, это норма магазина на всегда
		pRef.Goods.(goodName).NormPriceModify = pRef.Goods.(goodName).RndPriceModify; // начальная цена - тоже limit стремлений
	}
	//HardCoffee распределаем бабки по магазинам и контрабандистам
	switch(pRef.StoreSize)
	{
		case "large":
			pRef.money =			makeint(STORE_MIN_MONEY + frand(1.0)*STORE_RAND_MONEY);
			pRef.smugglerMoney =	makeint(SMUGG_MIN_MONEY	+ frand(1.0)*SMUGG_RAND_MONEY);
		break;
		case "medium":
			pRef.money =			makeint(STORE_MIN_MONEY/2 + frand(1.0)*STORE_RAND_MONEY/2);
			pRef.smugglerMoney =	makeint(SMUGG_MIN_MONEY	+ frand(1.0)*SMUGG_RAND_MONEY);
		break;
		case "small":
			pRef.money =			makeint(STORE_MIN_MONEY/2 + frand(1.0)*STORE_RAND_MONEY/2);
			pRef.smugglerMoney =	makeint(SMUGG_MIN_MONEY	+ frand(1.0)*SMUGG_RAND_MONEY);
		break;
	}
}

void StoreVoidFill(ref pRef)
{
	string goodName;
	//pRef.StoreSize = "large"; // "small"
	pRef.Island = "";
	for(int i=0; i<GOODS_QUANTITY; i++)
	{
		goodName = Goods[i].Name;
		// boal fix -->
		if (CheckAttribute(&Goods[i], "type"))
		{
		    pRef.Goods.(goodName).TradeType = Goods[i].type;
		}
		else
		{ // boal fix <--
			pRef.Goods.(goodName).TradeType = TRADE_TYPE_NORMAL;
		}
		pRef.Goods.(goodName).NotUsed = false;
		pRef.Goods.(goodName).Quantity = 0;
	}
}