// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Providencia_PortMan_3", RandPhraseSimple(
								StringFromKey("Providencia_PortMan_1"),
								StringFromKey("Providencia_PortMan_2", GetAddress_Form(NPChar)))),
						StringFromKey("Providencia_PortMan_4", GetAddress_Form(NPChar)),
						StringFromKey("Providencia_PortMan_5"),
						StringFromKey("Providencia_PortMan_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Providencia_PortMan_9", RandPhraseSimple(
								StringFromKey("Providencia_PortMan_7", pchar),
								StringFromKey("Providencia_PortMan_8"))),
						StringFromKey("Providencia_PortMan_10"),
						StringFromKey("Providencia_PortMan_11"),
						StringFromKey("Providencia_PortMan_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		/*if (pchar.questTemp.LSC == "PreparationsForDepartureLSC")
		{
			link.l1 = "Меня прислал к вам Эдвард Кольер по поводу стоянки кораблей.";
			link.l1.go = "PreparationsForDepartureLSC_1";
		}*/

		break;

		case "PreparationsForDepartureLSC":
			NextDiag.TempNode = "First time";
			NPChar.quest.meeting = "1";
			dialog.text = StringFromKey("Providencia_PortMan_13", GetAddress_Form(NPChar), GetFullName(npchar));
			link.l1 = StringFromKey("Providencia_PortMan_14");
			link.l1.go = "PreparationsForDepartureLSC_1";
		break;
		case "PreparationsForDepartureLSC_1":
			dialog.text = StringFromKey("Providencia_PortMan_15");
			link.l1 = StringFromKey("Providencia_PortMan_16");
			link.l1.go = "PreparationsForDepartureLSC_2";
		break;
		case "PreparationsForDepartureLSC_2":
			dialog.text = StringFromKey("Providencia_PortMan_17");
			link.l1 = StringFromKey("Providencia_PortMan_18");
			link.l1.go = "PreparationsForDepartureLSC_3";
		break;
		case "PreparationsForDepartureLSC_3":
			dialog.text = StringFromKey("Providencia_PortMan_19");
			link.l1 = StringFromKey("Providencia_PortMan_20");
			link.l1.go = "PreparationsForDepartureLSC_4";
		break;
		case "PreparationsForDepartureLSC_4":
			dialog.text = StringFromKey("Providencia_PortMan_21");
			link.l1 = StringFromKey("Providencia_PortMan_22");
			link.l1.go = "ShipStock_1";
			link.l2 = StringFromKey("Providencia_PortMan_23");
			link.l2.go = "First time";
			link.l3 = StringFromKey("Providencia_PortMan_24");
			link.l3.go = "exit";
			pchar.questTemp.LSC = "PreparationsForDepartureLSC";
			RemoveLandQuestMark_Main(npchar, "PreparationForISS");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
