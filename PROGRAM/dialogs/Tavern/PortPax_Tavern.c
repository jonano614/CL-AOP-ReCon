// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortPax_Tavern_1", GetCityName(npchar.city)),
						StringFromKey("PortPax_Tavern_2"),
						StringFromKey("PortPax_Tavern_3"),
						StringFromKey("PortPax_Tavern_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortPax_Tavern_5", NPChar.name),
						StringFromKey("PortPax_Tavern_6", pchar),
						StringFromKey("PortPax_Tavern_7"),
						StringFromKey("PortPax_Tavern_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (checkattribute(pchar, "questTemp.PDM_PK_UznatLichnost"))    // Квест "Потерянное кольцо"
			{
				link.l1 = StringFromKey("PortPax_Tavern_9");
				link.l1.go = "PDM_PK_UznatLichnost";
			}
		break;

		//******************** квест "Потерянное кольцо" ******************
		case "PDM_PK_UznatLichnost":
			dialog.text = StringFromKey("PortPax_Tavern_10");
			link.l1 = StringFromKey("PortPax_Tavern_11");
			link.l1.go = "PDM_PK_UznatLichnost_2";
		break;

		case "PDM_PK_UznatLichnost_2":
			dialog.text = StringFromKey("PortPax_Tavern_12");
			Link.l1 = StringFromKey("PortPax_Tavern_13", npchar.name);
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
			RemoveLandQuestMark_Main(npchar, "PDM_Poteryanoe_Koltso");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
