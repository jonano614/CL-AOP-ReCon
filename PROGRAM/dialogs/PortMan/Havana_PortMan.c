// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Havana_PortMan_3", RandPhraseSimple(
								StringFromKey("Havana_PortMan_1"),
								StringFromKey("Havana_PortMan_2", GetAddress_Form(NPChar)))),
						StringFromKey("Havana_PortMan_4", GetAddress_Form(NPChar)),
						StringFromKey("Havana_PortMan_5"),
						StringFromKey("Havana_PortMan_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Havana_PortMan_9", RandPhraseSimple(
								StringFromKey("Havana_PortMan_7", pchar),
								StringFromKey("Havana_PortMan_8"))),
						StringFromKey("Havana_PortMan_10"),
						StringFromKey("Havana_PortMan_11"),
						StringFromKey("Havana_PortMan_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
			{
				link.l1 = StringFromKey("Havana_PortMan_13", pchar, pchar.questTemp.Slavetrader.ShipName);
				link.l1.go = "Havana_ratP_1";
			}

		break;

		case "Havana_ratP_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Havana_PortMan_14"),
						StringFromKey("Havana_PortMan_15"),
						StringFromKey("Havana_PortMan_16"),
						StringFromKey("Havana_PortMan_17"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Havana_PortMan_18"),
						StringFromKey("Havana_PortMan_19"),
						StringFromKey("Havana_PortMan_20", pchar),
						StringFromKey("Havana_PortMan_21", npchar.name), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
