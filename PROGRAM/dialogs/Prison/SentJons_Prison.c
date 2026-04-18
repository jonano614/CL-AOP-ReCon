// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = StringFromKey("SentJons_Prison_1");
			link.l1 = StringFromKey("SentJons_Prison_2", pchar);
			link.l1.go = "Exit";
			// ==> Проверяем поле состояния квестов.
			if (pchar.questTemp.State == "WormEnglPlans_SaveOfficer")   // разговор по квест №3 голландской линейке.
			{
				link.l2 = StringFromKey("SentJons_Prison_3");
				link.l2.go = "Step_H3_1";
			}
		// <== Проверяем поле состояния квестов.
		break;

		case "Step_H3_1":
			dialog.text = StringFromKey("SentJons_Prison_4");
			link.l1 = StringFromKey("SentJons_Prison_5");
			link.l1.go = "fight";
			RemoveLandQuestmarkToFantoms_Main("JailOff", "Hol_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
