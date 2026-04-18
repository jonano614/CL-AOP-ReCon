// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Maracaibo_Tavern_3", RandPhraseSimple(
								StringFromKey("Maracaibo_Tavern_1"),
								StringFromKey("Maracaibo_Tavern_2", GetAddress_Form(NPChar)))),
						StringFromKey("Maracaibo_Tavern_4", GetAddress_Form(NPChar)),
						StringFromKey("Maracaibo_Tavern_5"),
						StringFromKey("Maracaibo_Tavern_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Maracaibo_Tavern_9", RandPhraseSimple(
								StringFromKey("Maracaibo_Tavern_7", pchar),
								StringFromKey("Maracaibo_Tavern_8"))),
						StringFromKey("Maracaibo_Tavern_10"),
						StringFromKey("Maracaibo_Tavern_11"),
						StringFromKey("Maracaibo_Tavern_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.MC == "toMaracaibo")
			{
				link.l1 = StringFromKey("Maracaibo_Tavern_13", pchar);
				link.l1.go = "MCTavernMar";
			}
		break;
		//зачарованный город
		case "MCTavernMar":
			dialog.text = StringFromKey("Maracaibo_Tavern_14");
			link.l1 = StringFromKey("Maracaibo_Tavern_15");
			link.l1.go = "MCTavernMar_1";
		break;
		case "MCTavernMar_1":
			dialog.text = StringFromKey("Maracaibo_Tavern_16");
			link.l1 = StringFromKey("Maracaibo_Tavern_17");
			link.l1.go = "MCTavernMar_2";
		break;
		case "MCTavernMar_2":
			dialog.text = StringFromKey("Maracaibo_Tavern_18");
			link.l1 = StringFromKey("Maracaibo_Tavern_19");
			link.l1.go = "exit";
			pchar.questTemp.MC = "toDesMoines";
			RemoveLandQuestMark_Main(npchar, "MagicCity");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
