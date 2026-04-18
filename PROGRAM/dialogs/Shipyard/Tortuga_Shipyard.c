// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_Shipyard_3", RandPhraseSimple(
								StringFromKey("Tortuga_Shipyard_1"),
								StringFromKey("Tortuga_Shipyard_2"))),
						StringFromKey("Tortuga_Shipyard_4"),
						StringFromKey("Tortuga_Shipyard_5"),
						StringFromKey("Tortuga_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_Shipyard_9", RandPhraseSimple(
								StringFromKey("Tortuga_Shipyard_7", pchar),
								StringFromKey("Tortuga_Shipyard_8"))),
						StringFromKey("Tortuga_Shipyard_10"),
						StringFromKey("Tortuga_Shipyard_11"),
						StringFromKey("Tortuga_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Проверяем поле состояния квестов.
			switch (pchar.questTemp.State)
			{
				case "WormEnglPlans_WormPicarder": //Голландская линейка, квест №3. узнаем о Пеьере Пикардийце.
					link.l2 = StringFromKey("Tortuga_Shipyard_13", pchar);
					link.l2.go = "Step_H3_1";
				break;

			}
		// <== Проверяем поле состояния квестов.
		break;
		case "Step_H3_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_Shipyard_14", pchar),
						StringFromKey("Tortuga_Shipyard_15", UpperFirst(GetAddress_Form(NPChar))),
						StringFromKey("Tortuga_Shipyard_16"),
						StringFromKey("Tortuga_Shipyard_17"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_Shipyard_18", pchar),
						StringFromKey("Tortuga_Shipyard_19"),
						StringFromKey("Tortuga_Shipyard_20", pchar),
						StringFromKey("Tortuga_Shipyard_21"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H3_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_H3_2":
			dialog.text = StringFromKey("Tortuga_Shipyard_22");
			link.l1 = StringFromKey("Tortuga_Shipyard_23");
			link.l1.go = "exit";
			pchar.questTemp.Hol_Line_AboutWorm.Shipyard = true;
			AddQuestRecord("Hol_Line_3_WormEnglishPlans", "9");
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

