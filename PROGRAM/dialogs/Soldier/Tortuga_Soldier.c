// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_Soldier_3", RandPhraseSimple(
								StringFromKey("Tortuga_Soldier_1"),
								StringFromKey("Tortuga_Soldier_2", GetAddress_Form(NPChar)))),
						StringFromKey("Tortuga_Soldier_4", GetAddress_Form(NPChar)),
						StringFromKey("Tortuga_Soldier_5"),
						StringFromKey("Tortuga_Soldier_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_Soldier_9", RandPhraseSimple(
								StringFromKey("Tortuga_Soldier_7", pchar),
								StringFromKey("Tortuga_Soldier_8"))),
						StringFromKey("Tortuga_Soldier_10"),
						StringFromKey("Tortuga_Soldier_11"),
						StringFromKey("Tortuga_Soldier_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
