void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);

	switch (Dialog.CurrentNode)
	{
		case "exit_HideBlade":
			if (CheckAttribute(NPChar, "IWantAskYou") && sti(NPChar.nation) != PIRATE) NPChar.WhoAreYou = "1";
			ExitNotBladeDialog(NPChar);
			SendMessage(pchar, "lsl", MSG_CHARACTER_EX_MSG, "SetFightMode", 1);
			LAi_SetFightMode(pchar, false);
			return;
		break;
		case "exit_NoHideBlade":
			if (sti(NPChar.nation) == PIRATE) TEV.checkPirateNoBlade = 120.0;

			if (NPChar.chr_ai.type == LAI_TYPE_GUARDIAN) NPChar.chr_ai.type.checkGuard = 15.0;
			else if (NPChar.chr_ai.type == LAI_TYPE_PATROL)
			{
				LAi_type_patrol_Goto(NPChar);
				NPChar.chr_ai.type.checkPatrol = 15.0;
			}
			else NPChar.chr_ai.type.checkFight = 15.0;

			if (sti(NPChar.nation) != PIRATE) ChangeCharacterReputation(pchar, -1.0);
			//if (NPChar.dialog.Base_Filename == "Population\Monk.c" && CheckAttribute(NPChar, "quest.capellan"))
			//DeleteAttribute(NPChar, "quest.capellan"); //Если оскорбили капелана - он откажется идти на корабль к гг
			ExitNotBladeDialog(NPChar);
			if (!LAi_IsSetBale(NPChar)) TEV.ChrAfraidIdx = NPChar.index;
			Lai_MethodDelay("ExitNoHideBlade", 0.35);
			return;
		break;
		case "exit_FightBlade":
			if (sti(NPChar.nation) != PIRATE && CheckAttribute(&TEV, "CitizenFightBlade"))
				ChangeCharacterReputation(pchar, -10.0);
			ExitNotBladeDialog(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			Lai_MethodDelay("ExitNoHideBlade", 0.35);
			return;
		break;
	}

	// возвращаю оригинальные диалоги -->
	switch (NPChar.dialog.Base_Filename)
	{
		case "Common_Soldier.c":
			if (sti(NPChar.nation) == PIRATE) Dialog.CurrentNode = "PirateNotBlade";
			else Dialog.CurrentNode = "TownNotBlade";
		break;
		case "Common_Fort.c": Dialog.CurrentNode = "FortNotBlade"; break;
		case "Quest\MagicCity.c": Dialog.CurrentNode = "MagicCityNotBlade"; break;
		case "Officer_Girl.c": Dialog.CurrentNode = "OfficerNotBlade"; break;
		case "Officer_Man.c": Dialog.CurrentNode = "OfficerNotBlade"; break;
		case "Officer_Mush.c": Dialog.CurrentNode = "OfficerNotBlade"; break;
	}

	dialog.text = StringFromKey("Common_NotBlade_1");
	Link.l1 = StringFromKey("Common_NotBlade_2");
	Link.l2 = StringFromKey("Common_NotBlade_3");
	Link.l1.go = "exit_HideBlade";
	Link.l2.go = "exit_FightBlade";

	switch (Dialog.CurrentNode)
	{
		case "TownNotBlade":
			if (isDay()) LAi_CharacterPlaySound(NPChar, "sold_weapon_off");
			dialog.text = StringFromKey("Common_NotBlade_7", LinkRandPhrase(
						StringFromKey("Common_NotBlade_4"),
						StringFromKey("Common_NotBlade_5"),
						StringFromKey("Common_NotBlade_6", GetAddress_Form(NPChar))));

			link.l1 = StringFromKey("Common_NotBlade_11", LinkRandPhrase(
						StringFromKey("Common_NotBlade_8"),
						StringFromKey("Common_NotBlade_9", pchar),
						StringFromKey("Common_NotBlade_10")));
			link.l2 = StringFromKey("Common_NotBlade_15", LinkRandPhrase(
						StringFromKey("Common_NotBlade_12"),
						StringFromKey("Common_NotBlade_13"),
						StringFromKey("Common_NotBlade_14")));
			link.l1.go = "exit_HideBlade";
			link.l2.go = "exit_FightBlade";
		break;

		case "FortNotBlade":
			LAi_CharacterPlaySound(NPChar, "sold_weapon_off");
			dialog.text = StringFromKey("Common_NotBlade_19", LinkRandPhrase(
						StringFromKey("Common_NotBlade_16"),
						StringFromKey("Common_NotBlade_17"),
						StringFromKey("Common_NotBlade_18", pchar)));

			link.l1 = StringFromKey("Common_NotBlade_23", LinkRandPhrase(
						StringFromKey("Common_NotBlade_20"),
						StringFromKey("Common_NotBlade_21"),
						StringFromKey("Common_NotBlade_22")));
			link.l2 = StringFromKey("Common_NotBlade_27", LinkRandPhrase(
						StringFromKey("Common_NotBlade_24"),
						StringFromKey("Common_NotBlade_25"),
						StringFromKey("Common_NotBlade_26")));
			link.l1.go = "exit_HideBlade";
			link.l2.go = "exit_FightBlade";
		break;

		case "MagicCityNotBlade":
			dialog.text = StringFromKey("Common_NotBlade_28");
			link.l1 = StringFromKey("Common_NotBlade_32", LinkRandPhrase(
						StringFromKey("Common_NotBlade_29"),
						StringFromKey("Common_NotBlade_30"),
						StringFromKey("Common_NotBlade_31")));
			link.l1.go = "exit_HideBlade";
		break;

		case "PirateNotBlade":
			dialog.text = StringFromKey("Common_NotBlade_33", npchar);
			link.l1 = StringFromKey("Common_NotBlade_36", RandPhraseSimple(
						StringFromKey("Common_NotBlade_34", pchar),
						StringFromKey("Common_NotBlade_35")));
			link.l2 = StringFromKey("Common_NotBlade_40", LinkRandPhrase(
						StringFromKey("Common_NotBlade_37"),
						StringFromKey("Common_NotBlade_38"),
						StringFromKey("Common_NotBlade_39")));
			link.l3 = StringFromKey("Common_NotBlade_44", LinkRandPhrase(
						StringFromKey("Common_NotBlade_41"),
						StringFromKey("Common_NotBlade_42"),
						StringFromKey("Common_NotBlade_43")));
			link.l1.go = "exit_HideBlade";
			link.l2.go = "exit_NoHideBlade";
			link.l3.go = "exit_FightBlade";
		break;

		case "CitizenNotBlade": //Гражданские
			TEV.CitizenFightBlade = "1"; //Чтобы не объявлять глобальную
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("Common_NotBlade_45", npchar);
				link.l1 = StringFromKey("Common_NotBlade_49", LinkRandPhrase(
							StringFromKey("Common_NotBlade_46"),
							StringFromKey("Common_NotBlade_47"),
							StringFromKey("Common_NotBlade_48")));
			}
			else
			{
				dialog.text = StringFromKey("Common_NotBlade_50", npchar);
				link.l1 = StringFromKey("Common_NotBlade_53", RandPhraseSimple(
							StringFromKey("Common_NotBlade_51", pchar),
							StringFromKey("Common_NotBlade_52")));
			}
			link.l2 = StringFromKey("Common_NotBlade_57", LinkRandPhrase(
						StringFromKey("Common_NotBlade_54"),
						StringFromKey("Common_NotBlade_55"),
						StringFromKey("Common_NotBlade_56")));
			link.l3 = StringFromKey("Common_NotBlade_61", LinkRandPhrase(
						StringFromKey("Common_NotBlade_58"),
						StringFromKey("Common_NotBlade_59"),
						StringFromKey("Common_NotBlade_60")));
			link.l1.go = "exit_HideBlade";
			link.l2.go = "exit_NoHideBlade";
			link.l3.go = "exit_FightBlade";
		break;

		case "OfficerNotBlade":
			dialog.text = StringFromKey("Common_NotBlade_62");
			link.l1 = StringFromKey("Common_NotBlade_66", LinkRandPhrase(
						StringFromKey("Common_NotBlade_63"),
						StringFromKey("Common_NotBlade_64"),
						StringFromKey("Common_NotBlade_65")));
			link.l2 = StringFromKey("Common_NotBlade_70", LinkRandPhrase(
						StringFromKey("Common_NotBlade_67"),
						StringFromKey("Common_NotBlade_68"),
						StringFromKey("Common_NotBlade_69")));
			link.l1.go = "exit_HideBlade";
			link.l2.go = "exit_NoHideBlade";
		break;
	}
	return;
}

void ExitNotBladeDialog(ref rChr)
{
	rChr.Dialog.Filename = rChr.Dialog.Base_Filename;
	DeleteAttribute(rChr, "Dialog.Base_Filename");
	DeleteAttribute(&TEV, "CitizenFightBlade");
	DeleteAttribute(rChr, "IWantAskYou");
	rChr.Dialog.CurrentNode = rChr.Dialog.TempNode;
	DialogExit();
}
