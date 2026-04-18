void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	bool bOk;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Gang" + locations[FindLocation(npchar.location)].index + "_";

	switch (Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "exit_Robbed":
			ChangeCharacterReputation(pchar, -1);
			int iMoney = makeint(makeint(Pchar.money) / 20) * 10;
			AddMoneyToCharacter(pchar, -iMoney);
			AddSimpleRumour(
						StringFromKey("Raiders_4", LinkRandPhrase(
								StringFromKey("Raiders_1", GetFullName(npchar), FindMoneyString(iMoney)),
								StringFromKey("Raiders_2", GetFullName(pchar), FindMoneyString(iMoney), GetFullName(npchar)),
								StringFromKey("Raiders_3", FindMoneyString(iMoney)))), sti(npchar.nation), 5, 1);
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgain";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld) - 1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();
		break;

		case "exit_fight":
			sGroup = "RaidersGroup_" + locations[FindLocation(npchar.location)].index;
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_RaidersAfrer");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_RunFight":
			AddSimpleRumour(
						StringFromKey("Raiders_10", LinkRandPhrase(
								StringFromKey("Raiders_7", RandPhraseSimple(
										StringFromKey("Raiders_5", pchar, GetFullName(npchar)),
										StringFromKey("Raiders_6", GetFullName(pchar), GetFullName(npchar)))),
								StringFromKey("Raiders_8", pchar, GetFullName(npchar)),
								StringFromKey("Raiders_9", pchar, GetFullName(npchar)))), sti(npchar.nation), 5, 1);
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorAfraid(sld, Pchar, true);
				sld.Dialog.CurrentNode = "GetTheHellOut";
			}
			DialogExit();
		break;

		case "exit_noFight":
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "GetLost";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld) - 1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();
		break;

		case "First Time":
			LAi_LockFightMode(pchar, false);
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = StringFromKey("Raiders_20", LinkRandPhrase(
						StringFromKey("Raiders_14", LinkRandPhrase(
								StringFromKey("Raiders_11"),
								StringFromKey("Raiders_12", pchar),
								StringFromKey("Raiders_13", pchar))),
						StringFromKey("Raiders_18", LinkRandPhrase(
								StringFromKey("Raiders_15", pchar),
								StringFromKey("Raiders_16", pchar),
								StringFromKey("Raiders_17", pchar))),
						StringFromKey("Raiders_19", pchar)));
			Link.l1 = StringFromKey("Raiders_27", LinkRandPhrase(
						StringFromKey("Raiders_24", LinkRandPhrase(
								StringFromKey("Raiders_21"),
								StringFromKey("Raiders_22"),
								StringFromKey("Raiders_23"))),
						StringFromKey("Raiders_25"),
						StringFromKey("Raiders_26")));
			Link.l1.go = "Node_2";
			Link.l2 = StringFromKey("Raiders_42", LinkRandPhrase(
						StringFromKey("Raiders_31", LinkRandPhrase(
								StringFromKey("Raiders_28"),
								StringFromKey("Raiders_29"),
								StringFromKey("Raiders_30", pchar))),
						StringFromKey("Raiders_35", LinkRandPhrase(
								StringFromKey("Raiders_32"),
								StringFromKey("Raiders_33"),
								StringFromKey("Raiders_34"))),
						StringFromKey("Raiders_41", LinkRandPhrase(
								StringFromKey("Raiders_38", RandPhraseSimple(
										StringFromKey("Raiders_36"),
										StringFromKey("Raiders_37", pchar))),
								StringFromKey("Raiders_39"),
								StringFromKey("Raiders_40")))));
			Link.l2.go = "CheckSkills";
			Link.l3 = StringFromKey("Raiders_50", LinkRandPhrase(
						StringFromKey("Raiders_43"),
						StringFromKey("Raiders_46", RandPhraseSimple(
								StringFromKey("Raiders_44"),
								StringFromKey("Raiders_45"))),
						StringFromKey("Raiders_49", RandPhraseSimple(
								StringFromKey("Raiders_47", pchar),
								StringFromKey("Raiders_48", pchar)))));
			Link.l3.go = "Node_3";
		break;

		case "Node_2":
			dialog.text = StringFromKey("Raiders_59", LinkRandPhrase(
						StringFromKey("Raiders_54", LinkRandPhrase(
								StringFromKey("Raiders_51"),
								StringFromKey("Raiders_52", pchar),
								StringFromKey("Raiders_53"))),
						StringFromKey("Raiders_57", RandPhraseSimple(
								StringFromKey("Raiders_55"),
								StringFromKey("Raiders_56"))),
						StringFromKey("Raiders_58", pchar)));
			Link.l1 = StringFromKey("Raiders_60", FindMoneyString(makeint(makeint(Pchar.money) / 20) * 10));
			Link.l1.go = "CheckMoney";
			Link.l2 = StringFromKey("Raiders_72", LinkRandPhrase(
						StringFromKey("Raiders_64", LinkRandPhrase(
								StringFromKey("Raiders_61"),
								StringFromKey("Raiders_62"),
								StringFromKey("Raiders_63", pchar))),
						StringFromKey("Raiders_68", LinkRandPhrase(
								StringFromKey("Raiders_65"),
								StringFromKey("Raiders_66"),
								StringFromKey("Raiders_67"))),
						StringFromKey("Raiders_71", RandPhraseSimple(
								StringFromKey("Raiders_69"),
								StringFromKey("Raiders_70", pchar)))));
			Link.l2.go = "CheckSkills";
		break;

		case "Node_3":
			bOk = makeint(pchar.reputation) < 11 || makeint(pchar.reputation) > 90;
			if (bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) == 100 || CheckCharacterPerk(pchar, "Trustworthy") || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				dialog.text = StringFromKey("Raiders_75", RandPhraseSimple(
							StringFromKey("Raiders_73"),
							StringFromKey("Raiders_74", pchar)));
				Link.l1 = StringFromKey("Raiders_78", RandPhraseSimple(
							StringFromKey("Raiders_76"),
							StringFromKey("Raiders_77")));
				Link.l1.go = "Exit_NoFight";
			}
			else
			{
				bOk = makeint(pchar.reputation) < 51 && makeint(pchar.reputation) > 41; //TODO: watch_moment + переписать реакцию на пиастры
				if (!bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
				{
					dialog.text = StringFromKey("Raiders_81", RandPhraseSimple(
								StringFromKey("Raiders_79"),
								StringFromKey("Raiders_80", pchar)));
					Link.l1 = StringFromKey("Raiders_82", pchar);
					Link.l1.go = "Exit_Fight";
				}
				else
				{
					dialog.text = StringFromKey("Raiders_85", RandPhraseSimple(
								StringFromKey("Raiders_83"),
								StringFromKey("Raiders_84", pchar)));
					Link.l1 = StringFromKey("Raiders_86", FindMoneyString(makeint(makeint(Pchar.money) / 20) * 10));
					Link.l1.go = "CheckMoney";
					Link.l2 = StringFromKey("Raiders_92", RandPhraseSimple(
								StringFromKey("Raiders_90", LinkRandPhrase(
										StringFromKey("Raiders_87"),
										StringFromKey("Raiders_88"),
										StringFromKey("Raiders_89"))),
								StringFromKey("Raiders_91")));
					Link.l2.go = "CheckSkills";
				}
			}
		break;

		case "CheckSkills":
			bOk = GetCharacterSkillToOld(Pchar, "Fencing") >= 7 && sti(Pchar.Rank) >= 10 && sti(PChar.reputation) <= 30;
			if (bOk || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				if (CheckCharacterPerk(pchar, "SeaDogProfessional")) PlayerRPGCheck_Perk_NotifyPass("SeaDogProfessional");
				Diag.TempNode = "GetLost";
				dialog.text = StringFromKey("Raiders_98", LinkRandPhrase(
							StringFromKey("Raiders_95", RandPhraseSimple(
									StringFromKey("Raiders_93", pchar),
									StringFromKey("Raiders_94", pchar))),
							StringFromKey("Raiders_96", pchar),
							StringFromKey("Raiders_97", pchar)));
				Link.l1 = StringFromKey("Raiders_109", LinkRandPhrase(
							StringFromKey("Raiders_102", LinkRandPhrase(
									StringFromKey("Raiders_99"),
									StringFromKey("Raiders_100"),
									StringFromKey("Raiders_101"))),
							StringFromKey("Raiders_105", RandPhraseSimple(
									StringFromKey("Raiders_103"),
									StringFromKey("Raiders_104", pchar))),
							StringFromKey("Raiders_108", RandPhraseSimple(
									StringFromKey("Raiders_106"),
									StringFromKey("Raiders_107")))));
				Link.l1.go = "Exit_NoFight";
				Link.l2 = StringFromKey("Raiders_113", LinkRandPhrase(
							StringFromKey("Raiders_110"),
							StringFromKey("Raiders_111"),
							StringFromKey("Raiders_112")));
				Link.l2.go = "GetTheHellOut";
			}
			else
			{
				dialog.text = StringFromKey("Raiders_117", LinkRandPhrase(
							StringFromKey("Raiders_114", pchar),
							StringFromKey("Raiders_115", pchar),
							StringFromKey("Raiders_116")));
				Link.l1 = StringFromKey("Raiders_120", RandPhraseSimple(
							StringFromKey("Raiders_118"),
							StringFromKey("Raiders_119")));
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "CheckMoney":
			if (makeint(makeint(Pchar.money) / 20) * 10 >= makeint(Pchar.rank) * 100)
			{
				Diag.TempNode = "OnceAgain";
				dialog.text = StringFromKey("Raiders_126", LinkRandPhrase(
							StringFromKey("Raiders_123", RandPhraseSimple(
									StringFromKey("Raiders_121"),
									StringFromKey("Raiders_122"))),
							StringFromKey("Raiders_124"),
							StringFromKey("Raiders_125", pchar)));
				Link.l1 = StringFromKey("Raiders_127");
				Link.l1.go = "Exit_Robbed";
			}
			else
			{
				dialog.text = StringFromKey("Raiders_128");
				Link.l1 = StringFromKey("Raiders_129");
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = StringFromKey("Raiders_133", LinkRandPhrase(
						StringFromKey("Raiders_130"),
						StringFromKey("Raiders_131", pchar),
						StringFromKey("Raiders_132", pchar)));
			Link.l1 = StringFromKey("Raiders_134");
			Link.l1.go = "Exit";
			Link.l2 = StringFromKey("Raiders_135", pchar);
			Link.l2.go = "Exit_Fight";
		break;

		case "GetLost":
			Diag.TempNode = "GetLost";
			dialog.text = StringFromKey("Raiders_139", LinkRandPhrase(
						StringFromKey("Raiders_136"),
						StringFromKey("Raiders_137", pchar),
						StringFromKey("Raiders_138", pchar)));
			Link.l1 = StringFromKey("Raiders_140");
			Link.l1.go = "Exit";
			Link.l2 = StringFromKey("Raiders_141", pchar);
			Link.l2.go = "Exit_Fight";
		break;

		case "GetTheHellOut":
			Diag.TempNode = "GetTheHellOut";
			dialog.text = StringFromKey("Raiders_145", LinkRandPhrase(
						StringFromKey("Raiders_142"),
						StringFromKey("Raiders_143", pchar),
						StringFromKey("Raiders_144")));
			Link.l1 = StringFromKey("Raiders_152", LinkRandPhrase(
						StringFromKey("Raiders_149", LinkRandPhrase(
								StringFromKey("Raiders_146"),
								StringFromKey("Raiders_147"),
								StringFromKey("Raiders_148"))),
						StringFromKey("Raiders_150"),
						StringFromKey("Raiders_151")));
			Link.l1.go = "exit_Fight";
		break;
	}
}
