// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SanJuan_Shipyard_3", RandPhraseSimple(
								StringFromKey("SanJuan_Shipyard_1"),
								StringFromKey("SanJuan_Shipyard_2"))),
						StringFromKey("SanJuan_Shipyard_4"),
						StringFromKey("SanJuan_Shipyard_5"),
						StringFromKey("SanJuan_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SanJuan_Shipyard_9", RandPhraseSimple(
								StringFromKey("SanJuan_Shipyard_7", pchar),
								StringFromKey("SanJuan_Shipyard_8"))),
						StringFromKey("SanJuan_Shipyard_10"),
						StringFromKey("SanJuan_Shipyard_11"),
						StringFromKey("SanJuan_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

