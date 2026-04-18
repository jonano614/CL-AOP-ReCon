// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortPax_Mayor_3", RandPhraseSimple(
								StringFromKey("PortPax_Mayor_1"),
								StringFromKey("PortPax_Mayor_2"))),
						StringFromKey("PortPax_Mayor_4"),
						StringFromKey("PortPax_Mayor_5"),
						StringFromKey("PortPax_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortPax_Mayor_9", RandPhraseSimple(
								StringFromKey("PortPax_Mayor_7", pchar),
								StringFromKey("PortPax_Mayor_8"))),
						StringFromKey("PortPax_Mayor_10"),
						StringFromKey("PortPax_Mayor_11"),
						StringFromKey("PortPax_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Fr9GuardPP_GoodWork")
			{
				dialog.text = StringFromKey("PortPax_Mayor_13");
				link.l1 = StringFromKey("PortPax_Mayor_14", pchar);
				link.l1.go = "exit";
			}
		break;

		case "Cupture_after":
			dialog.text = StringFromKey("PortPax_Mayor_17", RandPhraseSimple(
						StringFromKey("PortPax_Mayor_15"),
						StringFromKey("PortPax_Mayor_16")));
			link.l1 = StringFromKey("PortPax_Mayor_20", RandPhraseSimple(
						StringFromKey("PortPax_Mayor_18"),
						StringFromKey("PortPax_Mayor_19", pchar)));
			link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
		break;

		//==> Двенадцатый квест исп.линейки: захват Порт-о-Принса.
		case "SpaLine12Quest_PortPax":
			dialog.text = StringFromKey("PortPax_Mayor_21", pchar);
			link.l1 = StringFromKey("PortPax_Mayor_22");
			link.l1.go = "Step_S12_1";
			AfterTownBattle();
		break;
		case "Step_S12_1":
			dialog.text = StringFromKey("PortPax_Mayor_23");
			link.l1 = StringFromKey("PortPax_Mayor_24");
			link.l1.go = "exit";
			AddQuestRecord("Spa_Line_12_OccupyPortPax", "2");
			pchar.questTemp.State = "OccupyPortPax_WeWin";
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
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

