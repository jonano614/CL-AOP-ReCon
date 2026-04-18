// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Charles_Tavern_3", RandPhraseSimple(
								StringFromKey("Charles_Tavern_1"),
								StringFromKey("Charles_Tavern_2", GetAddress_Form(NPChar)))),
						StringFromKey("Charles_Tavern_4", GetAddress_Form(NPChar)),
						StringFromKey("Charles_Tavern_5"),
						StringFromKey("Charles_Tavern_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Charles_Tavern_9", RandPhraseSimple(
								StringFromKey("Charles_Tavern_7", pchar),
								StringFromKey("Charles_Tavern_8"))),
						StringFromKey("Charles_Tavern_10"),
						StringFromKey("Charles_Tavern_11"),
						StringFromKey("Charles_Tavern_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.MC == "toSeekSister")
			{
				link.l1 = StringFromKey("Charles_Tavern_13");
				link.l1.go = "MCLiz";
			}
		break;
		case "MCLiz":
			dialog.text = StringFromKey("Charles_Tavern_14");
			link.l1 = StringFromKey("Charles_Tavern_15");
			link.l1.go = "MCLiz_1";
		break;
		case "MCLiz_1":
			dialog.text = StringFromKey("Charles_Tavern_16");
			link.l1 = StringFromKey("Charles_Tavern_17");
			link.l1.go = "MCLiz_2";
		break;
		case "MCLiz_2":
			dialog.text = StringFromKey("Charles_Tavern_18");
			link.l1 = StringFromKey("Charles_Tavern_19");
			link.l1.go = "MCLiz_3";
		break;
		case "MCLiz_3":
			dialog.text = StringFromKey("Charles_Tavern_20");
			link.l1 = StringFromKey("Charles_Tavern_21");
			link.l1.go = "MCLiz_4";
		break;
		case "MCLiz_4":
			dialog.text = StringFromKey("Charles_Tavern_22");
			link.l1 = StringFromKey("Charles_Tavern_23");
			link.l1.go = "MCLiz_5";
		break;
		case "MCLiz_5":
			dialog.text = StringFromKey("Charles_Tavern_24");
			link.l1 = StringFromKey("Charles_Tavern_25");
			link.l1.go = "MCLiz_6";
		break;
		case "MCLiz_6":
			dialog.text = StringFromKey("Charles_Tavern_26");
			link.l1 = StringFromKey("Charles_Tavern_27");
			link.l1.go = "MCLiz_7";
		break;
		case "MCLiz_7":
			dialog.text = StringFromKey("Charles_Tavern_28");
			link.l1 = StringFromKey("Charles_Tavern_29");
			link.l1.go = "MCLiz_8";
		break;
		case "MCLiz_8":
			dialog.text = StringFromKey("Charles_Tavern_30");
			link.l1 = StringFromKey("Charles_Tavern_31");
			link.l1.go = "exit";
			pchar.questTemp.MC = "toSeekSisterAT";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
