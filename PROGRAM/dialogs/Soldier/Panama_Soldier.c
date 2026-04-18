// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Panama_Soldier_3", RandPhraseSimple(
								StringFromKey("Panama_Soldier_1"),
								StringFromKey("Panama_Soldier_2", GetAddress_Form(NPChar)))),
						StringFromKey("Panama_Soldier_4", GetAddress_Form(NPChar)),
						StringFromKey("Panama_Soldier_5"),
						StringFromKey("Panama_Soldier_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Panama_Soldier_9", RandPhraseSimple(
								StringFromKey("Panama_Soldier_7", pchar),
								StringFromKey("Panama_Soldier_8"))),
						StringFromKey("Panama_Soldier_10"),
						StringFromKey("Panama_Soldier_11"),
						StringFromKey("Panama_Soldier_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

