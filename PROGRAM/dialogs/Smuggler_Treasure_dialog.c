//navy
#include "DIALOGS\Common_Duel.c"
// boal 29.05.04 даем карту клада
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	aref item;
	bool ok;

	if (!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}

	ProcessDuelDialog(NPChar, link, Diag); //navy

	switch (Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "Map_NotBuy":
			dialog.Text = StringFromKey("Smuggler_Treasure_dialog_1");
			Link.l1 = StringFromKey("Smuggler_Treasure_dialog_2");
			Link.l1.go = "exit";
		break;

		case "First time":
			Diag.TempNode = "First time";

			dialog.Text = StringFromKey("Smuggler_Treasure_dialog_3");
			Link.l1 = StringFromKey("Smuggler_Treasure_dialog_4");
			Link.l1.go = "map_treasure_1";
		break;

		case "map_treasure_1":
			ok = (GetCharacterItem(Pchar, "map_part1") > 0) && (GetCharacterItem(Pchar, "map_part2") > 0);
			if (GetCharacterItem(Pchar, "map_full") > 0 || ok)
			{
				dialog.Text = StringFromKey("Smuggler_Treasure_dialog_5");
				Link.l1 = StringFromKey("Smuggler_Treasure_dialog_6", pchar);
				Link.l1.go = "exit";
			}
			else
			{
				dialog.Text = StringFromKey("Smuggler_Treasure_dialog_7");
				Link.l1 = StringFromKey("Smuggler_Treasure_dialog_8");
				Link.l1.go = "map_treasure_2";
				Link.l2 = StringFromKey("Smuggler_Treasure_dialog_9");
				Link.l2.go = "exit";
			}
		break;

		case "map_treasure_2":
			dialog.Text = StringFromKey("Smuggler_Treasure_dialog_10");
			Link.l1 = StringFromKey("Smuggler_Treasure_dialog_11");
			Link.l1.go = "map_treasure_3";
			Link.l2 = StringFromKey("Smuggler_Treasure_dialog_12");
			Link.l2.go = "exit";
		break;

		case "map_treasure_3":
			if (npchar.quest.trade_date != lastspeak_date)
			{
				npchar.quest.trade_date = lastspeak_date;
			}
			dialog.Text = StringFromKey("Smuggler_Treasure_dialog_13", FindMoneyString(sti(Pchar.GenQuest.TreasureMoney)));
			Link.l1 = StringFromKey("Smuggler_Treasure_dialog_14");
			if (sti(Pchar.Money) >= sti(Pchar.GenQuest.TreasureMoney))
			{
				Link.l1.go = "map_treasure_buy";
			}
			else
			{
				Link.l1.go = "Map_NotBuy";
			}
			Link.l2 = StringFromKey("Smuggler_Treasure_dialog_15");
			Link.l2.go = "exit";
		break;

		case "map_treasure_buy":
			dialog.Text = StringFromKey("Smuggler_Treasure_dialog_16");
			Link.l1 = StringFromKey("Smuggler_Treasure_dialog_17");
			Link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(Pchar.GenQuest.TreasureMoney));
			GiveItem2Character(pchar, "map_full");
			//Items_FindItem("map_full", &item);
			//FillMapForTreasure(item);
			Diag.TempNode = "Temp_treasure";
			npchar.LifeDay = 0; // продал и свалил, если дуэль, то продлится у него жизнь
			RemoveLandQuestMark_Gen(npchar, "Gen_Smuggler_Treasure");
		break;

		case "Temp_treasure":
			dialog.Text = StringFromKey("Smuggler_Treasure_dialog_18");
			Link.l1 = StringFromKey("Smuggler_Treasure_dialog_19");
			Link.l1.go = "exit";
			ok = (GetCharacterItem(Pchar, "map_part1") > 0) || (GetCharacterItem(Pchar, "map_part2") > 0);
			if (GetCharacterItem(Pchar, "map_full") == 0 && !ok)
			{
				Link.l2 = StringFromKey("Smuggler_Treasure_dialog_20");
				Link.l2.go = "Temp_treasure_1";
			}
			Diag.TempNode = "Temp_treasure";
		break;

		case "Temp_treasure_1":
			dialog.Text = StringFromKey("Smuggler_Treasure_dialog_21");
			Link.l1 = StringFromKey("Smuggler_Treasure_dialog_22");
			Link.l1.go = "exit";
			Link.l2 = StringFromKey("Smuggler_Treasure_dialog_23");
			//			Link.l2.go = "tavern_keeper";
			//			Diag.TempNode = "Temp_treasure";
			Link.l2.go = "outraged"; //navy -- дуэли!!!
			Diag.TempNode = "let_s_duel";
			npchar.LifeDay = 1; // чтоб не слетел на выходе
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;

		case "tavern_keeper":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
	}
}
