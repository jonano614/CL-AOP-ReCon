//HardCoffee диалог с матросом на орудийной палубе
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	sTemp = NPChar.greeting;

	switch (Dialog.CurrentNode)
	{
		case "Gun_deck_sailor":
			switch (sti(strcut(&sTemp, strlen(&sTemp)-5, strlen(&sTemp)-5)))
			{
				case 1:
					dialog.text = StringFromKey("Our_Sailor_1");
					link.l1 = StringFromKey("Our_Sailor_5", LinkRandPhrase(
								StringFromKey("Our_Sailor_2"),
								StringFromKey("Our_Sailor_3"),
								StringFromKey("Our_Sailor_4")));
				break;
				case 2:
					dialog.text = StringFromKey("Our_Sailor_6");
					if (!bMapEnter)
						link.l1 = StringFromKey("Our_Sailor_7");
					else
						link.l1 = StringFromKey("Our_Sailor_8");
				break;
				case 3:
					dialog.text = StringFromKey("Our_Sailor_9");
					link.l1 = StringFromKey("Our_Sailor_10");
				break;

				//pirat_guard_4.WAV and default
				dialog.text = StringFromKey("Our_Sailor_11");
				link.l1 = StringFromKey("Our_Sailor_12", pchar);
				sTemp = GetLastName(NPChar);
				if (sTemp != "")
					link.l1 = StringFromKey("Our_Sailor_13", link.l1, sTemp);
				link.l1 = link.l1 + "!";
			}
			link.l1.go = "exit";
		break;

		case "exit":
			NextDiag.CurrentNode = "Our_sailor";
			NPChar.chr_ai.disableDlg = "1"; //Запретим диалог, чтобы повторно одну и ту же фразу не спамить
			DialogExit();
		break;
	}
}