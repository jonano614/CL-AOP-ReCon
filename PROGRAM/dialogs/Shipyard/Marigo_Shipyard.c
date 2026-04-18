// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Marigo_Shipyard_3", RandPhraseSimple(
								StringFromKey("Marigo_Shipyard_1"),
								StringFromKey("Marigo_Shipyard_2"))),
						StringFromKey("Marigo_Shipyard_4"),
						StringFromKey("Marigo_Shipyard_5"),
						StringFromKey("Marigo_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Marigo_Shipyard_9", RandPhraseSimple(
								StringFromKey("Marigo_Shipyard_7", pchar),
								StringFromKey("Marigo_Shipyard_8"))),
						StringFromKey("Marigo_Shipyard_10"),
						StringFromKey("Marigo_Shipyard_11"),
						StringFromKey("Marigo_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

