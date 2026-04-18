// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Bridgetown_Shipyard_3", RandPhraseSimple(
								StringFromKey("Bridgetown_Shipyard_1"),
								StringFromKey("Bridgetown_Shipyard_2"))),
						StringFromKey("Bridgetown_Shipyard_4"),
						StringFromKey("Bridgetown_Shipyard_5"),
						StringFromKey("Bridgetown_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Bridgetown_Shipyard_9", RandPhraseSimple(
								StringFromKey("Bridgetown_Shipyard_7", pchar),
								StringFromKey("Bridgetown_Shipyard_8"))),
						StringFromKey("Bridgetown_Shipyard_10"),
						StringFromKey("Bridgetown_Shipyard_11"),
						StringFromKey("Bridgetown_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

