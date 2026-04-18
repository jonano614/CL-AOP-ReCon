// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Bridgetown_Tavern_3", RandPhraseSimple(
								StringFromKey("Bridgetown_Tavern_1"),
								StringFromKey("Bridgetown_Tavern_2", GetAddress_Form(NPChar)))),
						StringFromKey("Bridgetown_Tavern_4", GetAddress_Form(NPChar)),
						StringFromKey("Bridgetown_Tavern_5"),
						StringFromKey("Bridgetown_Tavern_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Bridgetown_Tavern_9", RandPhraseSimple(
								StringFromKey("Bridgetown_Tavern_7", pchar),
								StringFromKey("Bridgetown_Tavern_8"))),
						StringFromKey("Bridgetown_Tavern_10"),
						StringFromKey("Bridgetown_Tavern_11"),
						StringFromKey("Bridgetown_Tavern_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
