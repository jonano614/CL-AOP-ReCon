// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SantaCatalina_Usurer_3", RandPhraseSimple(
								StringFromKey("SantaCatalina_Usurer_1"),
								StringFromKey("SantaCatalina_Usurer_2"))),
						StringFromKey("SantaCatalina_Usurer_4"),
						StringFromKey("SantaCatalina_Usurer_5"),
						StringFromKey("SantaCatalina_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SantaCatalina_Usurer_9", RandPhraseSimple(
								StringFromKey("SantaCatalina_Usurer_7", pchar),
								StringFromKey("SantaCatalina_Usurer_8"))),
						StringFromKey("SantaCatalina_Usurer_10"),
						StringFromKey("SantaCatalina_Usurer_11"),
						StringFromKey("SantaCatalina_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
