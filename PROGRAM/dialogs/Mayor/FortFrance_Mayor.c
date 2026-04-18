// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortFrance_Mayor_3", RandPhraseSimple(
								StringFromKey("FortFrance_Mayor_1"),
								StringFromKey("FortFrance_Mayor_2"))),
						StringFromKey("FortFrance_Mayor_4"),
						StringFromKey("FortFrance_Mayor_5"),
						StringFromKey("FortFrance_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortFrance_Mayor_9", RandPhraseSimple(
								StringFromKey("FortFrance_Mayor_7", pchar),
								StringFromKey("FortFrance_Mayor_8"))),
						StringFromKey("FortFrance_Mayor_10"),
						StringFromKey("FortFrance_Mayor_11"),
						StringFromKey("FortFrance_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";

			// Французский сюжет - сдача капитана Black Twister
			if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "FL2_s31" && GetPassengerNumber(pchar, sti(pchar.MainQuest.PtisonIdx)) != -1)
			{
				link.l1 = StringFromKey("FortFrance_Mayor_13");
				link.l1.go = "FL2_1";
			}
		break;

		// Французский сюжет - сдача капитана Black Twister
		case "FL2_1":
			dialog.text = StringFromKey("FortFrance_Mayor_14");
			link.l1 = StringFromKey("FortFrance_Mayor_15");
			link.l1.go = "FL2_2";
		break;

		case "FL2_2":
			dialog.text = StringFromKey("FortFrance_Mayor_16");
			link.l1 = StringFromKey("FortFrance_Mayor_17");
			link.l1.go = "FL2_3";
		break;

		case "FL2_3":
			dialog.text = StringFromKey("FortFrance_Mayor_18");
			link.l1 = StringFromKey("FortFrance_Mayor_19");
			link.l1.go = "FL2_4";

			ReleasePrisoner(GetCharacter(sti(pchar.MainQuest.PtisonIdx)));
			DeleteAttribute(pchar, "MainQuest.PtisonIdx");
			ChangeCharacterAddressGroup(CharacterFromID("FortFrance_usurer"), "none", "", "");
		break;

		case "FL2_4":
			dialog.text = StringFromKey("FortFrance_Mayor_20");
			link.l1 = StringFromKey("FortFrance_Mayor_21");
			link.l1.go = "exit";
			ChangeCharacterNationReputation(pchar, FRANCE, 1);
			AddDialogExitQuest("FL2_s32");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

