// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Panama_Shipyard_3", RandPhraseSimple(
								StringFromKey("Panama_Shipyard_1"),
								StringFromKey("Panama_Shipyard_2"))),
						StringFromKey("Panama_Shipyard_4"),
						StringFromKey("Panama_Shipyard_5"),
						StringFromKey("Panama_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Panama_Shipyard_9", RandPhraseSimple(
								StringFromKey("Panama_Shipyard_7", pchar),
								StringFromKey("Panama_Shipyard_8"))),
						StringFromKey("Panama_Shipyard_10"),
						StringFromKey("Panama_Shipyard_11"),
						StringFromKey("Panama_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

