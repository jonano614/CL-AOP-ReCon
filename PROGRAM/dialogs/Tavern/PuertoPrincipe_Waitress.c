// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PuertoPrincipe_Waitress_3", RandPhraseSimple(
								StringFromKey("PuertoPrincipe_Waitress_1", GetAddress_Form(NPChar)),
								StringFromKey("PuertoPrincipe_Waitress_2", GetAddress_Form(NPChar)))),
						StringFromKey("PuertoPrincipe_Waitress_4", GetAddress_Form(NPChar)),
						StringFromKey("PuertoPrincipe_Waitress_5"),
						StringFromKey("PuertoPrincipe_Waitress_6", GetAddress_Form(NPChar)), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PuertoPrincipe_Waitress_9", RandPhraseSimple(
								StringFromKey("PuertoPrincipe_Waitress_7"),
								StringFromKey("PuertoPrincipe_Waitress_8"))),
						StringFromKey("PuertoPrincipe_Waitress_10"),
						StringFromKey("PuertoPrincipe_Waitress_11"),
						StringFromKey("PuertoPrincipe_Waitress_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "Soukins_toPuertoPrincipe")
			{
				link.l1 = StringFromKey("PuertoPrincipe_Waitress_13", pchar);
				link.l1.go = "PL_Q7_1";
			}
			if (pchar.questTemp.piratesLine == "Soukins_seekRings" && CheckCharacterItem(pchar, "jewelry18") && CheckCharacterItem(pchar, "jewelry7"))
			{
				link.l1 = StringFromKey("PuertoPrincipe_Waitress_14", pchar);
				link.l1.go = "PL_Q7_3";
			}
		break;
		case "PL_Q7_1":
			dialog.text = StringFromKey("PuertoPrincipe_Waitress_15");
			link.l1 = StringFromKey("PuertoPrincipe_Waitress_16");
			link.l1.go = "PL_Q7_2";
			pchar.questTemp.piratesLine = "Soukins_seekRings";
			RemoveLandQuestmark_Main(CharacterFromID("PuertoPrincipe_tavernkeeper"), "Pir_Line");
			if (CheckCharacterItem(pchar, "jewelry18") && CheckCharacterItem(pchar, "jewelry7"))
			{
				link.l2 = StringFromKey("PuertoPrincipe_Waitress_17");
				link.l2.go = "PL_Q7_3";
			}
		break;
		case "PL_Q7_2":
			dialog.text = StringFromKey("PuertoPrincipe_Waitress_18");
			link.l1 = StringFromKey("PuertoPrincipe_Waitress_19");
			link.l1.go = "exit";
		break;
		case "PL_Q7_3":
			dialog.text = StringFromKey("PuertoPrincipe_Waitress_20", pchar);
			link.l1 = StringFromKey("PuertoPrincipe_Waitress_21");
			link.l1.go = "PL_Q7_4";
			TakeItemFromCharacter(pchar, "jewelry7");
			TakeItemFromCharacter(pchar, "jewelry18");
		break;
		case "PL_Q7_4":
			dialog.text = StringFromKey("PuertoPrincipe_Waitress_22");
			link.l1 = StringFromKey("PuertoPrincipe_Waitress_23");
			link.l1.go = "PL_Q7_5";
		break;
		case "PL_Q7_5":
			dialog.text = StringFromKey("PuertoPrincipe_Waitress_24");
			link.l1 = StringFromKey("PuertoPrincipe_Waitress_25");
			link.l1.go = "PL_Q7_6";
		break;
		case "PL_Q7_6":
			dialog.text = StringFromKey("PuertoPrincipe_Waitress_26");
			link.l1 = StringFromKey("PuertoPrincipe_Waitress_27");
			link.l1.go = "PL_Q7_7";
		break;
		case "PL_Q7_7":
			dialog.text = StringFromKey("PuertoPrincipe_Waitress_28");
			link.l1 = StringFromKey("PuertoPrincipe_Waitress_29");
			link.l1.go = "PL_Q7_8";
		break;
		case "PL_Q7_8":
			dialog.text = StringFromKey("PuertoPrincipe_Waitress_30");
			link.l1 = StringFromKey("PuertoPrincipe_Waitress_31");
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "Soukins_toWindow";
			// указатель на лестницу
			sld = ItemsFromID("Ladder");
			if (sti(sld.shown) && !CheckAttribute(sld, "shown.used"))
			{
				QuestPointerToLoc(sld.startLocation, "item", sld.startLocator);
			}

			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
