// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = StringFromKey("Pirates_Church_3", RandPhraseSimple(
						StringFromKey("Pirates_Church_1"),
						StringFromKey("Pirates_Church_2")));
			link.l1 = StringFromKey("Pirates_Church_6", RandPhraseSimple(
						StringFromKey("Pirates_Church_4"),
						StringFromKey("Pirates_Church_5")));
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

