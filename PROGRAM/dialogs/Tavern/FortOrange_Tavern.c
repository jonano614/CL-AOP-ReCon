// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortOrange_Tavern_3", RandPhraseSimple(
								StringFromKey("FortOrange_Tavern_1"),
								StringFromKey("FortOrange_Tavern_2", GetAddress_Form(NPChar)))),
						StringFromKey("FortOrange_Tavern_4", GetAddress_Form(NPChar)),
						StringFromKey("FortOrange_Tavern_5"),
						StringFromKey("FortOrange_Tavern_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortOrange_Tavern_9", RandPhraseSimple(
								StringFromKey("FortOrange_Tavern_7", pchar),
								StringFromKey("FortOrange_Tavern_8"))),
						StringFromKey("FortOrange_Tavern_10"),
						StringFromKey("FortOrange_Tavern_11"),
						StringFromKey("FortOrange_Tavern_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
			{
				link.l1 = StringFromKey("FortOrange_Tavern_13");
				link.l1.go = "Jamaica_ratF_1";
			}
		break;

		case "DefenceOrange": //Голландская линейка, квест №4, защита форта Оранж.
			dialog.text = StringFromKey("FortOrange_Tavern_14");
			link.l2 = StringFromKey("FortOrange_Tavern_15");
			link.l2.go = "Step_H4_1";
		break;

		case "Step_H4_1":
			dialog.text = StringFromKey("FortOrange_Tavern_16", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("FortOrange_Tavern_17");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Jamaica_ratF_1":
			dialog.text = StringFromKey("FortOrange_Tavern_18");
			link.l1 = StringFromKey("FortOrange_Tavern_19");
			link.l1.go = "Jamaica_ratF_2";
		break;

		case "Jamaica_ratF_2":
			dialog.text = StringFromKey("FortOrange_Tavern_20");
			link.l1 = StringFromKey("FortOrange_Tavern_21");
			link.l1.go = "Jamaica_ratF_3";
		break;

		case "Jamaica_ratF_3":
			dialog.text = StringFromKey("FortOrange_Tavern_22", pchar);
			link.l1 = StringFromKey("FortOrange_Tavern_23");
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_4");
			pchar.questTemp.Slavetrader = "FindRatJamaica_H";

			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			RemoveLandQuestmark_Main(CharacterFromID("PortRoyal_tavernkeeper"), "Slavetrader");
			RemoveLandQuestmark_Main(CharacterFromID("PortRoyal_PortMan"), "Slavetrader");
			AddLandQuestmarkToFantoms_Main("habitue", "Slavetrader", "Slavetrader_FindRat_Habitues_QuestMarkCondition");
		break;

		case "OutFromMineLSC":
			dialog.text = StringFromKey("FortOrange_Tavern_24");
			link.l1 = StringFromKey("FortOrange_Tavern_25");
			link.l1.go = "OutFromMineLSC_1";
		break;
		case "OutFromMineLSC_1":
			//бомжам не нравится
			ref rSlave;
			for (int iSlave = 2; iSlave < 12; iSlave++)
			{
				rSlave = CharacterFromID("slavesLSC"+iSlave);
				if (rSlave.actions.idle.i1 == "Ground_sitting")
				{
					LAi_type_actor_Reset(rSlave);
					LAi_tmpl_ani_PlayAnimation(rSlave, "Ground_StandUp", -1);
					LAi_SetDefaultStayAnimation(rSlave);
				}
			}
			dialog.text = StringFromKey("FortOrange_Tavern_26");
			link.l1 = StringFromKey("FortOrange_Tavern_27");
			link.l1.go = "OutFromMineLSC_2";
		break;
		case "OutFromMineLSC_2":
			dialog.text = StringFromKey("FortOrange_Tavern_28");
			link.l1 = StringFromKey("FortOrange_Tavern_29");
			link.l1.go = "OutFromMineLSC_3";
		break;
		case "OutFromMineLSC_3":
			dialog.text = StringFromKey("FortOrange_Tavern_30");
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("OutFromMineLSC_12");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
