// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SantoDomingo_Mayor_3", RandPhraseSimple(
								StringFromKey("SantoDomingo_Mayor_1"),
								StringFromKey("SantoDomingo_Mayor_2"))),
						StringFromKey("SantoDomingo_Mayor_4"),
						StringFromKey("SantoDomingo_Mayor_5"),
						StringFromKey("SantoDomingo_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SantoDomingo_Mayor_9", RandPhraseSimple(
								StringFromKey("SantoDomingo_Mayor_7", pchar),
								StringFromKey("SantoDomingo_Mayor_8"))),
						StringFromKey("SantoDomingo_Mayor_10"),
						StringFromKey("SantoDomingo_Mayor_11"),
						StringFromKey("SantoDomingo_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
			dialog.text = StringFromKey("SantoDomingo_Mayor_15", RandPhraseSimple(
						StringFromKey("SantoDomingo_Mayor_13"),
						StringFromKey("SantoDomingo_Mayor_14")));
			link.l1 = StringFromKey("SantoDomingo_Mayor_18", RandPhraseSimple(
						StringFromKey("SantoDomingo_Mayor_16"),
						StringFromKey("SantoDomingo_Mayor_17", pchar)));
			link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
		break;

		//********************** Фр.линейка. Квест №10. Захват Санто-Доминго ************************
		case "FraLine10Quest_OccupySD":
			dialog.text = StringFromKey("SantoDomingo_Mayor_19");
			link.l1 = StringFromKey("SantoDomingo_Mayor_20", GetFullName(pchar));
			link.l1.go = "Step_F10_1";
			AfterTownBattle();
		break;

		case "Step_F10_1":
			dialog.text = StringFromKey("SantoDomingo_Mayor_21");
			link.l1 = StringFromKey("SantoDomingo_Mayor_22");
			link.l1.go = "exit";
			pchar.questTemp.State = "Fr10OccupySD_toWeWon";
			AddQuestRecord("Fra_Line_10_OccupySantoDomingo", "2");
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

