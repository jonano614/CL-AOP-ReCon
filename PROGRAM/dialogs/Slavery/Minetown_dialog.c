#include "DIALOGS\Slavery\Common_Slavery.c"
// диалоги обитателей рудников
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
			dialog.text = StringFromKey("Minetown_dialog_7", RandPhraseSimple(
						StringFromKey("Minetown_dialog_3", RandPhraseSimple(
								StringFromKey("Minetown_dialog_1"),
								StringFromKey("Minetown_dialog_2", pchar))),
						StringFromKey("Minetown_dialog_6", RandPhraseSimple(
								StringFromKey("Minetown_dialog_4"),
								StringFromKey("Minetown_dialog_5")))));
			link.l1 = StringFromKey("Minetown_dialog_10", RandPhraseSimple(
						StringFromKey("Minetown_dialog_8"),
						StringFromKey("Minetown_dialog_9")));
			link.l1.go = "exit";
		break;

		// охрана - протектор
		case "plantation_protector":
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if (sti(pchar.nation) == PIRATE)
				{
					dialog.text = StringFromKey("Minetown_dialog_13", RandPhraseSimple(
								StringFromKey("Minetown_dialog_11", pchar),
								StringFromKey("Minetown_dialog_12", pchar)));
					link.l1 = StringFromKey("Minetown_dialog_16", RandPhraseSimple(
								StringFromKey("Minetown_dialog_14"),
								StringFromKey("Minetown_dialog_15")));
					link.l1.go = "fight";
					break;
				}
				dialog.text = StringFromKey("Minetown_dialog_19", RandPhraseSimple(
							StringFromKey("Minetown_dialog_17", NationNameGenitive(sti(pchar.nation))),
							StringFromKey("Minetown_dialog_18", pchar, NationNameInstrumental(sti(pchar.nation)))));
				link.l1 = StringFromKey("Minetown_dialog_22", RandPhraseSimple(
							StringFromKey("Minetown_dialog_20"),
							StringFromKey("Minetown_dialog_21")));
				link.l1.go = "fight";
			}
			else
			{
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					if (sti(pchar.nation) == PIRATE)
					{
						dialog.text = StringFromKey("Minetown_dialog_25", RandPhraseSimple(
									StringFromKey("Minetown_dialog_23", pchar),
									StringFromKey("Minetown_dialog_24", pchar)));
						link.l1 = StringFromKey("Minetown_dialog_28", RandPhraseSimple(
									StringFromKey("Minetown_dialog_26"),
									StringFromKey("Minetown_dialog_27")));
						link.l1.go = "fight";
						break;
					}
					dialog.text = StringFromKey("Minetown_dialog_31", RandPhraseSimple(
								StringFromKey("Minetown_dialog_29"),
								StringFromKey("Minetown_dialog_30", pchar)));
					if (CheckNationLicence(sti(NPChar.nation)))
					{
						link.l1 = StringFromKey("Minetown_dialog_32");
						link.l1.go = "Licence";
						link.l2 = StringFromKey("Minetown_dialog_33");
						link.l2.go = CheckSneakByGuards(sti(NPChar.nation));
						link.l2 = DeceptionChance_TextWrapper(link.l2);
					}
					else
					{
						link.l1 = StringFromKey("Minetown_dialog_34");
						link.l1.go = CheckSneakByGuards(sti(NPChar.nation));
						link.l1 = DeceptionChance_TextWrapper(link.l1);
					}
				}
				else
				{
					dialog.text = StringFromKey("Minetown_dialog_37", RandPhraseSimple(
								StringFromKey("Minetown_dialog_35"),
								StringFromKey("Minetown_dialog_36", pchar)));
					link.l1 = StringFromKey("Minetown_dialog_38");
					link.l1.go = "NotPegYou";
				}
			}
		break;
	}
} 
