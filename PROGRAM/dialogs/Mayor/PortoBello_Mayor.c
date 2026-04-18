// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortoBello_Mayor_3", RandPhraseSimple(
								StringFromKey("PortoBello_Mayor_1"),
								StringFromKey("PortoBello_Mayor_2"))),
						StringFromKey("PortoBello_Mayor_4"),
						StringFromKey("PortoBello_Mayor_5"),
						StringFromKey("PortoBello_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortoBello_Mayor_9", RandPhraseSimple(
								StringFromKey("PortoBello_Mayor_7", pchar),
								StringFromKey("PortoBello_Mayor_8"))),
						StringFromKey("PortoBello_Mayor_10"),
						StringFromKey("PortoBello_Mayor_11"),
						StringFromKey("PortoBello_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Sp9SaveCumana_toPortoBello")//квест №9 испанки.
			{
				dialog.text = StringFromKey("PortoBello_Mayor_13");
				link.l1 = StringFromKey("PortoBello_Mayor_14", GetFullName(pchar));
				link.l1.go = "Step_S10_1";
			}
			if (pchar.questTemp.State == "Sp9SaveCumana_toCompOut")//квест №9 испанки, после того, как 0 компаньонов.
			{
				dialog.text = StringFromKey("PortoBello_Mayor_15");
				link.l1 = StringFromKey("PortoBello_Mayor_16");
				link.l1.go = "Step_S10_5";
			}
			if (pchar.questTemp.piratesLine == "Panama_toPortoBello")//пиратка, штурм Панамы
			{
				dialog.text = "";
				link.l1 = "";
				link.l1.go = "Step_S10_5";
			}
		break;
		//==> Девятый квест исп.линейки: сопроводить четыре золотых галеона.
		case "Step_S10_1":
			dialog.text = StringFromKey("PortoBello_Mayor_17");
			link.l1 = StringFromKey("PortoBello_Mayor_18", pchar);
			link.l1.go = "Step_S10_2";
			TakeItemFromCharacter(pchar, "letter_SpaLineQ10");
		break;
		case "Step_S10_2":
			dialog.text = StringFromKey("PortoBello_Mayor_19");
			link.l1 = StringFromKey("PortoBello_Mayor_20");
			link.l1.go = "Step_S10_3";
		break;
		case "Step_S10_3":
			dialog.text = StringFromKey("PortoBello_Mayor_21");
			link.l1 = StringFromKey("PortoBello_Mayor_22");
			link.l1.go = "Step_S10_4";
		break;
		case "Step_S10_4":
			dialog.text = StringFromKey("PortoBello_Mayor_23");
			link.l1 = StringFromKey("PortoBello_Mayor_24");
			link.l1.go = "Step_S10_5";
		break;
		case "Step_S10_5":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = StringFromKey("PortoBello_Mayor_25");
				link.l1 = StringFromKey("PortoBello_Mayor_26", pchar);
				link.l1.go = "exit";
				pchar.questTemp.State = "Sp9SaveCumana_toCompOut";
			}
			else
			{
				dialog.text = StringFromKey("PortoBello_Mayor_27");
				link.l1 = StringFromKey("PortoBello_Mayor_28", pchar);
				link.l1.go = "Step_S10_6";
			}
		break;
		case "Step_S10_6":
			dialog.text = StringFromKey("PortoBello_Mayor_29");
			link.l1 = StringFromKey("PortoBello_Mayor_30");
			link.l1.go = "Step_S10_7";
		break;
		case "Step_S10_7":
			pchar.questTemp.State = "Sp9SaveCumana_toCompOut";
			AddQuestRecord("Spa_Line_9_FourGolgGaleons", "2");
			AddQuestUserData("Spa_Line_9_FourGolgGaleons", "sSex", GetSexPhrase("ен", "на"));
			ref sld;
			for (int i = 1; i <= 4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Captain_" + i, "merch_" + (rand(14) + 1), "man", "man", 15, SPAIN, -1, true));
				FantomMakeCoolSailor(sld, SHIP_GALEON_L, "", CANNON_TYPE_CANNON_LBS16, 30, 15, 15);
				FantomMakeCoolFighter(sld, 15, 10, 10, BLADE_SHORT, "pistol1", 0);
				sld.Ship.Cargo.Goods.Balls = 48;
				sld.Ship.Cargo.Goods.Grapes = 10;
				sld.Ship.Cargo.Goods.Knippels = 48;
				sld.Ship.Cargo.Goods.Bombs = 48;
				sld.Ship.Cargo.Goods.Weapon = 0;
				sld.Ship.Cargo.Goods.Powder = 80;
				sld.Ship.Cargo.Goods.Food = 300;
				sld.Ship.Cargo.Goods.Gold = 1250;
				SetCharacterRemovable(sld, false);
				sld.CompanionEnemyEnable = false;
				sld.Abordage.Enable = false; // НЕЛЬЗЯ!
				SetCompanionIndex(pchar, -1, sti(sld.index));
				Pchar.quest.Sp9SaveCumana_toCaimanBattle.win_condition.l1 = "location";
				Pchar.quest.Sp9SaveCumana_toCaimanBattle.win_condition.l1.location = "Caiman";
				Pchar.quest.Sp9SaveCumana_toCaimanBattle.win_condition = "Sp9SaveCumana_toCaimanBattle";
			}
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
			dialog.text = StringFromKey("PortoBello_Mayor_33", RandPhraseSimple(
						StringFromKey("PortoBello_Mayor_31"),
						StringFromKey("PortoBello_Mayor_32")));
			link.l1 = StringFromKey("PortoBello_Mayor_36", RandPhraseSimple(
						StringFromKey("PortoBello_Mayor_34"),
						StringFromKey("PortoBello_Mayor_35", pchar)));
			link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
		break;
		//==> пиратка, штурм Панамы
		case "PQ8_MayorPortoBello":
			dialog.text = StringFromKey("PortoBello_Mayor_37");
			link.l1 = StringFromKey("PortoBello_Mayor_38");
			link.l1.go = "Step_P1_1";
			AfterTownBattle();
		break;
		case "Step_P1_1":
			dialog.text = StringFromKey("PortoBello_Mayor_39");
			link.l1 = StringFromKey("PortoBello_Mayor_40");
			link.l1.go = "Step_P1_2";
		break;
		case "Step_P1_2":
			dialog.text = StringFromKey("PortoBello_Mayor_41");
			link.l1 = StringFromKey("PortoBello_Mayor_42");
			link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
			Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
			Achievement_AddStats_SturmColonies();
			SetReturn_Gover_Dialog_Exit(NPChar);
			chrDisableReloadToLocation = false;
			AddDialogExitQuestFunction("PQ8_MorganInPortoBello");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

