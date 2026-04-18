// диалог протекторов, солдат и мушкетеров кланов LSC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	ref location;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string sAttr;
	int j;

	sAttr = Dialog.CurrentNode;
	if (HasStr(sAttr, "LSCParolChooseAnswer_"))
	{
		j = findsubstr(sAttr, "_", 0);
		TEV.LSCParolCheck.Answer = strcut(sAttr, j + 1, strlen(sAttr) - 1);
		Dialog.CurrentNode = "check_parol_1_chinese";
	}

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("Guardian_1");
			link.l1 = StringFromKey("Guardian_2");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		/* case "SoldierNotBlade": //HardCoffee ref SoldierNotBlade CitizenNotBlade
			 dialog.text = "Убери своё оружие!";
			 link.l1 = "Ладно.";
			 link.l1.go = "exit";
			 link.l2 = "Лучше я его использую по назначению.";
			 link.l2.go = "fight";
		 break;*/

		//------------------------------------- фразы охраны нарвалов --------------------------------------------
		// пост нарвалов
		case "Narval_warning":
			location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "nrv_parolinfo"))
			{
				dialog.text = StringFromKey("Guardian_3", pchar);
				link.l1 = StringFromKey("Guardian_4");
				link.l1.go = "Narval_warning_yes";
				link.l2 = StringFromKey("Guardian_5");
				link.l2.go = "Narval_warning_no";
				location.nrv_parolinfo = true;
			}
			else
			{
				dialog.text = StringFromKey("Guardian_6", pchar);
				link.l1 = StringFromKey("Guardian_7");
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;

		case "Narval_warning_yes":
			dialog.text = StringFromKey("Guardian_8", pchar);
			link.l1 = StringFromKey("Guardian_9");
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;

		case "Narval_warning_no":
			dialog.text = StringFromKey("Guardian_10", pchar);
			link.l1 = StringFromKey("Guardian_11");
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;

		case "Narval_warning_repeat":
			dialog.text = StringFromKey("Guardian_12", pchar);
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;

		case "Narval_parol":
			dialog.text = StringFromKey("Guardian_13");
			link.l1 = StringFromKey("Guardian_14");
			link.l1.go = "check_parol";
		break;

		case "check_parol":
			dialog.text = StringFromKey("Guardian_15");
			Link.l1.edit = 3;
			link.l1 = "";
			link.l1.go = "check_parol_1";

			LSCParol_Chinese_GenerateRandomAnswers(Npchar, Link);
		break;

		case "check_parol_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[3]);
			if (sTemp == pchar.questTemp.LSC.NarvalParol && CheckAttribute(pchar, "questTemp.LSC.NParol_bye"))
			{
				dialog.text = StringFromKey("Guardian_16");
				link.l1 = StringFromKey("Guardian_17");
				link.l1.go = "exit";
				LAi_SetGuardianType(npchar);
				LAi_group_MoveCharacter(npchar, "LSC_NARVAL");
				NextDiag.TempNode = "Narval_parol_repeat";
				pchar.questTemp.LSC.parol_nrv = true;
			}
			else
			{
				dialog.text = StringFromKey("Guardian_18");
				link.l1 = StringFromKey("Guardian_19");
				link.l1.go = "check_parol_fight";
			}
		break;

		case "check_parol_fight":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "LSC_NARVAL");
			LAi_group_Attack(npchar, pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Narval_parol_repeat":
			dialog.text = StringFromKey("Guardian_20");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
		break;

		case "Narval_soldier":
			dialog.text = StringFromKey("Guardian_21", pchar);
			link.l1 = StringFromKey("Guardian_22");
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_soldier";
		break;

		//------------------------------------- фразы охраны касперов --------------------------------------------
		// пост касперов
		case "Casper_warning":
			location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "crp_parolinfo"))
			{
				dialog.text = StringFromKey("Guardian_23");
				link.l1 = StringFromKey("Guardian_24");
				link.l1.go = "Casper_warning_yes";
				link.l2 = StringFromKey("Guardian_25");
				link.l2.go = "Casper_warning_no";
				location.crp_parolinfo = true;
			}
			else
			{
				dialog.text = StringFromKey("Guardian_26", pchar);
				link.l1 = StringFromKey("Guardian_27");
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Casper_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;

		case "Casper_warning_yes":
			dialog.text = StringFromKey("Guardian_28");
			link.l1 = StringFromKey("Guardian_29");
			link.l1.go = "exit";
			NextDiag.TempNode = "Casper_warning_repeat";
		break;

		case "Casper_warning_no":
			dialog.text = StringFromKey("Guardian_30", pchar);
			link.l1 = StringFromKey("Guardian_31");
			link.l1.go = "exit";
			NextDiag.TempNode = "Casper_warning_repeat";
		break;

		case "Casper_warning_repeat":
			dialog.text = StringFromKey("Guardian_32");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Casper_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;

		case "Casper_parol":
			dialog.text = StringFromKey("Guardian_33");
			link.l1 = StringFromKey("Guardian_34");
			link.l1.go = "Ccheck_parol";
		break;

		case "Ccheck_parol":
			dialog.text = StringFromKey("Guardian_35");
			Link.l1.edit = 3;
			link.l1 = "";
			link.l1.go = "Ccheck_parol_1";

			LSCParol_Chinese_GenerateRandomAnswers(Npchar, Link);
		break;

		case "Ccheck_parol_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[3]);
			if (sTemp == pchar.questTemp.LSC.CasperParol && CheckAttribute(pchar, "questTemp.LSC.CParol_bye"))
			{
				dialog.text = StringFromKey("Guardian_36");
				link.l1 = StringFromKey("Guardian_37");
				link.l1.go = "exit";
				LAi_SetGuardianType(npchar);
				LAi_group_MoveCharacter(npchar, "LSC_CASPER");
				NextDiag.TempNode = "Casper_parol_repeat";
				pchar.questTemp.LSC.parol_cpr = true;
			}
			else
			{
				dialog.text = StringFromKey("Guardian_38", pchar);
				link.l1 = StringFromKey("Guardian_39");
				link.l1.go = "Ccheck_parol_fight";
			}
		break;

		case "Ccheck_parol_fight":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "LSC_CASPER");
			LAi_group_Attack(npchar, pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Casper_parol_repeat":
			dialog.text = StringFromKey("Guardian_40");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Casper_parol_repeat";
		break;

		case "Casper_soldier":
			dialog.text = StringFromKey("Guardian_41");
			link.l1 = StringFromKey("Guardian_42");
			link.l1.go = "exit";
			NextDiag.TempNode = "Casper_soldier";
		break;

		//------------------------------------- фразы охраны ментов --------------------------------------------
		case "Ment_soldier":
			dialog.text = StringFromKey("Guardian_43");
			link.l1 = StringFromKey("Guardian_44");
			link.l1.go = "exit";
			NextDiag.TempNode = "Ment_soldier";
		break;

		case "Ment_NarvalAssault":
			if (sti(pchar.questTemp.LSC.qtyDeadNarvals) == 7) dialog.text = StringFromKey("Guardian_45");
			else dialog.text = StringFromKey("Guardian_46");
			link.l1 = StringFromKey("Guardian_47");
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
		break;

		//------------------------------------- фразы охраны ривадос --------------------------------------------
		case "Hello_Rivados":
			dialog.text = StringFromKey("Guardian_48");
			link.l1 = StringFromKey("Guardian_49");
			link.l1.go = "Hello_Rivados_1";
		break;
		case "Hello_Rivados_1":
			dialog.text = StringFromKey("Guardian_50");
			link.l1 = StringFromKey("Guardian_51");
			link.l1.go = "Hello_Rivados_3";
			link.l2 = StringFromKey("Guardian_52");
			link.l2.go = "Hello_Rivados_2";
		break;
		case "Hello_Rivados_2":
			dialog.text = StringFromKey("Guardian_53");
			link.l1 = StringFromKey("Guardian_54");
			link.l1.go = "Hello_Rivados_6";
		break;
		case "Hello_Rivados_3":
			dialog.text = StringFromKey("Guardian_55");
			link.l1 = StringFromKey("Guardian_56");
			link.l1.go = "Hello_Rivados_4";
			link.l2 = StringFromKey("Guardian_57");
			link.l2.go = "Hello_Rivados_2";
		break;
		case "Hello_Rivados_4":
			dialog.text = StringFromKey("Guardian_58");
			link.l1 = StringFromKey("Guardian_59");
			link.l1.go = "Hello_Rivados_5";
			NextDiag.TempNode = "Wait_Rivados";
		break;
		case "Hello_Rivados_5":
			sld = ItemsFromID("key3");
			sld.shown = false;
			DeleteAttribute(sld, "startLocation");
			DeleteAttribute(sld, "startLocator");
			if (CheckAttribute(sld, "particleId")) DeleteParticleSystem(sld.particleId); //очистка подсветки после взятия
			AddItemLog(pchar, "key3", "1", StringFromKey("InfoMessages_135", GetItemName("key3")), "Important_item");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetWarriorTypeNoGroup(npchar);
			AddDialogExitQuest("OpenTheDoors");
		break;
		case "Hello_Rivados_6":
			DialogExit();
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_group_SetRelation("LSC_RIVADOS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("LSC_RIVADOS", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("LSC_RIVADOS", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Wait_Rivados":
			dialog.text = StringFromKey("Guardian_60");
			link.l1 = StringFromKey("Guardian_63", RandPhraseSimple(
						StringFromKey("Guardian_61"),
						StringFromKey("Guardian_62")));
			link.l1.go = "exit";
			if (pchar.questTemp.LSC == "toSeekMechanik" && !CheckAttribute(npchar, "helpCheck") && CheckAttribute(pchar, "questTemp.LSC.suicideSquad"))
			{
				link.l2 = StringFromKey("Guardian_64");
				if (!CheckAttribute(pchar, "questTemp.LSC.MentosHelp")) link.l2.go = "Wait_Rivados_1";
				else link.l2.go = "Wait_Rivados_5";
			}
		break;
		case "Wait_Rivados_1":
			npchar.helpCheck = LSC_CheckDeceasedCaspers();
			if (npchar.helpCheck == "0")
			{
				dialog.text = StringFromKey("Guardian_65");
				link.l1 = StringFromKey("Guardian_66");
				link.l1.go = "exit";
				RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");
			}
			else if (CheckAttribute(pchar, "questTemp.LSC.MentosHelp"))
			{
				dialog.text = StringFromKey("Guardian_67");
				link.l1 = StringFromKey("Guardian_68");
				link.l1.go = "Wait_Rivados_3";
			}
			else
			{
				dialog.text = StringFromKey("Guardian_69", pchar);
				link.l1 = StringFromKey("Guardian_70");
				link.l1.go = "Wait_Rivados_2";
			}
		break;
		case "Wait_Rivados_2":
			dialog.text = StringFromKey("Guardian_71");
			link.l1 = StringFromKey("Guardian_72");
			link.l1.go = "exit";
			pchar.questTemp.LSC.RivadosHelp = true;
			AddQuestRecord("ISS_DefeatCasperClan", "13");
			NextDiag.TempNode = "Wait_RivadosPlan";
			pchar.quest.LSC_RivadosRevengeStart.win_condition.l1 = "Timer";
			pchar.quest.LSC_RivadosRevengeStart.win_condition.l1.date.hour = GetHour();
			pchar.quest.LSC_RivadosRevengeStart.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_RivadosRevengeStart.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_RivadosRevengeStart.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_RivadosRevengeStart.function = "LSC_RivadosRevengeStart"; // готовы
			pchar.quest.LSC_RivadosRevengeOver.win_condition.l1 = "Timer";
			pchar.quest.LSC_RivadosRevengeOver.win_condition.l1.date.hour = GetHour() + 2.0;
			pchar.quest.LSC_RivadosRevengeOver.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_RivadosRevengeOver.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_RivadosRevengeOver.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_RivadosRevengeOver.function = "LSC_RivadosRevengeOver"; // опоздание
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");
		break;
		case "Wait_Rivados_3":
			dialog.text = StringFromKey("Guardian_73");
			link.l1 = StringFromKey("Guardian_76", RandPhraseSimple(
						StringFromKey("Guardian_74"),
						StringFromKey("Guardian_75")));
			link.l1.go = "exit";
			NextDiag.TempNode = "Wait_Rivados_4";
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");
		break;
		case "Wait_Rivados_4":
			dialog.text = StringFromKey("Guardian_77");
			link.l1 = StringFromKey("Guardian_80", RandPhraseSimple(
						StringFromKey("Guardian_78"),
						StringFromKey("Guardian_79")));
			link.l1.go = "exit";
			NextDiag.TempNode = "Wait_Rivados_4";
		break;
		case "Wait_Rivados_5":
			dialog.text = StringFromKey("Guardian_81");
			link.l1 = StringFromKey("Guardian_82");
			link.l1.go = "Wait_Rivados_6";
		break;
		case "Wait_Rivados_6":
			dialog.text = StringFromKey("Guardian_83");
			link.l1 = StringFromKey("Guardian_86", RandPhraseSimple(
						StringFromKey("Guardian_84"),
						StringFromKey("Guardian_85")));
			link.l1.go = "exit";
			NextDiag.TempNode = "Wait_Rivados_4";
		break;

		case "Wait_RivadosPlan":
			dialog.text = StringFromKey("Guardian_87");
			link.l1 = StringFromKey("Guardian_88");
			link.l1.go = "exit";
		break;

		case "RivadosPlanStart":
			dialog.text = StringFromKey("Guardian_89");
			link.l1 = StringFromKey("Guardian_90");
			link.l1.go = "RivadosPlanStart_1";
		break;
		case "RivadosPlanStart_1":
			dialog.text = StringFromKey("Guardian_91");
			link.l1 = StringFromKey("Guardian_92");
			link.l1.go = "RivadosPlanStart_2";
		break;
		case "RivadosPlanStart_2":
			dialog.text = StringFromKey("Guardian_93");
			link.l1 = StringFromKey("Guardian_94");
			link.l1.go = "exit";
			AddQuestRecord("ISS_DefeatCasperClan", "14");
			NextDiag.TempNode = "Wait_Rivados";
			pchar.quest.LSC_RivadosRevengeOver.over = "yes";
			pchar.quest.LSC_RivadosRevengeAmbushStart.win_condition.l1 = "Timer";
			pchar.quest.LSC_RivadosRevengeAmbushStart.win_condition.l1.date.hour = 6;
			pchar.quest.LSC_RivadosRevengeAmbushStart.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_RivadosRevengeAmbushStart.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_RivadosRevengeAmbushStart.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_RivadosRevengeAmbushStart.function = "LSC_RivadosRevengeAmbushStart"; // готовы
			pchar.quest.LSC_RivadosRevengeAmbushOver.win_condition.l1 = "Timer";
			pchar.quest.LSC_RivadosRevengeAmbushOver.win_condition.l1.date.hour = 7;
			pchar.quest.LSC_RivadosRevengeAmbushOver.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_RivadosRevengeAmbushOver.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_RivadosRevengeAmbushOver.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_RivadosRevengeAmbushOver.function = "LSC_RivadosRevengeAmbushOver"; // опоздание
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");
		break;

		case "RivadosPlanOver":
			if (CheckAttribute(npchar, "revengeDone"))
			{
				dialog.text = StringFromKey("Guardian_95");
				link.l1 = StringFromKey("Guardian_96");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Guardian_97");
				link.l1 = StringFromKey("Guardian_98");
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Wait_Rivados";
		break;

		case "RivadosRevengeAmbushStart":
			pchar.quest.LSC_RivadosRevengeAmbushOver.over = "yes";
			int deceasedCaspers = LSC_CheckDeceasedCaspers();
			if (deceasedCaspers == 0)
			{
				dialog.text = StringFromKey("Guardian_99");
				link.l1 = StringFromKey("Guardian_100");
				link.l1.go = "RivadosRevengeAmbushEnd_1";
			}
			else
			{
				//если оба мушкетера живы
				bool checkStateOne = deceasedCaspers == 2 && !LAi_IsDead(CharacterFromId("CasperMush_3")) && !LAi_IsDead(CharacterFromId("CasperMush_4"));
				//если CasperMush_3 жив
				bool checkStateTwo = deceasedCaspers == 1 && !LAi_IsDead(CharacterFromId("CasperMush_3"));
				//если CasperMush_4 жив
				bool checkStateThree = deceasedCaspers == 1 && !LAi_IsDead(CharacterFromId("CasperMush_4"));
				if (checkStateOne || checkStateTwo || checkStateThree)
				{
					dialog.text = StringFromKey("Guardian_101");
					link.l1 = StringFromKey("Guardian_102");
					pchar.questTemp.LSC.SmallRivadosRevenge = true;
				}
				else
				{
					dialog.text = StringFromKey("Guardian_103");
					link.l1 = StringFromKey("Guardian_104");
				}
				link.l1.go = "RivadosRevengeAmbushStart_1";
			}
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");
		break;
		case "RivadosRevengeAmbushStart_1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorWaitDialog(pchar, npchar);
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestFunctionDelay("LSC_RivadosRevengeAct_1", 1.0);
		break;

		case "RivadosRevengeAmbushEnd":
			dialog.text = StringFromKey("Guardian_105");
			link.l1 = StringFromKey("Guardian_106");
			link.l1.go = "RivadosRevengeAmbushEnd_1";
		break;
		case "RivadosRevengeAmbushEnd_1":
			aref aTemp;
			makearef(aTemp, pchar.questTemp.LSC.suicideSquad);
			if (GetAttributesNum(aTemp) > 0) dialog.text = StringFromKey("Guardian_107");
			else dialog.text = StringFromKey("Guardian_108", pchar);
			link.l1 = StringFromKey("Guardian_109");
			link.l1.go = "RivadosRevengeAmbushEnd_2";
		break;
		case "RivadosRevengeAmbushEnd_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LSC_RivadosRevengeAmbushOver("ok");
			LAi_SetPlayerType(pchar);
			DoReloadCharacterToLocation("SanGabrielMechanic", "reload", "reload1");
			AddQuestRecord("ISS_DefeatCasperClan", "15");
		break;

		case "fight":
			DialogExit();
			LAi_group_Attack(npchar, pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "check_parol_1_chinese":
			dialogEditStrings[3] = TEV.LSCParolCheck.Answer;
			Dialog.CurrentNode = TEV.LSCParolCheck;
			DeleteAttribute(&TEV, "TEV.LSCParolCheck");
			ProcessDialogEvent();
		break;
	}
}