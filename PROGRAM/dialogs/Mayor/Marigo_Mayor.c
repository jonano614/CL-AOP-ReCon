// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Marigo_Mayor_3", RandPhraseSimple(
								StringFromKey("Marigo_Mayor_1"),
								StringFromKey("Marigo_Mayor_2"))),
						StringFromKey("Marigo_Mayor_4"),
						StringFromKey("Marigo_Mayor_5"),
						StringFromKey("Marigo_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Marigo_Mayor_9", RandPhraseSimple(
								StringFromKey("Marigo_Mayor_7", pchar),
								StringFromKey("Marigo_Mayor_8"))),
						StringFromKey("Marigo_Mayor_10"),
						StringFromKey("Marigo_Mayor_11"),
						StringFromKey("Marigo_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
			dialog.text = StringFromKey("Marigo_Mayor_15", RandPhraseSimple(
						StringFromKey("Marigo_Mayor_13"),
						StringFromKey("Marigo_Mayor_14")));
			link.l1 = StringFromKey("Marigo_Mayor_18", RandPhraseSimple(
						StringFromKey("Marigo_Mayor_16"),
						StringFromKey("Marigo_Mayor_17", pchar)));
			link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
		break;

		//==> Одиннадцатый квест исп.линейки: разорение Виллемстада и Мариго.
		case "SpaLine11Quest_DestrHol":
			dialog.text = StringFromKey("Marigo_Mayor_19");
			link.l1 = StringFromKey("Marigo_Mayor_20");
			link.l1.go = "Step_S11_1";
			AfterTownBattle();
		break;
		case "Step_S11_1":
			dialog.text = StringFromKey("Marigo_Mayor_21");
			link.l1 = StringFromKey("Marigo_Mayor_22");
			link.l1.go = "Step_S11_2";
		break;
		case "Step_S11_2":
			dialog.text = StringFromKey("Marigo_Mayor_23");
			link.l1 = StringFromKey("Marigo_Mayor_24");
			link.l1.go = "exit";
			AddQuestRecord("Spa_Line_11_DestrHolland", "3");
			pchar.questTemp.Q11_Marigo = 1;
			NextDiag.TempNode = "Cupture_after";
			Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
			Achievement_AddStats_SturmColonies();
			SetReturn_Gover_Dialog_Exit(NPChar);
			chrDisableReloadToLocation = false;
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

