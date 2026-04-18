#include "DIALOGS\Rumours\Simple_rumors.c"

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp, sText;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	if (HasStrEx(Dialog.CurrentNode, "Fencing,Defence", "|"))
	{
		DeleteAttribute(NPChar, "diag.refuse_fenc");
		if (HasStr(Dialog.CurrentNode, "Fencing")) NPChar.FencTeach = "";
		Dialog.CurrentNode = "Skill_2";
	}

	switch (Dialog.CurrentNode)
	{
		case "First time":
			if (NPChar.sex != "man")
			{
				dialog.text = StringFromKey("Walker_3", RandPhraseSimple(
							StringFromKey("Walker_1", pchar),
							StringFromKey("Walker_2")));
				Link.l1 = StringFromKey("Walker_4");
				Link.l1.go = "exit";
				break;
			}
			link.l10 = StringFromKey("Walker_8", LinkRandPhrase(
						StringFromKey("Walker_5"),
						StringFromKey("Walker_6"),
						StringFromKey("Walker_7")));
			link.l10.go = "rumours_citizen"; //TODO: отдельные слухи гулякам (но в церквях всё так же городские)
			switch (sti(npchar.diag))
			{
				case 0:
					dialog.text = StringFromKey("Walker_9");
					Link.l1 = StringFromKey("Walker_10");
					Link.l1.go = "healing";
					Link.l2 = StringFromKey("Walker_11");
					Link.l2.go = "exit_once_more_portion";
				break;

				case 1:
					dialog.text = StringFromKey("Walker_12");
					Link.l1 = StringFromKey("Walker_13");
					Link.l1.go = "reput";
					Link.l2 = StringFromKey("Walker_14");
					Link.l2.go = "exit_out";
				break;

				case 2:
					switch (Rand(1))
					{
						case 0:
							dialog.text = StringFromKey("Walker_15");
							Link.l1 = StringFromKey("Walker_16");
							Link.l1.go = "beg";
							Link.l2 = StringFromKey("Walker_17");
							Link.l2.go = "exit_out";
						break;

						case 1:
							dialog.text = StringFromKey("Walker_18");
							Link.l1 = StringFromKey("Walker_19");
							Link.l1.go = "beg";
							Link.l2 = StringFromKey("Walker_20");
							Link.l2.go = "exit_out";
						break;
					}
				break;

				case 3:
					dialog.text = StringFromKey("Walker_21");
					Link.l1 = StringFromKey("Walker_22");
					Link.l1.go = "health";
					Link.l2 = StringFromKey("Walker_23");
					Link.l2.go = "exit";
				break;

				case 4:
					dialog.text = StringFromKey("Walker_24");
					Link.l1 = StringFromKey("Walker_25");
					Link.l1.go = "tavern";
					Link.l2 = StringFromKey("Walker_26");
					Link.l2.go = "exit";
				break;

				case 5:
					dialog.text = StringFromKey("Walker_27");
					Link.l1 = StringFromKey("Walker_28");
					Link.l1.go = "officer";
					Link.l2 = StringFromKey("Walker_29");
					Link.l2.go = "exit";
				break;

				//--> skeletons
				case 6:
					dialog.text = StringFromKey("Walker_30");
					Link.l1 = StringFromKey("Walker_31");
					Link.l1.go = "skeletons";
					Link.l2 = StringFromKey("Walker_32");
					Link.l2.go = "exit";
				break;

				case 7:
					dialog.text = StringFromKey("Walker_33");
					Link.l1 = StringFromKey("Walker_34");
					Link.l1.go = "skeletons";
					Link.l2 = StringFromKey("Walker_35");
					Link.l2.go = "exit";
				break;
				//<-- skeletons

				//--> police
				case 8:
					dialog.text = StringFromKey("Walker_36");
					Link.l1 = StringFromKey("Walker_37");
					Link.l1.go = "police";
					Link.l2 = StringFromKey("Walker_38");
					Link.l2.go = "exit";
				break;

				case 9:
					dialog.text = StringFromKey("Walker_39");
					Link.l1 = StringFromKey("Walker_40");
					Link.l1.go = "police";
					Link.l2 = StringFromKey("Walker_41");
					Link.l2.go = "exit";
				break;
				//<-- police

				//--> shipyard
				case 10:
					dialog.text = StringFromKey("Walker_42");
					Link.l1 = StringFromKey("Walker_43");
					Link.l1.go = "shipyard";
					Link.l2 = StringFromKey("Walker_44");
					Link.l2.go = "exit";
				break;

				case 11:
					dialog.text = StringFromKey("Walker_45");
					Link.l1 = StringFromKey("Walker_46");
					Link.l1.go = "shipyard";
					Link.l2 = StringFromKey("Walker_47");
					Link.l2.go = "exit";
				break;
				//<-- shipyard

				//--> torg
				case 12:
					dialog.text = StringFromKey("Walker_48");
					Link.l1 = StringFromKey("Walker_49");
					Link.l1.go = "torg";
					Link.l2 = StringFromKey("Walker_50");
					Link.l2.go = "exit_once_more";
				break;

				case 13:
					dialog.text = StringFromKey("Walker_51");
					Link.l1 = StringFromKey("Walker_52");
					Link.l1.go = "torg";
					Link.l2 = StringFromKey("Walker_53");
					Link.l2.go = "exit_once_more";
				break;
				//<-- torg

				//--> masters
				case 14:
					dialog.text = StringFromKey("Walker_54");
					Link.l1 = StringFromKey("Walker_55");
					Link.l1.go = "masters";
					Link.l2 = StringFromKey("Walker_56");
					Link.l2.go = "exit";
				break;

				case 15:
					dialog.text = StringFromKey("Walker_57");
					Link.l1 = StringFromKey("Walker_58");
					Link.l1.go = "masters";
					Link.l2 = StringFromKey("Walker_59");
					Link.l2.go = "exit";
				break;

				case 16:
					dialog.text = StringFromKey("Walker_60");
					Link.l1 = StringFromKey("Walker_61");
					Link.l1.go = "masters";
					Link.l2 = StringFromKey("Walker_62");
					Link.l2.go = "exit";
				break;
				//<-- masters

				case 17: //Офицер
					DeleteAttribute(Link, "l10");
					dialog.text = StringFromKey("Walker_63");
					Link.l1 = StringFromKey("Walker_64");
					Link.l1.go = "enlist_me";
					Link.l2 = StringFromKey("Walker_65");
					Link.l2.go = "exit_out";
				break;

				case 18: //Учителя
					DeleteAttribute(Link, "l10");
					dialog.text = StringFromKey("Walker_68", pchar, RandPhraseSimple(
								StringFromKey("Walker_66"),
								StringFromKey("Walker_67", pchar)));
					Link.l1 = StringFromKey("Walker_69");
					Link.l1.go = "Skill_1";
					Link.l2 = StringFromKey("Walker_70");
					Link.l2.go = "exit_out";
				break;
			}
		break;

		case "skeletons":
			dialog.text = StringFromKey("Walker_71");
			Link.l1 = StringFromKey("Walker_72");
			Link.l1.go = "exit";
		break;

		case "police":
			dialog.text = StringFromKey("Walker_73");
			Link.l1 = StringFromKey("Walker_74");
			Link.l1.go = "police1";
			Link.l2 = StringFromKey("Walker_75");
			Link.l2.go = "exit";
		break;

		case "police1":
			dialog.text = StringFromKey("Walker_76");
			Link.l1 = StringFromKey("Walker_77");
			Link.l1.go = "exit";
		break;

		case "health":
			dialog.text = StringFromKey("Walker_78");
			Link.l1 = StringFromKey("Walker_79");
			Link.l1.go = "health1";
			Link.l2 = StringFromKey("Walker_80");
			Link.l2.go = "exit";
		break;

		case "health1":
			dialog.text = StringFromKey("Walker_81");
			Link.l1 = StringFromKey("Walker_82");
			Link.l1.go = "exit";
		break;

		case "tavern":
			dialog.text = StringFromKey("Walker_83");
			Link.l1 = StringFromKey("Walker_84");
			Link.l1.go = "exit";
		break;

		case "officer":
			dialog.text = StringFromKey("Walker_85");
			Link.l1 = StringFromKey("Walker_86");
			Link.l1.go = "exit";
		break;

		case "shipyard":
			dialog.text = StringFromKey("Walker_87");
			Link.l1 = StringFromKey("Walker_88");
			Link.l1.go = "exit";
		break;

		case "masters":
			dialog.text = StringFromKey("Walker_89");
			Link.l1 = StringFromKey("Walker_90");
			Link.l1.go = "exit";
		break;

		case "torg":
			if (Pchar.questTemp.CapBloodLine == true)//homo закрыл баг по линейке.
			{
				dialog.Text = StringFromKey("Walker_91");
				Link.l1 = StringFromKey("Walker_92", NPChar.name);
				Link.l1.go = "exit";
				break;
			}
			if (CheckNPCQuestDate(npchar, "Torg_date"))
			{
				SetNPCQuestDate(npchar, "Torg_date");
				GiveItemToTrader(npchar);
				npchar.Merchant = true;
				npchar.money = makeint(LIGHT_TRADER_MIN_MONEY + frand(1.0) * LIGHT_TRADER_RAND_MONEY);
			}

			NextDiag.TempNode = "once_more";
			NextDiag.CurrentNode = "once_more";
			DialogExit();

			LaunchItemsTrade(NPChar);
		break;

		case "healing":
			AddMoneytoCharacter(Pchar, -200);
			LAi_SetCurHP(pchar, LAi_GetCharacterMaxHP(pchar));
			NextDiag.TempNode = "once_more_portion";
			NextDiag.CurrentNode = "once_more_portion";
			DialogExit();
		break;

		case "healing1":
			LAi_SetCurHP(pchar, LAi_GetCharacterMaxHP(pchar));
			NextDiag.TempNode = "thanx";
			NextDiag.CurrentNode = "thanx";
			DialogExit();
		break;

		case "reput":
			dialog.text = StringFromKey("Walker_93");
			Link.l1 = StringFromKey("Walker_94");
			Link.l1.go = "exit_out";
			Link.l2 = StringFromKey("Walker_95");
			Link.l2.go = "exit1";
		break;

		case "beg":
			AddMoneyToCharacter(pchar, -200);
			switch (Rand(2))
			{
				case 0:
					dialog.text = StringFromKey("Walker_96");
					Link.l1 = StringFromKey("Walker_97");
					Link.l1.go = "healing1";
				break;

				case 1:
					dialog.text = StringFromKey("Walker_98");
					Link.l1 = StringFromKey("Walker_99");
					Link.l1.go = "item";
				break;

				case 2:
					dialog.text = StringFromKey("Walker_100");
					Link.l1 = StringFromKey("Walker_101");
					Link.l1.go = "exit_than";
				break;
			}
			if (CheckAttribute(npchar, "talker"))
			{
				DeleteAttribute(npchar, "talker");
			}
		break;

		case "item":
			sTemp = "indian" + (1 + rand(9));
			AddItemLog(pchar, sTemp, "1", StringFromKey("InfoMessages_135", GetItemName(sTemp)), "Important_item");
			NextDiag.TempNode = "thanx";
			NextDiag.CurrentNode = "thanx";
			DialogExit();
		break;

		case "enlist_me":
			dialog.text = StringFromKey("Walker_108", RandPhraseSimple(
						StringFromKey("Walker_102"),
						StringFromKey("Walker_103")), GetFullName(NPChar), RandPhraseSimple(
						StringFromKey("Walker_104"),
						StringFromKey("Walker_105")), RandPhraseSimple(
						StringFromKey("Walker_106"),
						StringFromKey("Walker_107")));
			if (sti(PChar.Ship.Type) != SHIP_NOTUSED)
			{
				if (FindFreeRandomOfficer() > 0)
				{
					Link.l1 = StringFromKey("Walker_111", RandPhraseSimple(
								StringFromKey("Walker_109"),
								StringFromKey("Walker_110")));
					Link.l1.go = "hire";
				}
				else
				{
					Link.l1 = StringFromKey("Walker_112");
					Link.l1.go = "exit_out";
				}
				Link.l2 = StringFromKey("Walker_113");
				Link.l2.go = "ShowParam_exit";
				if (GetFreeCrewQuantity(pchar) >= 1)
				{
					Link.l3 = StringFromKey("Walker_116", RandPhraseSimple(
								StringFromKey("Walker_114"),
								StringFromKey("Walker_115")));
					Link.l3.go = "hire_sailor";
				}
				Link.l4 = StringFromKey("Walker_117");
				Link.l4.go = "exit_out";
			}
			else
			{
				Link.l1 = StringFromKey("Walker_118");
				Link.l1.go = "exit_out";
			}
		break;

		case "ShowParam_exit":
			NextDiag.TempNode = "OnceAgain";
			NextDiag.CurrentNode = "OnceAgain";
			DialogExit();
			LaunchCharacter(NPChar);
		break;

		case "OnceAgain":
			NextDiag.TempNode = "OnceAgain";
			dialog.text = StringFromKey("Walker_122", LinkRandPhrase(
						StringFromKey("Walker_119"),
						StringFromKey("Walker_120"),
						StringFromKey("Walker_121")));
			if (FindFreeRandomOfficer() > 0)
			{
				Link.l1 = StringFromKey("Walker_125", RandPhraseSimple(
							StringFromKey("Walker_123"),
							StringFromKey("Walker_124")));
				Link.l1.go = "hire";
			}
			else
			{
				Link.l1 = StringFromKey("Walker_126");
				Link.l1.go = "exit_out";
			}
			if (GetFreeCrewQuantity(pchar) >= 1)
			{
				Link.l2 = StringFromKey("Walker_127");
				Link.l2.go = "hire_sailor";
			}
			Link.l3 = StringFromKey("Walker_128");
			Link.l3.go = "exit_out";
		break;

		case "hire_sailor":
		//			if(GetCharacterSPECIAL(NPChar, SPECIAL_C) < GetCharacterSPECIAL(PChar, SPECIAL_C))
			if (PlayerRPGCheck_SPECIAL(SPECIAL_C, GetCharacterSPECIAL(NPChar, SPECIAL_C) + 1))
			{
				dialog.text = StringFromKey("Walker_129");
				Link.l1 = StringFromKey("Walker_130", NPChar.name);
				Link.l1.go = "exit_hire_sailor";
			}
			else
			{
				dialog.text = StringFromKey("Walker_131");
				Link.l1 = StringFromKey("Walker_132");
				Link.l1.go = "exit_out";
			}
		break;

		case "hire":
			dialog.text = StringFromKey("Walker_135", RandPhraseSimple(
						StringFromKey("Walker_133"),
						StringFromKey("Walker_134")));
			Link.l1 = StringFromKey("Walker_136");
			Link.l1.go = "exit_hire";
		break;

		case "Skill_1":
			sText = StringFromKey("Walker_137");
			switch (sti(npchar.diag.skill))
			{
				case 0: //Абордажник
					dialog.text = StringFromKey("Walker_138");
				break;

				case 1: //Боцман
					sTemp = "Leadership";
					dialog.text = StringFromKey("Walker_139");
					sText = StringFromKey("Walker_140");
				break;

				case 2: //Штурман
					sTemp = "Sailing";
					dialog.text = StringFromKey("Walker_141");
					sText = StringFromKey("Walker_142");
				break;

				case 3: //Канонир
					sTemp = "Accuracy";
					dialog.text = StringFromKey("Walker_143");
				break;

				case 4: //Канонир
					sTemp = "Cannons";
					dialog.text = StringFromKey("Walker_144");
				break;

				case 5: //Боцман
					sTemp = "Grappling";
					dialog.text = StringFromKey("Walker_145");
				break;

				case 6: //Плотник
					sTemp = "Repair";
					dialog.text = StringFromKey("Walker_146");
				break;

				case 7: //Казначей
					sTemp = "Commerce";
					dialog.text = StringFromKey("Walker_147");
				break;
			}
			bOk = !sti(npchar.diag.skill) && sti(PChar.skill.Fencing) >= SKILL_MAX && sti(PChar.skill.Defence) >= SKILL_MAX;
			if (sti(PChar.skill.(sTemp)) >= SKILL_MAX || bOk)
			{
				Link.l1 = StringFromKey("Walker_148");
				Link.l1.go = "exit_out";
				break;
			}
			if (!sti(npchar.diag.skill))
			{
				if (sti(PChar.skill.Fencing) < SKILL_MAX)
				{
					Link.l1 = StringFromKey("Walker_149");
					Link.l1.go = "Fencing";
				}
				if (sti(PChar.skill.Defence) < SKILL_MAX)
				{
					Link.l2 = StringFromKey("Walker_150");
					Link.l2.go = "Defence";
				}
			}
			else
			{
				Link.l1 = sText;
				Link.l1.go = "Skill_2";
			}
			Link.l3 = StringFromKey("Walker_151");
			if (!sti(npchar.diag.skill))
				Link.l3.go = "exit_fenc";
			else
				Link.l3.go = "exit_skill";
		break;

		case "Skill_2":
			bOk = CheckAttribute(NPChar, "diag.refuse");
			//цена назначается единожды и не меняется
			switch (sti(npchar.diag.skill))
			{
				case 0: //Абордажник
					if (!CheckAttribute(NPChar, "diag.refuse_fenc"))
					{
						//Если это впервые или отказ был общим
						if (CheckAttribute(NPChar, "FencTeach"))
						{
							iTemp = sti(Pchar.skill.Fencing);
							sTemp = StringFromKey("Walker_152");
						}
						else
						{
							iTemp = sti(Pchar.skill.Defence);
							sTemp = StringFromKey("Walker_153");
						}
					}
				break;

				case 1: //Боцман
					iTemp = sti(Pchar.skill.Leadership);
					sTemp = StringFromKey("Walker_154");
				break;

				case 2: //Штурман
					iTemp = sti(Pchar.skill.Sailing);
					sTemp = StringFromKey("Walker_155");
				break;

				case 3: //Канонир
					iTemp = sti(Pchar.skill.Accuracy);
					sTemp = StringFromKey("Walker_156");
				break;

				case 4: //Канонир
					iTemp = sti(Pchar.skill.Cannons);
					sTemp = StringFromKey("Walker_157");
				break;

				case 5: //Боцман
					iTemp = sti(Pchar.skill.Grappling);
					sTemp = StringFromKey("Walker_158");
				break;

				case 6: //Плотник
					iTemp = sti(Pchar.skill.Repair);
					sTemp = StringFromKey("Walker_159");
				break;

				case 7: //Казначей
					iTemp = sti(Pchar.skill.Commerce);
					sTemp = StringFromKey("Walker_160");
				break;
			}
			if (!CheckAttribute(NPChar, "diag.refuse_fenc") && !CheckAttribute(NPChar, "Diag.Sum"))
				NPChar.Diag.Sum = 5000 * (iTemp + 1);
			if (CheckAttribute(NPChar, "diag.refuse_fenc"))
			{
				dialog.text = StringFromKey("Walker_161");
				if (sti(PChar.skill.Fencing) < SKILL_MAX)
				{
					Link.l1 = StringFromKey("Walker_162");
					Link.l1.go = "Fencing";
				}
				if (sti(PChar.skill.Defence) < SKILL_MAX)
				{
					Link.l2 = StringFromKey("Walker_163");
					Link.l2.go = "Defence";
				}
				Link.l3 = StringFromKey("Walker_164");
				Link.l3.go = "exit_skill";
			}
			else
			{
				if (bOk)
					dialog.text = StringFromKey("Walker_165", FindMoneyString(sti(NPChar.Diag.Sum)), sTemp);
				else
					dialog.text = StringFromKey("Walker_166", FindMoneyString(sti(NPChar.Diag.Sum)));
				if (sti(Pchar.money) < sti(NPChar.Diag.Sum))
				{
					Link.l1 = StringFromKey("Walker_167");
					Link.l1.go = "exit_skill";
				}
				else
				{
					Link.l1 = StringFromKey("Walker_168");
					Link.l1.go = "Skill_3";
					Link.l2 = StringFromKey("Walker_169");
					Link.l2.go = "exit_skill";
				}
			}
		break;

		case "Skill_3":
			switch (sti(npchar.diag.skill))
			{
				case 0: //Абордажник
					if (CheckAttribute(NPChar, "FencTeach"))
						AddCharacterSkill(Pchar, SKILL_FENCING, 10);
					else
						AddCharacterSkill(Pchar, SKILL_DEFENCE, 10);
				break;

				case 1: //Боцман
					AddCharacterSkill(Pchar, SKILL_LEADERSHIP, 10);
				break;

				case 2: //Штурман
					AddCharacterSkill(Pchar, SKILL_SAILING, 10);
				break;

				case 3: //Канонир
					AddCharacterSkill(Pchar, SKILL_ACCURACY, 10);
				break;

				case 4: //Канонир
					AddCharacterSkill(Pchar, SKILL_CANNONS, 10);
				break;

				case 5: //Боцман
					AddCharacterSkill(Pchar, SKILL_GRAPPLING, 10);
				break;

				case 6: //Плотник
					AddCharacterSkill(Pchar, SKILL_REPAIR, 10);
				break;

				case 7: //Казначей
					AddCharacterSkill(Pchar, SKILL_COMMERCE, 10);
				break;
			}
			AddMoneytoCharacter(Pchar, -sti(NPChar.Diag.Sum));
			AddMoneytoCharacter(NPChar, sti(NPChar.Diag.Sum) + rand(10000));
			NPChar.SaveMoneyForDead = true; //Отсылочка
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_205"), "", 0, 4);
			WaitDate("", 0, 0, 0, 3 + drand(2), 0);
			RefreshLandTime();
			LAi_MethodDelay("LaunchFrameForm", 0);
			NextDiag.TempNode = "Skill_Over";
			NextDiag.CurrentNode = "Skill_Over";
			DialogExit();
		break;

		case "Skill_Over":
			dialog.text = StringFromKey("Walker_170");
			Link.l2 = StringFromKey("Walker_171");
			Link.l2.go = "exit_temp";
		break;

		case "thanx":
			dialog.text = StringFromKey("Walker_172");
			Link.l1 = StringFromKey("Walker_173");
			Link.l1.go = "exit_than";
		break;

		case "once_more_portion":
			dialog.text = StringFromKey("Walker_174");
			Link.l1 = StringFromKey("Walker_175");
			Link.l1.go = "healing";
			Link.l2 = StringFromKey("Walker_176");
			Link.l2.go = "exit_once_more_portion";
		break;

		case "once_more":
			dialog.text = StringFromKey("Walker_177");
			Link.l1 = StringFromKey("Walker_178");
			Link.l1.go = "torg";
			Link.l2 = StringFromKey("Walker_179");
			Link.l2.go = "exit_once_more";
		break;

		case "get_out":
			dialog.text = StringFromKey("Walker_180");
			Link.l2 = StringFromKey("Walker_181");
			Link.l2.go = "exit_out";
		break;

		case "sovet":
			NextDiag.TempNode = "sovet";
			if (NPChar.sex != "man")
			{
				dialog.text = StringFromKey("Walker_184", RandPhraseSimple(
							StringFromKey("Walker_182", pchar),
							StringFromKey("Walker_183")));
				Link.l1 = StringFromKey("Walker_185");
				Link.l1.go = "exit";
				break;
			}
			link.l10 = StringFromKey("Walker_189", LinkRandPhrase(
						StringFromKey("Walker_186"),
						StringFromKey("Walker_187"),
						StringFromKey("Walker_188")));
			link.l10.go = "rumours_citizen"; //повесил на горожанина, если нужны отедельные слухи, то пишем соответствующую реализацию
			dialog.text = StringFromKey("Walker_190");
			Link.l1 = StringFromKey("Walker_191");
			Link.l1.go = "advises";
			Link.l2 = StringFromKey("Walker_192");
			Link.l2.go = "exit";
		break;

		case "advises":
			switch (Rand(6))
			{
				case 0:
					dialog.text = StringFromKey("Walker_193");
					Link.l1 = StringFromKey("Walker_194");
					Link.l1.go = "exit";
				break;

				case 1:
					dialog.text = StringFromKey("Walker_195");
					Link.l1 = StringFromKey("Walker_196");
					Link.l1.go = "police1";
					Link.l2 = StringFromKey("Walker_197");
					Link.l2.go = "exit";
				break;

				case 2:
					dialog.text = StringFromKey("Walker_198");
					Link.l1 = StringFromKey("Walker_199");
					Link.l1.go = "health1";
					Link.l2 = StringFromKey("Walker_200");
					Link.l2.go = "exit";
				break;

				case 3:
					dialog.text = StringFromKey("Walker_201");
					Link.l1 = StringFromKey("Walker_202");
					Link.l1.go = "exit";
				break;

				case 4:
					dialog.text = StringFromKey("Walker_203");
					Link.l1 = StringFromKey("Walker_204");
					Link.l1.go = "exit";
				break;

				case 5:
					dialog.text = StringFromKey("Walker_205");
					Link.l1 = StringFromKey("Walker_206");
					Link.l1.go = "exit";
				break;

				case 6:
					dialog.text = StringFromKey("Walker_207");
					Link.l1 = StringFromKey("Walker_208");
					Link.l1.go = "exit";
				break;
			}
		break;

		case "exit_skill":
			NPChar.diag.refuse = "";
			NextDiag.TempNode = "Skill_2";
			NextDiag.CurrentNode = "Skill_2";
			DialogExit();
		break;

		case "exit_fenc":
			NPChar.diag.refuse_fenc = "";
			NextDiag.TempNode = "Skill_2";
			NextDiag.CurrentNode = "Skill_2";
			DialogExit();
		break;

		case "exit":
			NextDiag.TempNode = "sovet";
			NextDiag.CurrentNode = "sovet";
			DialogExit();
		break;

		case "exit_temp":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit1":
			ChangeCharacterReputation(pchar, 1);
			AddMoneytoCharacter(Pchar, -200);
			NextDiag.TempNode = "thanx";
			NextDiag.CurrentNode = "thanx";
			DialogExit();
		break;

		case "exit_out":
			NextDiag.TempNode = "get_out";
			NextDiag.CurrentNode = "get_out";
			DialogExit();

			if (CheckAttribute(npchar, "talker"))
			{
				DeleteAttribute(npchar, "talker");
			}
		break;

		case "exit_once_more":
			NextDiag.TempNode = "once_more";
			NextDiag.CurrentNode = "once_more";
			DialogExit();
		break;

		case "exit_once_more_portion":
			NextDiag.TempNode = "once_more_portion";
			NextDiag.CurrentNode = "once_more_portion";
			DialogExit();
		break;

		case "exit_than":
			NextDiag.TempNode = "thanx";
			NextDiag.CurrentNode = "thanx";
			DialogExit();
		break;

		case "exit_hire_sailor":
			AddCharacterCrew(pchar, 1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", LAi_FindNearestLocator2NPC(npchar, "reload"), "none", "", "", "", -1.0);
			DialogExit();
		break;

		case "exit_hire":
			DeleteAttribute(NPChar, "Diag");
			npchar.dialog.filename = "Officer_Man.c";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
		break;

		case "new question":
			dialog.text = NPCharRepPhrase(npchar,
					PCharRepPhrase(
							StringFromKey("Walker_212", LinkRandPhrase(
									StringFromKey("Walker_209", npchar),
									StringFromKey("Walker_210"),
									StringFromKey("Walker_211", PChar.name))),
							StringFromKey("Walker_216", LinkRandPhrase(
									StringFromKey("Walker_213"),
									StringFromKey("Walker_214", pchar, PChar.name),
									StringFromKey("Walker_215", pchar)))),
					PCharRepPhrase(
							StringFromKey("Walker_220", LinkRandPhrase(
									StringFromKey("Walker_217", GetAddress_Form(NPChar)),
									StringFromKey("Walker_218"),
									StringFromKey("Walker_219"))),
							StringFromKey("Walker_224", LinkRandPhrase(
									StringFromKey("Walker_221", npchar, GetAddress_Form(NPChar), PChar.lastname),
									StringFromKey("Walker_222", GetAddress_Form(NPChar)),
									StringFromKey("Walker_223")))));
			// homo 25/06/06
			link.l1 = StringFromKey("Walker_228", LinkRandPhrase(
						StringFromKey("Walker_225"),
						StringFromKey("Walker_226"),
						StringFromKey("Walker_227")));
			link.l1.go = "rumours_citizen";
			link.l5 = PCharRepPhrase(
						StringFromKey("Walker_231", RandPhraseSimple(
								StringFromKey("Walker_229"),
								StringFromKey("Walker_230"))),
						StringFromKey("Walker_234", RandPhraseSimple(
								StringFromKey("Walker_232"),
								StringFromKey("Walker_233"))));
			link.l5.go = "exit";
		break;

		//замечение по обнаженному оружию
		/*case "CitizenNotBlade": //HardCoffee ref
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, StringFromKey("Walker_218"), StringFromKey("Walker_219"));
				link.l1 = LinkRandPhrase(StringFromKey("Walker_220"), StringFromKey("Walker_221"), StringFromKey("Walker_222"));
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, StringFromKey("Walker_223", GetSexPhrase(StringFromKey("SexPhrase_130"),StringFromKey("SexPhrase_131"))), StringFromKey("Walker_224", GetSexPhrase(StringFromKey("SexPhrase_191"),StringFromKey("SexPhrase_192"))));
				link.l1 = RandPhraseSimple(StringFromKey("Walker_225", GetSexPhrase("",StringFromKey("SexEnding_1"))), StringFromKey("Walker_226"));
			}
			link.l1.go = "exit_temp";
		break;*/

		case "Man_FackYou": //реакция на попытку залезть в сундук на маяках и кладбищах
			dialog.text = StringFromKey("Walker_238", LinkRandPhrase(
						StringFromKey("Walker_235", pchar),
						StringFromKey("Walker_236", pchar),
						StringFromKey("Walker_237", pchar)));
			link.l1 = StringFromKey("Walker_239");
			link.l1.go = "exit_temp";
		break;
	}
}
