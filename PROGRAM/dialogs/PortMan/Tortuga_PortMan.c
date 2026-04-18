// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_PortMan_3", RandPhraseSimple(
								StringFromKey("Tortuga_PortMan_1"),
								StringFromKey("Tortuga_PortMan_2", GetAddress_Form(NPChar)))),
						StringFromKey("Tortuga_PortMan_4", GetAddress_Form(NPChar)),
						StringFromKey("Tortuga_PortMan_5"),
						StringFromKey("Tortuga_PortMan_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_PortMan_9", RandPhraseSimple(
								StringFromKey("Tortuga_PortMan_7", pchar),
								StringFromKey("Tortuga_PortMan_8"))),
						StringFromKey("Tortuga_PortMan_10"),
						StringFromKey("Tortuga_PortMan_11"),
						StringFromKey("Tortuga_PortMan_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> квест №7 голл.линейки, догнать похитителей депеши
			if (pchar.questTemp.State == "DelivLettTortuga_toPortMan")
			{
				link.l1 = StringFromKey("Tortuga_PortMan_13");
				link.l1.go = "Step_H7_1";
			}
			if (pchar.questTemp.State == "Sp6TakeMess_toTotuga")
			{
				link.l1 = StringFromKey("Tortuga_PortMan_14", pchar);
				link.l1.go = "Step_S6_1";
			}
			if (pchar.questTemp.State == "Sp6TakeMess_waitMessanger")
			{
				link.l1 = StringFromKey("Tortuga_PortMan_15");
				link.l1.go = "Step_S6_6";
			}
			if (pchar.questTemp.State == "Fr4SoleiRoyal_toPortMan")
			{
				link.l1 = StringFromKey("Tortuga_PortMan_16");
				link.l1.go = "Step_F4_1";
			}

			if (pchar.questTemp.Slavetrader == "FindRatTortuga")
			{
				link.l1 = StringFromKey("Tortuga_PortMan_17", pchar.questTemp.Slavetrader.ShipName);
				link.l1.go = "Tortuga_ratP_1";
			}

		break;

		//************************************* Голл. линейка, квест №7, доставка депеши *******************************
		case "Step_H7_1":
			dialog.text = StringFromKey("Tortuga_PortMan_18");
			link.l1 = StringFromKey("Tortuga_PortMan_19");
			link.l1.go = "Step_H7_2";
		break;
		case "Step_H7_2":
			dialog.text = StringFromKey("Tortuga_PortMan_20");
			link.l1 = StringFromKey("Tortuga_PortMan_21");
			link.l1.go = "Step_H7_3";
		break;
		case "Step_H7_3":
			dialog.text = StringFromKey("Tortuga_PortMan_22");
			link.l1 = StringFromKey("Tortuga_PortMan_23", pchar);
			link.l1.go = "Step_H7_4";
		break;
		case "Step_H7_4":
			dialog.text = StringFromKey("Tortuga_PortMan_24");
			link.l1 = StringFromKey("Tortuga_PortMan_25");
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_7_DelivLettTortuga", "5");
			pchar.questTemp.State = "DelivLettTortuga_NotFoundLetter";
			Pchar.quest.DelivLettTortuga_AttackBrig.win_condition.l1 = "location";
			Pchar.quest.DelivLettTortuga_AttackBrig.win_condition.l1.location = "PuertoRico";
			Pchar.quest.DelivLettTortuga_AttackBrig.win_condition = "DelivLettTortuga_AttackBrig";
			SetTimerCondition("DelivLettTortuga_BrigTimeOver", 0, 0, 5, false);
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("hol_guber"), "Hol_Line");
		break;
		//************************************* Испанская линейка, квест №6, перехват вестового *******************************
		case "Step_S6_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_PortMan_26"),
						StringFromKey("Tortuga_PortMan_27"),
						StringFromKey("Tortuga_PortMan_28"),
						StringFromKey("Tortuga_PortMan_29"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_PortMan_30", pchar),
						StringFromKey("Tortuga_PortMan_31"),
						StringFromKey("Tortuga_PortMan_32"),
						StringFromKey("Tortuga_PortMan_33"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S6_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_S6_2":
			dialog.text = StringFromKey("Tortuga_PortMan_34");
			link.l1 = StringFromKey("Tortuga_PortMan_35");
			link.l1.go = "Step_S6_3";
		break;
		case "Step_S6_3":
			dialog.text = StringFromKey("Tortuga_PortMan_36");
			link.l1 = StringFromKey("Tortuga_PortMan_37");
			link.l1.go = "Step_S6_4";
		break;
		case "Step_S6_4":
			dialog.text = StringFromKey("Tortuga_PortMan_38", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Tortuga_PortMan_39", pchar);
			link.l1.go = "Step_S6_5";
		break;
		case "Step_S6_5":
			dialog.text = StringFromKey("Tortuga_PortMan_40");
			link.l1 = StringFromKey("Tortuga_PortMan_41");
			link.l1.go = "exit";
			AddQuestRecord("Spa_Line_6_TakeMessangeer", "2");
			pchar.questTemp.State = "Sp6TakeMess_waitMessanger";
			if (CheckAttribute(pchar, "questTemp.State.Sp6Ok"))
			{
				SetTimerCondition("Sp6TakeMess_waitingBoy", 0, 0, rand(7) + 1, false);
				DeleteAttribute(pchar, "questTemp.State.Sp6Ok");
			}
			else
			{
				pchar.questTemp.State.Sp6Ok = 1;
			}
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
		break;
		case "Step_S6_6":
			dialog.text = StringFromKey("Tortuga_PortMan_42");
			link.l1 = StringFromKey("Tortuga_PortMan_43");
			link.l1.go = "exit";
		break;
		//************************************* Французская линейка, квест №4, Солей Руаяль *******************************
		case "Step_F4_1":
			if (GetCompanionQuantity(pchar) == 1)
			{
				dialog.text = StringFromKey("Tortuga_PortMan_44", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Tortuga_PortMan_45", pchar);
				link.l1.go = "Step_F4_2";
			}
			else
			{
				dialog.text = StringFromKey("Tortuga_PortMan_46");
				link.l1 = StringFromKey("Tortuga_PortMan_47");
				link.l1.go = "exit";
			}
		break;
		case "Step_F4_2":
			pchar.questTemp.State = "Fr4SoleiRoyal_toBasTer";
			SaveCurrentQuestDateParam("questTemp");
			AddQuestRecord("Fra_Line_4_SoleiRoyal", "2");
			ref sld = GetCharacter(NPC_GenerateCharacter("SoleiRoyalCaptain", "navy_off_fra_5", "man", "man", 52, FRANCE, -1, true));
			sld.Ship.Name = FindPersonalName("SoleiRoyalCaptain_mapEnc");
			sld.Ship.Type = CreateBaseShip(SHIP_SOLEYRU);
			ResetShipCannonsDamages(sld);
			SetBaseShipData(sld);
			SetCrewQuantityFull(sld);
			Fantom_SetBalls(sld, "pirate");
			FantomMakeCoolFighter(sld, 35, 80, 70, BLADE_LONG, "pistol3", 100);

			sld.CompanionEnemyEnable = false;
			sld.Abordage.Enable = false; // НЕЛЬЗЯ!
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetShipRemovable(sld, false);

			Pchar.quest.Fr4SoleiRoyal_Fight.win_condition.l1 = "location";
			Pchar.quest.Fr4SoleiRoyal_Fight.win_condition.l1.location = "Dominica";
			Pchar.quest.Fr4SoleiRoyal_Fight.win_condition = "Fr4SoleiRoyal_Fight";
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;

		case "Tortuga_ratP_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_PortMan_48", pchar.questTemp.Slavetrader.ShipName),
						StringFromKey("Tortuga_PortMan_49"),
						StringFromKey("Tortuga_PortMan_50"),
						StringFromKey("Tortuga_PortMan_51"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_PortMan_52"),
						StringFromKey("Tortuga_PortMan_53"),
						StringFromKey("Tortuga_PortMan_54", pchar),
						StringFromKey("Tortuga_PortMan_55", npchar.name), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";

			RemoveLandQuestmark_Main(npchar, "Slavetrader");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
