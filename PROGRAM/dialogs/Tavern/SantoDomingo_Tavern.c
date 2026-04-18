// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SantoDomingo_Tavern_1", GetCityName(npchar.city)),
						StringFromKey("SantoDomingo_Tavern_2"),
						StringFromKey("SantoDomingo_Tavern_3"),
						StringFromKey("SantoDomingo_Tavern_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SantoDomingo_Tavern_5", NPChar.name),
						StringFromKey("SantoDomingo_Tavern_6", pchar),
						StringFromKey("SantoDomingo_Tavern_7"),
						StringFromKey("SantoDomingo_Tavern_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
			{
				dialog.text = StringFromKey("SantoDomingo_Tavern_9", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("SantoDomingo_Tavern_10", pchar);
				link.l1.go = "Step_F7_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_PK_IshemKoltso"))    // Квест "Потерянное кольцо"
			{
				link.l1 = StringFromKey("SantoDomingo_Tavern_11");
				link.l1.go = "IshemKoltso";
			}
		break;
		//******************** Фр.линейка, квест №7. Спасение Рока Бразильца ******************
		case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SantoDomingo_Tavern_12", GetAddress_Form(NPChar)),
						StringFromKey("SantoDomingo_Tavern_13"),
						StringFromKey("SantoDomingo_Tavern_14"),
						StringFromKey("SantoDomingo_Tavern_15"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SantoDomingo_Tavern_16"),
						StringFromKey("SantoDomingo_Tavern_17", pchar),
						StringFromKey("SantoDomingo_Tavern_18", pchar),
						StringFromKey("SantoDomingo_Tavern_19"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F7_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_F7_2":
			dialog.text = StringFromKey("SantoDomingo_Tavern_20", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("SantoDomingo_Tavern_21");
			link.l1.go = "Step_F7_3";
		break;
		case "Step_F7_3":
			dialog.text = StringFromKey("SantoDomingo_Tavern_22", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("SantoDomingo_Tavern_23");
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
		//******************** Квест "Потерянное кольцо" ******************
		case "IshemKoltso":
			dialog.text = StringFromKey("SantoDomingo_Tavern_24");
			link.l1 = StringFromKey("SantoDomingo_Tavern_25");
			link.l1.go = "IshemKoltso_2";
		break;

		case "IshemKoltso_2":
			DialogExit();

			AddQuestRecord("PDM_Poteryanoe_Koltso", "3");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("", "а"));
			DeleteAttribute(pchar, "questTemp.PDM_PK_IshemKoltso");

			ref sld = GetCharacter(NPC_GenerateCharacter("PDM_PK_Francheska", "Francesca", "woman", "towngirl", 10, SPAIN, -1, false));
			sld.name = FindPersonalName("PDM_PK_Francheska_name");
			sld.lastname = FindPersonalName("PDM_PK_Francheska_lastname");
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
			RemoveLandQuestMark_Main(npchar, "PDM_Poteryanoe_Koltso");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
