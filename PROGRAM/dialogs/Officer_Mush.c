#include "DIALOGS\Officer_Common.c"

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
		//--> хорошист-саксонец
		case "Saxon":
			if (sti(PChar.reputation) >= 51) //при низкой репутации - в сад
			{
				PlayerRPGCheck_Reputation_NotifyPass(false, true);
				dialog.text = StringFromKey("Officer_Mush_1");
				link.l1 = StringFromKey("Officer_Mush_2");
				link.l1.go = "Saxon_1";
			}
			else
			{
				PlayerRPGCheck_Reputation_NotifyFail("good");
				dialog.text = StringFromKey("Officer_Mush_3", pchar);
				link.l1 = StringFromKey("Officer_Mush_4");
				link.l1.go = "exit";
				NextDiag.TempNode = "Saxon";
			}
		break;

		case "Saxon_1":
			dialog.text = StringFromKey("Officer_Mush_5");
			link.l1 = StringFromKey("Officer_Mush_6");
			link.l1.go = "Saxon_2";
		break;

		case "Saxon_2":
			dialog.text = StringFromKey("Officer_Mush_7", pchar);
			link.l1 = StringFromKey("Officer_Mush_8");
			link.l1.go = "Saxon_3";
		break;

		case "Saxon_3":
			dialog.text = StringFromKey("Officer_Mush_9");
			link.l1 = StringFromKey("Officer_Mush_10");
			link.l1.go = "Saxon_4";
		break;

		case "Saxon_4":
			dialog.text = StringFromKey("Officer_Mush_11");
			if (sti(Pchar.money) >= 40000)
			{
				link.l1 = StringFromKey("Officer_Mush_12");
				link.l1.go = "Saxon_check";
			}
			link.l2 = StringFromKey("Officer_Mush_13", pchar);
			link.l2.go = "exit";
			NextDiag.TempNode = "OnceAgain";
		break;

		case "OnceAgain":
			NextDiag.TempNode = "OnceAgain";
			dialog.text = StringFromKey("Officer_Mush_14");
			link.l1 = StringFromKey("Officer_Mush_15");
			link.l1.go = "Saxon_4";
			link.l2 = StringFromKey("Officer_Mush_16", pchar);
			link.l2.go = "exit";
		break;

		case "Saxon_check":
			if (FindFreeRandomOfficer() == -1)//если перебор с офицерами
			{
				dialog.text = StringFromKey("Officer_Mush_17");
				link.l1 = StringFromKey("Officer_Mush_18");
				link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgain";
				break;
			}
			if (sti(PChar.reputation) < 51)//повторная проверка репутации, для второго и далее заходов
			{
				PlayerRPGCheck_Reputation_NotifyFail("good");
				dialog.text = StringFromKey("Officer_Mush_19");
				link.l1 = StringFromKey("Officer_Mush_20");
				link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgain";
				break;
			}
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 21 + MOD_SKILL_ENEMY_RATE)//при низком лидерстве - в сад
			{
				PlayerRPGCheck_Skill_NotifyFail(SKILL_LEADERSHIP, false);
				dialog.text = StringFromKey("Officer_Mush_21");
				link.l1 = StringFromKey("Officer_Mush_22");
				link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgain";
				break;
			}
			PlayerRPGCheck_Reputation_NotifyPass(false, true);
			PlayerRPGCheck_Skill_NotifyPass(SKILL_LEADERSHIP);
			dialog.text = StringFromKey("Officer_Mush_23");
			link.l1 = StringFromKey("Officer_Mush_24", pchar);
			link.l1.go = "Exit_hire_Saxon";
		break;
		//<-- хорошист-саксонец

		//--> плохиш-пират
		case "Lostpirate":
			if (sti(PChar.reputation) < 36)//при повышенной репутации - в сад
			{
				PlayerRPGCheck_Reputation_NotifyPass(false, false);
				dialog.text = StringFromKey("Officer_Mush_25");
				link.l1 = StringFromKey("Officer_Mush_26");
				link.l1.go = "Lostpirate_1";
			}
			else
			{
				PlayerRPGCheck_Reputation_NotifyFail("bad");
				dialog.text = StringFromKey("Officer_Mush_27", pchar);
				link.l1 = StringFromKey("Officer_Mush_28", pchar);
				link.l1.go = "exit_Rep";
			}
		break;

		case "exit_Rep":
			NextDiag.TempNode = "Lostpirate";
			dialog.text = StringFromKey("Officer_Mush_29");
			link.l1 = StringFromKey("Officer_Mush_30");
			link.l1.go = "exit";
		break;

		case "Lostpirate_1":
			dialog.text = StringFromKey("Officer_Mush_31");
			link.l1 = StringFromKey("Officer_Mush_32");
			link.l1.go = "Lostpirate_2";
		break;

		case "Lostpirate_2":
			dialog.text = StringFromKey("Officer_Mush_33");
			link.l1 = StringFromKey("Officer_Mush_34");
			link.l1.go = "Lostpirate_check";
		break;

		case "OnceAgainLP":
			NextDiag.TempNode = "OnceAgainLP";
			dialog.text = StringFromKey("Officer_Mush_35", pchar);
			link.l1 = StringFromKey("Officer_Mush_36");
			link.l1.go = "Lostpirate_check";
			link.l2 = StringFromKey("Officer_Mush_37", pchar);
			link.l2.go = "exit";
		break;

		case "Lostpirate_check":
			if (FindFreeRandomOfficer() == -1)//если перебор с офицерами
			{
				dialog.text = StringFromKey("Officer_Mush_38");
				link.l1 = StringFromKey("Officer_Mush_39");
				link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgainLP";
				break;
			}
			if (sti(PChar.reputation) >= 36)//повторная проверка репутации, для второго и далее заходов
			{
				PlayerRPGCheck_Reputation_NotifyFail("bad");
				dialog.text = StringFromKey("Officer_Mush_40");
				link.l1 = StringFromKey("Officer_Mush_41");
				link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgainLP";
				break;
			}
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) < 31)//при низком везении - в сад
			{
				PlayerRPGCheck_Skill_NotifyFail(SKILL_FORTUNE, false);
				dialog.text = StringFromKey("Officer_Mush_42");
				link.l1 = StringFromKey("Officer_Mush_43");
				link.l1.go = "exit";
				NextDiag.TempNode = "OnceAgainLP";
				break;
			}
			PlayerRPGCheck_Reputation_NotifyPass(false, false);
			PlayerRPGCheck_Skill_NotifyPass(SKILL_FORTUNE);
			dialog.text = StringFromKey("Officer_Mush_44");
			link.l1 = StringFromKey("Officer_Mush_45");
			link.l1.go = "Exit_hire_Lostpirate";
			link.l2 = StringFromKey("Officer_Mush_46", pchar);
			link.l2.go = "exit";
			NextDiag.TempNode = "OnceAgainLP";
		break;
		//<-- плохиш-пират

		//--> найм
		case "Exit_hire_Saxon":
			AddMoneyToCharacter(Pchar, -40000);
			npchar.MusketerDistance = 10;
			TakeNItems(npchar, "Mineral7", 1);
			TakeNItems(npchar, "indian17", 1);
			TakeNItems(npchar, "potionwine", 1);
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit_hire_Lostpirate":
			AddItemLog(pchar, "Mineral4", "5", StringFromKey("InfoMessages_169"), "Important_item");
			npchar.MusketerDistance = 10;
			TakeNItems(npchar, "Mineral2", 1);
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(&locations[FindLocation("Shore59")], "DisableEncounters"); //энкаутеры в бухте откроем
		break;
		//<-- найм
	}
}