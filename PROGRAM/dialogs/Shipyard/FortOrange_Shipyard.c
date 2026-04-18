// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortOrange_Shipyard_3", RandPhraseSimple(
								StringFromKey("FortOrange_Shipyard_1"),
								StringFromKey("FortOrange_Shipyard_2"))),
						StringFromKey("FortOrange_Shipyard_4"),
						StringFromKey("FortOrange_Shipyard_5"),
						StringFromKey("FortOrange_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortOrange_Shipyard_9", RandPhraseSimple(
								StringFromKey("FortOrange_Shipyard_7", pchar),
								StringFromKey("FortOrange_Shipyard_8"))),
						StringFromKey("FortOrange_Shipyard_10"),
						StringFromKey("FortOrange_Shipyard_11"),
						StringFromKey("FortOrange_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

