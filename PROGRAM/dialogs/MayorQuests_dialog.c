void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		//----------------- уничтожение банды ----------------------
		case "DestroyGang_begin":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //боевке можно
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.DestroyGang.Location)], "DisableEncounters"); //энкаунтеры можно 
			for (i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)]);
			dialog.text = StringFromKey("MayorQuests_dialog_4", LinkRandPhrase(
						StringFromKey("MayorQuests_dialog_1", pchar, GetFullName(npchar)),
						StringFromKey("MayorQuests_dialog_2", pchar, GetFullName(npchar)),
						StringFromKey("MayorQuests_dialog_3", GetFullName(npchar))));
			Link.l1 = StringFromKey("MayorQuests_dialog_8", LinkRandPhrase(
						StringFromKey("MayorQuests_dialog_5", GetFullName(npchar), sTemp),
						StringFromKey("MayorQuests_dialog_6", sTemp),
						StringFromKey("MayorQuests_dialog_7", pchar, GetFullName(npchar), sTemp)));
			Link.l1.go = "DestroyGang_1";
		break;
		case "DestroyGang_1":
			dialog.text = StringFromKey("MayorQuests_dialog_12", LinkRandPhrase(
						StringFromKey("MayorQuests_dialog_9", pchar),
						StringFromKey("MayorQuests_dialog_10", pchar),
						StringFromKey("MayorQuests_dialog_11")));
			Link.l1 = StringFromKey("MayorQuests_dialog_16", LinkRandPhrase(
						StringFromKey("MayorQuests_dialog_13"),
						StringFromKey("MayorQuests_dialog_14"),
						StringFromKey("MayorQuests_dialog_15")));
			Link.l1.go = "DestroyGang_ExitFight";
			Link.l2 = StringFromKey("MayorQuests_dialog_20", LinkRandPhrase(
						StringFromKey("MayorQuests_dialog_17"),
						StringFromKey("MayorQuests_dialog_18"),
						StringFromKey("MayorQuests_dialog_19")));
			Link.l2.go = "DestroyGang_2";
		break;
		case "DestroyGang_2":
			dialog.text = StringFromKey("MayorQuests_dialog_24", LinkRandPhrase(
						StringFromKey("MayorQuests_dialog_21", pchar),
						StringFromKey("MayorQuests_dialog_22", pchar),
						StringFromKey("MayorQuests_dialog_23", pchar)));
			Link.l1 = StringFromKey("MayorQuests_dialog_25");
			Link.l1.go = "DestroyGang_ExitAfraid";
		break;

		case "DestroyGang_ExitAfraid":
			pchar.GenQuest.DestroyGang = "Found"; //флаг нашёл, но струсил
			npchar.money = AddMoneyToCharacter(npchar, sti(pchar.money));
			pchar.money = 0;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar) - 1, false, "DestroyGang_SuddenAttack");
			for (i = 1; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
				LAi_SetImmortal(sld, true);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld) - 1, false, "DestroyGang_SuddenAttack");
			}
			DialogExit();
		break;

		case "DestroyGang_ExitFight":
			for (i = 0; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "DestroyGang");
			}
			LAi_group_SetRelation("DestroyGang", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("DestroyGang", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("DestroyGang", "DestroyGang_After");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//----------------- поиски лазутчика в коммонах ----------------------
		case "SeekSpy_house":
			chrDisableReloadToLocation = false;
			dialog.text = StringFromKey("MayorQuests_dialog_26", GetAddress_Form(PChar));
			Link.l1 = StringFromKey("MayorQuests_dialog_27");
			Link.l1.go = "SeekSpy_1";
		break;
		case "SeekSpy_1":
			dialog.text = StringFromKey("MayorQuests_dialog_28", pchar);
			Link.l1 = StringFromKey("MayorQuests_dialog_29");
			Link.l1.go = "SeekSpy_2";
		break;
		case "SeekSpy_2":
			dialog.text = StringFromKey("MayorQuests_dialog_30");
			Link.l1 = StringFromKey("MayorQuests_dialog_31");
			Link.l1.go = "SeekSpy_3";
		break;
		case "SeekSpy_3":
			dialog.text = StringFromKey("MayorQuests_dialog_32", pchar);
			Link.l1 = StringFromKey("MayorQuests_dialog_33");
			Link.l1.go = "SeekSpy_fight";
		break;
		case "SeekSpy_fight":
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "SeekSpy");
			LAi_group_SetRelation("SeekSpy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("SeekSpy", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("SeekSpy", "SeekSpy_After");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//----------------- поиски лазутчика на улице ----------------------
		case "SeekSpy_street":
			Diag.TempNode = "SeekSpy_street";
			dialog.Text = NPCharRepPhrase(npchar,
					PCharRepPhrase(
							StringFromKey("MayorQuests_dialog_43", LinkRandPhrase(
									StringFromKey("MayorQuests_dialog_34", pchar, GetFullName(Pchar)),
									StringFromKey("MayorQuests_dialog_35", pchar, Pchar.name),
									StringFromKey("MayorQuests_dialog_36", pchar, GetFullName(Pchar))), LinkRandPhrase(
									StringFromKey("MayorQuests_dialog_37"),
									StringFromKey("MayorQuests_dialog_38", pchar),
									StringFromKey("MayorQuests_dialog_39")), LinkRandPhrase(
									StringFromKey("MayorQuests_dialog_40"),
									StringFromKey("MayorQuests_dialog_41"),
									StringFromKey("MayorQuests_dialog_42"))),
							StringFromKey("MayorQuests_dialog_50", LinkRandPhrase(
									StringFromKey("MayorQuests_dialog_44", TimeGreeting()),
									StringFromKey("MayorQuests_dialog_45", GetAddress_Form(NPChar)),
									StringFromKey("MayorQuests_dialog_46")), GetFullName(Pchar), LinkRandPhrase(
									StringFromKey("MayorQuests_dialog_47", pchar),
									StringFromKey("MayorQuests_dialog_48"),
									StringFromKey("MayorQuests_dialog_49")))),
					PCharRepPhrase(
							StringFromKey("MayorQuests_dialog_60", LinkRandPhrase(
									StringFromKey("MayorQuests_dialog_51"),
									StringFromKey("MayorQuests_dialog_52", GetAddress_Form(NPChar)),
									StringFromKey("MayorQuests_dialog_53")), GetFullName(Pchar), LinkRandPhrase(
									StringFromKey("MayorQuests_dialog_54", npchar),
									StringFromKey("MayorQuests_dialog_55", npchar),
									StringFromKey("MayorQuests_dialog_56")), LinkRandPhrase(
									StringFromKey("MayorQuests_dialog_57"),
									StringFromKey("MayorQuests_dialog_58"),
									StringFromKey("MayorQuests_dialog_59", npchar))),
							StringFromKey("MayorQuests_dialog_64", LinkRandPhrase(
									StringFromKey("MayorQuests_dialog_61", TimeGreeting(), GetFullName(Pchar)),
									StringFromKey("MayorQuests_dialog_62", GetFullName(Pchar)),
									StringFromKey("MayorQuests_dialog_63", GetAddress_Form(NPChar), Pchar.lastname)))));
			link.l1 = PCharRepPhrase(
						StringFromKey("MayorQuests_dialog_67", RandPhraseSimple(
								StringFromKey("MayorQuests_dialog_65"),
								StringFromKey("MayorQuests_dialog_66", pchar))),
						StringFromKey("MayorQuests_dialog_70", RandPhraseSimple(
								StringFromKey("MayorQuests_dialog_68"),
								StringFromKey("MayorQuests_dialog_69"))));
			link.l1.go = "exit";
			link.l2 = StringFromKey("MayorQuests_dialog_73", RandPhraseSimple(
						StringFromKey("MayorQuests_dialog_71"),
						StringFromKey("MayorQuests_dialog_72")));
			link.l2.go = "exit";//(перессылка в файл города)
			// --> квестовый генератор мэра, поиск шпиёна на улице. eddy
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City") && pchar.location == (npchar.city + "_town"))
			{
				link.l4 = StringFromKey("MayorQuests_dialog_80", npchar, LinkRandPhrase(
							StringFromKey("MayorQuests_dialog_74"),
							StringFromKey("MayorQuests_dialog_75"),
							StringFromKey("MayorQuests_dialog_76")), LinkRandPhrase(
							StringFromKey("MayorQuests_dialog_77", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city + "Gen")),
							StringFromKey("MayorQuests_dialog_78", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city + "Gen")),
							StringFromKey("MayorQuests_dialog_79", characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].lastname)));
				link.l4.go = "SitySpy";
			}
			// <-- квестовый генератор мэра, поиск шпиёна на улице
			link.l5 = PCharRepPhrase(
						StringFromKey("MayorQuests_dialog_81", pchar),
						StringFromKey("MayorQuests_dialog_82", pchar));
			link.l5.go = "new question";
		break;

		case "new question":
			dialog.text = NPCharRepPhrase(npchar,
					PCharRepPhrase(
							StringFromKey("MayorQuests_dialog_86", LinkRandPhrase(
									StringFromKey("MayorQuests_dialog_83", npchar),
									StringFromKey("MayorQuests_dialog_84"),
									StringFromKey("MayorQuests_dialog_85", PChar.name))),
							StringFromKey("MayorQuests_dialog_90", LinkRandPhrase(
									StringFromKey("MayorQuests_dialog_87"),
									StringFromKey("MayorQuests_dialog_88", pchar, PChar.name),
									StringFromKey("MayorQuests_dialog_89", pchar)))),
					PCharRepPhrase(
							StringFromKey("MayorQuests_dialog_94", LinkRandPhrase(
									StringFromKey("MayorQuests_dialog_91", GetAddress_Form(NPChar)),
									StringFromKey("MayorQuests_dialog_92"),
									StringFromKey("MayorQuests_dialog_93"))),
							StringFromKey("MayorQuests_dialog_98", LinkRandPhrase(
									StringFromKey("MayorQuests_dialog_95", npchar, GetAddress_Form(NPChar), PChar.lastname),
									StringFromKey("MayorQuests_dialog_96", GetAddress_Form(NPChar)),
									StringFromKey("MayorQuests_dialog_97")))));

			// homo 25/06/06
			link.l1 = StringFromKey("MayorQuests_dialog_102", LinkRandPhrase(
						StringFromKey("MayorQuests_dialog_99"),
						StringFromKey("MayorQuests_dialog_100"),
						StringFromKey("MayorQuests_dialog_101")));
			link.l1.go = "rumours_citizen";
			link.l2 = StringFromKey("MayorQuests_dialog_106", LinkRandPhrase(
						StringFromKey("MayorQuests_dialog_103"),
						StringFromKey("MayorQuests_dialog_104"),
						StringFromKey("MayorQuests_dialog_105")));
			link.l2.go = "exit";  //(перессылка в файл города)
			link.l3 = StringFromKey("MayorQuests_dialog_107");
			link.l3.go = "colony";
			link.l4 = StringFromKey("MayorQuests_dialog_110", RandPhraseSimple(
						StringFromKey("MayorQuests_dialog_108"),
						StringFromKey("MayorQuests_dialog_109")));
			link.l4.go = "exit";  //(перессылка в файл города)
			link.l5 = PCharRepPhrase(
						StringFromKey("MayorQuests_dialog_113", RandPhraseSimple(
								StringFromKey("MayorQuests_dialog_111"),
								StringFromKey("MayorQuests_dialog_112", pchar))),
						StringFromKey("MayorQuests_dialog_116", RandPhraseSimple(
								StringFromKey("MayorQuests_dialog_114"),
								StringFromKey("MayorQuests_dialog_115"))));
			link.l5.go = "exit";
		break;

		case "colony":
			dialog.text = StringFromKey("MayorQuests_dialog_120", LinkRandPhrase(
						StringFromKey("MayorQuests_dialog_117"),
						StringFromKey("MayorQuests_dialog_118"),
						StringFromKey("MayorQuests_dialog_119")));
			switch (Rand(1))
			{
				case 0:
					link.l1 = StringFromKey("MayorQuests_dialog_121");
					link.l1.go = "colony_town";
				break;

				case 1:
					link.l1 = StringFromKey("MayorQuests_dialog_122");
					link.l1.go = "fort";
				break;
			}
			link.l2 = StringFromKey("MayorQuests_dialog_123");
			link.l2.go = "new question";
		break;
		case "colony_town":
			dialog.text = StringFromKey("MayorQuests_dialog_124", UpperFirst(GetAddress_Form(NPChar)), XI_ConvertString("Colony" + NPChar.City));
			link.l1 = StringFromKey("MayorQuests_dialog_125");
			link.l1.go = "exit";
		break;

		case "fort":
			dialog.text = StringFromKey("MayorQuests_dialog_126");
			link.l1 = StringFromKey("MayorQuests_dialog_127");
			link.l1.go = "exit";
		break;
		//==> поймал засланца
		case "SitySpy":
			dialog.text = StringFromKey("MayorQuests_dialog_128");
			link.l1 = StringFromKey("MayorQuests_dialog_129");
			link.l1.go = "SitySpy_1";
		break;
		case "SitySpy_1":
			dialog.text = StringFromKey("MayorQuests_dialog_130");
			link.l1 = StringFromKey("MayorQuests_dialog_131", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city + "Gen"));
			link.l1.go = "SitySpy_3";
		break;
		case "SitySpy_3":
			dialog.text = StringFromKey("MayorQuests_dialog_132");
			link.l1 = StringFromKey("MayorQuests_dialog_133");
			link.l1.go = "SitySpy_4";
		break;
		case "SitySpy_4":
			dialog.text = StringFromKey("MayorQuests_dialog_134");
			link.l1 = StringFromKey("MayorQuests_dialog_135");
			link.l1.go = "SitySpy_5";
		break;
		case "SitySpy_5":
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)]);
			AddQuestRecord("MayorsQuestsList", "5");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city + "Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", sTemp);
			// слухи
			AddSimpleRumour(
						StringFromKey("MayorQuests_dialog_138", RandPhraseSimple(
								StringFromKey("MayorQuests_dialog_136", pchar, sTemp, GetMainCharacterNameGen()),
								StringFromKey("MayorQuests_dialog_137", pchar, GetMainCharacterNameGen()))), sti(characters[sti(pchar.GenQuest.SeekSpy.MayorId)].nation), 5, 1);
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			pchar.GenQuest.SeekSpy = "FoundSpy"; //флаг нашёл шпиона
			DeleteAttribute(pchar, "GenQuest.SeekSpy.City"); //не опрашивать более в городе
			LocatorReloadEnterDisable(pchar.location, "gate_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload1_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload2_back", true);
			LocatorReloadEnterDisable(pchar.location, "boat", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;
		//----------------- найти и уничтожить пирата в море ----------------------
		case "DestroyPirate_Abordage": //абордаж
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate.wasTalkInDeck"))
			{
				dialog.text = StringFromKey("MayorQuests_dialog_139", pchar);
				Link.l1 = StringFromKey("MayorQuests_dialog_140", pchar);
				Link.l1.go = "DP_Abordage_1";
			}
			else
			{
				dialog.text = StringFromKey("MayorQuests_dialog_141", pchar);
				Link.l1 = StringFromKey("MayorQuests_dialog_142", pchar, XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.DestroyPirate.MayorId)].city + "Gen"));
				Link.l1.go = "DP_Abordage_2";
			}
		break;
		case "DP_Abordage_1":
			dialog.text = StringFromKey("MayorQuests_dialog_143");
			Link.l1 = StringFromKey("MayorQuests_dialog_144");
			Link.l1.go = "DP_Abordage_fight";
		break;
		case "DP_Abordage_2":
			dialog.text = StringFromKey("MayorQuests_dialog_145");
			Link.l1 = StringFromKey("MayorQuests_dialog_146");
			Link.l1.go = "DP_Abordage_fight";
		break;
		case "DP_Abordage_fight":
			LAi_SetCurHP(npchar, rand(sti(npchar.chr_ai.hp_max)) + 5);
			LAi_GetCharacterMaxEnergy(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
		break;
		//разговор на палубе
		case "DestroyPirate_Deck":
			pchar.GenQuest.DestroyPirate.wasTalkInDeck = true; //флаг на палубный базар
			dialog.text = StringFromKey("MayorQuests_dialog_147", pchar);
			Link.l1 = StringFromKey("MayorQuests_dialog_148", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.DestroyPirate.MayorId)].city + "Gen"));
			Link.l1.go = "DestroyPirate_1";
		break;
		case "DestroyPirate_1":
			dialog.text = StringFromKey("MayorQuests_dialog_149");
			Link.l1 = StringFromKey("MayorQuests_dialog_150");
			Link.l1.go = "DestroyPirate_2";
		break;
		case "DestroyPirate_2":
			dialog.text = StringFromKey("MayorQuests_dialog_151");
			Link.l1 = StringFromKey("MayorQuests_dialog_152");
			Link.l1.go = "DestroyPirate_3";
		break;
		case "DestroyPirate_3":
			dialog.text = StringFromKey("MayorQuests_dialog_153", pchar);
			Link.l1 = StringFromKey("MayorQuests_dialog_154");
			Link.l1.go = "DestroyPirate_4";
		break;
		case "DestroyPirate_4":
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate.fortPlace") && pchar.GenQuest.DestroyPirate.fortPlace == "1")
			{
				pchar.GenQuest.DestroyPirate.outShoreId = GetIslandRandomShoreId(pchar.GenQuest.DestroyPirate.Areal);
				sTemp = GetConvertStr(pchar.GenQuest.DestroyPirate.outShoreId, "LocLables.txt");
				dialog.text = StringFromKey("MayorQuests_dialog_155", sTemp, XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.DestroyPirate.MayorId)].city + "Pre"));
				Link.l1 = StringFromKey("MayorQuests_dialog_156");
				Link.l1.go = "DestroyPirate_5";
				break;
			}
			if (GetCompanionQuantity(pchar) == 1 && CheckAttribute(pchar, "GenQuest.DestroyPirate.shipState") && sti(pchar.GenQuest.DestroyPirate.shipState) > 1)
			{
				dialog.text = StringFromKey("MayorQuests_dialog_157", pchar);
				Link.l1 = StringFromKey("MayorQuests_dialog_158");
				Link.l1.go = "DP_WithoutFight";
				Link.l2 = StringFromKey("MayorQuests_dialog_159");
				Link.l2.go = "DP_FightInDeck";
			}
			else
			{
				pchar.GenQuest.DestroyPirate.outShoreId = GetIslandRandomShoreId(pchar.GenQuest.DestroyPirate.Areal);
				sTemp = GetConvertStr(pchar.GenQuest.DestroyPirate.outShoreId, "LocLables.txt"); //TODO: на падежи заменить
				dialog.text = StringFromKey("MayorQuests_dialog_160", sTemp, XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.DestroyPirate.MayorId)].city + "Pre"));
				Link.l1 = StringFromKey("MayorQuests_dialog_161", pchar);
				Link.l1.go = "DestroyPirate_5";
			}
		break;
		case "DestroyPirate_5":
			dialog.text = StringFromKey("MayorQuests_dialog_162");
			Link.l1 = StringFromKey("MayorQuests_dialog_163", pchar);
			Link.l1.go = "DP_toShore";
			Link.l2 = StringFromKey("MayorQuests_dialog_164");
			Link.l2.go = "DP_FightInDeck";
		break;

		case "DP_toShore":
			dialog.text = StringFromKey("MayorQuests_dialog_165");
			Link.l1 = StringFromKey("MayorQuests_dialog_166", pchar);
			Link.l1.go = "exit";
			AddDialogExitQuest("DestroyPirate_toShore");
		break;

		case "DP_WithoutFight":
			dialog.text = StringFromKey("MayorQuests_dialog_167");
			Link.l1 = StringFromKey("MayorQuests_dialog_168");
			Link.l1.go = "exit";
			Diag.TempNode = "DP_WithoutFight_again";
			AddDialogExitQuest("DestroyPirate_WithoutFight");
		break;
		case "DP_WithoutFight_again":
			dialog.text = StringFromKey("MayorQuests_dialog_169");
			Link.l1 = StringFromKey("MayorQuests_dialog_170");
			Link.l1.go = "exit";
			Diag.TempNode = "DP_WithoutFight_again";
		break;

		case "DP_FightInDeck":
			dialog.text = StringFromKey("MayorQuests_dialog_171", pchar);
			Link.l1 = StringFromKey("MayorQuests_dialog_172");
			Link.l1.go = "DP_FightInDeck_1";
		break;
		case "DP_FightInDeck_1":
			pchar.GenQuest.DestroyPirate.FightAfterDeck = true; //после резни на палубе - драка в море
			float locx, locy, locz;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "DestroyPirate_FightInDeck", 3.5);
			DialogExit();
		break;
	}
}
