// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Havana_Lighthouse_3", RandPhraseSimple(
								StringFromKey("Havana_Lighthouse_1"),
								StringFromKey("Havana_Lighthouse_2"))),
						StringFromKey("Havana_Lighthouse_4", GetAddress_Form(NPChar)),
						StringFromKey("Havana_Lighthouse_5"),
						StringFromKey("Havana_Lighthouse_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Havana_Lighthouse_9", RandPhraseSimple(
								StringFromKey("Havana_Lighthouse_7", pchar),
								StringFromKey("Havana_Lighthouse_8"))),
						StringFromKey("Havana_Lighthouse_10", pchar),
						StringFromKey("Havana_Lighthouse_11"),
						StringFromKey("Havana_Lighthouse_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		/* // калеуче
		if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
		{
			link.l1 = "Послушай, сюда не прибывал человек по имени Жоаким Мерриман? Немолодой сеньор, португалец, носит усы и эспаньолку, с пронзительным взглядом? Может, в бухте высадился, или на маяке? Не видал такого?";
			link.l1.go = "merriman";
		}
		break;

		// калеуче
		case "merriman":
			dialog.text = "Нет, " + GetSexPhrase("дружище", "девушка") + ", не видал. Мне никто такой на глаза не попадался.";
			link.l1 = "Ясно. Жаль. Буду искать дальше...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;*/
	}
	UnloadSegment(NPChar.FileDialog2);
}


