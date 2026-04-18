// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Caracas_Tavern_3", RandPhraseSimple(
								StringFromKey("Caracas_Tavern_1"),
								StringFromKey("Caracas_Tavern_2", GetAddress_Form(NPChar)))),
						StringFromKey("Caracas_Tavern_4", GetAddress_Form(NPChar)),
						StringFromKey("Caracas_Tavern_5"),
						StringFromKey("Caracas_Tavern_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Caracas_Tavern_9", RandPhraseSimple(
								StringFromKey("Caracas_Tavern_7", pchar),
								StringFromKey("Caracas_Tavern_8"))),
						StringFromKey("Caracas_Tavern_10"),
						StringFromKey("Caracas_Tavern_11"),
						StringFromKey("Caracas_Tavern_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
