string totalInfo = "";
int  	TableSelect = 0;
int		nCurScrollNum = 0;
int 	iShipCapacity;
int 	iTotalSpace;
float 	fShipWeight, fStoreWeight;
int 	iMaxGoodsStore = 50000;

bool 	bShowChangeWin = false;
int  	BuyOrSell = 0; // 1-buy -1 sell
string 	sChrId;
ref 	refCharacter, refShipChar;
int 	iShipQty, iStoreQty, iShipPrice, iStorePrice, iUnits;
float 	fWeight;
int  	iCurGoodsIdx;
bool 	ok; // for if

void InitInterface(string iniName)
{
 	StartAboveForm(true);
	refCharacter = pchar;

	GameInterface.TABLE_LIST.hr.td1.str = XI_ConvertString("In the hold");
	GameInterface.TABLE_LIST.hr.td1.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td2.str = XI_ConvertString("weight");
	GameInterface.TABLE_LIST.hr.td2.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("Good name");
	GameInterface.TABLE_LIST.hr.td3.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td4.str = XI_ConvertString("GoodsToBuy");
	GameInterface.TABLE_LIST.hr.td4.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td5.str = XI_ConvertString("weight");
	GameInterface.TABLE_LIST.hr.td5.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td6.str = XI_ConvertString("Cost");
	GameInterface.TABLE_LIST.hr.td6.scale = 0.9;

    FillShipsScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetFormatedText("STORE_CAPACITY", XI_ConvertString("treasurer") + NewStr() + GetFullNameTitulForm(Characters[sti(pchar.Fellows.Passengers.treasurer)]));
	SetNewPicture("OTHER_PICTURE", "interfaces\portraits\256\face_" + Characters[sti(refCharacter.Fellows.Passengers.treasurer)].FaceId + ".tga");

	CreateString(true,"ShipName","",FONT_NORMAL,COLOR_MONEY, 400,98,SCRIPT_ALIGN_CENTER,0.7);

    SetShipWeight();
	SetDescription();

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);

	SetEventHandler("OnTableClick", "OnTableClick", 0);
	SetEventHandler("MouseRClickUP","EndTooltip",0);
	SetEventHandler("ShowItemInfo", "ShowItemInfo", 0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("TransactionOK", "TransactionOK", 0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);

	SetEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON", 0);
	SetEventHandler("ADD_BUTTON","ADD_BUTTON",0);
	SetEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON", 0);
	SetEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON", 0);

    SetEventHandler("CheckButtonChange", "ProcessCheckBox", 0);
	SetEventHandler("frame","ProcessFrame",1);
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_GOODS_TRANSFER );
}

void ProcessCancelExit()
{
	if (bShowChangeWin) EndTooltip();
	else IDoExit( RC_INTERFACE_GOODS_TRANSFER );
}

void IDoExit(int exitCode)
{
    EndAboveForm(true);

	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");

	DelEventHandler("OnTableClick", "OnTableClick");
	DelEventHandler("MouseRClickUP","EndTooltip");
	DelEventHandler("ShowItemInfo", "ShowItemInfo");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("frame","ProcessFrame");
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON");
	DelEventHandler("ADD_BUTTON","ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");
	DelEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON");
	DelEventHandler("CheckButtonChange", "ProcessCheckBox");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{

		case "CLEAR_TABLE_LIST":
			DeleteAttribute(&refCharacter,"TransferGoods");
			CalculateInfoData();
		break;

		case "QTY_OK_BUTTON":
			if(comName == "leftstep")
			{
	            ADD_BUTTON();
			}
			if(comName == "rightstep")
			{
	            REMOVE_BUTTON();
			}
			if(comName == "speedleft")
			{
	      		ADD_ALL_BUTTON();
			}
			if(comName == "speedright")
			{
	            REMOVE_ALL_BUTTON();
			}
		break;

		case "QTY_CANCEL_BUTTON":
			if(comName == "leftstep")
			{
	            ADD_BUTTON();
			}
			if(comName == "rightstep")
			{
	            REMOVE_BUTTON();
			}
			if(comName == "speedleft")
			{
	      		ADD_ALL_BUTTON();
			}
			if(comName == "speedright")
			{
	            REMOVE_ALL_BUTTON();
			}
		break;

		case "TABLE_LIST":
			if(comName == "leftstep")
			{
	            ADD_BUTTON();
			}
			if(comName == "rightstep")
			{
	            REMOVE_BUTTON();
			}
			if(comName == "speedleft")
			{
	      		ADD_ALL_BUTTON();
			}
			if(comName == "speedright")
			{
	            REMOVE_ALL_BUTTON();
			}
		break;
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void CalculateInfoData()
{
    AddToTable();
    SetCheckButtonsStates();
	ShowGoodsInfo(sti(GameInterface.TABLE_LIST.tr1.index));
}

void AddToTable()
{
	int n, i, iColor, buyCount, iShipQ;
	string row, sShipGroup;
	ref rShip;
	string sGood;
	string sBuy, sSell, sStoreWeight;
	aref refGoods;

	n = 1;
	Table_Clear("TABLE_LIST", false, true, false);
    for (i = 0; i< GOODS_QUANTITY; i++)
	{
        row = "tr" + n;
        if (i == GOOD_PINCTADA) continue;
		if (CheckAttribute(&Goods[i],"CannonIdx")) continue;
		sGood = Goods[i].name;

		iShipQ = GetCargoGoods(refCharacter, i);

		if (CheckAttribute(&refCharacter, "TransferGoods." + sGood)) buyCount = sti(refCharacter.TransferGoods.(sGood));
		else buyCount = 0;

		GameInterface.TABLE_LIST.(row).index = i;
		GameInterface.TABLE_LIST.(row).td1.str = iShipQ;
		GameInterface.TABLE_LIST.(row).td2.str = GetGoodWeightByType(i, iShipQ);
		GameInterface.TABLE_LIST.(row).td5.str = GetGoodWeightByType(i, sti(buyCount));

		GameInterface.TABLE_LIST.(row).td4.str = buyCount;
		GameInterface.TABLE_LIST.(row).td6.str = sti(Goods[i].Cost) * buyCount;

		iColor = argb(255,255,255,255);

		if(checkAttribute(refCharacter, "ship.cargo.goods." + sGood + ".isquest"))
		{
			iColor = argb(255,255,192,255);
		}

        GameInterface.TABLE_LIST.(row).td3.icon.group = "GOODS";
		GameInterface.TABLE_LIST.(row).td3.icon.image = sGood;
		GameInterface.TABLE_LIST.(row).td3.icon.offset = "0, 0";
		GameInterface.TABLE_LIST.(row).td3.icon.width = 29;
		GameInterface.TABLE_LIST.(row).td3.icon.height = 29;
		GameInterface.TABLE_LIST.(row).td3.textoffset = "25,0";
		GameInterface.TABLE_LIST.(row).td3.str = XI_ConvertString(sGood);
		GameInterface.TABLE_LIST.(row).td3.color = iColor;
		n++;
	}
	NextFrameRefreshTable();
}

void NextFrameRefreshTable()
{
	SetEventHandler("frame", "RefreshTableByFrameEvent", 0);
}

void RefreshTableByFrameEvent()
{
	DelEventHandler("frame", "RefreshTableByFrameEvent");
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TABLE_LIST", 0 );
}

void OnTableClick()
{
	string sControl = GetEventData();
	int iRow = GetEventData();
	int iColumn = GetEventData();

	string sRow = "tr" + (iRow + 1);
    Table_UpdateWindow(sControl);
}

void EndTooltip()
{
	CloseTooltip(); // всегда убирать, если был
    GameInterface.qty_edit.str = 0;
	SetShipWeight();
	SetVariable();
	SetCurrentNode("TABLE_LIST");
 	XI_WindowDisable("QTY_WINDOW", true);
	XI_WindowShow("QTY_WINDOW", false);
	bShowChangeWin = false;
}

void ShowItemInfo()
{
	if (bShowChangeWin) // жмем окей, когда курсор на таблице
	{
	    TransactionOK();
	}
	else
	{
		GameInterface.qty_edit.str = "0";
		BuyOrSell = 0;
		ChangeQTY_EDIT();

		XI_WindowDisable("QTY_WINDOW", false);
		XI_WindowShow("QTY_WINDOW", true);
		bShowChangeWin = true;
		if (GetRemovable(refCharacter))
		{
		    SetSelectable("QTY_OK_BUTTON", true);
		}
		else
		{
		    SetSelectable("QTY_OK_BUTTON", false);
		}
	}
}

void RefreshTable()
{
    PostEvent("RefreshTable", 100);
    if (TableSelect != sti(GameInterface.TABLE_LIST.select))
    {
        TableSelect = sti(GameInterface.TABLE_LIST.select);
    }
}

void CS_TableSelectChange()
{
	string sControl = GetEventData();
	int iSelected = GetEventData();
    TableSelect = iSelected;
    string sRow = "tr" + (iSelected);
	SetShipWeight();
	SetVariable();
    ShowGoodsInfo(sti(GameInterface.TABLE_LIST.(sRow).index));
}

void FillShipsScroll()
{
	nCurScrollNum = -1;
	FillScrollImageWithCompanionShips("SHIPS_SCROLL", 4);

	if(!CheckAttribute(&GameInterface,"SHIPS_SCROLL.current"))
	{
		GameInterface.SHIPS_SCROLL.current = 0;
	}
}

void SetVariable()
{
	string sText, sTextSecond;

	iShipCapacity = GetCargoMaxSpace(refCharacter);
	sText  = iShipCapacity;

	sText  = makeint(fShipWeight) + " / " + sText;
	sText = sText;
	SetFormatedText("CAPACITY", XI_ConvertString("Capacity") + ":\n" + sText);

	iTotalSpace = iMaxGoodsStore;

	if (CheckAttribute(refCharacter, "ship.name"))
	{
		GameInterface.strings.shipname = refCharacter.ship.name;
	}
	else
	{
	    GameInterface.strings.shipname = "";
	}
}

void ProcessFrame()
{
	if(GetCurrentNode() == "SHIPS_SCROLL")
	{
		if(sti(GameInterface.SHIPS_SCROLL.current)!=nCurScrollNum)
		{
            XI_WindowDisable("QTY_WINDOW", true);
			XI_WindowShow("QTY_WINDOW", false);
			nCurScrollNum = sti(GameInterface.SHIPS_SCROLL.current);

			SetDescription();
   			GameInterface.TABLE_LIST.select = 1;
			GameInterface.TABLE_LIST.top = 0;
		}
	}
}

void SetDescription()
{
 	if(GetCurrentNode() == "SHIPS_SCROLL")
	{
		string attributeName = "pic" + (nCurScrollNum+1);
		if(CheckAttribute(&GameInterface, "SHIPS_SCROLL." + attributeName))
		{
			int iCharacter = GameInterface.SHIPS_SCROLL.(attributeName).companionIndex;
			sChrId = characters[iCharacter].id;
			refCharacter = characterFromID(sChrId);
			SetShipWeight();
		}
	}
    CalculateInfoData();
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\256\face_" + its(refCharacter.FaceId) + ".tga");
	SetVariable();
}

void SetShipWeight()
{
    if (CheckAttribute(refCharacter, "Ship.Cargo.RecalculateCargoLoad") && sti(refCharacter.Ship.Cargo.RecalculateCargoLoad))
	{   // остатки с моря
		RecalculateCargoLoad(refCharacter);
		refCharacter.Ship.Cargo.RecalculateCargoLoad = 0;
	}
	fShipWeight  = makeint(GetCargoLoad(refCharacter)+ 0.4);

	fStoreWeight = 0;
}

void ShowGoodsInfo(int iGoodIndex)
{
	string GoodName = goods[iGoodIndex].name;
	string sHeader = XI_ConvertString(GoodName);

    iCurGoodsIdx = iGoodIndex;
    string goodsDescr = "";

	goodsDescr += GetAssembledString(GetConvertStr(goodName+"_descr", "GoodsDescribe.txt"), &Goods[iGoodIndex]);
    goodsDescr += newStr() + XI_ConvertString("weight") + " " + Goods[iGoodIndex].weight + " " + XI_ConvertString("cwt") +
	              ", " + XI_ConvertString("Pack") + " " + Goods[iGoodIndex].Units + " " + XI_ConvertString("units");

	iUnits  = sti(Goods[iGoodIndex].Units);
	fWeight = stf(Goods[iGoodIndex].weight);

    BuyOrSell = 0;
    SetFormatedText("QTY_RESULT", "");
    GameInterface.qty_edit.str = "0";

	SetNewGroupPicture("QTY_GOODS_PICTURE", "GOODS", GoodName);
    SetFormatedText("QTY_CAPTION", sHeader);
    SetFormatedText("QTY_GOODS_INFO", goodsDescr);

	iShipQty = GetCargoGoods(refCharacter, iGoodIndex);
	iStoreQty = 1;

	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty));
	BuyOrSell = 0;

	ShowFoodInfo();
}

void ShowFoodInfo()
{
	if(iCurGoodsIdx == GOOD_FOOD)
	{
		// чтоб прикинуть как оно будет, скинем на время колво на продажное
		SetCharacterGoods(refCharacter, GOOD_FOOD, iShipQty + BuyOrSell*sti(GameInterface.qty_edit.str));
		SetFoodShipInfo(refCharacter, "QTY_FOOD_INFO");
		SetCharacterGoods(refCharacter, GOOD_FOOD, iShipQty);
	}
	else
	{
		if(iCurGoodsIdx == GOOD_RUM) // Warship 11.07.09 На сколько хватит рому
		{
			// чтоб прикинуть как оно будет, скинем на время колво на продажное
			SetCharacterGoods(refCharacter, GOOD_RUM, iShipQty + BuyOrSell*sti(GameInterface.qty_edit.str));
			SetRumShipInfo(refCharacter, "QTY_FOOD_INFO");
			SetCharacterGoods(refCharacter, GOOD_RUM, iShipQty);
		}
		else
		{
			SetFormatedText("QTY_FOOD_INFO", "");
		}
	}
}

void TransactionOK()
{
	int iNum = 0;
    string sGood;
    int iTemp = 0;
    ref rGood;
    string companionId = refCharacter.Id;
    rGood = &Goods[iCurGoodsIdx];
    sGood = rGood.name;
    if (!CheckAttribute(&refCharacter,"TransferGoods." + sGood)) refCharacter.TransferGoods.(sGood) = 0;
    iNum =  sti(GameInterface.QTY_EDIT.str);
    if (iNum >999999) iNum = 999999;
    if (iNum == 0) DeleteAttribute(&refCharacter,"TransferGoods." + sGood);
    else refCharacter.TransferGoods.(sGood) = iNum; // Прибавим в список закупок
	AddToTable();
	EndTooltip();
	ShowGoodsInfo(iCurGoodsIdx); //сбросим все состояния
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
    SetCurrentNode("QTY_OK_BUTTON");
}

void ChangeQTY_EDIT()
{
	int  iWeight;
	SetShipWeight();
	GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str);

	string GoodName = goods[iCurGoodsIdx].name;

	if (sti(GameInterface.qty_edit.str) == 0)
	{
	    SetFormatedText("QTY_RESULT", "");
	    BuyOrSell = 0;
	}
	else
	{
		if (sti(GameInterface.qty_edit.str) < 0 || BuyOrSell == -1)
		{
			if (BuyOrSell != -1)
			{
		    	GameInterface.qty_edit.str = -sti(GameInterface.qty_edit.str);
		    }
            BuyOrSell = -1;

		    // проверка на колво доступное -->
		    if (sti(GameInterface.qty_edit.str) > iShipQty)
		    {
		        GameInterface.qty_edit.str = iShipQty;
		    }
		    iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
		    if ((fStoreWeight + iWeight) > iTotalSpace)
		    {
		        iWeight = iTotalSpace - fStoreWeight - fWeight;
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight * iUnits );
		        iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight * iUnits ); // округление
		    }
		    // проверка на колво доступное <--
		    SetFormatedText("QTY_RESULT", XI_ConvertString("UnloadWarehouse"));
		}
		else
		{
			BuyOrSell = 1;
         	// проверка на колво доступное -->
		    if (sti(GameInterface.qty_edit.str) > iStoreQty)
		    {
		        GameInterface.qty_edit.str = iStoreQty;
		    }
		    iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
		    if ((fShipWeight + iWeight) > iShipCapacity)
		    {
		        iWeight = iShipCapacity - fShipWeight - fWeight;
				if (iWeight < 0) iWeight = 0;
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight * iUnits );
		        iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
		        GameInterface.qty_edit.str = makeint(iWeight / fWeight * iUnits ); // округление
		    }
		    // проверка на колво доступное <--
			SetFormatedText("QTY_RESULT", XI_ConvertString("LoadInHold"));
		}
	}
	// если получили ноль
	if (sti(GameInterface.qty_edit.str) <= 0)
	{
	    SetFormatedText("QTY_RESULT", "");
	    BuyOrSell = 0;
	}
    SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty - BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty + BuyOrSell*sti(GameInterface.qty_edit.str)));
    SetShipWeight();
    fShipWeight  = fShipWeight  + BuyOrSell * iWeight;
	fStoreWeight = fStoreWeight - BuyOrSell * iWeight;
    SetVariable();
    ShowFoodInfo();
}

void REMOVE_ALL_BUTTON()
{
	if (!bShowChangeWin) return;
    OnAddBtnClick(50);
}

void ADD_ALL_BUTTON()
{
	if (!bShowChangeWin) return;
    OnAddBtnClick(-50);
}

void REMOVE_BUTTON()
{
	if (!bShowChangeWin) return;
    OnAddBtnClick(1);
}

void ADD_BUTTON()
{
	if (!bShowChangeWin) return;
    OnAddBtnClick(-1);
}

void ProcessCheckBox()
{
	string sControl = GetEventData();
	int iSelectedCB = GetEventData();
	int iNewState = GetEventData();

	if (sControl == "NOTGOODSTRANSFER_CHECK")
	{
		if (iNewState) refCharacter.TransferGoods.Enable = true;
		else DeleteAttribute(&refCharacter, "TransferGoods.Enable");
		return;
	}

	if (sControl == "BUYCONTRABAND_CHECK")
	{
		if (iNewState) refCharacter.TransferGoods.BuyContraband = true;
		else DeleteAttribute(&refCharacter, "TransferGoods.BuyContraband");
		return;
	}

	if (sControl == "SELLRESTRICTION_CHECK")
	{
		if (iNewState) refCharacter.TransferGoods.SellRestriction = true;
		else DeleteAttribute(&refCharacter, "TransferGoods.SellRestriction");
		return;
	}
}

void SetCheckButtonsStates()
{
	string companionId = refCharacter.Id;

	if(CheckAttribute(&refCharacter, "TransferGoods.Enable")) CheckButton_SetState("NOTGOODSTRANSFER_CHECK", 1, true);
	else CheckButton_SetState("NOTGOODSTRANSFER_CHECK", 1, false);

	if(CheckAttribute(&refCharacter, "TransferGoods.BuyContraband")) CheckButton_SetState("BUYCONTRABAND_CHECK", 1, true);
	else CheckButton_SetState("BUYCONTRABAND_CHECK", 1, false);

	if(CheckAttribute(&refCharacter, "TransferGoods.SellRestriction")) CheckButton_SetState("SELLRESTRICTION_CHECK", 1, true);
	else CheckButton_SetState("SELLRESTRICTION_CHECK", 1, false);
}

void OnAddBtnClick(int _add)
{
	int iNum = MakeInt(GameInterface.QTY_EDIT.str);

	ref rGood = &Goods[iCurGoodsIdx];
	int _Units = sti(rGood.Units);

	iNum = iNum + _add * _Units;
	if (iNum < 0) iNum = 0;
	// максимум 15000 грузоподъемности, хотя и 10000 много было бы
	if (iNum > 15000 / sti(rGood.Weight) * _Units) iNum = 15000 / sti(rGood.Weight) * _Units;

	GameInterface.QTY_EDIT.str = iNum;
}