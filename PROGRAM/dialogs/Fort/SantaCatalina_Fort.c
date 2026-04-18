// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SantaCatalina_Fort_3", RandPhraseSimple(
								StringFromKey("SantaCatalina_Fort_1"),
								StringFromKey("SantaCatalina_Fort_2", GetAddress_Form(NPChar)))),
						StringFromKey("SantaCatalina_Fort_4", GetAddress_Form(NPChar)),
						StringFromKey("SantaCatalina_Fort_5"),
						StringFromKey("SantaCatalina_Fort_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SantaCatalina_Fort_9", RandPhraseSimple(
								StringFromKey("SantaCatalina_Fort_7", pchar),
								StringFromKey("SantaCatalina_Fort_8"))),
						StringFromKey("SantaCatalina_Fort_10"),
						StringFromKey("SantaCatalina_Fort_11"),
						StringFromKey("SantaCatalina_Fort_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


