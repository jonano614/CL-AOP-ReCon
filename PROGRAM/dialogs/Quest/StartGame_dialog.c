// Диалог начала игры (туториал) 03.10.06 boal
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref sld;

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Finish_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			loadedLocation.lockCamAngle = 0.4;
			LAi_RemoveCheckMinHP(Pchar); // снимем проверки
			LAi_SetImmortal(pchar, false);
			LAi_SetPlayerType(pchar);
			InterfaceStates.Buttons.Save.enable = true;
			DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
		break;

		case "ChangePIRATES":
			LAi_SetCitizenTypeNoGroup(NPChar);
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Node_5";
			DialogExit();
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;

		case "ChangePIRATES_Jess":
			LAi_SetCitizenTypeNoGroup(NPChar);
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Node_5_Jess";
			DialogExit();
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
		break;

		case "Teach_battle_1":
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Teach_6";
			AddDialogExitQuestFunction("Tut_TeachBattle");
			DialogExit();
		break;

		case "First time":
			NextDiag.TempNode = "First time";
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LockFightMode(Pchar, false);
			LAi_SetActorTypeNoGroup(Pchar);
			LAi_ActorTurnToCharacter(Pchar, NPChar);
			if (pchar.FaceId == "1005")
			{
				dialog.text = StringFromKey("StartGame_dialog_1");
				if (bBettaTestMode)
				{
					link.l0 = StringFromKey("StartGame_dialog_2");
					link.l0.go = "Finish_2";
				}
				link.l1 = StringFromKey("StartGame_dialog_3");
				link.l1.go = "Node_1_Jess";
			}
			else
			{
				dialog.text = StringFromKey("StartGame_dialog_4", GetFullName(pchar));
				if (bBettaTestMode)
				{
					link.l0 = StringFromKey("StartGame_dialog_5");
					link.l0.go = "Finish_2";
				}
				link.l1 = StringFromKey("StartGame_dialog_6");
				link.l1.go = "Node_1";
			}
		break;

		case "Node_1":
			dialog.text = StringFromKey("StartGame_dialog_7");
			link.l1 = StringFromKey("StartGame_dialog_8", pchar);
			link.l1.go = "Node_2";
		break;

		case "Node_1_Jess":
			dialog.text = StringFromKey("StartGame_dialog_9");
			link.l1 = StringFromKey("StartGame_dialog_10");
			link.l1.go = "Node_2_Jess";
		break;

		case "Node_2":
			dialog.text = StringFromKey("StartGame_dialog_11");
			link.l1 = StringFromKey("StartGame_dialog_12", pchar);
			link.l1.go = "Node_3";
		break;

		case "Node_2_Jess":
			dialog.text = StringFromKey("StartGame_dialog_13");
			link.l1 = StringFromKey("StartGame_dialog_14");
			link.l1.go = "Node_3_Jess";
		break;

		case "Node_3":
			dialog.text = StringFromKey("StartGame_dialog_15", pchar);
			link.l1 = StringFromKey("StartGame_dialog_16");
			link.l1.go = "Node_4";
		break;

		case "Node_3_Jess":
			dialog.text = StringFromKey("StartGame_dialog_17");
			link.l1 = StringFromKey("StartGame_dialog_18");
			link.l1.go = "Node_4_Jess";
		break;

		case "Node_4":
			dialog.text = StringFromKey("StartGame_dialog_19");
			link.l1 = StringFromKey("StartGame_dialog_20");
			link.l1.go = "ChangePIRATES";
			link.l2 = StringFromKey("StartGame_dialog_21");
			link.l2.go = "Node_5";
		break;

		case "Node_4_Jess":
			dialog.text = StringFromKey("StartGame_dialog_22");
			link.l1 = StringFromKey("StartGame_dialog_23");
			link.l1.go = "ChangePIRATES_Jess";
			link.l2 = StringFromKey("StartGame_dialog_24");
			link.l2.go = "Node_5_Jess";
		break;

		case "Node_5":
			dialog.text = StringFromKey("StartGame_dialog_25");
			link.l1 = StringFromKey("StartGame_dialog_26", pchar);
			link.l1.go = "Teach_1";
			link.l2 = StringFromKey("StartGame_dialog_27", pchar);
			link.l2.go = "Finish_1";
		break;

		case "Node_5_Jess":
			dialog.text = StringFromKey("StartGame_dialog_28");
			link.l1 = StringFromKey("StartGame_dialog_29");
			link.l1.go = "Teach_1_Jess";
			link.l2 = StringFromKey("StartGame_dialog_30");
			link.l2.go = "Finish_1";
		break;

		case "Finish_1":
			if (pchar.FaceId == "1005")
			{
				dialog.text = StringFromKey("StartGame_dialog_31", GetStartPhraseAboutLocation(pchar.HeroParam.ToCityId));
				link.l1 = StringFromKey("StartGame_dialog_32");
				link.l1.go = "Finish_2";
				link.l2 = StringFromKey("StartGame_dialog_33");
				link.l2.go = "Advice_1";
			}
			else
			{
				dialog.text = StringFromKey("StartGame_dialog_34", GetStartPhraseAboutLocation(pchar.HeroParam.ToCityId));
				link.l1 = StringFromKey("StartGame_dialog_35", pchar);
				link.l1.go = "Finish_2";
				link.l2 = StringFromKey("StartGame_dialog_36");
				link.l2.go = "Advice_1";
			}
		break;

		case "Advice_1":
			dialog.text = StringFromKey("StartGame_dialog_37");
			link.l1 = StringFromKey("StartGame_dialog_38");
			link.l1.go = "Advice_2";
			link.l2 = StringFromKey("StartGame_dialog_39");
			link.l2.go = "Finish_2";
		break;

		case "Advice_2":
			dialog.text = StringFromKey("StartGame_dialog_40");
			link.l1 = StringFromKey("StartGame_dialog_41");
			link.l1.go = "Advice_3";
			link.l2 = StringFromKey("StartGame_dialog_42");
			link.l2.go = "Finish_2";
		break;

		case "Advice_3":
			dialog.text = StringFromKey("StartGame_dialog_43");
			link.l1 = StringFromKey("StartGame_dialog_44");
			link.l1.go = "Advice_4";
			link.l2 = StringFromKey("StartGame_dialog_45");
			link.l2.go = "Finish_2";
		break;

		case "Advice_4":
			dialog.text = StringFromKey("StartGame_dialog_46");
			link.l1 = StringFromKey("StartGame_dialog_47");
			link.l1.go = "Advice_5";
			link.l2 = StringFromKey("StartGame_dialog_48");
			link.l2.go = "Finish_2";
		break;

		case "Advice_5":
			dialog.text = StringFromKey("StartGame_dialog_49");
			link.l1 = StringFromKey("StartGame_dialog_50");
			link.l1.go = "Advice_6";
			link.l2 = StringFromKey("StartGame_dialog_51");
			link.l2.go = "Finish_2";
		break;

		case "Advice_6":
			dialog.text = StringFromKey("StartGame_dialog_52");
			link.l1 = StringFromKey("StartGame_dialog_53");
			link.l1.go = "Advice_7";
			link.l2 = StringFromKey("StartGame_dialog_54");
			link.l2.go = "Finish_2";
		break;

		case "Advice_7":
			dialog.text = StringFromKey("StartGame_dialog_55");
			link.l1 = StringFromKey("StartGame_dialog_56");
			link.l1.go = "Advice_8";
			link.l2 = StringFromKey("StartGame_dialog_57");
			link.l2.go = "Finish_2";
		break;

		case "Advice_8":
			dialog.text = StringFromKey("StartGame_dialog_58");
			link.l1 = StringFromKey("StartGame_dialog_59");
			link.l1.go = "Advice_9";
			link.l2 = StringFromKey("StartGame_dialog_60");
			link.l2.go = "Finish_2";
		break;

		case "Advice_9":
			dialog.text = StringFromKey("StartGame_dialog_61");
			link.l1 = StringFromKey("StartGame_dialog_62");
			link.l1.go = "Advice_10";
			link.l2 = StringFromKey("StartGame_dialog_63");
			link.l2.go = "Finish_2";
		break;

		case "Advice_10":
			dialog.text = StringFromKey("StartGame_dialog_64");
			link.l1 = StringFromKey("StartGame_dialog_65");
			link.l1.go = "Finish_2";
		break;
		/////   фехт 
		case "Teach_1":
			dialog.text = StringFromKey("StartGame_dialog_66");
			link.l1 = StringFromKey("StartGame_dialog_67");
			link.l1.go = "Teach_2";
			locCameraTarget(pchar);
			locCameraToPos(-2.5749109, 2.7001140, 3.8744259, false);
			DeleteAttribute(loadedLocation, "lockCamAngle");
		break;

		case "Teach_1_Jess":
			dialog.text = StringFromKey("StartGame_dialog_68");
			link.l1 = StringFromKey("StartGame_dialog_69");
			link.l1.go = "Teach_2";
		break;

		case "Teach_2":
			dialog.text = StringFromKey("StartGame_dialog_70");
			link.l1 = StringFromKey("StartGame_dialog_71");
			link.l1.go = "Teach_2_1";
		break;

		case "Teach_2_1":
			dialog.text = StringFromKey("StartGame_dialog_72");
			link.l1 = StringFromKey("StartGame_dialog_73");
			link.l1.go = "Teach_3";
		break;

		case "Teach_3":
			dialog.text = StringFromKey("StartGame_dialog_74");
			link.l1 = StringFromKey("StartGame_dialog_75");
			link.l1.go = "Teach_4";
		break;

		case "Teach_4":
			dialog.text = StringFromKey("StartGame_dialog_76");
			link.l1 = StringFromKey("StartGame_dialog_77");
			link.l1.go = "Teach_5";
		break;

		case "Teach_5":
			dialog.text = StringFromKey("StartGame_dialog_78");
			link.l1 = StringFromKey("StartGame_dialog_79");
			link.l1.go = "Teach_6";
		break;

		case "Teach_6":
			pchar.HeroParam.Teach_battle = 1;
			pchar.HeroParam.Teach_battle_count = 0;
			Tut_RestoreState();
			dialog.text = StringFromKey("StartGame_dialog_80");
			link.l1 = StringFromKey("StartGame_dialog_81");
			link.l1.go = "Teach_battle_1";
			link.l2 = StringFromKey("StartGame_dialog_82", pchar);
			link.l2.go = "Finish_1";
		break;

		case "Teach_battle_lose":
			Tut_RestoreState();
			dialog.text = StringFromKey("StartGame_dialog_86", LinkRandPhrase(
						StringFromKey("StartGame_dialog_83"),
						StringFromKey("StartGame_dialog_84"),
						StringFromKey("StartGame_dialog_85")));
			if (sti(pchar.rank) < 3) // чтоб не качались до упора
			{
				link.l1 = StringFromKey("StartGame_dialog_87");
				link.l1.go = "Teach_battle_1";
			}
			link.l2 = StringFromKey("StartGame_dialog_88", pchar);
			link.l2.go = "Finish_1";
		break;

		case "Teach_battle_win":
			pchar.HeroParam.Teach_battle = 2;
			Tut_RestoreState();
			dialog.text = StringFromKey("StartGame_dialog_89");
			link.l1 = StringFromKey("StartGame_dialog_90");
			link.l1.go = "Teach_battle_1";
			link.l2 = StringFromKey("StartGame_dialog_91", pchar);
			link.l2.go = "Finish_1";
		break;

		case "Teach_battle_win_2":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			if (pchar.FaceId == "1005")
			{
				dialog.text = StringFromKey("StartGame_dialog_92");
			}
			else
			{
				dialog.text = StringFromKey("StartGame_dialog_93");
			}
			link.l1 = StringFromKey("StartGame_dialog_94");
			link.l1.go = "Finish_1";
		break;

		case "Teach_battle_win_3":
			Tut_RestoreState();
			sld = characterFromID("Sailor_2");
			LAi_SetCitizenType(sld);
			dialog.text = StringFromKey("StartGame_dialog_95");
			if (sti(pchar.rank) < 3) // чтоб не качались до упора
			{
				link.l1 = StringFromKey("StartGame_dialog_96");
				link.l1.go = "Teach_battle_1";
			}
			link.l2 = StringFromKey("StartGame_dialog_97", pchar);
			link.l2.go = "Finish_1";
		break;
	}
}

string GetStartPhraseAboutLocation(string cityName)
{
	//получаем фразу о стартовой локации. заглушка для старта в городах без портов
	if (cityName == "FortOrange") //ФортОранж
	{
		return StringFromKey("StartGame_dialog_98");
	}
	return StringFromKey("StartGame_dialog_99", XI_ConvertString("Colony" + cityName + "Gen"));
}
