// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Cartahena_Lighthouse_3", RandPhraseSimple(
								StringFromKey("Cartahena_Lighthouse_1"),
								StringFromKey("Cartahena_Lighthouse_2"))),
						StringFromKey("Cartahena_Lighthouse_4", GetAddress_Form(NPChar)),
						StringFromKey("Cartahena_Lighthouse_5"),
						StringFromKey("Cartahena_Lighthouse_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Cartahena_Lighthouse_9", RandPhraseSimple(
								StringFromKey("Cartahena_Lighthouse_7", pchar),
								StringFromKey("Cartahena_Lighthouse_8"))),
						StringFromKey("Cartahena_Lighthouse_10", pchar),
						StringFromKey("Cartahena_Lighthouse_11"),
						StringFromKey("Cartahena_Lighthouse_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
