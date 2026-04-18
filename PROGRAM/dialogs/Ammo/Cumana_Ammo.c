// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = StringFromKey("Cumana_Ammo_1");
			link.l1 = StringFromKey("Cumana_Ammo_2", pchar);
			link.l1.go = "Exit";
			// Опасный груз -->
			if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
			{
				link.l4 = StringFromKey("Cumana_Ammo_3");
				link.l4.go = "zpq_prs1";
			}
			if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 50000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
			{
				link.l5 = StringFromKey("Cumana_Ammo_4");
				link.l5.go = "zpq_ex";
			}
			if (pchar.questTemp.zpq == "begin")
			{
				link.l6 = StringFromKey("Cumana_Ammo_5");
				link.l6.go = "zpq_fld2";
			}
		// <-- Опасный груз
		break;

		// Опасный груз -->
		case "zpq_prs1":
		//			if(!isBadReputation(pchar, 70))
			if (!PlayerRPGCheck_BadReputation(70, true))
			{
				dialog.text = StringFromKey("Cumana_Ammo_6");
				link.l1 = StringFromKey("Cumana_Ammo_7", pchar);
				link.l1.go = "zpq_prs2";
				link.l2 = StringFromKey("Cumana_Ammo_8");
				link.l2.go = "zpq_fld";
			}
			else
			{
				dialog.text = StringFromKey("Cumana_Ammo_9");
				link.l1 = StringFromKey("Cumana_Ammo_10");
				link.l1.go = "exit";
			}
		break;
		case "zpq_fld":
			dialog.text = StringFromKey("Cumana_Ammo_11");
			link.l1 = StringFromKey("Cumana_Ammo_12");
			link.l1.go = "exit";
			pchar.questTemp.zpq = "failed";
			RemoveLandQuestmarkToFantoms_Main("AmmoOff", "zpq");
			RemoveMapQuestMark("Cumana_Fort", "zpq");
		break;
		case "zpq_fld2":
			dialog.text = StringFromKey("Cumana_Ammo_13");
			link.l1 = StringFromKey("Cumana_Ammo_14");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -10);

			if (pchar.questTemp.zpq == "begin")
			{
				AddQuestRecord("zpq", "6");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("", "а"));
				CloseQuestHeader("zpq");
			}
			pchar.questTemp.zpq = "failed";
			RemoveLandQuestmarkToFantoms_Main("AmmoOff", "zpq");
			RemoveMapQuestMark("Cumana_Fort", "zpq");
		break;
		case "zpq_prs2":
			dialog.text = StringFromKey("Cumana_Ammo_15");
			link.l1 = StringFromKey("Cumana_Ammo_16");
			link.l1.go = "zpq_prs3";
		break;
		case "zpq_prs3":
			dialog.text = StringFromKey("Cumana_Ammo_17");
			link.l1 = StringFromKey("Cumana_Ammo_18");
			link.l1.go = "zpq_prs4";
		break;
		case "zpq_prs4":
			dialog.text = StringFromKey("Cumana_Ammo_19");
			link.l1 = StringFromKey("Cumana_Ammo_20");
			link.l1.go = "zpq_prs5";
			link.l2 = StringFromKey("Cumana_Ammo_21", GetAddress_FormToNPC(NPChar));
			link.l2.go = "zpq_fld2";
		break;
		case "zpq_prs5":
			dialog.text = StringFromKey("Cumana_Ammo_22");
			link.l1 = StringFromKey("Cumana_Ammo_23", GetAddress_FormToNPC(NPChar));
			link.l1.go = "zpq_prs5_ok";
		break;
		case "zpq_prs5_ok":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.zpq = "begin";
			pchar.questTemp.zpq.time = 20;
			AddQuestRecord("zpq", "1");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("", "а"));
			SaveCurrentQuestDateParam("pchar.questTemp.zpq");
			AddLandQuestmarkToFantoms_Main("AmmoOff", "zpq", "zpq_WaitPowder_AmmoOff_QuestMarkCondition");
			RemoveMapQuestMark("Cumana_Fort", "zpq");
		break;
		case "zpq_ex":
			dialog.text = StringFromKey("Cumana_Ammo_24");
			link.l1 = StringFromKey("Cumana_Ammo_25", pchar, GetAddress_FormToNPC(NPChar));
			link.l1.go = "zpq_ex2";
			RemoveCharacterGoods(pchar, GOOD_POWDER, 50000);
			AddCharacterExpToSkill(pchar, "Sailing", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 500);
			pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
			pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
			pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
		break;
		case "zpq_ex2":
			dialog.text = StringFromKey("Cumana_Ammo_26");
			link.l1 = StringFromKey("Cumana_Ammo_27", pchar, GetAddress_FormToNPC(NPChar));
			link.l1.go = "zpq_ex3";
			link.l2 = StringFromKey("Cumana_Ammo_28");
			link.l2.go = "zpq_ex4";
			link.l3 = StringFromKey("Cumana_Ammo_29", pchar);
			link.l3.go = "zpq_ex5";
		break;
		case "zpq_ex3":
		//			if (GetSummonSkillFromName(pchar, "Leadership") > 50)
			if (PlayerRPGCheck_Skill("Leadership", 51, false))
			{
				dialog.text = StringFromKey("Cumana_Ammo_30");
				link.l1 = StringFromKey("Cumana_Ammo_31", GetAddress_FormToNPC(NPChar));
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
				AddQuestRecord("zpq", "2");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("", "а"));
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 300000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
				RemoveLandQuestmarkToFantoms_Main("AmmoOff", "zpq");
			}
			else
			{
				dialog.text = StringFromKey("Cumana_Ammo_32");
				link.l1 = StringFromKey("Cumana_Ammo_33", GetAddress_FormToNPC(NPChar));
				link.l1.go = "zpq_ex_agry";
				link.l2 = StringFromKey("Cumana_Ammo_34");
				link.l2.go = "zpq_ex5";
			}
		break;
		case "zpq_ex4":
			dialog.text = StringFromKey("Cumana_Ammo_35");
			link.l1 = StringFromKey("Cumana_Ammo_36");
			link.l1.go = "zpq_ex6";
		break;
		case "zpq_ex6":
		//			if (GetSummonSkillFromName(pchar, "Leadership") > 75)
			if (PlayerRPGCheck_Skill("Leadership", 76, false))
			{
				dialog.text = StringFromKey("Cumana_Ammo_37");
				link.l1 = StringFromKey("Cumana_Ammo_38", GetAddress_FormToNPC(NPChar));
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
				AddQuestRecord("zpq", "5");
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 450000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
				RemoveLandQuestmarkToFantoms_Main("AmmoOff", "zpq");
			}
			else
			{
				dialog.text = StringFromKey("Cumana_Ammo_39", pchar);
				link.l1 = StringFromKey("Cumana_Ammo_40");
				link.l1.go = "zpq_ex_war";
			}
		break;
		case "zpq_ex5":
			dialog.text = StringFromKey("Cumana_Ammo_41");
			link.l1 = StringFromKey("Cumana_Ammo_42");
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
			AddQuestRecord("zpq", "3");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 150000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			RemoveLandQuestmarkToFantoms_Main("AmmoOff", "zpq");
		break;
		case "zpq_ex_agry":
			dialog.text = StringFromKey("Cumana_Ammo_43", pchar);
			link.l1 = StringFromKey("Cumana_Ammo_44");
			link.l1.go = "zpq_ex_war";
		break;
		case "zpq_ex_war":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			Flag_PIRATE();
			pchar.questTemp.zpq = "failed";
			AddQuestRecord("zpq", "4");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 150000;
			AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum) * 2 + rand(5000)));
			GiveItem2Character(npchar, "blade20");
			EquipCharacterbyItem(npchar, "blade20");
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			npchar.cirassId = FindItem("cirass3");
			chrDisableReloadToLocation = true;
			string slai_group = GetNationNameByType(sti(npchar.nation)) + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_group_SetCheck(slai_group, "OpenTheDoors");
			RemoveLandQuestmarkToFantoms_Main("AmmoOff", "zpq");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
