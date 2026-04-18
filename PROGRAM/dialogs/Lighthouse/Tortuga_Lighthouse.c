// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_Lighthouse_3", RandPhraseSimple(
								StringFromKey("Tortuga_Lighthouse_1"),
								StringFromKey("Tortuga_Lighthouse_2"))),
						StringFromKey("Tortuga_Lighthouse_4", GetAddress_Form(NPChar)),
						StringFromKey("Tortuga_Lighthouse_5"),
						StringFromKey("Tortuga_Lighthouse_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_Lighthouse_9", RandPhraseSimple(
								StringFromKey("Tortuga_Lighthouse_7", pchar),
								StringFromKey("Tortuga_Lighthouse_8"))),
						StringFromKey("Tortuga_Lighthouse_10", pchar),
						StringFromKey("Tortuga_Lighthouse_11"),
						StringFromKey("Tortuga_Lighthouse_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}


