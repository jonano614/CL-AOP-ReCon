// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Santiago_Soldier_3", RandPhraseSimple(
								StringFromKey("Santiago_Soldier_1"),
								StringFromKey("Santiago_Soldier_2", GetAddress_Form(NPChar)))),
						StringFromKey("Santiago_Soldier_4", GetAddress_Form(NPChar)),
						StringFromKey("Santiago_Soldier_5"),
						StringFromKey("Santiago_Soldier_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Santiago_Soldier_9", RandPhraseSimple(
								StringFromKey("Santiago_Soldier_7", pchar),
								StringFromKey("Santiago_Soldier_8"))),
						StringFromKey("Santiago_Soldier_10"),
						StringFromKey("Santiago_Soldier_11"),
						StringFromKey("Santiago_Soldier_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
