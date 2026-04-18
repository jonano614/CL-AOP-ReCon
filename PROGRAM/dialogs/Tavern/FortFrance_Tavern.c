// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortFrance_Tavern_3", RandPhraseSimple(
								StringFromKey("FortFrance_Tavern_1"),
								StringFromKey("FortFrance_Tavern_2", GetAddress_Form(NPChar)))),
						StringFromKey("FortFrance_Tavern_4", GetAddress_Form(NPChar)),
						StringFromKey("FortFrance_Tavern_5"),
						StringFromKey("FortFrance_Tavern_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortFrance_Tavern_9", RandPhraseSimple(
								StringFromKey("FortFrance_Tavern_7", pchar),
								StringFromKey("FortFrance_Tavern_8"))),
						StringFromKey("FortFrance_Tavern_10"),
						StringFromKey("FortFrance_Tavern_11"),
						StringFromKey("FortFrance_Tavern_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "BlackLabel_toLaVega")
			{
				link.l1 = StringFromKey("FortFrance_Tavern_13");
				link.l1.go = "PL_Q2_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_PJ_KV"))    //Квест ***Проклятая жара***		(Вино)
			{
				link.l1 = StringFromKey("FortFrance_Tavern_14", pchar);
				link.l1.go = "PDM_PJ_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_PJ_KR"))    //Квест ***Проклятая жара***		(Ром)
			{
				link.l1 = StringFromKey("FortFrance_Tavern_15");
				link.l1.go = "PDM_PJ_Rom_1";
			}
		break;
		case "PL_Q2_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortFrance_Tavern_16"),
						StringFromKey("FortFrance_Tavern_17", pchar),
						StringFromKey("FortFrance_Tavern_18"),
						StringFromKey("FortFrance_Tavern_19"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortFrance_Tavern_20"),
						StringFromKey("FortFrance_Tavern_21", pchar),
						StringFromKey("FortFrance_Tavern_22"), "...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;

		case "PDM_PJ_1":
			dialog.text = StringFromKey("FortFrance_Tavern_23");
			link.l1 = StringFromKey("FortFrance_Tavern_24");
			link.l1.go = "PDM_PJ_2";
		break;

		case "PDM_PJ_2":
			dialog.text = StringFromKey("FortFrance_Tavern_25", GetAddress_Form(NPChar));
			MakeRandomLinkOrderThree(link,
					StringFromKey("FortFrance_Tavern_26", npchar.name), "PDM_PJ_Beru_1",
					StringFromKey("FortFrance_Tavern_27"), "PDM_PJ_Beru_2",
					StringFromKey("FortFrance_Tavern_28"), "exit");
		break;

		case "PDM_PJ_Beru_1":
			dialog.text = StringFromKey("FortFrance_Tavern_29", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("FortFrance_Tavern_30", npchar.name);
			link.l1.go = "PDM_PJ_Beru_3";
		break;

		case "PDM_PJ_Beru_2":
			dialog.text = StringFromKey("FortFrance_Tavern_31", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("FortFrance_Tavern_32");
			link.l1.go = "PDM_PJ_Beru_3";
		break;

		case "PDM_PJ_Beru_3":
			DialogExit();

			AddQuestRecord("PDM_Proklyataya_Jara", "2");
			GiveItem2Character(PChar, "PDM_PJ_Vino");
			AddMoneyToCharacter(pchar, -200);
			DeleteAttribute(pchar, "questTemp.PDM_PJ_KV");
			DeleteAttribute(pchar, "questTemp.PDM_PJ_SS");
			sld = CharacterFromID("PDM_PJ_Strajnik_1");
			sld.Dialog.Filename = "Quest\PDM\Proklyataya_Jara.c";
			sld.dialog.currentnode = "Prines_Vino_1";
			AddLandQuestMark_Main(sld, "PDM_Proklyataya_Jara");

			RemoveLandQuestMark_Main(npchar, "PDM_Proklyataya_Jara");
			RemoveLandQuestMarkToFantoms_Main("Maltie_officer", "PDM_Proklyataya_Jara");
		break;

		case "PDM_PJ_Rom_1":
			dialog.text = StringFromKey("FortFrance_Tavern_33", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("FortFrance_Tavern_34", npchar.name);
			link.l1.go = "PDM_PJ_Rom_2";
		break;

		case "PDM_PJ_Rom_2":
			dialog.text = StringFromKey("FortFrance_Tavern_35", pchar, GetAddress_Form(NPChar));
			link.l1 = StringFromKey("FortFrance_Tavern_36");
			link.l1.go = "PDM_PJ_Rom_3";
		break;

		case "PDM_PJ_Rom_3":
			dialog.text = StringFromKey("FortFrance_Tavern_37");
			link.l1 = StringFromKey("FortFrance_Tavern_38", npchar.name);
			link.l1.go = "exit";
			link.l2 = StringFromKey("FortFrance_Tavern_39");
			link.l2.go = "PDM_PJ_Rom_4";
		break;

		case "PDM_PJ_Rom_4":
			dialog.text = StringFromKey("FortFrance_Tavern_40", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("FortFrance_Tavern_41", npchar.name);
			link.l1.go = "PDM_PJ_Rom_5";
			AddMoneyToCharacter(pchar, -200);
		break;

		case "PDM_PJ_Rom_5":
			DialogExit();

			Log_info(StringFromKey("InfoMessages_153"));
			GiveItem2Character(PChar, "PDM_PJ_Rom");
			GiveItem2Character(PChar, "PDM_PJ_BsRL");
			DeleteAttribute(pchar, "questTemp.PDM_PJ_KR");
			sld = CharacterFromID("PDM_PJ_Strajnik_2");
			sld.Dialog.Filename = "Quest\PDM\Proklyataya_Jara.c";
			sld.dialog.currentnode = "Prines_Rom_1";
			AddQuestRecord("PDM_Proklyataya_Jara", "4");
			AddLandQuestMark_Main(sld, "PDM_Proklyataya_Jara");

			sld = CharacterFromID("PDM_PJ_Strajnik_1");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "stun_1", "", 1.0);

			RemoveLandQuestMark_Main(npchar, "PDM_Proklyataya_Jara");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
