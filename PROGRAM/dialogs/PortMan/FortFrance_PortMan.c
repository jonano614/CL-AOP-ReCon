// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortFrance_PortMan_3", RandPhraseSimple(
								StringFromKey("FortFrance_PortMan_1"),
								StringFromKey("FortFrance_PortMan_2", GetAddress_Form(NPChar)))),
						StringFromKey("FortFrance_PortMan_4", GetAddress_Form(NPChar)),
						StringFromKey("FortFrance_PortMan_5"),
						StringFromKey("FortFrance_PortMan_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortFrance_PortMan_9", RandPhraseSimple(
								StringFromKey("FortFrance_PortMan_7", pchar),
								StringFromKey("FortFrance_PortMan_8"))),
						StringFromKey("FortFrance_PortMan_10"),
						StringFromKey("FortFrance_PortMan_11"),
						StringFromKey("FortFrance_PortMan_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";

			if (pchar.questTemp.piratesLine == "KillLoy_toSeek")
			{
				link.l1 = StringFromKey("FortFrance_PortMan_13");
				link.l1.go = "PL_Q3_1";
			}
			if (pchar.questTemp.piratesLine == "KillLoy_noMoney")
			{
				link.l1 = StringFromKey("FortFrance_PortMan_14", pchar);
				link.l1.go = "PL_Q3_7";
			}
		break;

		// Французский сюжет ИП
		if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "FL1_s42")
		{
			dialog.text = StringFromKey("FortFrance_PortMan_15");
			link.l1 = StringFromKey("FortFrance_PortMan_16");
			link.l1.go = "FL1";
		}

		/*//пропавший жених служанки ИП
		if(CheckAttribute(pchar, "WaitressHusbent") && pchar.WaitressHusbent == "start")
		{
			link.l1 = "Мсье "+NPChar.name+". Кхм, у меня к вам такой вопрос. Вам что-нибудь известно о судьбе корабля 'Антуанетта', который покинул порт два месяца назад?";
			link.l1.go = "WaitressHusbent_1";
		}
		break;*/

		case "FL1":
			dialog.text = StringFromKey("FortFrance_PortMan_17");
			link.l1 = StringFromKey("FortFrance_PortMan_18");
			link.l1.go = "exit";

			AddDialogExitQuest("FL1_s43");
		break;

		/* //пропавший жених служанки ИП
		case "WaitressHusbent_1":
            dialog.text = "Вы знаете, я не слежу за судьбой каждого корабля, заходящего в порт Фор-де-Франс.";
            link.l1 = " Мсье, этот корабль ходит под флагом Франции и у вас наверняка должны иметься о нём хоть какие-то сведения. Дело в том, что он должен был прибыть ещё две недели назад, а его все нет.";
            link.l1.go = "WaitressHusbent_2";
        break;
        
        case "WaitressHusbent_2":
            dialog.text = "Вы меня заинтриговали, капитан, сейчас посмотрим, что это за судно... Так, да, был такой - флейт 'Антуанетта', капитан Лионель Матис. Стоял в порту с 11 по 23 число позапрошлого месяца. Куда ушёл, не знаю, этот корабль не состоит ни в одной эскадре, но, по-моему, капитан выполняет задания губернатора.";
            link.l1 = "Спасибо за информацию, мсье "+NPChar.name+".";
            link.l1.go = "Exit";
            pchar.WaitressHusbent = "start_1";
            AddQuestRecord("WaitressHusbent", "1");
        break; */

		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortFrance_PortMan_19"),
						StringFromKey("FortFrance_PortMan_20"),
						StringFromKey("FortFrance_PortMan_21"),
						StringFromKey("FortFrance_PortMan_22", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortFrance_PortMan_23"),
						StringFromKey("FortFrance_PortMan_24"),
						StringFromKey("FortFrance_PortMan_25"),
						StringFromKey("FortFrance_PortMan_26"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q3_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q3_2":
			dialog.text = StringFromKey("FortFrance_PortMan_27");
			link.l1 = StringFromKey("FortFrance_PortMan_28");
			link.l1.go = "PL_Q3_out";
			link.l2 = StringFromKey("FortFrance_PortMan_29", pchar);
			link.l2.go = "PL_Q3_3";
		break;

		case "PL_Q3_out":
			dialog.text = StringFromKey("FortFrance_PortMan_30");
			link.l1 = StringFromKey("FortFrance_PortMan_31");
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "6");
			AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("", "а"));
			pchar.questTemp.piratesLine = "KillLoy_notFound";
			QuestSetCurrentNode("Henry Morgan", "PL_Q3_notFound");
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			AddLandQuestmark_Main(CharacterFromID("Henry Morgan"), "Pir_Line");
		break;
		case "PL_Q3_3":
			if (GetCharacterSkill(pchar, "Sneak") >= 60 || GetCharacterSPECIAL(pchar, "Charisma") > 6)
			{
				PlayerRPGCheck_Skill_NotifyPass("Sneak");
				PlayerRPGCheck_SPECIAL_NotifyPass("Charisma");
				dialog.text = StringFromKey("FortFrance_PortMan_32");
				link.l1 = StringFromKey("FortFrance_PortMan_33");
				link.l1.go = "exit";
				AddQuestRecord("Pir_Line_3_KillLoy", "7");
				pchar.questTemp.piratesLine = "KillLoy_toBermudes";
				RemoveLandQuestmark_Main(npchar, "Pir_Line");
				RemoveLandQuestmark_Main(CharacterFromID("LeFransua_tavernkeeper"), "Pir_Line");
				RemoveLandQuestmark_Main(CharacterFromID("LeFransua_trader"), "Pir_Line");
				RemoveLandQuestmark_Main(CharacterFromID("FortFrance_shipyarder"), "Pir_Line");
				RemoveLandQuestmark_Main(CharacterFromID("FortFrance_usurer"), "Pir_Line");
				AddLandQuestmark_Main(CharacterFromID("Pirates_tavernkeeper"), "Pir_Line");
			}
			else
			{
				PlayerRPGCheck_Skill_NotifyFail("Sneak", false);
				PlayerRPGCheck_SPECIAL_NotifyFail("Charisma");
				dialog.text = StringFromKey("FortFrance_PortMan_34");
				link.l1 = StringFromKey("FortFrance_PortMan_35");
				link.l1.go = "PL_Q3_4";
			}
		break;
		case "PL_Q3_4":
			dialog.text = StringFromKey("FortFrance_PortMan_36");
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = StringFromKey("FortFrance_PortMan_37");
				link.l1.go = "PL_Q3_5";
			}
			else
			{
				link.l1 = StringFromKey("FortFrance_PortMan_38");
				link.l1.go = "PL_Q3_6";
			}
		break;
		case "PL_Q3_5":
			dialog.text = StringFromKey("FortFrance_PortMan_39");
			link.l1 = StringFromKey("FortFrance_PortMan_40", pchar);
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "7_1");
			pchar.questTemp.piratesLine = "KillLoy_toBermudes";
			AddMoneyToCharacter(pchar, -15000);
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			RemoveLandQuestmark_Main(CharacterFromID("LeFransua_tavernkeeper"), "Pir_Line");
			RemoveLandQuestmark_Main(CharacterFromID("LeFransua_trader"), "Pir_Line");
			RemoveLandQuestmark_Main(CharacterFromID("FortFrance_shipyarder"), "Pir_Line");
			RemoveLandQuestmark_Main(CharacterFromID("FortFrance_usurer"), "Pir_Line");
			AddLandQuestmark_Main(CharacterFromID("Pirates_tavernkeeper"), "Pir_Line");
		break;
		case "PL_Q3_6":
			dialog.text = StringFromKey("FortFrance_PortMan_41");
			link.l1 = StringFromKey("FortFrance_PortMan_42");
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "8");
			pchar.questTemp.piratesLine = "KillLoy_noMoney";
		break;
		case "PL_Q3_7":
			if (sti(pchar.money) >= 15000)
			{
				dialog.text = StringFromKey("FortFrance_PortMan_43");
				link.l1 = StringFromKey("FortFrance_PortMan_44");
				link.l1.go = "PL_Q3_5";
			}
			else
			{
				dialog.text = StringFromKey("FortFrance_PortMan_45");
				link.l1 = StringFromKey("FortFrance_PortMan_46");
				link.l1.go = "exit";
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
