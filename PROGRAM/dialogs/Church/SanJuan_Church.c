// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SanJuan_Church_3", RandPhraseSimple(
								StringFromKey("SanJuan_Church_1", pchar),
								StringFromKey("SanJuan_Church_2"))),
						StringFromKey("SanJuan_Church_4", pchar),
						StringFromKey("SanJuan_Church_5", pchar),
						StringFromKey("SanJuan_Church_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SanJuan_Church_9", RandPhraseSimple(
								StringFromKey("SanJuan_Church_7", pchar),
								StringFromKey("SanJuan_Church_8"))),
						StringFromKey("SanJuan_Church_10"),
						StringFromKey("SanJuan_Church_11"),
						StringFromKey("SanJuan_Church_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//============= Изабелла Росселини ================
			if (CheckAttribute(Pchar, "RomanticQuest.PriestAsk"))
			{
				link.l2 = StringFromKey("SanJuan_Church_13");
				link.l2.go = "Romantic_1";
			}
		break;

		case "Romantic_1":
			dialog.text = StringFromKey("SanJuan_Church_14");
			link.l1 = StringFromKey("SanJuan_Church_15");
			link.l1.go = "exit";
			DeleteAttribute(Pchar, "RomanticQuest.PriestAsk");
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;

		case "Romantic_2":
			dialog.text = StringFromKey("SanJuan_Church_16", GetFullName(pchar));
			link.l1 = StringFromKey("SanJuan_Church_17");
			link.l1.go = "Romantic_3";
		break;
		case "Romantic_3":
			locCameraToPos(3.64, 3.25, -7.84, false);
			LAi_SetActorType(npchar);
			LAi_ActorTurnToLocator(npchar, "goto", "goto5");
			dialog.text = StringFromKey("SanJuan_Church_18", GetMainCharacterNameGen());
			link.l1 = StringFromKey("SanJuan_Church_19");
			link.l1.go = "Romantic_4";
		break;
		case "Romantic_4":
			locCameraToPos(-0.75, 3.85, -10.60, false);
			LAi_SetActorType(npchar);
			LAi_ActorTurnToLocator(npchar, "goto", "goto5");
			dialog.text = StringFromKey("SanJuan_Church_20");
			link.l1 = "...";
			link.l1.go = "Romantic_5";
		break;
		case "Romantic_5":
			dialog.text = StringFromKey("SanJuan_Church_21");
			link.l1 = "...";
			link.l1.go = "exit";
			sld = CharacterFromID("Isabella");
			sld.lastname = pchar.lastname;
			NextDiag.TempNode = "First time";
			AddDialogExitQuest("Romantic_Padre_3");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
