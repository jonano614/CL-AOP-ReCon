// диалоговый файл №2 на голландку
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	float locx, locy, locz;

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("HolLineNpc_2_1");
			link.l1 = StringFromKey("HolLineNpc_2_2");
			link.l1.go = "exit";

			//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
			if (pchar.questTemp.State == "DelivLettTortuga_NotFoundLetter")// кэп пиратов, вывезший де Барраса из Тортуги
			{
				dialog.text = StringFromKey("HolLineNpc_2_3", pchar);
				link.l1 = StringFromKey("HolLineNpc_2_4");
				link.l1.go = "Step_H7_1";
			}
			if (npchar.id == "LoranDeGraf")// Лоран де Граф, квест №8
			{
				dialog.text = StringFromKey("HolLineNpc_2_5", pchar);
				link.l1 = StringFromKey("HolLineNpc_2_6");
				link.l1.go = "exit";
			}
			if (pchar.questTemp.State == "SeekBible_WeWon" && npchar.id == "LoranDeGraf")// Лоран де Граф, квест №8
			{
				dialog.text = StringFromKey("HolLineNpc_2_7", pchar);
				link.l1 = StringFromKey("HolLineNpc_2_8", pchar);
				link.l1.go = "Step_H8_10";
			}
			if (pchar.questTemp.State == "SeekBible_IHaveMap")
			{
				dialog.text = StringFromKey("HolLineNpc_2_9", pchar);
				link.l1 = StringFromKey("HolLineNpc_2_10");
				link.l1.go = "exit";
			}
			if (pchar.questTemp.State == "SeekBible_SeekMoney")
			{
				dialog.text = StringFromKey("HolLineNpc_2_11", pchar);
				if (sti(pchar.money) >= 235000)
				{
					link.l1 = StringFromKey("HolLineNpc_2_12", pchar);
					link.l1.go = "Step_H8_13";
				}
				else
				{
					link.l1 = StringFromKey("HolLineNpc_2_13");
					link.l1.go = "exit";
				}
			}
		break;

		//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//********************************* Диалоги кэпа, который увез де Барраса из Тортуги **********************************
		case "Step_H7_1":
			dialog.text = StringFromKey("HolLineNpc_2_14");
			link.l1 = StringFromKey("HolLineNpc_2_15");
			link.l1.go = "Step_H7_2";
		break;
		case "Step_H7_2":
			dialog.text = StringFromKey("HolLineNpc_2_16");
			link.l1 = StringFromKey("HolLineNpc_2_17");
			link.l1.go = "Step_H7_3";
		break;
		case "Step_H7_3":
			dialog.text = StringFromKey("HolLineNpc_2_18", pchar);
			link.l1 = StringFromKey("HolLineNpc_2_19");
			link.l1.go = "Step_H7_4";
		break;
		case "Step_H7_4":
			GetCharacterPos(pchar, &locx, &locy, &locz);
			for (int i = 1; i <= 2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Pirate" + i, "citiz_" + (rand(9) + 51), "man", "man", 25, PIRATE, 0, true)); //watch_quest_moment
				FantomMakeCoolFighter(sld, 25, 100, 100, BLADE_LONG, "pistol3", 50);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
				ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
			}
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			QuestAboardCabinDialogExitWithBattle("");
			AddQuestRecord("Hol_Line_7_DelivLettTortuga", "8");
			AddQuestUserData("Hol_Line_7_DelivLettTortuga", "sSex", GetSexPhrase("", "а"));
			pchar.questTemp.State.KingResult = "BrigAborded"; //флаг бриг взят на абордаж
			pchar.quest.DelivLettTortuga_BrigDieHard.over = "yes";
			pchar.quest.DelivLettTortuga_AfterBrigSunk.over = "yes";
			Island_SetReloadEnableGlobal("PuertoRico", true);
			Pchar.quest.DelivLettTortuga_AttackWarship.win_condition.l1 = "location";
			Pchar.quest.DelivLettTortuga_AttackWarship.win_condition.l1.location = "SantaCatalina";
			Pchar.quest.DelivLettTortuga_AttackWarship.win_condition = "DelivLettTortuga_AttackWarship";
			SetTimerCondition("DelivLettTortuga_WarshipTimeOver", 0, 0, 12, false);
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;

		case "Step_H8_10":
			dialog.text = StringFromKey("HolLineNpc_2_20");
			link.l1 = StringFromKey("HolLineNpc_2_21", pchar, GetFullName(pchar));
			link.l1.go = "Step_H8_11";
		break;
		case "Step_H8_11":
			dialog.text = StringFromKey("HolLineNpc_2_22");
			link.l1 = StringFromKey("HolLineNpc_2_23");
			link.l1.go = "Step_H8_12";
		break;
		case "Step_H8_12":
			dialog.text = StringFromKey("HolLineNpc_2_24");
			if (sti(pchar.money) >= 235000)
			{
				link.l1 = StringFromKey("HolLineNpc_2_25");
				link.l1.go = "Step_H8_13";
				AddMoneyToCharacter(pchar, -235000);
			}
			else
			{
				link.l1 = StringFromKey("HolLineNpc_2_26");
				link.l1.go = "Step_H8_15";
			}
		break;
		case "Step_H8_13":
			dialog.text = StringFromKey("HolLineNpc_2_27");
			link.l1 = StringFromKey("HolLineNpc_2_28");
			link.l1.go = "Step_H8_14";
			GiveItem2Character(pchar, "LegransMap");
		break;
		case "Step_H8_14":
			dialog.text = StringFromKey("HolLineNpc_2_29");
			link.l1 = StringFromKey("HolLineNpc_2_30", pchar);
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_8_SeekBible", "9");
			NPChar.LifeDay = 2;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			pchar.questTemp.State = "SeekBible_IHaveMap";
			pchar.GenQuestBox.Terks_Grot = true;
			pchar.GenQuestBox.Terks_Grot.box1.items.jewelry5 = 200;
			pchar.GenQuestBox.Terks_Grot.box1.items.jewelry17 = 300;
			pchar.GenQuestBox.Terks_Grot.box1.items.blade33 = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.blade28 = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.blade34 = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.blade32 = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.blade23 = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.pistol5 = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.pistol4 = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.pistol6 = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.potion2 = 5;
			pchar.GenQuestBox.Terks_Grot.box1.items.indian18 = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.jewelry7 = 5;
			pchar.GenQuestBox.Terks_Grot.box1.items.blade5 = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.potion2 = 10;
			pchar.GenQuestBox.Terks_Grot.box1.items.potionwine = 3;
			pchar.GenQuestBox.Terks_Grot.box1.items.jewelry1 = 110;
			pchar.GenQuestBox.Terks_Grot.box1.items.jewelry2 = 60;
			pchar.GenQuestBox.Terks_Grot.box1.items.jewelry3 = 80;
			pchar.GenQuestBox.Terks_Grot.box1.items.jewelry4 = 35;
			pchar.GenQuestBox.Terks_Grot.box1.items.chest = 5;
			pchar.GenQuestBox.Terks_Grot.box1.items.incas_collection = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.jewelry14 = 10;
			pchar.GenQuestBox.Terks_Grot.box1.items.indian6 = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.indian11 = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.indian15 = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.indian12 = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.indian18 = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.cirass5 = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.Bible = 1;

			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;
		case "Step_H8_15":
			dialog.text = StringFromKey("HolLineNpc_2_31", pchar);
			link.l1 = StringFromKey("HolLineNpc_2_32");
			link.l1.go = "exit";
			pchar.questTemp.State = "SeekBible_SeekMoney";
			pchar.quest.SeekBible_DeGrafToTavern.win_condition.l1 = "MapEnter";
			pchar.quest.SeekBible_DeGrafToTavern.win_condition = "SeekBible_DeGrafToTavern";
		break;

	}
}
