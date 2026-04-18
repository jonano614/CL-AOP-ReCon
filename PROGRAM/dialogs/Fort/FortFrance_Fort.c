// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortFrance_Fort_3", RandPhraseSimple(
								StringFromKey("FortFrance_Fort_1"),
								StringFromKey("FortFrance_Fort_2", GetAddress_Form(NPChar)))),
						StringFromKey("FortFrance_Fort_4", GetAddress_Form(NPChar)),
						StringFromKey("FortFrance_Fort_5"),
						StringFromKey("FortFrance_Fort_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortFrance_Fort_9", RandPhraseSimple(
								StringFromKey("FortFrance_Fort_7", pchar),
								StringFromKey("FortFrance_Fort_8"))),
						StringFromKey("FortFrance_Fort_10"),
						StringFromKey("FortFrance_Fort_11"),
						StringFromKey("FortFrance_Fort_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


