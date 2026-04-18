int iTotalTemp; //Работает, пока активен интерфейс

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iGun, qty; //iMush TODO: торговля мушкетами
	string sGroup, sLink, sText;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Carib" + locations[FindLocation(npchar.location)].index + "_";

	switch (Dialog.CurrentNode)
	{
		case "exit_fight":
			chrDisableReloadToLocation = false;
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
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
			LAi_group_SetCheck(sGroup, "LandEnc_CaribAfrer");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_peace":
			chrDisableReloadToLocation = false;
			DialogExit();
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_SetImmortal(sld, false);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_group_SetCheck(sGroup, "LandEnc_CaribAfrer");
			ChangeIndianRelation(0.5);
		break;

		// Карибы (агрессивные) -->
		case "war_indian":
			chrDisableReloadToLocation = false;
			LAi_LockFightMode(pchar, false);
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			if (sti(pchar.questTemp.Indian.relation) >= 60) //TODO: откалибровать
			{
				dialog.text = StringFromKey("Indians_4", LinkRandPhrase(
							StringFromKey("Indians_1", pchar),
							StringFromKey("Indians_2", pchar, npchar.name),
							StringFromKey("Indians_3", pchar, npchar.name)));
				link.l1 = StringFromKey("Indians_7", RandPhraseSimple(
							StringFromKey("Indians_5"),
							StringFromKey("Indians_6")));
				link.l1.go = "exit_peace";
				if (CheckCaribGuns())
				{
					npchar.quest.count = 0;
					link.l2 = StringFromKey("Indians_10", RandPhraseSimple(
								StringFromKey("Indians_8"),
								StringFromKey("Indians_9")));
					link.l2.go = "war_indian_trade";
				}
			}
			else
			{
				dialog.text = StringFromKey("Indians_14", LinkRandPhrase(
							StringFromKey("Indians_11", pchar),
							StringFromKey("Indians_12"),
							StringFromKey("Indians_13")));
				link.l1 = StringFromKey("Indians_17", RandPhraseSimple(
							StringFromKey("Indians_15"),
							StringFromKey("Indians_16")));
				link.l1.go = "war_indian_1";
				link.l2 = StringFromKey("Indians_20", RandPhraseSimple(
							StringFromKey("Indians_18", pchar),
							StringFromKey("Indians_19", pchar)));
				if (sti(pchar.questTemp.Indian.relation) + (makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) / 3)) > dRandEx(70, true)) link.l2.go = "war_indian_2_1";
				else link.l2.go = "war_indian_2_2"; //TODO: откалибровать
				link.l3 = StringFromKey("Indians_23", RandPhraseSimple(
							StringFromKey("Indians_21", pchar),
							StringFromKey("Indians_22")));
				if (sti(pchar.questTemp.Indian.relation) + (makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) / 6) + makeint(GetSummonSkillFromName(pchar, SKILL_FORTUNE) / 6)) > dRandEx(80, true)) link.l3.go = "war_indian_3_1";
				else link.l3.go = "war_indian_3_2"; //TODO: откалибровать
			}
		break;

		case "war_indian_1":
			dialog.text = StringFromKey("Indians_26", RandPhraseSimple(
						StringFromKey("Indians_24", pchar),
						StringFromKey("Indians_25", pchar)));
			link.l1 = StringFromKey("Indians_29", RandPhraseSimple(
						StringFromKey("Indians_27"),
						StringFromKey("Indians_28")));
			link.l1.go = "exit_fight";
		break;

		case "war_indian_2_1":
			dialog.text = StringFromKey("Indians_32", RandPhraseSimple(
						StringFromKey("Indians_30", pchar),
						StringFromKey("Indians_31")));
			link.l1 = StringFromKey("Indians_35", RandPhraseSimple(
						StringFromKey("Indians_33"),
						StringFromKey("Indians_34", pchar)));
			link.l1.go = "exit_peace";
		break;

		case "war_indian_2_2":
			dialog.text = StringFromKey("Indians_38", RandPhraseSimple(
						StringFromKey("Indians_36"),
						StringFromKey("Indians_37")));
			link.l1 = StringFromKey("Indians_41", RandPhraseSimple(
						StringFromKey("Indians_39", pchar),
						StringFromKey("Indians_40")));
			link.l1.go = "exit_fight";
		break;

		case "war_indian_3_1":
			if (CheckCaribGuns())
			{
				npchar.quest.count = 0;
				dialog.text = StringFromKey("Indians_42");
				link.l1 = StringFromKey("Indians_43");
				link.l1.go = "war_indian_trade";
				link.l2 = StringFromKey("Indians_44");
				link.l2.go = "exit_fight";
			}
			else
			{
				dialog.text = StringFromKey("Indians_45", pchar);
				link.l1 = StringFromKey("Indians_46");
				link.l1.go = "exit_fight";
			}
		break;

		case "war_indian_3_2":
			dialog.text = StringFromKey("Indians_49", RandPhraseSimple(
						StringFromKey("Indians_47", pchar),
						StringFromKey("Indians_48")));
			link.l1 = StringFromKey("Indians_52", RandPhraseSimple(
						StringFromKey("Indians_50"),
						StringFromKey("Indians_51")));
			link.l1.go = "exit_fight";
		break;

		case "war_indian_trade":
			iGun = 1;
			dialog.text = StringFromKey("Indians_53");
			for (i = 6; i > 0; i--)
			{
				if (GetCharacterFreeItem(pchar, "pistol" + i) > 0)
				{
					sLink = "l" + iGun;
					link.(sLink) = StringFromKey("Indians_54", LowerFirst(GetItemName("pistol" + i)));
					link.(sLink).go = "gun_" + i;
					iGun++;
				}
			}
		break;

		case "gun_1":
			npchar.quest.gun = "pistol1";
			if (IndRand(1, npchar) == 0)
			{
				npchar.quest.item = "potion" + (IndRand(2, npchar) + 2);
				iTotalTemp = IndRand(1, npchar) + 1;
				sText = StringFromKey("Indians_55", FindQtyString(iTotalTemp));
			}
			else
			{
				npchar.quest.item = "jewelry16";
				iTotalTemp = IndRand(2, npchar) + 1;
				sText = StringFromKey("Indians_56", FindQtyString(iTotalTemp));
			}
			dialog.text = StringFromKey("Indians_57", sText);
			link.l1 = StringFromKey("Indians_58");
			link.l1.go = "war_indian_trade_agree";
			link.l2 = StringFromKey("Indians_59");
			link.l2.go = "war_indian_trade_bad";
		break;

		case "gun_2":
			npchar.quest.gun = "pistol2";
			if (IndRand(3, npchar) < 2)
			{
				npchar.quest.item = "potion" + (IndRand(2, npchar) + 2);
				iTotalTemp = IndRand(2, npchar) + 2;
				sText = StringFromKey("Indians_60", FindQtyString(iTotalTemp));
			}
			else
			{
				npchar.quest.item = "jewelry" + (IndRand(3, npchar) + 1);
				iTotalTemp = IndRand(2, npchar) + 2;
				sText = StringFromKey("Indians_61", FindQtyString(iTotalTemp));
			}
			dialog.text = StringFromKey("Indians_62", sText);
			link.l1 = StringFromKey("Indians_63");
			link.l1.go = "war_indian_trade_agree";
			link.l2 = StringFromKey("Indians_64");
			link.l2.go = "war_indian_trade_bad";
		break;

		case "gun_3":
			npchar.quest.gun = "pistol3";
			if (IndRand(5, npchar) < 3)
			{
				qty = IndRand(1, npchar) + 1;
				npchar.quest.item = "jewelry1" + qty;
				iTotalTemp = IndRand(6, npchar) + qty * 15;
				sText = StringFromKey("Indians_65", FindQtyString(iTotalTemp));
			}
			else
			{
				npchar.quest.item = "jewelry" + (IndRand(2, npchar) + 2);
				iTotalTemp = IndRand(2, npchar) + 5;
				sText = StringFromKey("Indians_66", FindQtyString(iTotalTemp));
			}
			dialog.text = StringFromKey("Indians_67", sText);
			link.l1 = StringFromKey("Indians_68");
			link.l1.go = "war_indian_trade_agree";
			link.l2 = StringFromKey("Indians_69");
			link.l2.go = "war_indian_trade_bad";
		break;

		case "gun_4":
			npchar.quest.gun = "pistol4";
			if (IndRand(9, npchar) < 8)
			{
				qty = IndRand(1, npchar) + 1;
				npchar.quest.item = GetSubStringByNum("jewelry17,jewelry5", qty);
				iTotalTemp = IndRand(10, npchar) + qty * 30; //золота даёт в 2 раза меньше
				sText = StringFromKey("Indians_70", FindQtyString(iTotalTemp));
			}
			else
			{
				npchar.quest.item = "indian11"; //TODO: после медицины пусть будет другой набор вещей, но не Крысобог
				iTotalTemp = 1;                    //к тому же это не пантеон Карибов (Камазоц)
				sText = StringFromKey("Indians_71");
			}
			dialog.text = StringFromKey("Indians_72", sText);
			link.l1 = StringFromKey("Indians_73");
			link.l1.go = "war_indian_trade_agree";
			link.l2 = StringFromKey("Indians_74");
			link.l2.go = "war_indian_trade_bad";
		break;

		case "gun_5":
			npchar.quest.gun = "pistol5";
			if (IndRand(7, npchar) < 7)
			{
				if (IndRand(10, npchar) < 8)
				{
					npchar.quest.item = "jewelry4";
					iTotalTemp = IndRand(4, npchar) + 10;
				}
				else
				{
					npchar.quest.item = GetSubStringByNum("jewelry1,jewelry2,jewelry3", IndRand(3, npchar));
					iTotalTemp = IndRand(4, npchar) + 18;
				}
				sText = StringFromKey("Indians_75", FindQtyString(iTotalTemp));
			}
			else
			{
				npchar.quest.item = "indian18"; //TODO: после медицины пусть будет другой набор вещей, но не Атлауа
				iTotalTemp = 1;                    //к тому же это не пантеон Карибов
				sText = StringFromKey("Indians_76");
			}
			dialog.text = StringFromKey("Indians_77", sText);
			link.l1 = StringFromKey("Indians_78");
			link.l1.go = "war_indian_trade_agree";
			link.l2 = StringFromKey("Indians_79");
			link.l2.go = "war_indian_trade_bad";
		break;

		case "gun_6":
			npchar.quest.gun = "pistol6";
			if (IndRand(9, npchar) < 8)
			{
				qty = IndRand(1, npchar) + 1;
				npchar.quest.item = GetSubStringByNum("jewelry17,jewelry5", qty);
				iTotalTemp = IndRand(8, npchar) + qty * 20; //золота даёт в 2 раза меньше
				sText = StringFromKey("Indians_80", FindQtyString(iTotalTemp));
			}
			else
			{
				npchar.quest.item = "indian18"; //TODO: после медицины пусть будет другой набор вещей, но не Атлауа
				iTotalTemp = 1;                    //к тому же это не пантеон Карибов
				sText = StringFromKey("Indians_81");
			}
			dialog.text = StringFromKey("Indians_82", sText);
			link.l1 = StringFromKey("Indians_83");
			link.l1.go = "war_indian_trade_agree";
			link.l2 = StringFromKey("Indians_84");
			link.l2.go = "war_indian_trade_bad";
		break;

		case "war_indian_trade_agree":
			ChangeIndianRelation(1.0);
			npchar.quest.count = sti(npchar.quest.count) + 1;
			TakeNItems(pchar, npchar.quest.item, iTotalTemp);
			RemoveItems(pchar, npchar.quest.gun, 1);
			LogSound_WithNotify(StringFromKey("InfoMessages_200", LowerFirst(GetItemName(npchar.quest.gun)), LowerFirst(GetItemName(npchar.quest.item)), FindQtyString(iTotalTemp)), "Important_item", "BoxPlus");
			if (sti(npchar.quest.count) > 3 + idRand(npchar.id + npchar.location, 2))
			{
				dialog.text = StringFromKey("Indians_85");
				link.l1 = StringFromKey("Indians_86");
				link.l1.go = "exit_peace";
			}
			else
			{
				dialog.text = StringFromKey("Indians_87");
				if (CheckCaribGuns())
				{
					link.l1 = StringFromKey("Indians_88");
					link.l1.go = "war_indian_trade";
				}
				link.l2 = StringFromKey("Indians_89");
				link.l2.go = "war_indian_trade_exit";
			}
		break;

		case "war_indian_trade_exit":
			dialog.text = StringFromKey("Indians_90");
			link.l1 = StringFromKey("Indians_91");
			link.l1.go = "exit_peace";
		break;

		case "war_indian_trade_bad":
			if (sti(pchar.questTemp.Indian.relation) >= 60) //TODO: откалибровать
			{
				DialogExit();
				sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
				for (i = 0; i < iTemp; i++)
				{
					sld = CharacterFromID(sTemp + i);
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sGroup);
					LAi_SetImmortal(sld, false);
					LAi_CharacterDisableDialog(sld);
				}
			}
			else
			{
				dialog.text = StringFromKey("Indians_92");
				link.l1 = StringFromKey("Indians_93");
				link.l1.go = "exit_fight";
			}
		break;
		// <-- Карибы (агрессивные)

		// Мискито (мирные) -->
		// TODO: торговля травами
		case "peace_indian":
			chrDisableReloadToLocation = false;
			LAi_LockFightMode(pchar, false);
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = StringFromKey("Indians_97", LinkRandPhrase(
						StringFromKey("Indians_94"),
						StringFromKey("Indians_95"),
						StringFromKey("Indians_96")));
			link.l1 = StringFromKey("Indians_100", RandPhraseSimple(
						StringFromKey("Indians_98"),
						StringFromKey("Indians_99")));
			link.l1.go = "peace_indian_1";
			link.l2 = StringFromKey("Indians_103", RandPhraseSimple(
						StringFromKey("Indians_101"),
						StringFromKey("Indians_102")));
			link.l2.go = "peace_indian_2";
		break;

		case "peace_indian_1":
			dialog.text = StringFromKey("Indians_106", RandPhraseSimple(
						StringFromKey("Indians_104"),
						StringFromKey("Indians_105", pchar)));
			link.l1 = StringFromKey("Indians_109", RandPhraseSimple(
						StringFromKey("Indians_107"),
						StringFromKey("Indians_108")));
			link.l1.go = "exit_peace";
		break;

		case "peace_indian_2":
			dialog.text = StringFromKey("Indians_112", RandPhraseSimple(
						StringFromKey("Indians_110"),
						StringFromKey("Indians_111")));
			link.l1 = StringFromKey("Indians_115", RandPhraseSimple(
						StringFromKey("Indians_113"),
						StringFromKey("Indians_114")));
			link.l1.go = "exit_fight";
		break;
		// <-- Мискито (мирные)
	}
}

int IndRand(int _rand, ref _npchar)
{
	return idRand(_npchar.id + _npchar.quest.count + _npchar.quest.gun, _rand);
}