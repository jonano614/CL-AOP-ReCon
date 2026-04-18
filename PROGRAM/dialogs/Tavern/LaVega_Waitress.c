// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("LaVega_Waitress_3", RandPhraseSimple(
								StringFromKey("LaVega_Waitress_1", GetAddress_Form(NPChar)),
								StringFromKey("LaVega_Waitress_2", GetAddress_Form(NPChar)))),
						StringFromKey("LaVega_Waitress_4", pchar),
						StringFromKey("LaVega_Waitress_5", pchar),
						StringFromKey("LaVega_Waitress_6", GetAddress_Form(NPChar)), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("LaVega_Waitress_9", RandPhraseSimple(
								StringFromKey("LaVega_Waitress_7", pchar),
								StringFromKey("LaVega_Waitress_8"))),
						StringFromKey("LaVega_Waitress_10"),
						StringFromKey("LaVega_Waitress_11"),
						StringFromKey("LaVega_Waitress_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
