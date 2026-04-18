// НПС офиса ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("HWIC_Office_1");
			link.l1 = StringFromKey("HWIC_Office_2");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		// солдаты
		case "HWIC_soldier":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = StringFromKey("HWIC_Office_3");
				link.l1 = StringFromKey("HWIC_Office_4");
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = StringFromKey("HWIC_Office_5", pchar);
				link.l1 = StringFromKey("HWIC_Office_6");
				link.l1.go = "fight";
				break;
			}
			dialog.text = StringFromKey("HWIC_Office_7");
			link.l1 = StringFromKey("HWIC_Office_8", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_soldier";
		break;

		// клерки
		case "HWIC_clerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = StringFromKey("HWIC_Office_9");
				link.l1 = StringFromKey("HWIC_Office_10");
				link.l1.go = "fight";
				break;
			}
			dialog.text = StringFromKey("HWIC_Office_11");
			link.l1 = StringFromKey("HWIC_Office_12", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_clerk";
		break;

		// главный клерк - минхер Герритц
		case "HWIC_headclerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = StringFromKey("HWIC_Office_13", pchar);
				link.l1 = StringFromKey("HWIC_Office_14");
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = StringFromKey("HWIC_Office_15", pchar);
				link.l1 = StringFromKey("HWIC_Office_16");
				link.l1.go = "fight";
				break;
			}
			dialog.text = StringFromKey("HWIC_Office_17", GetAddress_Form(NPChar));
			link.l9 = StringFromKey("HWIC_Office_18");
			link.l9.go = "exit";
			NextDiag.TempNode = "HWIC_headclerk";
		break;

		case "fight":
			DialogExit();
			for (i = 1; i <= 6; i++)
			{
				sld = characterFromId("HWIC_sold_" + i);
				LAi_group_Attack(sld, Pchar);
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}