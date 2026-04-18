// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortSpein_Mayor_3", RandPhraseSimple(
								StringFromKey("PortSpein_Mayor_1"),
								StringFromKey("PortSpein_Mayor_2"))),
						StringFromKey("PortSpein_Mayor_4"),
						StringFromKey("PortSpein_Mayor_5"),
						StringFromKey("PortSpein_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortSpein_Mayor_9", RandPhraseSimple(
								StringFromKey("PortSpein_Mayor_7", pchar),
								StringFromKey("PortSpein_Mayor_8"))),
						StringFromKey("PortSpein_Mayor_10"),
						StringFromKey("PortSpein_Mayor_11"),
						StringFromKey("PortSpein_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
