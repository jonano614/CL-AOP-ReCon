// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortFrance_Waitress_3", RandPhraseSimple(
								StringFromKey("FortFrance_Waitress_1", GetAddress_Form(NPChar)),
								StringFromKey("FortFrance_Waitress_2", GetAddress_Form(NPChar)))),
						StringFromKey("FortFrance_Waitress_4", pchar),
						StringFromKey("FortFrance_Waitress_5", pchar),
						StringFromKey("FortFrance_Waitress_6", GetAddress_Form(NPChar)), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortFrance_Waitress_9", RandPhraseSimple(
								StringFromKey("FortFrance_Waitress_7", pchar),
								StringFromKey("FortFrance_Waitress_8"))),
						StringFromKey("FortFrance_Waitress_10"),
						StringFromKey("FortFrance_Waitress_11"),
						StringFromKey("FortFrance_Waitress_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
