// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SantoDomingo_Shipyard_3", RandPhraseSimple(
								StringFromKey("SantoDomingo_Shipyard_1"),
								StringFromKey("SantoDomingo_Shipyard_2"))),
						StringFromKey("SantoDomingo_Shipyard_4"),
						StringFromKey("SantoDomingo_Shipyard_5"),
						StringFromKey("SantoDomingo_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SantoDomingo_Shipyard_9", RandPhraseSimple(
								StringFromKey("SantoDomingo_Shipyard_7", pchar),
								StringFromKey("SantoDomingo_Shipyard_8"))),
						StringFromKey("SantoDomingo_Shipyard_10"),
						StringFromKey("SantoDomingo_Shipyard_11"),
						StringFromKey("SantoDomingo_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "Soukins_toSantoDomingo")
			{
				link.l1 = StringFromKey("SantoDomingo_Shipyard_13");
				link.l1.go = "PL_Q7_1";
			}
		break;
		//пиратка, квест №7
		case "PL_Q7_1":
			dialog.text = StringFromKey("SantoDomingo_Shipyard_14");
			link.l1 = StringFromKey("SantoDomingo_Shipyard_15");
			link.l1.go = "PL_Q7_2";
		break;
		case "PL_Q7_2":
			dialog.text = StringFromKey("SantoDomingo_Shipyard_16");
			link.l1 = StringFromKey("SantoDomingo_Shipyard_17");
			link.l1.go = "PL_Q7_3";
		break;
		case "PL_Q7_3":
			dialog.text = StringFromKey("SantoDomingo_Shipyard_18");
			link.l1 = StringFromKey("SantoDomingo_Shipyard_19");
			link.l1.go = "PL_Q7_4";
		break;
		case "PL_Q7_4":
			dialog.text = StringFromKey("SantoDomingo_Shipyard_20");
			link.l1 = StringFromKey("SantoDomingo_Shipyard_21");
			link.l1.go = "PL_Q7_5";
		break;
		case "PL_Q7_5":
			dialog.text = StringFromKey("SantoDomingo_Shipyard_22");
			link.l1 = StringFromKey("SantoDomingo_Shipyard_23");
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "Soukins_seekLeon";
			AddQuestRecord("Pir_Line_7_Soukins", "6");
			AddDialogExitQuestFunction("PQ7_LoginLeon");
			//HardCoffee ref Morgan's dialogue
			//QuestSetCurrentNode("Henry Morgan", "PL_Q7_LeonNotFound"); //нода, ничего не узнал
			pchar.QuestTemp.PirLine_quests_task = "PL_Q7_AboutLiney";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

