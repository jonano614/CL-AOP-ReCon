// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Maracaibo_Waitress_3", RandPhraseSimple(
								StringFromKey("Maracaibo_Waitress_1", GetAddress_Form(NPChar)),
								StringFromKey("Maracaibo_Waitress_2", GetAddress_Form(NPChar)))),
						StringFromKey("Maracaibo_Waitress_4", pchar),
						StringFromKey("Maracaibo_Waitress_5", pchar),
						StringFromKey("Maracaibo_Waitress_6", GetAddress_Form(NPChar)), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Maracaibo_Waitress_9", RandPhraseSimple(
								StringFromKey("Maracaibo_Waitress_7", pchar),
								StringFromKey("Maracaibo_Waitress_8"))),
						StringFromKey("Maracaibo_Waitress_10"),
						StringFromKey("Maracaibo_Waitress_11"),
						StringFromKey("Maracaibo_Waitress_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
