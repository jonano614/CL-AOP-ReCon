// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Santiago_Tavern_3", RandPhraseSimple(
								StringFromKey("Santiago_Tavern_1"),
								StringFromKey("Santiago_Tavern_2", GetAddress_Form(NPChar)))),
						StringFromKey("Santiago_Tavern_4", GetAddress_Form(NPChar)),
						StringFromKey("Santiago_Tavern_5"),
						StringFromKey("Santiago_Tavern_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Santiago_Tavern_9", RandPhraseSimple(
								StringFromKey("Santiago_Tavern_7", pchar),
								StringFromKey("Santiago_Tavern_8"))),
						StringFromKey("Santiago_Tavern_10"),
						StringFromKey("Santiago_Tavern_11"),
						StringFromKey("Santiago_Tavern_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			switch (pchar.questTemp.State)
			{
				case "RevengeMansfield_toTavern": //Голландская линейка, квест №6. Узнать инфу о губере.
					link.l2 = StringFromKey("Santiago_Tavern_13");
					link.l2.go = "Step_H6_1";
				break;
				case "Fr7RockBras_toSeekPlace": //Фр. линейка, квест №7. Узнать инфу о Роке Бразильце.
					link.l1 = StringFromKey("Santiago_Tavern_14", pchar);
					link.l1.go = "Step_F7_1";
				break;
			}
		// <== Проверяем поле состояния квестов.
		break;
		//**************************** Голл. линейка, квест №6. Узнать для Моргана инфу о губере Сантьяго ************************
		case "Step_H6_1":
			dialog.text = StringFromKey("Santiago_Tavern_15");
			link.l1 = StringFromKey("Santiago_Tavern_16");
			link.l1.go = "Step_H6_2";
		break;
		case "Step_H6_2":
			dialog.text = StringFromKey("Santiago_Tavern_17");
			link.l1 = StringFromKey("Santiago_Tavern_18");
			link.l1.go = "Step_H6_3";
		break;
		case "Step_H6_3":
			dialog.text = StringFromKey("Santiago_Tavern_19");
			link.l1 = StringFromKey("Santiago_Tavern_20");
			link.l1.go = "Step_H6_4";
		break;
		case "Step_H6_4":
			dialog.text = StringFromKey("Santiago_Tavern_21");
			link.l1 = StringFromKey("Santiago_Tavern_22");
			link.l1.go = "Step_H6_5";
		break;
		case "Step_H6_5":
			dialog.text = StringFromKey("Santiago_Tavern_23");
			link.l1 = StringFromKey("Santiago_Tavern_24");
			link.l1.go = "Step_H6_6";
		break;
		case "Step_H6_6":
			dialog.text = StringFromKey("Santiago_Tavern_25");
			link.l1 = StringFromKey("Santiago_Tavern_26");
			link.l1.go = "Step_H6_7";
		break;
		case "Step_H6_7":
			dialog.text = StringFromKey("Santiago_Tavern_27");
			link.l1 = StringFromKey("Santiago_Tavern_28");
			link.l1.go = "Step_H6_8";
		break;
		case "Step_H6_8":
			dialog.text = StringFromKey("Santiago_Tavern_29", pchar);
			link.l1 = StringFromKey("Santiago_Tavern_30");
			link.l1.go = "Step_H6_9";
		break;
		case "Step_H6_9":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = true; // закрыть выход из локации
			AddQuestRecord("Hol_Line_6_RevengeMansfield", "3");
			//HardCoffee реф диалогов Моргана
			//QuestSetCurrentNode("Henry Morgan", "HolLine6_fromSantiago");
			pchar.QuestTemp.HolLine_quests_task = "fromSantiago";
			//==> потом вернуть
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			//<== потом вернуть
			LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
			LAi_group_MoveCharacter(characterFromID("Santiago_waitress"), "SPAIN_CITIZENS");
			LAi_group_Delete("QuestGroup");
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //если флаг сменен
			ref sld;
			for (int i = 1; i <= 2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Solder" + i, "off_spa_" + i, "man", "man", 30, SPAIN, 0, true)); //watch_quest_moment
				FantomMakeCoolFighter(sld, 30, 100, 80, "blade33", "pistol3", 120);

				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
			LAi_group_SetLookRadius("EnemyFight", 100);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "CannotFightCurLocation");
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(characterFromID("Henry Morgan"), "Hol_Line");
		break;
		//**************************** Фр. линейка, квест №7. Узнать инфу о Роке Бразильце ************************
		case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Santiago_Tavern_31"),
						StringFromKey("Santiago_Tavern_32"),
						StringFromKey("Santiago_Tavern_33"),
						StringFromKey("Santiago_Tavern_34"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Santiago_Tavern_35"),
						StringFromKey("Santiago_Tavern_36", pchar),
						StringFromKey("Santiago_Tavern_37", pchar),
						StringFromKey("Santiago_Tavern_38"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F7_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_F7_2":
			dialog.text = StringFromKey("Santiago_Tavern_39");
			link.l1 = StringFromKey("Santiago_Tavern_40");
			link.l1.go = "Step_F7_3";
		break;
		case "Step_F7_3":
			dialog.text = StringFromKey("Santiago_Tavern_41", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Santiago_Tavern_42");
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
