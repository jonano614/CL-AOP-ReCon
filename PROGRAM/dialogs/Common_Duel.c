//navy 26.07.06
//генератор дуэлей...
//в диалоге НПС делаем линк с проверкой флага оскорбления... по нему переход на "outraged"
//если НПС сделал что-то ГГ (продажа фальшивки) или ГГ наехал на НПС, вешаем на него флаг.
//для некоторых, например ПГГ, можно делать переход сразу на вызов: "let_s_duel"
void ProcessDuelDialog(ref NPChar, aref Link, aref NextDiag)
{
	int iHour;
	string sLocation;

	//флаг убираем
	DeleteAttribute(NPChar, "Outrage");
	switch (Dialog.CurrentNode)
	{
		case "outraged":
			Dialog.Text = NPCharRepPhrase(NPChar,
					StringFromKey("Common_Duel_3", RandSwear(), RandPhraseSimple(
							StringFromKey("Common_Duel_1", pchar),
							StringFromKey("Common_Duel_2"))),
					StringFromKey("Common_Duel_6", RandPhraseSimple(
							StringFromKey("Common_Duel_4", GetAddress_Form(NPChar)),
							StringFromKey("Common_Duel_5"))));

			//это такая засада.. чтобы читали текст
			MakeRandomLinkOrderTwo(link,
					NPCharRepPhrase(pchar,
						StringFromKey("Common_Duel_9", RandPhraseSimple(
								StringFromKey("Common_Duel_7"),
								StringFromKey("Common_Duel_8"))),
						StringFromKey("Common_Duel_12", RandPhraseSimple(
								StringFromKey("Common_Duel_10"),
								StringFromKey("Common_Duel_11", pchar)))), "outraged_1",
					NPCharRepPhrase(pchar,
						StringFromKey("Common_Duel_15", RandSwear(), RandPhraseSimple(
								StringFromKey("Common_Duel_13", pchar),
								StringFromKey("Common_Duel_14", pchar))),
						StringFromKey("Common_Duel_18", RandPhraseSimple(
								StringFromKey("Common_Duel_16"),
								StringFromKey("Common_Duel_17", pchar, GetAddress_FormToNPC(NPChar))))), "change_mind");
		break;

		case "outraged_1":
			Dialog.Text = NPCharRepPhrase(NPChar,
					StringFromKey("Common_Duel_21", RandPhraseSimple(
							StringFromKey("Common_Duel_19"),
							StringFromKey("Common_Duel_20"))),
					StringFromKey("Common_Duel_24", RandPhraseSimple(
							StringFromKey("Common_Duel_22"),
							StringFromKey("Common_Duel_23"))));

			MakeRandomLinkOrderTwo(link,
					NPCharRepPhrase(pchar,
						StringFromKey("Common_Duel_27", RandSwear(), RandPhraseSimple(
								StringFromKey("Common_Duel_25"),
								StringFromKey("Common_Duel_26"))),
						StringFromKey("Common_Duel_30", RandPhraseSimple(
								StringFromKey("Common_Duel_28"),
								StringFromKey("Common_Duel_29")))), "let_s_duel",
					NPCharRepPhrase(pchar,
						StringFromKey("Common_Duel_33", RandPhraseSimple(
								StringFromKey("Common_Duel_31", pchar),
								StringFromKey("Common_Duel_32"))),
						StringFromKey("Common_Duel_36", RandPhraseSimple(
								StringFromKey("Common_Duel_34", pchar),
								StringFromKey("Common_Duel_35")))), "change_mind");
		break;

		case "let_s_duel":
		//проверка на начатые дуэли
			if (CheckAttribute(PChar, "questTemp.duel.Start") && sti(PChar.questTemp.duel.Start))
			{
				Dialog.Text = StringFromKey("Common_Duel_37");
				if (PChar.questTemp.duel.enemy == NPChar.id)
				{
					Dialog.Text = StringFromKey("Common_Duel_38");
				}
				link.l1 = StringFromKey("Common_Duel_39", pchar, RandSwear());
				link.l1.go = "exit";
				break;
			}
			//может отказаться
			if (rand(100) < 30)
			{
				Dialog.Text = StringFromKey("Common_Duel_42", RandPhraseSimple(
							StringFromKey("Common_Duel_40"),
							StringFromKey("Common_Duel_41")));
				link.l1 = StringFromKey("Common_Duel_45", RandPhraseSimple(
							StringFromKey("Common_Duel_43"),
							StringFromKey("Common_Duel_44")));
				link.l1.go = "exit";

				//можно дать возможность драться полюбому
				if (rand(100) < 30 || npchar.dialog.filename == "Smuggler_Treasure_dialog.c")
				{
					link.l1 = StringFromKey("Common_Duel_48", RandPhraseSimple(
								StringFromKey("Common_Duel_46"),
								StringFromKey("Common_Duel_47")));
					link.l1.go = "fight_right_now";
				}
				break;
			}

			//согласен.
			Dialog.Text = StringFromKey("Common_Duel_51", RandPhraseSimple(
						StringFromKey("Common_Duel_49"),
						StringFromKey("Common_Duel_50")));
			link.l1 = StringFromKey("Common_Duel_54", RandPhraseSimple(
						StringFromKey("Common_Duel_52"),
						StringFromKey("Common_Duel_53", npchar)));
			link.l1.go = "land_duel";
			if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
			{
				Dialog.Text = StringFromKey("Common_Duel_57", RandPhraseSimple(
							StringFromKey("Common_Duel_55", Dialog.Text),
							StringFromKey("Common_Duel_56")));
				link.l2 = StringFromKey("Common_Duel_60", RandPhraseSimple(
							StringFromKey("Common_Duel_58"),
							StringFromKey("Common_Duel_59")));
				link.l2.go = "sea_duel";
			}
			link.l3 = StringFromKey("Common_Duel_61", pchar);
			link.l3.go = "change_mind";
		break;

		//дуэль на подводных лодках
		case "sea_duel":
			Dialog.Text = StringFromKey("Common_Duel_64", RandPhraseSimple(
						StringFromKey("Common_Duel_62"),
						StringFromKey("Common_Duel_63")));
			link.l1 = StringFromKey("Common_Duel_67", RandPhraseSimple(
						StringFromKey("Common_Duel_65"),
						StringFromKey("Common_Duel_66")));
			link.l1.go = "exit";
			if (pchar.location.from_sea == GetCurrentTown() + "_town")
			{
				Dialog.Text = StringFromKey("Common_Duel_68");
				link.l1 = StringFromKey("Common_Duel_69");

				pchar.questTemp.Duel.enemy = NPChar.id;
				pchar.questTemp.Duel.Sea_Location = Islands[GetCharacterCurrentIsland(PChar)].id;
				AddDialogExitQuestFunction("Duel_Sea_Prepare");
			}
		break;

		//на суше
		case "land_duel":
			iHour = 1 + rand(2);
			if (GetTime() > 4.0 && GetTime() < 17.0)
			{
				//			iHour = MakeInt(18.0 - GetTime()) + rand(2); //раскоментировать для дуэлей только по ночам
			}
			pchar.questTemp.Duel.WaitTime = iHour;
			Dialog.Text = StringFromKey("Common_Duel_72", RandSwear(), RandPhraseSimple(
						StringFromKey("Common_Duel_70"),
						StringFromKey("Common_Duel_71")));
			link.l1 = StringFromKey("Common_Duel_75", RandPhraseSimple(
						StringFromKey("Common_Duel_73", iHour),
						StringFromKey("Common_Duel_74", iHour)));
			link.l1.go = "fight_off_town";
			link.l2 = StringFromKey("Common_Duel_78", RandPhraseSimple(
						StringFromKey("Common_Duel_76"),
						StringFromKey("Common_Duel_77")));
			link.l2.go = "fight_right_now";
			link.l3 = StringFromKey("Common_Duel_79");
			link.l3.go = "change_mind";

			if (rand(1))
			{
				Dialog.Text = StringFromKey("Common_Duel_82", RandSwear(), RandPhraseSimple(
							StringFromKey("Common_Duel_80", pchar.questTemp.Duel.WaitTime),
							StringFromKey("Common_Duel_81", pchar.questTemp.Duel.WaitTime)));
				link.l1 = StringFromKey("Common_Duel_85", RandPhraseSimple(
							StringFromKey("Common_Duel_83"),
							StringFromKey("Common_Duel_84")));
				link.l1.go = "fight_right_now";
				link.l2 = StringFromKey("Common_Duel_88", RandPhraseSimple(
							StringFromKey("Common_Duel_86"),
							StringFromKey("Common_Duel_87", npchar)));
				link.l2.go = "fight_off_town_prep";
			}
		break;

		//предложение "пойдём выйдем" рассматривается
		case "fight_off_town":
			Dialog.Text = StringFromKey("Common_Duel_91", RandPhraseSimple(
						StringFromKey("Common_Duel_89"),
						StringFromKey("Common_Duel_90")));
			link.l1 = StringFromKey("Common_Duel_94", RandPhraseSimple(
						StringFromKey("Common_Duel_92"),
						StringFromKey("Common_Duel_93")));
			link.l1.go = "fight_right_now";
			if (rand(1))
			{
				Dialog.Text = StringFromKey("Common_Duel_97", RandPhraseSimple(
							StringFromKey("Common_Duel_95"),
							StringFromKey("Common_Duel_96")));
				link.l1 = StringFromKey("Common_Duel_100", RandPhraseSimple(
							StringFromKey("Common_Duel_98"),
							StringFromKey("Common_Duel_99")));
				link.l1.go = "fight_off_town_prep";
			}
		break;

		//что ж, пойдём выйдем
		case "fight_off_town_prep":
			SaveCurrentQuestDateParam("questTemp.Duel.StartTime");
			PChar.questTemp.duel.Start = true;
			PChar.questTemp.duel.enemy = NPChar.id;
			sLocation = GetCurrentTown();
			if (sLocation != "")
			{
				//где?
				sLocation += "_ExitTown";
				pchar.questTemp.duel.place = sLocation;

				Locations[FindLocation(sLocation)].DisableEncounters = true;
				//приходит ко времени.
				pchar.quest.duel_move_opponent2place.win_condition.l1 = "Location";
				pchar.quest.duel_move_opponent2place.win_condition.l1.location = pchar.questTemp.duel.place;
				pchar.quest.duel_move_opponent2place.function = "Duel_Move_Opponent2Place";
				LAi_LocationDisableOfficersGen(pchar.questTemp.duel.place, true); //не пускаем офицеров
				//на случай, если не дождется, часа вполне достаточно
				SetTimerConditionParamFunction("duel_move_opponentBack", "Duel_Move_OpponentBack", 0, 0, 0, sti(GetTime() + 0.5) + sti(pchar.questTemp.Duel.WaitTime) + 1, false);
				if (CheckAttribute(NPChar, "CityType"))
				{
					DeleteAttribute(NPChar, "City"); // чтоб не было ругани с нацией
					DeleteAttribute(NPChar, "CityType");
				}
				if (!CheckAttribute(NPChar, "PGGAi"))
				{
					if (!CheckAttribute(NPChar, "LifeDay")) npchar.LifeDay = 0;
					npchar.LifeDay = sti(npchar.LifeDay) + 3; // чтоб до дуэли не помер
				}
				else if (sti(npchar.PGGAi.IsPGG)) //чтобы в таверну не вернулся, а то может
				{
					npchar.BackUp.town = npchar.PGGAi.location.town;
					npchar.PGGAi.location.town = "none";
				}
				npchar.BackUp.location = npchar.location;
				npchar.BackUp.location.group = npchar.location.group;
				npchar.BackUp.location.locator = npchar.location.locator;
				npchar.BackUp.DialogNode = npchar.Dialog.CurrentNode;
			}
			NextDiag.CurrentNode = "let_s_duel";
			DialogExit();
		break;

		//последнее слово перед боем
		case "talk_off_town":
			Dialog.Text = StringFromKey("Common_Duel_101", pchar);
			link.l1 = StringFromKey("Common_Duel_102");
			link.l1.go = "fight_right_now";
			link.l2 = StringFromKey("Common_Duel_103", pchar);
			link.l2.go = "change_mind";
			if (rand(100) < 20)
			{
				Dialog.Text = StringFromKey("Common_Duel_106", RandPhraseSimple(
							StringFromKey("Common_Duel_104", npchar),
							StringFromKey("Common_Duel_105", pchar)));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Common_Duel_109", RandPhraseSimple(
								StringFromKey("Common_Duel_107"),
								StringFromKey("Common_Duel_108"))),
						StringFromKey("Common_Duel_112", RandPhraseSimple(
								StringFromKey("Common_Duel_110"),
								StringFromKey("Common_Duel_111"))));
				link.l1.go = "fight_right_now";
				link.l2 = NPCharRepPhrase(pchar,
						StringFromKey("Common_Duel_115", RandPhraseSimple(
								StringFromKey("Common_Duel_113", pchar),
								StringFromKey("Common_Duel_114"))),
						StringFromKey("Common_Duel_118", RandPhraseSimple(
								StringFromKey("Common_Duel_116"),
								StringFromKey("Common_Duel_117"))));
				link.l2.go = "peace";
			}
			NextDiag.TempNode = npchar.BackUp.DialogNode;
			pchar.questTemp.Duel.End = true;
		break;

		//дуэли быть!
		case "fight_right_now":
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight_right_now_1":
			PChar.questTemp.duel.enemy = NPChar.id;
			PChar.questTemp.duel.enemyQty = rand(2) + 1;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//передумал, э... не хорошо
		case "change_mind":
			if (CheckAttribute(pchar, "questTemp.Duel.End")) LAi_SetWarriorType(NPChar);
			Dialog.Text = NPCharRepPhrase(NPChar,
					StringFromKey("Common_Duel_121", RandSwear(), RandPhraseSimple(
							StringFromKey("Common_Duel_119"),
							StringFromKey("Common_Duel_120"))),
					StringFromKey("Common_Duel_124", RandPhraseSimple(
							StringFromKey("Common_Duel_122"),
							StringFromKey("Common_Duel_123", npchar))));
			link.l1 = StringFromKey("Common_Duel_125");
			link.l1.go = "peace";
		break;

		case "after_peace":
			Dialog.Text = NPCharRepPhrase(NPChar,
					StringFromKey("Common_Duel_128", RandSwear(), RandPhraseSimple(
							StringFromKey("Common_Duel_126"),
							StringFromKey("Common_Duel_127"))),
					StringFromKey("Common_Duel_131", RandPhraseSimple(
							StringFromKey("Common_Duel_129"),
							StringFromKey("Common_Duel_130"))));
			link.l1 = StringFromKey("Common_Duel_132");
			link.l1.go = "peace";
		break;

		//мир и все такое.
		case "peace":
			LAi_SetWarriorType(NPChar);
			NextDiag.CurrentNode = "after_peace";
			DialogExit();
		break;
	}
}
