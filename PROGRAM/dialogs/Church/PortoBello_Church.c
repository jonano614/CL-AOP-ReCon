// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortoBello_Church_3", RandPhraseSimple(
								StringFromKey("PortoBello_Church_1", pchar),
								StringFromKey("PortoBello_Church_2"))),
						StringFromKey("PortoBello_Church_4", pchar),
						StringFromKey("PortoBello_Church_5", pchar),
						StringFromKey("PortoBello_Church_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortoBello_Church_9", RandPhraseSimple(
								StringFromKey("PortoBello_Church_7", pchar),
								StringFromKey("PortoBello_Church_8"))),
						StringFromKey("PortoBello_Church_10"),
						StringFromKey("PortoBello_Church_11"),
						StringFromKey("PortoBello_Church_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}



