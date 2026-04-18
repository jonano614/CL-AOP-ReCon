// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Villemstad_Mayor_3", RandPhraseSimple(
								StringFromKey("Villemstad_Mayor_1"),
								StringFromKey("Villemstad_Mayor_2"))),
						StringFromKey("Villemstad_Mayor_4"),
						StringFromKey("Villemstad_Mayor_5"),
						StringFromKey("Villemstad_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Villemstad_Mayor_9", RandPhraseSimple(
								StringFromKey("Villemstad_Mayor_7", pchar),
								StringFromKey("Villemstad_Mayor_8"))),
						StringFromKey("Villemstad_Mayor_10"),
						StringFromKey("Villemstad_Mayor_11"),
						StringFromKey("Villemstad_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
			dialog.text = StringFromKey("Villemstad_Mayor_15", RandPhraseSimple(
						StringFromKey("Villemstad_Mayor_13"),
						StringFromKey("Villemstad_Mayor_14")));
			link.l1 = StringFromKey("Villemstad_Mayor_18", RandPhraseSimple(
						StringFromKey("Villemstad_Mayor_16"),
						StringFromKey("Villemstad_Mayor_17", pchar)));
			link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
		break;

		//==> Одиннадцатый квест исп.линейки: разорение Виллемстада и Мариго.
		case "SpaLine11Quest_DestrHol":
			dialog.text = StringFromKey("Villemstad_Mayor_19");
			link.l1 = StringFromKey("Villemstad_Mayor_20");
			link.l1.go = "Step_S11_1";
			AfterTownBattle();
		break;
		case "Step_S11_1":
			dialog.text = StringFromKey("Villemstad_Mayor_21");
			link.l1 = StringFromKey("Villemstad_Mayor_22");
			link.l1.go = "exit";
			AddQuestRecord("Spa_Line_11_DestrHolland", "2");
			pchar.questTemp.Q11_Villemstad = 1;
			NextDiag.TempNode = "Cupture_after";
			Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
			Achievement_AddStats_SturmColonies();
			SetReturn_Gover_Dialog_Exit(NPChar);
			chrDisableReloadToLocation = false;
			pchar.quest.VillemstadResGatesLock.win_condition.l1 = "MapEnter";
			pchar.quest.VillemstadResGatesLock.function = "VillemstadResGatesLock";
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

