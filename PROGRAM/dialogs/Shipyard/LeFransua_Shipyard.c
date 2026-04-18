// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("LeFransua_Shipyard_3", RandPhraseSimple(
								StringFromKey("LeFransua_Shipyard_1"),
								StringFromKey("LeFransua_Shipyard_2"))),
						StringFromKey("LeFransua_Shipyard_4"),
						StringFromKey("LeFransua_Shipyard_5"),
						StringFromKey("LeFransua_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("LeFransua_Shipyard_9", RandPhraseSimple(
								StringFromKey("LeFransua_Shipyard_7", pchar),
								StringFromKey("LeFransua_Shipyard_8"))),
						StringFromKey("LeFransua_Shipyard_10"),
						StringFromKey("LeFransua_Shipyard_11"),
						StringFromKey("LeFransua_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

