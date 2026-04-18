// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Beliz_Tavern_1", GetCityName(npchar.city)),
						StringFromKey("Beliz_Tavern_2"),
						StringFromKey("Beliz_Tavern_3"),
						StringFromKey("Beliz_Tavern_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Beliz_Tavern_5", NPChar.name),
						StringFromKey("Beliz_Tavern_6", pchar),
						StringFromKey("Beliz_Tavern_7"),
						StringFromKey("Beliz_Tavern_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
			{
				dialog.text = StringFromKey("Beliz_Tavern_9", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Beliz_Tavern_10", pchar);
				link.l1.go = "Step_F7_1";
			}
		break;
		//******************** Фр.линейка, квест №7. Спасение Рока Бразильца ******************
		case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Beliz_Tavern_11", GetAddress_Form(NPChar)),
						StringFromKey("Beliz_Tavern_12"),
						StringFromKey("Beliz_Tavern_13"),
						StringFromKey("Beliz_Tavern_14"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Beliz_Tavern_15"),
						StringFromKey("Beliz_Tavern_16", pchar),
						StringFromKey("Beliz_Tavern_17", pchar),
						StringFromKey("Beliz_Tavern_18"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F7_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_F7_2":
			dialog.text = StringFromKey("Beliz_Tavern_19", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Beliz_Tavern_20");
			link.l1.go = "Step_F7_3";
		break;
		case "Step_F7_3":
			dialog.text = StringFromKey("Beliz_Tavern_21", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Beliz_Tavern_22");
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
