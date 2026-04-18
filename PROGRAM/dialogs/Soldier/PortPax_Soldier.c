// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortPax_Soldier_3", RandPhraseSimple(
								StringFromKey("PortPax_Soldier_1"),
								StringFromKey("PortPax_Soldier_2", GetAddress_Form(NPChar)))),
						StringFromKey("PortPax_Soldier_4", GetAddress_Form(NPChar)),
						StringFromKey("PortPax_Soldier_5"),
						StringFromKey("PortPax_Soldier_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortPax_Soldier_9", RandPhraseSimple(
								StringFromKey("PortPax_Soldier_7", pchar),
								StringFromKey("PortPax_Soldier_8"))),
						StringFromKey("PortPax_Soldier_10"),
						StringFromKey("PortPax_Soldier_11"),
						StringFromKey("PortPax_Soldier_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

