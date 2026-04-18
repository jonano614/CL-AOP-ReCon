// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SantoDomingo_Waitress_3", RandPhraseSimple(
								StringFromKey("SantoDomingo_Waitress_1", GetAddress_Form(NPChar)),
								StringFromKey("SantoDomingo_Waitress_2", GetAddress_Form(NPChar)))),
						StringFromKey("SantoDomingo_Waitress_4", pchar),
						StringFromKey("SantoDomingo_Waitress_5", pchar),
						StringFromKey("SantoDomingo_Waitress_6", GetAddress_Form(NPChar)), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SantoDomingo_Waitress_9", RandPhraseSimple(
								StringFromKey("SantoDomingo_Waitress_7", pchar),
								StringFromKey("SantoDomingo_Waitress_8"))),
						StringFromKey("SantoDomingo_Waitress_10"),
						StringFromKey("SantoDomingo_Waitress_11"),
						StringFromKey("SantoDomingo_Waitress_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
