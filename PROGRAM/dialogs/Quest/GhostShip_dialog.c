void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;
	ref shTo;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = StringFromKey("GhostShip_dialog_1", pchar);
			link.l1 = StringFromKey("GhostShip_dialog_2", pchar);
			link.l1.go = "Meeting_1";
			NextDiag.TempNode = "First time";
		break;

		case "Meeting_1":
			dialog.text = StringFromKey("GhostShip_dialog_3");
			link.l1 = StringFromKey("GhostShip_dialog_4");
			link.l1.go = "Meeting_2";
		break;

		case "Meeting_2":
			dialog.text = StringFromKey("GhostShip_dialog_5");
			link.l1 = StringFromKey("GhostShip_dialog_6");
			link.l1.go = "Meeting_3";
		break;

		case "Meeting_3":
			dialog.text = StringFromKey("GhostShip_dialog_7");
			link.l1 = StringFromKey("GhostShip_dialog_8");
			link.l1.go = "Meeting_4";
		break;

		case "Meeting_4":
			dialog.text = StringFromKey("GhostShip_dialog_9");
			link.l1 = StringFromKey("GhostShip_dialog_10");
			link.l1.go = "Exit";
			NextDiag.TempNode = "AfterMeet";
			ReOpenQuestHeader("GhostShipQuest");
			AddQuestRecord("GhostShipQuest", "4");
		break;

		case "AfterMeet":
			dialog.text = StringFromKey("GhostShip_dialog_11", pchar);
			link.l1 = StringFromKey("GhostShip_dialog_12");
			link.l1.go = "Exit";
			NextDiag.TempNode = "AfterMeet";
			bOk = (sti(PChar.GenQuest.GhostShip.KillMe) > 0) || (sti(PChar.GenQuest.GhostShip.DeadByMe) > 0);
			if (bOk && !CheckAttribute(pchar, "GenQuest.GhostShip.NeedCoins"))
			{
				Link.l3 = StringFromKey("GhostShip_dialog_13");
				Link.l3.go = "GhostCapt";
			}
			if (GetCharacterItem(Pchar, "Coins") >= 666 && CheckAttribute(pchar, "GenQuest.GhostShip.NeedCoins"))
			{
				Link.l4 = StringFromKey("GhostShip_dialog_14", pchar);
				Link.l4.go = "quest_coin_2";
			}
		break;

		// корабль
		case "GhostCapt":
			NextDiag.TempNode = "AfterMeet";
			dialog.Text = StringFromKey("GhostShip_dialog_15");
			Link.l1 = StringFromKey("GhostShip_dialog_16");
			Link.l1.go = "GhostCapt_1";
		break;

		case "GhostCapt_1":
			dialog.Text = StringFromKey("GhostShip_dialog_17");
			Link.l1 = StringFromKey("GhostShip_dialog_18");
			Link.l1.go = "GhostCapt_2";
		break;

		case "GhostCapt_2":
			dialog.Text = StringFromKey("GhostShip_dialog_19");
			Link.l1 = StringFromKey("GhostShip_dialog_20");
			Link.l1.go = "GhostCapt_3";
		break;

		case "GhostCapt_3":
			dialog.Text = StringFromKey("GhostShip_dialog_21");
			Link.l1 = StringFromKey("GhostShip_dialog_22");
			Link.l1.go = "GhostCapt_4";
		break;

		case "GhostCapt_4":
			dialog.Text = StringFromKey("GhostShip_dialog_23");
			Link.l1 = StringFromKey("GhostShip_dialog_24");
			Link.l1.go = "Exit";
			AddQuestRecord("GhostShipQuest", "5");
			PChar.GenQuest.GhostShip.NeedCoins = true;
			SetCurrentQuestMark(npchar); // обновим квест метку
			GhostShipQuest_NeedCoins_Mayor_AddQuestMarks();
			RemoveMapQuestMark("Shore9", "GhostShipQuest");
		break;

		case "quest_coin_2":
			dialog.Text = StringFromKey("GhostShip_dialog_25");
			Link.l1 = StringFromKey("GhostShip_dialog_26");
			Link.l1.go = "Exit";
			TakeNItems(pchar, "Coins", -666);
			AddQuestRecord("GhostShipQuest", "6");
			AddQuestUserData("GhostShipQuest", "sSex", GetSexPhrase("", "а"));
			PChar.GenQuest.GhostShip.LastBattle = true;
			NPChar.location = "none";
			NPChar.LifeDay = 0;
			NextDiag.TempNode = "temp_coins";
			RemoveLandQuestmarkToFantoms_Main("JohnDavy", "GhostShipQuest");
			GhostShipQuest_NeedCoins_Mayor_DelQuestMarks();
		break;

		case "temp_coins":
			dialog.Text = StringFromKey("GhostShip_dialog_27");
			Link.l1 = StringFromKey("GhostShip_dialog_28");
			Link.l1.go = "Exit";
			NextDiag.TempNode = "temp_coins";
		break;

		case "GhostCapt_Prize":
			dialog.text = StringFromKey("GhostShip_dialog_29", pchar);
			link.l1 = StringFromKey("GhostShip_dialog_30");
			link.l1.go = "GhostCapt_Prize1";
		break;

		case "GhostCapt_Prize1":
			dialog.text = StringFromKey("GhostShip_dialog_31");
			link.l1 = StringFromKey("GhostShip_dialog_32");
			link.l1.go = "GhostCapt_Prize2";
		break;

		case "GhostCapt_Prize2":
			dialog.text = StringFromKey("GhostShip_dialog_33", pchar);
			link.l1 = StringFromKey("GhostShip_dialog_34", pchar);
			link.l1.go = "GhostCapt_Prize3";
		break;

		case "GhostCapt_Prize3":
			dialog.text = StringFromKey("GhostShip_dialog_35");
			link.l1 = StringFromKey("GhostShip_dialog_36");
			link.l1.go = "GhostCapt_Prize4";
		break;
		/*
		case "GhostCapt_Prize4":
			dialog.text = "Го-го-го! Да ты и " + GetSexPhrase("сам", "сама") +" его не возьмёшь, не по зубам он тебе... Нет уж - это мой крест... А я, в качестве награды за отвагу, могу улучшить ходовые характеристики твоему судну. Выбирай, что пожелаешь.";
			link.l1 = "Для меня главное это скорость. Без неё любой корабль, как плавучая мишень.";
			link.l1.go = "GhostCapt_upgrade1";
			link.l2 = "Манёвренность в корабле - самое важное. С нею от любого бортового залпа увернуться можно.";
			link.l2.go = "GhostCapt_upgrade2";
			link.l3 = "По мне, так скорость в бейдевинд даёт кораблю главные преимущества. При хорошем ходе в бейдевинд для капитана нет плохого ветра, все пути открыты.";
			link.l3.go = "GhostCapt_upgrade3";
			link.l4 = "Благодарю, но мой кораблик меня вполне устраивает! Потопил же он твоего хвалёного 'Голландца'.";
			link.l4.go = "GhostCapt_noupgrade";
		break;
		
		case "GhostCapt_upgrade1":
			dialog.text = "Ну, как пожелаешь, скорость - так скорость.\nЛадно, пора мне. Я и так у тебя засиделся. Редко, знаешь ли, доводится вот так с живым человеком посудачить... И это... если будешь на западном Мейне, найди там, в деревушке ловцов жемчуга Белого Мальчика - передай привет...";
			link.l1 = "Что так и сказать, мол привет тебе от покойного капитана 'Летучего Голландца', мистера Ван дер Декена?";
			link.l1.go = "GhostCapt_Prize5";	
			shTo = &RealShips[sti(pchar.Ship.Type)];
			shTo.Tuning.GhostShip = true;
			GetBaseShipParam_ToUpgrade(shTo, "SpeedRate");
		break;

		case "GhostCapt_upgrade2":
			dialog.text = "Ну, как пожелаешь, манёвренность - так манёвренность.\nЛадно, пора мне. Я и так у тебя засиделся. Редко, знаешь ли, доводится вот так с живым человеком посудачить... И это... если будешь на западном Мейне, найди там, в деревушке ловцов жемчуга Белого Мальчика - передай привет...";
			link.l1 = "Что так и сказать, мол привет тебе от покойного капитана 'Летучего Голландца', мистера Ван дер Декена?";
			link.l1.go = "GhostCapt_Prize5";				
			shTo = &RealShips[sti(pchar.Ship.Type)];			
			shTo.Tuning.GhostShip = true;
			GetBaseShipParam_ToUpgrade(shTo, "TurnRate");
		break;		
		
		case "GhostCapt_upgrade3":
			dialog.text = "Ну, как пожелаешь, бейдевинд - так бейдевинд.\nЛадно, пора мне. Я и так у тебя засиделся. Редко, знаешь ли, доводится вот так с живым человеком посудачить... И это... если будешь на западном Мейне, найди там, в деревушке ловцов жемчуга Белого Мальчика - передай привет...";
			link.l1 = "Что так и сказать, мол привет тебе от покойного капитана 'Летучего Голландца', мистера Ван дер Декена?";
			link.l1.go = "GhostCapt_Prize5";					
			shTo = &RealShips[sti(pchar.Ship.Type)];
			shTo.Tuning.GhostShip = true;
			GetBaseShipParam_ToUpgrade(shTo, "WindAgainstSpeed");
		break;		
		
		case "GhostCapt_noupgrade":
			dialog.text = "Ишь " + GetSexPhrase("какой", "какая") +"! " + GetSexPhrase("Расхрабрился", "Расхрабрилась") +". Говорю же - повезло тебе, "+ GetSexPhrase("сосунку","соплячке") +". Я вот своим канонирам-то хвосты понакручу, в другой раз одним бортовым на дно отправлю!..\nЛадно, пора мне. Я и так у тебя засиделся. Редко, знаешь ли, доводится вот так с живым человеком посудачить... "+
				"И это... если будешь на западном Мейне, найди там, в деревушке ловцов жемчуга Белого Мальчика - передай привет...";
			link.l1 = "Что так и сказать, мол привет тебе от покойного капитана 'Летучего Голландца', мистера Ван-дер-Декена?";	
			link.l1.go = "GhostCapt_Prize5";
		break;
		
		case "GhostCapt_Prize5":
			dialog.text = "Хм, действительно... ладно, не нужно ничего... Если суждено сбыться, то и без привета сбудется... Прощай... Да не попадайся мне больше - в другой раз не спущу...";
			link.l1 = "" + GetSexPhrase("Рад", "Рада") + " " + GetSexPhrase("был", "была") +" знакомству с легендарным капитаном.";
			link.l1.go = "GhostCapt_PrizeExit";
		break;
		*/
		case "GhostCapt_Prize4":
			dialog.text = StringFromKey("GhostShip_dialog_37");
			link.l1 = StringFromKey("GhostShip_dialog_38", pchar);
			link.l1.go = "GhostCapt_PrizeExit";
		break;

		case "GhostCapt_PrizeExit":
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "GhostShipCapInCabinDied", -1);
			LAi_LockFightMode(pchar, false);
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true;
			SetCharacterPerk(pchar, "GhostsGift");
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;

		case "GhostCapt_LastDialog":
			dialog.text = StringFromKey("GhostShip_dialog_39", pchar);
			link.l1 = StringFromKey("GhostShip_dialog_40", pchar);
			link.l1.go = "GhostCapt_LastDialog1";
		break;

		case "GhostCapt_LastDialog1":
			dialog.text = StringFromKey("GhostShip_dialog_41", pchar);
			link.l1 = StringFromKey("GhostShip_dialog_42", pchar);
			link.l1.go = "GhostCapt_LastDialog2";
		break;

		case "GhostCapt_LastDialog2":
			dialog.text = StringFromKey("GhostShip_dialog_43", pchar);
			link.l1 = StringFromKey("GhostShip_dialog_44");
			link.l1.go = "GhostCapt_LastDialog3";
		break;

		case "GhostCapt_LastDialog3":
			NPChar.KeepItems.recipe_fulminate_silver = "1";
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	}
}
/*
void GetBaseShipParam_ToUpgrade(ref shTo, string param)
{
	string sAttr = "Bonus_"+param;
	int iRealShipType = sti(shTo.basetype);
	string sParam =	GetBaseShipParamFromType(iRealShipType, param);
	float paramValue = 1.1 * stf(sParam)/5.0;
	if(CheckAttribute(shTo, sAttr))
	{
		shTo.(param) = stf(shTo.(param)) - stf(shTo.(sAttr));
		shTo.(sAttr) = stf(shTo.(sAttr)) + paramValue;
		shTo.(param) = stf(shTo.(param)) + stf(shTo.(sAttr));
	}
	else
	{
		shTo.(sAttr) = paramValue;
		shTo.(param) = stf(shTo.(param)) + stf(shTo.(sAttr));
	}	
}
*/