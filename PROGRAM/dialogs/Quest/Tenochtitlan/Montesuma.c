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
		case "First time":
			dialog.text = StringFromKey("Montesuma_1", pchar);
			link.l1 = StringFromKey("Montesuma_2", pchar);
			link.l1.go = "FT_1";
			if (pchar.questTemp.Teno == "takeFire")
			{
				dialog.text = StringFromKey("Montesuma_3", pchar);
				link.l1 = StringFromKey("Montesuma_4", pchar);
				link.l1.go = "FTS_1";
			}
		break;
		case "FT_1":
			dialog.text = StringFromKey("Montesuma_5", pchar);
			link.l1 = StringFromKey("Montesuma_6");
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = StringFromKey("Montesuma_7");
			link.l1 = StringFromKey("Montesuma_8");
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = StringFromKey("Montesuma_9", pchar);
			link.l1 = StringFromKey("Montesuma_10", GetFullName(pchar));
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = StringFromKey("Montesuma_11", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("Montesuma_12");
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = StringFromKey("Montesuma_13", pchar);
			link.l1 = StringFromKey("Montesuma_14");
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = StringFromKey("Montesuma_15");
			link.l1 = StringFromKey("Montesuma_16");
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = StringFromKey("Montesuma_17", pchar);
			link.l1 = StringFromKey("Montesuma_18");
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = StringFromKey("Montesuma_19");
			link.l1 = StringFromKey("Montesuma_20");
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			dialog.text = StringFromKey("Montesuma_21");
			link.l1 = StringFromKey("Montesuma_22");
			link.l1.go = "FT_11";
		break;
		case "FT_11":
			dialog.text = StringFromKey("Montesuma_23", pchar);
			link.l1 = StringFromKey("Montesuma_24");
			link.l1.go = "FT_12";
		break;
		case "FT_12":
			dialog.text = StringFromKey("Montesuma_25");
			link.l1 = StringFromKey("Montesuma_26");
			link.l1.go = "FT_13";
		break;
		case "FT_13":
			dialog.text = StringFromKey("Montesuma_27");
			link.l1 = StringFromKey("Montesuma_28");
			link.l1.go = "FT_14";
		break;
		case "FT_14":
			dialog.text = StringFromKey("Montesuma_29");
			link.l1 = StringFromKey("Montesuma_30");
			link.l1.go = "FT_15";
		break;
		case "FT_15":
			dialog.text = StringFromKey("Montesuma_31", pchar);
			link.l1 = StringFromKey("Montesuma_32");
			link.l1.go = "FT_16";
		break;
		case "FT_16":
			dialog.text = StringFromKey("Montesuma_33");
			link.l1 = StringFromKey("Montesuma_34");
			link.l1.go = "FT_17";
		break;
		case "FT_17":
			dialog.text = StringFromKey("Montesuma_35", pchar);
			link.l1 = StringFromKey("Montesuma_36", pchar);
			link.l1.go = "FT_18";
		break;
		case "FT_18":
			dialog.text = StringFromKey("Montesuma_37");
			link.l1 = StringFromKey("Montesuma_38");
			link.l1.go = "FT_19";
		break;
		case "FT_19":
			dialog.text = StringFromKey("Montesuma_39");
			link.l1 = StringFromKey("Montesuma_40");
			link.l1.go = "FT_20";
		break;
		case "FT_20":
			dialog.text = StringFromKey("Montesuma_41");
			link.l1 = StringFromKey("Montesuma_42");
			link.l1.go = "FT_21";
		break;
		case "FT_21":
			dialog.text = StringFromKey("Montesuma_43");
			link.l1 = StringFromKey("Montesuma_44");
			link.l1.go = "FT_22";
		break;
		case "FT_22":
			dialog.text = StringFromKey("Montesuma_45");
			link.l1 = StringFromKey("Montesuma_46");
			link.l1.go = "FT_23";
		break;
		case "FT_23":
			dialog.text = StringFromKey("Montesuma_47");
			link.l1 = StringFromKey("Montesuma_48");
			link.l1.go = "FT_24";
		break;
		case "FT_24":
			dialog.text = StringFromKey("Montesuma_49");
			link.l1 = StringFromKey("Montesuma_50");
			link.l1.go = "FT_25";
		break;
		case "FT_25":
			dialog.text = StringFromKey("Montesuma_51", pchar);
			link.l1 = StringFromKey("Montesuma_52");
			link.l1.go = "exit";
			npchar.location.locator = "quest1";
			NextDiag.TempNode = "Fire";
			AddDialogExitQuestFunction("Teno_MontesumaGoQuest1");
			AddDialogExitQuestFunction("Teno_SeekFireMagicTotems_SetQuestPointers");
		break;
		//--------------
		case "FTS_1":
			dialog.text = StringFromKey("Montesuma_53", pchar);
			link.l1 = StringFromKey("Montesuma_54", GetFullName(pchar));
			link.l1.go = "FTS_2";
		break;
		case "FTS_2":
			dialog.text = StringFromKey("Montesuma_55", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("Montesuma_56");
			link.l1.go = "FTS_3";
		break;
		case "FTS_3":
			dialog.text = StringFromKey("Montesuma_57");
			link.l1 = StringFromKey("Montesuma_58");
			link.l1.go = "FTS_4";
		break;
		case "FTS_4":
			dialog.text = StringFromKey("Montesuma_59", pchar);
			link.l1 = StringFromKey("Montesuma_60");
			link.l1.go = "FTS_5";
		break;
		case "FTS_5":
			dialog.text = StringFromKey("Montesuma_61");
			link.l1 = StringFromKey("Montesuma_62");
			link.l1.go = "FTS_6";
		break;
		case "FTS_6":
			dialog.text = StringFromKey("Montesuma_63");
			link.l1 = StringFromKey("Montesuma_64");
			link.l1.go = "FTS_7";
		break;
		case "FTS_7":
			dialog.text = StringFromKey("Montesuma_65", pchar);
			link.l1 = StringFromKey("Montesuma_66");
			link.l1.go = "FTS_8";
		break;
		case "FTS_8":
			dialog.text = StringFromKey("Montesuma_67");
			link.l1 = StringFromKey("Montesuma_68");
			link.l1.go = "FTS_9";
		break;
		case "FTS_9":
			dialog.text = StringFromKey("Montesuma_69");
			link.l1 = StringFromKey("Montesuma_70");
			link.l1.go = "FTS_10";
		break;
		case "FTS_10":
			dialog.text = StringFromKey("Montesuma_71");
			link.l1 = StringFromKey("Montesuma_72");
			link.l1.go = "FTS_11";
		break;
		case "FTS_11":
			dialog.text = StringFromKey("Montesuma_73", pchar);
			link.l1 = StringFromKey("Montesuma_74");
			link.l1.go = "FTS_12";
		break;
		case "FTS_12":
			dialog.text = StringFromKey("Montesuma_75");
			link.l1 = StringFromKey("Montesuma_76");
			link.l1.go = "FTS_13";
		break;
		case "FTS_13":
			dialog.text = StringFromKey("Montesuma_77", pchar);
			link.l1 = StringFromKey("Montesuma_78", pchar);
			link.l1.go = "FTS_14";
		break;
		case "FTS_14":
			dialog.text = StringFromKey("Montesuma_79", pchar);
			link.l1 = StringFromKey("Montesuma_80");
			link.l1.go = "Fire_1";
		break;
		//после снятия огня
		case "Fire":
			if (CheckAttribute(loadedLocation, "gotoFire"))
			{
				dialog.text = StringFromKey("Montesuma_81");
				link.l1 = StringFromKey("Montesuma_82");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Montesuma_83", pchar);
				link.l1 = StringFromKey("Montesuma_84");
				link.l1.go = "Fire_1";
			}
		break;
		case "Fire_1":
			dialog.text = StringFromKey("Montesuma_85", pchar);
			link.l1 = StringFromKey("Montesuma_86");
			link.l1.go = "Fire_2";
		break;
		case "Fire_2":
			dialog.text = StringFromKey("Montesuma_87");
			link.l1 = StringFromKey("Montesuma_88");
			link.l1.go = "Fire_3";
		break;
		case "Fire_3":
			dialog.text = StringFromKey("Montesuma_89");
			link.l1 = StringFromKey("Montesuma_90", pchar);
			link.l1.go = "Fire_4";
		break;
		case "Fire_4":
			dialog.text = StringFromKey("Montesuma_91", pchar);
			link.l1 = StringFromKey("Montesuma_92");
			link.l1.go = "Fire_5";
		break;
		case "Fire_5":
			dialog.text = StringFromKey("Montesuma_93", pchar);
			link.l1 = StringFromKey("Montesuma_94");
			link.l1.go = "Fire_6";
		break;
		case "Fire_6":
			dialog.text = StringFromKey("Montesuma_95");
			link.l1 = StringFromKey("Montesuma_96");
			link.l1.go = "Fire_7";
		break;
		case "Fire_7":
			dialog.text = StringFromKey("Montesuma_97", pchar);
			link.l1 = StringFromKey("Montesuma_98");
			link.l1.go = "exit";
			NextDiag.TempNode = "Totem";
			pchar.questTemp.Teno = "openTenTemples";
			AddQuestRecord("TenochtitlanQuest", "3");
			AddQuestUserData("TenochtitlanQuest", "sSex", GetSexPhrase("ен", "на"));
			RemoveLandQuestMark_Main(npchar, "TenochtitlanQuest");
			AddDialogExitQuestFunction("Teno_SeekFireMagicTotems_DelQuestPointers");
			AddDialogExitQuestFunction("Teno_SeekTempleTotems_SetQuestPointers");
		break;

		case "Totem":
			dialog.text = StringFromKey("Montesuma_99", pchar);
			link.l1 = StringFromKey("Montesuma_100");
			link.l1.go = "exit";
		break;

		//после драки с 
		case "AfterGTemple":
			if (CheckCharacterItem(pchar, "SkullAztec")) //череп найден
			{
				dialog.text = StringFromKey("Montesuma_101", pchar);
				if (CheckCharacterItem(pchar, "pistol7"))
				{
					link.l1 = StringFromKey("Montesuma_102");
					link.l1.go = "Skull_1";
				}
				else
				{
					link.l1 = StringFromKey("Montesuma_103", pchar);
					link.l1.go = "NotShootgun_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("Montesuma_104", pchar);
				link.l1 = StringFromKey("Montesuma_105", pchar);
				link.l1.go = "NotSkull";
			}
		break;
		//с собой нет черепа
		case "NotSkull":
			dialog.text = StringFromKey("Montesuma_106", pchar);
			link.l1 = StringFromKey("Montesuma_107");
			link.l1.go = "NotSkull_1";
		break;
		case "NotSkull_1":
			chrDisableReloadToLocation = true;
			LAi_group_SetRelation("MontesumaGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("MontesumaGroup", LAI_GROUP_PLAYER, true);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NotShootgun_1":
			dialog.text = StringFromKey("Montesuma_108");
			link.l1 = StringFromKey("Montesuma_109");
			link.l1.go = "NotShootgun_2";
		break;
		case "NotShootgun_2":
			dialog.text = StringFromKey("Montesuma_110");
			link.l1 = StringFromKey("Montesuma_111");
			link.l1.go = "NotShootgun_3";
		break;
		case "NotShootgun_3":
			dialog.text = StringFromKey("Montesuma_112");
			link.l1 = StringFromKey("Montesuma_113");
			link.l1.go = "Skull_1";
		break;

		case "Skull_1":
			dialog.text = StringFromKey("Montesuma_114", pchar);
			link.l1 = StringFromKey("Montesuma_115");
			link.l1.go = "Skull_2";
		break;
		case "Skull_2":
			dialog.text = StringFromKey("Montesuma_116");
			link.l1 = StringFromKey("Montesuma_117");
			link.l1.go = "Skull_3";
		break;
		case "Skull_3":
			dialog.text = StringFromKey("Montesuma_118");
			link.l1 = StringFromKey("Montesuma_119");
			link.l1.go = "Skull_4";
		break;
		case "Skull_4":
			dialog.text = StringFromKey("Montesuma_120");
			link.l1 = StringFromKey("Montesuma_121");
			link.l1.go = "Skull_5";
		break;
		case "Skull_5":
			dialog.text = StringFromKey("Montesuma_122");
			link.l1 = StringFromKey("Montesuma_123", pchar);
			link.l1.go = "Skull_6";
		break;
		case "Skull_6":
			dialog.text = StringFromKey("Montesuma_124", pchar);
			link.l1 = StringFromKey("Montesuma_125");
			link.l1.go = "Skull_7";
		break;
		case "Skull_7":
			AddQuestRecord("TenochtitlanQuest", "5");
			AddQuestUserData("TenochtitlanQuest", "sSex", GetSexPhrase("ся", "ась"));
			LAi_SetImmortal(npchar, false);
			LocatorReloadEnterDisable("Tenochtitlan", "reload1_back", false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "MontesumaGroup");
			LAi_group_SetRelation("MontesumaGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("MontesumaGroup", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("MontesumaGroup", "OpenTheDoors");
			pchar.quest.Teno_clearGroups.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Teno_clearGroups.win_condition.l1.location = pchar.location;
			pchar.quest.Teno_clearGroups.function = "Teno_clearGroups";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
