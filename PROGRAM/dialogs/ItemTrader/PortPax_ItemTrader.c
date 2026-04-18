// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortPax_ItemTrader_3", RandPhraseSimple(
								StringFromKey("PortPax_ItemTrader_1"),
								StringFromKey("PortPax_ItemTrader_2", GetAddress_Form(NPChar)))),
						StringFromKey("PortPax_ItemTrader_4", GetAddress_Form(NPChar)),
						StringFromKey("PortPax_ItemTrader_5", GetAddress_Form(NPChar)),
						StringFromKey("PortPax_ItemTrader_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortPax_ItemTrader_9", RandPhraseSimple(
								StringFromKey("PortPax_ItemTrader_7"),
								StringFromKey("PortPax_ItemTrader_8"))),
						StringFromKey("PortPax_ItemTrader_10"),
						StringFromKey("PortPax_ItemTrader_11"),
						StringFromKey("PortPax_ItemTrader_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.PDM_PK_UznatLichnost") && pchar.questTemp.PDM_PK_UznatLichnost == "UznatLichnost")    // Квест "Потерянное кольцо"
			{
				link.l1 = StringFromKey("PortPax_ItemTrader_13");
				link.l1.go = "PDM_PK_UznatLichnost";
			}
		break;

		//**************************Квест "Потерянное кольцо"*******************************
		case "PDM_PK_UznatLichnost":
			int Phrase;
			Phrase = rand(4);
			if (Phrase == 0)
			{
				dialog.text = StringFromKey("PortPax_ItemTrader_14");
				link.l1 = StringFromKey("PortPax_ItemTrader_15");
				link.l1.go = "exit";
				break;
			}
			if (Phrase == 1)
			{
				dialog.text = StringFromKey("PortPax_ItemTrader_16");
				link.l1 = StringFromKey("PortPax_ItemTrader_17");
				link.l1.go = "exit";
				break;
			}
			if (Phrase == 2)
			{
				dialog.text = StringFromKey("PortPax_ItemTrader_18", pchar);
				link.l1 = StringFromKey("PortPax_ItemTrader_19");
				link.l1.go = "exit";
				break;
			}
			if (Phrase == 3)
			{
				dialog.text = StringFromKey("PortPax_ItemTrader_20");
				link.l1 = StringFromKey("PortPax_ItemTrader_21");
				link.l1.go = "exit";
				break;
			}
			if (Phrase == 4)
			{
				dialog.text = StringFromKey("PortPax_ItemTrader_22");
				link.l1 = StringFromKey("PortPax_ItemTrader_23");
				link.l1.go = "PDM_PK_UznatLichnost_2";
				break;
			}
		break;

		case "PDM_PK_UznatLichnost_2":
			dialog.text = StringFromKey("PortPax_ItemTrader_24", npchar);
			Link.l1 = StringFromKey("PortPax_ItemTrader_25", npchar.name);
			Link.l1.go = "exit";

			ref sld = CharacterFromID("Josephine_Lodet");
			sld.name = FindPersonalName("Josephine_Lodet_name");
			sld.lastname = FindPersonalName("Josephine_Lodet_lastname");

			AddQuestRecord("PDM_Poteryanoe_Koltso", "2");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("", "а"));

			pchar.questTemp.PDM_PK_IshemKoltso = "IshemKoltso";
			DeleteAttribute(pchar, "questTemp.PDM_PK_UznatLichnost");
			AddLandQuestMarkToFantoms_Main("ItemTrader", "PDM_Poteryanoe_Koltso", "PDM_Poteryanoe_Koltso_IshemKoltso_QuestMarkCondition");
			AddLandQuestMarkToFantoms_Main("Citizen", "PDM_Poteryanoe_Koltso", "PDM_Poteryanoe_Koltso_IshemKoltso_QuestMarkCondition");
			AddLandQuestMarkToFantoms_Main("Commoner", "PDM_Poteryanoe_Koltso", "PDM_Poteryanoe_Koltso_IshemKoltso_QuestMarkCondition");
			AddLandQuestMark_Main(CharacterFromId("SantoDomingo_tavernkeeper"), "PDM_Poteryanoe_Koltso");
			RemoveLandQuestMark_Main(CharacterFromId("PortPax_tavernkeeper"), "PDM_Poteryanoe_Koltso");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

