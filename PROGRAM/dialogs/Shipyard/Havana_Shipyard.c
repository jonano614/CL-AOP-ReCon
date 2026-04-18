// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Havana_Shipyard_3", RandPhraseSimple(
								StringFromKey("Havana_Shipyard_1"),
								StringFromKey("Havana_Shipyard_2"))),
						StringFromKey("Havana_Shipyard_4"),
						StringFromKey("Havana_Shipyard_5"),
						StringFromKey("Havana_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Havana_Shipyard_9", RandPhraseSimple(
								StringFromKey("Havana_Shipyard_7", pchar),
								StringFromKey("Havana_Shipyard_8"))),
						StringFromKey("Havana_Shipyard_10"),
						StringFromKey("Havana_Shipyard_11"),
						StringFromKey("Havana_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

