void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			if (Pchar.Location == Pchar.location.from_sea)
			{
				dialog.text = StringFromKey("pSQ_Smuggler_dialog_1", pchar);
				link.l1 = StringFromKey("pSQ_Smuggler_dialog_2");
				link.l1.go = "pirateStartQuest_Smuggler3_1";
			}
			else
			{
				dialog.text = StringFromKey("pSQ_Smuggler_dialog_3", pchar);
				link.l1 = StringFromKey("pSQ_Smuggler_dialog_4", pchar);
				link.l1.go = "exit";

			}
		break;
		case "pirateStartQuest_Smuggler3_1":
			pchar.quest.pirateStartQuest_Smuggler_fc.over = "yes";
			pchar.quest.pirateStartQuest_Smuggler_RemoveSmugglers.over = "yes";

			dialog.text = StringFromKey("pSQ_Smuggler_dialog_5", pchar, GetFullName(CharacterFromID(pchar.questTemp.pirateStartQuest.BaronId)));
			link.l1 = StringFromKey("pSQ_Smuggler_dialog_6", pchar);
			link.l1.go = "pirateStartQuest_Smuggler3_2";
		break;
		case "pirateStartQuest_Smuggler3_2":
			dialog.text = StringFromKey("pSQ_Smuggler_dialog_7");
			//			if (sti(pchar.money) >= 15000 && GetCharacterSPECIAL(pchar, SPECIAL_C) >= 7)
			if (sti(pchar.money) >= 15000 && PlayerRPGCheck_SPECIAL(SPECIAL_C, 7))
			{
				link.l1 = StringFromKey("pSQ_Smuggler_dialog_8");
				link.l1.go = "Exit_pirateStartQuest_Smuggler_LoadSlaves";
			}
			link.l2 = StringFromKey("pSQ_Smuggler_dialog_9");
			link.l2.go = "pirateStartQuest_Smuggler3_5";
			GiveItem2Character(npchar, "pirateStartQuest");
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
		break;

		case "Exit_pirateStartQuest_Smuggler_LoadSlaves":
			TEV.pirateStartQuest_SmugglerCharId = npchar.id;
			AddDialogExitQuestFunction("pirateStartQuest_Smuggler_LoadSlaves");
			NextDiag.TempNode = "pirateStartQuest_Smuggler3_3";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "pirateStartQuest_Smuggler3_3":
			TEV.pSQ_SmugglerPatrolNoTalk = true;

			dialog.text = StringFromKey("pSQ_Smuggler_dialog_10");
			link.l1 = StringFromKey("pSQ_Smuggler_dialog_11");
			link.l1.go = "pirateStartQuest_Smuggler3_5";
			AddMoneyToCharacter(pchar, -15000);
			AddMoneyToCharacter(npchar, 15000);
			AddCharacterGoods(pchar, GOOD_SLAVES, 100);
			AddQuestUserData("pSQ", "sText", StringFromKey("pSQ_Smuggler_dialog_51", pchar));
		break;
		case "pirateStartQuest_Smuggler3_5":
			dialog.text = StringFromKey("pSQ_Smuggler_dialog_12");
			link.l1 = StringFromKey("pSQ_Smuggler_dialog_13");
			link.l1.go = "pirateStartQuest_Smuggler3_6";
		break;
		case "pirateStartQuest_Smuggler3_6":
			dialog.text = StringFromKey("pSQ_Smuggler_dialog_14", GetFullName(CharacterFromID(pchar.questTemp.pirateStartQuest.BaronId)));
			link.l1 = StringFromKey("pSQ_Smuggler_dialog_15");
			link.l1.go = "pirateStartQuest_Smuggler3_7";
		break;
		case "pirateStartQuest_Smuggler3_7":
			chrDisableReloadToLocation = true;
			RemoveGeometryFromLocation(pchar.questTemp.pirateStartQuest.Shore, "smg");
			ref sld;
			for (int i = 1; i <= 3; i++)
			{
				sld = CharacterFromID("psq2_" + i);
				LAi_SetImmortal(sld, false);
				RemoveLandQuestMark_Main(sld, "pSQ");
			}

			LAi_group_SetRelation("pirateStartQuest_Smuggler_group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("pirateStartQuest_Smuggler_group", LAI_GROUP_PLAYER, true);
			LAi_Group_SetCheckFunction("pirateStartQuest_Smuggler_group", "pirateStartQuest_Smuggler_group_dead");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetPlayerType(pchar);

			pchar.quest.pirateStartQuest_Lether_fc.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirateStartQuest_Lether_fc.win_condition.l1.location = pchar.location;
			pchar.quest.pirateStartQuest_Lether_fc.function = "pirateStartQuest_Lether_fc";

			pchar.quest.pirateStartQuest_Lether_fc1.win_condition.l1 = "item";
			pchar.quest.pirateStartQuest_Lether_fc1.win_condition.l1.item = "pirateStartQuest";
			pchar.quest.pirateStartQuest_Lether_fc1.function = "pirateStartQuest_Lether_fc1";

			AddQuestRecord("pSQ", "5");
			AddQuestUserData("pSQ", "sSex", GetSexPhrase("ёл", "ла"));
			AddQuestUserData("pSQ", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City2 + "Gen"));
		break;

		// Патруль после схватки
		case "pirateStartQuest_Patrol1":
			LAi_LockFightMode(pchar, false);
			dialog.text = StringFromKey("pSQ_Smuggler_dialog_16", pchar);
			link.l1 = StringFromKey("pSQ_Smuggler_dialog_17");
			link.l1.go = "pirateStartQuest_Patrol2";
		break;
		case "pirateStartQuest_Patrol2":
			if (CheckAttribute(&TEV, "pSQ_SmugglerPatrolNoTalk"))
			{
				DeleteAttribute(&TEV, "pSQ_SmugglerPatrolNoTalk");
				dialog.text = StringFromKey("pSQ_Smuggler_dialog_18", pchar);
				link.l1 = StringFromKey("pSQ_Smuggler_dialog_19");
				link.l1.go = "Exit_pirateStartQuest_PatrolFight";
			}
			else
			{
				dialog.text = StringFromKey("pSQ_Smuggler_dialog_20");

				if (GetCharacterReputation_WithNation(pchar, sti(npchar.nation)) > 20) // ReputationGood или выше
				{
					link.l1 = StringFromKey("pSQ_Smuggler_dialog_21");
					link.l1.go = "pirateStartQuest_PatrolRep";
				}
				else
				{
					PlayerRPGCheck_NationReputation_NotifyFail(sti(npchar.nation));
				}
				//                if (GetCharacterSPECIAL(pchar, SPECIAL_C) >= 5)
				if (PlayerRPGCheck_SPECIAL(SPECIAL_C, 5))
				{
					link.l2 = StringFromKey("pSQ_Smuggler_dialog_22");
					link.l2.go = "pirateStartQuest_PatrolAllure";
				}
				if (sti(pchar.money) >= 4000)
				{
					link.l3 = StringFromKey("pSQ_Smuggler_dialog_23");
					link.l3.go = "pirateStartQuest_PatrolMoney";
				}

				link.l4 = StringFromKey("pSQ_Smuggler_dialog_24");
				link.l4.go = "pirateStartQuest_PatrolFight";
			}
		break;
		case "pirateStartQuest_PatrolRep":
			dialog.text = StringFromKey("pSQ_Smuggler_dialog_25");
			link.l1 = StringFromKey("pSQ_Smuggler_dialog_26");
			link.l1.go = "pirateStartQuest_PatrolRep_1";
		break;
		case "pirateStartQuest_PatrolRep_1":
			dialog.text = StringFromKey("pSQ_Smuggler_dialog_27", GetFullName(pchar));

			ChangeCharacterReputation(pchar, 5); // plus rep

			link.l1 = StringFromKey("pSQ_Smuggler_dialog_28");
			link.l1.go = "Exit_pirateStartQuest_PatrolEvadeFight";
		break;
		case "Exit_pirateStartQuest_PatrolEvadeFight":
			DoQuestFunctionDelay("pirateStartQuest_Smuggler_patrol_note_NoFight", 1.2);
			DialogExit();
		break;
		case "pirateStartQuest_PatrolAllure":
			dialog.text = StringFromKey("pSQ_Smuggler_dialog_29");
			link.l1 = StringFromKey("pSQ_Smuggler_dialog_30");
			link.l1.go = "pirateStartQuest_PatrolAllure_2";
		break;
		case "pirateStartQuest_PatrolAllure_2":
			dialog.text = StringFromKey("pSQ_Smuggler_dialog_31");
			link.l1 = StringFromKey("pSQ_Smuggler_dialog_32");
			link.l1.go = "pirateStartQuest_PatrolAllure_3";
		break;
		case "pirateStartQuest_PatrolAllure_3":
			dialog.text = StringFromKey("pSQ_Smuggler_dialog_33");
			link.l1 = StringFromKey("pSQ_Smuggler_dialog_34", pchar);
			link.l1.go = "pirateStartQuest_PatrolAllure_4";
		break;
		case "pirateStartQuest_PatrolAllure_4":
			dialog.text = StringFromKey("pSQ_Smuggler_dialog_35");
			link.l1 = StringFromKey("pSQ_Smuggler_dialog_36");
			link.l1.go = "pirateStartQuest_PatrolAllure_5";
		break;
		case "pirateStartQuest_PatrolAllure_5":
			dialog.text = StringFromKey("pSQ_Smuggler_dialog_37");
			link.l1 = StringFromKey("pSQ_Smuggler_dialog_38", pchar);
			link.l1.go = "Exit_pirateStartQuest_PatrolEvadeFight";
		break;
		case "pirateStartQuest_PatrolMoney":
			dialog.text = StringFromKey("pSQ_Smuggler_dialog_39");
			link.l1 = StringFromKey("pSQ_Smuggler_dialog_40");
			link.l1.go = "pirateStartQuest_PatrolMoney_1";
			link.l2 = StringFromKey("pSQ_Smuggler_dialog_41");
			link.l2.go = "pirateStartQuest_PatrolMoney_2";
		break;
		case "pirateStartQuest_PatrolMoney_1":
			dialog.text = StringFromKey("pSQ_Smuggler_dialog_42");
			link.l1 = StringFromKey("pSQ_Smuggler_dialog_43");
			link.l1.go = "pirateStartQuest_PatrolMoney_2";
			link.l2 = StringFromKey("pSQ_Smuggler_dialog_44");
			link.l2.go = "pirateStartQuest_PatrolMoney_refuse";
		break;
		case "pirateStartQuest_PatrolMoney_refuse":
			dialog.text = StringFromKey("pSQ_Smuggler_dialog_45");
			link.l1 = StringFromKey("pSQ_Smuggler_dialog_46");
			link.l1.go = "pirateStartQuest_PatrolFight";
		break;
		case "pirateStartQuest_PatrolMoney_2":
			dialog.text = StringFromKey("pSQ_Smuggler_dialog_47");

			// take money
			AddMoneyToCharacter(pchar, -4000);
			AddCharacterExpToSkill(pchar, "Commerce", 25);

			link.l1 = StringFromKey("pSQ_Smuggler_dialog_48");
			link.l1.go = "Exit_pirateStartQuest_PatrolEvadeFight";
		break;
		case "pirateStartQuest_PatrolFight":
			dialog.text = StringFromKey("pSQ_Smuggler_dialog_49");
			link.l1 = StringFromKey("pSQ_Smuggler_dialog_50");
			link.l1.go = "Exit_pirateStartQuest_PatrolFight";
		break;
		case "Exit_pirateStartQuest_PatrolFight":
			DialogExit();

			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, true);

			LAi_group_SetRelation("pirateStartQuest_SmugglerPatrol_group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("pirateStartQuest_SmugglerPatrol_group", LAI_GROUP_PLAYER, true);
			LAi_Group_SetCheckFunction("pirateStartQuest_SmugglerPatrol_group", "pirateStartQuest_Smuggler_patrol_dead");
		break;
	}
}





