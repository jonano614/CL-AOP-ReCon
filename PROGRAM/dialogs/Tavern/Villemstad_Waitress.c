// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Villemstad_Waitress_3", RandPhraseSimple(
								StringFromKey("Villemstad_Waitress_1", GetAddress_Form(NPChar)),
								StringFromKey("Villemstad_Waitress_2", GetAddress_Form(NPChar)))),
						StringFromKey("Villemstad_Waitress_4", pchar),
						StringFromKey("Villemstad_Waitress_5", pchar),
						StringFromKey("Villemstad_Waitress_6", GetAddress_Form(NPChar)), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Villemstad_Waitress_9", RandPhraseSimple(
								StringFromKey("Villemstad_Waitress_7", pchar),
								StringFromKey("Villemstad_Waitress_8"))),
						StringFromKey("Villemstad_Waitress_10"),
						StringFromKey("Villemstad_Waitress_11"),
						StringFromKey("Villemstad_Waitress_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//==> проверяем поле состояния квестов
			if (CheckAttribute(pchar, "questTemp.State.Usurer"))
			{
				dialog.text = StringFromKey("Villemstad_Waitress_13");
				link.l1 = StringFromKey("Villemstad_Waitress_14", pchar);
				link.l1.go = "Step_S2_1";
			}
		//<== проверяем поле состояния квестов
		break;
		//*************************** Квест №2 испанки, задание Инквизиции ***************************
		case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Villemstad_Waitress_15"),
						StringFromKey("Villemstad_Waitress_16"),
						StringFromKey("Villemstad_Waitress_17"),
						StringFromKey("Villemstad_Waitress_18", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Villemstad_Waitress_19"),
						StringFromKey("Villemstad_Waitress_20"),
						StringFromKey("Villemstad_Waitress_21"),
						StringFromKey("Villemstad_Waitress_22", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S2_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_S2_2":
			dialog.text = StringFromKey("Villemstad_Waitress_23");
			link.l1 = StringFromKey("Villemstad_Waitress_24");
			link.l1.go = "Step_S2_3";
		break;
		case "Step_S2_3":
			dialog.text = StringFromKey("Villemstad_Waitress_25");
			link.l1 = StringFromKey("Villemstad_Waitress_26");
			link.l1.go = "Step_S2_4";
		break;
		case "Step_S2_4":
			dialog.text = StringFromKey("Villemstad_Waitress_27");
			link.l1 = StringFromKey("Villemstad_Waitress_28");
			link.l1.go = "exit";
			AddQuestRecord("Spa_Line_2_Inquisition", "6");
			Pchar.quest.Inquisition_AttackLugger.win_condition.l1 = "location";
			Pchar.quest.Inquisition_AttackLugger.win_condition.l1.location = "Jamaica";
			Pchar.quest.Inquisition_AttackLugger.win_condition = "Inquisition_AttackLugger";
			SetTimerCondition("Inquisition_LuggerTimeOver", 0, 0, 20, false);
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
