#include "DIALOGS\Rumours\Simple_rumors.c"
#include "DIALOGS\Quest\LostShipsCity\SeekLSCCitizen_CN.c"

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
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
					dialog.text = StringFromKey("Mentos_4", LinkRandPhrase(
								StringFromKey("Mentos_1", pchar, GetFullName(npchar)),
								StringFromKey("Mentos_2", pchar, GetFullName(npchar)),
								StringFromKey("Mentos_3", pchar, GetFullName(npchar))));
					link.l1 = StringFromKey("Mentos_7", RandPhraseSimple(
								StringFromKey("Mentos_5", GetFullName(pchar)),
								StringFromKey("Mentos_6", GetFullName(pchar))));
					link.l1.go = "FT_1";
				}
				else
				{
					dialog.text = StringFromKey("Mentos_11", LinkRandPhrase(
								StringFromKey("Mentos_8", pchar, GetFullName(npchar)),
								StringFromKey("Mentos_9", pchar, GetFullName(npchar)),
								StringFromKey("Mentos_10", GetFullName(npchar))));
					link.l1 = StringFromKey("Mentos_14", RandPhraseSimple(
								StringFromKey("Mentos_12", GetFullName(pchar)),
								StringFromKey("Mentos_13", GetFullName(pchar))));
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("Mentos_18", LinkRandPhrase(
							StringFromKey("Mentos_15"),
							StringFromKey("Mentos_16"),
							StringFromKey("Mentos_17")));
				link.l1 = StringFromKey("Mentos_21", RandPhraseSimple(
							StringFromKey("Mentos_19"),
							StringFromKey("Mentos_20")));
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("Mentos_24", RandPhraseSimple(
							StringFromKey("Mentos_22"),
							StringFromKey("Mentos_23")));
				link.l2.go = "int_quests";
				//разговор о судьбе Декстера
				if (CheckAttribute(npchar, "quest.DeksterDestiny") && CheckCharacterItem(pchar, "shark_tooth") && CheckActiveQuest("LSC_findDekster"))
				{
					link.l7 = StringFromKey("Mentos_25");
					link.l7.go = "DeksterDestiny";
				}
				//сбор отряда самоубийц
				if (npchar.id == "Ment_6" && !CheckAttribute(npchar, "quest.NoSuicideSquad") && CheckAttribute(pchar, "questTemp.LSC.suicideSquad") && !CheckAttribute(pchar, "questTemp.LSC.suicideSquad." + GetCharacterIndex(npchar.id)))
				{
					link.l1 = StringFromKey("Mentos_26");
					link.l1.go = "SuicideSquad";
				}
				//план-капкан от ментов
				if (npchar.id == "Ment_6" && CheckAttribute(pchar, "questTemp.LSC.MentosHelp.Ready") && CheckAttribute(pchar, "questTemp.LSC.suicideSquad." + GetCharacterIndex(npchar.id)))
				{
					link.l1 = StringFromKey("Mentos_27", pchar);
					link.l1.go = "MentosHelp";
				}
				//план не нужен, все готово к штурму
				if (npchar.id == "Ment_6" && CheckAttribute(pchar, "questTemp.LSC.suicideSquad") && CheckAttribute(npchar, "quest.NoPlanGoReady") && LSC_CheckDeceasedCaspers() == 0)
				{
					link.l1 = StringFromKey("Mentos_28");
					link.l1.go = "MentosHelp_1";
				}
				//думаем о помощи ментам
				if (npchar.id == "Ment_6" && CheckAttribute(npchar, "quest.WaitPlan") && !CheckAttribute(pchar, "questTemp.LSC.RivadosHelp") && !CheckAttribute(pchar, "questTemp.LSC.MentosHelp") && CheckAttribute(pchar, "questTemp.LSC.suicideSquad"))
				{
					link.l1 = StringFromKey("Mentos_29");
					link.l1.go = "SuicideSquad_19";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods" && npchar.id == "Ment_6" && CheckAttribute(pchar, "questTemp.LSC.additional.powder") && sti(pchar.questTemp.LSC.additional.powder))
				{
					link.l8 = StringFromKey("Mentos_30");
					link.l8.go = "SeekGoods";
				}
				//поиски команды на корвет
				if (CheckAttribute(npchar, "quest.toSeekPeopleInCrew"))
				{
					link.l8 = StringFromKey("Mentos_31");
					link.l8.go = "SeekCrew";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew") && npchar.id == "Ment_6" && CheckAttribute(pchar, "questTemp.LSC.crew.ment_6"))
				{
					link.l8 = StringFromKey("Mentos_32");
					link.l8.go = "SeekCrew2";
				}
				if (pchar.questTemp.LSC == "MechanicIsArrest_toResidence" && npchar.id == "Ment_6" && CheckAttribute(npchar, "quest.LSCofficer")
					&& !CheckAttribute(npchar, "quest.ReadyToResidenceFight"))
				{
					link.l8 = StringFromKey("Mentos_33");
					link.l8.go = "SeekCrew3";
				}
				if (pchar.questTemp.LSC == "MechanicIsArrest_toResidence" && npchar.id == "Ment_6" && !CheckAttribute(npchar, "quest.LSCofficer"))
				{
					link.l8 = StringFromKey("Mentos_34");
					link.l8.go = "SeekCrew4";
				}
				link.l10 = StringFromKey("Mentos_35");
				link.l10.go = "exit";
			}
		break;

		case "FT_1":
			dialog.text = StringFromKey("Mentos_39", LinkRandPhrase(
						StringFromKey("Mentos_36"),
						StringFromKey("Mentos_37"),
						StringFromKey("Mentos_38")));
			link.l1 = StringFromKey("Mentos_42", RandPhraseSimple(
						StringFromKey("Mentos_40"),
						StringFromKey("Mentos_41")));
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
			dialog.text = StringFromKey("Mentos_46", LinkRandPhrase(
						StringFromKey("Mentos_43", pchar),
						StringFromKey("Mentos_44", pchar),
						StringFromKey("Mentos_45", pchar)));
			link.l1 = StringFromKey("Mentos_47");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("Mentos_48");
			link.l1 = StringFromKey("Mentos_49");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("Mentos_53", LinkRandPhrase(
						StringFromKey("Mentos_50", pchar),
						StringFromKey("Mentos_51"),
						StringFromKey("Mentos_52", pchar)));
			link.l1 = StringFromKey("Mentos_57", LinkRandPhrase(
						StringFromKey("Mentos_54"),
						StringFromKey("Mentos_55"),
						StringFromKey("Mentos_56")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("Mentos_58", npchar);
				link.l1 = StringFromKey("Mentos_62", LinkRandPhrase(
							StringFromKey("Mentos_59"),
							StringFromKey("Mentos_60"),
							StringFromKey("Mentos_61")));
			}
			else
			{
				dialog.text = StringFromKey("Mentos_63", npchar);
				link.l1 = StringFromKey("Mentos_66", RandPhraseSimple(
							StringFromKey("Mentos_64"),
							StringFromKey("Mentos_65")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("Mentos_67");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("Mentos_68");
				Link.l1 = StringFromKey("Mentos_69");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("Mentos_70", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("Mentos_71");
					link.l1 = StringFromKey("Mentos_72", pchar);
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("Mentos_73", GetFullName(sld));
					Link.l1 = StringFromKey("Mentos_74");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("Mentos_75");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("Mentos_76", GetFullName(sld));
					Link.l1 = StringFromKey("Mentos_77");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("Mentos_78");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("Mentos_79");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("Mentos_80");
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
					dialog.text = StringFromKey("Mentos_84", LinkRandPhrase(
								StringFromKey("Mentos_81"),
								StringFromKey("Mentos_82"),
								StringFromKey("Mentos_83")));
					link.l1 = StringFromKey("Mentos_87", RandPhraseSimple(
								StringFromKey("Mentos_85"),
								StringFromKey("Mentos_86")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("Mentos_91", LinkRandPhrase(
								StringFromKey("Mentos_88"),
								StringFromKey("Mentos_89"),
								StringFromKey("Mentos_90")));
					link.l1 = StringFromKey("Mentos_94", RandPhraseSimple(
								StringFromKey("Mentos_92"),
								StringFromKey("Mentos_93")));
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
							dialog.text = StringFromKey("Mentos_98", LinkRandPhrase(
										StringFromKey("Mentos_95"),
										StringFromKey("Mentos_96"),
										StringFromKey("Mentos_97", pchar)));
						}
						else
						{
							dialog.text = StringFromKey("Mentos_102", LinkRandPhrase(
										StringFromKey("Mentos_99", npchar.quest.seekIdx.where),
										StringFromKey("Mentos_100", npchar.quest.seekIdx.where),
										StringFromKey("Mentos_101", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("Mentos_106", LinkRandPhrase(
										StringFromKey("Mentos_103", npchar.quest.seekIdx.where),
										StringFromKey("Mentos_104"),
										StringFromKey("Mentos_105")));
						}
						else
						{
							dialog.text = StringFromKey("Mentos_110", LinkRandPhrase(
										StringFromKey("Mentos_107", npchar.quest.seekIdx.where),
										StringFromKey("Mentos_108", npchar.quest.seekIdx.where),
										StringFromKey("Mentos_109", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("Mentos_113", RandPhraseSimple(
								StringFromKey("Mentos_111"),
								StringFromKey("Mentos_112")));
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
							dialog.text = StringFromKey("Mentos_117", LinkRandPhrase(
										StringFromKey("Mentos_114"),
										StringFromKey("Mentos_115"),
										StringFromKey("Mentos_116", pchar)));
						}
						else
						{
							dialog.text = StringFromKey("Mentos_121", LinkRandPhrase(
										StringFromKey("Mentos_118", npchar.quest.seekIdx.where),
										StringFromKey("Mentos_119", npchar.quest.seekIdx.where),
										StringFromKey("Mentos_120", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("Mentos_125", LinkRandPhrase(
										StringFromKey("Mentos_122", npchar.quest.seekIdx.where),
										StringFromKey("Mentos_123"),
										StringFromKey("Mentos_124")));
						}
						else
						{
							dialog.text = StringFromKey("Mentos_129", LinkRandPhrase(
										StringFromKey("Mentos_126", npchar.quest.seekIdx.where),
										StringFromKey("Mentos_127", npchar.quest.seekIdx.where),
										StringFromKey("Mentos_128", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("Mentos_132", RandPhraseSimple(
								StringFromKey("Mentos_130"),
								StringFromKey("Mentos_131")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("Mentos_136", LinkRandPhrase(
						StringFromKey("Mentos_133", pchar),
						StringFromKey("Mentos_134"),
						StringFromKey("Mentos_135")));
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("Mentos_140", LinkRandPhrase(
							StringFromKey("Mentos_137"),
							StringFromKey("Mentos_138"),
							StringFromKey("Mentos_139")));
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("Mentos_144", LinkRandPhrase(
							StringFromKey("Mentos_141"),
							StringFromKey("Mentos_142"),
							StringFromKey("Mentos_143")));
				link.l2.go = "ansewer_2";
			}
			link.l10 = StringFromKey("Mentos_147", RandPhraseSimple(
						StringFromKey("Mentos_145"),
						StringFromKey("Mentos_146", pchar)));
			link.l10.go = "exit";
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("Mentos_151", LinkRandPhrase(
						StringFromKey("Mentos_148"),
						StringFromKey("Mentos_149"),
						StringFromKey("Mentos_150")));
			link.l1 = StringFromKey("Mentos_154", RandPhraseSimple(
						StringFromKey("Mentos_152"),
						StringFromKey("Mentos_153")));
			link.l1.go = "exit";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("Mentos_158", LinkRandPhrase(
						StringFromKey("Mentos_155"),
						StringFromKey("Mentos_156"),
						StringFromKey("Mentos_157")));
			link.l1 = StringFromKey("Mentos_161", RandPhraseSimple(
						StringFromKey("Mentos_159"),
						StringFromKey("Mentos_160")));
			link.l1.go = "exit";
			NextDiag.(NodePrevName).l2 = true;
		break;
		//диалог Воркмента перед боем на Веласко
		case "NarvalAssault":
			if (sti(pchar.questTemp.LSC.qtyDeadNarvals) == 7) dialog.text = StringFromKey("Mentos_162");
			else dialog.text = StringFromKey("Mentos_163");
			link.l1 = StringFromKey("Mentos_164");
			link.l1.go = "NarvalAssault_1";
		break;
		case "NarvalAssault_1":
			dialog.text = StringFromKey("Mentos_165");
			link.l1 = StringFromKey("Mentos_166");
			link.l1.go = "NarvalAssaultExit";
		break;
		case "NarvalAssaultExit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload68", "LSC_NarvalDestroyedGotoVelasco", 5);
			LAi_SetStayTypeNoGroup(npchar);
		break;
		//диалог штурмовиков перед боем на Веласко
		case "OffNarval":
			dialog.text = StringFromKey("Mentos_170", LinkRandPhrase(
						StringFromKey("Mentos_167"),
						StringFromKey("Mentos_168"),
						StringFromKey("Mentos_169")));
			link.l1 = StringFromKey("Mentos_171");
			link.l1.go = "exit";
		break;
		//диалог Воркмента после боя на Веласко
		case "AffterFightNWorkman":
			dialog.text = StringFromKey("Mentos_172");
			link.l1 = StringFromKey("Mentos_173");
			link.l1.go = "exit";
			AddDialogExitQuest("LSC_NavalExitVelasco");
			//менты на фоне топают к выходу, дабы потом не исчезать в воздухе
			for (int i = 1; i <= 3; i++)
			{
				int iTemp = GetCharacterIndex("Ment_" + i);
				if (iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
				{
					LAi_SetActorType(&characters[iTemp]);
					LAi_ActorGoToLocation(&characters[iTemp], "reload", LAi_FindNearestLocator2NPC(&characters[iTemp], "reload"), "none", "", "", "", 0.0);
				}
			}
		break;
		//диалог штурмовиков после боя на Веласко
		case "AffterFightN":
			dialog.text = StringFromKey("Mentos_177", LinkRandPhrase(
						StringFromKey("Mentos_174"),
						StringFromKey("Mentos_175"),
						StringFromKey("Mentos_176")));
			link.l1 = StringFromKey("Mentos_178");
			link.l1.go = "exit";
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Mentos_179"),
						StringFromKey("Mentos_180"),
						StringFromKey("Mentos_181"),
						StringFromKey("Mentos_182", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Mentos_183"),
						StringFromKey("Mentos_184"),
						StringFromKey("Mentos_185"),
						StringFromKey("Mentos_186"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("Mentos_187");
			link.l1 = StringFromKey("Mentos_188");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = StringFromKey("Mentos_189");
			link.l1 = StringFromKey("Mentos_190", pchar);
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = StringFromKey("Mentos_191");
			link.l1 = StringFromKey("Mentos_192");
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = StringFromKey("Mentos_193");
			link.l1 = StringFromKey("Mentos_194");
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_WEAPON, 50);
			AddCharacterGoods(pchar, GOOD_POWDER, 200);
			AddQuestRecord("ISS_MainLine", "53");
			pchar.questTemp.LSC.additional.powder = false;
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
		//поиски команды на корвет
		case "SeekCrew":
			dialog.text = StringFromKey("Mentos_195");
			link.l1 = StringFromKey("Mentos_196");
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("Mentos_197");
			link.l1 = StringFromKey("Mentos_198");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("Mentos_199");
			link.l1 = StringFromKey("Mentos_200");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("Mentos_201");
			link.l1 = StringFromKey("Mentos_202");
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.toSeekPeopleInCrew");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.LSC.crew.ment_6 = true;
			npchar.quest.LSCofficer = true;
			AddQuestRecord("ISS_MainLine", "57");
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;

		case "SeekCrew2":
			dialog.text = StringFromKey("Mentos_203");
			link.l1 = StringFromKey("Mentos_204");
			link.l1.go = "exit";
		break;

		case "SeekCrew3":
			dialog.text = StringFromKey("Mentos_205");
			link.l1 = StringFromKey("Mentos_206");
			link.l1.go = "exit";
			npchar.quest.AngerAtAdmiral = sti(npchar.quest.AngerAtAdmiral) + 1; //накапливаем злость на адмирала
			npchar.quest.ReadyToResidenceFight = true;
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;

		case "SeekCrew4":
			dialog.text = StringFromKey("Mentos_207");
			link.l1 = StringFromKey("Mentos_208", pchar);
			link.l1.go = "SeekCrew4_1";
		break;
		case "SeekCrew4_1":
			dialog.text = StringFromKey("Mentos_209");
			link.l1 = StringFromKey("Mentos_210");
			link.l1.go = "SeekCrew4_2";
		break;
		case "SeekCrew4_2":
			dialog.text = StringFromKey("Mentos_211");
			link.l1 = StringFromKey("Mentos_212");
			link.l1.go = "SeekCrew4_3";
		break;
		case "SeekCrew4_3":
			dialog.text = StringFromKey("Mentos_213");
			link.l1 = StringFromKey("Mentos_214");
			link.l1.go = "exit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.quest.LSCofficer = true;
			AddQuestRecord("ISS_MainLine", "64");
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
		//финальный разговор мента_6 перед посадкой на корвет
		case "MentOffIsLife":
			dialog.text = StringFromKey("Mentos_215");
			link.l1 = StringFromKey("Mentos_216");
			link.l1.go = "MentOffIsLife_1";
		break;
		case "MentOffIsLife_1":
		//Npchar.quest.OfficerPrice = (rand(4)+1)*1000; TODO_salary
			dialog.text = StringFromKey("Mentos_217");
			link.l1 = StringFromKey("Mentos_218");
			link.l1.go = "MentOffIsLife_2";
		break;
		case "MentOffIsLife_2":
			dialog.text = StringFromKey("Mentos_219");
			link.l1 = StringFromKey("Mentos_220");
			link.l1.go = "MentOffIsLife_3";
		break;
		case "MentOffIsLife_3":
			dialog.text = StringFromKey("Mentos_221");
			link.l1 = StringFromKey("Mentos_222");
			link.l1.go = "MentOffIsLife_4";
		break;
		case "MentOffIsLife_4":
			dialog.text = StringFromKey("Mentos_223");
			link.l1 = StringFromKey("Mentos_224");
			link.l1.go = "exit_hire";
		break;
		case "exit_hire":
			DeleteAttribute(npchar, "city");
			chrDisableReloadToLocation = false;
			AddQuestRecord("ISS_MainLine", "62");
			NPChar.quest.meeting = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "GetOutNow":
			if (CheckAttribute(npchar, "warning_date") && GetNpcQuestPastDayParam(npchar, "warning_date") < 1)
			{
				dialog.text = StringFromKey("Mentos_225", pchar);
				link.l1 = StringFromKey("Mentos_226");
				link.l1.go = "fight";
			}
			else
			{
				//что бы лишний раз не пинговали ввел групповое палево
				npchar.near_brothers = FindNearCharacters(pchar, 10.0, -1.0, 180.0, 0.01, false, false);
				if (sti(npchar.near_brothers) > 1)
					dialog.text = StringFromKey("Mentos_230", LinkRandPhrase(
					StringFromKey("Mentos_227"),
					StringFromKey("Mentos_228"),
					StringFromKey("Mentos_229")));
				else
					dialog.text = StringFromKey("Mentos_234", LinkRandPhrase(
					StringFromKey("Mentos_231"),
					StringFromKey("Mentos_232"),
					StringFromKey("Mentos_233")));
				link.l1 = StringFromKey("Mentos_238", LinkRandPhrase(
							StringFromKey("Mentos_235"),
							StringFromKey("Mentos_236"),
							StringFromKey("Mentos_237")));
				link.l1.go = "GetOutNowExit";
			}
		break;
		case "GetOutNowExit":
		//вначале нас запоминают все кто находились рядом на момент начала диалога
			UpdateBrothersWarningTime(sti(npchar.near_brothers));
			DeleteAttribute(npchar, "npchar.near_brothers");
			//потом на нас еще посмотрят и запомнят менты подошедшие в процессе диалога
			UpdateBrothersWarningTime(FindNearCharacters(pchar, 10.0, -1.0, 180.0, 0.01, false, false));
			npchar.time_to_go = 1;
			SaveCurrentNpcQuestDateParam(npchar, "warning_date");
			NextDiag.CurrentNode = "First time";
			LAi_SetWarriorTypeNoGroup(npchar);
			DialogExit();
		break;

		//Разговор Уоркмана по поводу Декстера
		case "talkAboutDextar":
			dialog.text = StringFromKey("Mentos_239");
			link.l1 = StringFromKey("Mentos_240");
			link.l1.go = "talkAboutDextar_1";
		break;
		case "talkAboutDextar_1":
			dialog.text = StringFromKey("Mentos_241");
			link.l1 = StringFromKey("Mentos_242");
			link.l1.go = "talkAboutDextar_2";
		break;
		case "talkAboutDextar_2":
			dialog.text = StringFromKey("Mentos_243");
			link.l1 = StringFromKey("Mentos_244");
			link.l1.go = "talkAboutDextar_3";
		break;
		case "talkAboutDextar_3":
			dialog.text = StringFromKey("Mentos_245");
			link.l1 = StringFromKey("Mentos_246");
			link.l1.go = "talkAboutDextar_4";
		break;
		case "talkAboutDextar_4":
			DialogExit();
			GiveItem2Character(pchar, "shark_tooth");
			NextDiag.CurrentNode = "First time";
			LAi_SetWarriorTypeNoGroup(npchar);
			AddQuestRecord("LSC_findDekster", "13");
			pchar.questTemp.LSC.lostDecster = "fromMentos";
			chrDisableReloadToLocation = false;
			AddLandQuestMark_Main(CharacterFromID("LSC_Prisoner1"), "LSC_findDekster");
		break;

		//Уоркман страшную ПРАВДУ о судьбе ДЕКСТЕРЕ
		case "DeksterDestiny":
			dialog.text = StringFromKey("Mentos_247");
			link.l1 = StringFromKey("Mentos_248");
			link.l1.go = "DeksterDestiny_1";
		break;
		case "DeksterDestiny_1":
			dialog.text = StringFromKey("Mentos_249");
			link.l1 = StringFromKey("Mentos_250");
			link.l1.go = "DeksterDestiny_2";
		break;
		case "DeksterDestiny_2":
			dialog.text = StringFromKey("Mentos_251");
			link.l1 = StringFromKey("Mentos_252");
			link.l1.go = "DeksterDestiny_3";
		break;
		case "DeksterDestiny_3":
			dialog.text = StringFromKey("Mentos_253");
			link.l1 = StringFromKey("Mentos_254");
			link.l1.go = "DeksterDestiny_4";
		break;
		case "DeksterDestiny_4":
			dialog.text = StringFromKey("Mentos_255");
			link.l1 = StringFromKey("Mentos_256");
			link.l1.go = "DeksterDestiny_5";
		break;
		case "DeksterDestiny_5":
			dialog.text = StringFromKey("Mentos_257");
			link.l1 = StringFromKey("Mentos_258");
			link.l1.go = "DeksterDestiny_6";
		break;
		case "DeksterDestiny_6":
			dialog.text = StringFromKey("Mentos_259");
			link.l1 = StringFromKey("Mentos_260");
			link.l1.go = "DeksterDestiny_7";
		break;
		case "DeksterDestiny_7":
			dialog.text = StringFromKey("Mentos_261");
			link.l1 = StringFromKey("Mentos_262");
			link.l1.go = "DeksterDestiny_8";
		break;
		case "DeksterDestiny_8":
			dialog.text = StringFromKey("Mentos_263");
			link.l1 = StringFromKey("Mentos_264");
			link.l1.go = "DeksterDestiny_9";
		break;
		case "DeksterDestiny_9":
			dialog.text = StringFromKey("Mentos_265");
			link.l1 = StringFromKey("Mentos_266");
			link.l1.go = "DeksterDestiny_10";
		break;
		case "DeksterDestiny_10":
			dialog.text = StringFromKey("Mentos_267");
			link.l1 = StringFromKey("Mentos_268");
			link.l1.go = "DeksterDestiny_11";
			link.l2 = StringFromKey("Mentos_269");
			link.l2.go = "DeksterDestiny_11";
			link.l3 = StringFromKey("Mentos_270");
			link.l3.go = "DeksterDestiny_11";
		break;
		case "DeksterDestiny_11":
			dialog.text = StringFromKey("Mentos_271");
			link.l1 = StringFromKey("Mentos_272");
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.DeksterDestiny");
			npchar.quest.AngerAtAdmiral = sti(npchar.quest.AngerAtAdmiral) + 1; //накапливаем злость на адмирала
			sld = &Items[FindItem("shark_tooth")];
			sld.price = 330;
			sld.rare = 0.1;
			DeleteAttribute(sld, "ItemType");
			AddQuestRecord("LSC_findDekster", "16");
			RemoveLandQuestMark_Main(npchar, "LSC_findDekster");
		break;

		//Разговор Уоркмана по поводу Сесиль
		case "talkAboutSesil":
			dialog.text = StringFromKey("Mentos_273");
			link.l1 = StringFromKey("Mentos_274");
			link.l1.go = "talkAboutSesil_1";
		break;
		case "talkAboutSesil_1":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;

		//сбор отряда самоубийц
		case "SuicideSquad":
			if (!CheckAttribute(pchar, "questTemp.LSC.suicideSquad_TalkCounter"))
				pchar.questTemp.LSC.suicideSquad_TalkCounter = 0;
			pchar.questTemp.LSC.suicideSquad_TalkCounter = sti(pchar.questTemp.LSC.suicideSquad_TalkCounter) + 1;

			dialog.text = StringFromKey("Mentos_275", GetFullName(pchar));
			link.l1 = StringFromKey("Mentos_276");
			link.l1.go = "SuicideSquad_1";
		break;
		case "SuicideSquad_1":
			dialog.text = StringFromKey("Mentos_277");
			link.l1 = StringFromKey("Mentos_278");
			link.l1.go = "SuicideSquad_2";
		break;
		case "SuicideSquad_2":
			dialog.text = StringFromKey("Mentos_279", pchar);
			link.l1 = StringFromKey("Mentos_280");
			link.l1.go = "SuicideSquad_3";
		break;
		case "SuicideSquad_3":
			dialog.text = StringFromKey("Mentos_281");
			link.l1 = StringFromKey("Mentos_282");
			link.l1.go = "SuicideSquad_4";
		break;
		case "SuicideSquad_4":
			dialog.text = StringFromKey("Mentos_283");
			link.l1 = StringFromKey("Mentos_284");
			link.l1.go = "SuicideSquad_5";
		break;
		case "SuicideSquad_5":
			dialog.text = StringFromKey("Mentos_285");
			link.l1 = StringFromKey("Mentos_286");
			link.l1.go = "SuicideSquad_6";
		break;
		case "SuicideSquad_6":
			dialog.text = StringFromKey("Mentos_287");
			link.l1 = StringFromKey("Mentos_288");
			link.l1.go = "SuicideSquad_7";
		break;
		case "SuicideSquad_7":
			dialog.text = StringFromKey("Mentos_289");
			link.l1 = StringFromKey("Mentos_290");
			link.l1.go = "SuicideSquad_10";
			link.l2 = StringFromKey("Mentos_291");
			link.l2.go = "SuicideSquad_8";
		break;
		case "SuicideSquad_8":
			dialog.text = StringFromKey("Mentos_292");
			link.l1 = StringFromKey("Mentos_293");
			link.l1.go = "SuicideSquad_9";
		break;
		case "SuicideSquad_9":
			dialog.text = StringFromKey("Mentos_294");
			link.l1 = StringFromKey("Mentos_295", pchar);
			link.l1.go = "SuicideSquad_10";
		break;
		case "SuicideSquad_10":
			dialog.text = StringFromKey("Mentos_296", GetFullName(pchar));
			link.l1 = StringFromKey("Mentos_297");
			link.l1.go = "SuicideSquad_11_1";
			link.l2 = StringFromKey("Mentos_298");
			link.l2.go = "SuicideSquad_11";
			link.l3 = StringFromKey("Mentos_299");
			link.l3.go = "SuicideSquad_11_1";
		break;
		case "SuicideSquad_11_1":
			dialog.text = StringFromKey("Mentos_300");
			link.l1 = StringFromKey("Mentos_301");
			link.l1.go = "SuicideSquad_10";
		break;
		case "SuicideSquad_11":
			dialog.text = StringFromKey("Mentos_302");
			link.l1 = StringFromKey("Mentos_303");
			link.l1.go = "SuicideSquad_12";
		break;
		case "SuicideSquad_12":
			dialog.text = StringFromKey("Mentos_304");
			link.l1 = StringFromKey("Mentos_305");
			link.l1.go = "SuicideSquad_13";
		break;
		case "SuicideSquad_13":
			dialog.text = StringFromKey("Mentos_306");
			link.l1 = StringFromKey("Mentos_307");
			link.l1.go = "SuicideSquad_14";
		break;
		case "SuicideSquad_14":
			dialog.text = StringFromKey("Mentos_308");
			link.l1 = StringFromKey("Mentos_309");
			link.l1.go = "SuicideSquad_15";
		break;
		case "SuicideSquad_15":
			dialog.text = StringFromKey("Mentos_310");
			link.l1 = StringFromKey("Mentos_311");
			link.l1.go = "SuicideSquad_16";
		break;
		case "SuicideSquad_16":
			if (sti(npchar.quest.AngerAtAdmiral) > 0)
			{
				if (CheckAttribute(pchar, "questTemp.LSC.RivadosHelp") || LSC_CheckDeceasedCaspers() == 0)
				{
					dialog.text = StringFromKey("Mentos_312");
					link.l1 = StringFromKey("Mentos_313");
					link.l1.go = "exit";
					npchar.quest.NoPlanGoReady = true;
				}
				else
				{
					dialog.text = StringFromKey("Mentos_314");
					link.l1 = StringFromKey("Mentos_315");
					link.l1.go = "SuicideSquad_17";
					link.l3 = StringFromKey("Mentos_316");
					link.l3.go = "SuicideSquad_18";
				}
				npchar.quest.AngerAtAdmiral = sti(npchar.quest.AngerAtAdmiral) + 1; //накапливаем злость на адмирала
				AddQuestRecord("ISS_DefeatCasperClan", "18");
				AddQuestUserData("ISS_DefeatCasperClan", "sName", GetFullName(npchar));
				string sIndex = its(GetCharacterIndex(npchar.id));
				pchar.questTemp.LSC.suicideSquad.(sIndex) = true;

				LSC_SuicideSquadEnough();
			}
			else
			{
				dialog.text = StringFromKey("Mentos_317", GetFullName(pchar));
				link.l1 = StringFromKey("Mentos_318");
				link.l1.go = "exit";
				npchar.quest.NoSuicideSquad = true;
				AddQuestRecord("ISS_DefeatCasperClan", "21");
				AddLandQuestMark_Main_WithCondition(CharacterFromID("LSC_Usurer"), "ISS_DefeatCasperClan", "LSC_ToSeekMechanik_Usurer_QuestMarkCondition");
			}
		break;
		case "SuicideSquad_17":
			dialog.text = StringFromKey("Mentos_319");
			link.l1 = StringFromKey("Mentos_320");
			link.l1.go = "SuicideSquad_20";
		break;
		case "SuicideSquad_18":
			npchar.quest.WaitPlan = true;
			dialog.text = StringFromKey("Mentos_321");
			link.l1 = StringFromKey("Mentos_322");
			link.l1.go = "exit";
		break;
		case "SuicideSquad_19":
			dialog.text = StringFromKey("Mentos_323");
			link.l1 = StringFromKey("Mentos_324");
			link.l1.go = "SuicideSquad_17";
			link.l2 = StringFromKey("Mentos_325");
			link.l2.go = "MentosHelp_1";
			link.l3 = StringFromKey("Mentos_326");
			link.l3.go = "exit";
		break;
		case "SuicideSquad_20":
			AddQuestRecord("ISS_DefeatCasperClan", "19");
			pchar.questTemp.LSC.MentosHelp = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.quest.LSC_MentosAttackOnCasper.win_condition.l1 = "Timer";
			pchar.quest.LSC_MentosAttackOnCasper.win_condition.l1.date.hour = GetHour();
			pchar.quest.LSC_MentosAttackOnCasper.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_MentosAttackOnCasper.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_MentosAttackOnCasper.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_MentosAttackOnCasper.function = "LSC_MentosAttackOnCasper"; // готовы
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");
		break;
		//штурм касперов
		case "MentosHelp":
			dialog.text = StringFromKey("Mentos_327");
			link.l1 = StringFromKey("Mentos_328");
			link.l1.go = "MentosHelp_0";
			link.l2 = StringFromKey("Mentos_329");
			link.l2.go = "MentosHelp_00";
		break;
		case "MentosHelp_0":
			dialog.text = StringFromKey("Mentos_330", GetFullName(pchar));
			link.l1 = StringFromKey("Mentos_331");
			link.l1.go = "MentosHelp_00";
			link.l2 = StringFromKey("Mentos_332");
			link.l2.go = "MentosHelp_00";
			link.l3 = StringFromKey("Mentos_333");
			link.l3.go = "MentosHelp_00";
			link.l4 = StringFromKey("Mentos_334");
			link.l4.go = "MentosHelp_00";
		break;
		case "MentosHelp_00":
			dialog.text = StringFromKey("Mentos_335");
			link.l1 = StringFromKey("Mentos_336");
			link.l1.go = "MentosHelp_1";
		break;
		case "MentosHelp_1":
			dialog.text = StringFromKey("Mentos_337");
			link.l1 = StringFromKey("Mentos_338");
			if (LSC_CheckDeceasedCaspers() == 0)
				link.l1.go = "StormCaspers_2";
			else
				link.l1.go = "MentosHelp_2";
			link.l2 = StringFromKey("Mentos_339");
			link.l2.go = "exit";
		break;
		case "MentosHelp_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("LSC_MentosStartAttackOnCasper");
			RemoveLandQuestMark_Main(npchar, "ISS_DefeatCasperClan");
		break;

		//хороший финал с Уоркменом
		case "GoodWalkerFinish":
			AddDialogExitQuest("LSC_talkWithWalker_1");
			dialog.text = StringFromKey("Mentos_340");
			link.l1 = StringFromKey("Mentos_341");
			link.l1.go = "GoodWalkerFinish_1";
			AddQuestRecord("ISS_MainLine", "73"); // Добавлена новая запись о том, что Уоркман убедил людей
		break;
		case "GoodWalkerFinish_1":
			LAi_ActorTurnToCharacter(npchar, &characters[sti(npchar.quest.agree_man)]);
			dialog.text = StringFromKey("Mentos_342");
			link.l1 = StringFromKey("Mentos_343");
			link.l1.go = "exit";
			link.l2 = StringFromKey("Mentos_344");
			link.l2.go = "exit";
			link.l3 = StringFromKey("Mentos_345");
			link.l3.go = "exit";
		break;
		case "GoodWalkerFinishForeverAlone":
			AddDialogExitQuest("LSC_talkWithWalker_1");
			dialog.text = StringFromKey("Mentos_346", pchar);
			link.l1 = StringFromKey("Mentos_347");
			link.l1.go = "GoodWalkerFinishForeverAlone_1";
		break;
		case "GoodWalkerFinishForeverAlone_1":
			dialog.text = StringFromKey("Mentos_348");
			link.l1 = StringFromKey("Mentos_349");
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "74");
		break;

		//плохой финал с Уоркменом
		case "BadWalkerFinish":
			pchar.questTemp.LSC.walker_finish.walker_ment = true;
			AddDialogExitQuest("LSC_talkWithWalker_1");
			dialog.text = StringFromKey("Mentos_350", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("Mentos_351", pchar);
			if (CheckAttribute(npchar, "quest.agree_man")) link.l1.go = "BadWalkerFinish_1";
			else                                           link.l1.go = "exit";
		break;
		case "BadWalkerFinish_1":
			LAi_ActorTurnToCharacter(npchar, &characters[sti(npchar.quest.agree_man)]);
			dialog.text = StringFromKey("Mentos_352");
			link.l1 = StringFromKey("Mentos_353");
			link.l1.go = "BadWalkerFinish_2";
		break;
		case "BadWalkerFinish_2":
			dialog.text = StringFromKey("Mentos_354");
			link.l1 = StringFromKey("Mentos_355");
			link.l1.go = "exit";
		break;

		//диалог с бойцами Чада
		case "EndWalkerFinish":
			dialog.text = StringFromKey("Mentos_356");
			link.l1 = StringFromKey("Mentos_357", GetFullName(pchar));
			link.l1.go = "EndWalkerFinish_1";
			link.l2 = StringFromKey("Mentos_358");
			link.l2.go = "EndWalkerFinish_5";
		break;
		case "EndWalkerFinish_1":
			dialog.text = StringFromKey("Mentos_359");
			link.l1 = StringFromKey("Mentos_360");
			link.l1.go = "EndWalkerFinish_5";
			link.l2 = StringFromKey("Mentos_361");
			link.l2.go = "EndWalkerFinish_2";
		break;
		case "EndWalkerFinish_2":
			dialog.text = StringFromKey("Mentos_362");
			link.l1 = StringFromKey("Mentos_363");
			link.l1.go = "EndWalkerFinish_3";
			//убедили
			//            if (GetCharacterSPECIAL(pchar, SPECIAL_C) >= 8 && GetCharacterSkill(pchar, SKILL_LEADERSHIP) > 50) link.l1.go = "EndWalkerFinish_3";
			if (PlayerRPGCheck_SPECIAL(SPECIAL_C, 8) && PlayerRPGCheck_Skill(SKILL_LEADERSHIP, 51, false)) link.l1.go = "EndWalkerFinish_3";
			//не убедили
			else link.l1.go = "EndWalkerFinish_5";
		break;
		case "EndWalkerFinish_3":
			dialog.text = StringFromKey("Mentos_364");
			link.l1 = StringFromKey("Mentos_365");
			link.l1.go = "EndWalkerFinish_4";
		break;
		case "EndWalkerFinish_4":
			dialog.text = StringFromKey("Mentos_366", GetFullName(pchar), GetFullName(pchar));
			link.l1 = StringFromKey("Mentos_367");
			link.l1.go = "EndWalkerFinish_6";
			AddQuestRecord("ISS_MainLine", "69"); // Добавлена запись в журнал
		break;
		case "EndWalkerFinish_5":
			pchar.questTemp.LSC.walker_finish.admital_ment = true;
			dialog.text = StringFromKey("Mentos_368", pchar);
			link.l1 = StringFromKey("Mentos_369");
			link.l1.go = "EndWalkerFinish_6";
			AddQuestRecord("ISS_MainLine", "70"); // Добавлена запись в журнал
		break;
		case "EndWalkerFinish_6":
			DeleteAttribute(&TEV, "LSC_talkWithWalker_AllLookIt");
			if (!CheckAttribute(pchar, "questTemp.LSC.walker_finish.walker_ment") && !CheckAttribute(pchar, "questTemp.LSC.walker_finish.admital_ment"))
				AddDialogExitQuest("LSC_talkWithWalker_3");
			else
				AddDialogExitQuest("LSC_talkWithWalker_2");
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "GoodBye":
			dialog.text = StringFromKey("Mentos_370");
			link.l1 = StringFromKey("Mentos_371");
			link.l1.go = "GoodBye_1";
		break;
		case "GoodBye_1":
			dialog.text = StringFromKey("Mentos_372");
			link.l1 = StringFromKey("Mentos_373");
			link.l1.go = "GoodBye_2";
		break;
		case "GoodBye_2":
			dialog.text = StringFromKey("Mentos_374", pchar);
			link.l1 = StringFromKey("Mentos_375", pchar);
			link.l1.go = "GoodBye_3";
		break;

		case "GoodBye_3":
			dialog.text = StringFromKey("Mentos_376", pchar);
			link.l1 = StringFromKey("Mentos_377");
			link.l1.go = "GoodBye_4";
		break;
		case "GoodBye_4":
			dialog.text = StringFromKey("Mentos_378");
			link.l1 = StringFromKey("Mentos_379");
			link.l1.go = "Exit_GoodBye";
		break;
	}
	NextDiag.PrevNode = NodeName;
}

void UpdateBrothersWarningTime(int num)
{
	ref sld;
	for (int i = 0; i < num; i++)
	{
		makeref(sld, characters[sti(chrFindNearCharacters[i].index)]);
		if (!bMainCharacterInBox)
		{
			bool bCheckOldWarning = CheckAttribute(sld, "warning_date") && GetNpcQuestPastDayParam(sld, "warning_date") > 0;
			if (!CheckAttribute(sld, "time_to_go") || bCheckOldWarning)
			{
				sld.time_to_go = 1;
				SaveCurrentNpcQuestDateParam(sld, "warning_date");
			}
		}
	}
}
