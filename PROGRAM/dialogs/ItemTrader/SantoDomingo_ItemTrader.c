// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SantoDomingo_ItemTrader_3", RandPhraseSimple(
								StringFromKey("SantoDomingo_ItemTrader_1"),
								StringFromKey("SantoDomingo_ItemTrader_2", GetAddress_Form(NPChar)))),
						StringFromKey("SantoDomingo_ItemTrader_4", GetAddress_Form(NPChar)),
						StringFromKey("SantoDomingo_ItemTrader_5", GetAddress_Form(NPChar)),
						StringFromKey("SantoDomingo_ItemTrader_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SantoDomingo_ItemTrader_9", RandPhraseSimple(
								StringFromKey("SantoDomingo_ItemTrader_7"),
								StringFromKey("SantoDomingo_ItemTrader_8"))),
						StringFromKey("SantoDomingo_ItemTrader_10"),
						StringFromKey("SantoDomingo_ItemTrader_11"),
						StringFromKey("SantoDomingo_ItemTrader_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.PDM_PK_IshemKoltso"))    // Квест "Потерянное кольцо"
			{
				link.l1 = StringFromKey("SantoDomingo_ItemTrader_13", npchar);
				link.l1.go = "IshemKoltso";
			}
		break;

		//******************** Квест "Потерянное кольцо" ******************
		case "IshemKoltso":
			int Phrase;
			Phrase = rand(4);
			if (Phrase == 0)
			{
				dialog.text = StringFromKey("SantoDomingo_ItemTrader_14");
				link.l1 = StringFromKey("SantoDomingo_ItemTrader_15");
				link.l1.go = "exit";
				break;
			}
			if (Phrase == 1)
			{
				dialog.text = StringFromKey("SantoDomingo_ItemTrader_19", LinkRandPhrase(
							StringFromKey("SantoDomingo_ItemTrader_16"),
							StringFromKey("SantoDomingo_ItemTrader_17"),
							StringFromKey("SantoDomingo_ItemTrader_18")));
				link.l1 = StringFromKey("SantoDomingo_ItemTrader_20", pchar);
				link.l1.go = "exit";
				break;
			}
			if (Phrase == 2)
			{
				dialog.text = StringFromKey("SantoDomingo_ItemTrader_21");
				link.l1 = StringFromKey("SantoDomingo_ItemTrader_22");
				link.l1.go = "exit";
				break;
			}
			if (Phrase == 3)
			{
				dialog.text = StringFromKey("SantoDomingo_ItemTrader_23");
				link.l1 = StringFromKey("SantoDomingo_ItemTrader_24");
				link.l1.go = "exit";
				break;
			}
			if (Phrase == 4)
			{
				dialog.text = StringFromKey("SantoDomingo_ItemTrader_25", npchar);
				link.l1 = StringFromKey("SantoDomingo_ItemTrader_26", npchar.name);
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

