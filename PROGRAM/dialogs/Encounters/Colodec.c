void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iRank, iMassive;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = StringFromKey("Colodec_4", LinkRandPhrase(
						StringFromKey("Colodec_1"),
						StringFromKey("Colodec_2"),
						StringFromKey("Colodec_3")));
			Link.l1 = StringFromKey("Colodec_8", LinkRandPhrase(
						StringFromKey("Colodec_5"),
						StringFromKey("Colodec_6"),
						StringFromKey("Colodec_7")));
			Link.l1.go = "Step_1";
		break;
		case "Step_1":
			dialog.text = StringFromKey("Colodec_12", LinkRandPhrase(
						StringFromKey("Colodec_9"),
						StringFromKey("Colodec_10"),
						StringFromKey("Colodec_11")));
			Link.l1 = StringFromKey("Colodec_13");
			Link.l1.go = "Step_2";
		break;
		case "Step_2":
			dialog.text = StringFromKey("Colodec_14");
			Link.l1 = StringFromKey("Colodec_15");
			Link.l1.go = "Step_3";
		break;
		case "Step_3":
			dialog.text = StringFromKey("Colodec_16");
			Link.l1 = StringFromKey("Colodec_17");
			Link.l1.go = "Step_agree";
			Link.l2 = StringFromKey("Colodec_18");
			Link.l2.go = "Step_disAgree";
		break;

		case "Step_agree":
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			if (rand(1))
			{
				//бандюганы
				LAi_LocationDisableMonGenTimer(pchar.GenQuest.EncGirl.locationId, 1); //монстров не генерить 1 день
				LAi_LocationDisableOffGenTimer(pchar.GenQuest.EncGirl.locationId, 1); //офицеров не пускать 1 день
				LocatorReloadEnterDisable(pchar.GenQuest.EncGirl.locationId, "reload2", true);
				pchar.GenQuest.OpenTheRopeExit = pchar.GenQuest.EncGirl.locationId; //флаг для открытия релоада
				i = 0;
				arrayNPCModelHow = 0;
				while(i < 3)
				{
					iRank = sti(pchar.rank) - rand(5) + rand(5);
					if (iRank < 1) iRank = 1;
					sld = GetCharacter(NPC_GenerateCharacter("CaveGandMan" + i, "pirate_" + (rand(15) + 1), "man", "man", iRank, PIRATE, 1, true));
					SetNPCModelUniq(sld, "pirate", MAN);
					SetFantomParamFromRank(sld, iRank, true);
					sld.SaveItemsForDead = true;
					sld.DontClearDead = true;
					sld.money = iRank * 200 + 1000 + rand(500);
					LAi_SetWarriorType(sld);
					LAi_warrior_SetStay(sld, true);
					LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirl.locationId, "quest", "quest" + i);
					i++;
				}
				pchar.quest.Enc_FriendGirl_afterGang.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Enc_FriendGirl_afterGang.win_condition.l1.location = pchar.location;
				pchar.quest.Enc_FriendGirl_afterGang.win_condition = "Enc_FriendGirl_afterGang";
			}
			else
			{
				//и правда девка
				sld = GetCharacter(NPC_GenerateCharacter("UndergroundGirl", "girl_" + (rand(9) + 1), "woman", "towngirl", 5, PIRATE, 1, false));
				sld.dialog.filename = "Encounters\Colodec.c";
				int iTemp = rand(1);
				sld.dialog.currentnode = "Underground1";//+ iTemp; //здесь рендом поведения девки: 0-помогите, 1-сама крутая
				sld.greeting = "Enc_RapersGirl_" + (iTemp + 1); //соотв. озвучка
				LAi_SetStayType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirl.locationId, "monsters", "monster" + (rand(9) + 1));
			}
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Step_disAgree":
			ChangeCharacterReputation(pchar, -3);
			LAi_SetCitizenTypeNoGroup(npchar);
			pchar.quest.Enc_FriendGirl_after.over = "yes";
			NextDiag.CurrentNode = "FackYou";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		case "FackYou":
			NextDiag.TempNode = "FackYou";
			dialog.text = StringFromKey("Colodec_19", pchar);
			Link.l1 = StringFromKey("Colodec_20");
			Link.l1.go = "exit";
		break;

		case "Underground0": //девка реально заблудилась
			dialog.text = StringFromKey("Colodec_21");
			Link.l1 = StringFromKey("Colodec_22");
			Link.l1.go = "Underground0_1";
		break;
		case "Underground0_1":
			dialog.text = StringFromKey("Colodec_23");
			Link.l1 = StringFromKey("Colodec_24", pchar);
			Link.l1.go = "Underground0_2";
		break;
		case "Underground0_2":
			dialog.text = StringFromKey("Colodec_25", GetAddress_Form(NPChar));
			Link.l1 = StringFromKey("Colodec_26");
			Link.l1.go = "exit";
			npchar.LifeDay = 0;
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			ChangeCharacterReputation(pchar, 4);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;

		case "Underground1": //крутая мочалка
			dialog.text = StringFromKey("Colodec_27");
			Link.l1 = StringFromKey("Colodec_28");
			Link.l1.go = "Underground1_1";
		break;
		case "Underground1_1":
			dialog.text = StringFromKey("Colodec_29");
			Link.l1 = StringFromKey("Colodec_30");
			Link.l1.go = "Underground1_2";
		break;
		case "Underground1_2":
			dialog.text = StringFromKey("Colodec_31", pchar);
			Link.l1 = StringFromKey("Colodec_32");
			Link.l1.go = "Underground1_3";
		break;
		case "Underground1_3":
			dialog.text = StringFromKey("Colodec_33");
			Link.l1 = StringFromKey("Colodec_34");
			Link.l1.go = "Underground1_4";
		break;
		case "Underground1_4":
			dialog.text = StringFromKey("Colodec_35");
			Link.l1 = StringFromKey("Colodec_36");
			Link.l1.go = "Underground1_5";
		break;
		case "Underground1_5":
			dialog.text = StringFromKey("Colodec_37");
			Link.l1 = StringFromKey("Colodec_38");
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		case "Underground1_again":
			dialog.text = StringFromKey("Colodec_39", pchar);
			Link.l1 = StringFromKey("Colodec_40");
			Link.l1.go = "exit";
			NextDiag.TempNode = "Underground1_again";
		break;

	}
}
