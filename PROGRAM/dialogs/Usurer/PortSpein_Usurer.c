// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortSpein_Usurer_3", RandPhraseSimple(
								StringFromKey("PortSpein_Usurer_1"),
								StringFromKey("PortSpein_Usurer_2"))),
						StringFromKey("PortSpein_Usurer_4"),
						StringFromKey("PortSpein_Usurer_5"),
						StringFromKey("PortSpein_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortSpein_Usurer_9", RandPhraseSimple(
								StringFromKey("PortSpein_Usurer_7", pchar),
								StringFromKey("PortSpein_Usurer_8"))),
						StringFromKey("PortSpein_Usurer_10"),
						StringFromKey("PortSpein_Usurer_11"),
						StringFromKey("PortSpein_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
