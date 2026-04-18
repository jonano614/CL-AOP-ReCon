// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_cemetery_3", RandPhraseSimple(
								StringFromKey("Tortuga_cemetery_1"),
								StringFromKey("Tortuga_cemetery_2"))),
						StringFromKey("Tortuga_cemetery_4", GetAddress_Form(NPChar)),
						StringFromKey("Tortuga_cemetery_5"),
						StringFromKey("Tortuga_cemetery_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_cemetery_9", RandPhraseSimple(
								StringFromKey("Tortuga_cemetery_7", pchar),
								StringFromKey("Tortuga_cemetery_8"))),
						StringFromKey("Tortuga_cemetery_10"),
						StringFromKey("Tortuga_cemetery_11"),
						StringFromKey("Tortuga_cemetery_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(NPChar, "talkedLSC") && CheckAttribute(pchar, "questTemp.LSC") && pchar.questTemp.LSC == "UndertakersSurveyLSC")
			{
				NPChar.talkedLSC = 1;
				link.l1 = StringFromKey("Tortuga_cemetery_13");
				link.l1.go = "TortugaCemeteryLSC_1";
			}
		break;

		case "TortugaCemeteryLSC_1":
			dialog.text = StringFromKey("Tortuga_cemetery_14");
			link.l1 = "...";
			link.l1.go = "TortugaCemeteryLSC_2";
		break;
		case "TortugaCemeteryLSC_2":
			dialog.text = StringFromKey("Tortuga_cemetery_15");
			link.l1 = StringFromKey("Tortuga_cemetery_16");
			link.l1.go = "exit";
			pchar.questTemp.UndertakersSurveyLSC = sti(pchar.questTemp.UndertakersSurveyLSC) + 1;
			AddDialogExitQuestFunction("CheckCountCemeteryLSC");
			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

