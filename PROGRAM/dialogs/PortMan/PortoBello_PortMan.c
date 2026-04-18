// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortoBello_PortMan_3", RandPhraseSimple(
								StringFromKey("PortoBello_PortMan_1"),
								StringFromKey("PortoBello_PortMan_2", GetAddress_Form(NPChar)))),
						StringFromKey("PortoBello_PortMan_4", GetAddress_Form(NPChar)),
						StringFromKey("PortoBello_PortMan_5"),
						StringFromKey("PortoBello_PortMan_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortoBello_PortMan_9", RandPhraseSimple(
								StringFromKey("PortoBello_PortMan_7", pchar),
								StringFromKey("PortoBello_PortMan_8"))),
						StringFromKey("PortoBello_PortMan_10"),
						StringFromKey("PortoBello_PortMan_11"),
						StringFromKey("PortoBello_PortMan_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello_1")
			{
				link.l1 = StringFromKey("PortoBello_PortMan_13", pchar);
				link.l1.go = "Portobello_ratP_1";
			}
		break;

		case "Portobello_ratP_1":
			dialog.text = StringFromKey("PortoBello_PortMan_14", pchar.questTemp.Slavetrader.ShipName);
			link.l1 = StringFromKey("PortoBello_PortMan_15");
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatJamaica";
			AddQuestRecord("Slavetrader", "21_3");
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);

			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			AddLandQuestmark_Main(CharacterFromID("PortRoyal_tavernkeeper"), "Slavetrader");
			AddLandQuestmark_Main(CharacterFromID("PortRoyal_PortMan"), "Slavetrader");
			AddLandQuestmark_Main(CharacterFromID("FortOrange_tavernkeeper"), "Slavetrader");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
