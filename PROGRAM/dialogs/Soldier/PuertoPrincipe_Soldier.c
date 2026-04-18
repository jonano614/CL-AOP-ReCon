// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PuertoPrincipe_Soldier_3", RandPhraseSimple(
								StringFromKey("PuertoPrincipe_Soldier_1"),
								StringFromKey("PuertoPrincipe_Soldier_2", GetAddress_Form(NPChar)))),
						StringFromKey("PuertoPrincipe_Soldier_4", GetAddress_Form(NPChar)),
						StringFromKey("PuertoPrincipe_Soldier_5"),
						StringFromKey("PuertoPrincipe_Soldier_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PuertoPrincipe_Soldier_9", RandPhraseSimple(
								StringFromKey("PuertoPrincipe_Soldier_7", pchar),
								StringFromKey("PuertoPrincipe_Soldier_8"))),
						StringFromKey("PuertoPrincipe_Soldier_10"),
						StringFromKey("PuertoPrincipe_Soldier_11"),
						StringFromKey("PuertoPrincipe_Soldier_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
