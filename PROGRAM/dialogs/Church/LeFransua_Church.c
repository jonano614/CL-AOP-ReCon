// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = StringFromKey("LeFransua_Church_3", RandPhraseSimple(
						StringFromKey("LeFransua_Church_1"),
						StringFromKey("LeFransua_Church_2")));
			link.l1 = StringFromKey("LeFransua_Church_6", RandPhraseSimple(
						StringFromKey("LeFransua_Church_4"),
						StringFromKey("LeFransua_Church_5")));
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

