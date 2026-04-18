// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = StringFromKey("Cumana_Citizen_3", RandPhraseSimple(
						StringFromKey("Cumana_Citizen_1"),
						StringFromKey("Cumana_Citizen_2")));
			link.l1 = StringFromKey("Cumana_Citizen_6", RandPhraseSimple(
						StringFromKey("Cumana_Citizen_4", pchar),
						StringFromKey("Cumana_Citizen_5")));
			link.l1.go = "exit";
			// Квест Изабеллы, розыск кэпа брига "раны"
			if (CheckAttribute(pchar, "RomanticQuest.ShipToCumana"))
			{
				dialog.Text = StringFromKey("Cumana_Citizen_7");
				link.l1 = StringFromKey("Cumana_Citizen_8");
				Link.l1.go = "RomanticQuest_1";
			}
		break;
		// ==> Квест Изабеллы, розыск кэпа брига "раны"
		case "RomanticQuest_1":
			dialog.Text = StringFromKey("Cumana_Citizen_9", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Cumana_Citizen_10");
			Link.l1.go = "RomanticQuest_2";
		break;
		case "RomanticQuest_2":
			dialog.Text = StringFromKey("Cumana_Citizen_11");
			link.l1 = StringFromKey("Cumana_Citizen_12");
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "RomanticQuest.ShipToCumana");
			Pchar.RomanticQuest.ShipToCumanaTavenrn = true;
			ref rChar = GetCharacter(NPC_GenerateCharacter("BrigCaptain", "officer_21", "man", "man", 20, SPAIN, -1, false));
			rChar.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
			FreeSitLocator("Cumana_tavern", "sit3");  // очистим стул
			ChangeCharacterAddressGroup(rChar, "Cumana_tavern", "sit", "sit3");
			LAi_SetSitType(rChar);
			RemoveLandQuestmarkToFantoms_Main("Citizen", "Romantic_Line");
			RemoveLandQuestmarkToFantoms_Main("Commoner", "Romantic_Line");
			AddLandQuestmark_Main(CharacterFromID("Cumana_tavernkeeper"), "Romantic_Line");
		break;
		// <== Квест Изабеллы, розыск кэпа брига "раны"
		case "info":
		// заменить на описание неких НПС, по квестам
			dialog.text = StringFromKey("Cumana_Citizen_13", NationNameGenitive(sti(NPChar.nation)));
			link.l1 = StringFromKey("Cumana_Citizen_14");
			link.l1.go = "exit";
			link.l2 = StringFromKey("Cumana_Citizen_15");
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
