// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PuertoPrincipe_Shipyard_3", RandPhraseSimple(
								StringFromKey("PuertoPrincipe_Shipyard_1"),
								StringFromKey("PuertoPrincipe_Shipyard_2"))),
						StringFromKey("PuertoPrincipe_Shipyard_4"),
						StringFromKey("PuertoPrincipe_Shipyard_5"),
						StringFromKey("PuertoPrincipe_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PuertoPrincipe_Shipyard_9", RandPhraseSimple(
								StringFromKey("PuertoPrincipe_Shipyard_7", pchar),
								StringFromKey("PuertoPrincipe_Shipyard_8"))),
						StringFromKey("PuertoPrincipe_Shipyard_10"),
						StringFromKey("PuertoPrincipe_Shipyard_11"),
						StringFromKey("PuertoPrincipe_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

