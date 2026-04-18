#include "DIALOGS\Slavery\Common_Slavery.c"
// диалоги обитателей плантаций
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonSlavery(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{
		// охрана - солдаты
		case "plantation_soldier":
			dialog.text = StringFromKey("Plantation_dialog_7", RandPhraseSimple(
						StringFromKey("Plantation_dialog_3", RandPhraseSimple(
								StringFromKey("Plantation_dialog_1"),
								StringFromKey("Plantation_dialog_2", pchar))),
						StringFromKey("Plantation_dialog_6", RandPhraseSimple(
								StringFromKey("Plantation_dialog_4"),
								StringFromKey("Plantation_dialog_5")))));
			link.l1 = StringFromKey("Plantation_dialog_10", RandPhraseSimple(
						StringFromKey("Plantation_dialog_8"),
						StringFromKey("Plantation_dialog_9")));
			link.l1.go = "exit";
		break;

		// охрана - протектор
		case "plantation_protector":
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if (sti(pchar.nation) == PIRATE)
				{
					dialog.text = StringFromKey("Plantation_dialog_13", RandPhraseSimple(
								StringFromKey("Plantation_dialog_11", pchar),
								StringFromKey("Plantation_dialog_12", pchar)));
					link.l1 = StringFromKey("Plantation_dialog_16", RandPhraseSimple(
								StringFromKey("Plantation_dialog_14"),
								StringFromKey("Plantation_dialog_15")));
					link.l1.go = "fight";
					break;
				}
				dialog.text = StringFromKey("Plantation_dialog_19", RandPhraseSimple(
							StringFromKey("Plantation_dialog_17", NationNameGenitive(sti(pchar.nation))),
							StringFromKey("Plantation_dialog_18", pchar, NationNameInstrumental(sti(pchar.nation)))));
				link.l1 = StringFromKey("Plantation_dialog_22", RandPhraseSimple(
							StringFromKey("Plantation_dialog_20"),
							StringFromKey("Plantation_dialog_21")));
				link.l1.go = "fight";
			}
			else
			{
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					if (sti(pchar.nation) == PIRATE)
					{
						dialog.text = StringFromKey("Plantation_dialog_25", RandPhraseSimple(
									StringFromKey("Plantation_dialog_23", pchar),
									StringFromKey("Plantation_dialog_24", pchar)));
						link.l1 = StringFromKey("Plantation_dialog_28", RandPhraseSimple(
									StringFromKey("Plantation_dialog_26"),
									StringFromKey("Plantation_dialog_27")));
						link.l1.go = "fight";
						break;
					}
					dialog.text = StringFromKey("Plantation_dialog_31", RandPhraseSimple(
								StringFromKey("Plantation_dialog_29"),
								StringFromKey("Plantation_dialog_30", pchar)));
					if (CheckNationLicence(sti(NPChar.nation)))
					{
						link.l1 = StringFromKey("Plantation_dialog_32");
						link.l1.go = "Licence";
						link.l2 = StringFromKey("Plantation_dialog_33");
						link.l2.go = CheckSneakByGuards(sti(NPChar.nation));
						link.l2 = DeceptionChance_TextWrapper(link.l2);
					}
					else
					{
						link.l1 = StringFromKey("Plantation_dialog_34");
						link.l1.go = CheckSneakByGuards(sti(NPChar.nation));
						link.l1 = DeceptionChance_TextWrapper(link.l1);
					}
				}
				else
				{
					dialog.text = StringFromKey("Plantation_dialog_37", RandPhraseSimple(
								StringFromKey("Plantation_dialog_35"),
								StringFromKey("Plantation_dialog_36", pchar)));
					link.l1 = StringFromKey("Plantation_dialog_38");
					link.l1.go = "NotPegYou";
				}
			}
		break;

		// управляющий в Маракайбо
		case "Plantator":
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "plant_2" && GetSquadronGoods(pchar, GOOD_SLAVES) >= 50)
			{
				dialog.text = StringFromKey("Plantation_dialog_39", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Plantation_dialog_40", TimeGreeting(), GetAddress_FormToNPC(NPChar), FindQtyString(sti(GetSquadronGoods(pchar, GOOD_SLAVES))));
				link.l1.go = "mtraxx";
			}
			dialog.text = StringFromKey("Plantation_dialog_41", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Plantation_dialog_42", pchar);
			link.l1.go = "exit";
		break;

		case "plantator_1":
			dialog.text = StringFromKey("Plantation_dialog_43", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Plantation_dialog_44");
			link.l1.go = "exit";
		break;

		case "mtraxx":
			dialog.text = StringFromKey("Plantation_dialog_45", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Plantation_dialog_46", GetAddress_FormToNPC(NPChar));
			link.l1.go = "mtraxx_1";
		break;

		case "mtraxx_1":
			dialog.text = StringFromKey("Plantation_dialog_47");
			link.l1 = StringFromKey("Plantation_dialog_48", pchar, GetAddress_FormToNPC(NPChar));
			link.l1.go = "mtraxx_2";
		break;

		case "mtraxx_2":
			dialog.text = StringFromKey("Plantation_dialog_49");
			link.l1 = StringFromKey("Plantation_dialog_50");
			link.l1.go = "mtraxx_3";
		break;

		case "mtraxx_3":
			dialog.text = StringFromKey("Plantation_dialog_51");
			link.l1 = StringFromKey("Plantation_dialog_52", GetAddress_FormToNPC(NPChar));
			link.l1.go = "mtraxx_4";
		break;

		case "mtraxx_4":
			DialogExit();
			NextDiag.CurrentNode = "plantator_1";
			pchar.questTemp.Mtraxx = "plant_3";
		//AddQuestRecord("Roger_3", "5"); нет такой записи
		break;

		// солдат на страже
		case "guard":
			if (GetTime() < 7.0 || GetTime() > 21.0)
			{
				dialog.text = StringFromKey("Plantation_dialog_53");
				link.l1 = StringFromKey("Plantation_dialog_54");
				link.l1.go = "exit";
				break;
			}
			if (npchar.location == "Bridgetown_Plantation_Sp1") dialog.text = StringFromKey("Plantation_dialog_55");
			else dialog.text = StringFromKey("Plantation_dialog_56");
			link.l1 = StringFromKey("Plantation_dialog_57");
			link.l1.go = "exit";
		break;
	}
} 
