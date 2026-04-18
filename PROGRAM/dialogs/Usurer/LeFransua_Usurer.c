// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("LeFransua_Usurer_3", RandPhraseSimple(
								StringFromKey("LeFransua_Usurer_1"),
								StringFromKey("LeFransua_Usurer_2"))),
						StringFromKey("LeFransua_Usurer_4"),
						StringFromKey("LeFransua_Usurer_5"),
						StringFromKey("LeFransua_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("LeFransua_Usurer_9", RandPhraseSimple(
								StringFromKey("LeFransua_Usurer_7"),
								StringFromKey("LeFransua_Usurer_8"))),
						StringFromKey("LeFransua_Usurer_10"),
						StringFromKey("LeFransua_Usurer_11"),
						StringFromKey("LeFransua_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
