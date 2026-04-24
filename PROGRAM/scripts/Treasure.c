#define 100_PERCENT 100
#define TREASURE_QUALITY_BAD 0
#define TREASURE_QUALITY_GOOD 1
#define TREASURE_QUALITY_BEST 2

//  Карты сокровищ  ГЕНЕРАТОР -->
string GetIslandForTreasure()
{
	aref islandArrayRef, islandRef;
	string islandName;

	int islandsForNewTreasureArrayLength = 0;
	string currentIslandId = GetCharacterCurrentIslandId(Pchar);
	makearef(islandArrayRef, NullCharacter.TravelMap.Islands);
	int islandsCount = GetAttributesNum(islandArrayRef);

	string islandsForNewTreasureArray[50]; // динамические массивы в Шторме не организуешь
	for (int i = 0; i < islandsCount; i++)
	{
		islandRef = GetAttributeN(islandArrayRef, i);
		islandName = GetAttributeName(islandRef);
		if(CheckAttribute(&NullCharacter,"TravelMap.Islands." + islandName + ".Treasure"))
		{
			if(currentIslandId == islandName || CheckTreasureMaps(islandName)) continue;
			else
			{
				islandsForNewTreasureArray[islandsForNewTreasureArrayLength] = islandName;
				islandsForNewTreasureArrayLength++;
			}
		}
	}
	int islandForNewTreasureSelectedIndex = rand(islandsForNewTreasureArrayLength - 1);
	return islandsForNewTreasureArray[islandForNewTreasureSelectedIndex];
}

bool CheckTreasureMaps(string sIsland)
{
	ref Itm;

	if(GetCharacterItem(Pchar,"mapQuest") > 0)
	{
		itm = ItemsFromID("mapQuest");
		if(CheckAttribute(itm, "MapIslId") && itm.MapIslId == sIsland) return true;
	}
	if(GetCharacterItem(Pchar,"map_full") > 0)
	{
		itm = ItemsFromID("map_full");
		if(CheckAttribute(itm, "MapIslId") && itm.MapIslId == sIsland) return true;
	}
	return false;
}

string GetLocationForTreasure(string island)
{
	aref treasureLocationArrayRef, treasureLocationRef;

	makearef(treasureLocationArrayRef, NullCharacter.TravelMap.Islands.(island).Treasure);
	int treasureLocationArrayLength = GetAttributesNum(treasureLocationArrayRef);
	int selectedTreasureLocationIndex = rand(treasureLocationArrayLength - 1);

	treasureLocationRef = GetAttributeN(treasureLocationArrayRef, selectedTreasureLocationIndex);
	return GetAttributeName(treasureLocationRef);
}

string GetBoxForTreasure(string island, string location)
{
	aref treasureBoxArrayRef, treasureBoxRef;

	makearef(treasureBoxArrayRef, NullCharacter.TravelMap.Islands.(island).Treasure.(location));
	int treasureBoxArrayLength = GetAttributesNum(treasureBoxArrayRef);
	int selectedTreasureBoxIndex = rand(treasureBoxArrayLength - 1);

	treasureBoxRef = GetAttributeN(treasureBoxArrayRef, selectedTreasureBoxIndex);
	return GetAttributeValue(treasureBoxRef);  // тут не атрибут, а значеие
}

// не при деле....
string GetFileMapForTreasure(string island)
{
	int n;

	for (n = 0; n < ITEMS_QUANTITY; n++)
	{
		if (CheckAttribute(&Items[n], "MapIsland") )
		{
			if (Items[n].MapIsland == island)
			{
				return Items[n].imageTga;
			}
		}
	}
	return "";
}

void GenerateMapsInTreasure(ref item, int iProbability1, int iProbability2)
{
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_jam")) item.BoxTreasure.map_jam = 1;

	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_barbados")) item.BoxTreasure.map_barbados = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_trinidad")) item.BoxTreasure.map_trinidad = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_Curacao")) item.BoxTreasure.map_Curacao = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_martiniqua")) item.BoxTreasure.map_martiniqua = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_puerto")) item.BoxTreasure.map_puerto = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_cuba")) item.BoxTreasure.map_cuba = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_hisp")) item.BoxTreasure.map_hisp = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_nevis")) item.BoxTreasure.map_nevis = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_guad")) item.BoxTreasure.map_guad = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_antigua")) item.BoxTreasure.map_antigua = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_TORTUGA")) item.BoxTreasure.map_TORTUGA = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_sm")) item.BoxTreasure.map_sm = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_bermudas")) item.BoxTreasure.map_bermudas = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_beliz")) item.BoxTreasure.map_beliz = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_santa")) item.BoxTreasure.map_santa = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_panama")) item.BoxTreasure.map_panama = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_maracaibo")) item.BoxTreasure.map_maracaibo = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_cumana")) item.BoxTreasure.map_cumana = 1;
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_providence")) item.BoxTreasure.map_providence = 1;

	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_cayman")) item.BoxTreasure.map_cayman = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_dominica")) item.BoxTreasure.map_dominica = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_terks")) item.BoxTreasure.map_terks = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_Pearl")) item.BoxTreasure.map_Pearl = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_maine_1")) item.BoxTreasure.map_maine_1 = 1;
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_maine_2")) item.BoxTreasure.map_maine_2 = 1;
}

void FillMapForTreasure(ref item)
{
	item.MapIslId   = GetIslandForTreasure();
	item.MapLocId   = GetLocationForTreasure(item.MapIslId);
	item.MapBoxId   = GetBoxForTreasure(item.MapIslId, item.MapLocId);
	item.MapTypeIdx = rand(2);

	// генерим клад
	DeleteAttribute(item, "BoxTreasure");

	bool isSuperTreasure = CheckAttribute(Pchar, "GenQuest.TreasureBuild") || CheckAttribute(&TEV, "MapTreasureNoScam");

	FillBoxForTreasure(item, isSuperTreasure);
	FillBoxForTreasureAddition(item);

	if (!isSuperTreasure)
	{
		if (rand(15) == 1)
			item.MapTypeIdx = -1;
	}
	else
	{
		FillBoxForTreasureSuper(item);
	}

	//TraceGeneratedTreasureBox(item);

	DeleteAttribute(Pchar, "GenQuest.TreasureBuild"); //сборный
	DeleteAttribute(&TEV, "MapTreasureNoScam");

	if (sti(item.MapTypeIdx) != -1)
	{
		Pchar.quest.SetTreasureFromMap.win_condition.l1          = "location";
		Pchar.quest.SetTreasureFromMap.win_condition.l1.location = item.MapLocId;
		Pchar.quest.SetTreasureFromMap.win_condition             = "SetTreasureFromMap";
	}
}

void FillBoxForTreasure(ref treasure, bool isSuperTreasure)
{
	int luck = GetCharacterSPECIAL(pchar, SPECIAL_L);
	int fortune = GetCharacterSkill(Pchar, SKILL_FORTUNE);

	// quantity of items in treasury depends on luck
	// for example some item in treasure can have max quantity = 100
	// with luck = 10 luckMultiplierFactor = 1.0 and max possible quantity = 100 * 1.0 = 100
	// with luck = 3 luckMultiplierFactor = 0.3 and max possible quantity = 100 * 0.3 = 30
	float luckMultiplierFactor = luck / 10.0;

	int treasureQuality = GetTreasureQuality(fortune, isSuperTreasure);

	switch(treasureQuality)
	{
		case TREASURE_QUALITY_BAD:
			GenerateBadTreasureContent(treasure, luckMultiplierFactor);
		break;
		case TREASURE_QUALITY_GOOD:
			GenerateGoodTreasureContent(treasure, luckMultiplierFactor);
		break;
		case TREASURE_QUALITY_BEST:
			GenerateBestTreasureContent(treasure, luckMultiplierFactor);
		break;
	}
}

void GenerateGoodTreasureContent(ref treasure, float luckMultiplierFactor)
{
	int additionalItemQty;

	if (rand(1) == 1)
	{
		additionalItemQty = 30 * luckMultiplierFactor;
		treasure.BoxTreasure.jewelry2 = 2 + rand(additionalItemQty);
	}
	else
	{
		additionalItemQty = 3 * luckMultiplierFactor;
		treasure.BoxTreasure.jewelry3 = 10 + rand(additionalItemQty);
	}
	if (rand(1) == 1)
	{
		additionalItemQty = 30 * luckMultiplierFactor;
		treasure.BoxTreasure.jewelry3 = 1 + rand(additionalItemQty);
	}
	if (rand(1) == 1)
	{
		additionalItemQty = 60 * luckMultiplierFactor;
		treasure.BoxTreasure.jewelry5 = 5 + rand(additionalItemQty);
	}
	if (rand(1) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.jewelry7 = 15 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.jewelry10 = 15 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.jewelry13 = 5 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.jewelry14 = 5 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.jewelry17 = 5 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.jewelry18 = 5 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.mineral2 = 5 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.mineral5 = 5 + rand(additionalItemQty);
	}
	if (rand(4) == 1)
	{
		treasure.BoxTreasure.suit_2 = 1;
	}
	if (rand(4) == 1)
	{
		treasure.BoxTreasure.mushket_poor = 1;
	}

	int craftRand = rand(12); // ~30%
	switch (craftRand)
	{
		case  4:	treasure.BoxTreasure.lamp = 1;				break;
		case  6:	treasure.BoxTreasure.mortar_and_pestle = 1;	break;
		case  9:	treasure.BoxTreasure.bullet_mold = 1;		break;
		case 11:	treasure.BoxTreasure.crucible = 1;			break;
	}

	GenerateMapsInTreasure(treasure, 35, 70);
}

void GenerateBestTreasureContent(ref treasure, float luckMultiplierFactor)
{
	int additionalItemQty;

	if (rand(2) == 1)
	{
		additionalItemQty = 14 * luckMultiplierFactor;
		treasure.BoxTreasure.chest = 1 + rand(additionalItemQty);
	}
	else
	{
		additionalItemQty = 3 * luckMultiplierFactor;
		treasure.BoxTreasure.jewelry12 = 10 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 4 * luckMultiplierFactor;
		treasure.BoxTreasure.incas_collection = 1 + rand(additionalItemQty);
	}
	if (rand(1) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.jewelry1 = 15 + rand(additionalItemQty);
	}
	if (rand(1) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.jewelry12 = 15 + rand(additionalItemQty);
	}
	if (rand(1) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.jewelry11 = 15 + rand(additionalItemQty);
	}
	if (rand(1) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.jewelry6 = 5 + rand(additionalItemQty);
	}
	if (rand(4) == 1)
	{
		treasure.BoxTreasure.suit_3 = 1;
	}
	if (rand(4) == 1)
	{
		treasure.BoxTreasure.mushket = 1;
	}

	int craftRand = rand(12); // ~30%
	switch (craftRand)
	{
		case  0:
			if (!isMultiObjectKnown("recipe_fulminate_silver"))
				treasure.BoxTreasure.recipe_fulminate_silver = 1;
		break;
		//case 3:	item.BoxTreasure.carpenter_kit = 1;		break;
		case  7:	treasure.BoxTreasure.tailor_kit = 1;		break;
		case  8:	treasure.BoxTreasure.mechanic_kit = 1;		break;
		case 11:	treasure.BoxTreasure.alchemy_kit = 1;		break;
	}

	craftRand = rand(5); // ~50%
	switch (craftRand)
	{
		case 2:	treasure.BoxTreasure.ethanol = 1;			break;
		case 3:	treasure.BoxTreasure.nitric_acid = 1;		break;
		case 4:	treasure.BoxTreasure.fulminate_silver = 1;	break;
	}

	GenerateMapsInTreasure(treasure, 25, 50);
}

void GenerateBadTreasureContent(ref treasure, float luckMultiplierFactor)
{
	int additionalItemQty;

	if (rand(2) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.kocherg = 5 + rand(additionalItemQty);
	}
	else
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.blade1 = 5 + rand(additionalItemQty);//fix
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.blade1 = 5 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.blade5 = 5 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.jewelry16 = 5 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.mineral4 = 5 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 200 * luckMultiplierFactor;
		treasure.BoxTreasure.mineral6 = 5 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.mineral7 = 5 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.mineral9 = 5 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 300 * luckMultiplierFactor;
		treasure.BoxTreasure.mineral10 = 25 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 300 * luckMultiplierFactor;
		treasure.BoxTreasure.indian4 = 15 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.indian8 = 5 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.indian9 = 5 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 100 * luckMultiplierFactor;
		treasure.BoxTreasure.indian13 = 5 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		additionalItemQty = 200 * luckMultiplierFactor;
		treasure.BoxTreasure.indian16 = 5 + rand(additionalItemQty);
	}
	if (rand(2) == 1)
	{
		treasure.BoxTreasure.blade5 = 1;
	}
	if (rand(2) == 1)
	{
		treasure.BoxTreasure.suit_1 = 1;
	}
}

void FillBoxForTreasureAddition(ref item)
{
	float fortune = GetCharacterSkillToOld(Pchar, SKILL_FORTUNE);

	if (5 * fortune > rand(55))
	{
		if (GetCharacterItem(Pchar, "map_part1") == 0)
		{
			item.BoxTreasure.map_part1 = 1;
		}
		else
		{
			if (GetCharacterItem(Pchar, "map_part2") == 0)
			{
				item.BoxTreasure.map_part2 = 1;
			}
		}
	}
	// +1 вещи
	switch (rand(40))
	{
		case 1:
			item.BoxTreasure.STATUE1 = 1;
		break;
		case 2:
			item.BoxTreasure.jewelry9 = 1;
		break;
		case 3:
			item.BoxTreasure.jewelry15 = 1;
		break;
		case 4:
			item.BoxTreasure.jewelry8 = 1;
		break;
		case 5:
			item.BoxTreasure.indian7 = 1;
		break;
		case 6:
			item.BoxTreasure.indian2 = 1;
		break;
		case 7:
			item.BoxTreasure.jewelry4 = 1;
		break;
		case 8:
			item.BoxTreasure.indian3 = 1;
		break;
		case 9:
			item.BoxTreasure.indian1 = 1;
		break;
		case 10:
			item.BoxTreasure.indian5 = 1;
		break;
		case 11:
			item.BoxTreasure.indian6 = 1;
		break;
		case 12:
			item.BoxTreasure.indian10 = 1;
		break;
		case 13:
			item.BoxTreasure.indian12 = 1;
		break;
		case 14:
			item.BoxTreasure.indian14 = 1;
		break;
		case 15:
			item.BoxTreasure.indian15 = 1;
		break;
		case 16:
			item.BoxTreasure.indian17 = 1;
		break;
		case 17:
			item.BoxTreasure.indian18 = 1;
		break;
		case 18:
			item.BoxTreasure.indian19 = 1;
		break;
		case 19:
			item.BoxTreasure.indian20 = 1;
		break;
		case 20:
			item.BoxTreasure.indian21 = 1;
		break;
		case 21:
			item.BoxTreasure.indian22 = 1;
		break;
		case 22:
			item.BoxTreasure.Mineral3 = 1;
		break;
		case 23:
			item.BoxTreasure.Mineral8 = 1;
		break;
		case 24:
			item.BoxTreasure.Coins = 1;
		break;
		case 25:
			item.BoxTreasure.sculMa1 = 1;
		break;
		case 26:
			item.BoxTreasure.sculMa2 = 1;
		break;
		case 27:
			item.BoxTreasure.sculMa3 = 1;
		break;
		case 28:
			item.BoxTreasure.mushket_flint = 1;
		break;
	}
	GenerateMapsInTreasure(item, 10, 20);

	//добавим тотемы
	string sName = "Totem_" + (rand(9)+1);
	if (!CheckMainHeroTotem(sName) && rand(20)==1) item.BoxTreasure.(sName) = 1;
}

void FillBoxForTreasureSuper(ref item)
{
	// evganat - энциклопедия
	if (CheckRandomPage("treasurechest", "", -1))
	{
		item.encyclopedia.tome = GetRandomTome();
		item.encyclopedia.page = 3;
	}

	float fortune   = GetCharacterSkillToOld(Pchar, SKILL_FORTUNE);
	if (3 * fortune > rand(21))// ещё поди найди 2 куска
	{
		string itemName = GetSuperTreasureItem();
		if (itemName != "")
		{
			item.BoxTreasure.(itemName) = 1;
		}
	}
}

string GetSuperTreasureItem()
{
	int limit = 0;
	string  itemName = "";
	while (itemName == "" && limit < 15)
	{
		switch (rand(16))
		{
			case 0:
				itemName = GetGeneratedItem("blade13");
			break;
			case 1:
				itemName = GetGeneratedItem("blade20");
			break;
			case 2:
				itemName = GetGeneratedItem("blade23");
			break;
			case 3:
				itemName = GetGeneratedItem("blade24");
			break;
			case 4:
				itemName = "pistol4";
			break;
			case 5:
				itemName = "indian11";//"idol";
			break;
			case 6:
				itemName = GetGeneratedItem("topor2"); // TODO
			break;
			case 7:
				itemName = "spyglass4";
			break;
			case 8:
				itemName = "cirass4";
			break;
			case 9:
				itemName = "indian11";
			break;
			case 10:
				itemName = "cirass3";
			break;
			case 11:
				itemName = "spyglass5";
			break;
			case 12:
				itemName = GetGeneratedItem("blade25");
			break;
			case 13:
				itemName = GetGeneratedItem("blade26");
			break;
			case 14:
				itemName = GetGeneratedItem("blade30");
			break;
			case 15:
				itemName = GetGeneratedItem("blade33");
			break;
			case 16:
				itemName = "mushket_H2";
			break;
		}
		if (GetCharacterItem(Pchar, itemName) > 0)
		{
			itemName = "";
		}
		limit++;
	}
	return itemName;
}

void SetTreasureBoxFromMap()
{
	aref   item;
	ref    loc;
	aref   arToBox;
	aref   arFromBox;

	if (GetCharacterItem(Pchar, "map_full")>0 )
	{
		//        Log_Info(StringFromKey("InfoMessages_105"));
		notification(StringFromKey("InfoMessages_105"), "Icollection");
		PlaySound("Notebook");
		Statistic_AddValue(Pchar, "Treasure", 1);
		Achievement_AddStats_Treasure();

		// немного веселой жизни
		TraderHunterOnMap();
		if( CheckAttribute(Pchar,"location.from_sea") )
		{
			if (rand(2) == 1) //33%
			{
				Pchar.quest.SetTreasureHunter.win_condition.l1          = "location";
				Pchar.quest.SetTreasureHunter.win_condition.l1.location = Pchar.location.from_sea;
				Pchar.quest.SetTreasureHunter.win_condition             = "";
				Pchar.quest.SetTreasureHunter.function    = "SetTreasureHunter";
			}
		}

		Items_FindItem("map_full", &item);

		string box = item.MapBoxId;

		loc = &locations[FindLocation(item.MapLocId)];
		loc.(box).items = "";

		makearef(arToBox, loc.(box).items);
		makearef(arFromBox, item.BoxTreasure);
		CopyAttributes(arToBox, arFromBox);

		loc.(box) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
		loc.(box).Treasure =  true; // признак сокровища в сундуке

		// evganat - энциклопедия
		if (!ENCYCLOPEDIA_DISABLED && CheckAttribute(item, "encyclopedia"))
		{
			loc.(box).encyclopedia.tome = item.encyclopedia.tome;
			loc.(box).encyclopedia.page = item.encyclopedia.page;
		}

		DeleteAttribute(item, "MapIslId");
		TakeNItems(Pchar, "map_full", -1);
	}
}
//  Карты сокровищ  ГЕНЕРАТОР <--

// погодня за ГГ на карте
void  TraderHunterOnMap()
{
	// немного веселой жизни
	ref  sld;

	string sCapId = "Follower0";
	string sGroup = "Sea_" + sCapId + "1";

	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	for (int i = 1; i <= GetCompanionQuantity(Pchar); i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", sti(PChar.rank) + 5, PIRATE, 15, true));
		SetShipHunter(sld);
		SetFantomParamHunter(sld); //крутые парни
		SetCaptanModelByEncType(sld, "war");
		sld.AlwaysEnemy = true;
		sld.DontRansackCaptain = true;
		sld.mapEnc.type = "war";
		sld.mapEnc.Name = FindPersonalName("Gentlemen_mapEnc");
		sld.hunter = "pirate";
		Group_AddCharacter(sGroup, sCapId + i);
	}

	Group_SetGroupCommander(sGroup, sCapId+ "1");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Map_CreateWarrior("", sCapId + "1", 8);
}

void SetTreasureHunter(string temp)
{
	int index, k;
	ref sld;

	if (chrDisableReloadToLocation) return; // идет некий другой квест с запретом выхода

	Pchar.GenQuest.Hunter2Pause = true;

	int j = GetOfficersQuantity(Pchar) + 2;

	string sCapId = "LandHunter0";
	string sTemp = "LAND_HUNTER";
	bool ok = true;
	arrayNPCModelHow = 0;

	for (index = 1; index <= j; index++)
	{
		sld = GetCharacter(NPC_GenerateCharacter(sCapId + index, "off_hol_2", "man", "man", sti(PChar.rank) + 5, PIRATE, 0, true));
		SetFantomParamHunter(sld); //крутые парни
		sld.Dialog.CurrentNode = "TreasureHunter";
		sld.dialog.filename = "Hunter_dialog.c";
		sld.greeting = "Gr_HUNTER";
		sld.location = "none"; // вот где порылась собака!!!!!!!!!!!

		SetModelPirate(sld);
		k = 0;
		while (!CheckNPCModelUniq(sld) && k < 10)
		{
			k++;
			SetModelPirate(sld);
		}
		arrayNPCModel[arrayNPCModelHow] = sld.model;
		arrayNPCModelHow++;

		LAi_SetActorTypeNoGroup(sld);
		LAi_SetCheckMinHP(sld, (LAi_GetCharacterHP(sld) - 1), false, "Battle_Hunters_Land");
		if (PlaceCharacter(sld, "goto", "random_must_be_near") == "" && index == 1) // fix если вдруг нет в локации
		{
			ok = false;
			break;
		}
		LAi_ActorFollow(sld, Pchar, "", 8.0);
		//LAi_Actor2WaitDialog(sld, Pchar); // ждать диалог, но бежать
		LAi_group_MoveCharacter(sld, sTemp);
	}

	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER_OWN, LAI_GROUP_NEITRAL);

	LAi_group_ClearAllTargets();
	LAi_SetFightModeForOfficers(false);
	if (ok)
	{
		PChar.HunterCost = makeint(sti(Pchar.money) / 5) + rand(20)*1000; //сразу генерим
		PChar.HunterCost.Qty = index;
		PChar.HunterCost.TempHunterType = "";
		sld = characterFromID(sCapId + "1");
		LAi_type_actor_Reset(sld);
		LAi_ActorDialog(sld, Pchar, "", 4.0, 0);
		chrDisableReloadToLocation = true;
		DoQuestCheckDelay("OpenTheDoors", 5.0);
	}
}

//=====================================================================================================================================
// Ugeen. ГЕНЕРАТОР  "Специальный энкаунтер - бочка"
//=====================================================================================================================================
void Set_TreasureBarrel()
{
	aref trBarrel;

	ref nulChr = &NullCharacter;
	if(CheckAttribute(nulChr,"GenQuest.Barrel")) DeleteAttribute(nulChr,"GenQuest.Barrel");

	makearef(trBarrel, nulChr.GenQuest.Barrel);
	int irand;
	if(CheckCharacterPerk(Pchar, "HawkEye"))
	{
		irand = rand(100);
	}
	else
	{
		irand = rand(200);
	}
	if(GetSummonSkillFromName(Pchar, "Fortune") > irand)
	{
		irand = rand(20);
		switch(irand)
		{
			case 1:		trBarrel.items.jewelry1 = rand(18) + 27;	break;
			case 2:		trBarrel.items.jewelry2 = rand(22) + 22;	break;
			case 3:		trBarrel.items.jewelry3 = rand(15) + 32;	break;
			case 4:		trBarrel.items.jewelry4 = rand(22) + 15;	break;
			case 5:		trBarrel.items.jewelry5 = rand(19) + 22;	break;
			case 6:		trBarrel.items.jewelry6 = rand(22) + 16;	break;
			case 7:		trBarrel.items.jewelry7 = rand(17) + 32;	break;
			case 8:		trBarrel.items.jewelry8 = rand(5) + 18;		break;
			case 9:		trBarrel.items.jewelry9 = rand(8) + 12;		break;
			case 10:	trBarrel.items.jewelry10 = rand(35) + 12;	break;
			case 11:	trBarrel.items.jewelry11 = rand(13) + 27;	break;
			case 12:	trBarrel.items.jewelry12 = rand(16) + 18;	break;
			case 13:	trBarrel.items.jewelry13 = rand(30) + 15;	break;
			case 14:	trBarrel.items.jewelry14 = rand(30) + 15;	break;
			case 15:	trBarrel.items.jewelry16 = rand(35) + 14;	break;
			case 16:	trBarrel.items.jewelry17 = rand(24) + 18;	break;
			case 17:	trBarrel.items.jewelry18 = rand(17) + 13;	break;
			case 18:	trBarrel.items.chest = rand(2) + 1;			break;
			case 19:	trBarrel.items.coins = rand(10) + 7;		break;
		}
		irand = rand(25);
		switch(irand)
		{
			case 3:		trBarrel.items.indian18 = 1;			break;
			case 6:		trBarrel.items.indian20 = 1;			break;
			case 9:		trBarrel.items.indian21 = 1;			break;
			case 12:	trBarrel.items.indian11 = 1;			break;
			case 15:	trBarrel.items.indian12 = 1;			break;
			case 18:	trBarrel.items.indian6 = 1;				break;
			case 21:	trBarrel.items.incas_collection = 1;	break;
			case 24:
				if (GetCharacterItem(Pchar, "map_full") == 0)
				{
					if (GetCharacterItem(Pchar, "map_part1") == 0)
						trBarrel.items.map_part1 = 1;
					else
					{
						if (GetCharacterItem(Pchar, "map_part2") == 0)
							trBarrel.items.map_part2 = 1;
					}
				}
			break;
		}
		irand = rand(39);
		switch (irand)
		{
			case  9:	trBarrel.items.lamp = 1;				break;
			case 19:	trBarrel.items.mortar_and_pestle = 1;	break;
			case 29:	trBarrel.items.bullet_mold = 1;			break;
			case 39:	trBarrel.items.crucible = 1;			break;
		}

		irand = rand(35);
		switch(irand)
		{
			case 20:	trBarrel.items.sculMa2 = 1;		break;
			case 28:	trBarrel.items.sculMa3 = 1;		break;
		}
	}
	else
	{
		if(rand(1) == 0) trBarrel.items.mineral2 = rand(7) + 7;
		if(rand(1) == 0) trBarrel.items.mineral3 = rand(15) + 5;
		if(rand(1) == 0) trBarrel.items.mineral4 = rand(10) + 2;
		if(rand(1) == 0) trBarrel.items.mineral5 = rand(8) + 4;
		if(rand(1) == 0) trBarrel.items.mineral6 = rand(14) + 7;
		if(rand(1) == 0) trBarrel.items.mineral7 = rand(12) + 8;
		if(rand(1) == 0) trBarrel.items.mineral8 = rand(12) + 6;
		if(rand(1) == 0) trBarrel.items.mineral9 = rand(8) + 2;
		if(rand(1) == 0) trBarrel.items.mineral10 = rand(16) + 6;
	}
	trBarrel.items.gold = rand(5000) + 5000;
	LaunchItemsBarrel(&trBarrel);
}
//=====================================================================================================================================
// Ugeen. ГЕНЕРАТОР  "Специальный энкаунтер - бочка"
//=====================================================================================================================================

int GetTreasureQuality(int fortune, bool isSuperTreasure)
{
	// chance to get bad treasure
	// for treasure level 1: 10% when fortune = 100 and 50% when fortune = 0
	// for treasure level 2: 5% when fortune = 100 and 25% when fortune = 0
	float chanceToGetBadTreasure;
	if(!isSuperTreasure)
	{
		chanceToGetBadTreasure =  (SKILL_MAX - fortune * 0.8) / 2.0;
	}
	else
	{
		chanceToGetBadTreasure =  (SKILL_MAX - fortune * 0.8) / 4.0;
	}
	int roll = rand(100_PERCENT - 1);
	if(roll < chanceToGetBadTreasure)
	{
		return TREASURE_QUALITY_BAD;
	}

	// chance to get the best treasure (either best or good)
	// for treasure level 1: 50% when fortune = 100 and 20% when fortune = 0
	// for treasure level 2: 68% when fortune = 100 and 38% when fortune = 0
	float chanceToGetBestTreasure;
	if(!isSuperTreasure)
	{
		chanceToGetBestTreasure = fortune * 0.6 / 2.0 + 20;
	}
	else
	{
		chanceToGetBestTreasure = fortune * 0.6 / 2.0 + 38;
	}
	roll = rand(100_PERCENT - 1);
	if(roll < chanceToGetBestTreasure)
	{
		return TREASURE_QUALITY_BEST;
	}

	return TREASURE_QUALITY_GOOD;
}

void TraceGeneratedTreasureBox(ref treasure)
{
	aref arBox;

	makearef(arBox, treasure.BoxTreasure);
	int itemsCount = GetAttributesNum(arBox);

	for (int i = 0; i < itemsCount; i++)
	{
		aref item = GetAttributeN(arBox, i);
		string itemId = GetAttributeName(item);
		string localizedName = GetItemName(itemId);

		int qty = makeint(GetAttributeValue(item));

		Trace("Item: " + itemId + "  name = '" + localizedName + "'  quantity = " + qty);
	}
}