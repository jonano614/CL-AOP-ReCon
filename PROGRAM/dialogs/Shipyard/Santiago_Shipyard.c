// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Santiago_Shipyard_3", RandPhraseSimple(
								StringFromKey("Santiago_Shipyard_1"),
								StringFromKey("Santiago_Shipyard_2"))),
						StringFromKey("Santiago_Shipyard_4"),
						StringFromKey("Santiago_Shipyard_5"),
						StringFromKey("Santiago_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Santiago_Shipyard_9", RandPhraseSimple(
								StringFromKey("Santiago_Shipyard_7", pchar),
								StringFromKey("Santiago_Shipyard_8"))),
						StringFromKey("Santiago_Shipyard_10"),
						StringFromKey("Santiago_Shipyard_11"),
						StringFromKey("Santiago_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

