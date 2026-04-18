// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortOrange_Soldier_3", RandPhraseSimple(
								StringFromKey("FortOrange_Soldier_1"),
								StringFromKey("FortOrange_Soldier_2", GetAddress_Form(NPChar)))),
						StringFromKey("FortOrange_Soldier_4", GetAddress_Form(NPChar)),
						StringFromKey("FortOrange_Soldier_5"),
						StringFromKey("FortOrange_Soldier_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortOrange_Soldier_9", RandPhraseSimple(
								StringFromKey("FortOrange_Soldier_7", pchar),
								StringFromKey("FortOrange_Soldier_8"))),
						StringFromKey("FortOrange_Soldier_10"),
						StringFromKey("FortOrange_Soldier_11"),
						StringFromKey("FortOrange_Soldier_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

