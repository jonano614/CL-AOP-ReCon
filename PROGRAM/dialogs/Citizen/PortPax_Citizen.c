// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = StringFromKey("PortPax_Citizen_3", RandPhraseSimple(
						StringFromKey("PortPax_Citizen_1"),
						StringFromKey("PortPax_Citizen_2")));
			link.l1 = StringFromKey("PortPax_Citizen_6", RandPhraseSimple(
						StringFromKey("PortPax_Citizen_4", pchar),
						StringFromKey("PortPax_Citizen_5")));
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.PDM_PK_UznatLichnost")) // Квест "Потерянное кольцо"
			{
				link.l1 = StringFromKey("PortPax_Citizen_7");
				link.l1.go = "PDM_PK_UznatLichnost";
			}
		break;

		case "info":
		// заменить на описание неких НПС, по квестам
			dialog.text = StringFromKey("PortPax_Citizen_8", NationNameGenitive(sti(NPChar.nation)));
			link.l1 = StringFromKey("PortPax_Citizen_9");
			link.l1.go = "exit";
			link.l2 = StringFromKey("PortPax_Citizen_10");
			link.l2.go = "new question";
		break;

		//**************************Квест "Потерянное кольцо"*******************************
		case "PDM_PK_UznatLichnost":
			int Phrase;
			Phrase = rand(4);
			if (Phrase == 0)
			{
				dialog.text = StringFromKey("PortPax_Citizen_11");
				link.l1 = StringFromKey("PortPax_Citizen_12");
				link.l1.go = "exit";
				break;
			}
			if (Phrase == 1)
			{
				dialog.text = StringFromKey("PortPax_Citizen_13");
				link.l1 = StringFromKey("PortPax_Citizen_14");
				link.l1.go = "exit";
				break;
			}
			if (Phrase == 2)
			{
				dialog.text = StringFromKey("PortPax_Citizen_15");
				link.l1 = StringFromKey("PortPax_Citizen_16");
				link.l1.go = "exit";
				break;
			}
			if (Phrase == 3)
			{
				dialog.text = StringFromKey("PortPax_Citizen_17");
				link.l1 = StringFromKey("PortPax_Citizen_18");
				link.l1.go = "exit";
				break;
			}
			if (Phrase == 4)
			{
				dialog.text = StringFromKey("PortPax_Citizen_19");
				link.l1 = StringFromKey("PortPax_Citizen_20");
				link.l1.go = "PDM_PK_UznatLichnost_2";
				break;
			}
		break;

		case "PDM_PK_UznatLichnost_2":
			dialog.text = StringFromKey("PortPax_Citizen_21", npchar);
			Link.l1 = StringFromKey("PortPax_Citizen_22", npchar.name);
			Link.l1.go = "exit";

			ref sld = CharacterFromID("Josephine_Lodet");
			sld.name = FindPersonalName("Josephine_Lodet_name");
			sld.lastname = FindPersonalName("Josephine_Lodet_lastname");

			AddQuestRecord("PDM_Poteryanoe_Koltso", "2");

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

