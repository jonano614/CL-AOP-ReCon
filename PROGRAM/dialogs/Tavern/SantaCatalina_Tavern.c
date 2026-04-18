// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SantaCatalina_Tavern_3", RandPhraseSimple(
								StringFromKey("SantaCatalina_Tavern_1"),
								StringFromKey("SantaCatalina_Tavern_2", GetAddress_Form(NPChar)))),
						StringFromKey("SantaCatalina_Tavern_4", GetAddress_Form(NPChar)),
						StringFromKey("SantaCatalina_Tavern_5"),
						StringFromKey("SantaCatalina_Tavern_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SantaCatalina_Tavern_9", RandPhraseSimple(
								StringFromKey("SantaCatalina_Tavern_7", pchar),
								StringFromKey("SantaCatalina_Tavern_8"))),
						StringFromKey("SantaCatalina_Tavern_10"),
						StringFromKey("SantaCatalina_Tavern_11"),
						StringFromKey("SantaCatalina_Tavern_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
