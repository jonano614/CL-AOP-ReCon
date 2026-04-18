// Эдвард Мэнсфилд, глава буканьеров и авторитетный пират
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// ============================================================================
	// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
	if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
	{
		npchar.angry.ok = 1;
		if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
		{
			NextDiag.TempNode = NextDiag.CurrentNode;
			Dialog.CurrentNode = "AngryExitAgain";
			npchar.angry.first = 1;
		}
		else
		{
			switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
			{
				case "repeat":
					if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
				break;
			}
		}
	}
	// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
	// ============================================================================
	switch (Dialog.CurrentNode)
	{
		case "Exit":
		//Если поговорили по делу - сбросим агр
			if (CheckAttribute(npchar, "quest.repeat.Firsttime")) DeleteAttribute(npchar, "quest.repeat.Firsttime");
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		case "ExitAgr":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "First time":
			NextDiag.TempNode = "First time";
			if (CheckAttribute(npchar, "Sp5LaVegaAttackDone"))
			{
				if (NPChar.quest.meeting == "0")
				{
					dialog.Text = StringFromKey("EdwardMansfield_1", TimeGreeting(), GetFullName(NPChar));
					Link.l1 = StringFromKey("EdwardMansfield_2", pchar, GetFullName(Pchar));
					Link.l1.go = "exit";
					NPChar.quest.meeting = "1";
				}
				else
				{
					dialog.Text = StringFromKey("EdwardMansfield_3", TimeGreeting());
					Link.l1 = StringFromKey("EdwardMansfield_4");
					Link.l1.go = "exit";
				}
				break; //fix
			}
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("EdwardMansfield_5", pchar),
						StringFromKey("EdwardMansfield_6"),
						StringFromKey("EdwardMansfield_7"),
						StringFromKey("EdwardMansfield_8", pchar), "repeat", 2, npchar, Dialog.CurrentNode);

			link.l1 = HeroStringReactionRepeat(
						StringFromKey("EdwardMansfield_9"),
						StringFromKey("EdwardMansfield_10", npchar.name),
						StringFromKey("EdwardMansfield_11", npchar.name),
						StringFromKey("EdwardMansfield_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "ExitAgr";
			if (sti(NPChar.quest.repeat.Firsttime) > 3) break; //fix

			if (CheckAttribute(pchar, "questTemp.Sharp") && StrStartsWith(pchar.questTemp.Sharp, "takeRumour"))
			{
				link.l2 = StringFromKey("EdwardMansfield_13");
				link.l2.go = "SharpPearl_1";
			}
			//Английская линейка
			if (CheckAttribute(pchar, "QuestTemp.EngLine_Mansfield_task") && pchar.QuestTemp.EngLine_Mansfield_task == "EngLine_begin")
			{
				link.l3 = StringFromKey("EdwardMansfield_14", pchar);
				link.l3.go = "Step_1";
			}
			//Голландская линейка
			if (CheckAttribute(pchar, "QuestTemp.HolLine_Mansfield_task") && pchar.QuestTemp.HolLine_Mansfield_task == "WormEngPlans")
			{
				link.l4 = StringFromKey("EdwardMansfield_15", pchar);
				link.l4.go = "Step_H3_1";
			}

			if (CheckAttribute(PChar, "questTemp.pSQ_Bacchus") && CheckAttribute(PChar, "questTemp.pirateStartQuest"))
			{
				if (pchar.questTemp.pSQ_Bacchus == "to_Baron" && npchar.city == pchar.questTemp.pirateStartQuest.City && GetSquadronGoods(pchar, GOOD_SLAVES) >= 200)
				{
					link.l5 = StringFromKey("EdwardMansfield_16");
					link.l5.go = "pirateStartQuest_BacchusSlaves";
				}

				if (pchar.questTemp.pSQ_Bacchus == "to_Baron_noTalk" && npchar.city == pchar.questTemp.pirateStartQuest.City && GetSquadronGoods(pchar, GOOD_SLAVES) >= 200)
				{
					link.l5 = StringFromKey("EdwardMansfield_17");
					link.l5.go = "pirateStartQuest_BacchusSlaves_NoTalk";
				}
			}

			//if (Pchar.BaseNation == PIRATE) Доступно всем. Konstrush
			if (!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
			{
				link.l6 = StringFromKey("EdwardMansfield_18");
				link.l6.go = "pirateStartQuest";
			}
			else if (pchar.questTemp.pirateStartQuest == "0") break;
			else if (pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many") && npchar.city == pchar.questTemp.pirateStartQuest.City)
			{
				link.l6 = StringFromKey("EdwardMansfield_19", pchar);
				link.l6.go = "pirateStartQuest_many";
			}
			else if (pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "pirateStartQuest") > 0 && npchar.city == pchar.questTemp.pirateStartQuest.City)
			{
				link.l6 = StringFromKey("EdwardMansfield_20", pchar);
				link.l6.go = "pirateStartQuest_info_1";
			}
			else if (pchar.questTemp.pirateStartQuest == "5" && npchar.city == pchar.questTemp.pirateStartQuest.City)
			{
				link.l6 = StringFromKey("EdwardMansfield_21");
				link.l6.go = "pirateStartQuest_final";
			}
		break;

		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = StringFromKey("EdwardMansfield_22", pchar);
			link.l1 = StringFromKey("EdwardMansfield_23");
			link.l1.go = "pirateStartQuest_1";
			link.l2 = StringFromKey("EdwardMansfield_24");
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
			pirateStartQuest_Begin_DelQuestMarks();
		break;
		case "pirateStartQuest_1":
			dialog.text = StringFromKey("EdwardMansfield_25");
			link.l1 = StringFromKey("EdwardMansfield_26", pchar);
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = StringFromKey("EdwardMansfield_27");
			link.l1 = StringFromKey("EdwardMansfield_28");
			link.l1.go = "pirateStartQuest_3";
			link.l2 = StringFromKey("EdwardMansfield_29");
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = StringFromKey("EdwardMansfield_30");
			link.l1 = StringFromKey("EdwardMansfield_31");
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.BaronId = npchar.id;

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", GetFullName(npchar));

			AddLandQuestMark_Main(CharacterFromID("SantoDomingo_tavernkeeper"), "pSQ");
			AddLandQuestMark_Main(CharacterFromID("PortPax_tavernkeeper"), "pSQ");
		break;
		case "pirateStartQuest_4":
			dialog.text = StringFromKey("EdwardMansfield_32");
			link.l1 = StringFromKey("EdwardMansfield_33");
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = StringFromKey("EdwardMansfield_34");
			link.l1 = StringFromKey("EdwardMansfield_35");
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = StringFromKey("EdwardMansfield_36");
			link.l1 = StringFromKey("EdwardMansfield_37");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
			RemoveLandQuestMark_Main(npchar, "pSQ");
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = StringFromKey("EdwardMansfield_38");
			link.l1 = StringFromKey("EdwardMansfield_39", pchar);
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "pirateStartQuest");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = StringFromKey("EdwardMansfield_40", pchar);
			link.l1 = StringFromKey("EdwardMansfield_41");
			if (!CheckAttribute(pchar, "questTemp.pSQ_Bacchus"))
			{
				link.l1.go = "pirateStartQuest_info_3_Bacchus";
			}
			else
			{
				link.l1.go = "pirateStartQuest_info_3";
			}

			link.l2 = StringFromKey("EdwardMansfield_42");
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//Если поговорили по делу - сбросим агр
			if (CheckAttribute(npchar, "quest.repeat.Firsttime")) DeleteAttribute(npchar, "quest.repeat.Firsttime");
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			RemoveLandQuestMark_Main(npchar, "pSQ");
		break;
		case "pirateStartQuest_info_3_Bacchus":
			dialog.text = StringFromKey("EdwardMansfield_43");
			link.l1 = StringFromKey("EdwardMansfield_44");
			link.l1.go = "pirateStartQuest_info_3_Bacchus_1";

			link.l2 = StringFromKey("EdwardMansfield_45");
			link.l2.go = "pirateStartQuest_info_3_Bacchus_2";
		break;
		case "pirateStartQuest_info_3_Bacchus_1":
			dialog.text = StringFromKey("EdwardMansfield_46");
			link.l1 = StringFromKey("EdwardMansfield_47");
			link.l1.go = "pirateStartQuest_info_3";

			// СЖ запись
			pchar.questTemp.pSQ_Bacchus = "to_Bacchus";
			AddQuestRecord("pSQ_Bacchus", "1");
			AddQuestUserData("pSQ_Bacchus", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ_Bacchus", "sName", GetFullName(npchar));
		break;
		case "pirateStartQuest_info_3_Bacchus_2":
			dialog.text = StringFromKey("EdwardMansfield_48");
			link.l1 = StringFromKey("EdwardMansfield_49");
			link.l1.go = "pirateStartQuest_info_3";

			pchar.questTemp.pSQ_Bacchus = "over";
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//Если поговорили по делу - сбросим агр
			if (CheckAttribute(npchar, "quest.repeat.Firsttime")) DeleteAttribute(npchar, "quest.repeat.Firsttime");
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", GetFullName(CharacterFromID(pchar.questTemp.pirateStartQuest.BaronId)));
			RemoveLandQuestMark_Main(npchar, "pSQ");

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = StringFromKey("EdwardMansfield_50", pchar);
			link.l1 = StringFromKey("EdwardMansfield_51", pchar);
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			AddQuestRecord("pSQ", "10");
			CloseQuestHeader("pSQ");
			RemoveLandQuestMark_Main(npchar, "pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
			Achievment_Set(ACH_Pervye_shagi_k_viselitse);
		break;

		case "pirateStartQuest_BacchusSlaves":
			dialog.text = StringFromKey("EdwardMansfield_52");
			link.l1 = StringFromKey("EdwardMansfield_53");
			link.l1.go = "exit";

			AddMoneyToCharacter(pchar, 200 * 250);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, 200);

			pchar.questTemp.pSQ_Bacchus = "over";
			pchar.quest.pirateStartQuest_Bahus_Expired.over = "yes";
			AddQuestRecord("pSQ_Bacchus", "3");
			CloseQuestHeader("pSQ_Bacchus");
			RemoveLandQuestMark_Main(npchar, "pSQ_Bacchus");
		break;

		case "pirateStartQuest_BacchusSlaves_NoTalk":
			dialog.text = StringFromKey("EdwardMansfield_54");
			link.l1 = StringFromKey("EdwardMansfield_55");
			link.l1.go = "pirateStartQuest_BacchusSlaves_NoTalk_0";
		break;

		case "pirateStartQuest_BacchusSlaves_NoTalk_0":
			dialog.text = StringFromKey("EdwardMansfield_56");
			link.l1 = StringFromKey("EdwardMansfield_57");
			link.l1.go = "pirateStartQuest_BacchusSlaves_NoTalk_1";
		break;

		case "pirateStartQuest_BacchusSlaves_NoTalk_1":
			dialog.text = StringFromKey("EdwardMansfield_58");
			link.l1 = StringFromKey("EdwardMansfield_59");
			link.l1.go = "exit";

			AddMoneyToCharacter(pchar, 200 * 250);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, 200);

			pchar.questTemp.pSQ_Bacchus = "over";
			pchar.quest.pirateStartQuest_Bahus_Expired.over = "yes";
			AddQuestRecord("pSQ_Bacchus", "3");
			CloseQuestHeader("pSQ_Bacchus");
			RemoveLandQuestMark_Main(npchar, "pSQ_Bacchus");
		break;

		//********************* Английская линейка *********************
		/*case "EngLine_quests": //HardCoffee ref dialogue
		   dialog.text = "Я слушаю вас, капитан.";
		   link.l1 = "Я " + GetSexPhrase("прибыл", "прибыла") +" к вам по поручению генерал-губернатора Ямайки сэра Томаса Мэдифорда.";
		   link.l1.go = "Step_1";
		 break;*/
		case "Step_1":
			DeleteAttribute(pchar, "QuestTemp.EngLine_Mansfield_task");
			dialog.text = StringFromKey("EdwardMansfield_60");
			link.l1 = StringFromKey("EdwardMansfield_61");
			link.l1.go = "Step_2";
		break;
		case "Step_2":
			dialog.text = StringFromKey("EdwardMansfield_62");
			link.l1 = StringFromKey("EdwardMansfield_63");
			link.l1.go = "Step_3";
		break;
		case "Step_3":
			dialog.text = StringFromKey("EdwardMansfield_64");
			link.l1 = StringFromKey("EdwardMansfield_65");
			link.l1.go = "Step_4";
		break;
		case "Step_4":
			dialog.text = StringFromKey("EdwardMansfield_66", pchar);
			link.l1 = StringFromKey("EdwardMansfield_67");
			link.l1.go = "Step_5";
		break;
		case "Step_5":
			dialog.text = StringFromKey("EdwardMansfield_68");
			link.l1 = StringFromKey("EdwardMansfield_69");
			link.l1.go = "Step_6";
		break;
		case "Step_6":
			dialog.text = StringFromKey("EdwardMansfield_70");
			link.l1 = StringFromKey("EdwardMansfield_71");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddQuestRecord("Eng_Line_2_Talking", "3");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");

			pchar.questTemp.Count = makeint(sti(pchar.questTemp.Count) + 1);
			if (pchar.questTemp.Count == "4")
			{
				pchar.questTemp.State = "after_talks_with_pirates";
				AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
			}
		break;
		case "No_Mansfield_first_time":
			dialog.text = StringFromKey("EdwardMansfield_72");
			link.l1 = StringFromKey("EdwardMansfield_73");
			link.l1.go = "exit";
			NextDiag.TempNode = "No_Mansfield";
		break;
		case "No_Mansfield":
			dialog.text = StringFromKey("EdwardMansfield_74");
			link.l1 = StringFromKey("EdwardMansfield_75");
			link.l1.go = "exit";
		break;
		//********************* Голландская линейка *********************
		/*case "HolLine3_WormEngPlans": //HardCoffee ref dialogue
		  dialog.text = "Что привело тебя ко мне?";
		  link.l1 = "Я " + GetSexPhrase("прибыл", "прибыла") +" к вам по поручению генерал-губернатора Кюрасао Питера Стэвезанта.";
		  link.l1.go = "Step_H3_1";
	  break;*/
		case "Step_H3_1":
			DeleteAttribute(pchar, "QuestTemp.HolLine_Mansfield_task");
			dialog.text = StringFromKey("EdwardMansfield_76");
			link.l1 = StringFromKey("EdwardMansfield_77");
			link.l1.go = "Step_H3_2";
		break;
		case "Step_H3_2":
			dialog.text = StringFromKey("EdwardMansfield_78");
			link.l1 = StringFromKey("EdwardMansfield_79");
			link.l1.go = "Step_H3_3";
		break;
		case "Step_H3_3":
			dialog.text = StringFromKey("EdwardMansfield_80");
			link.l1 = StringFromKey("EdwardMansfield_81");
			link.l1.go = "Step_H3_4";
			TakeItemFromCharacter(pchar, "letter_HolLineQ3");
		break;
		case "Step_H3_4":
			dialog.text = StringFromKey("EdwardMansfield_82");
			link.l1 = StringFromKey("EdwardMansfield_83");
			link.l1.go = "Step_H3_5";
		break;
		case "Step_H3_5":
			dialog.text = StringFromKey("EdwardMansfield_84", pchar);
			link.l1 = StringFromKey("EdwardMansfield_85");
			link.l1.go = "Step_H3_6";
		break;
		case "Step_H3_6":
			dialog.text = StringFromKey("EdwardMansfield_86");
			link.l1 = StringFromKey("EdwardMansfield_87");
			link.l1.go = "Step_H3_7";
		break;
		case "Step_H3_7":
			dialog.text = StringFromKey("EdwardMansfield_88");
			link.l1 = StringFromKey("EdwardMansfield_89");
			link.l1.go = "Step_H3_8";
		break;
		case "Step_H3_8":
			dialog.text = StringFromKey("EdwardMansfield_90");
			link.l1 = StringFromKey("EdwardMansfield_91");
			link.l1.go = "Step_H3_9";
		break;
		case "Step_H3_9":
			dialog.text = StringFromKey("EdwardMansfield_92");
			link.l1 = StringFromKey("EdwardMansfield_93");
			link.l1.go = "Step_H3_10";
		break;
		case "Step_H3_10":
			dialog.text = StringFromKey("EdwardMansfield_94");
			link.l1 = StringFromKey("EdwardMansfield_95");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			pchar.questTemp.State = "WormEnglPlans_toMorgan";
			AddQuestRecord("Hol_Line_3_WormEnglishPlans", "2");
			//HardCoffee реф далогов с Морганом
			//QuestSetCurrentNode("Henry Morgan", "HolLine3_fromMansfield");
			pchar.QuestTemp.HolLine_quests_task = "fromMansfield";
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "SentJons_HouseF3", "goto", "goto1");
			LAi_SetHuberStayType(characterFromId("Henry Morgan"));
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(characterFromID("Henry Morgan"), "Hol_Line");
		break;

		//********************* капитан Шарп *********************
		case "SharpPearl_1":
			dialog.text = StringFromKey("EdwardMansfield_96");
			link.l1 = StringFromKey("EdwardMansfield_97");
			link.l1.go = "SharpPearl_2";
			pchar.questTemp.Sharp = "seekSharp";
			RemoveLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl");
			SeaPearl_PiratesBaron_DelQuestMarks();
			SeaPearl_Hostess_AddQuestMarks();
		break;
		case "SharpPearl_2":
			AddQuestRecord("SharpPearl", "16");
			AddQuestUserData("SharpPearl", "sName", GetFullName(NPChar));

			dialog.text = StringFromKey("EdwardMansfield_98");
			link.l1 = StringFromKey("EdwardMansfield_99");
			link.l1.go = "exit";
		break;

		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
			dialog.text = StringFromKey("EdwardMansfield_102", RandPhraseSimple(
						StringFromKey("EdwardMansfield_100", pchar),
						StringFromKey("EdwardMansfield_101")));
			link.l1 = StringFromKey("EdwardMansfield_103");
			link.l1.go = "AngryExitAgainWithOut";
			if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Мэнсфилдом через 30 дней.
			{
				if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
				{
					dialog.text = StringFromKey("EdwardMansfield_104");
					link.l1 = StringFromKey("EdwardMansfield_105", pchar);
					link.l1.go = NextDiag.TempNode;
					CharacterDelAngry(npchar);
				}
			}
		break;
		case "AngryExitAgain":
			DialogExit();
			DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
			DialogExit();
			DeleteAttribute(npchar, "angry.ok");
			DoReloadCharacterToLocation("LaVega_town", "reload", "reload3");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
