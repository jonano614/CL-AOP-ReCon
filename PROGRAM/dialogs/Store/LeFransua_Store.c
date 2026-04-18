// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("LeFransua_Store_3", RandPhraseSimple(
								StringFromKey("LeFransua_Store_1"),
								StringFromKey("LeFransua_Store_2"))),
						StringFromKey("LeFransua_Store_4"),
						StringFromKey("LeFransua_Store_5"),
						StringFromKey("LeFransua_Store_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("LeFransua_Store_9", RandPhraseSimple(
								StringFromKey("LeFransua_Store_7", pchar),
								StringFromKey("LeFransua_Store_8"))),
						StringFromKey("LeFransua_Store_10", pchar),
						StringFromKey("LeFransua_Store_11"),
						StringFromKey("LeFransua_Store_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "KillLoy_toSeek")
			{
				link.l1 = StringFromKey("LeFransua_Store_13");
				link.l1.go = "PL_Q3_1";
			}
		break;
		//пиратка, квест №3, поиски Лоу
		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("LeFransua_Store_14", pchar),
						StringFromKey("LeFransua_Store_15"),
						StringFromKey("LeFransua_Store_16", pchar),
						StringFromKey("LeFransua_Store_17"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("LeFransua_Store_18"),
						StringFromKey("LeFransua_Store_19"),
						StringFromKey("LeFransua_Store_20"),
						StringFromKey("LeFransua_Store_21"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q3_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q3_2":
			dialog.text = StringFromKey("LeFransua_Store_22");
			link.l1 = StringFromKey("LeFransua_Store_23");
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "3");
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
