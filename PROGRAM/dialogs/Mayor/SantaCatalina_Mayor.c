// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SantaCatalina_Mayor_3", RandPhraseSimple(
								StringFromKey("SantaCatalina_Mayor_1"),
								StringFromKey("SantaCatalina_Mayor_2"))),
						StringFromKey("SantaCatalina_Mayor_4"),
						StringFromKey("SantaCatalina_Mayor_5"),
						StringFromKey("SantaCatalina_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SantaCatalina_Mayor_9", RandPhraseSimple(
								StringFromKey("SantaCatalina_Mayor_7", pchar),
								StringFromKey("SantaCatalina_Mayor_8"))),
						StringFromKey("SantaCatalina_Mayor_10"),
						StringFromKey("SantaCatalina_Mayor_11"),
						StringFromKey("SantaCatalina_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		case "Cupture_after":
			dialog.text = StringFromKey("SantaCatalina_Mayor_15", RandPhraseSimple(
						StringFromKey("SantaCatalina_Mayor_13"),
						StringFromKey("SantaCatalina_Mayor_14")));
			link.l1 = StringFromKey("SantaCatalina_Mayor_18", RandPhraseSimple(
						StringFromKey("SantaCatalina_Mayor_16"),
						StringFromKey("SantaCatalina_Mayor_17", pchar)));
			link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
		break;

		//********************** Фр.линейка. Квест №11. Захват Санта Каталины ************************
		case "FraLine11Quest_OccupySC":
			dialog.text = StringFromKey("SantaCatalina_Mayor_19");
			link.l1 = StringFromKey("SantaCatalina_Mayor_20");
			link.l1.go = "Step_F11_1";
			AfterTownBattle();
		break;
		case "Step_F11_1":
			dialog.text = StringFromKey("SantaCatalina_Mayor_21");
			link.l1 = StringFromKey("SantaCatalina_Mayor_22", pchar);
			link.l1.go = "Step_F11_2";
		break;
		case "Step_F11_2":
			dialog.text = StringFromKey("SantaCatalina_Mayor_23", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("SantaCatalina_Mayor_24");
			link.l1.go = "exit";
			pchar.questTemp.State = "Fr11OccupySC_toWeWon";
			AddQuestRecord("Fra_Line_11_OccupySantaCatalina", "2");
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
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

