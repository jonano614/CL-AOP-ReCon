// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortOrange_Waitress_3", RandPhraseSimple(
								StringFromKey("FortOrange_Waitress_1", GetAddress_Form(NPChar)),
								StringFromKey("FortOrange_Waitress_2", GetAddress_Form(NPChar)))),
						StringFromKey("FortOrange_Waitress_4", pchar),
						StringFromKey("FortOrange_Waitress_5", pchar),
						StringFromKey("FortOrange_Waitress_6", GetAddress_Form(NPChar)), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortOrange_Waitress_9", RandPhraseSimple(
								StringFromKey("FortOrange_Waitress_7", pchar),
								StringFromKey("FortOrange_Waitress_8"))),
						StringFromKey("FortOrange_Waitress_10"),
						StringFromKey("FortOrange_Waitress_11"),
						StringFromKey("FortOrange_Waitress_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_W")
			{
				link.l1 = StringFromKey("FortOrange_Waitress_13");
				link.l1.go = "Jamaica_ratW_1";
			}

			if (pchar.questTemp.Slavetrader == "FindRatJamaica_WP")
			{
				if (CheckCharacterItem(pchar, "jewelry15"))
				{
					link.l1 = StringFromKey("FortOrange_Waitress_14");
					link.l1.go = "Jamaica_ratW_5";
				}
				else
				{
					link.l1 = StringFromKey("FortOrange_Waitress_15");
					link.l1.go = "exit";
				}
			}

		break;

		case "DefenceOrange": //Голландская линейка, квест №4, защита форта Оранж.
			dialog.text = StringFromKey("FortOrange_Waitress_16", GetAddress_Form(NPChar));
			link.l2 = StringFromKey("FortOrange_Waitress_17");
			link.l2.go = "Step_H4_1";
		break;

		case "Step_H4_1":
			dialog.text = StringFromKey("FortOrange_Waitress_18", pchar);
			link.l1 = StringFromKey("FortOrange_Waitress_19", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Jamaica_ratW_1":
			dialog.text = StringFromKey("FortOrange_Waitress_20");
			link.l1 = StringFromKey("FortOrange_Waitress_21");
			link.l1.go = "Jamaica_ratW_2";
		break;

		case "Jamaica_ratW_2":
			dialog.text = StringFromKey("FortOrange_Waitress_22", pchar);
			link.l1 = StringFromKey("FortOrange_Waitress_23");
			link.l1.go = "Jamaica_ratW_3";
		break;

		case "Jamaica_ratW_3":
			dialog.text = StringFromKey("FortOrange_Waitress_24");
			link.l1 = StringFromKey("FortOrange_Waitress_25");
			link.l1.go = "Jamaica_ratW_4";
		break;

		case "Jamaica_ratW_4":
			dialog.text = StringFromKey("FortOrange_Waitress_26", pchar);
			link.l1 = StringFromKey("FortOrange_Waitress_27");
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_5");
			pchar.questTemp.Slavetrader = "FindRatJamaica_WP";
		break;

		case "Jamaica_ratW_5":
			dialog.text = StringFromKey("FortOrange_Waitress_28");
			link.l1 = StringFromKey("FortOrange_Waitress_29");
			link.l1.go = "Jamaica_ratW_6";
			RemoveItems(PChar, "jewelry15", 1);
		break;

		case "Jamaica_ratW_6":
			dialog.text = StringFromKey("FortOrange_Waitress_30", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("FortOrange_Waitress_31", pchar);
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_6");
			pchar.questTemp.Slavetrader = "FindRatHavana";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			AddLandQuestmark_Main(CharacterFromID("Havana_tavernkeeper"), "Slavetrader");
			AddLandQuestmark_Main(CharacterFromID("Havana_PortMan"), "Slavetrader");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
