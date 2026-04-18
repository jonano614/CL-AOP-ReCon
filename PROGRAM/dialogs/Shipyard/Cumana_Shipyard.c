// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Cumana_Shipyard_3", RandPhraseSimple(
								StringFromKey("Cumana_Shipyard_1"),
								StringFromKey("Cumana_Shipyard_2"))),
						StringFromKey("Cumana_Shipyard_4"),
						StringFromKey("Cumana_Shipyard_5"),
						StringFromKey("Cumana_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Cumana_Shipyard_9", RandPhraseSimple(
								StringFromKey("Cumana_Shipyard_7", pchar),
								StringFromKey("Cumana_Shipyard_8"))),
						StringFromKey("Cumana_Shipyard_10"),
						StringFromKey("Cumana_Shipyard_11"),
						StringFromKey("Cumana_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

