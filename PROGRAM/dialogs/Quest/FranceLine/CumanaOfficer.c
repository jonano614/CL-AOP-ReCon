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
		case "first time":
			dialog.text = StringFromKey("CumanaOfficer_1");
			link.l1 = StringFromKey("CumanaOfficer_2");
			link.l1.go = "1";
		break;

		case "1":
			dialog.text = StringFromKey("CumanaOfficer_3");
			link.l1 = StringFromKey("CumanaOfficer_4");
			link.l1.go = "exit";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "exit":
			if (CheckAttribute(NextDiag, "TempNode")) NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
