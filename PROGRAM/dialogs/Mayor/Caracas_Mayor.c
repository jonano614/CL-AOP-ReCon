// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Caracas_Mayor_3", RandPhraseSimple(
								StringFromKey("Caracas_Mayor_1"),
								StringFromKey("Caracas_Mayor_2"))),
						StringFromKey("Caracas_Mayor_4"),
						StringFromKey("Caracas_Mayor_5"),
						StringFromKey("Caracas_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Caracas_Mayor_9", RandPhraseSimple(
								StringFromKey("Caracas_Mayor_7", pchar),
								StringFromKey("Caracas_Mayor_8"))),
						StringFromKey("Caracas_Mayor_10"),
						StringFromKey("Caracas_Mayor_11"),
						StringFromKey("Caracas_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
			dialog.text = StringFromKey("Caracas_Mayor_15", RandPhraseSimple(
						StringFromKey("Caracas_Mayor_13"),
						StringFromKey("Caracas_Mayor_14")));
			link.l1 = StringFromKey("Caracas_Mayor_18", RandPhraseSimple(
						StringFromKey("Caracas_Mayor_16"),
						StringFromKey("Caracas_Mayor_17", pchar)));
			link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
		break;
		//************************** Квестовые штрумы ************************
		//==> Одиннадцатый квест англ.линейки: захват Каракаса и Куманы.
		case "EngLine11Quest_OccupyMein":
			dialog.text = StringFromKey("Caracas_Mayor_19");
			link.l1 = StringFromKey("Caracas_Mayor_20");
			link.l1.go = "Step_E10_1";
			AfterTownBattle();
		break;
		case "Step_E10_1":
			dialog.text = StringFromKey("Caracas_Mayor_21");
			link.l1 = StringFromKey("Caracas_Mayor_22");
			link.l1.go = "exit";
			AddQuestRecord("Eng_Line_11_OccupyMein", "2");
			pchar.questTemp.Q11_Caracas = 1;
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

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

