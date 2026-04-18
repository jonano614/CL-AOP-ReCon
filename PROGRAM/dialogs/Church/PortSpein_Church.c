// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortSpein_Church_3", RandPhraseSimple(
								StringFromKey("PortSpein_Church_1", pchar),
								StringFromKey("PortSpein_Church_2"))),
						StringFromKey("PortSpein_Church_4", pchar),
						StringFromKey("PortSpein_Church_5", pchar),
						StringFromKey("PortSpein_Church_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortSpein_Church_9", RandPhraseSimple(
								StringFromKey("PortSpein_Church_7", pchar),
								StringFromKey("PortSpein_Church_8"))),
						StringFromKey("PortSpein_Church_10"),
						StringFromKey("PortSpein_Church_11"),
						StringFromKey("PortSpein_Church_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}



