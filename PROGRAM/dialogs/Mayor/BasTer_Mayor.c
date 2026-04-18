// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("BasTer_Mayor_3", RandPhraseSimple(
								StringFromKey("BasTer_Mayor_1"),
								StringFromKey("BasTer_Mayor_2"))),
						StringFromKey("BasTer_Mayor_4"),
						StringFromKey("BasTer_Mayor_5"),
						StringFromKey("BasTer_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("BasTer_Mayor_9", RandPhraseSimple(
								StringFromKey("BasTer_Mayor_7", pchar),
								StringFromKey("BasTer_Mayor_8"))),
						StringFromKey("BasTer_Mayor_10"),
						StringFromKey("BasTer_Mayor_11"),
						StringFromKey("BasTer_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Fr4SoleiRoyal_GoodWork")
			{
				dialog.text = StringFromKey("BasTer_Mayor_13");
				link.l1 = StringFromKey("BasTer_Mayor_14");
				link.l1.go = "Step_F4_1";
			}
		break;
		//************************** Фр.линкейка, квест №4. Солей Руаяль ************************
		case "Step_F4_1":
			dialog.text = StringFromKey("BasTer_Mayor_15");
			link.l1 = StringFromKey("BasTer_Mayor_16");
			link.l1.go = "Step_F4_2";
		break;
		case "Step_F4_2":
			dialog.text = StringFromKey("BasTer_Mayor_17");
			link.l1 = StringFromKey("BasTer_Mayor_18");
			link.l1.go = "Step_F4_3";
		break;
		case "Step_F4_3":
			if (CheckCompanionInCharacter(pchar, "SoleiRoyalCaptain"))
			{
				dialog.text = StringFromKey("BasTer_Mayor_19");
				link.l1 = StringFromKey("BasTer_Mayor_20");
				link.l1.go = "exit";
				RemoveCharacterCompanion(pchar, characterFromId("SoleiRoyalCaptain"));
				pchar.questTemp.State = "Fr4SoleiRoyal_backTortuga";
				AddQuestRecord("Fra_Line_4_SoleiRoyal", "6");
			}
			else
			{
				dialog.text = StringFromKey("BasTer_Mayor_21", pchar);
				link.l1 = StringFromKey("BasTer_Mayor_22");
				link.l1.go = "exit";
				pchar.questTemp.State = "Fr4SoleiRoyal_SoleiRoyalSunk";
				AddQuestRecord("Fra_Line_4_SoleiRoyal", "7");
			}
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
		break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
			dialog.text = StringFromKey("BasTer_Mayor_25", RandPhraseSimple(
						StringFromKey("BasTer_Mayor_23"),
						StringFromKey("BasTer_Mayor_24")));
			link.l1 = StringFromKey("BasTer_Mayor_28", RandPhraseSimple(
						StringFromKey("BasTer_Mayor_26"),
						StringFromKey("BasTer_Mayor_27", pchar)));
			link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
		break;
		//Квест Аскольда, штурм в обличие мумии
		case "Ascold_MummyAttack":
			dialog.text = StringFromKey("BasTer_Mayor_29");
			Link.l1 = StringFromKey("BasTer_Mayor_30");
			Link.l1.go = "Step_Asc1";
			AfterTownBattle();
		break;
		case "Step_Asc1":
			dialog.text = StringFromKey("BasTer_Mayor_31");
			Link.l1 = StringFromKey("BasTer_Mayor_32");
			Link.l1.go = "Step_Asc2";
		break;
		case "Step_Asc2":
			dialog.text = StringFromKey("BasTer_Mayor_33");
			Link.l1 = StringFromKey("BasTer_Mayor_34");
			Link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
			Locations[FindLocation(pchar.location)].box1.items.sculMa1 = 1;
			Locations[FindLocation(pchar.location)].box1.items.sculMa2 = 1;
			Locations[FindLocation(pchar.location)].box1.items.sculMa3 = 1;
			Locations[FindLocation(pchar.location)].box1.items.indian22 = 1;
			pchar.questTemp.Ascold = "Ascold_MummyFoundItems";
			chrDisableReloadToLocation = false;
			SetReturn_Gover_Dialog_Exit(NPChar);
			RemoveLandQuestmark_Main(npchar, "Ascold");
			AddLandQuestmark_Main(CharacterFromID("LeifEricson"), "Ascold");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

