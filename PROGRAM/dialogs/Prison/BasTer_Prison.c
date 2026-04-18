// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = StringFromKey("BasTer_Prison_1");
			link.l1 = StringFromKey("BasTer_Prison_2", pchar);
			link.l1.go = "Exit";
			if (CheckAttribute(pchar, "questTemp.Tichingitu") && pchar.questTemp.Tichingitu == "true")
			{
				link.l1 = StringFromKey("BasTer_Prison_3");
				link.l1.go = "Tichingitu";
			}
			if (CheckAttribute(pchar, "questTemp.Tichingitu") && pchar.questTemp.Tichingitu == "commandante")
			{
				link.l1 = StringFromKey("BasTer_Prison_4");
				link.l1.go = "Tichingitu_3";
			}
			if (CheckAttribute(pchar, "questTemp.Tichingitu") && pchar.questTemp.Tichingitu == "pay")
			{
				link.l1 = StringFromKey("BasTer_Prison_5");
				link.l1.go = "Tichingitu_6";
			}
		break;

		case "Tichingitu":
			dialog.text = StringFromKey("BasTer_Prison_6", pchar);
			link.l1 = StringFromKey("BasTer_Prison_7");
			link.l1.go = "Tichingitu_1";
		break;

		case "Tichingitu_1":
			dialog.text = StringFromKey("BasTer_Prison_8");
			link.l1 = StringFromKey("BasTer_Prison_9");
			link.l1.go = "Tichingitu_2";
		break;

		case "Tichingitu_2":
			DialogExit();
			pchar.questTemp.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
		break;

		case "Tichingitu_3":
			dialog.text = StringFromKey("BasTer_Prison_10");
			link.l1 = StringFromKey("BasTer_Prison_11");
			link.l1.go = "Tichingitu_4";
		break;

		case "Tichingitu_4":
			dialog.text = StringFromKey("BasTer_Prison_12", pchar);
			link.l1 = StringFromKey("BasTer_Prison_13", pchar);
			link.l1.go = "Tichingitu_5";
		break;

		case "Tichingitu_5":
			DialogExit();
			pchar.questTemp.Tichingitu = "ascold";
		break;

		case "Tichingitu_6":
			RemoveItems(pchar, "letter_A", 1);
			dialog.text = StringFromKey("BasTer_Prison_14");
			link.l1 = StringFromKey("BasTer_Prison_15");
			link.l1.go = "Tichingitu_7";
		break;

		case "Tichingitu_7":
			DialogExit();
			pchar.questTemp.Tichingitu = "wait";
			pchar.questTemp.jailCanMove = true;
			ref sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_6";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
