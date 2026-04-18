// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Villemstad_Store_1"),
						StringFromKey("Villemstad_Store_2"),
						StringFromKey("Villemstad_Store_3"),
						StringFromKey("Villemstad_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Villemstad_Store_5", NPChar.name),
						StringFromKey("Villemstad_Store_6", pchar),
						StringFromKey("Villemstad_Store_7"),
						StringFromKey("Villemstad_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			if (pchar.questTemp.State == "Inquisition_toCuracao" || pchar.questTemp.State == "Inquisition_afterFrancisco")// квест №2 голл. линейки.
			{
				if (!CheckAttribute(pchar, "questTemp.State.Store"))
				{
					dialog.text = StringFromKey("Villemstad_Store_9");
					link.l1 = StringFromKey("Villemstad_Store_10", GetFullName(pchar));
					link.l1.go = "Step_S2_1";
				}
				else
				{
					if (CheckPassengerInCharacter(pchar, "JacowDeFonseka"))
					{
						dialog.text = StringFromKey("Villemstad_Store_11");
						link.l1 = StringFromKey("Villemstad_Store_12");
						link.l1.go = "Step_S2_7";
						AddMoneyToCharacter(pchar, 100000);
						pchar.questTemp.State.Store = "Ok";
						AddQuestRecord("Spa_Line_2_Inquisition", "14");
						RemovePassenger(pchar, characterFromId("JacowDeFonseka"));
					}
					else
					{
						if (pchar.questTemp.State.Store != "Ok")
						{
							dialog.text = StringFromKey("Villemstad_Store_13");
							link.l1 = StringFromKey("Villemstad_Store_14");
							link.l1.go = "exit";
						}
						else
						{
							dialog.text = StringFromKey("Villemstad_Store_15");
							link.l1 = StringFromKey("Villemstad_Store_16");
							link.l1.go = "exit";
						}
					}
				}
			}
		// <== Проверяем поле состояния квестов.
		break;
		//*************************** Квест №2 испанки, задание Инквизиции ***************************
		case "Step_S2_1":
			dialog.text = StringFromKey("Villemstad_Store_17");
			link.l1 = StringFromKey("Villemstad_Store_18");
			link.l1.go = "Step_S2_2";
		break;
		case "Step_S2_2":
			dialog.text = StringFromKey("Villemstad_Store_19");
			link.l1 = StringFromKey("Villemstad_Store_20");
			link.l1.go = "Step_S2_3";
		break;
		case "Step_S2_3":
			dialog.text = StringFromKey("Villemstad_Store_21");
			link.l1 = StringFromKey("Villemstad_Store_22");
			link.l1.go = "Step_S2_4";
		break;
		case "Step_S2_4":
			dialog.text = StringFromKey("Villemstad_Store_23");
			link.l1 = StringFromKey("Villemstad_Store_24", pchar);
			link.l1.go = "Step_S2_5";
		break;
		case "Step_S2_5":
			dialog.text = StringFromKey("Villemstad_Store_25");
			link.l1 = StringFromKey("Villemstad_Store_26");
			link.l1.go = "Step_S2_6";
		break;
		case "Step_S2_6":
			dialog.text = StringFromKey("Villemstad_Store_27");
			link.l1 = StringFromKey("Villemstad_Store_28");
			link.l1.go = "exit";
			AddQuestRecord("Spa_Line_2_Inquisition", "3");
			AddQuestUserData("Spa_Line_2_Inquisition", "sSex", GetSexPhrase("ся", "ась"));
			pchar.questTemp.State.Store = 1;
			Pchar.quest.Inquisition_fightForJacow.win_condition.l1 = "location";
			Pchar.quest.Inquisition_fightForJacow.win_condition.l1.location = "Panama_houseSp1";
			Pchar.quest.Inquisition_fightForJacow.win_condition = "Inquisition_fightForJacow";
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
		case "Step_S2_7":
			dialog.text = StringFromKey("Villemstad_Store_29");
			link.l1 = StringFromKey("Villemstad_Store_30");
			link.l1.go = "exit";
			if (CheckCharacterItem(pchar, "Bible"))
			{
				link.l2 = StringFromKey("Villemstad_Store_31");
				link.l2.go = "Step_S2_8";
			}
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
		case "Step_S2_8":
			dialog.text = StringFromKey("Villemstad_Store_32");
			link.l1 = StringFromKey("Villemstad_Store_33");
			link.l1.go = "Step_S2_9";
			link.l2 = StringFromKey("Villemstad_Store_34");
			link.l2.go = "exit";
		break;
		case "Step_S2_9":
			dialog.text = StringFromKey("Villemstad_Store_35");
			link.l1 = StringFromKey("Villemstad_Store_36");
			link.l1.go = "Step_S2_10";
		break;
		case "Step_S2_10":
			dialog.text = StringFromKey("Villemstad_Store_37");
			link.l1 = StringFromKey("Villemstad_Store_38");
			link.l1.go = "Step_S2_11";
			TakeItemFromCharacter(pchar, "Bible");
		break;
		case "Step_S2_11":
			dialog.text = StringFromKey("Villemstad_Store_39");
			link.l1 = StringFromKey("Villemstad_Store_40");
			link.l1.go = "Step_S2_12";
			AddMoneyToCharacter(pchar, 1000000);
		break;
		case "Step_S2_12":
			dialog.text = StringFromKey("Villemstad_Store_41");
			link.l1 = StringFromKey("Villemstad_Store_42");
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
