// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Cartahena_Tavern_1", GetCityName(npchar.city)),
						StringFromKey("Cartahena_Tavern_2"),
						StringFromKey("Cartahena_Tavern_3"),
						StringFromKey("Cartahena_Tavern_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Cartahena_Tavern_5", NPChar.name),
						StringFromKey("Cartahena_Tavern_6", pchar),
						StringFromKey("Cartahena_Tavern_7"),
						StringFromKey("Cartahena_Tavern_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
