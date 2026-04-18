// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = StringFromKey("SantoDomingo_Citizen_3", RandPhraseSimple(
						StringFromKey("SantoDomingo_Citizen_1"),
						StringFromKey("SantoDomingo_Citizen_2")));
			link.l1 = StringFromKey("SantoDomingo_Citizen_6", RandPhraseSimple(
						StringFromKey("SantoDomingo_Citizen_4", pchar),
						StringFromKey("SantoDomingo_Citizen_5")));
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.PDM_PK_IshemKoltso"))    // Квест "Потерянное кольцо"
			{
				link.l1 = StringFromKey("SantoDomingo_Citizen_7", npchar);
				link.l1.go = "IshemKoltso";
			}
		break;

		case "info":
		// заменить на описание неких НПС, по квестам
			dialog.text = StringFromKey("SantoDomingo_Citizen_8", NationNameGenitive(sti(NPChar.nation)));
			link.l1 = StringFromKey("SantoDomingo_Citizen_9");
			link.l1.go = "exit";
			link.l2 = StringFromKey("SantoDomingo_Citizen_10");
			link.l2.go = "new question";
		break;

		//******************** Квест "Потерянное кольцо" ******************
		case "IshemKoltso":
			int Phrase;
			Phrase = rand(4);
			if (Phrase == 0)
			{
				dialog.text = StringFromKey("SantoDomingo_Citizen_11");
				link.l1 = StringFromKey("SantoDomingo_Citizen_12");
				link.l1.go = "exit";
				break;
			}
			if (Phrase == 1)
			{
				dialog.text = StringFromKey("SantoDomingo_Citizen_16", LinkRandPhrase(
							StringFromKey("SantoDomingo_Citizen_13"),
							StringFromKey("SantoDomingo_Citizen_14"),
							StringFromKey("SantoDomingo_Citizen_15")));
				link.l1 = StringFromKey("SantoDomingo_Citizen_17", pchar);
				link.l1.go = "exit";
				break;
			}
			if (Phrase == 2)
			{
				dialog.text = StringFromKey("SantoDomingo_Citizen_18");
				link.l1 = StringFromKey("SantoDomingo_Citizen_19");
				link.l1.go = "exit";
				break;
			}
			if (Phrase == 3)
			{
				dialog.text = StringFromKey("SantoDomingo_Citizen_20");
				link.l1 = StringFromKey("SantoDomingo_Citizen_21");
				link.l1.go = "exit";
				break;
			}
			if (Phrase == 4)
			{
				dialog.text = StringFromKey("SantoDomingo_Citizen_22", npchar);
				link.l1 = StringFromKey("SantoDomingo_Citizen_23", npchar.name);
				link.l1.go = "exit";

				AddQuestRecord("PDM_Poteryanoe_Koltso", "3");
				DeleteAttribute(pchar, "questTemp.PDM_PK_IshemKoltso");

				ref sld = GetCharacter(NPC_GenerateCharacter("PDM_PK_Francheska", "Francesca", "woman", "towngirl", 10, SPAIN, -1, false));
				sld.name = FindPersonalName("PDM_PK_Francheska_name");
				sld.lastname = "";
				sld.city = "SantoDomingo";
				sld.location = "SantoDomingo_Brothel";
				sld.location.group = "goto";
				sld.location.locator = "goto3";
				sld.dialog.filename = "Quest\PDM\Poteryanoe_Koltso.c";
				sld.dialog.currentnode = "Francheska";
				LAi_SetCitizenType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				LAi_SetImmortal(sld, true);
				AddLandQuestMark_Main(sld, "PDM_Poteryanoe_Koltso");

				RemoveLandQuestMarkToFantoms_Main("ItemTrader", "PDM_Poteryanoe_Koltso");
				RemoveLandQuestMarkToFantoms_Main("Citizen", "PDM_Poteryanoe_Koltso");
				RemoveLandQuestMarkToFantoms_Main("Commoner", "PDM_Poteryanoe_Koltso");
				RemoveLandQuestMark_Main(CharacterFromId("SantoDomingo_tavernkeeper"), "PDM_Poteryanoe_Koltso");
				break;
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

