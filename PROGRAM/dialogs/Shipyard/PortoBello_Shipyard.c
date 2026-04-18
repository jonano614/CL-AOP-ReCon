// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortoBello_Shipyard_3", RandPhraseSimple(
								StringFromKey("PortoBello_Shipyard_1"),
								StringFromKey("PortoBello_Shipyard_2"))),
						StringFromKey("PortoBello_Shipyard_4"),
						StringFromKey("PortoBello_Shipyard_5"),
						StringFromKey("PortoBello_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortoBello_Shipyard_9", RandPhraseSimple(
								StringFromKey("PortoBello_Shipyard_7", pchar),
								StringFromKey("PortoBello_Shipyard_8"))),
						StringFromKey("PortoBello_Shipyard_10"),
						StringFromKey("PortoBello_Shipyard_11"),
						StringFromKey("PortoBello_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
			{
				link.l1 = StringFromKey("PortoBello_Shipyard_13");
				link.l1.go = "Portobello_ratS_1";
			}
		break;

		case "Portobello_ratS_1":
			dialog.text = StringFromKey("PortoBello_Shipyard_14");
			link.l1 = StringFromKey("PortoBello_Shipyard_15");
			link.l1.go = "Portobello_ratS_2";
		break;

		case "Portobello_ratS_2":
			dialog.text = StringFromKey("PortoBello_Shipyard_16", pchar);
			link.l1 = StringFromKey("PortoBello_Shipyard_17");
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello_1";
			AddQuestRecord("Slavetrader", "21_2");

			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			RemoveLandQuestmark_Main(CharacterFromID("PortoBello_tavernkeeper"), "Slavetrader");
			AddLandQuestmark_Main(CharacterFromID("PortoBello_PortMan"), "Slavetrader");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

