// boal 25/04/04 общий диалог солдат форта
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\Fort\" + NPChar.City + "_Fort.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--
	int iTest, iTemp;
	string sTemp;
	iTest = FindColony(NPChar.City); // город
	ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			//			if (HasSubStr(sTemp, "_townhall")) AddDialogExitQuest("MainHeroFightModeOff"); // не актуально
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(NPChar, "IWantAskYou");
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			DeleteAttribute(NPChar, "IWantAskYou");
		break;

		case "First time":
			NextDiag.TempNode = "First time";
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = StringFromKey("Common_Fort_3", RandPhraseSimple(
							StringFromKey("Common_Fort_1"),
							StringFromKey("Common_Fort_2", pchar)));
				link.l1 = StringFromKey("Common_Fort_6", RandPhraseSimple(
							StringFromKey("Common_Fort_4"),
							StringFromKey("Common_Fort_5")));
				link.l1.go = "fight";
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetRelation2BaseNation(sti(npchar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = StringFromKey("Common_Fort_9", RandPhraseSimple(
								StringFromKey("Common_Fort_7"),
								StringFromKey("Common_Fort_8")));
					//==> по лицензии
					if (CheckNationLicence(sti(npchar.nation)))
					{
						link.l1 = StringFromKey("Common_Fort_10", GetRusNameNationLicence(sti(npchar.nation)));
						link.l1.go = "LicenceOk";
						if (HasSubStr(pchar.location.from_sea, "_town")) //если причалил в городе
						{
							link.l2 = StringFromKey("Common_Fort_11", NationNameGenitive(sti(pchar.nation)));
						}
						else //если причалил не в городе
						{
							link.l2 = StringFromKey("Common_Fort_12", pchar, XI_ConvertString(GetIslandNameByCity(npchar.city) + "Gen"), NationNameGenitive(sti(pchar.nation)));
						}
						link.l2 = DeceptionChance_TextWrapper(link.l2);
						link.l2.go = CheckSneakByGuards(sti(npchar.nation));
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
							dialog.text = StringFromKey("Common_Fort_15", RandPhraseSimple(
										StringFromKey("Common_Fort_13", pchar),
										StringFromKey("Common_Fort_14", pchar)));
							link.l1 = StringFromKey("Common_Fort_18", RandPhraseSimple(
										StringFromKey("Common_Fort_16"),
										StringFromKey("Common_Fort_17")));
							link.l1.go = "fight";
							break;
						}
						if (HasSubStr(pchar.location.from_sea, "_town")) //если причалил в городе
						{
							link.l1 = StringFromKey("Common_Fort_19", NationNameGenitive(sti(pchar.nation)));
						}
						else //если причалил не в городе
						{
							link.l1 = StringFromKey("Common_Fort_20", XI_ConvertString(GetIslandNameByCity(npchar.city) + "Gen"), NationNameGenitive(sti(pchar.nation)));
						}
						link.l1 = DeceptionChance_TextWrapper(link.l1);
						link.l1.go = CheckSneakByGuards(sti(npchar.nation));
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn)) // наш горожанин
						{
							switch (rand(10))
							{
								case 0:
									dialog.text = StringFromKey("Common_Fort_21");
									link.l1 = StringFromKey("Common_Fort_22");
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = StringFromKey("Common_Fort_23");
									link.l1 = StringFromKey("Common_Fort_24");
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = StringFromKey("Common_Fort_25");
									link.l1 = StringFromKey("Common_Fort_26");
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = StringFromKey("Common_Fort_27");
									link.l1 = StringFromKey("Common_Fort_28", pchar);
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = StringFromKey("Common_Fort_29");
									link.l1 = StringFromKey("Common_Fort_30");
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = StringFromKey("Common_Fort_31");
									link.l1 = StringFromKey("Common_Fort_32");
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = StringFromKey("Common_Fort_33");
									link.l1 = StringFromKey("Common_Fort_34");
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = StringFromKey("Common_Fort_35");
									link.l1 = StringFromKey("Common_Fort_36");
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = StringFromKey("Common_Fort_37");
									link.l1 = StringFromKey("Common_Fort_38");
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = StringFromKey("Common_Fort_39");
									link.l1 = StringFromKey("Common_Fort_40");
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = StringFromKey("Common_Fort_41");
									link.l1 = StringFromKey("Common_Fort_42");
									link.l1.go = "exit";
								break;
							}
							link.l2 = StringFromKey("Common_Fort_45", RandPhraseSimple(
										StringFromKey("Common_Fort_43"),
										StringFromKey("Common_Fort_44")));
							link.l2.go = "quests";//(перессылка в файл города)
							break;
						}
					}
					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = StringFromKey("Common_Fort_46");
							link.l1 = StringFromKey("Common_Fort_47");
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = StringFromKey("Common_Fort_48");
							link.l1 = StringFromKey("Common_Fort_49");
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = StringFromKey("Common_Fort_50");
							link.l1 = StringFromKey("Common_Fort_51");
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = StringFromKey("Common_Fort_52");
							link.l1 = StringFromKey("Common_Fort_53", pchar);
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = StringFromKey("Common_Fort_54");
							link.l1 = StringFromKey("Common_Fort_55", pchar);
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = StringFromKey("Common_Fort_56");
							link.l1 = StringFromKey("Common_Fort_57");
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = StringFromKey("Common_Fort_58");
							link.l1 = StringFromKey("Common_Fort_59");
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = StringFromKey("Common_Fort_60");
							link.l1 = StringFromKey("Common_Fort_61");
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = StringFromKey("Common_Fort_62", pchar);
							link.l1 = StringFromKey("Common_Fort_63", pchar);
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = StringFromKey("Common_Fort_64", pchar);
							link.l1 = StringFromKey("Common_Fort_65", pchar);
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = StringFromKey("Common_Fort_66");
							link.l1 = StringFromKey("Common_Fort_67");
							link.l1.go = "exit";
						break;
					}
					link.l3 = StringFromKey("Common_Fort_68", pchar);
					link.l3.go = "quests";//(перессылка в файл города)
				}
			}
		break;
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = StringFromKey("Common_Fort_71", RandPhraseSimple(
						StringFromKey("Common_Fort_69", pchar),
						StringFromKey("Common_Fort_70", pchar, GetAddress_Form(npchar))));
			link.l1 = StringFromKey("Common_Fort_74", RandPhraseSimple(
						StringFromKey("Common_Fort_72"),
						StringFromKey("Common_Fort_73")));
			link.l1.go = "fight";
			if (CheckAttribute(NPChar, "IWantAskYou"))
			{
				DeleteAttribute(NPChar, "IWantAskYou");
				if (isDay()) AddCharacterExpToSkill(pchar, SKILL_SNEAK, 20.0);
				else  AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40.0);
			}
			//Оставил на случай, если гг сам обратится к менту
			else if (!CheckAttribute(pchar, "questTemp.stels.landFort") || sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "NotPegYou":
			dialog.text = StringFromKey("Common_Fort_77", RandPhraseSimple(
						StringFromKey("Common_Fort_75", GetAddress_Form(pchar)),
						StringFromKey("Common_Fort_76", GetAddress_Form(pchar))));
			link.l1 = StringFromKey("Common_Fort_78");
			link.l1.go = "exit";
			if (CheckAttribute(NPChar, "IWantAskYou"))
			{
				DeleteAttribute(NPChar, "IWantAskYou");
				if (isDay()) AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40.0);
				else  AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80.0);
			}
			//Оставил на случай, если гг сам обратится к менту
			else if (!CheckAttribute(pchar, "questTemp.stels.landFort") || sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(sti(npchar.nation));
			if (iTemp == -1)
			{
				dialog.text = StringFromKey("Common_Fort_79");
				link.l1 = StringFromKey("Common_Fort_82", RandPhraseSimple(
							StringFromKey("Common_Fort_80"),
							StringFromKey("Common_Fort_81")));
				link.l1.go = "fight";
				TakeNationLicence(sti(npchar.nation));
			}
			if (iTemp == 0)
			{
				dialog.text = StringFromKey("Common_Fort_83");
				link.l1 = StringFromKey("Common_Fort_84");
				link.l1.go = "exit";
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = StringFromKey("Common_Fort_85", FindDaysString(iTemp), GetAddress_Form(npchar));
				link.l1 = StringFromKey("Common_Fort_86");
				link.l1.go = "exit";
			}
			if (iTemp > 10)
			{
				dialog.text = StringFromKey("Common_Fort_90", LinkRandPhrase(
							StringFromKey("Common_Fort_87", FindDaysString(iTemp)),
							StringFromKey("Common_Fort_88", GetAddress_Form(npchar), FindDaysString(iTemp)),
							StringFromKey("Common_Fort_89", GetAddress_Form(npchar))));
				link.l1 = StringFromKey("Common_Fort_93", RandPhraseSimple(
							StringFromKey("Common_Fort_91"),
							StringFromKey("Common_Fort_92")));
				link.l1.go = "exit";
			}
		break;

		//замечение по обнаженному оружию
		/*case "SoldierNotBlade": //HardCoffee ref SoldierNotBlade CitizenNotBlade
			if(GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				if(sti(pchar.nation) == PIRATE)
				{
					dialog.text = RandPhraseSimple(StringFromKey("Common_Fort_87", GetSexPhrase(StringFromKey("SexPhrase_54"), StringFromKey("SexPhrase_55"))), StringFromKey("Common_Fort_88", GetSexPhrase(StringFromKey("SexPhrase_54"), StringFromKey("SexPhrase_55"))));
					link.l1 = RandPhraseSimple(StringFromKey("Common_Fort_89"), StringFromKey("Common_Fort_90"));
					link.l1.go = "fight";
					break;
				}
				dialog.text = RandPhraseSimple(StringFromKey("Common_Fort_92"), StringFromKey("Common_Fort_91", GetSexPhrase(StringFromKey("SexPhrase_54"), StringFromKey("SexPhrase_55"))));
				link.l1 = RandPhraseSimple(StringFromKey("Common_Fort_93"), StringFromKey("Common_Fort_94"));
				link.l1.go = "fight";
			}
			else
			{
				dialog.text = LinkRandPhrase(StringFromKey("Common_Fort_96"), StringFromKey("Common_Fort_97"), StringFromKey("Common_Fort_95", GetSexPhrase(StringFromKey("SexPhrase_130"),StringFromKey("SexPhrase_131"))));
				link.l1 = LinkRandPhrase(StringFromKey("Common_Fort_98"), StringFromKey("Common_Fort_99"), StringFromKey("Common_Fort_100"));
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) != RELATION_ENEMY) link.l1.go = "exit";
				else link.l1.go = "First Time"; //Не миновать нам проверки!
				link.l2 = LinkRandPhrase(StringFromKey("Common_Fort_101"), StringFromKey("Common_Fort_102"), StringFromKey("Common_Fort_103"));
				link.l2.go = "fight";
				NextDiag.TempNode = "First Time";
				if (CheckAttribute(NPChar, "protector")) NPChar.greeting = "soldier_arest";
				else NPChar.greeting = "soldier_common";
			}
		break;*/
	}
}
