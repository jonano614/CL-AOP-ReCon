// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Villemstad_Shipyard_3", RandPhraseSimple(
								StringFromKey("Villemstad_Shipyard_1"),
								StringFromKey("Villemstad_Shipyard_2"))),
						StringFromKey("Villemstad_Shipyard_4"),
						StringFromKey("Villemstad_Shipyard_5"),
						StringFromKey("Villemstad_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Villemstad_Shipyard_9", RandPhraseSimple(
								StringFromKey("Villemstad_Shipyard_7", pchar),
								StringFromKey("Villemstad_Shipyard_8"))),
						StringFromKey("Villemstad_Shipyard_10"),
						StringFromKey("Villemstad_Shipyard_11"),
						StringFromKey("Villemstad_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

