void ProcessDialogEvent()
{
	ref NPChar, Gover;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// Проверяем владение городом -->
	int iTest, iGover;
	iTest = FindColony(NPChar.City);
	ref rColony;
	if (iTest != -1) rColony = GetColonyByIndex(iTest);
	if (CheckAttribute(rColony, "OfficerIdx"))
	{
		iGover = rColony.OfficerIdx; //Индекс наместника
		makeref(Gover, characters[iGover]);
	}
	// Проверяем владение городом <--

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit_Refuse":
			NPChar.quest.refused = 1;
			NextDiag.CurrentNode = "ResWoman";
			DialogExit();
		break;

		case "Exit_Affraid":
			NPChar.LifeDay = 0;
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1); //LAi_FindNearestFreeLocator
			ChangeCharacterReputation(pchar, -10);
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(npchar, pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------------- служанка в резиденции ---------------------------------
		case "ResWoman":
			NextDiag.TempNode = "ResWoman";
			if (LAi_grp_playeralarm > 0 && sti(rColony.HeroOwn) != true)
			{
				dialog.text = StringFromKey("Residence_dialog_3", RandPhraseSimple(
							StringFromKey("Residence_dialog_1"),
							StringFromKey("Residence_dialog_2", pchar)));
				link.l1 = StringFromKey("Residence_dialog_6", RandPhraseSimple(
							StringFromKey("Residence_dialog_4"),
							StringFromKey("Residence_dialog_5")));
				link.l1.go = "exit_setOwner";
				break;
			}
			if (isBadReputation(pchar, 40) && sti(rColony.HeroOwn) != true)
			{
				dialog.text = StringFromKey("Residence_dialog_10", LinkRandPhrase(
							StringFromKey("Residence_dialog_7", pchar, GetAddress_Form(NPChar)),
							StringFromKey("Residence_dialog_8", pchar),
							StringFromKey("Residence_dialog_9", XI_ConvertString("Colony" + npchar.city + "Gen"))));
				link.l1 = StringFromKey("Residence_dialog_13", RandPhraseSimple(
							StringFromKey("Residence_dialog_11"),
							StringFromKey("Residence_dialog_12")));
				link.l1.go = "exit";
				break;
			}
			if (sti(rColony.HeroOwn) != true)
			{
				dialog.text = StringFromKey("Residence_dialog_17", LinkRandPhrase(
							StringFromKey("Residence_dialog_14", GetFullName(NPChar)),
							StringFromKey("Residence_dialog_15", GetAddress_Form(NPChar)),
							StringFromKey("Residence_dialog_16", GetAddress_Form(NPChar))));
				link.l1 = StringFromKey("Residence_dialog_20", RandPhraseSimple(
							StringFromKey("Residence_dialog_18"),
							StringFromKey("Residence_dialog_19")));
				link.l1.go = "exit";
				break;
			}
			// Rosarak. Далее в отдельных случаях вместо GetAddress_Form мы сразу используем обращение "сэр", так как оно по умолчанию используется для пиратской нации.
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = StringFromKey("Residence_dialog_23", RandPhraseSimple(
							StringFromKey("Residence_dialog_21"),
							StringFromKey("Residence_dialog_22", pchar)));
				link.l1 = StringFromKey("Residence_dialog_26", RandPhraseSimple(
							StringFromKey("Residence_dialog_24"),
							StringFromKey("Residence_dialog_25")));
				link.l1.go = "Exit";
				break;
			}
			if (npchar.quest.meeting == 0)
			{
				npchar.quest.meeting = 1;
				dialog.text = StringFromKey("Residence_dialog_27", pchar, pchar.lastname, GetFullName(NPChar));
				link.l1 = StringFromKey("Residence_dialog_30", TimeGreeting(), NPChar.name, RandPhraseSimple(
							StringFromKey("Residence_dialog_28"),
							StringFromKey("Residence_dialog_29")));
				link.l1.go = "ResWoman";
				break;
			}
			dialog.text = StringFromKey("Residence_dialog_31", pchar);
			if (CheckAttribute(loadedLocation, "Bedroom"))
			{
				link.l2 = StringFromKey("Residence_dialog_32", pchar);
				link.l2.go = "Sleep";
				link.l3 = StringFromKey("Residence_dialog_33"); //в будущем добавим всякие мелкие просьбы, вроде найти вина
				link.l3.go = "Orders";
			}
			if (!HasSubStr(npchar.model, "oldWoman"))
			{
				link.l1 = StringFromKey("Residence_dialog_36", RandPhraseSimple(
							StringFromKey("Residence_dialog_34", pchar),
							StringFromKey("Residence_dialog_35")));
				link.l1.go = "exit";
			}
			else
			{
				//Со старухой не флиртуем
				link.l1 = StringFromKey("Residence_dialog_39", RandPhraseSimple(
							StringFromKey("Residence_dialog_37"),
							StringFromKey("Residence_dialog_38")));
				link.l1.go = "exit";
			}
		/*
		if()
		{
			Попросить выйти из комнаты, чтобы остаться там с данькой. Если пусто, то её можно позвать через мысли вслух.

		}
		*/
		break;
		case "Sleep":
			dialog.text = StringFromKey("Residence_dialog_42", RandPhraseSimple(
						StringFromKey("Residence_dialog_40"),
						StringFromKey("Residence_dialog_41")));
			if (!isDay())
			{
				link.l1 = StringFromKey("Residence_dialog_43");
				link.l1.go = "Sleep_day";
				link.l2 = StringFromKey("Residence_dialog_44");
				link.l2.go = "exit";
			}
			else
			{
				link.l1 = StringFromKey("Residence_dialog_45");
				link.l1.go = "Sleep_day";
				link.l2 = StringFromKey("Residence_dialog_46", pchar);
				link.l2.go = "Sleep_night";
				link.l3 = StringFromKey("Residence_dialog_47");
				link.l3.go = "exit";
			}
		break;
		case "Sleep_day":
			dialog.text = StringFromKey("Residence_dialog_48", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Residence_dialog_49");
			link.l1.go = "room_day_wait";
			link.l2 = StringFromKey("Residence_dialog_50", pchar);
			link.l2.go = "exit";
		break;
		case "Sleep_night":
			dialog.text = StringFromKey("Residence_dialog_51", pchar);
			link.l1 = StringFromKey("Residence_dialog_52");
			link.l1.go = "room_night_wait";
			link.l2 = StringFromKey("Residence_dialog_53", pchar);
			link.l2.go = "exit";
		break;
		case "room_day_wait":
			DialogExit();
			NextDiag.TempNode = "ResWoman";
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate("wait_day");
			AddDialogExitQuest("royal_sleep");
		break;
		case "room_night_wait":
			DialogExit();
			NextDiag.TempNode = "ResWoman";
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate("wait_night");
			AddDialogExitQuest("royal_sleep");
		break;
		case "Orders":
			dialog.text = StringFromKey("Residence_dialog_56", RandPhraseSimple(
						StringFromKey("Residence_dialog_54"),
						StringFromKey("Residence_dialog_55")));
			if (pchar.sex == "man" && !HasSubStr(npchar.model, "oldWoman") && GetNpcQuestPastTimeParam(npchar, "sex") >= 12 && !CheckAttribute(npchar, "quest.refused"))
			{
				link.l1 = PcharRepPhrase(
							StringFromKey("Residence_dialog_57"),
							StringFromKey("Residence_dialog_58"));
				link.l1.go = "Sex";
			}
			link.l2 = StringFromKey("Residence_dialog_61", RandPhraseSimple(
						StringFromKey("Residence_dialog_59", pchar),
						StringFromKey("Residence_dialog_60")));
			link.l2.go = "exit";
		break;
		case "Sex": //При npchar.city == SanJuan не хватает дополнительных реплик про Изабеллу, ведь служанка явно осведомлена о жене губернатора, если она есть.
			if (npchar.relations == 1 || CheckAttribute(npchar, "quest.fucked")) //Шанс успеха 75%, а если уже было, то не станет отказываться
			{
				dialog.text = PcharRepPhrase(
							StringFromKey("Residence_dialog_64", RandPhraseSimple(
									StringFromKey("Residence_dialog_62"),
									StringFromKey("Residence_dialog_63"))),
							StringFromKey("Residence_dialog_67", RandPhraseSimple(
									StringFromKey("Residence_dialog_65"),
									StringFromKey("Residence_dialog_66"))));
				link.l1 = PcharRepPhrase(
							StringFromKey("Residence_dialog_70", RandPhraseSimple(
									StringFromKey("Residence_dialog_68"),
									StringFromKey("Residence_dialog_69"))),
							StringFromKey("Residence_dialog_73", RandPhraseSimple(
									StringFromKey("Residence_dialog_71"),
									StringFromKey("Residence_dialog_72"))));
				link.l1.go = "MakeSex";
				break;
			}
			if (npchar.relations == 2 && CheckAttribute(rColony, "OfficerIdx") && gover.sex != "woman") //Если мутки с наместником-мужиком
			{
				dialog.text = StringFromKey("Residence_dialog_76", RandPhraseSimple(
							StringFromKey("Residence_dialog_74", UpperFirst(GetAddress_Form(NPChar)), gover.lastname),
							StringFromKey("Residence_dialog_75", gover.lastname)));
				link.l1 = StringFromKey("Residence_dialog_77", gover.lastname);
				link.l1.go = "LittleSecret";
				link.l2 = StringFromKey("Residence_dialog_78");
				link.l2.go = "Exit_Refuse";
			}
			else
			{
				dialog.text = StringFromKey("Residence_dialog_81", RandPhraseSimple(
							StringFromKey("Residence_dialog_79"),
							StringFromKey("Residence_dialog_80")));
				link.l1 = StringFromKey("Residence_dialog_84", RandPhraseSimple(
							StringFromKey("Residence_dialog_82"),
							StringFromKey("Residence_dialog_83")));
				link.l1.go = "Pressure";
				link.l2 = StringFromKey("Residence_dialog_85");
				link.l2.go = "Exit_Refuse";
			}
		break;
		case "Pressure":
			dialog.text = StringFromKey("Residence_dialog_88", RandPhraseSimple(
						StringFromKey("Residence_dialog_86"),
						StringFromKey("Residence_dialog_87")));
			link.l1 = StringFromKey("Residence_dialog_91", RandPhraseSimple(
						StringFromKey("Residence_dialog_89"),
						StringFromKey("Residence_dialog_90")));
			link.l1.go = "Exit_Affraid";
			link.l2 = StringFromKey("Residence_dialog_92");
			link.l2.go = "Exit_Refuse";
		break;
		case "LittleSecret":
		// if(rand(3) == 0) gover.loyality = makeint(gover.loyality) - 5; //25% наместник не будет воодушевлён делёжкой его крали
			if (rand(3) == 0) ChangeCharacterLoyality(gover, -5); //25% наместник не будет воодушевлён делёжкой его крали
			dialog.text = StringFromKey("Residence_dialog_95", RandPhraseSimple(
						StringFromKey("Residence_dialog_93"),
						StringFromKey("Residence_dialog_94")));
			link.l1 = PcharRepPhrase(
						StringFromKey("Residence_dialog_98", RandPhraseSimple(
								StringFromKey("Residence_dialog_96"),
								StringFromKey("Residence_dialog_97"))),
						StringFromKey("Residence_dialog_101", RandPhraseSimple(
								StringFromKey("Residence_dialog_99"),
								StringFromKey("Residence_dialog_100"))));
			link.l1.go = "MakeSex";
		break;
		case "MakeSex":
			SaveCurrentNpcQuestDateParam(npchar, "sex"); //Сохраняем дату секса, чтобы не предлагать слишком часто (12 часов перерыв)
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; //Счетчик для Данек (в будущем не потребуется)
			if (rand(4) == 0) pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //20% шанс, что до Изабеллы дойдут вести об измене
			AddCharacterHealth(pchar, 4);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			NextDiag.CurrentNode = "AfterSex";
			AddDialogExitQuest("PlaySex_1");
			DialogExit();
		break;
		case "AfterSex":
			NextDiag.TempNode = "ResWoman";
			npchar.quest.fucked = 1;
			if (LAi_grp_playeralarm > 0) //Если испугал после секса, даже не поговорив
			{
				dialog.text = StringFromKey("Residence_dialog_104", RandPhraseSimple(
							StringFromKey("Residence_dialog_102"),
							StringFromKey("Residence_dialog_103")));
				link.l1 = StringFromKey("Residence_dialog_107", RandPhraseSimple(
							StringFromKey("Residence_dialog_105"),
							StringFromKey("Residence_dialog_106")));
				link.l1.go = "Exit";
				break;
			}
			dialog.text = StringFromKey("Residence_dialog_110", RandPhraseSimple(
						StringFromKey("Residence_dialog_108"),
						StringFromKey("Residence_dialog_109", pchar.name)));
			link.l1 = StringFromKey("Residence_dialog_113", RandPhraseSimple(
						StringFromKey("Residence_dialog_111"),
						StringFromKey("Residence_dialog_112")));
			link.l1.go = "exit";
		break;
		case "Woman_FackYou":
			NextDiag.TempNode = "ResWoman";
			dialog.text = StringFromKey("Residence_dialog_114");
			link.l1 = StringFromKey("Residence_dialog_115");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- слуга в резиденции ---------------------------------
		case "ResMan":
			NextDiag.TempNode = "ResMan";
			if (isBadReputation(pchar, 40) && sti(rColony.HeroOwn) != true)
			{
				dialog.text = StringFromKey("Residence_dialog_119", LinkRandPhrase(
							StringFromKey("Residence_dialog_116", pchar),
							StringFromKey("Residence_dialog_117", pchar),
							StringFromKey("Residence_dialog_118", XI_ConvertString("Colony" + npchar.city + "Gen"))));
				link.l1 = StringFromKey("Residence_dialog_122", RandPhraseSimple(
							StringFromKey("Residence_dialog_120"),
							StringFromKey("Residence_dialog_121")));
				link.l1.go = "exit";
				break;
			}
			if (sti(rColony.HeroOwn) != true)
			{
				dialog.text = StringFromKey("Residence_dialog_126", LinkRandPhrase(
							StringFromKey("Residence_dialog_123", GetFullName(NPChar)),
							StringFromKey("Residence_dialog_124", GetAddress_Form(NPChar)),
							StringFromKey("Residence_dialog_125", GetAddress_Form(NPChar))));
				link.l1 = StringFromKey("Residence_dialog_129", RandPhraseSimple(
							StringFromKey("Residence_dialog_127"),
							StringFromKey("Residence_dialog_128")));
				link.l1.go = "exit";
			}
			else // Rosarak. Временная заглушка, пока я не дописал нормальные реплики
			{
				dialog.text = StringFromKey("Residence_dialog_132", RandPhraseSimple(
							StringFromKey("Residence_dialog_130", GetFullName(NPChar)),
							StringFromKey("Residence_dialog_131")));
				link.l1 = StringFromKey("Residence_dialog_135", RandPhraseSimple(
							StringFromKey("Residence_dialog_133"),
							StringFromKey("Residence_dialog_134")));
				link.l1.go = "exit";
			}
		break;
		case "Man_FackYou":
			if (npchar.greeting == "guardHouse") NextDiag.TempNode = "ResGuard";
			else NextDiag.TempNode = "ResMan";
			dialog.text = StringFromKey("Residence_dialog_136", pchar);
			link.l1 = StringFromKey("Residence_dialog_137");
			link.l1.go = "fight";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- солдат в резиденции ---------------------------------
		case "ResGuard":
			NextDiag.TempNode = "ResGuard";
			if (isBadReputation(pchar, 40) && sti(rColony.HeroOwn) != true)
			{
				dialog.text = StringFromKey("Residence_dialog_141", LinkRandPhrase(
							StringFromKey("Residence_dialog_138", pchar),
							StringFromKey("Residence_dialog_139"),
							StringFromKey("Residence_dialog_140", pchar, XI_ConvertString("Colony" + npchar.city + "Gen"))));
				link.l1 = StringFromKey("Residence_dialog_144", RandPhraseSimple(
							StringFromKey("Residence_dialog_142"),
							StringFromKey("Residence_dialog_143")));
				link.l1.go = "exit";
				break;
			}
			if (sti(rColony.HeroOwn) != true)
			{
				dialog.text = StringFromKey("Residence_dialog_148", LinkRandPhrase(
							StringFromKey("Residence_dialog_145"),
							StringFromKey("Residence_dialog_146", GetAddress_Form(NPChar)),
							StringFromKey("Residence_dialog_147")));
				link.l1 = StringFromKey("Residence_dialog_151", RandPhraseSimple(
							StringFromKey("Residence_dialog_149"),
							StringFromKey("Residence_dialog_150")));
				link.l1.go = "exit";
			}
			else // Rosarak. Временная заглушка, пока я не дописал нормальные реплики
			{
				dialog.text = StringFromKey("Residence_dialog_154", RandPhraseSimple(
							StringFromKey("Residence_dialog_152", pchar),
							StringFromKey("Residence_dialog_153", GetAddress_Form(NPChar))));
				link.l1 = StringFromKey("Residence_dialog_157", RandPhraseSimple(
							StringFromKey("Residence_dialog_155"),
							StringFromKey("Residence_dialog_156")));
				link.l1.go = "exit";
			}
		break;
	}
}
