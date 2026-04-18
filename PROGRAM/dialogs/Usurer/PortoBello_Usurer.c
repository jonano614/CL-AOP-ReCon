// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortoBello_Usurer_3", RandPhraseSimple(
								StringFromKey("PortoBello_Usurer_1"),
								StringFromKey("PortoBello_Usurer_2"))),
						StringFromKey("PortoBello_Usurer_4"),
						StringFromKey("PortoBello_Usurer_5"),
						StringFromKey("PortoBello_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortoBello_Usurer_9", RandPhraseSimple(
								StringFromKey("PortoBello_Usurer_7", pchar),
								StringFromKey("PortoBello_Usurer_8"))),
						StringFromKey("PortoBello_Usurer_10"),
						StringFromKey("PortoBello_Usurer_11"),
						StringFromKey("PortoBello_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
