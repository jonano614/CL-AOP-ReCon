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
			dialog.text = StringFromKey("Mictlantecuhtli_1");
			link.l1 = StringFromKey("Mictlantecuhtli_2");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//должок ростовщика ГПК
		case "ClimeUsurer":
			dialog.text = StringFromKey("Mictlantecuhtli_3", pchar);
			link.l1 = StringFromKey("Mictlantecuhtli_4", pchar);
			link.l1.go = "ClimeUsurer_1";
		break;
		case "ClimeUsurer_1":
			dialog.text = StringFromKey("Mictlantecuhtli_5", pchar, FindMoneyString(sti(pchar.questTemp.LSC_climeUsurer.qtyMoney)));
			if (sti(pchar.money) >= sti(pchar.questTemp.LSC_climeUsurer.qtyMoney))
			{
				link.l1 = StringFromKey("Mictlantecuhtli_6");
				link.l1.go = "ClimeUsurer_yes";
			}
			else
			{
				link.l1 = StringFromKey("Mictlantecuhtli_7", pchar);
				link.l1.go = "ClimeUsurer_no";
			}
		break;
		case "ClimeUsurer_yes":
			dialog.text = StringFromKey("Mictlantecuhtli_8");
			link.l1 = StringFromKey("Mictlantecuhtli_9");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.LSC_climeUsurer.qtyMoney));
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("ClimeUsurer_haveMoney");
		break;
		case "ClimeUsurer_no":
			dialog.text = StringFromKey("Mictlantecuhtli_10", pchar);
			link.l1 = StringFromKey("Mictlantecuhtli_11");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClimeUsurer_noMoney");
		break;

		//в большом храме разговор перед боевкой
		case "InGreateTemple":
			dialog.text = StringFromKey("Mictlantecuhtli_12", pchar);
			link.l1 = StringFromKey("Mictlantecuhtli_13");
			link.l1.go = "InGreateTemple_1";
		break;
		case "InGreateTemple_1":
			dialog.text = StringFromKey("Mictlantecuhtli_14", pchar);
			link.l1 = StringFromKey("Mictlantecuhtli_15");
			link.l1.go = "InGreateTemple_2";
		break;
		case "InGreateTemple_2":
			dialog.text = StringFromKey("Mictlantecuhtli_16", pchar);
			link.l1 = StringFromKey("Mictlantecuhtli_17", pchar);
			link.l1.go = "InGreateTemple_3";
		break;
		case "InGreateTemple_3":
			dialog.text = StringFromKey("Mictlantecuhtli_18");
			link.l1 = StringFromKey("Mictlantecuhtli_19");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Teno_fightInTemple");
		break;

		//в большом храме разговор после боевки
		case "WinInTemple":
			dialog.text = StringFromKey("Mictlantecuhtli_20", pchar);
			link.l1 = StringFromKey("Mictlantecuhtli_21");
			link.l1.go = "WinInTemple_1";
		break;
		case "WinInTemple_1":
			AddItemLog(PChar, "recipe_bullet_colt,recipe_GunPowder_colt", "1", XI_ConvertString("You take item") + ": " + GetItemName("recipe_bullet_colt") + "&" + XI_ConvertString("You take item") + ": " + GetItemName("recipe_GunPowder_colt"), "Important_item");
			dialog.text = StringFromKey("Mictlantecuhtli_22", pchar);
			link.l1 = StringFromKey("Mictlantecuhtli_23");
			link.l1.go = "WinInTemple_2";
		break;
		case "WinInTemple_2":
			dialog.text = StringFromKey("Mictlantecuhtli_24");
			link.l1 = StringFromKey("Mictlantecuhtli_25");
			link.l1.go = "WinInTemple_3";
		break;
		case "WinInTemple_3":
			dialog.text = StringFromKey("Mictlantecuhtli_26");
			link.l1 = StringFromKey("Mictlantecuhtli_27");
			link.l1.go = "WinInTemple_4";
		break;
		case "WinInTemple_4":
			dialog.text = StringFromKey("Mictlantecuhtli_28");
			link.l1 = StringFromKey("Mictlantecuhtli_29");
			link.l1.go = "WinInTemple_5";
		break;
		case "WinInTemple_5":
			dialog.text = StringFromKey("Mictlantecuhtli_30");
			link.l1 = StringFromKey("Mictlantecuhtli_31");
			link.l1.go = "WinInTemple_6";
		break;
		case "WinInTemple_6":
			chrDisableReloadToLocation = false;
			ChangeCharacterAddress(npchar, "none", "");
			AddQuestRecord("TenochtitlanQuest", "4");
			AddQuestUserData("TenochtitlanQuest", "sSex", GetSexPhrase("", "а"));
			DialogExit();
		break;
	}
}
