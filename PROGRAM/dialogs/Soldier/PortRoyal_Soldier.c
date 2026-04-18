// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortRoyal_Soldier_3", RandPhraseSimple(
								StringFromKey("PortRoyal_Soldier_1"),
								StringFromKey("PortRoyal_Soldier_2", GetAddress_Form(NPChar)))),
						StringFromKey("PortRoyal_Soldier_4", GetAddress_Form(NPChar)),
						StringFromKey("PortRoyal_Soldier_5"),
						StringFromKey("PortRoyal_Soldier_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortRoyal_Soldier_9", RandPhraseSimple(
								StringFromKey("PortRoyal_Soldier_7", pchar),
								StringFromKey("PortRoyal_Soldier_8"))),
						StringFromKey("PortRoyal_Soldier_10"),
						StringFromKey("PortRoyal_Soldier_11"),
						StringFromKey("PortRoyal_Soldier_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		/*sld = characterFromId("eng_guber");
		if (npchar.location == "PortRoyal_townhall" && pchar.questTemp.State == "" && CheckAttribute(sld, "notQuestLine"))
		{
			dialog.text = "Ключ! Дай мне ключ!!!";
			Link.l1.edit = 7;
			link.l1 = "";
			link.l1.go = "ELOpenKey_1";
		}*/
		break;

		case "ELOpenKey_1":
			if (dialogEditStrings[7] == KEY_ENG_LINE)
			{
				dialog.text = StringFromKey("PortRoyal_Soldier_13");
				Link.l1 = StringFromKey("PortRoyal_Soldier_14");
				Link.l1.go = "exit";
				sld = characterFromId("eng_guber");
				DeleteAttribute(sld, "notQuestLine");
			}
			else
			{
				dialog.text = StringFromKey("PortRoyal_Soldier_15");
				Link.l1 = StringFromKey("PortRoyal_Soldier_16");
				Link.l1.go = "exit";
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
