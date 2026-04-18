// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	int i;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Cumana_Mayor_3", RandPhraseSimple(
								StringFromKey("Cumana_Mayor_1"),
								StringFromKey("Cumana_Mayor_2"))),
						StringFromKey("Cumana_Mayor_4"),
						StringFromKey("Cumana_Mayor_5"),
						StringFromKey("Cumana_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Cumana_Mayor_9", RandPhraseSimple(
								StringFromKey("Cumana_Mayor_7", pchar),
								StringFromKey("Cumana_Mayor_8"))),
						StringFromKey("Cumana_Mayor_10"),
						StringFromKey("Cumana_Mayor_11"),
						StringFromKey("Cumana_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Sp8SaveCumana_GoodWork")//квест №8 испанки.
			{
				dialog.text = StringFromKey("Cumana_Mayor_15", RandPhraseSimple(
							StringFromKey("Cumana_Mayor_13", UpperFirst(GetAddress_Form(NPChar))),
							StringFromKey("Cumana_Mayor_14")));
				link.l1 = StringFromKey("Cumana_Mayor_18", RandPhraseSimple(
							StringFromKey("Cumana_Mayor_16"),
							StringFromKey("Cumana_Mayor_17")));
				link.l1.go = "exit";
			}
		break;

		case "Cupture_after":
			dialog.text = StringFromKey("Cumana_Mayor_21", RandPhraseSimple(
						StringFromKey("Cumana_Mayor_19"),
						StringFromKey("Cumana_Mayor_20")));
			link.l1 = StringFromKey("Cumana_Mayor_24", RandPhraseSimple(
						StringFromKey("Cumana_Mayor_22"),
						StringFromKey("Cumana_Mayor_23", pchar)));
			link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
		break;
		//************************** Квестовые штрумы ************************	
		//==> Одиннадцатый квест англ.линейки: захват Каракаса и Куманы.
		case "EngLine11Quest_OccupyMein":
			dialog.text = StringFromKey("Cumana_Mayor_25");
			link.l1 = StringFromKey("Cumana_Mayor_26");
			link.l1.go = "Step_E10_1";
			AfterTownBattle();
		break;
		case "Step_E10_1":
			dialog.text = StringFromKey("Cumana_Mayor_27");
			link.l1 = StringFromKey("Cumana_Mayor_28");
			link.l1.go = "exit";
			AddQuestRecord("Eng_Line_11_OccupyMein", "3");
			pchar.questTemp.Q11_Cumana = 1;
			NextDiag.TempNode = "Cupture_after";
			PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
			PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
			SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
			DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
			UpdateRelations();
			Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
			Achievement_AddStats_SturmColonies();
			SetReturn_Gover_Dialog_Exit(NPChar);
			chrDisableReloadToLocation = false;
			AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
		break;
		//==> Шестой квест фр.линейки: захват Куманы с Олоне.
		case "FraLine6Quest_Attack":
			dialog.text = StringFromKey("Cumana_Mayor_29");
			link.l1 = StringFromKey("Cumana_Mayor_30");
			link.l1.go = "Step_F6_1";
			group_DeleteGroup("Spa_Attack");
			AfterTownBattle();
		break;
		case "Step_F6_1":
			dialog.text = StringFromKey("Cumana_Mayor_31");
			link.l1 = StringFromKey("Cumana_Mayor_32");
			link.l1.go = "Step_F6_2";
		break;
		case "Step_F6_2":
			dialog.text = StringFromKey("Cumana_Mayor_33");
			link.l1 = StringFromKey("Cumana_Mayor_34");
			link.l1.go = "Step_F6_3";
		break;
		case "Step_F6_3":
			if (GetQuestPastDayParam("questTemp") < 14)
			{
				dialog.text = StringFromKey("Cumana_Mayor_35");
				link.l1 = StringFromKey("Cumana_Mayor_36");
				link.l1.go = "Step_F6_exit";
				pchar.GenQuestBox.Cumana_TownhallRoom = true;
				pchar.GenQuestBox.Cumana_TownhallRoom.box1.money = 200000;
				LocatorReloadEnterDisable("Cumana_townhall", "reload2", false);
				pchar.questTemp.State = "Fr5Olone_FoundMoney";
			}
			else
			{
				dialog.text = StringFromKey("Cumana_Mayor_37");
				link.l1 = StringFromKey("Cumana_Mayor_38");
				link.l1.go = "Step_F6_4";
			}
		break;
		case "Step_F6_4":
			dialog.text = StringFromKey("Cumana_Mayor_39", UpperFirst(GetAddress_Form(NPChar)));
			link.l1 = StringFromKey("Cumana_Mayor_40", pchar);
			link.l1.go = "Step_F6_exit";
			pchar.questTemp.State = "Fr5Olone_WeLate";
		break;
		case "Step_F6_exit":
			for (i = 0; i < 3; i++)
			{
				if (i == 0)    sld = characterFromID("Olone");
				else    sld = characterFromID("Captain_" + i);
				RemoveCharacterCompanion(pchar, sld);
				sld.dialog.currentnode = "First time";
				LAi_SetStayType(sld);
				LAi_SetCurHPMax(sld);
				LAi_LoginInCaptureTown(sld, true);
			}
			Pchar.quest.Fr6Olone_TalkWithOlone.win_condition.l1 = "location";
			Pchar.quest.Fr6Olone_TalkWithOlone.win_condition.l1.location = "Cumana_town";
			Pchar.quest.Fr6Olone_TalkWithOlone.win_condition = "Fr6Olone_TalkWithOlone";
			LAi_LocationDisableOfficersGen("Cumana_town", true); //офицеров не пускать
			chrDisableReloadToLocation = false;
			NextDiag.CurrentNode = "Cupture_after";
			SetReturn_Gover_Dialog_Exit(NPChar);
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

