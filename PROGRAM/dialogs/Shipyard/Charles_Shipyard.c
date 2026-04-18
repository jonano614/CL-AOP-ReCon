// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Charles_Shipyard_3", RandPhraseSimple(
								StringFromKey("Charles_Shipyard_1"),
								StringFromKey("Charles_Shipyard_2"))),
						StringFromKey("Charles_Shipyard_4"),
						StringFromKey("Charles_Shipyard_5"),
						StringFromKey("Charles_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Charles_Shipyard_9", RandPhraseSimple(
								StringFromKey("Charles_Shipyard_7", pchar),
								StringFromKey("Charles_Shipyard_8"))),
						StringFromKey("Charles_Shipyard_10"),
						StringFromKey("Charles_Shipyard_11"),
						StringFromKey("Charles_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

