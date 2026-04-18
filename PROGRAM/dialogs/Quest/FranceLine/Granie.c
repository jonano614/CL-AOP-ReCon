//TODO: переделать офицерские ноды в этом диалоге в зависимости от ситуации

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		//Офицерские ноды (BETA) -->
		//Выпилено: компаньон, наместник, абордажник, увольнение
		//TODO: забрать CompanionDisable из ККС; также для Тичингиту, Фликера, Данек и т.д.
		//TODO: должен быть greeting по умолчанию, но с учётом воспроизводимых звуков
		case "Hired":
			PlayVoice("Voice\" + VoiceGetLanguage() + "\FranceLine\canonir.wav");

			NextDiag.TempNode = "Hired";
			dialog.text = StringFromKey("Granie_1");

			if (CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
				Link.l8 = StringFromKey("Granie_2", GetStrSmallRegister(XI_ConvertString("treasurer")));
				Link.l8.go = "QMASTER_1";
				Link.l11 = StringFromKey("Granie_3");
				Link.l11.go = "TransferGoodsEnable";
			}

			Link.l9 = StringFromKey("Granie_4");
			Link.l9.go = "Exit";
		break;

		case "TransferGoodsEnable":
			if (sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = StringFromKey("Granie_5");
				Link.l1 = StringFromKey("Granie_6");
				Link.l1.go = "Exit";
				NextDiag.TempNode = "Hired";
				break;
			}
			dialog.text = StringFromKey("Granie_9", RandPhraseSimple(
						StringFromKey("Granie_7"),
						StringFromKey("Granie_8")));
			Link.l1 = StringFromKey("Granie_10");
			Link.l1.go = "TransferGoodsEnable_2";
		break;

		case "TransferGoodsEnable_2":
			NextDiag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen();
		break;

		case "QMASTER_1":
			if (sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = StringFromKey("Granie_11");
				Link.l1 = StringFromKey("Granie_12");
				Link.l1.go = "Exit";
				NextDiag.TempNode = "Hired";
				break;
			}
			dialog.text = StringFromKey("Granie_13", FloatToString(50.0 / (2.0 + GetSummonSkillFromNameToOld(PChar, SKILL_REPAIR) + GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK)), 1), FindSailorString(GetCrewQuantity(PChar), "Acc"), makeint((GetCrewQuantity(PChar) + 6) / 10));
			Link.l1 = StringFromKey("Granie_14");
			Link.l1.go = "Exit";
			NextDiag.TempNode = "Hired";
		break;
		// <-- Офицерские ноды

		// Квестовые ноды -->
		/* первый диалог - в пещере */
		case "0":
			NextDiag.TempNode = "0";
			if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest != "")
			{
				dialog.text = StringFromKey("Granie_15");
				link.l1 = "...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "" && sti(pchar.Money) <= 9999)
			{
				PlaySound("Voice\" + VoiceGetLanguage() + "\FranceLine\merzavci.ogg");
				dialog.text = StringFromKey("Granie_16");
				link.l1 = StringFromKey("Granie_17");
				link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "" && sti(pchar.Money) >= 10000)
			{
				PlaySound("Voice\" + VoiceGetLanguage() + "\FranceLine\merzavci.ogg");
				dialog.text = StringFromKey("Granie_18");
				link.l1 = StringFromKey("Granie_19");
				link.l1.go = "1";
			}
		break;

		case "1":
			dialog.text = StringFromKey("Granie_20");
			link.l1 = StringFromKey("Granie_21");
			link.l1.go = "2";
		break;

		case "2":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = StringFromKey("Granie_22");
			link.l1 = StringFromKey("Granie_23");
			link.l1.go = "3";
		break;

		case "3":
			AddMoneyToCharacter(pchar, 5000);
			dialog.text = StringFromKey("Granie_24");
			link.l1 = StringFromKey("Granie_25");
			link.l1.go = "4";
		break;

		case "4":
			dialog.text = StringFromKey("Granie_26");
			link.l1 = StringFromKey("Granie_27");
			link.l1.go = "exit";

			NextDiag.TempNode = "5";
			AddDialogExitQuest("FL2_s26");
		break;
		/* -------------------------------------------------------------------- */

		/* второй диалог - на корабле */
		case "5":
			dialog.text = "...";
			link.l1 = StringFromKey("Granie_28");
			link.l1.go = "6";
		break;

		case "6":
			PlaySound("Voice\" + VoiceGetLanguage() + "\FranceLine\canonir.wav");
			dialog.text = StringFromKey("Granie_29");
			link.l1 = StringFromKey("Granie_30");
			link.l1.go = "7";
		break;

		case "7":
			dialog.text = StringFromKey("Granie_31");
			link.l1 = StringFromKey("Granie_32");
			link.l1.go = "8";
		break;

		case "8":
			dialog.text = StringFromKey("Granie_33");
			link.l1 = StringFromKey("Granie_34");
			link.l1.go = "9";
		break;

		case "9":
			dialog.text = StringFromKey("Granie_35");
			link.l1 = StringFromKey("Granie_36");
			link.l1.go = "10";
		break;

		case "10":
			dialog.text = StringFromKey("Granie_37");
			link.l1 = StringFromKey("Granie_38");
			link.l1.go = "11";
		break;

		case "11":
			dialog.text = StringFromKey("Granie_39");
			link.l1 = StringFromKey("Granie_40");
			link.l1.go = "12";
		break;

		case "12":
			dialog.text = StringFromKey("Granie_41");
			link.l1 = StringFromKey("Granie_42");
			link.l1.go = "13";
		break;

		case "13":
			dialog.text = StringFromKey("Granie_43");
			link.l1 = StringFromKey("Granie_44");
			link.l1.go = "14";
		break;

		case "14":
			dialog.text = StringFromKey("Granie_45");
			link.l1 = StringFromKey("Granie_46");
			link.l1.go = "exit";

			NextDiag.TempNode = "15";
		break;
		/* -------------------------------------------------------------------- */

		/* в ФдФ */
		case "15":
			dialog.text = StringFromKey("Granie_47");
			link.l1 = StringFromKey("Granie_48");
			link.l1.go = "16";
		break;

		case "16":
			dialog.text = StringFromKey("Granie_49");
			link.l1 = StringFromKey("Granie_50");
			link.l1.go = "exit";

			NextDiag.TempNode = "17";
		break;
		/* -------------------------------------------------------------------- */

		/* в таверне ФдФ */
		case "17":
			dialog.text = StringFromKey("Granie_51");
			link.l1 = StringFromKey("Granie_52");
			link.l1.go = "exit";

			AddDialogExitQuest("FL2_s36");
			NextDiag.TempNode = "18";
		break;

		case "18":
			dialog.text = StringFromKey("Granie_53");
			link.l1 = StringFromKey("Granie_54");
			link.l1.go = "19";
		break;

		case "19":
			dialog.text = StringFromKey("Granie_55");
			link.l1 = StringFromKey("Granie_56");
			link.l1.go = "20";
		break;

		case "20":
			dialog.text = StringFromKey("Granie_57");
			link.l1 = StringFromKey("Granie_58");
			link.l1.go = "21";
		break;

		case "21":
			dialog.text = StringFromKey("Granie_59");
			link.l1 = StringFromKey("Granie_60");
			link.l1.go = "exit";

			NextDiag.TempNode = "22";
		break;
		/* -------------------------------------------------------------------- */

		/* в таверне на Тортуге */
		case "22":
			dialog.text = StringFromKey("Granie_61");
			link.l1 = StringFromKey("Granie_62");
			link.l1.go = "23";
		break;

		case "23":
			dialog.text = StringFromKey("Granie_63");
			link.l1 = StringFromKey("Granie_64");
			link.l1.go = "24";
		break;

		case "24":
			dialog.text = StringFromKey("Granie_65");
			link.l1 = StringFromKey("Granie_66");
			link.l1.go = "25";
		break;

		case "25":
			dialog.text = StringFromKey("Granie_67");
			link.l1 = StringFromKey("Granie_68");
			link.l1.go = "26";
		break;

		case "26":
			dialog.text = StringFromKey("Granie_69");
			link.l1 = StringFromKey("Granie_70");
			link.l1.go = "27";
		break;

		case "27":
			dialog.text = StringFromKey("Granie_71");
			link.l1 = StringFromKey("Granie_72");
			link.l1.go = "28";
		break;

		case "28":
			dialog.text = StringFromKey("Granie_73");
			link.l1 = StringFromKey("Granie_74");
			link.l1.go = "29";
		break;

		case "29":
			dialog.text = StringFromKey("Granie_75");
			link.l1 = "...";
			link.l1.go = "exit";

			LAi_SetImmortal(NPChar, false); //ПОТОМ СМОТРИ, ЧТОБЫ КВЕСТЫ НЕ ПОТЕРЯЛИСЬ
			NextDiag.TempNode = "Hired"; //"30";
		break;
		/* -------------------------------------------------------------------- */

		//ПРОВЕРЬ
		/* диалог в каюте возле Портобело */
		case "30":
			dialog.text = StringFromKey("Granie_76");
			link.l1 = StringFromKey("Granie_77");
			link.l1.go = "31";
		break;

		case "31":
			dialog.text = StringFromKey("Granie_78");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "Hired"; //"32";
		break;
		/* -------------------------------------------------------------------- */

		//ПРОВЕРЬ
		/* диалог на пристани Картахены */
		case "32":
			dialog.text = StringFromKey("Granie_79");
			link.l1 = StringFromKey("Granie_80");
			link.l1.go = "33";
		break;

		case "33":
			dialog.text = StringFromKey("Granie_81");
			link.l1 = StringFromKey("Granie_82");
			link.l1.go = "34";
		break;

		case "34":
			dialog.text = StringFromKey("Granie_83");
			link.l1 = StringFromKey("Granie_84");
			link.l1.go = "35";
		break;

		case "35":
			dialog.text = StringFromKey("Granie_85");
			link.l1 = StringFromKey("Granie_86");
			link.l1.go = "36";
		break;

		case "36":
			dialog.text = StringFromKey("Granie_87");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "Hired"; //"37";
		break;
		/* -------------------------------------------------------------------- */

		//ПРОВЕРЬ
		/* диалог на пристани Куманы */
		case "37":
			dialog.text = StringFromKey("Granie_88");
			link.l1 = StringFromKey("Granie_89");
			link.l1.go = "38";
		break;

		case "38":
			dialog.text = StringFromKey("Granie_90");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "Hired"; //"39";
		break;
		/* -------------------------------------------------------------------- */

		//ПРОВЕРЬ
		/* диалог в таверне Куманы */
		case "39":
			dialog.text = "...";
			link.l1 = StringFromKey("Granie_91");
			link.l1.go = "40";
		break;

		case "40":
			dialog.text = StringFromKey("Granie_92");
			link.l1 = StringFromKey("Granie_93");
			link.l1.go = "41";
		break;

		case "41":
			dialog.text = StringFromKey("Granie_94");
			link.l1 = StringFromKey("Granie_95");
			link.l1.go = "42";
		break;

		case "42":
			dialog.text = StringFromKey("Granie_96");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "Hired"; //"43";
		break;
		/* -------------------------------------------------------------------- */

		//ПРОВЕРЬ
		/* диалог на палубе, во время псевдоабордажа */
		case "43":
			dialog.text = StringFromKey("Granie_97");
			link.l1 = StringFromKey("Granie_98");
			link.l1.go = "44";
		break;

		case "44":
			dialog.text = StringFromKey("Granie_99");
			link.l1 = StringFromKey("Granie_100");
			link.l1.go = "45";
		break;

		case "45":
			dialog.text = StringFromKey("Granie_101");
			link.l1 = StringFromKey("Granie_102");
			link.l1.go = "46";
		break;

		case "46":
			dialog.text = StringFromKey("Granie_103");
			link.l1 = StringFromKey("Granie_104");
			link.l1.go = "47";
		break;

		case "47":
			dialog.text = StringFromKey("Granie_105");
			link.l1 = StringFromKey("Granie_106");
			link.l1.go = "48";
		break;

		case "48":
			dialog.text = StringFromKey("Granie_107");
			link.l1 = StringFromKey("Granie_108");
			link.l1.go = "49";
		break;

		case "49":
			dialog.text = StringFromKey("Granie_109");
			link.l1 = StringFromKey("Granie_110");
			link.l1.go = "50";
		break;

		case "50":
			dialog.text = StringFromKey("Granie_111");
			link.l1 = StringFromKey("Granie_112");
			link.l1.go = "exit";

			NextDiag.TempNode = "Hired"; //"51";
		break;
		/* -------------------------------------------------------------------- */

		//ПРОВЕРЬ
		/* case name */
		case "51":
			dialog.text = StringFromKey("Granie_113");
			link.l1 = StringFromKey("Granie_114");
			link.l1.go = "52";
		break;

		case "52":
			dialog.text = StringFromKey("Granie_115");
			link.l1 = StringFromKey("Granie_116");
			link.l1.go = "53";
		break;

		case "53":
			dialog.text = StringFromKey("Granie_117");
			link.l1 = StringFromKey("Granie_118");
			link.l1.go = "exit";

			NextDiag.TempNode = "Hired"; //"54";
		break;
		/* -------------------------------------------------------------------- */

		//ПРОВЕРЬ
		/* case name */
		case "54":
			dialog.text = StringFromKey("Granie_119");
			link.l1 = StringFromKey("Granie_120");
			link.l1.go = "55";
		break;

		case "55":
			dialog.text = StringFromKey("Granie_121");
			link.l1 = StringFromKey("Granie_122");
			link.l1.go = "56";
		break;

		case "56":
			dialog.text = StringFromKey("Granie_123");
			link.l1 = StringFromKey("Granie_124");
			link.l1.go = "57";
		break;

		case "57":
			dialog.text = StringFromKey("Granie_125");
			link.l1 = StringFromKey("Granie_126");
			link.l1.go = "58";
		break;

		case "58":
			dialog.text = StringFromKey("Granie_127");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "Hired"; //"59";
		break;
		/* -------------------------------------------------------------------- */

		//ПРОВЕРЬ
		/* case name */
		case "59":
			dialog.text = StringFromKey("Granie_128");
			link.l1 = StringFromKey("Granie_129");
			link.l1.go = "60";
		break;

		case "60":
			dialog.text = StringFromKey("Granie_130");
			link.l1 = StringFromKey("Granie_131");
			link.l1.go = "61";
		break;

		case "61":
			dialog.text = StringFromKey("Granie_132");
			link.l1 = StringFromKey("Granie_133");
			link.l1.go = "62";
		break;

		case "62":
			dialog.text = StringFromKey("Granie_134");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "Hired"; //"63";
		break;
		/* -------------------------------------------------------------------- */

		//ПРОВЕРЬ
		/* case name */
		case "63":
			dialog.text = StringFromKey("Granie_135");
			link.l1 = StringFromKey("Granie_136");
			link.l1.go = "64";
		break;

		case "64":
			dialog.text = StringFromKey("Granie_137");
			link.l1 = StringFromKey("Granie_138");
			link.l1.go = "65";
		break;

		case "65":
			dialog.text = StringFromKey("Granie_139");
			link.l1 = StringFromKey("Granie_140");
			link.l1.go = "66";
		break;

		case "66":
			dialog.text = StringFromKey("Granie_141");
			link.l1 = StringFromKey("Granie_142");
			link.l1.go = "67";
		break;

		case "67":
			dialog.text = StringFromKey("Granie_143");
			link.l1 = StringFromKey("Granie_144");
			link.l1.go = "68";
		break;

		case "68":
			dialog.text = StringFromKey("Granie_145");
			link.l1 = StringFromKey("Granie_146");
			link.l1.go = "69";
		break;

		case "69":
			dialog.text = StringFromKey("Granie_147");
			link.l1 = StringFromKey("Granie_148");
			link.l1.go = "70";
		break;

		case "70":
			dialog.text = StringFromKey("Granie_149");
			link.l1 = StringFromKey("Granie_150");
			link.l1.go = "71";
		break;

		case "71":
			dialog.text = StringFromKey("Granie_151");
			link.l1 = StringFromKey("Granie_152");
			link.l1.go = "72";
		break;

		case "72":
			dialog.text = StringFromKey("Granie_153");
			link.l1 = StringFromKey("Granie_154");
			link.l1.go = "73";
		break;

		case "73":
			dialog.text = StringFromKey("Granie_155");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "Hired"; //"74";
		break;
		/* -------------------------------------------------------------------- */

		//ПРОВЕРЬ
		/* case name */
		case "74":
			dialog.text = StringFromKey("Granie_156");
			link.l1 = StringFromKey("Granie_157");
			link.l1.go = "75";
		break;

		case "75":
			dialog.text = StringFromKey("Granie_158");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "Hired"; //"76";
		break;
		/* -------------------------------------------------------------------- */

		//ПРОВЕРЬ
		/* case name */
		case "76":
			dialog.text = StringFromKey("Granie_159");
			link.l1 = StringFromKey("Granie_160");
			link.l1.go = "77";
		break;

		case "77":
			dialog.text = StringFromKey("Granie_161");
			link.l1 = StringFromKey("Granie_162");
			link.l1.go = "78";
		break;

		case "78":
			dialog.text = StringFromKey("Granie_163");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "Hired"; //"79";
		break;
		/*--------------------------------------------------------------------- */

		//ПРОВЕРЬ
		/* case name */
		case "79":
			dialog.text = StringFromKey("Granie_164");
			link.l1 = StringFromKey("Granie_165");
			link.l1.go = "80";
		break;

		case "80":
			dialog.text = "...";
			link.l1 = StringFromKey("Granie_166");
			link.l1.go = "81";
		break;

		case "81":
			dialog.text = StringFromKey("Granie_167");
			link.l1 = StringFromKey("Granie_168");
			link.l1.go = "82";
		break;

		case "82":
			dialog.text = StringFromKey("Granie_169");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "Hired"; //"83";
		break;
		/* -------------------------------------------------------------------- */

		//ПРОВЕРЬ
		/* case name */
		case "83":
			dialog.text = StringFromKey("Granie_170");
			link.l1 = StringFromKey("Granie_171");
			link.l1.go = "84";
		break;

		case "84":
			dialog.text = StringFromKey("Granie_172");
			link.l1 = StringFromKey("Granie_173");
			link.l1.go = "85";
		break;

		case "85":
			dialog.text = StringFromKey("Granie_174");
			link.l1 = StringFromKey("Granie_175");
			link.l1.go = "exit";

			NextDiag.TempNode = "Hired"; //"86";
		break;
		// <-- Квестовые ноды

		case "exit":
			if (CheckAttribute(NextDiag, "TempNode")) NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		/*case "CitizenNotBlade": //HardCoffee ref
			dialog.text = "Капитан, что за глупости! Уберите оружие, пока бед не наделали!";
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Не переживай, уже убираю...");
			link.l1.go = "exit";
		break;*/
	}
}
