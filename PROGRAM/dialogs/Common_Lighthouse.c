#include "DIALOGS\Rumours\Simple_rumors.c" //Jason
// Jason общий диалог смотрителей маяков
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\Lighthouse\" + NPChar.City + "_Lighthouse.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	int iTest, iTemp;
	string sTemp;
	bool ok;
	iTest = FindColony(NPChar.City); // город
	ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch (Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = PCharRepPhrase(
							StringFromKey("Common_Lighthouse_4", LinkRandPhrase(
									StringFromKey("Common_Lighthouse_1"),
									StringFromKey("Common_Lighthouse_2"),
									StringFromKey("Common_Lighthouse_3"))),
							StringFromKey("Common_Lighthouse_8", LinkRandPhrase(
									StringFromKey("Common_Lighthouse_5", pchar),
									StringFromKey("Common_Lighthouse_6", pchar),
									StringFromKey("Common_Lighthouse_7", pchar))));
				link.l1 = PCharRepPhrase(
							StringFromKey("Common_Lighthouse_11", RandPhraseSimple(
									StringFromKey("Common_Lighthouse_9"),
									StringFromKey("Common_Lighthouse_10", XI_ConvertString("Colony" + npchar.city + "Gen")))),
							StringFromKey("Common_Lighthouse_14", RandPhraseSimple(
									StringFromKey("Common_Lighthouse_12"),
									StringFromKey("Common_Lighthouse_13"))));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}

			// линейка капитана Блада
			if (Pchar.questTemp.CapBloodLine == true)
			{
				if (npchar.quest.meeting == "0")
				{
					dialog.text = StringFromKey("Common_Lighthouse_44", GetFullName(npchar));
					link.l1 = StringFromKey("Common_Lighthouse_45", GetLastName(npchar));
					link.l1.go = "Lightman_meeting_blood";
					npchar.quest.meeting = "1";
				}
				else
				{
					dialog.text = StringFromKey("Common_Lighthouse_46");
					link.l1 = StringFromKey("Common_Lighthouse_47");
					link.l1.go = "Lightman_talk_blood";
				}
				NextDiag.TempNode = "First time";
				break;
			}

			if (npchar.quest.meeting == "0")
			{
				dialog.text = StringFromKey("Common_Lighthouse_17", RandPhraseSimple(
							StringFromKey("Common_Lighthouse_15", GetFullName(npchar)),
							StringFromKey("Common_Lighthouse_16", GetFullName(npchar))));
				link.l1 = StringFromKey("Common_Lighthouse_18", pchar, npchar.name, GetFullName(pchar));
				link.l1.go = "Lightman_meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = StringFromKey("Common_Lighthouse_19", GetFullName(pchar));
				link.l1 = StringFromKey("Common_Lighthouse_20");
				link.l1.go = "Lightman_talk";
			}
			NextDiag.TempNode = "First time";
		break;

		case "Lightman_meeting":
			dialog.text = StringFromKey("Common_Lighthouse_21");
			/* link.l1 = "А чем ты торгуешь, скажи пожалуйста?";
			link.l1.go = "trade_info"; */
			link.l1 = StringFromKey("Common_Lighthouse_22");
			link.l1.go = "Trade_lighthouse";
			link.l2 = StringFromKey("Common_Lighthouse_25", RandPhraseSimple(
						StringFromKey("Common_Lighthouse_23"),
						StringFromKey("Common_Lighthouse_24", pchar)));
			link.l2.go = "rumours_lighthouse";
			link.l3 = StringFromKey("Common_Lighthouse_26", pchar);
			link.l3.go = "quests";
		break;

		case "Lightman_talk":
			dialog.text = StringFromKey("Common_Lighthouse_27");
			link.l1 = StringFromKey("Common_Lighthouse_30", RandPhraseSimple(
						StringFromKey("Common_Lighthouse_28"),
						StringFromKey("Common_Lighthouse_29", pchar)));
			link.l1.go = "rumours_lighthouse";
			link.l2 = StringFromKey("Common_Lighthouse_31", pchar);
			link.l2.go = "quests";
			NextDiag.TempNode = "First time";

			link.l3 = StringFromKey("Common_Lighthouse_32");
			link.l3.go = "Trade_lighthouse";
			link.l9 = StringFromKey("Common_Lighthouse_33", pchar);
			link.l9.go = "exit";

		/*if (CheckAttribute(npchar, "artefact"))
		{
			if (CheckAttribute(npchar, "quest.art"))
			{
				link.l4 = "Ну что, "+npchar.name+", мой амулет ещё не привезли?";
				link.l4.go = "Trade_artefact_3";
			}
			else
			{
				link.l4 = npchar.name+", я хочу заказать у тебя амулет.";
				link.l4.go = "Trade_artefact_1";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "amulet" && !CheckAttribute(npchar, "quest.Caleuche"))
			{
				link.l5 = "Послушай, "+npchar.name+", я знаю, что ты занимаешься привозом амулетов под заказ. Значит, ты наверняка в них хорошо разбираешься. Посмотри, пожалуйста, на эту вещицу - что ты можешь сказать о ней?";
				link.l5.go = "Caleuche";
			}
			if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster && CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "mayak")
			{
				link.l5 = "Приятель, я снова к тебе по поводу тех странных амулетов.";
				link.l5.go = "Caleuche_9";
			}
		}
		NextDiag.TempNode = "First time";*/
		break;

		// линейка капитана Блада
		case "Lightman_meeting_blood":
			dialog.text = StringFromKey("Common_Lighthouse_48");
			link.l1 = StringFromKey("Common_Lighthouse_49", GetFirstName(npchar));
			link.l1.go = "Lightman_meeting_blood_1_1";
			link.l2 = StringFromKey("Common_Lighthouse_50", GetLastName(npchar));
			link.l2.go = "Lightman_meeting_blood_1_2";
		break;

		case "Lightman_meeting_blood_1_1":
			AddCharacterExpToSkill(pchar, "Commerce", 35); // (+ опыт в торговлю)

			dialog.text = StringFromKey("Common_Lighthouse_51");
			link.l1 = StringFromKey("Common_Lighthouse_52", GetLastName(npchar));
			link.l1.go = "Trade_lighthouse";
		break;

		case "Lightman_meeting_blood_1_2":
			ChangeCharacterReputation(pchar, 5); // (+ чутка репутации)

			dialog.text = StringFromKey("Common_Lighthouse_53");
			link.l1 = StringFromKey("Common_Lighthouse_54", GetLastName(npchar));
			link.l1.go = "Trade_lighthouse";
		break;

		case "Lightman_talk_blood":
			dialog.text = StringFromKey("Common_Lighthouse_58", LinkRandPhrase(
	StringFromKey("Common_Lighthouse_55"),
	StringFromKey("Common_Lighthouse_56"),
	StringFromKey("Common_Lighthouse_57")));
			link.l1 = StringFromKey("Common_Lighthouse_59");
			link.l1.go = "Trade_lighthouse";

			link.l9 = StringFromKey("Common_Lighthouse_60");
			link.l9.go = "exit";

			NextDiag.TempNode = "First time";
		break;
		// <--

		/*case "trade_info":
			dialog.text = "Время от времени я хожу за раковинами. Здесь недалеко есть неплохое местечко. Так что у меня всегда можно купить жемчужины. После каждого шторма я обхожу свой пляж - море выбрасывает на берег куски янтаря - его я тоже продаю, хотя сразу говорю - недёшево\nИногда волны выкидывают всякие занятные вещицы с утонувших кораблей, да и мои старые знакомцы привозят диковины на продажу, но меня в основном интересуют заговорённые амулеты - за них можно выручить у знающего человека хорошую сумму\nИногда мне приносят, или я сам нахожу на... ну, неважно где, сабли и прочее оружие. Всякий хлам у меня покупает городской торговец, а достойные экземпляры я привожу в порядок и выставляю на продажу\nА вот насчёт купить - меня интересует ром. Только не это дешёвое пойло, что в кабаке по два пиастра за кружку продают, а бутилированный ямайский ром многолетней выдержки. Он способен исцелять от хворей и невероятно бодрит с первого же глотка. Я готов платить десятикратную цену за каждую бутылку, так что приносите.";
			link.l1 = "Послушай, "+npchar.name+", ты сказал, что у тебя есть старые друзья-моряки, которые привозят тебе заговорённые амулеты. А нельзя ли заказать тебе конкретный амулет? Я хорошо заплачу.";
			link.l1.go = "Trade_artefact";
		break;*/

		case "Trade_lighthouse":
		//иногда продает корабельные товары // Addon-2016 Jason
			npchar.quest.goods = GOOD_COFFEE + idRand(npchar.id + "Trade_lighthouse_goods", sti(GOOD_PAPRIKA - GOOD_COFFEE));
			npchar.quest.goodsqty = 50 + idRand(npchar.id + "Trade_lighthouse", 100);
			if (sti(npchar.quest.goods) == GOOD_EBONY || sti(npchar.quest.goods) == GOOD_MAHOGANY) npchar.quest.goodsqty = 25 + idRand(npchar.id + "Trade_lighthouse", 50);
			npchar.quest.goodsprice = makeint(sti(Goods[sti(npchar.quest.goods)].Cost) / 4);//цена единицы товара
			npchar.quest.goodscost = sti(npchar.quest.goodsprice) * sti(npchar.quest.goodsqty);//стоимость товара
			ok = (!CheckAttribute(npchar, "goods_date")) || (GetNpcQuestPastDayParam(npchar, "goods_date") >= 10);
			ok = ok && pchar.questTemp.CapBloodLine == false;
			if (idRand(npchar.id + "Trade_lighthouse", 4) == 1 && makeint(GetCharacterFreeSpace(pchar, sti(npchar.quest.goods))) > sti(npchar.quest.goodsqty) && sti(pchar.money) >= sti(npchar.quest.goodscost) && ok)
			{
				dialog.text = StringFromKey("Common_Lighthouse_34", GetGoodsNameAlt(sti(npchar.quest.goods)), FindQtyString(sti(npchar.quest.goodsqty)), FindMoneyString(sti(npchar.quest.goodsprice)));
				link.l1 = StringFromKey("Common_Lighthouse_35");
				link.l1.go = "Trade_lighthouse_double";
				link.l2 = StringFromKey("Common_Lighthouse_36", pchar, FindMoneyString(sti(npchar.quest.goodscost)));
				link.l2.go = "Trade_goods";
				SaveCurrentNpcQuestDateParam(npchar, "goods_date");
			}
			else
			{
				if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
				{
					GiveItemToTrader(npchar);
					SaveCurrentNpcQuestDateParam(npchar, "trade_date");
				}

				Nextdiag.CurrentNode = Nextdiag.TempNode;
				DialogExit();
				LaunchItemsTrade(NPChar);
			}
		break;

		case "Trade_lighthouse_double":
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}

			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar);
		break;

		case "Trade_goods":
			AddCharacterGoods(pchar, sti(npchar.quest.goods), sti(npchar.quest.goodsqty));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.goodscost));
			AddMoneyToCharacter(npchar, sti(npchar.quest.goodscost));
			dialog.text = StringFromKey("Common_Lighthouse_37");
			link.l1 = StringFromKey("Common_Lighthouse_38");
			link.l1.go = "Trade_lighthouse_double";
		break;
		//------------------------------------------------заказ артефактов------------------------------------------------
		/* case "Trade_artefact": // Addon-2016 Jason за дублоны
			if (CheckAttribute(npchar, "artefact"))
			{
				dialog.text = "Ну, не всё конечно, но кое-какие вещицы мне привозят чаще других, так что, думаю, смогу вам помочь. Сразу предупреждаю: стоимость любого амулета под заказ - 100 дублонов. Сами понимаете...";
				link.l1 = "Цена меня не пугает. И какие амулеты ты сможешь достать?";
				link.l1.go = "Trade_artefact_1";
				link.l2 = "Да ну! Дороговато выходит. Лучше я уж как-нибудь сам" + GetSexPhrase("", "а") + "...";
				link.l2.go = "exit_artefact";
			}
			else
			{
				dialog.text = "Нет, капитан. Эти вещицы находят случайно, как их можно привезти под заказ? Да и ждать пришлось бы невесть сколько времени...";
				link.l1 = "Ну, как говорится, на нет - и суда нет...";
				link.l1.go = "exit_artefact";
			}
		break;
		
		case "exit_artefact":
			if (CheckAttribute(npchar, "artefact")) dialog.text = "Ну, как знаете. Надумаете - обращайтесь.";
			else dialog.text = "Будете смотреть, что у меня есть сегодня в продаже, капитан? Если ничего достойного не найдёте - заходите ещё, почаще, может, что интересующее вас и появится.";
			link.l1 = "Покажи мне свои товары.";
			link.l1.go = "Trade_lighthouse";
			link.l2 = RandPhraseSimple("Лучше расскажи, что интересного в вашей колонии случилось за последнее время?","Торговля-торговлей, а вот я давненько не был" + GetSexPhrase("", "а") + " на суше... Что новенького в ваших краях?");
			link.l2.go = "rumours_lighthouse";
			link.l3 = "Всё это, конечно, хорошо, но я вот что хотел" + GetSexPhrase("", "а") + " спросить...";
			link.l3.go = "quests";
			link.l4 = "Всего доброго, "+npchar.name+"! Приятно было познакомиться! Ещё загляну...";
			link.l4.go = "exit";
		break;
		
		case "Trade_artefact_1":
			dialog.text = "Выбирайте.";
			iTemp = 1;
			string sArt;
			if (CheckAttribute(npchar, "artefact.indian")) sArt = "indian_";
			if (CheckAttribute(npchar, "artefact.amulet")) sArt = "amulet_";
			if (CheckAttribute(npchar, "artefact.obereg")) sArt = "obereg_";
			for (i=11; i>=1; i--)
			{
				sTemp = "l"+iTemp;
				link.(sTemp) = XI_ConvertString(sArt+i);
				link.(sTemp).go = sArt+i;
				iTemp++;
			}
			link.l12 = "К сожалению, ничего из этого списка меня не интересует.";
			link.l12.go = "exit";
		break;
		
		//группа indian
		case "indian_1":
			dialog.text = "Кукла Вуду? Уважаете огнестрельное оружие? Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_1";
		break;
		
		case "indian_2":
			dialog.text = "Пороховой тестер? Меткая стрельба - залог успеха в схватке. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_2";
		break;
		
		case "indian_3":
			dialog.text = "Ритуальный нож? Любите от души рубануть своего врага тяжёлым палашом? Тогда это точно для вас. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_3";
		break;
		
		case "indian_4":
			dialog.text = "Секира? Нет надёжней удара, чем рубануть сверху вниз здоровенным топором! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_4";
		break;
		
		case "indian_5":
			dialog.text = "Тсантса? Эта штучка припугнёт даже самого отчаянного пирата. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_5";
		break;
		
		case "indian_6":
			dialog.text = "Коралловая голова? Пусть картечь из ваших пушек летит всегда точно в цель! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_6";
		break;
		
		case "indian_7":
			dialog.text = "Горбун? Неутомимость - это лучший друг воина. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_7";
		break;
		
		case "indian_8":
			dialog.text = "Шиутекутли? Пускай корпус вражеского судна рассыпется в труху! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_8";
		break;
		
		case "indian_9":
			dialog.text = "Бальд? Наденьте Бальд - и пусть все ядра летят точно в цель! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_9";
		break;
		
		case "indian_10":
			dialog.text = "Каскавела? Нет ничего страшнее змеиного яда. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_10";
		break;
		
		case "indian_11":
			dialog.text = "Маска нгомбо? Надень и усыпи бдительность врагов, ха-ха! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_11";
		break;
		
		//группа amulet
		case "amulet_1":
			dialog.text = "Щит нгомбо? Если не удалось увернуться от пули, этот амулет может спасти жизнь. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_1";
		break;
		
		case "amulet_2":
			dialog.text = "Молитвослов? Добрая молитва способна даже пулю отвести в сторону. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_2";
		break;
		
		case "amulet_3":
			dialog.text = "Нательный крест? Он здорово поможет христианину в рукопашной схватке. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_3";
		break;
		
		case "amulet_4":
			dialog.text = "Эль Трозо? Он делает смертельную рану лёгкой царапиной. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_4";
		break;
		
		case "amulet_5":
			dialog.text = "Согбо? И пусть пушки будут всегда готовы к бою! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_5";
		break;
		
		case "amulet_6":
			dialog.text = "Мадонна? Образ Пресвятой Девы обладает воистину исцеляющими способностями. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_6";
		break;
		
		case "amulet_7":
			dialog.text = "Святая вода? Даже хиляк, окропившийся святой водой, становится богатырём! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_7";
		break;
		
		case "amulet_8":
			dialog.text = "Якорь? И пусть судно остается на плаву под градом ядер, ха-ха! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_8";
		break;
		
		case "amulet_9":
			dialog.text = "Энколпион? Никакой ветер не страшен парусам, если у вас есть этот амулет. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_9";
		break;
		
		case "amulet_10":
			dialog.text = "Чудотворец? Да хранит Господь вашу команду на суше и на море! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_10";
		break;
		
		case "amulet_11":
			dialog.text = "Чимарута? Мушкетные пули просвистят над головами, не причинив вреда! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_11";
		break;
		
		//группа obereg
		case "obereg_1":
			dialog.text = "Тередо? Каждый корабельный плотник мечтает о нём. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_1";
		break;
		
		case "obereg_2":
			dialog.text = "Шочипили? Всё меньше колоть пальцы иглой, штопая паруса. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_2";
		break;
		
		case "obereg_3":
			dialog.text = "Обезьяна? А по мне так - вьючный мул! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_3";
		break;
		
		case "obereg_4":
			dialog.text = "Веер цыганки? Надень шоры на глаза патрулю! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_4";
		break;
		
		case "obereg_5":
			dialog.text = "Нефритовая черепашка? Это ваш джокер в колоде карт! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_5";
		break;
		
		case "obereg_6":
			dialog.text = "Обезьяний кулак? Как говорится - заставь уважать себя! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_6";
		break;
		
		case "obereg_7":
			dialog.text = "Рыбак? Его видит во сне каждый штурман. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_7";
		break;
		
		case "obereg_8":
			dialog.text = "Чётки торговца? Деньги любят счёт, не правда ли? Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_8";
		break;
		
		case "obereg_9":
			dialog.text = "Эхекатль? Любое тихоходное корыто несётся быстрее ветра! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_9";
		break;
		
		case "obereg_10":
			dialog.text = "Серьга морехода? Вставьте её в ухо своему рулевому! Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_10";
		break;
		
		case "obereg_11":
			dialog.text = "Пилигрим? Встречный ветер становится попутным. Хорошо...";
			link.l1 = "Когда мне вернуться к тебе за своим заказом?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_11";
		break;
		
		case "Trade_artefact_2":
			dialog.text = "Месяца через два, не раньше. Думаю, к тому моменту мне уже его привезут. Так что жду вас к этому времени с деньгами.";
			link.l1 = "Хорошо! Обязательно буду! Спасибо, "+npchar.name+"!";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "art_date");
			npchar.quest.artday = rand(20)+50;
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "1");
			ReOpenQuestHeader(sTemp);
			AddQuestUserData(sTemp, "sAml", XI_ConvertString(npchar.quest.art)); // dlc
		break;
		
		case "Trade_artefact_3":
			if (CheckAttribute(npchar, "art_date") && GetNpcQuestPastDayParam(npchar, "art_date") >= sti(npchar.quest.artday))
			{
			dialog.text = "Да, он у меня. Вы приготовили 100 дублонов, капитан?"; // Addon-2016 Jason
				if(GetCharacterItem(pchar, "gold_dublon") >= 100)
				{
					link.l1 = "Конечно! Вот, держи, как и договаривались.";
					link.l1.go = "Trade_artefact_4";
				}
				else
				{
					link.l1 = "Эх, деньги на корабле забыл" + GetSexPhrase("", "а") + "! Сейчас принесу...";
					link.l1.go = "exit";
				}
			}
			else
			{
			dialog.text = "Ещё нет. Загляните ко мне попозже и не беспокойтесь - привезут обязательно.";
			link.l1 = "Хорошо.";
			link.l1.go = "exit";
			}
		break;
		
		case "Trade_artefact_4":
			RemoveItems(pchar, "gold_dublon", 100); // Addon-2016 Jason
			Log_Info("Вы отдали 100 дублонов");
			dialog.text = "Так, всё верно. Вот, получите ваш амулет. Пользуйтесь на здоровье!";
			link.l1 = "Спасибо, "+npchar.name+"!";
			link.l1.go = "Trade_artefact_5";
		break;
		
		case "Trade_artefact_5":
			DialogExit();
			Log_Info("Вы получили "+XI_ConvertString(npchar.quest.art));
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, npchar.quest.art, 1);
			DeleteAttribute(npchar, "quest.art");
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "2");
			CloseQuestHeader(sTemp);
		break;
		
		// --> калеуче
		case "caleuche":
			PlaySound("interface\important_item.wav");
			dialog.text = "Показывай, что там у тебя.";
			link.l1 = "Вот, похоже на старинный индейский амулет. Но только для чего он может быть нужен - ума не приложу.";
			link.l1.go = "caleuche_1";
			npchar.quest.caleuche = "true";
		break;
		
		case "caleuche_1":
			if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster)
			{
				dialog.text = "Так-так... Ты уже трет" + GetSexPhrase("ий", "ья") + ", кто показывает мне такую штуковину. Этот амулет, " + GetSexPhrase("приятель", "подруга") + ", попал сюда из дикой сельвы Южного Мэйна. Где-то там, далеко, южнее Панамы, у подножия гор, живут индейцы, которые носят похожие на этот амулеты. Сами краснокожие говорят, что это наследие их 'великих предков'\nКто их великие предки, и какое наследие они им оставили - я не ведаю. Но могу дать совет, у кого расспросить подробнее. Тебе это интересно?";
				link.l1 = "Конечно!";
				link.l1.go = "caleuche_2";
			}
			else
			{
				dialog.text = "Хм... Держал я много самых разных амулетов в своих руках, но такой на Карибах встечаю впервые. Извини, " + GetSexPhrase("дружище", "подруга") + ", ничем помочь не могу - сам не знаю, что это за диковина. Но то, что вещь не простая - факт. Спроси ещё у кого-нибудь - может, кто-то встречал подобное.";
				link.l1 = "Жаль... Буду спрашивать дальше - глядишь, повезёт.";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_2":
			dialog.text = "На Доминике есть деревня карибов вождя Мокнитекуври. У них есть шаман по имени Туттуатхапак, очень уважаемый индеец. Он не из карибов, а как раз из тех мест, про которые я тебе сказал. Он-то наверняка сможет поведать об этом амулете побольше меня. Но будь осторож" + GetSexPhrase("ен", "на") + " - Туттуатхапак очень не любит белых. Очень. Ведь они когда-то забрали его в рабство и увезли из родных мест...";
			link.l1 = "Значит, он именно таким образом и попал на Карибы?";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Да. Тут очень интересная история... Судно, на котором перевозили индейцев-рабов, попало в мёртвый штиль у острова Мария Галанте, и половина команды умерла за несколько дней от внезапной эпидемии лихорадки. Но ни один индеец-раб не заболел!\nА потом капитан рехнулся и поджёг свою лоханку. В итоге пленные индейцы в суматохе вырвались на свободу и порешили почти всех матросов. Как думаешь, кто был у них главарём?";
			link.l1 = "Догадываюсь...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "Вот-вот. Не пить мне рома до конца дней моих, если это не шаман навёл колдовскими чарами штиль на море, заразу на команду и помешательство на капитана. Этот индеец очень умён и очень опасен. Если пойдёшь к нему - веди себя вежливо и следи за тем, что говоришь - иначе быть беде. И без подношения к нему не суйся - он даже не станет с тобой разговаривать.";
			link.l1 = "А что за подношение ему нужно?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Всякой чепухой ты его не купишь. Как я слышал, он отправляет своих воинов-карибов покупать у белых огнестрельное оружие. Принеси ему в подарок мушкет - думаю, он обрадуется и уделит тебе немного своего внимания.";
			link.l1 = "Спасибо! Так и сделаю... Скажи, приятель, а откуда ты всё это знаешь?";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Мой друг был матросом на том злосчастном корабле. По счастью, ему удалось выжить в том аду кромешном... У него я и увидел в первый раз побрякушки с таким рисунком, как на твоём амулете - видать, вместе с индейцами капитан покойный прихватил ещё и их скарб. Уверен, что и твой амулет из его коллекции - когда капитан свихнулся и устроил пожар, матросы его кокнули, а потом разграбили сундуки в каюте.";
			link.l1 = "Ясно. Тогда мне остаётся только отправиться с подарком на Доминику. Спасибо за помощь и за интересный рассказ!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Удачи, " + GetSexPhrase("дружище", "подруга") + ", и будь осторож" + GetSexPhrase("ен", "на") + " с этим краснокожим дьяволом...";
			link.l1 = "...";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			AddQuestRecord("Caleuche", "2");
			pchar.questTemp.Caleuche = "dominica";
			Caleuche_CreateShamane();
		break;
		
		case "caleuche_9":
			dialog.text = "Да? Ты был" + GetSexPhrase("", "а") + " у Туттуатхапака?";
			link.l1 = "Точно. И теперь я хочу найти ещё два амулета. Ты же вроде говорил, что я трет" + GetSexPhrase("ий", "ья") + ", кто тебе такой артефакт показал. А кто были ещё двое?";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Один - это мой друг, тот самый матрос с корабля работорговцев, на котором привезли Туттуатхапака. С того случая он больше в море ни ногой. Я его давно не видел, но знаю, где он обретается. Ищи его на Западном Мэйне в Белизе - он заделался охотником и теперь шастает по джунглям. Имя - Фергус Хупер.";
			link.l1 = "Запомню. А второй?";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "Про второго я знаю немного. Его зовут то ли Джек, то ли Джексон, и он то ли капер, то ли мелкий делец, то ли просто авантюрист. У него шебека с каким-то странным именем... м-м-м... как же называлась его лоханка? Чёрт возьми, забыл! Но имечко какое-то бесовское. Я спросил его, что оно означает, и он сказал, что это полуженщина-полуптица, рожденная морскими божествами. Тьфу ты, нехристь...";
			link.l1 = "Вот умник выискался... Так названия шебеки ты не помнишь?";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "Нет, разрази меня гром, не помню. А, и ещё: когда он представлялся мне, то сказал, что он с Барбадоса.";
			link.l1 = "Уже что-то! Ладно, попробую разыскать этого любителя пернатых женщин, пока его не нашёл кое-кто другой... Спасибо, дружище, ты мне очень помог!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			dialog.text = "Не за что, " + GetSexPhrase("кэп", "красавица") + ", захаживай ещё, поболтаем.";
			link.l1 = "Загляну обязательно!";
			link.l1.go = "caleuche_14";
		break;
		
		case "caleuche_14":
			DialogExit();
			AddQuestRecord("Caleuche", "7");
			pchar.questTemp.Caleuche = "hunting";
			pchar.questTemp.Caleuche.Belizterms = rand(4)+3;
			pchar.quest.caleuche_prepare_beliz.win_condition.l1 = "location";
			pchar.quest.caleuche_prepare_beliz.win_condition.l1.location = "Beliz";
			pchar.quest.caleuche_prepare_beliz.function = "Caleuche_PrepareBeliz";
		break;*/

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_SetOwnerType(NPChar); // belamour иначе обижается навсегда
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = StringFromKey("Common_Lighthouse_42", LinkRandPhrase(
						StringFromKey("Common_Lighthouse_39", pchar),
						StringFromKey("Common_Lighthouse_40", pchar),
						StringFromKey("Common_Lighthouse_41", pchar)));
			link.l1 = StringFromKey("Common_Lighthouse_43");
			link.l1.go = "fight";
		break;
	}
}