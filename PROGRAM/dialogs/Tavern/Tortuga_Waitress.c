// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_Waitress_3", RandPhraseSimple(
								StringFromKey("Tortuga_Waitress_1", GetAddress_Form(NPChar)),
								StringFromKey("Tortuga_Waitress_2", GetAddress_Form(NPChar)))),
						StringFromKey("Tortuga_Waitress_4", pchar),
						StringFromKey("Tortuga_Waitress_5", pchar),
						StringFromKey("Tortuga_Waitress_6", GetAddress_Form(NPChar)), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_Waitress_9", RandPhraseSimple(
								StringFromKey("Tortuga_Waitress_7", pchar),
								StringFromKey("Tortuga_Waitress_8"))),
						StringFromKey("Tortuga_Waitress_10"),
						StringFromKey("Tortuga_Waitress_11"),
						StringFromKey("Tortuga_Waitress_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
