void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// ============================================================================
	// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
	if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
	{
		npchar.angry.ok = 1;
		if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
		{
			NextDiag.TempNode = NextDiag.CurrentNode;
			Dialog.CurrentNode = "AngryExitAgain";
			npchar.angry.first = 1;
		}
		else
		{
			Dialog.CurrentNode = "AngryQuest";
		}
	}
	// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
	// ============================================================================

	switch (Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			dialog.text = StringFromKey("Azzy_dialog_1", GetFullName(pchar));
			link.l1 = StringFromKey("Azzy_dialog_2", pchar, XI_ConvertString("Colony" + pchar.questTemp.Ascold.ShipyarderColony + "Gen"));
			link.l1.go = "Step_1";
		break;

		case "Step_1":
			dialog.text = StringFromKey("Azzy_dialog_3", pchar);
			link.l1 = StringFromKey("Azzy_dialog_4");
			link.l1.go = "Step_2";
		break;

		case "Step_2":
			dialog.text = StringFromKey("Azzy_dialog_5");
			link.l1 = StringFromKey("Azzy_dialog_6");
			link.l1.go = "Step_3";
		break;

		case "Step_3":
			dialog.text = StringFromKey("Azzy_dialog_7");
			link.l1 = StringFromKey("Azzy_dialog_8");
			link.l1.go = "Step_4";
		break;

		case "Step_4":
			dialog.text = StringFromKey("Azzy_dialog_9", pchar);
			link.l1 = StringFromKey("Azzy_dialog_10");
			link.l1.go = "Step_5";
		break;

		case "Step_5":
			dialog.text = StringFromKey("Azzy_dialog_11", pchar);
			link.l1 = StringFromKey("Azzy_dialog_12");
			link.l1.go = "Step_6";
		break;

		case "Step_6":
			dialog.text = StringFromKey("Azzy_dialog_13");
			link.l1 = StringFromKey("Azzy_dialog_14");
			link.l1.go = "Step_7";
		break;

		case "Step_7":
			dialog.text = StringFromKey("Azzy_dialog_15", pchar);
			link.l1 = StringFromKey("Azzy_dialog_16");
			link.l1.go = "Step_8";
		break;

		case "Step_8":
			dialog.text = StringFromKey("Azzy_dialog_17");
			link.l1 = StringFromKey("Azzy_dialog_18");
			link.l1.go = "Step_9";
		break;

		case "Step_9":
			dialog.text = StringFromKey("Azzy_dialog_19");
			link.l1 = StringFromKey("Azzy_dialog_20");
			link.l1.go = "Step_10";
		break;

		case "Step_10":
			dialog.text = StringFromKey("Azzy_dialog_21");
			link.l1 = StringFromKey("Azzy_dialog_22", pchar);
			link.l1.go = "Step_11";
		break;

		case "Step_11":
			dialog.text = StringFromKey("Azzy_dialog_23", pchar);
			link.l1 = StringFromKey("Azzy_dialog_24");
			link.l1.go = "Step_12";
		break;

		case "Step_12":
			dialog.text = StringFromKey("Azzy_dialog_25");
			link.l1 = StringFromKey("Azzy_dialog_26");
			link.l1.go = "Step_13";
		break;

		case "Step_13":
			dialog.text = StringFromKey("Azzy_dialog_27", pchar);
			link.l1 = StringFromKey("Azzy_dialog_28");
			link.l1.go = "Step_14";
		break;

		case "Step_14":
			dialog.text = StringFromKey("Azzy_dialog_29");
			link.l1 = StringFromKey("Azzy_dialog_30");
			link.l1.go = "Step_15";
		break;

		case "Step_15":
			dialog.text = StringFromKey("Azzy_dialog_31");
			link.l1 = StringFromKey("Azzy_dialog_32");
			link.l1.go = "Wishes";
		break;

		case "Wishes":
			dialog.text = StringFromKey("Azzy_dialog_36", LinkRandPhrase(
						StringFromKey("Azzy_dialog_33"),
						StringFromKey("Azzy_dialog_34"),
						StringFromKey("Azzy_dialog_35")));
			link.l1 = StringFromKey("Azzy_dialog_37");
			link.l1.go = "ToKillEnemy";
			link.l2 = StringFromKey("Azzy_dialog_38");
			link.l2.go = "ToGiveMoney";
			link.l4 = StringFromKey("Azzy_dialog_39");
			link.l4.go = "ToGiveRum";
			link.l5 = StringFromKey("Azzy_dialog_40");
			link.l5.go = "ToShip";
			link.l6 = StringFromKey("Azzy_dialog_41");
			link.l6.go = "ToImmortal";
			link.l7 = StringFromKey("Azzy_dialog_42");
			link.l7.go = "ToGovernor";
			link.l8 = StringFromKey("Azzy_dialog_43", pchar);
			link.l8.go = "ToAddSpecial";
			link.l9 = StringFromKey("Azzy_dialog_44");
			link.l9.go = "ToEnd";
		break;

		case "ToKillEnemy":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Azzy_dialog_45"),
						StringFromKey("Azzy_dialog_46"),
						StringFromKey("Azzy_dialog_47"),
						StringFromKey("Azzy_dialog_48", pchar), "quest", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Azzy_dialog_49", pchar),
						StringFromKey("Azzy_dialog_50"),
						StringFromKey("Azzy_dialog_51", pchar),
						StringFromKey("Azzy_dialog_52"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_16", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_16":
			dialog.text = StringFromKey("Azzy_dialog_53", GetFullName(pchar));
			link.l1 = StringFromKey("Azzy_dialog_54");
			link.l1.go = "Step_17";
		break;

		case "Step_17":
			dialog.text = StringFromKey("Azzy_dialog_55");
			link.l1 = StringFromKey("Azzy_dialog_56");
			link.l1.go = "Step_18";
		break;

		case "Step_18":
			dialog.text = StringFromKey("Azzy_dialog_57");
			link.l1 = StringFromKey("Azzy_dialog_58");
			link.l1.go = "Step_19";
		break;

		case "Step_19":
			dialog.text = StringFromKey("Azzy_dialog_59", pchar);
			link.l1 = StringFromKey("Azzy_dialog_60");
			link.l1.go = "Wishes";
		break;

		case "ToGiveMoney":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Azzy_dialog_61"),
						StringFromKey("Azzy_dialog_62"),
						StringFromKey("Azzy_dialog_63"),
						StringFromKey("Azzy_dialog_64"), "quest", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Azzy_dialog_65"),
						StringFromKey("Azzy_dialog_66"),
						StringFromKey("Azzy_dialog_67", pchar),
						StringFromKey("Azzy_dialog_68"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_20", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_20":
			dialog.text = StringFromKey("Azzy_dialog_69", pchar);
			link.l1 = StringFromKey("Azzy_dialog_70");
			link.l1.go = "Step_21";
		break;

		case "Step_21":
			dialog.text = StringFromKey("Azzy_dialog_71", GetFullName(characterFromId("Charles_usurer")));
			link.l1 = StringFromKey("Azzy_dialog_72");
			link.l1.go = "Step_22";
			pchar.questTemp.Azzy.GiveMoney = 1;
			AddLandQuestmark_Main(CharacterFromID("Charles_usurer"), "Azzy_Wishes");
		break;

		case "Step_22":
			dialog.text = StringFromKey("Azzy_dialog_73", pchar);
			link.l1 = StringFromKey("Azzy_dialog_74");
			link.l1.go = "Wishes";
		break;

		case "ToGovernor":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Azzy_dialog_75"),
						StringFromKey("Azzy_dialog_76", pchar),
						StringFromKey("Azzy_dialog_77"),
						StringFromKey("Azzy_dialog_78"), "quest", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Azzy_dialog_79"),
						StringFromKey("Azzy_dialog_80", pchar),
						StringFromKey("Azzy_dialog_81"),
						StringFromKey("Azzy_dialog_82"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_25", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_25":
			dialog.text = StringFromKey("Azzy_dialog_83");
			link.l1 = StringFromKey("Azzy_dialog_84");
			link.l1.go = "Step_26";
		break;

		case "Step_26":
			dialog.text = StringFromKey("Azzy_dialog_85");
			link.l1 = StringFromKey("Azzy_dialog_86");
			link.l1.go = "Step_27";
		break;

		case "Step_27":
			dialog.text = StringFromKey("Azzy_dialog_87", pchar);
			link.l1 = StringFromKey("Azzy_dialog_88", pchar);
			link.l1.go = "Step_28";
		break;

		case "Step_28":
			dialog.text = StringFromKey("Azzy_dialog_89");
			link.l1 = StringFromKey("Azzy_dialog_90");
			link.l1.go = "Wishes";
		break;

		case "ToImmortal":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Azzy_dialog_91"),
						StringFromKey("Azzy_dialog_92"),
						StringFromKey("Azzy_dialog_93"),
						StringFromKey("Azzy_dialog_94"), "quest", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Azzy_dialog_95"),
						StringFromKey("Azzy_dialog_96"),
						StringFromKey("Azzy_dialog_97"),
						StringFromKey("Azzy_dialog_98"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_29", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_29":
			dialog.text = StringFromKey("Azzy_dialog_99", pchar);
			link.l1 = StringFromKey("Azzy_dialog_100");
			link.l1.go = "Step_30";
		break;

		case "Step_30":
			dialog.text = StringFromKey("Azzy_dialog_101");
			link.l1 = StringFromKey("Azzy_dialog_102");
			link.l1.go = "Step_31";
		break;

		case "Step_31":
			dialog.text = StringFromKey("Azzy_dialog_103", pchar);
			link.l1 = StringFromKey("Azzy_dialog_104", pchar);
			link.l1.go = "Step_32";
		break;

		case "Step_32":
			dialog.text = StringFromKey("Azzy_dialog_105", pchar);
			link.l1 = StringFromKey("Azzy_dialog_106");
			link.l1.go = "Step_33";
		break;

		case "Step_33":
			dialog.text = StringFromKey("Azzy_dialog_107", pchar);
			link.l1 = StringFromKey("Azzy_dialog_108");
			link.l1.go = "Step_34";
		break;

		case "Step_34":
			dialog.text = StringFromKey("Azzy_dialog_109", pchar);
			link.l1 = StringFromKey("Azzy_dialog_110", pchar);
			link.l1.go = "Step_35";
		break;

		case "Step_35":
			dialog.text = StringFromKey("Azzy_dialog_111", pchar);
			link.l1 = StringFromKey("Azzy_dialog_112", pchar);
			link.l1.go = "Step_36";
			link.l2 = StringFromKey("Azzy_dialog_113", pchar);
			link.l2.go = "Wishes";
		break;

		case "Step_36":
			dialog.text = StringFromKey("Azzy_dialog_114", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("Azzy_dialog_115", GetFullName(pchar));
			link.l1.go = "Step_37";
		break;

		case "Step_37":
			dialog.text = StringFromKey("Azzy_dialog_116", pchar);
			link.l1 = StringFromKey("Azzy_dialog_117");
			link.l1.go = "Wishes";
			LAi_SetImmortal(pchar, true);
			SetQuestHeader("ContractWithHell");
			AddQuestRecord("ContractWithHell", "1");
			AddQuestUserData("ContractWithHell", "Conrtragent", GetFullName(pchar));
			pchar.questTemp.Azzy.Immortal = 1;
			SaveCurrentQuestDateParam("questTemp.Azzy");
			SaveCurrentQuestDateParam("questTemp.Azzy.Immortal");
			pchar.questTemp.Azzy.Immortal.AllQuota = 0;
			pchar.questTemp.Azzy.Immortal.DayQuota = 3; //ежедневный норматив
			pchar.questTemp.Azzy.Immortal.CurBalance = 0;
			pchar.questTemp.Azzy.Immortal.CurKilled = 0;
			pchar.questTemp.Azzy.Immortal.Penalty = 0;
			pchar.questTemp.Azzy.Immortal.EarlyKilled = Statistic_AddValue(PChar, "Solder_s", 0) +
						Statistic_AddValue(PChar, "Solder_g", 0) +
							Statistic_AddValue(PChar, "Warrior_s", 0) +
								Statistic_AddValue(PChar, "Warrior_g", 0) +
									Statistic_AddValue(PChar, "Citizen_s", 0) +
										Statistic_AddValue(PChar, "Citizen_g", 0) +
											Statistic_AddValue(PChar, "Monster_s", 0) +
											Statistic_AddValue(PChar, "Monster_g", 0);
			AddQuestRecord("Azzy_HellSign", "1");
			AddQuestUserData("Azzy_HellSign", "sName", GetMainCharacterNameGen());
			AddQuestUserData("Azzy_HellSign", "DayQuota", pchar.questTemp.Azzy.Immortal.DayQuota);
			AddQuestUserData("Azzy_HellSign", "AllQuota", pchar.questTemp.Azzy.Immortal.AllQuota);
			AddQuestUserData("Azzy_HellSign", "CurKilled", pchar.questTemp.Azzy.Immortal.CurKilled);
			AddQuestUserData("Azzy_HellSign", "CurBalance", pchar.questTemp.Azzy.Immortal.CurBalance);
		break;

		case "ToGiveRum":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Azzy_dialog_118"),
						StringFromKey("Azzy_dialog_119"),
						StringFromKey("Azzy_dialog_120"),
						StringFromKey("Azzy_dialog_121"), "quest", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Azzy_dialog_122"),
						StringFromKey("Azzy_dialog_123"),
						StringFromKey("Azzy_dialog_124"),
						StringFromKey("Azzy_dialog_125"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_38", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_38":
			dialog.text = StringFromKey("Azzy_dialog_126", GetFullName(characterFromId("PortPax_trader")));
			link.l1 = StringFromKey("Azzy_dialog_127", pchar);
			link.l1.go = "Step_39";
			pchar.questTemp.Azzy.GiveRum = 1;
			AddLandQuestmark_Main(CharacterFromID("PortPax_trader"), "Azzy_Wishes");
		break;

		case "Step_39":
			dialog.text = StringFromKey("Azzy_dialog_128");
			link.l1 = StringFromKey("Azzy_dialog_129");
			link.l1.go = "Wishes";
		break;

		case "ToAddSpecial":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Azzy_dialog_130", pchar),
						StringFromKey("Azzy_dialog_131"),
						StringFromKey("Azzy_dialog_132"),
						StringFromKey("Azzy_dialog_133"), "quest", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Azzy_dialog_134"),
						StringFromKey("Azzy_dialog_135"),
						StringFromKey("Azzy_dialog_136"),
						StringFromKey("Azzy_dialog_137"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_40", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_40":
			dialog.text = StringFromKey("Azzy_dialog_138");
			link.l1 = StringFromKey("Azzy_dialog_139");
			link.l1.go = "Wishes";
			pchar.questTemp.Azzy.AddSpecial = 1;
			AddLandQuestmark_Main(CharacterFromID("Tortuga_Hostess"), "Azzy_Wishes");
		break;

		case "ToShip":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Azzy_dialog_140"),
						StringFromKey("Azzy_dialog_141"),
						StringFromKey("Azzy_dialog_142"),
						StringFromKey("Azzy_dialog_143"), "quest", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Azzy_dialog_144"),
						StringFromKey("Azzy_dialog_145"),
						StringFromKey("Azzy_dialog_146", pchar),
						StringFromKey("Azzy_dialog_147"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_41", "Wishes", "Wishes", "", npchar, Dialog.CurrentNode);
		break;

		case "Step_41":
			dialog.text = StringFromKey("Azzy_dialog_148");
			link.l1 = StringFromKey("Azzy_dialog_149");
			link.l1.go = "Step_42";
		break;

		case "Step_42":
			dialog.text = StringFromKey("Azzy_dialog_150");
			link.l1 = StringFromKey("Azzy_dialog_151");
			link.l1.go = "Step_43";
		break;

		case "Step_43":
			dialog.text = StringFromKey("Azzy_dialog_152");
			link.l1 = StringFromKey("Azzy_dialog_153");
			link.l1.go = "Wishes";
			if (CheckAttribute(pchar, "questTemp.Azzy.Immortal"))
			{
				dialog.text = StringFromKey("Azzy_dialog_154", pchar);
				link.l1 = StringFromKey("Azzy_dialog_155");
			}
		break;

		case "ToEnd":
			dialog.text = StringFromKey("Azzy_dialog_156", pchar);
			link.l1 = StringFromKey("Azzy_dialog_157");
			link.l1.go = "Back_Exit";
		break;

		case "Back_Exit":
			LAi_LocationFightDisable(&Locations[FindLocation("Shore28")], false);
			ChangeCharacterAddress(characterFromID("Azzy"), "None", "");
			DoReloadCharacterToLocation(pchar.questTemp.Ascold.ShipyarderColony + "_Shipyard", "reload", "reload2");
			LAi_SetPlayerType(PChar);
			NextDiag.TempNode = "Second time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Azzy_Exit":
			ChangeCharacterAddress(characterFromID("Azzy"), "None", "");
			LAi_SetPlayerType(PChar);
			NextDiag.TempNode = "Death";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Second time":
			dialog.text = StringFromKey("Azzy_dialog_158", GetFullName(pchar));
			link.l1 = StringFromKey("Azzy_dialog_159");
			link.l1.go = "Step_44";
		break;

		case "Step_44":
			dialog.text = StringFromKey("Azzy_dialog_160");
			link.l1 = StringFromKey("Azzy_dialog_161");
			link.l1.go = "Step_45";
		break;

		case "Step_45":
			dialog.text = StringFromKey("Azzy_dialog_162", pchar);
			link.l1 = StringFromKey("Azzy_dialog_163", pchar);
			link.l1.go = "Step_46";
		break;

		case "Step_46":
			dialog.text = StringFromKey("Azzy_dialog_164");
			link.l1 = StringFromKey("Azzy_dialog_165");
			link.l1.go = "Step_47";
		break;

		case "Step_47":
			dialog.text = StringFromKey("Azzy_dialog_166", pchar);
			link.l1 = StringFromKey("Azzy_dialog_167");
			link.l1.go = "Step_48";
			pchar.questTemp.Azzy = "over";
			LAi_SetImmortal(pchar, false);
			DeleteAttribute(pchar, "questTemp.Azzy.Immortal");
			DeleteQuestHeader("ContractWithHell");
			DeleteQuestHeader("Azzy_HellSign");
		break;

		case "Step_48":
			dialog.text = StringFromKey("Azzy_dialog_168", pchar);
			link.l1 = StringFromKey("Azzy_dialog_169");
			link.l1.go = "Azzy_Exit";
			npchar.lifeDay = 0;
		break;
		//помощь ГГ, если вляпался с долгом у ростовщика ГПК
		case "ClimeUsurer":
			dialog.text = StringFromKey("Azzy_dialog_170", pchar);
			link.l1 = StringFromKey("Azzy_dialog_171", pchar);
			link.l1.go = "ClimeUsurer_1";
		break;
		case "ClimeUsurer_1":
			dialog.text = StringFromKey("Azzy_dialog_172");
			link.l1 = StringFromKey("Azzy_dialog_173", pchar);
			link.l1.go = "ClimeUsurer_2";
		break;
		case "ClimeUsurer_2":
			dialog.text = StringFromKey("Azzy_dialog_174", pchar);
			link.l1 = StringFromKey("Azzy_dialog_175", pchar);
			link.l1.go = "ClimeUsurer_3";
		break;
		case "ClimeUsurer_3":
			dialog.text = StringFromKey("Azzy_dialog_176");
			link.l1 = StringFromKey("Azzy_dialog_177");
			link.l1.go = "ClimeUsurer_4";
		break;
		case "ClimeUsurer_4":
			dialog.text = StringFromKey("Azzy_dialog_178", pchar);
			link.l1 = StringFromKey("Azzy_dialog_179", pchar);
			link.l1.go = "ClimeUsurer_5";
		break;
		case "ClimeUsurer_5":
			dialog.text = StringFromKey("Azzy_dialog_180");
			link.l1 = StringFromKey("Azzy_dialog_181", pchar);
			link.l1.go = "ClimeUsurer_6";
		break;
		case "ClimeUsurer_6":
			dialog.text = StringFromKey("Azzy_dialog_182", pchar);
			link.l1 = StringFromKey("Azzy_dialog_183");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClimeUsurer_haveMoney");
		break;

		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		//==> попытки дать денег
		case "AngryQuest":
			Dialog.text = StringFromKey("Azzy_dialog_184", GetFullName(pchar));
			Link.l1 = StringFromKey("Azzy_dialog_185");
			Link.l1.go = "AngStep_1";
		break;

		case "AngStep_1":
			Dialog.text = StringFromKey("Azzy_dialog_186", pchar);
			Link.l1 = "...";
			Link.l1.go = "Back_Exit";
			DeleteAttribute(npchar, "angry.ok");
			Dialog.CurrentNode = "Back_Exit";
		break;

		case "AngryExitAgain":
			ChangeCharacterAddress(characterFromID("Azzy"), "None", "");
			LAi_SetPlayerType(PChar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(npchar, "angry.ok");
		break;

		// <<<<<<<<<<<<============= блок нод angry =============================
	}
}


