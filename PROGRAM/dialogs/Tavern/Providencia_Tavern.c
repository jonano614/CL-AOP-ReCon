// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Providencia_Tavern_1", GetCityName(npchar.city)),
						StringFromKey("Providencia_Tavern_2"),
						StringFromKey("Providencia_Tavern_3"),
						StringFromKey("Providencia_Tavern_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Providencia_Tavern_5", NPChar.name),
						StringFromKey("Providencia_Tavern_6", pchar),
						StringFromKey("Providencia_Tavern_7"),
						StringFromKey("Providencia_Tavern_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
