// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("LaVega_Shipyard_3", RandPhraseSimple(
								StringFromKey("LaVega_Shipyard_1"),
								StringFromKey("LaVega_Shipyard_2"))),
						StringFromKey("LaVega_Shipyard_4"),
						StringFromKey("LaVega_Shipyard_5"),
						StringFromKey("LaVega_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("LaVega_Shipyard_9", RandPhraseSimple(
								StringFromKey("LaVega_Shipyard_7", pchar),
								StringFromKey("LaVega_Shipyard_8"))),
						StringFromKey("LaVega_Shipyard_10"),
						StringFromKey("LaVega_Shipyard_11"),
						StringFromKey("LaVega_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

