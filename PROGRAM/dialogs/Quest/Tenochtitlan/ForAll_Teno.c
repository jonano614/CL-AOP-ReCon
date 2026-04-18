void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("ForAll_Teno_1");
			link.l1 = StringFromKey("ForAll_Teno_2");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//встреча в бухте с перцем, который валит из Тено
		case "Shore53":
			pchar.defaultanimation = MainChAnim;
			dialog.text = StringFromKey("ForAll_Teno_3", UpperFirst(GetAddress_Form(NPChar)));
			link.l1 = StringFromKey("ForAll_Teno_4");
			link.l1.go = "Shore53_1";
		break;
		case "Shore53_1":
			dialog.text = StringFromKey("ForAll_Teno_5");
			link.l1 = StringFromKey("ForAll_Teno_6");
			link.l1.go = "Shore53_2";
		break;
		case "Shore53_2":
			dialog.text = StringFromKey("ForAll_Teno_7");
			link.l1 = StringFromKey("ForAll_Teno_8");
			link.l1.go = "Shore53_3";
		break;
		case "Shore53_3":
			dialog.text = StringFromKey("ForAll_Teno_9", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("ForAll_Teno_10");
			link.l1.go = "Shore53_4";
		break;
		case "Shore53_4":
			dialog.text = StringFromKey("ForAll_Teno_11", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("ForAll_Teno_12");
			link.l1.go = "Shore53_5";
		break;
		case "Shore53_5":
			dialog.text = StringFromKey("ForAll_Teno_13", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("ForAll_Teno_14");
			link.l1.go = "Shore53_6";
		break;
		case "Shore53_6":
			dialog.text = StringFromKey("ForAll_Teno_15", pchar, GetAddress_Form(NPChar));
			link.l1 = StringFromKey("ForAll_Teno_16");
			link.l1.go = "Shore53_7";
		break;
		case "Shore53_7":
			dialog.text = StringFromKey("ForAll_Teno_17");
			link.l1 = StringFromKey("ForAll_Teno_18");
			link.l1.go = "Shore53_8";
		break;
		case "Shore53_8":
			dialog.text = StringFromKey("ForAll_Teno_19");
			link.l1 = StringFromKey("ForAll_Teno_20");
			link.l1.go = "Shore53_9";
		break;
		case "Shore53_9":
			dialog.text = StringFromKey("ForAll_Teno_21", UpperFirst(GetAddress_Form(NPChar)));
			link.l1 = StringFromKey("ForAll_Teno_22");
			link.l1.go = "Shore53_10";
		break;
		case "Shore53_10":
			dialog.text = StringFromKey("ForAll_Teno_23", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("ForAll_Teno_24");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Teno_startInShore_2");
		break;
	}
}
