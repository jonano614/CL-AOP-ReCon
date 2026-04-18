// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Villemstad_Fort_3", RandPhraseSimple(
								StringFromKey("Villemstad_Fort_1"),
								StringFromKey("Villemstad_Fort_2", GetAddress_Form(NPChar)))),
						StringFromKey("Villemstad_Fort_4", GetAddress_Form(NPChar)),
						StringFromKey("Villemstad_Fort_5"),
						StringFromKey("Villemstad_Fort_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Villemstad_Fort_9", RandPhraseSimple(
								StringFromKey("Villemstad_Fort_7", pchar),
								StringFromKey("Villemstad_Fort_8"))),
						StringFromKey("Villemstad_Fort_10"),
						StringFromKey("Villemstad_Fort_11"),
						StringFromKey("Villemstad_Fort_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


