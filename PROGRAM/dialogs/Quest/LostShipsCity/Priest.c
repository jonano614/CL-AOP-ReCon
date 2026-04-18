#include "DIALOGS\Quest\LostShipsCity\SeekLSCCitizen_CN.c"

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;

	ProcessDialog_SeekLSCCitizenCN(NPChar, Link, NextDiag);

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;

	switch (Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = StringFromKey("Priest_1");
					link.l1 = StringFromKey("Priest_2", GetFullName(pchar));
					link.l1.go = "FT_1";
				}
				else
				{
					dialog.text = StringFromKey("Priest_3");
					link.l1 = StringFromKey("Priest_4", GetFullName(pchar));
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("Priest_5", pchar);
				link.l1 = StringFromKey("Priest_8", RandPhraseSimple(
							StringFromKey("Priest_6"),
							StringFromKey("Priest_7")));
				link.l1.go = "donation";
				link.l2 = StringFromKey("Priest_9");
				link.l2.go = "SeekCitizen";
				link.l3 = StringFromKey("Priest_10");
				link.l3.go = "int_quests";
				//квесты
				if (pchar.questTemp.LSC != "AdmiralIsWaiting" && !CheckAttribute(npchar, "quest.takeCandles") && pchar.questTemp.LSC.takeCandles != "over")
				{
					link.l4 = StringFromKey("Priest_11");
					link.l4.go = "askCandles";
				}
				if (CheckAttribute(npchar, "quest.takeCandles") && npchar.quest.takeCandles == "seek" && CheckCharacterItem(pchar, "mineral3"))
				{
					link.l4 = StringFromKey("Priest_12");
					link.l4.go = "takeCandles";
				}
				if (stf(pchar.Health.HP) < 60.0)
				{
					link.l5 = StringFromKey("Priest_13");
					link.l5.go = "healthAdd_1";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && !CheckAttribute(npchar, "quest.takeCandles"))
				{
					link.l8 = StringFromKey("Priest_14");
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.takeCandles") && npchar.quest.takeCandles == "seek")
				{
					link.l8 = StringFromKey("Priest_15");
					link.l8.go = "SeekGoods";
				}
				if (pchar.questTemp.LSC == "toSeekGoods" && CheckAttribute(npchar, "quest.takeCandles") && npchar.quest.takeCandles == "found")
				{
					link.l8 = StringFromKey("Priest_16");
					link.l8.go = "FSeekGoods";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					link.l8 = StringFromKey("Priest_17");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("Priest_18");
				link.l10.go = "exit";
			}
		break;

		case "FT_1":
			dialog.text = StringFromKey("Priest_19", pchar);
			Link.l1 = StringFromKey("Priest_20");
			Link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = StringFromKey("Priest_21", pchar);
			link.l1 = StringFromKey("Priest_22");
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = StringFromKey("Priest_23");
			link.l1 = StringFromKey("Priest_24", pchar);
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = StringFromKey("Priest_25", pchar);
			link.l1 = StringFromKey("Priest_26");
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = StringFromKey("Priest_27");
			link.l1 = StringFromKey("Priest_28");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//обнаружение ГГ в сундуках
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Man_FackYou":
			dialog.text = StringFromKey("Priest_32", LinkRandPhrase(
						StringFromKey("Priest_29", pchar),
						StringFromKey("Priest_30", pchar),
						StringFromKey("Priest_31")));
			link.l1 = StringFromKey("Priest_33");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("Priest_34");
			link.l1 = StringFromKey("Priest_35");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("Priest_39", LinkRandPhrase(
						StringFromKey("Priest_36", pchar),
						StringFromKey("Priest_37"),
						StringFromKey("Priest_38", pchar)));
			link.l1 = StringFromKey("Priest_43", LinkRandPhrase(
						StringFromKey("Priest_40"),
						StringFromKey("Priest_41"),
						StringFromKey("Priest_42")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("Priest_44");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("Priest_45");
				Link.l1 = StringFromKey("Priest_46");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("Priest_47", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("Priest_48");
					link.l1 = StringFromKey("Priest_49", pchar);
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("Priest_50", GetFullName(sld));
					Link.l1 = StringFromKey("Priest_51");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("Priest_52");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("Priest_53", GetFullName(sld));
					Link.l1 = StringFromKey("Priest_54");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("Priest_55");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("Priest_56");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("Priest_57");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;

		case "SeekCitizen_agree":
			sld = &characters[sti(npchar.quest.seekIdx)];
			npchar.quest.seekIdx.where = WhereLSCCitizen(sld);
			if (npchar.quest.seekIdx.where == "none")
			{
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("Priest_61", LinkRandPhrase(
								StringFromKey("Priest_58"),
								StringFromKey("Priest_59"),
								StringFromKey("Priest_60")));
					link.l1 = StringFromKey("Priest_64", RandPhraseSimple(
								StringFromKey("Priest_62"),
								StringFromKey("Priest_63")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("Priest_68", LinkRandPhrase(
								StringFromKey("Priest_65"),
								StringFromKey("Priest_66"),
								StringFromKey("Priest_67")));
					link.l1 = StringFromKey("Priest_71", RandPhraseSimple(
								StringFromKey("Priest_69"),
								StringFromKey("Priest_70")));
					link.l1.go = "exit";
				}
			}
			else
			{
				if (sld.sex == "man")
				{
					if (sld.location == "LostShipsCity_town")
					{
						string Str1 = npchar.location.locator;
						string Str2 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str1, 0, 5) == strcut(Str2, 0, 5))
						{
							dialog.text = StringFromKey("Priest_75", LinkRandPhrase(
										StringFromKey("Priest_72"),
										StringFromKey("Priest_73"),
										StringFromKey("Priest_74", pchar)));
						}
						else
						{
							dialog.text = StringFromKey("Priest_79", LinkRandPhrase(
										StringFromKey("Priest_76", npchar.quest.seekIdx.where),
										StringFromKey("Priest_77", npchar.quest.seekIdx.where),
										StringFromKey("Priest_78", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("Priest_83", LinkRandPhrase(
										StringFromKey("Priest_80", npchar.quest.seekIdx.where),
										StringFromKey("Priest_81"),
										StringFromKey("Priest_82")));
						}
						else
						{
							dialog.text = StringFromKey("Priest_87", LinkRandPhrase(
										StringFromKey("Priest_84", npchar.quest.seekIdx.where),
										StringFromKey("Priest_85", npchar.quest.seekIdx.where),
										StringFromKey("Priest_86", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("Priest_90", RandPhraseSimple(
								StringFromKey("Priest_88"),
								StringFromKey("Priest_89")));
					link.l1.go = "exit";
				}
				else
				{
					if (sld.location == "LostShipsCity_town")
					{
						string Str3 = npchar.location.locator;
						string Str4 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str3, 0, 5) == strcut(Str4, 0, 5))
						{
							dialog.text = StringFromKey("Priest_94", LinkRandPhrase(
										StringFromKey("Priest_91"),
										StringFromKey("Priest_92"),
										StringFromKey("Priest_93", pchar)));
						}
						else
						{
							dialog.text = StringFromKey("Priest_98", LinkRandPhrase(
										StringFromKey("Priest_95", npchar.quest.seekIdx.where),
										StringFromKey("Priest_96", npchar.quest.seekIdx.where),
										StringFromKey("Priest_97", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("Priest_102", LinkRandPhrase(
										StringFromKey("Priest_99", npchar.quest.seekIdx.where),
										StringFromKey("Priest_100"),
										StringFromKey("Priest_101")));
						}
						else
						{
							dialog.text = StringFromKey("Priest_106", LinkRandPhrase(
										StringFromKey("Priest_103", npchar.quest.seekIdx.where),
										StringFromKey("Priest_104", npchar.quest.seekIdx.where),
										StringFromKey("Priest_105", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("Priest_109", RandPhraseSimple(
								StringFromKey("Priest_107"),
								StringFromKey("Priest_108")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("Priest_110", pchar);
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("Priest_111");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("Priest_112");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l3") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l3 = StringFromKey("Priest_113");
				link.l3.go = "ansewer_3";
			}
			link.l10 = StringFromKey("Priest_114");
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("Priest_115");
			link.l1 = StringFromKey("Priest_116");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("Priest_117");
			link.l1 = StringFromKey("Priest_118");
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = StringFromKey("Priest_119");
			link.l1 = StringFromKey("Priest_120");
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("Priest_121");
			link.l1 = StringFromKey("Priest_122");
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = StringFromKey("Priest_123");
			link.l1 = StringFromKey("Priest_124");
			link.l1.go = "int_quests";
		break;
		//Исповедь
		case "donation":
			dialog.Text = StringFromKey("Priest_125", pchar);
			Link.l1 = StringFromKey("Priest_126", pchar);
			Link.l1.go = "No donation";
			if (makeint(PChar.money) >= 100)
			{
				Link.l2 = StringFromKey("Priest_127");
				Link.l2.go = "donation paid_100";
			}
			if (makeint(PChar.money) >= 1000)
			{
				Link.l3 = StringFromKey("Priest_128");
				Link.l3.go = "donation paid_1000";
			}
			if (makeint(PChar.money) >= 5000)
			{
				Link.l4 = StringFromKey("Priest_129");
				Link.l4.go = "donation paid_5000";
			}
		break;

		case "No donation":
			dialog.Text = StringFromKey("Priest_130");
			Link.l1 = StringFromKey("Priest_131");
			Link.l1.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = StringFromKey("Priest_132", pchar);
			Link.l1 = StringFromKey("Priest_133");
			Link.l1.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = StringFromKey("Priest_134", pchar);
			Link.l1 = StringFromKey("Priest_135");
			Link.l1.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = StringFromKey("Priest_136", pchar);
			Link.l1 = StringFromKey("Priest_137");
			Link.l1.go = "exit";
			AddDialogExitQuest("donation");
		break;

		//достать свечки
		case "askCandles":
			dialog.text = StringFromKey("Priest_138", pchar);
			link.l1 = StringFromKey("Priest_139");
			link.l1.go = "askCandles_1";
		break;
		case "askCandles_1":
			dialog.text = StringFromKey("Priest_140", pchar);
			link.l1 = StringFromKey("Priest_141");
			link.l1.go = "askCandles_2";
			link.l2 = StringFromKey("Priest_142");
			link.l2.go = "askCandles_3";
		break;
		case "askCandles_2":
			dialog.text = StringFromKey("Priest_143", pchar);
			link.l1 = StringFromKey("Priest_144", pchar);
			link.l1.go = "exit";
			npchar.quest.takeCandles = "seek";
			pchar.questTemp.LSC.takeCandles = "seek";
			npchar.quest.takeCandles.Qty = 0; //кол-во свечей
			AddQuestRecord("ISS_takeCandles", "1");
			AddLandQuestMark_Main(CharacterFromID("LSC_Trader"), "ISS_takeCandles");
		break;
		case "askCandles_3":
			dialog.text = StringFromKey("Priest_145", pchar);
			link.l1 = StringFromKey("Priest_146");
			link.l1.go = "exit";
			pchar.questTemp.LSC.takeCandles = "over";
			CloseQuestHeader("ISS_takeCandles");
			LSC_CheckReadyMainLine(); //проверка все ли готово для продолжения основной линейки
			RemoveLandQuestMark_Main(npchar, "ISS_takeCandles");
		break;
		case "takeCandles":
			iTemp = GetCharacterItem(pchar, "mineral3");
			npchar.quest.takeCandles.Qty = sti(npchar.quest.takeCandles.Qty) + iTemp;
			DeleteAttribute(pchar, "items.mineral3");
			if (sti(npchar.quest.takeCandles.Qty) < 400)
			{
				dialog.text = StringFromKey("Priest_147", pchar, FindQtyString(iTemp), FindQtyString(sti(npchar.quest.takeCandles.Qty)), FindQtyString(400 - sti(npchar.quest.takeCandles.Qty)));
				link.l1 = StringFromKey("Priest_148");
				link.l1.go = "exit";
				AddQuestRecord("ISS_takeCandles", "2");
				AddQuestUserData("ISS_takeCandles", "iQty", 400 - sti(npchar.quest.takeCandles.Qty));
			}
			else
			{
				dialog.text = StringFromKey("Priest_149", pchar);
				link.l1 = StringFromKey("Priest_150", pchar);
				link.l1.go = "takeCandles_ok";
			}
		break;
		case "takeCandles_ok":
			dialog.text = StringFromKey("Priest_151", pchar);
			link.l1 = StringFromKey("Priest_152");
			link.l1.go = "exit";
			pchar.skill.FreeSPECIAL = 1;
			npchar.quest.takeCandles = "found";
			pchar.questTemp.LSC.takeCandles = "over";
			AddQuestRecord("ISS_takeCandles", "3");
			CloseQuestHeader("ISS_takeCandles");
			LSC_CheckReadyMainLine(); //проверка все ли готово для продолжения основной линейки
			RemoveLandQuestMark_Main(npchar, "ISS_takeCandles");
		break;

		//поиск товаров на корвет не принеся свечи
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Priest_153", pchar),
						StringFromKey("Priest_154", pchar),
						StringFromKey("Priest_155", pchar),
						StringFromKey("Priest_156", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Priest_157"),
						StringFromKey("Priest_158", pchar),
						StringFromKey("Priest_159"),
						StringFromKey("Priest_160", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("Priest_161");
			link.l1 = StringFromKey("Priest_162");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = StringFromKey("Priest_163", pchar);
			link.l1 = StringFromKey("Priest_164");
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = StringFromKey("Priest_165", pchar);
			link.l1 = StringFromKey("Priest_166");
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = StringFromKey("Priest_167", pchar);
			link.l1 = StringFromKey("Priest_168", pchar);
			link.l1.go = "SeekGoods_5";
		break;
		case "SeekGoods_5":
			dialog.text = StringFromKey("Priest_169", pchar);
			link.l1 = StringFromKey("Priest_170", pchar);
			link.l1.go = "SeekGoods_6";
			link.l2 = StringFromKey("Priest_171", pchar);
			link.l2.go = "SeekGoods_6";
			link.l3 = StringFromKey("Priest_172", pchar);
			link.l3.go = "SeekGoods_6";
		break;
		case "SeekGoods_6":
			dialog.text = StringFromKey("Priest_173", pchar);
			link.l1 = StringFromKey("Priest_174");
			link.l1.go = "SeekGoods_7";
		break;
		case "SeekGoods_7":
			dialog.text = StringFromKey("Priest_175");
			link.l1 = StringFromKey("Priest_176");
			link.l1.go = "FSeekGoods_3"; // Переход напрямую в финальный кейс
		break;

		//поиск товаров на корвет принеся свечи
		case "FSeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Priest_177"),
						StringFromKey("Priest_178", pchar),
						StringFromKey("Priest_179", pchar),
						StringFromKey("Priest_180", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Priest_181"),
						StringFromKey("Priest_182", pchar),
						StringFromKey("Priest_183"),
						StringFromKey("Priest_184", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("FSeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "FSeekGoods_1":
			dialog.text = StringFromKey("Priest_185", pchar);
			link.l1 = StringFromKey("Priest_186");
			link.l1.go = "FSeekGoods_2";
		break;
		case "FSeekGoods_2":
			dialog.text = StringFromKey("Priest_187", pchar);
			link.l1 = StringFromKey("Priest_188");
			link.l1.go = "FSeekGoods_3";
		break;
		case "FSeekGoods_3":
			dialog.text = StringFromKey("Priest_189", pchar);
			link.l1 = StringFromKey("Priest_190");
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_MEDICAMENT, 50);
			AddQuestRecord("ISS_MainLine", "42");
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;

		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Priest_191", pchar),
						StringFromKey("Priest_192"),
						StringFromKey("Priest_193", pchar),
						StringFromKey("Priest_194", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Priest_195"),
						StringFromKey("Priest_196", pchar),
						StringFromKey("Priest_197"),
						StringFromKey("Priest_198"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("Priest_199");
			link.l1 = StringFromKey("Priest_200");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("Priest_201", pchar);
			link.l1 = StringFromKey("Priest_202");
			link.l1.go = "exit";
		break;

		//починка здоровья
		case "healthAdd_1":
			if (sti(pchar.Health.maxHP) == 60.0) // отлично
			{
				dialog.text = StringFromKey("Priest_203", GetHealthNameMaxSmall(pchar));
				link.l1 = StringFromKey("Priest_204");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Priest_205", GetHealthNameMaxSmall(pchar));
				link.l1 = StringFromKey("Priest_206");
				link.l1.go = "healthAdd_2";
			}
			link.l2 = StringFromKey("Priest_207");
			link.l2.go = "healthAdd_info";
		break;
		case "healthAdd_info":
			dialog.text = StringFromKey("Priest_208", pchar);
			link.l1 = StringFromKey("Priest_209");
			link.l1.go = "exit";
		break;
		case "healthAdd_2":
			dialog.text = StringFromKey("Priest_210", pchar);
			link.l1 = StringFromKey("Priest_211");
			link.l1.go = "healthAdd_3";
			link.l2 = StringFromKey("Priest_212");
			link.l2.go = "exit";
		break;
		case "healthAdd_3":
			if (npchar.quest.HealthMonth != environment.date.month)
			{
				dialog.text = StringFromKey("Priest_213");
				link.l1 = pcharrepphrase(
							StringFromKey("Priest_214"),
							StringFromKey("Priest_215"));
				link.l1.go = "healthAdd_4";
				link.l2 = StringFromKey("Priest_216", pchar);
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Priest_217", pchar);
				link.l1 = StringFromKey("Priest_220", RandPhraseSimple(
							StringFromKey("Priest_218"),
							StringFromKey("Priest_219")));
				link.l1.go = "exit";
			}
		break;
		case "healthAdd_4":
			dialog.text = StringFromKey("Priest_221");
			link.l1 = StringFromKey("Priest_222");
			link.l1.go = "exit";
			if (sti(pchar.Money) >= 100000)
			{
				link.l2 = StringFromKey("Priest_223", pchar);
				link.l2.go = "healthAdd_5";
			}
		break;
		case "healthAdd_5":
			AddMoneyToCharacter(pchar, -100000);
			AddCharacterMaxHealth(pchar, 4); // можно не проверять, тк явно меньше 51
			npchar.quest.HealthMonth = environment.date.month;
			dialog.text = StringFromKey("Priest_224");
			link.l1 = StringFromKey("Priest_225");
			link.l1.go = "exit";
		break;
	}
	NextDiag.PrevNode = NodeName;
}
