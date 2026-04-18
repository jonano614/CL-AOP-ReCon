// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("BasTer_Shipyard_3", RandPhraseSimple(
								StringFromKey("BasTer_Shipyard_1"),
								StringFromKey("BasTer_Shipyard_2"))),
						StringFromKey("BasTer_Shipyard_4"),
						StringFromKey("BasTer_Shipyard_5"),
						StringFromKey("BasTer_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("BasTer_Shipyard_9", RandPhraseSimple(
								StringFromKey("BasTer_Shipyard_7", pchar),
								StringFromKey("BasTer_Shipyard_8"))),
						StringFromKey("BasTer_Shipyard_10"),
						StringFromKey("BasTer_Shipyard_11"),
						StringFromKey("BasTer_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

