// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = StringFromKey("PuertoPrincipe_Church_3", RandPhraseSimple(
						StringFromKey("PuertoPrincipe_Church_1"),
						StringFromKey("PuertoPrincipe_Church_2")));
			link.l1 = StringFromKey("PuertoPrincipe_Church_6", RandPhraseSimple(
						StringFromKey("PuertoPrincipe_Church_4"),
						StringFromKey("PuertoPrincipe_Church_5")));
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

