// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = StringFromKey("PortRoyal_Prison_1");
			link.l1 = StringFromKey("PortRoyal_Prison_2", pchar);
			link.l1.go = "Exit";
			if (pchar.questTemp.State == "MorrisWillams_ArrestedToPrison")   // разговор по шестому квесту англ.линейки
			{
				link.l2 = StringFromKey("PortRoyal_Prison_3");
				link.l2.go = "Step_E6_1";
			}
			if (pchar.questTemp.State == "SaveFromMorgan_toPrison")   // испанка, квест №1
			{
				link.l2 = StringFromKey("PortRoyal_Prison_4");
				link.l2.go = "Step_S1_1";
			}
		break;

		case "Step_E6_1":
			dialog.text = StringFromKey("PortRoyal_Prison_5");
			link.l1 = StringFromKey("PortRoyal_Prison_6");
			link.l1.go = "Step_E6_2";
		break;
		case "Step_E6_2":
			dialog.text = StringFromKey("PortRoyal_Prison_7");
			link.l1 = StringFromKey("PortRoyal_Prison_8");
			link.l1.go = "Step_E6_3";
		break;
		case "Step_E6_3":
			dialog.text = StringFromKey("PortRoyal_Prison_9");
			link.l1 = StringFromKey("PortRoyal_Prison_10");
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			pchar.questTemp.State = "MorrisWillams_ArrestedToModiford";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "16");
			RemoveLandQuestmarkToFantoms_Main("JailOff", "Eng_Line");
			AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
		break;

		case "Step_S1_1":
			dialog.text = StringFromKey("PortRoyal_Prison_11");
			link.l1 = StringFromKey("PortRoyal_Prison_12");
			link.l1.go = "Step_S1_2";
		break;
		case "Step_S1_2":
			dialog.text = StringFromKey("PortRoyal_Prison_13");
			link.l1 = StringFromKey("PortRoyal_Prison_14");
			link.l1.go = "Step_S1_3";
		break;
		case "Step_S1_3":
			dialog.text = StringFromKey("PortRoyal_Prison_15", pchar);
			link.l1 = StringFromKey("PortRoyal_Prison_16");
			link.l1.go = "fight";
			RemoveLandQuestmarkToFantoms_Main("JailOff", "Spa_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
