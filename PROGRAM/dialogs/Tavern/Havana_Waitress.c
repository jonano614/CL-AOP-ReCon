// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	float locx, locy, locz, fTemp;

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Havana_Waitress_3", RandPhraseSimple(
								StringFromKey("Havana_Waitress_1", GetAddress_Form(NPChar)),
								StringFromKey("Havana_Waitress_2", GetAddress_Form(NPChar)))),
						StringFromKey("Havana_Waitress_4", pchar),
						StringFromKey("Havana_Waitress_5", pchar),
						StringFromKey("Havana_Waitress_6", GetAddress_Form(NPChar)), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Havana_Waitress_9", RandPhraseSimple(
								StringFromKey("Havana_Waitress_7", pchar),
								StringFromKey("Havana_Waitress_8"))),
						StringFromKey("Havana_Waitress_10"),
						StringFromKey("Havana_Waitress_11"),
						StringFromKey("Havana_Waitress_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			if (CheckAttribute(pchar, "questTemp.State") && pchar.questTemp.State == "Fr3TakeAnna_WaitForMoney" && sti(pchar.money) >= 500)
			{
				link.l1 = StringFromKey("Havana_Waitress_13");
				link.l1.go = "Step_F3_3";
			}
			if (CheckAttribute(pchar, "questTemp.State") && pchar.questTemp.State == "Sp4Detection_FoundLetter")
			{
				dialog.text = StringFromKey("Havana_Waitress_14", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Havana_Waitress_15", pchar);
				link.l1.go = "Step_S4_1";
			}
			if (CheckAttribute(pchar, "questTemp.State") && pchar.questTemp.State == "Fr3TakeAnna_toHavana")
			{
				dialog.text = StringFromKey("Havana_Waitress_16", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Havana_Waitress_17");
				link.l1.go = "Step_F3_1";
			}
			if (CheckAttribute(pchar, "questTemp.State") && pchar.questTemp.State == "Fr3TakeAnna_WaitOneDay")
			{
				if (GetQuestPastDayParam("questTemp") > 0)
				{
					dialog.text = StringFromKey("Havana_Waitress_18", GetAddress_Form(NPChar));
					link.l1 = StringFromKey("Havana_Waitress_19");
					link.l1.go = "Step_F3_4";
				}
				else
				{
					dialog.text = StringFromKey("Havana_Waitress_20", UpperFirst(GetAddress_Form(NPChar)));
					link.l1 = StringFromKey("Havana_Waitress_21");
					link.l1.go = "exit";
				}
			}
		// <== Проверяем поле состояния квестов.
		break;
		//========================== Исп. линейка, квест №4. Расследование убийства ==================================
		case "Step_S4_1":
			dialog.text = StringFromKey("Havana_Waitress_22", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Havana_Waitress_23");
			link.l1.go = "Step_S4_2";
		break;
		case "Step_S4_2":
			dialog.text = StringFromKey("Havana_Waitress_24");
			link.l1 = StringFromKey("Havana_Waitress_25");
			link.l1.go = "Step_S4_3";
		break;
		case "Step_S4_3":
			dialog.text = StringFromKey("Havana_Waitress_26", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Havana_Waitress_27", pchar);
			link.l1.go = "Step_S4_4";
		break;
		case "Step_S4_4":
			dialog.text = StringFromKey("Havana_Waitress_28");
			link.l1 = StringFromKey("Havana_Waitress_29");
			link.l1.go = "Step_S4_5";
		break;
		case "Step_S4_5":
			dialog.text = StringFromKey("Havana_Waitress_30", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Havana_Waitress_31");
			link.l1.go = "Step_S4_6";
		break;
		case "Step_S4_6":
			dialog.text = StringFromKey("Havana_Waitress_32", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Havana_Waitress_33");
			link.l1.go = "Step_S4_7";
		break;
		case "Step_S4_7":
			dialog.text = StringFromKey("Havana_Waitress_34", UpperFirst(GetAddress_Form(NPChar)));
			link.l1 = StringFromKey("Havana_Waitress_35");
			link.l1.go = "Step_S4_8";
		break;
		case "Step_S4_8":
			dialog.text = StringFromKey("Havana_Waitress_36");
			link.l1 = StringFromKey("Havana_Waitress_37");
			link.l1.go = "Step_S4_9";
		break;
		case "Step_S4_9":
			dialog.text = StringFromKey("Havana_Waitress_38", GetAddress_Form(NPChar), UpperFirst(GetAddress_Form(NPChar)));
			link.l1 = StringFromKey("Havana_Waitress_39");
			link.l1.go = "Step_S4_10";
		break;
		case "Step_S4_10":
			dialog.text = StringFromKey("Havana_Waitress_40", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Havana_Waitress_41");
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp4Detection_toGovernor";
			AddQuestRecord("Spa_Line_4_MirderDetection", "3");
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
		break;
		//========================== Фр. линейка, квест №3. Увезти донну Анну ==================================
		case "Step_F3_1":
			dialog.text = StringFromKey("Havana_Waitress_42", pchar);
			link.l1 = StringFromKey("Havana_Waitress_43");
			link.l1.go = "Step_F3_2";
		break;
		case "Step_F3_2":
			if (sti(pchar.money) < 500)
			{
				pchar.questTemp.State = "Fr3TakeAnna_WaitForMoney";
				dialog.text = StringFromKey("Havana_Waitress_44");
				link.l1 = StringFromKey("Havana_Waitress_45");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Havana_Waitress_46");
				link.l1 = StringFromKey("Havana_Waitress_47", pchar);
				link.l1.go = "Step_F3_3";
			}
		break;
		case "Step_F3_3":
			AddMoneyToCharacter(pchar, -500);
			dialog.text = StringFromKey("Havana_Waitress_48", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Havana_Waitress_49");
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "DOjeronRing");
			pchar.questTemp.State = "Fr3TakeAnna_WaitOneDay";
			SaveCurrentQuestDateParam("questTemp");
			AddQuestRecord("Fra_Line_3_TakeAnna", "2");
			AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "FraLine_3_WaitOneDay_QuestMarkCondition");
		break;
		case "Step_F3_4":
			dialog.text = StringFromKey("Havana_Waitress_50");
			link.l1 = StringFromKey("Havana_Waitress_51");
			link.l1.go = "Step_F3_5";
		break;
		case "Step_F3_5":
			dialog.text = StringFromKey("Havana_Waitress_52", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Havana_Waitress_53");
			link.l1.go = "Step_F3_6";
		break;
		case "Step_F3_6":
			dialog.text = StringFromKey("Havana_Waitress_54", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Havana_Waitress_55");
			link.l1.go = "Step_F3_7";
		break;
		case "Step_F3_7":
			dialog.text = StringFromKey("Havana_Waitress_56");
			link.l1 = StringFromKey("Havana_Waitress_57");
			link.l1.go = "Step_F3_8";
		break;
		case "Step_F3_8":
			dialog.text = StringFromKey("Havana_Waitress_58", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Havana_Waitress_59");
			link.l1.go = "Step_F3_9";
		break;
		case "Step_F3_9":
			dialog.text = StringFromKey("Havana_Waitress_60", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Havana_Waitress_61");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -500);
			AddQuestRecord("Fra_Line_3_TakeAnna", "3");
			AddQuestUserData("Fra_Line_3_TakeAnna", "sSex", GetSexPhrase("ёл", "ла"));
			GiveItem2Character(pchar, "letter_FraLineQ3");
			pchar.questTemp.State = "Fr3TakeAnna_WaitMidnight";
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
		//========================== Тревога в таверне Гаваны ==================================
		case "Allarm":
			dialog.text = StringFromKey("Havana_Waitress_62", pchar);
			link.l1 = StringFromKey("Havana_Waitress_63");
			link.l1.go = "Step_F_Allarm";
		break;
		case "Step_F_Allarm":
			NextDiag.CurrentNode = "First time";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = true; // закрыть выход из локации.
			GetCharacterPos(pchar, &locx, &locy, &locz);
			for (int i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SpaGuard" + i, "urban_spa_" + (rand(7) + 1), "man", "man", 20, SPAIN, 0, true)); //watch_quest_moment
				FantomMakeCoolFighter(sld, 20, 60, 50, BLADE_LONG, "pistol3", 30);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "Havana_tavern", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "CannotFightCurLocation");
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //на всякий случай	
			LAi_SetWaitressType(npchar);
			LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			DialogExit();
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
