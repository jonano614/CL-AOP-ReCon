// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PuertoPrincipe_Usurer_3", RandPhraseSimple(
								StringFromKey("PuertoPrincipe_Usurer_1"),
								StringFromKey("PuertoPrincipe_Usurer_2"))),
						StringFromKey("PuertoPrincipe_Usurer_4"),
						StringFromKey("PuertoPrincipe_Usurer_5"),
						StringFromKey("PuertoPrincipe_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PuertoPrincipe_Usurer_9", RandPhraseSimple(
								StringFromKey("PuertoPrincipe_Usurer_7", pchar),
								StringFromKey("PuertoPrincipe_Usurer_8"))),
						StringFromKey("PuertoPrincipe_Usurer_10"),
						StringFromKey("PuertoPrincipe_Usurer_11"),
						StringFromKey("PuertoPrincipe_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
