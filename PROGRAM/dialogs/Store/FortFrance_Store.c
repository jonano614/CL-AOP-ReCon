// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortFrance_Store_1"),
						StringFromKey("FortFrance_Store_2"),
						StringFromKey("FortFrance_Store_3"),
						StringFromKey("FortFrance_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortFrance_Store_5", NPChar.name),
						StringFromKey("FortFrance_Store_6", pchar),
						StringFromKey("FortFrance_Store_7"),
						StringFromKey("FortFrance_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";

			if (CheckAttribute(pchar, "MainQuest"))
			{
				switch (pchar.MainQuest)
				{
					case "FL1_s28":
						link.l1 = StringFromKey("FortFrance_Store_9");
						link.l1.go = "FL1";
					break;

					case "FL4_s49":
						if (!CheckAttribute(pchar, "MainQuest.FL4_s49.store"))
						{
							link.l1 = StringFromKey("FortFrance_Store_10");
							link.l1.go = "FL4_1";
						}
					break;

					case "FL6_s31_needMoney":
						if (sti(pchar.money) >= 100000)
						{
							link.l1 = StringFromKey("FortFrance_Store_11");
							link.l1.go = "exit";
							//AddDialogExitQuest("FL6_s31");
						}
					break;
				}
			}

			if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "FL1_s37" && !LAi_IsDead(CharacterFromID("FL_Mary")))
			{
				link.l1 = StringFromKey("FortFrance_Store_12");
				link.l1.go = "FL8";
			}
		break;

		//----------------------------------------------------------------------------------------------
		//	Фр. сюжет - Разоблачение
		case "FL4_1":
			dialog.text = StringFromKey("FortFrance_Store_13");
			link.l1 = StringFromKey("FortFrance_Store_14");
			link.l1.go = "FL4_2";
		break;

		case "FL4_2":
			dialog.text = StringFromKey("FortFrance_Store_15");
			link.l1 = StringFromKey("FortFrance_Store_16");
			link.l1.go = "exit";

			pchar.MainQuest.FL4_s49.store = 1;
		//AddDialogExitQuest("FL4_s50");
		break;

		//---------------------------------------------------
		//	Французский сюжет
		case "FL1":
			dialog.text = StringFromKey("FortFrance_Store_17");
			link.l1 = StringFromKey("FortFrance_Store_18");
			link.l1.go = "FL2";
		break;

		case "FL2":
			dialog.text = StringFromKey("FortFrance_Store_19");
			link.l1 = StringFromKey("FortFrance_Store_20");
			link.l1.go = "FL3";
		break;

		case "FL3":
			dialog.text = StringFromKey("FortFrance_Store_21");
			link.l1 = StringFromKey("FortFrance_Store_22");
			link.l1.go = "FL5";
			link.l2 = StringFromKey("FortFrance_Store_23");
			link.l2.go = "FL4";

		break;

		case "FL4":
			dialog.text = StringFromKey("FortFrance_Store_24");
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.MainQuest = "FL1_s30_v1";
			AddDialogExitQuest("FL1_s30");
		break;

		case "FL5":
			dialog.text = StringFromKey("FortFrance_Store_25");
			link.l1 = StringFromKey("FortFrance_Store_26");
			link.l1.go = "FL6";
		break;

		case "FL6":
			dialog.text = StringFromKey("FortFrance_Store_27");
			link.l1 = StringFromKey("FortFrance_Store_28");
			link.l1.go = "FL7";
		break;

		case "FL7":
			dialog.text = StringFromKey("FortFrance_Store_29");
			link.l1 = "...";
			link.l1.go = "exit";

			AddDialogExitQuest("FL1_s32");
		break;

		case "FL8":
			dialog.text = StringFromKey("FortFrance_Store_30");
			link.l1 = StringFromKey("FortFrance_Store_31", npchar.name);
			link.l1.go = "FL9";
		break;

		case "FL9":
			dialog.text = StringFromKey("FortFrance_Store_32");
			link.l1 = StringFromKey("FortFrance_Store_33");
			link.l1.go = "FL10";
		break;

		case "FL10":
			dialog.text = StringFromKey("FortFrance_Store_34");
			link.l1 = StringFromKey("FortFrance_Store_35");
			link.l1.go = "FL11";
		break;

		case "FL11":
			dialog.text = StringFromKey("FortFrance_Store_36");
			link.l1 = StringFromKey("FortFrance_Store_37");
			link.l1.go = "exit";

			AddDialogExitQuest("FL1_s38");
		break;

		case "FL":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "FL";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
