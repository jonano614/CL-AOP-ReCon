// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PuertoPrincipe_Tavern_3", RandPhraseSimple(
								StringFromKey("PuertoPrincipe_Tavern_1"),
								StringFromKey("PuertoPrincipe_Tavern_2", GetAddress_Form(NPChar)))),
						StringFromKey("PuertoPrincipe_Tavern_4", GetAddress_Form(NPChar)),
						StringFromKey("PuertoPrincipe_Tavern_5"),
						StringFromKey("PuertoPrincipe_Tavern_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PuertoPrincipe_Tavern_9", RandPhraseSimple(
								StringFromKey("PuertoPrincipe_Tavern_7", pchar),
								StringFromKey("PuertoPrincipe_Tavern_8"))),
						StringFromKey("PuertoPrincipe_Tavern_10"),
						StringFromKey("PuertoPrincipe_Tavern_11"),
						StringFromKey("PuertoPrincipe_Tavern_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "Soukins_toPuertoPrincipe")
			{
				link.l1 = StringFromKey("PuertoPrincipe_Tavern_13");
				link.l1.go = "PL_Q7_1";
			}
			switch (pchar.MainQuest)
			{
				/* case "FindZags":	// голландский сюжет
					link.l1 = "Я ищу человека, его имя Фернандо Загс, говорят, он остановился у тебя в таверне.";
                    link.l1.go = "FindZags_1";
				break;*/

				case "FL2_s10":
					link.l1 = StringFromKey("PuertoPrincipe_Tavern_14");
					link.l1.go = "FL2_1";
				break;
			}
		break;

		case "FL2_1":
			dialog.text = StringFromKey("PuertoPrincipe_Tavern_15");
			link.l1 = StringFromKey("PuertoPrincipe_Tavern_16");
			link.l1.go = "exit";

			AddDialogExitQuest("FL2_s11");
		break;

		//пиратка, квест №7, попытка узнать о планах Соукинса
		case "PL_Q7_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PuertoPrincipe_Tavern_17"),
						StringFromKey("PuertoPrincipe_Tavern_18"),
						StringFromKey("PuertoPrincipe_Tavern_19"),
						StringFromKey("PuertoPrincipe_Tavern_20"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PuertoPrincipe_Tavern_21"),
						StringFromKey("PuertoPrincipe_Tavern_22"),
						StringFromKey("PuertoPrincipe_Tavern_23"),
						StringFromKey("PuertoPrincipe_Tavern_24"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q7_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q7_2":
			dialog.text = StringFromKey("PuertoPrincipe_Tavern_25");
			link.l1 = StringFromKey("PuertoPrincipe_Tavern_26");
			link.l1.go = "PL_Q7_3";
		break;
		case "PL_Q7_3":
			dialog.text = StringFromKey("PuertoPrincipe_Tavern_27", pchar);
			link.l1 = StringFromKey("PuertoPrincipe_Tavern_28");
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
