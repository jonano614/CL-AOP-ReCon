// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Caracas_Shipyard_3", RandPhraseSimple(
								StringFromKey("Caracas_Shipyard_1"),
								StringFromKey("Caracas_Shipyard_2"))),
						StringFromKey("Caracas_Shipyard_4"),
						StringFromKey("Caracas_Shipyard_5"),
						StringFromKey("Caracas_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Caracas_Shipyard_9", RandPhraseSimple(
								StringFromKey("Caracas_Shipyard_7", pchar),
								StringFromKey("Caracas_Shipyard_8"))),
						StringFromKey("Caracas_Shipyard_10"),
						StringFromKey("Caracas_Shipyard_11"),
						StringFromKey("Caracas_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
