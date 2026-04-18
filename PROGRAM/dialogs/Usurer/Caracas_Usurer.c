// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Caracas_Usurer_3", RandPhraseSimple(
								StringFromKey("Caracas_Usurer_1"),
								StringFromKey("Caracas_Usurer_2"))),
						StringFromKey("Caracas_Usurer_4"),
						StringFromKey("Caracas_Usurer_5"),
						StringFromKey("Caracas_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Caracas_Usurer_9", RandPhraseSimple(
								StringFromKey("Caracas_Usurer_7", pchar),
								StringFromKey("Caracas_Usurer_8"))),
						StringFromKey("Caracas_Usurer_10"),
						StringFromKey("Caracas_Usurer_11"),
						StringFromKey("Caracas_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
