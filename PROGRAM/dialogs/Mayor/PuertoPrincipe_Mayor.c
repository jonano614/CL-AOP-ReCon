// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PuertoPrincipe_Mayor_3", RandPhraseSimple(
								StringFromKey("PuertoPrincipe_Mayor_1"),
								StringFromKey("PuertoPrincipe_Mayor_2"))),
						StringFromKey("PuertoPrincipe_Mayor_4"),
						StringFromKey("PuertoPrincipe_Mayor_5"),
						StringFromKey("PuertoPrincipe_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PuertoPrincipe_Mayor_9", RandPhraseSimple(
								StringFromKey("PuertoPrincipe_Mayor_7", pchar),
								StringFromKey("PuertoPrincipe_Mayor_8"))),
						StringFromKey("PuertoPrincipe_Mayor_10"),
						StringFromKey("PuertoPrincipe_Mayor_11"),
						StringFromKey("PuertoPrincipe_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

