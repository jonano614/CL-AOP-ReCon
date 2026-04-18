// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SanJuan_Mayor_3", RandPhraseSimple(
								StringFromKey("SanJuan_Mayor_1"),
								StringFromKey("SanJuan_Mayor_2"))),
						StringFromKey("SanJuan_Mayor_4"),
						StringFromKey("SanJuan_Mayor_5"),
						StringFromKey("SanJuan_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SanJuan_Mayor_9", RandPhraseSimple(
								StringFromKey("SanJuan_Mayor_7", pchar),
								StringFromKey("SanJuan_Mayor_8"))),
						StringFromKey("SanJuan_Mayor_10"),
						StringFromKey("SanJuan_Mayor_11"),
						StringFromKey("SanJuan_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "RomanticQuest.MayorOk"))
			{
				link.l1 = StringFromKey("SanJuan_Mayor_13", UpperFirst(GetAddress_FormToNPC(NPChar)), GetFullName(pchar));
				link.l1.go = "Romantic_1";
			}
		break;
		case "Romantic_1":
			dialog.text = StringFromKey("SanJuan_Mayor_14");
			link.l1 = StringFromKey("SanJuan_Mayor_15", UpperFirst(GetAddress_FormToNPC(NPChar)), npchar.lastname);
			link.l1.go = "Romantic_2";
		break;
		case "Romantic_2":
			dialog.text = StringFromKey("SanJuan_Mayor_16");
			link.l1 = StringFromKey("SanJuan_Mayor_17", UpperFirst(GetAddress_FormToNPC(NPChar)));
			link.l1.go = "Romantic_3";
		break;
		case "Romantic_3":
			dialog.text = StringFromKey("SanJuan_Mayor_18");
			link.l1 = StringFromKey("SanJuan_Mayor_19", GetAddress_FormToNPC(NPChar));
			link.l1.go = "Romantic_4";
		break;
		case "Romantic_4":
			dialog.text = StringFromKey("SanJuan_Mayor_20");
			link.l1 = StringFromKey("SanJuan_Mayor_21", GetAddress_FormToNPC(NPChar));
			link.l1.go = "Romantic_5";
		break;
		case "Romantic_5":
			dialog.text = StringFromKey("SanJuan_Mayor_22");
			link.l1 = StringFromKey("SanJuan_Mayor_23", UpperFirst(GetAddress_FormToNPC(NPChar)));
			link.l1.go = "Romantic_6";
		break;
		case "Romantic_6":
			dialog.text = StringFromKey("SanJuan_Mayor_24");
			link.l1 = StringFromKey("SanJuan_Mayor_25", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit";
			AddQuestRecord("Romantic_Line", "27");
			DeleteAttribute(pchar, "RomanticQuest.MayorOk");
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false); //и только теперь открываем дверь в дом Изабеллы
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

