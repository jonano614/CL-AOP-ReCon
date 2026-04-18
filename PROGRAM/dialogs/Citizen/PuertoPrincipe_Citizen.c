// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = StringFromKey("PuertoPrincipe_Citizen_3", RandPhraseSimple(
						StringFromKey("PuertoPrincipe_Citizen_1"),
						StringFromKey("PuertoPrincipe_Citizen_2")));
			link.l1 = StringFromKey("PuertoPrincipe_Citizen_6", RandPhraseSimple(
						StringFromKey("PuertoPrincipe_Citizen_4", pchar),
						StringFromKey("PuertoPrincipe_Citizen_5")));
			link.l1.go = "exit";
		break;

		case "info":
		// заменить на описание неких НПС, по квестам
			dialog.text = StringFromKey("PuertoPrincipe_Citizen_7", NationNameGenitive(sti(NPChar.nation)));
			link.l1 = StringFromKey("PuertoPrincipe_Citizen_8");
			link.l1.go = "exit";
			link.l2 = StringFromKey("PuertoPrincipe_Citizen_9");
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

