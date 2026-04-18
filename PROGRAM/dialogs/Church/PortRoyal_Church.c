// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortRoyal_Church_3", RandPhraseSimple(
								StringFromKey("PortRoyal_Church_1", pchar),
								StringFromKey("PortRoyal_Church_2"))),
						StringFromKey("PortRoyal_Church_4", pchar),
						StringFromKey("PortRoyal_Church_5", pchar),
						StringFromKey("PortRoyal_Church_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortRoyal_Church_9", RandPhraseSimple(
								StringFromKey("PortRoyal_Church_7", pchar),
								StringFromKey("PortRoyal_Church_8"))),
						StringFromKey("PortRoyal_Church_10"),
						StringFromKey("PortRoyal_Church_11"),
						StringFromKey("PortRoyal_Church_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "MorrisWillams_ArrestedSeekInfo" || pchar.questTemp.State == "MorrisWillams_ArrestedSeekInfoFather")
			{
				link.l1 = StringFromKey("PortRoyal_Church_13");
				link.l1.go = "Step_E6_1";
			}
		break;

		case "Step_E6_1":
			dialog.text = StringFromKey("PortRoyal_Church_14");
			link.l1 = StringFromKey("PortRoyal_Church_15");
			link.l1.go = "Step_E6_2";
		break;

		case "Step_E6_2":
			dialog.text = StringFromKey("PortRoyal_Church_16");
			link.l1 = StringFromKey("PortRoyal_Church_17");
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_ArrestedSeekInfoWomen";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "19");
			AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex", GetSexPhrase("", "а"));
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			RemoveLandQuestmark_Main(characterFromID("PortRoyal_tavernkeeper"), "Eng_Line");
			ref sld = GetCharacter(NPC_GenerateCharacter("Gillian Atterbury", "women_12", "woman", "towngirl", 5, ENGLAND, 100, false));
			sld.name = FindPersonalName("Gillian_Atterbury_name");
			sld.lastname = FindPersonalName("Gillian_Atterbury_lastname");
			LAi_SetCitizenType(sld);
			sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "PortRoyal_town", "goto", "goto1");
			LAi_SetFanatic(sld, "PortRoyal_church", "sit", "sit1", 11.0, 14.0);
			AddLandQuestmark_Main(sld, "Eng_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

