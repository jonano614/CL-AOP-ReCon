// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortRoyal_cemetery_3", RandPhraseSimple(
								StringFromKey("PortRoyal_cemetery_1"),
								StringFromKey("PortRoyal_cemetery_2"))),
						StringFromKey("PortRoyal_cemetery_4", GetAddress_Form(NPChar)),
						StringFromKey("PortRoyal_cemetery_5"),
						StringFromKey("PortRoyal_cemetery_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortRoyal_cemetery_9", RandPhraseSimple(
								StringFromKey("PortRoyal_cemetery_7", pchar),
								StringFromKey("PortRoyal_cemetery_8"))),
						StringFromKey("PortRoyal_cemetery_10"),
						StringFromKey("PortRoyal_cemetery_11"),
						StringFromKey("PortRoyal_cemetery_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(NPChar, "talkedLSC") && CheckAttribute(pchar, "questTemp.LSC") && pchar.questTemp.LSC == "UndertakersSurveyLSC")
			{
				NPChar.talkedLSC = 1;
				link.l1 = StringFromKey("PortRoyal_cemetery_13");
				link.l1.go = "PortRoyalCemeteryLSC_1";
			}
		break;

		case "PortRoyalCemeteryLSC_1":
			dialog.text = StringFromKey("PortRoyal_cemetery_14");
			link.l1 = "...";
			link.l1.go = "PortRoyalCemeteryLSC_2";
		break;
		case "PortRoyalCemeteryLSC_2":
			dialog.text = StringFromKey("PortRoyal_cemetery_15");
			link.l1 = StringFromKey("PortRoyal_cemetery_16");
			link.l1.go = "exit";
			pchar.questTemp.UndertakersSurveyLSC = sti(pchar.questTemp.UndertakersSurveyLSC) + 1;
			AddDialogExitQuestFunction("CheckCountCemeteryLSC");
			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

