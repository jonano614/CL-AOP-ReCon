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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//------------------------ Мешитли ------------------------
		case "AztecFT":
			dialog.text = StringFromKey("AztecCitizens_1", pchar);
			link.l1 = StringFromKey("AztecCitizens_2", GetFullName(pchar));
			link.l1.go = "AztecFT_1";
		break;
		case "AztecFT_1":
			dialog.text = StringFromKey("AztecCitizens_3");
			link.l1 = StringFromKey("AztecCitizens_4");
			link.l1.go = "AztecFT_2";
		break;
		case "AztecFT_2":
			dialog.text = StringFromKey("AztecCitizens_5");
			link.l1 = StringFromKey("AztecCitizens_6");
			link.l1.go = "AztecFT_3";
		break;
		case "AztecFT_3":
			dialog.text = StringFromKey("AztecCitizens_7");
			link.l1 = StringFromKey("AztecCitizens_8");
			link.l1.go = "AztecFT_4";
		break;
		case "AztecFT_4":
			dialog.text = StringFromKey("AztecCitizens_9");
			link.l1 = StringFromKey("AztecCitizens_10");
			link.l1.go = "AztecFT_5";
		break;
		case "AztecFT_5":
			dialog.text = StringFromKey("AztecCitizens_11", pchar);
			link.l1 = StringFromKey("AztecCitizens_12");
			link.l1.go = "AztecFT_6";
		break;
		case "AztecFT_6":
			dialog.text = StringFromKey("AztecCitizens_13");
			link.l1 = StringFromKey("AztecCitizens_14", pchar);
			link.l1.go = "AztecFT_7";
		break;
		case "AztecFT_7":
			dialog.text = StringFromKey("AztecCitizens_15");
			link.l1 = StringFromKey("AztecCitizens_16", pchar);
			link.l1.go = "AztecFT_8";
		break;
		case "AztecFT_8":
			dialog.text = StringFromKey("AztecCitizens_17");
			link.l1 = StringFromKey("AztecCitizens_18");
			link.l1.go = "AztecFT_9";
		break;
		case "AztecFT_9":
			dialog.text = StringFromKey("AztecCitizens_19");
			link.l1 = StringFromKey("AztecCitizens_20");
			link.l1.go = "AztecFT_10";
		break;
		case "AztecFT_10":
			dialog.text = StringFromKey("AztecCitizens_21", pchar);
			link.l1 = StringFromKey("AztecCitizens_22", pchar);
			link.l1.go = "AztecFT_11";
		break;
		case "AztecFT_11":
			LAi_SetImmortal(npchar, false);
			LAi_SetCitizenType(npchar);
			NextDiag.TempNode = "Aztec1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Aztec1":
			dialog.text = StringFromKey("AztecCitizens_23", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("AztecCitizens_24");
			link.l1.go = "exit";
		break;

		case "Aztec1AF":
			dialog.text = StringFromKey("AztecCitizens_25", pchar);
			link.l1 = StringFromKey("AztecCitizens_26", pchar);
			link.l1.go = "Aztec1AF_1";
		break;
		case "Aztec1AF_1":
			dialog.text = StringFromKey("AztecCitizens_27", pchar);
			link.l1 = StringFromKey("AztecCitizens_28", pchar);
			link.l1.go = "Aztec1AF_2";
		break;
		case "Aztec1AF_2":
			dialog.text = StringFromKey("AztecCitizens_29", pchar);
			link.l1 = StringFromKey("AztecCitizens_30");
			link.l1.go = "Aztec1AF_3";
		break;
		case "Aztec1AF_3":
			dialog.text = StringFromKey("AztecCitizens_31", pchar);
			link.l1 = StringFromKey("AztecCitizens_32");
			link.l1.go = "exit";
			NextDiag.TempNode = "Aztec1";
		break;

		//------------------------ Ауисотль ------------------------
		case "AztecFT2":
			dialog.text = StringFromKey("AztecCitizens_33", pchar);
			link.l1 = StringFromKey("AztecCitizens_34");
			link.l1.go = "AztecFT2_1";
		break;

		case "AztecFT2_1":
			dialog.text = StringFromKey("AztecCitizens_35", pchar);
			link.l1 = StringFromKey("AztecCitizens_36", pchar, GetFullName(pchar));
			link.l1.go = "AztecFT2_2";
		break;
		case "AztecFT2_2":
			dialog.text = StringFromKey("AztecCitizens_37", pchar);
			link.l1 = StringFromKey("AztecCitizens_38");
			link.l1.go = "AztecFT2_3";
		break;
		case "AztecFT2_3":
			dialog.text = StringFromKey("AztecCitizens_39", pchar);
			link.l1 = StringFromKey("AztecCitizens_40");
			link.l1.go = "AztecFT2_4";
		break;
		case "AztecFT2_4":
			dialog.text = StringFromKey("AztecCitizens_41", pchar);
			link.l1 = StringFromKey("AztecCitizens_42");
			link.l1.go = "AztecFT2_5";
		break;
		case "AztecFT2_5":
			dialog.text = StringFromKey("AztecCitizens_43", pchar);
			link.l1 = StringFromKey("AztecCitizens_44");
			link.l1.go = "exit";
			NextDiag.TempNode = "Aztec2";
		break;

		case "Aztec2":
			dialog.text = StringFromKey("AztecCitizens_45", pchar);
			link.l1 = StringFromKey("AztecCitizens_46");
			link.l1.go = "exit";
		break;

		case "Aztec2AF":
			dialog.text = StringFromKey("AztecCitizens_47", pchar);
			link.l1 = StringFromKey("AztecCitizens_48", pchar);
			link.l1.go = "Aztec2AF_1";
		break;
		case "Aztec2AF_1":
			dialog.text = StringFromKey("AztecCitizens_49");
			link.l1 = StringFromKey("AztecCitizens_50", pchar);
			link.l1.go = "Aztec2AF_2";
		break;
		case "Aztec2AF_2":
			dialog.text = StringFromKey("AztecCitizens_51");
			link.l1 = StringFromKey("AztecCitizens_52");
			link.l1.go = "Aztec2AF_3";
		break;
		case "Aztec2AF_3":
			dialog.text = StringFromKey("AztecCitizens_53", pchar);
			link.l1 = StringFromKey("AztecCitizens_54");
			link.l1.go = "exit";
			NextDiag.TempNode = "Aztec2AF_4";
		break;

		case "Aztec2AF_4":
			dialog.text = StringFromKey("AztecCitizens_55", pchar);
			link.l1 = StringFromKey("AztecCitizens_56");
			link.l1.go = "exit";
		break;
	}
}
