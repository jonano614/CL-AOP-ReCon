#include "DIALOGS\Officer_Common.c"

//диалог офицера/компаньона девушки
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessBaseOfficerEvent(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "First time":
			NextDiag.TempNode = "First time";
			dialog.text = StringFromKey("Officer_Girl_3", RandPhraseSimple(
						StringFromKey("Officer_Girl_1"),
						StringFromKey("Officer_Girl_2")));
			link.l1 = StringFromKey("Officer_Girl_4", pchar);
			link.l1.go = "Girl_Node_2";
			link.l2 = StringFromKey("Officer_Girl_5", pchar);
			link.l2.go = "exit";
		break;

		case "Girl_Node_2":
			if (NPChar.alignment == "good" && sti(pchar.reputation) < 70)
			{
				PlayerRPGCheck_Reputation_NotifyFail("good");
				dialog.text = StringFromKey("Officer_Girl_6");
				link.l1 = StringFromKey("Officer_Girl_7");
				link.l1.go = "exit";
				break;
			}
			if (NPChar.alignment == "bad" && sti(pchar.reputation) > 30)
			{
				PlayerRPGCheck_Reputation_NotifyFail("bad");
				dialog.text = StringFromKey("Officer_Girl_8", pchar);
				link.l1 = StringFromKey("Officer_Girl_9");
				link.l1.go = "exit";
				break;
			}
			PlayerRPGCheck_Reputation_NotifyPass(false, NPChar.alignment == "good");
			Npchar.quest.OfficerPrice = 50000;
			Npchar.quest.OfficerLowPrice = 100000;
			dialog.text = StringFromKey("Officer_Girl_10");
			link.l1 = StringFromKey("Officer_Girl_11", pchar);
			link.l1.go = "price";
			link.l2 = StringFromKey("Officer_Girl_12");
			link.l2.go = "exit";
			NextDiag.TempNode = "OnboardSoon";
		break;

		case "OnboardSoon":
			NextDiag.TempNode = "OnboardSoon";
			if (NPChar.alignment == "good" && sti(pchar.reputation) < 70)
			{
				PlayerRPGCheck_Reputation_NotifyFail("good");
				dialog.text = StringFromKey("Officer_Girl_13");
				link.l1 = StringFromKey("Officer_Girl_14");
				link.l1.go = "exit";
				break;
			}

			if (NPChar.alignment == "bad" && sti(pchar.reputation) > 30)
			{
				PlayerRPGCheck_Reputation_NotifyFail("bad");
				dialog.text = StringFromKey("Officer_Girl_15", pchar);
				link.l1 = StringFromKey("Officer_Girl_16");
				link.l1.go = "exit";
				break;
			}
			PlayerRPGCheck_Reputation_NotifyPass(false, NPChar.alignment == "good");
			dialog.text = StringFromKey("Officer_Girl_17");
			link.l1 = StringFromKey("Officer_Girl_18");
			link.l1.go = "price";
			link.l2 = StringFromKey("Officer_Girl_19");
			link.l2.go = "exit";
		break;

		case "hired":
			NextDiag.TempNode = "Hired";

			// приколы -->
			if (PChar.location == Get_My_Cabin())
			{
				if (PChar.sex != "woman")
				{
					Link.l3 = StringFromKey("Officer_Girl_22", RandPhraseSimple(
								StringFromKey("Officer_Girl_20"),
								StringFromKey("Officer_Girl_21")));
					if (sti(pchar.GenQuest.BrothelCount) > 4 + rand(3))
					{
						Link.l3.go = "Love_Sex_Yes";
					}
					else
					{
						Link.l3.go = "Love_Sex";
					}
				}
				if (CheckAttribute(pchar, "questTemp.FUNY_SHIP_FIND") && PChar.questTemp.FUNY_SHIP_FIND == true && GetCharacterItem(PChar, "mineral4") >= 25)
				{
					Link.l4 = StringFromKey("Officer_Girl_23");
					Link.l4.go = "FUNY_SHIP_1";
				}
			}
			else
			{
				if (PChar.sex != "woman" && CheckCharacterPerk(NPChar, "SweetBaby")) //временно только для отмеченных данек, но не для ПГГ-девочек
				{
					Link.l3 = StringFromKey("Officer_Girl_26", RandPhraseSimple(
								StringFromKey("Officer_Girl_24"),
								StringFromKey("Officer_Girl_25")));
					Link.l3.go = "Love_Sex";
				}
			}
		break;

		case "FUNY_SHIP_1":
			dialog.text = StringFromKey("Officer_Girl_27");
			Link.l1 = StringFromKey("Officer_Girl_28");
			Link.l1.go = "exit";
			Link.l2 = StringFromKey("Officer_Girl_29");
			Link.l2.go = "FUNY_SHIP_2";
		break;

		case "FUNY_SHIP_2":
			dialog.text = StringFromKey("Officer_Girl_30");
			Link.l1 = StringFromKey("Officer_Girl_31");
			Link.l1.go = "FUNY_SHIP_3";
		break;

		case "FUNY_SHIP_3":
			PChar.questTemp.FUNY_SHIP_FIND = false;
			DialogExit();
			NextDiag.CurrentNode = "Hired";

			TakeNItems(pchar, "mineral4", -25);
			AddSPECIALValue(Npchar, SPECIAL_S, 1);
			AddSPECIALValue(Npchar, SPECIAL_P, 1);
			AddSPECIALValue(Npchar, SPECIAL_E, 1);
			AddSPECIALValue(Npchar, SPECIAL_C, 1);
			AddSPECIALValue(Npchar, SPECIAL_I, 1);
			AddSPECIALValue(Npchar, SPECIAL_A, 1);
			AddSPECIALValue(Npchar, SPECIAL_L, 1);
		break;

		case "Love_Sex_Yes":
			dialog.text = StringFromKey("Officer_Girl_34", RandPhraseSimple(
						StringFromKey("Officer_Girl_32"),
						StringFromKey("Officer_Girl_33")));
			link.l1 = StringFromKey("Officer_Girl_37", RandPhraseSimple(
						StringFromKey("Officer_Girl_35"),
						StringFromKey("Officer_Girl_36")));
			link.l1.go = "Love_Sex_Yes_2";
		break;

		case "Love_Sex_Yes_2":
			pchar.GenQuest.BrothelCount = 0;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Fencing", -50);// утрахала
			AddCharacterExpToSkill(pchar, "Pistol", -50);
			AddCharacterHealth(pchar, 10);

			AddDialogExitQuest("PlaySex_1");
			NextDiag.CurrentNode = "After_sex";
			DialogExit();
		break;

		case "After_sex":
			NextDiag.TempNode = "Hired";
			dialog.text = StringFromKey("Officer_Girl_40", RandPhraseSimple(
						StringFromKey("Officer_Girl_38"),
						StringFromKey("Officer_Girl_39")));
			link.l1 = StringFromKey("Officer_Girl_43", RandPhraseSimple(
						StringFromKey("Officer_Girl_41"),
						StringFromKey("Officer_Girl_42")));
			link.l1.go = "exit";
		break;

		case "Love_Sex":
			NextDiag.TempNode = "Hired";
			dialog.text = StringFromKey("Officer_Girl_46", RandPhraseSimple(
						StringFromKey("Officer_Girl_44"),
						StringFromKey("Officer_Girl_45")));
			link.l1 = StringFromKey("Officer_Girl_49", RandPhraseSimple(
						StringFromKey("Officer_Girl_47"),
						StringFromKey("Officer_Girl_48")));
			link.l1.go = "Love_Sex_2";
			link.l2 = StringFromKey("Officer_Girl_52", RandPhraseSimple(
						StringFromKey("Officer_Girl_50"),
						StringFromKey("Officer_Girl_51")));
			link.l2.go = "exit";
		break;

		case "Love_Sex_2":
			NextDiag.TempNode = "Hired";
			dialog.text = StringFromKey("Officer_Girl_55", RandPhraseSimple(
						StringFromKey("Officer_Girl_53"),
						StringFromKey("Officer_Girl_54")));
			link.l1 = StringFromKey("Officer_Girl_58", RandPhraseSimple(
						StringFromKey("Officer_Girl_56"),
						StringFromKey("Officer_Girl_57")));
			link.l1.go = "Love_Sex_3";
			link.l2 = StringFromKey("Officer_Girl_61", RandPhraseSimple(
						StringFromKey("Officer_Girl_59"),
						StringFromKey("Officer_Girl_60")));
			link.l2.go = "exit";
		break;

		case "Love_Sex_3":
			NextDiag.TempNode = "Hired";
			dialog.text = StringFromKey("Officer_Girl_64", RandPhraseSimple(
						StringFromKey("Officer_Girl_62"),
						StringFromKey("Officer_Girl_63")));
			link.l1 = StringFromKey("Officer_Girl_65");
			link.l1.go = "Love_Sex_4";
		break;

		case "Love_Sex_4":
			ChangeCharacterReputation(pchar, -15);
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			LAi_SetWarriorType(Npchar);
			LAi_group_MoveCharacter(Npchar, "TmpEnemy");
			LAi_group_SetHearRadius("TmpEnemy", 100.0);
			LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);

			if (HasStrEx(PChar.location, "My_Cabin,_tavern", "|"))
			{
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff_NoLock");
			}
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		// приколы <--
	}
}
