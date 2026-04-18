// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Beliz_Shipyard_3", RandPhraseSimple(
								StringFromKey("Beliz_Shipyard_1"),
								StringFromKey("Beliz_Shipyard_2"))),
						StringFromKey("Beliz_Shipyard_4"),
						StringFromKey("Beliz_Shipyard_5"),
						StringFromKey("Beliz_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Beliz_Shipyard_9", RandPhraseSimple(
								StringFromKey("Beliz_Shipyard_7", pchar),
								StringFromKey("Beliz_Shipyard_8"))),
						StringFromKey("Beliz_Shipyard_10"),
						StringFromKey("Beliz_Shipyard_11"),
						StringFromKey("Beliz_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

