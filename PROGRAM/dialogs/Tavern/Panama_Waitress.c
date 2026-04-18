// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Panama_Waitress_3", RandPhraseSimple(
								StringFromKey("Panama_Waitress_1", GetAddress_Form(NPChar)),
								StringFromKey("Panama_Waitress_2", GetAddress_Form(NPChar)))),
						StringFromKey("Panama_Waitress_4", pchar),
						StringFromKey("Panama_Waitress_5", pchar),
						StringFromKey("Panama_Waitress_6", GetAddress_Form(NPChar)), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Panama_Waitress_9", RandPhraseSimple(
								StringFromKey("Panama_Waitress_7", pchar),
								StringFromKey("Panama_Waitress_8"))),
						StringFromKey("Panama_Waitress_10"),
						StringFromKey("Panama_Waitress_11"),
						StringFromKey("Panama_Waitress_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
