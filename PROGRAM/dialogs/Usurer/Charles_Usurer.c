// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Charles_Usurer_3", RandPhraseSimple(
								StringFromKey("Charles_Usurer_1"),
								StringFromKey("Charles_Usurer_2"))),
						StringFromKey("Charles_Usurer_4"),
						StringFromKey("Charles_Usurer_5"),
						StringFromKey("Charles_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Charles_Usurer_9", RandPhraseSimple(
								StringFromKey("Charles_Usurer_7", pchar),
								StringFromKey("Charles_Usurer_8"))),
						StringFromKey("Charles_Usurer_10"),
						StringFromKey("Charles_Usurer_11"),
						StringFromKey("Charles_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Квест Аззи
			if (CheckAttribute(pchar, "questTemp.Azzy.GiveMoney"))
			{
				link.l5 = StringFromKey("Charles_Usurer_13", pchar);
				link.l5.go = "Step_Az_1";
			}
			if (!CheckAttribute(pchar, "questTemp.Azzy.GiveMoney") && pchar.questTemp.Azzy == "HowToKnowAzzy")
			{
				link.l5 = StringFromKey("Charles_Usurer_14");
				link.l5.go = "Step_Az_4";
			}
		break;
		// ==> Квест Аззи. Дача трёх лимонов ГГ по поручению Аззи.
		case "Step_Az_1":
			dialog.text = StringFromKey("Charles_Usurer_15", GetAddress_Form(NPChar));
			Link.l1 = StringFromKey("Charles_Usurer_16");
			Link.l1.go = "Step_Az_2";
		break;
		case "Step_Az_2":
			dialog.text = StringFromKey("Charles_Usurer_17", GetAddress_Form(NPChar));
			Link.l1 = StringFromKey("Charles_Usurer_18");
			Link.l1.go = "Step_Az_3";
			DeleteAttribute(pchar, "questTemp.Azzy.GiveMoney");
			AddMoneyToCharacter(pchar, 3000000);
			RemoveLandQuestmark_Main(npchar, "Azzy_Wishes");
		break;
		case "Step_Az_3":
			dialog.text = StringFromKey("Charles_Usurer_19", UpperFirst(GetAddress_Form(NPChar)));
			Link.l1 = StringFromKey("Charles_Usurer_20");
			Link.l1.go = "exit";
		break;
		case "Step_Az_4":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Charles_Usurer_21"),
						StringFromKey("Charles_Usurer_22"),
						StringFromKey("Charles_Usurer_23"),
						StringFromKey("Charles_Usurer_24"), "block", 0, npchar, Dialog.CurrentNode);
			Link.l1 = HeroStringReactionRepeat(
						StringFromKey("Charles_Usurer_25"),
						StringFromKey("Charles_Usurer_26"),
						StringFromKey("Charles_Usurer_27"),
						StringFromKey("Charles_Usurer_28"), npchar, Dialog.CurrentNode);
			Link.l1.go = DialogGoNodeRepeat("Step_Az_5", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_Az_5":
			dialog.text = StringFromKey("Charles_Usurer_29");
			Link.l1 = StringFromKey("Charles_Usurer_30");
			Link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
