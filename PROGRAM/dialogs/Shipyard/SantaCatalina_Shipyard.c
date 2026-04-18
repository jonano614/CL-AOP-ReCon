// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SantaCatalina_Shipyard_3", RandPhraseSimple(
								StringFromKey("SantaCatalina_Shipyard_1"),
								StringFromKey("SantaCatalina_Shipyard_2"))),
						StringFromKey("SantaCatalina_Shipyard_4"),
						StringFromKey("SantaCatalina_Shipyard_5"),
						StringFromKey("SantaCatalina_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SantaCatalina_Shipyard_9", RandPhraseSimple(
								StringFromKey("SantaCatalina_Shipyard_7", pchar),
								StringFromKey("SantaCatalina_Shipyard_8"))),
						StringFromKey("SantaCatalina_Shipyard_10"),
						StringFromKey("SantaCatalina_Shipyard_11"),
						StringFromKey("SantaCatalina_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

