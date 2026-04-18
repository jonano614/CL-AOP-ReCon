void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;
	int iTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("Pearl_dialog_1");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// ==> глава поселения
		case "HeadMan":
			NextDiag.TempNode = "HeadMan";

			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(NPChar, "nation") && NPChar.nation == pchar.nation)
					sTemp = StringFromKey("Pearl_dialog_2", pchar);
				else
					sTemp = StringFromKey("Pearl_dialog_3", pchar);
				dialog.text = StringFromKey("Pearl_dialog_4", sTemp, NationNameGenitive(sti(npchar.nation)));
				link.l1 = StringFromKey("Pearl_dialog_5", GetFullName(pchar));
				link.l1.go = "HeadMan_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("Pearl_dialog_6"),
							StringFromKey("Pearl_dialog_7"),
							StringFromKey("Pearl_dialog_8"),
							StringFromKey("Pearl_dialog_9"), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Pearl_dialog_10", pchar, GetAddress_FormToNPC(NPChar)),
							StringFromKey("Pearl_dialog_11"),
							StringFromKey("Pearl_dialog_12", GetAddress_FormToNPC(NPChar)),
							StringFromKey("Pearl_dialog_13"), npchar, Dialog.CurrentNode);
				link.l1.go = "exit";

				//-------- поиск шпиёна Шарпа ------------
				if (or(pchar.questTemp.Sharp == "grantMeRevenge", pchar.questTemp.Sharp == "sharpFirstPearlFail") && pchar.questTemp.Sharp.SeekSpy == "begin")
				{
					link.l2 = StringFromKey("Pearl_dialog_14");
					link.l2.go = "SharpSeekSpy";
				}
				//-------- поиски Шарпа ------------
				if (pchar.questTemp.Sharp == "begin" || pchar.questTemp.Sharp == "takeRumour")
				{
					link.l2 = StringFromKey("Pearl_dialog_15");
					link.l2.go = "SeekSharpAlt_1";
				}
			}
			if (pchar.questTemp.Sharp.SeekSpy == "alwaysKnow")
			{
				link.l2 = StringFromKey("Pearl_dialog_16", pchar);
				link.l2.go = "SharpSeekSpy_10";
			}
			//-------- Сдаем Шарпа ------------
			if (CheckAttribute(pchar, "questTemp.Sharp") && StrStartsWith(pchar.questTemp.Sharp, "Sharp_Prisoner") && !CheckAttribute(&TEV, "Sharp_Prisoner_DialogChoosen.PearlVillage"))
			{
				link.l3 = StringFromKey("Pearl_dialog_17");
				link.l3.go = "Sharp_Prisoner_PearlVillage";
			}
		break;
		// <------- жемчужный генератор Шарпа
		case "SharpSeekSpy":
			dialog.text = StringFromKey("Pearl_dialog_18");
			link.l1 = StringFromKey("Pearl_dialog_19");
			link.l1.go = "SharpSeekSpy_1";
		break;
		case "SharpSeekSpy_1":
			dialog.text = StringFromKey("Pearl_dialog_20", pchar);
			link.l1 = StringFromKey("Pearl_dialog_21");
			link.l1.go = "SharpSeekSpy_2";
		break;
		case "SharpSeekSpy_2":
			dialog.text = StringFromKey("Pearl_dialog_22");
			link.l1 = StringFromKey("Pearl_dialog_23", pchar);
			link.l1.go = "SharpSeekSpy_3";
		break;
		case "SharpSeekSpy_3":
			dialog.text = StringFromKey("Pearl_dialog_24");
			link.l1 = StringFromKey("Pearl_dialog_25");
			link.l1.go = "SharpSeekSpy_4";
		break;
		case "SharpSeekSpy_4":
			dialog.text = StringFromKey("Pearl_dialog_26");
			link.l1 = StringFromKey("Pearl_dialog_27");
			link.l1.go = "SharpSeekSpy_5";
		break;
		case "SharpSeekSpy_5":
			dialog.text = StringFromKey("Pearl_dialog_28");
			link.l1 = StringFromKey("Pearl_dialog_29");
			link.l1.go = "SharpSeekSpy_6";
		break;
		case "SharpSeekSpy_6":
			dialog.text = StringFromKey("Pearl_dialog_30");
			link.l1 = StringFromKey("Pearl_dialog_31");
			link.l1.go = "SharpSeekSpy_7";
		break;
		case "SharpSeekSpy_7":
			dialog.text = StringFromKey("Pearl_dialog_32");
			link.l1 = StringFromKey("Pearl_dialog_33", pchar);
			link.l1.go = "SharpSeekSpy_8";
			link.l2 = StringFromKey("Pearl_dialog_34");
			link.l2.go = "SharpSeekSpy_8over";
		break;

		case "SharpSeekSpy_8":
			dialog.text = StringFromKey("Pearl_dialog_35");
			link.l1 = StringFromKey("Pearl_dialog_36", pchar);
			link.l1.go = "SharpSeekSpy_9";
		break;
		case "SharpSeekSpy_9":
			GiveItem2Character(pchar, "mechanic_kit");
			pchar.questTemp.Sharp.SeekSpy = "seekSpy";
			SetQuestHeader("SharpPearl_SeekSpy");
			AddQuestRecord("SharpPearl_SeekSpy", "1");
			AddQuestUserData("SharpPearl_SeekSpy", "sSex", GetSexPhrase("", "а"));
			RemoveLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl_SeekSpy");
			AddLandQuestmarkToFantoms_Main("Pearl_WorkMan", "SharpPearl_SeekSpy", "SharpPearl_SeekSpy_PearlWorkMan_QuestMarkCondition");
			RemoveMapQuestMark("Shore9", "SharpPearl_SeekSpy");
			RemoveMapQuestMark("Shore55", "SharpPearl_SeekSpy");
			//CloseQuestHeader("SharpPearl"); // Временно закроем предыдущий квест
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "SharpSeekSpy_8over":
			dialog.text = StringFromKey("Pearl_dialog_37", pchar);
			link.l1 = StringFromKey("Pearl_dialog_38");
			link.l1.go = "SharpSeekSpy_8fight";
		break;
		case "SharpSeekSpy_8fight":
		//			pchar.questTemp.Sharp.SeekSpy = "over"; // квест не закрываем, можно снова поговорить
			DelLandQuestMark(npchar);
			LAi_group_Attack(npchar, pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "SharpSeekSpy_10":
			dialog.text = StringFromKey("Pearl_dialog_39");
			link.l1 = StringFromKey("Pearl_dialog_40", pchar);
			link.l1.go = "SharpSeekSpy_11";
		break;
		case "SharpSeekSpy_11":
			dialog.text = StringFromKey("Pearl_dialog_41");
			link.l1 = StringFromKey("Pearl_dialog_42", pchar);
			if (CheckAttribute(pchar, "questTemp.Sharp.SeekSpy.NewAgentPlanted"))
			{
				link.l1.go = "SharpSeekSpy_12_TooLate";
			}
			else
			{
				link.l1.go = "SharpSeekSpy_12";
			}
		break;
		case "SharpSeekSpy_12":
			dialog.text = StringFromKey("Pearl_dialog_43");
			link.l1 = StringFromKey("Pearl_dialog_44");
			link.l1.go = "SharpSeekSpy_rapier";
			link.l2 = StringFromKey("Pearl_dialog_45");
			link.l2.go = "SharpSeekSpy_pistol";
			link.l3 = StringFromKey("Pearl_dialog_46");
			link.l3.go = "SharpSeekSpy_chekan";
			link.l4 = StringFromKey("Pearl_dialog_47");
			link.l4.go = "SharpSeekSpy_cuirass";
			link.l5 = StringFromKey("Pearl_dialog_48");
			link.l5.go = "SharpSeekSpy_ratgod";
		break;
		case "SharpSeekSpy_rapier":
			dialog.text = StringFromKey("Pearl_dialog_49");
			link.l1 = StringFromKey("Pearl_dialog_50");
			link.l1.go = "SharpSeekSpy_13";
			GiveItem2Character(pchar, "blade22");
		break;

		case "SharpSeekSpy_pistol":
			dialog.text = StringFromKey("Pearl_dialog_51");
			link.l1 = StringFromKey("Pearl_dialog_52");
			link.l1.go = "SharpSeekSpy_13";
			GiveItem2Character(pchar, "pistol5");
		break;

		case "SharpSeekSpy_chekan":
			dialog.text = StringFromKey("Pearl_dialog_53");
			link.l1 = StringFromKey("Pearl_dialog_54");
			link.l1.go = "SharpSeekSpy_13";
			GiveItem2Character(pchar, "topor2");
		break;

		case "SharpSeekSpy_cuirass":
			dialog.text = StringFromKey("Pearl_dialog_55");
			link.l1 = StringFromKey("Pearl_dialog_56");
			link.l1.go = "SharpSeekSpy_13";
			GiveItem2Character(pchar, "cirass3");
		break;

		case "SharpSeekSpy_ratgod":
			dialog.text = StringFromKey("Pearl_dialog_57");
			link.l1 = StringFromKey("Pearl_dialog_58");
			link.l1.go = "SharpSeekSpy_13";
			GiveItem2Character(pchar, "indian11");
		break;
		case "SharpSeekSpy_13":
			dialog.text = StringFromKey("Pearl_dialog_59");
			link.l1 = StringFromKey("Pearl_dialog_60", pchar);
			link.l1.go = "exit";

			pchar.questTemp.Sharp.SeekSpy = "over";
			AddQuestRecord("SharpPearl_SeekSpy", "5");
			AddQuestUserData("SharpPearl_SeekSpy", "sSex", GetSexPhrase("", "а"));
			RemoveLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl_SeekSpy");

			//zagolski. битва в бухте
			pchar.quest.sharp_pre.win_condition.l1 = "location";
			pchar.quest.sharp_pre.win_condition.l1.location = "Shore9";
			pchar.quest.sharp_pre.function = "sharp_pre";
		break;
		case "SharpSeekSpy_12_TooLate":
			dialog.text = StringFromKey("Pearl_dialog_61");
			link.l1 = StringFromKey("Pearl_dialog_62");
			link.l1.go = "Exit_SharpSeekSpy_12_TooLate";
		break;
		case "Exit_SharpSeekSpy_12_TooLate":
			pchar.questTemp.Sharp.SeekSpy = "over_TooLate";
			CloseQuestHeader("SharpPearl_SeekSpy");
			RemoveLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl_SeekSpy");
			DialogExit();
		break;

		case "Sharp_Prisoner_PearlVillage":
			TEV.Sharp_Prisoner_DialogChoosen.PearlVillage = true;

			dialog.text = StringFromKey("Pearl_dialog_63");
			link.l1 = StringFromKey("Pearl_dialog_64");
			link.l1.go = "Sharp_Prisoner_PearlVillage_1";
		break;
		case "Sharp_Prisoner_PearlVillage_1":
			dialog.text = StringFromKey("Pearl_dialog_65");
			link.l1 = StringFromKey("Pearl_dialog_66");
			link.l1.go = "Exit_Sharp_Prisoner_PearlVillage";
		break;
		case "Exit_Sharp_Prisoner_PearlVillage":
			AddQuestRecord("SharpPearl", "26");
			RemoveLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl");

			DialogExit();
		break;

		// >------- жемчужный генератор Шарпа
		case "HeadMan_1":
			dialog.text = StringFromKey("Pearl_dialog_67");
			link.l1 = StringFromKey("Pearl_dialog_68");
			link.l1.go = "HeadMan_2";
		break;
		case "HeadMan_2":
			dialog.text = StringFromKey("Pearl_dialog_69", pchar);
			link.l1 = StringFromKey("Pearl_dialog_70");
			link.l1.go = "HeadMan_3";
		break;
		case "HeadMan_3":
			dialog.text = StringFromKey("Pearl_dialog_71", NationNameGenitive(sti(npchar.nation)));
			link.l1 = StringFromKey("Pearl_dialog_72");
			link.l1.go = "HeadMan_4";
		break;
		case "HeadMan_4":
			dialog.text = StringFromKey("Pearl_dialog_73");
			link.l1 = StringFromKey("Pearl_dialog_74");
			link.l1.go = "HeadMan_5";
		break;
		case "HeadMan_5":
			dialog.text = StringFromKey("Pearl_dialog_75", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Pearl_dialog_76");
			link.l1.go = "exit";
		break;
		// Поиск Шарпа
		case "SeekSharpAlt_1":
			dialog.text = StringFromKey("Pearl_dialog_77");
			link.l1 = StringFromKey("Pearl_dialog_78", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit";

			pchar.questTemp.Sharp = "takeRumourAlt";
			AddQuestRecord("SharpPearl", "15");
			RemoveLandQuestmarkToFantoms_Main("habitue", "SharpPearl");
			RemoveLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl");
			RemoveMapQuestMark("Shore9", "SharpPearl");
			RemoveMapQuestMark("Shore55", "SharpPearl");
			SeaPearl_PiratesBaron_AddQuestMarks();
		break;

		// ==> часовой у поселения
		case "GuardMan":
			NextDiag.TempNode = "GuardMan";
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Pearl_dialog_79", GetFullName(npchar)),
						StringFromKey("Pearl_dialog_80"),
						StringFromKey("Pearl_dialog_81"),
						StringFromKey("Pearl_dialog_82"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Pearl_dialog_83", GetFullName(pchar)),
						StringFromKey("Pearl_dialog_84"),
						StringFromKey("Pearl_dialog_85"),
						StringFromKey("Pearl_dialog_86"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("GuardMan_1", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;

		case "GuardMan_1":
			dialog.text = StringFromKey("Pearl_dialog_87");
			link.l1 = StringFromKey("Pearl_dialog_88");
			link.l1.go = "GuardMan_2";
		break;
		case "GuardMan_2":
			chrDisableReloadToLocation = false;
			npchar.quest.TalkOk = true; //флаг разговор состоялся, все ОК.
			LAi_SetCitizenTypeNoGroup(npchar);
			DialogExit();
		break;

		case "GuardManAllarm":
			dialog.text = StringFromKey("Pearl_dialog_89");
			link.l1 = StringFromKey("Pearl_dialog_90");
			link.l1.go = "GuardManAllarm_1";
		break;
		case "GuardManAllarm_1":
			chrDisableReloadToLocation = false;
			LAi_SetWarriorTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			DialogExit();
		break;
		// ==> пиплы в поселении
		case "PearlMan":
			NextDiag.TempNode = "PearlMan";
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Pearl_dialog_91", GetFullName(npchar)),
						StringFromKey("Pearl_dialog_92"),
						StringFromKey("Pearl_dialog_93"),
						StringFromKey("Pearl_dialog_94"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Pearl_dialog_95"),
						StringFromKey("Pearl_dialog_96"),
						StringFromKey("Pearl_dialog_97"),
						StringFromKey("Pearl_dialog_98"), npchar, Dialog.CurrentNode);
			link.l1.go = "PearlMan_1";
			if (pchar.questTemp.Sharp.SeekSpy == "seekSpy")
			{
				link.l2 = StringFromKey("Pearl_dialog_102", LinkRandPhrase(
							StringFromKey("Pearl_dialog_99"),
							StringFromKey("Pearl_dialog_100"),
							StringFromKey("Pearl_dialog_101")));
				link.l2.go = "PearlMan_Sharp_1";
			}
		break;
		case "PearlMan_1":
			dialog.text = StringFromKey("Pearl_dialog_103", NationNameGenitive(sti(npchar.nation)));
			link.l1 = StringFromKey("Pearl_dialog_104");
			link.l1.go = "exit";
			link.l2 = StringFromKey("Pearl_dialog_105");
			link.l2.go = "PearlMan_2";
		break;
		case "PearlMan_2":
			if (rand(10) < 9)
			{
				dialog.text = StringFromKey("Pearl_dialog_106");
				link.l1 = StringFromKey("Pearl_dialog_107");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Pearl_dialog_108");
				link.l1 = StringFromKey("Pearl_dialog_109");
				link.l1.go = "exit";
			}
		break;
		case "PearlMan_Sharp_1":
			dialog.text = StringFromKey("Pearl_dialog_113", LinkRandPhrase(
						StringFromKey("Pearl_dialog_110", pchar),
						StringFromKey("Pearl_dialog_111"),
						StringFromKey("Pearl_dialog_112", pchar)));
			link.l1 = StringFromKey("Pearl_dialog_116", RandPhraseSimple(
						StringFromKey("Pearl_dialog_114"),
						StringFromKey("Pearl_dialog_115")));
			link.l1.go = "exit";
		break;

		// ==> индейцы в поселении
		case "IndPearlMan":
			NextDiag.TempNode = "IndPearlMan";
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Pearl_dialog_117", pchar),
						StringFromKey("Pearl_dialog_118", pchar),
						StringFromKey("Pearl_dialog_119", pchar),
						StringFromKey("Pearl_dialog_120", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Pearl_dialog_121"),
						StringFromKey("Pearl_dialog_122"),
						StringFromKey("Pearl_dialog_123"),
						StringFromKey("Pearl_dialog_124", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		case "IndPearlMan_1":
			dialog.text = StringFromKey("Pearl_dialog_125", pchar);
			link.l1 = StringFromKey("Pearl_dialog_126", pchar);
			link.l1.go = "exit";
			link.l2 = StringFromKey("Pearl_dialog_127");
			link.l2.go = "IndPearlMan_2";
			if (pchar.questTemp.Sharp.SeekSpy == "seekSpy")
			{
				link.l3 = StringFromKey("Pearl_dialog_128");
				link.l3.go = "IndPearlMan_Sharp_1";
			}
		break;
		//жемчужный генератор Шарпа, поиски осведомителя
		case "IndPearlMan_Sharp_1":
			dialog.text = StringFromKey("Pearl_dialog_129", pchar);
			link.l1 = StringFromKey("Pearl_dialog_130");
			link.l1.go = "IndPearlMan_Sharp_2";
		break;
		case "IndPearlMan_Sharp_2":
			dialog.text = StringFromKey("Pearl_dialog_131", pchar);
			link.l1 = StringFromKey("Pearl_dialog_132");
			link.l1.go = "IndPearlMan_Sharp_3";
		break;
		case "IndPearlMan_Sharp_3":
			dialog.text = StringFromKey("Pearl_dialog_133", pchar);
			link.l1 = StringFromKey("Pearl_dialog_134");
			link.l1.go = "IndPearlMan_Sharp_4";
		break;
		case "IndPearlMan_Sharp_4":
			dialog.text = StringFromKey("Pearl_dialog_135");
			link.l1 = StringFromKey("Pearl_dialog_136");
			link.l1.go = "IndPearlMan_Sharp_5";
		break;
		case "IndPearlMan_Sharp_5":
			dialog.text = StringFromKey("Pearl_dialog_137");
			link.l1 = StringFromKey("Pearl_dialog_138");
			link.l1.go = "IndPearlMan_Sharp_6";
		break;
		case "IndPearlMan_Sharp_6":
			dialog.text = StringFromKey("Pearl_dialog_139");
			link.l1 = StringFromKey("Pearl_dialog_140");
			link.l1.go = "exit";
			pchar.questTemp.Sharp.SeekSpy = "toLaVega";
			AddQuestRecord("SharpPearl_SeekSpy", "2");
			AddQuestUserData("SharpPearl_SeekSpy", "sName", npchar.name);
			pchar.quest.SharpSeekSpy_loginSpy.win_condition.l1 = "location";
			pchar.quest.SharpSeekSpy_loginSpy.win_condition.l1.location = "Shore55";
			pchar.quest.SharpSeekSpy_loginSpy.function = "SharpSeekSpy_loginSpy";
			RemoveLandQuestmarkToFantoms_Main("Pearl_WorkMan", "SharpPearl_SeekSpy");
		break;
		//продажа жемчуга
		case "IndPearlMan_2":
			if (!CheckAttribute(npchar, "quest.pearl")) npchar.quest.pearl = rand(1);
			if (sti(npchar.quest.pearl) == 0 || CheckAttribute(pchar, "quest.PearlToShore_ForSale.id"))
			{
				dialog.text = StringFromKey("Pearl_dialog_141", pchar);
				link.l1 = StringFromKey("Pearl_dialog_142");
				link.l1.go = "exit";
			}
			else
			{
				bOk = false;
				int num = FindNearCharacters(npchar, 5.0, -1.0, -1.0, 1.0, false, true);
				if (num > 0)
				{
					for (int i = 0; i < num; i++)
					{
						iTemp = chrFindNearCharacters[i].index;
						if (iTemp == GetMainCharacterIndex()) continue;
						sTemp = characters[iTemp].id;
						if (HasSubStr(sTemp, "FightMan"))
						{
							bOk = true;
							break;
						}
					}
				}
				if (bOk)
				{
					dialog.text = StringFromKey("Pearl_dialog_143", pchar);
					link.l1 = StringFromKey("Pearl_dialog_144");
					link.l1.go = "IndPearlMan_4";
				}
				else
				{
					dialog.text = StringFromKey("Pearl_dialog_145", pchar);
					link.l1 = StringFromKey("Pearl_dialog_146");
					link.l1.go = "IndPearlMan_3";
				}
			}
		break;
		case "IndPearlMan_3":
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			NextDiag.CurrentNode = "IndPearlMan_Sale";
			LAi_SetActorTypeNoGroup(NPChar);
			if (npchar.location == "Pearl_town_2")
			{
				LAi_ActorRunToLocation(NPChar, "reload", "reload1", "Shore51", "goto", "goto1", "PearlToShore_ForSale", 10.0);
			}
			else
			{
				LAi_ActorRunToLocation(NPChar, "reload", "reload1", "Shore49", "goto", "goto1", "PearlToShore_ForSale", 10.0);
			}
			pchar.quest.PearlToShore_ForSale.idx = npchar.index;
			npchar.quest.Pearl.bigQty = rand(30) + 10;
			npchar.quest.Pearl.smallQty = rand(60) + 20;
			chrDisableReloadToLocation = true;
			DialogExit();
		break;
		case "IndPearlMan_4":
			npchar.LifeDay = 0;
			LAi_group_Attack(NPChar, Pchar);
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 10.0);
			DialogExit();
		break;

		case "IndPearlMan_Sale":
			dialog.text = StringFromKey("Pearl_dialog_147", pchar);
			link.l1 = StringFromKey("Pearl_dialog_148");
			link.l1.go = "IndPearlMan_Sale_1";
		break;
		case "IndPearlMan_Sale_1":
			dialog.text = StringFromKey("Pearl_dialog_149");
			link.l1 = StringFromKey("Pearl_dialog_150");
			link.l1.go = "IndPearlMan_Sale_2";
			link.l2 = StringFromKey("Pearl_dialog_151", pchar);
			link.l2.go = "IndPearlMan_Sale_Out";
		break;
		case "IndPearlMan_Sale_2":
			dialog.text = StringFromKey("Pearl_dialog_152", npchar.quest.Pearl.bigQty, npchar.quest.Pearl.smallQty);
			link.l1 = StringFromKey("Pearl_dialog_153");
			link.l1.go = "IndPearlMan_Sale_3";
		break;
		case "IndPearlMan_Sale_3":
			iTemp = (sti(npchar.quest.Pearl.bigQty) * 10) + (sti(npchar.quest.Pearl.smallQty) * 5);
			if (sti(pchar.money) >= iTemp)
			{
				dialog.text = StringFromKey("Pearl_dialog_154");
				link.l1 = StringFromKey("Pearl_dialog_155");
				AddMoneyToCharacter(pchar, -iTemp);
				TakeNItems(pchar, "jewelry11", sti(npchar.quest.Pearl.bigQty));
				TakeNItems(pchar, "jewelry12", sti(npchar.quest.Pearl.smallQty));
				ChangeIndianRelation(3.0);
			}
			else
			{
				dialog.text = StringFromKey("Pearl_dialog_156", pchar, iTemp);
				link.l1 = StringFromKey("Pearl_dialog_157");
			}
			link.l1.go = "IndPearlMan_Sale_Out";
		break;
		case "IndPearlMan_Sale_Out":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "CanFightCurLocation", -1);
		break;
	}
}
