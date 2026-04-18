// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SantoDomingo_Fort_3", RandPhraseSimple(
								StringFromKey("SantoDomingo_Fort_1"),
								StringFromKey("SantoDomingo_Fort_2", GetAddress_Form(NPChar)))),
						StringFromKey("SantoDomingo_Fort_4", GetAddress_Form(NPChar)),
						StringFromKey("SantoDomingo_Fort_5"),
						StringFromKey("SantoDomingo_Fort_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SantoDomingo_Fort_9", RandPhraseSimple(
								StringFromKey("SantoDomingo_Fort_7", pchar),
								StringFromKey("SantoDomingo_Fort_8"))),
						StringFromKey("SantoDomingo_Fort_10"),
						StringFromKey("SantoDomingo_Fort_11"),
						StringFromKey("SantoDomingo_Fort_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


