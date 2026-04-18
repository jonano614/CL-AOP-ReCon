// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Santiago_Church_3", RandPhraseSimple(
								StringFromKey("Santiago_Church_1", pchar),
								StringFromKey("Santiago_Church_2"))),
						StringFromKey("Santiago_Church_4", pchar),
						StringFromKey("Santiago_Church_5", pchar),
						StringFromKey("Santiago_Church_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Santiago_Church_9", RandPhraseSimple(
								StringFromKey("Santiago_Church_7", pchar),
								StringFromKey("Santiago_Church_8"))),
						StringFromKey("Santiago_Church_10"),
						StringFromKey("Santiago_Church_11"),
						StringFromKey("Santiago_Church_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Inquisition_toDeSouza")
			{
				link.l1 = StringFromKey("Santiago_Church_13");
				link.l1.go = "Step_S2_1";
			}
			if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
			{
				link.l1 = StringFromKey("Santiago_Church_14");
				link.l1.go = "Step_F7_1";
			}
		break;
		case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Santiago_Church_15", pchar),
						StringFromKey("Santiago_Church_16", pchar),
						StringFromKey("Santiago_Church_17"),
						StringFromKey("Santiago_Church_18"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Santiago_Church_19"),
						StringFromKey("Santiago_Church_20", pchar),
						StringFromKey("Santiago_Church_21", pchar),
						StringFromKey("Santiago_Church_22"), npchar, Dialog.CurrentNode);
			link.l1.go = "Step_S2_2";
		break;
		case "Step_S2_2":
			dialog.text = StringFromKey("Santiago_Church_23");
			link.l1 = StringFromKey("Santiago_Church_24");
			link.l1.go = "Step_S2_3";
		break;
		case "Step_S2_3":
			dialog.text = StringFromKey("Santiago_Church_25");
			link.l1 = StringFromKey("Santiago_Church_26");
			link.l1.go = "Step_S2_4";
		break;
		case "Step_S2_4":
			dialog.text = StringFromKey("Santiago_Church_27", pchar);
			link.l1 = StringFromKey("Santiago_Church_28");
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;

		case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Santiago_Church_29", pchar),
						StringFromKey("Santiago_Church_30", pchar),
						StringFromKey("Santiago_Church_31", pchar),
						StringFromKey("Santiago_Church_32"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Santiago_Church_33"),
						StringFromKey("Santiago_Church_34"),
						StringFromKey("Santiago_Church_35"),
						StringFromKey("Santiago_Church_36"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

