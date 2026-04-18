// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = StringFromKey("LaVega_Church_3", RandPhraseSimple(
						StringFromKey("LaVega_Church_1"),
						StringFromKey("LaVega_Church_2")));
			link.l1 = StringFromKey("LaVega_Church_6", RandPhraseSimple(
						StringFromKey("LaVega_Church_4"),
						StringFromKey("LaVega_Church_5")));
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

