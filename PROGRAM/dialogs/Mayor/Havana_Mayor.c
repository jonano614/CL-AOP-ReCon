// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref FortChref;
	FortChref = GetFortCommander(NPChar.City);
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Havana_Mayor_3", RandPhraseSimple(
								StringFromKey("Havana_Mayor_1"),
								StringFromKey("Havana_Mayor_2"))),
						StringFromKey("Havana_Mayor_4"),
						StringFromKey("Havana_Mayor_5"),
						StringFromKey("Havana_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Havana_Mayor_9", RandPhraseSimple(
								StringFromKey("Havana_Mayor_7", pchar),
								StringFromKey("Havana_Mayor_8"))),
						StringFromKey("Havana_Mayor_10"),
						StringFromKey("Havana_Mayor_11"),
						StringFromKey("Havana_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
			dialog.text = StringFromKey("Havana_Mayor_15", RandPhraseSimple(
						StringFromKey("Havana_Mayor_13"),
						StringFromKey("Havana_Mayor_14")));
			link.l1 = StringFromKey("Havana_Mayor_18", RandPhraseSimple(
						StringFromKey("Havana_Mayor_16"),
						StringFromKey("Havana_Mayor_17", pchar)));
			link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
		break;

		case "Slavetrader_HavanaAttack":
			dialog.text = StringFromKey("Havana_Mayor_19");
			link.l1 = StringFromKey("Havana_Mayor_20");
			link.l1.go = "Slavetrader_HavanaAttack_1";
			pchar.quest.Slavetrader_HavanaOver.over = "yes";
			AfterTownBattle();
		break;

		case "Slavetrader_HavanaAttack_1":
			dialog.text = StringFromKey("Havana_Mayor_21");
			link.l1 = StringFromKey("Havana_Mayor_22");
			link.l1.go = "Slavetrader_HavanaAttack_2";
		break;

		case "Slavetrader_HavanaAttack_2":
			if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)//для особо хитрых - нефиг лезть с суши
			{
				dialog.text = StringFromKey("Havana_Mayor_23");
				link.l1 = StringFromKey("Havana_Mayor_24");
				link.l1.go = "Slavetrader_HavanaAttack_lose";
			}
			else
			{
				dialog.text = StringFromKey("Havana_Mayor_25");
				link.l1 = StringFromKey("Havana_Mayor_26");
				link.l1.go = "Slavetrader_HavanaAttack_3";
			}
		break;

		case "Slavetrader_HavanaAttack_3":
			dialog.text = StringFromKey("Havana_Mayor_27");
			link.l1 = StringFromKey("Havana_Mayor_28");
			link.l1.go = "Slavetrader_HavanaAttack_4";
			ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 50);
			ChangeCharacterReputation(pchar, -8);
		break;

		case "Slavetrader_HavanaAttack_4":
			string sTemp;
			NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			Achievement_AddStats_SturmColonies();
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//теперь можно на карту
			SetCharacterGoods(pchar, GOOD_SLAVES, 5000 + rand(500));// c перегрузом пойдет
			Log_SetStringToLog(StringFromKey("InfoMessages_187"));
			Log_SetStringToLog(StringFromKey("InfoMessages_188"));
			chrDisableReloadToLocation = false;
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			AddQuestRecord("Slavetrader", "27");
			AddQuestUserData("Slavetrader", "sQty", FindSlavesString(sti(sTemp)));
			SetFunctionTimerCondition("Slavetrader_FiveTSlavesOver", 0, 0, 30, false);    //таймер
			pchar.questTemp.Slavetrader = "Win_HavanaFort";
			AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.Slavetrader.UsurerId), "Slavetrader");
			DeleteAttributeMass(&TEV, "Music", "KeepPlaying,ForceKeepPlaying,PreviousTrack,ForcePlayTrack");
		break;

		case "Slavetrader_HavanaAttack_lose":
			NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			ChangeCharacterReputation(pchar, -8);
			Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			Achievement_AddStats_SturmColonies();
			chrDisableReloadToLocation = false;
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//можно на карту
			pchar.quest.Slavetrader_HavanaAttack.over = "yes";//если из Сантьяго по суше пришёл - уберем корабли
			AddQuestRecord("Slavetrader", "27_1");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

