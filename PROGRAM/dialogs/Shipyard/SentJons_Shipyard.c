// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SentJons_Shipyard_3", RandPhraseSimple(
								StringFromKey("SentJons_Shipyard_1"),
								StringFromKey("SentJons_Shipyard_2"))),
						StringFromKey("SentJons_Shipyard_4"),
						StringFromKey("SentJons_Shipyard_5"),
						StringFromKey("SentJons_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SentJons_Shipyard_9", RandPhraseSimple(
								StringFromKey("SentJons_Shipyard_7", pchar),
								StringFromKey("SentJons_Shipyard_8"))),
						StringFromKey("SentJons_Shipyard_10"),
						StringFromKey("SentJons_Shipyard_11"),
						StringFromKey("SentJons_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

