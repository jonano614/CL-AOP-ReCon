// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Caracas_Soldier_3", RandPhraseSimple(
								StringFromKey("Caracas_Soldier_1"),
								StringFromKey("Caracas_Soldier_2", GetAddress_Form(NPChar)))),
						StringFromKey("Caracas_Soldier_4", GetAddress_Form(NPChar)),
						StringFromKey("Caracas_Soldier_5"),
						StringFromKey("Caracas_Soldier_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Caracas_Soldier_9", RandPhraseSimple(
								StringFromKey("Caracas_Soldier_7", pchar),
								StringFromKey("Caracas_Soldier_8"))),
						StringFromKey("Caracas_Soldier_10"),
						StringFromKey("Caracas_Soldier_11"),
						StringFromKey("Caracas_Soldier_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

