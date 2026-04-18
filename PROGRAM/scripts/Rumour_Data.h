#define SIMPLE_RUMOUR_NUM	12
#define CITIZEN_RUMOUR_NUM	10

string DefaultText(int index)
{
    string DEFAULT_TEXT[31];
    //Советы по осадам (siege_group)
    DEFAULT_TEXT[0] = StringFromKey("Rumour_Data_1");
    DEFAULT_TEXT[1] = StringFromKey("Rumour_Data_2");
    //Слухи по шебеке (xebek_group)
    DEFAULT_TEXT[2] = StringFromKey("Rumour_Data_3");
    DEFAULT_TEXT[3] = StringFromKey("Rumour_Data_4");
    DEFAULT_TEXT[4] = StringFromKey("Rumour_Data_5");
    DEFAULT_TEXT[5] = StringFromKey("Rumour_Data_6");
    DEFAULT_TEXT[6] = StringFromKey("Rumour_Data_7");
    DEFAULT_TEXT[7] = StringFromKey("Rumour_Data_8");
    //Слухи по Шарпу (sharp_group)
    DEFAULT_TEXT[8] = StringFromKey("Rumour_Data_9");
    DEFAULT_TEXT[9] = StringFromKey("Rumour_Data_10");
    DEFAULT_TEXT[10] = StringFromKey("Rumour_Data_11");
    //Слухи по ацтекам (aztec_group)
    DEFAULT_TEXT[11] = StringFromKey("Rumour_Data_12");
    DEFAULT_TEXT[12] = StringFromKey("Rumour_Data_13");
    //Слухи по ГПК
    DEFAULT_TEXT[13] = StringFromKey("Rumour_Data_14");
    //Общие советы
    DEFAULT_TEXT[14] = StringFromKey("Rumour_Data_15");
    DEFAULT_TEXT[15] = StringFromKey("Rumour_Data_16");
    DEFAULT_TEXT[16] = StringFromKey("Rumour_Data_17");
    DEFAULT_TEXT[17] = StringFromKey("Rumour_Data_18");
    DEFAULT_TEXT[18] = StringFromKey("Rumour_Data_19");
    DEFAULT_TEXT[19] = StringFromKey("Rumour_Data_20");
    DEFAULT_TEXT[20] = StringFromKey("Rumour_Data_21");
    DEFAULT_TEXT[21] = StringFromKey("Rumour_Data_22");
    DEFAULT_TEXT[22] = StringFromKey("Rumour_Data_23");
    DEFAULT_TEXT[23] = StringFromKey("Rumour_Data_24");
    DEFAULT_TEXT[24] = StringFromKey("Rumour_Data_25");
    DEFAULT_TEXT[25] = StringFromKey("Rumour_Data_26");
    DEFAULT_TEXT[26] = StringFromKey("Rumour_Data_27");
    DEFAULT_TEXT[27] = StringFromKey("Rumour_Data_28");
    DEFAULT_TEXT[28] = StringFromKey("Rumour_Data_29");
    DEFAULT_TEXT[29] = StringFromKey("Rumour_Data_30");
    DEFAULT_TEXT[30] = StringFromKey("Rumour_Data_31");
    return DEFAULT_TEXT[index];
}

/// Слухи нищих
string PoorRumourText(int index)
{
    string POOR_RUMOUR_TEXT[10];
    POOR_RUMOUR_TEXT[0] = StringFromKey("Rumour_Data_32");
    POOR_RUMOUR_TEXT[1] = StringFromKey("Rumour_Data_33");
    POOR_RUMOUR_TEXT[2] = StringFromKey("Rumour_Data_34");
    POOR_RUMOUR_TEXT[3] = StringFromKey("Rumour_Data_35");
    POOR_RUMOUR_TEXT[4] = StringFromKey("Rumour_Data_36");
    POOR_RUMOUR_TEXT[5] = StringFromKey("Rumour_Data_37");
    POOR_RUMOUR_TEXT[6] = StringFromKey("Rumour_Data_38");
    POOR_RUMOUR_TEXT[7] = StringFromKey("Rumour_Data_39");
    POOR_RUMOUR_TEXT[8] = StringFromKey("Rumour_Data_40");
    POOR_RUMOUR_TEXT[9] = StringFromKey("Rumour_Data_41");
    return POOR_RUMOUR_TEXT[index];
}

/// Сплетни при отсутствии актуальных слухов (простолюдинов, корчмарей, маргиналов, ...)
string NoRumourText(int index)
{
    string NO_RUMOUR_TEXT[SIMPLE_RUMOUR_NUM];
    NO_RUMOUR_TEXT[0] = StringFromKey("Rumour_Data_42");
    NO_RUMOUR_TEXT[1] = StringFromKey("Rumour_Data_43");
    NO_RUMOUR_TEXT[2] = StringFromKey("Rumour_Data_44");
    NO_RUMOUR_TEXT[3] = StringFromKey("Rumour_Data_45");
    NO_RUMOUR_TEXT[4] = StringFromKey("Rumour_Data_46");
    NO_RUMOUR_TEXT[5] = StringFromKey("Rumour_Data_47");
    NO_RUMOUR_TEXT[6] = StringFromKey("Rumour_Data_48");
    NO_RUMOUR_TEXT[7] = StringFromKey("Rumour_Data_49");
    NO_RUMOUR_TEXT[8] = StringFromKey("Rumour_Data_50");
    NO_RUMOUR_TEXT[9] = StringFromKey("Rumour_Data_51");
    NO_RUMOUR_TEXT[10] = StringFromKey("Rumour_Data_52");
    NO_RUMOUR_TEXT[11] = StringFromKey("Rumour_Data_53");
    return NO_RUMOUR_TEXT[index];
}

/// Сплетни капитанов (при отсутствии актуальных слухов)
string CaptainRumourText(int index)
{
    string CAPTAIN_RUMOUR_TEXT[CITIZEN_RUMOUR_NUM];
    CAPTAIN_RUMOUR_TEXT[0] = StringFromKey("Rumour_Data_54");
    CAPTAIN_RUMOUR_TEXT[1] = StringFromKey("Rumour_Data_55");
    CAPTAIN_RUMOUR_TEXT[2] = StringFromKey("Rumour_Data_56");
    CAPTAIN_RUMOUR_TEXT[3] = StringFromKey("Rumour_Data_57");
    CAPTAIN_RUMOUR_TEXT[4] = StringFromKey("Rumour_Data_58");
    CAPTAIN_RUMOUR_TEXT[5] = StringFromKey("Rumour_Data_59");
    CAPTAIN_RUMOUR_TEXT[6] = StringFromKey("Rumour_Data_60");
    CAPTAIN_RUMOUR_TEXT[7] = StringFromKey("Rumour_Data_61");
    CAPTAIN_RUMOUR_TEXT[8] = StringFromKey("Rumour_Data_62");
    CAPTAIN_RUMOUR_TEXT[9] = StringFromKey("Rumour_Data_63");
    return CAPTAIN_RUMOUR_TEXT[index];
}

/// Сплетни мещан мужские (при отсутствии актуальных слухов)
string CitizenManRumourText(int index)
{
    string CITIZEN_MAN_RUMOUR_TEXT[CITIZEN_RUMOUR_NUM];
    CITIZEN_MAN_RUMOUR_TEXT[0] = StringFromKey("Rumour_Data_64");
    CITIZEN_MAN_RUMOUR_TEXT[1] = StringFromKey("Rumour_Data_65");
    CITIZEN_MAN_RUMOUR_TEXT[2] = StringFromKey("Rumour_Data_66");
    CITIZEN_MAN_RUMOUR_TEXT[3] = StringFromKey("Rumour_Data_67");
    CITIZEN_MAN_RUMOUR_TEXT[4] = StringFromKey("Rumour_Data_68");
    CITIZEN_MAN_RUMOUR_TEXT[5] = StringFromKey("Rumour_Data_69");
    CITIZEN_MAN_RUMOUR_TEXT[6] = StringFromKey("Rumour_Data_70");
    CITIZEN_MAN_RUMOUR_TEXT[7] = StringFromKey("Rumour_Data_71");
    CITIZEN_MAN_RUMOUR_TEXT[8] = StringFromKey("Rumour_Data_72");
    CITIZEN_MAN_RUMOUR_TEXT[9] = StringFromKey("Rumour_Data_73");
    return CITIZEN_MAN_RUMOUR_TEXT[index];
}

/// TODO: Сплетни мещан женские (при отсутствии актуальных слухов)
string CitizenWomanRumourText(int index)
{
    string CITIZEN_WOMAN_RUMOUR_TEXT[CITIZEN_RUMOUR_NUM];
    CITIZEN_WOMAN_RUMOUR_TEXT[0] = StringFromKey("Rumour_Data_74");
    CITIZEN_WOMAN_RUMOUR_TEXT[1] = StringFromKey("Rumour_Data_75");
    CITIZEN_WOMAN_RUMOUR_TEXT[2] = StringFromKey("Rumour_Data_76");
    CITIZEN_WOMAN_RUMOUR_TEXT[3] = StringFromKey("Rumour_Data_77");
    CITIZEN_WOMAN_RUMOUR_TEXT[4] = "------------";
    CITIZEN_WOMAN_RUMOUR_TEXT[5] = "------------";
    CITIZEN_WOMAN_RUMOUR_TEXT[6] = "------------";
    CITIZEN_WOMAN_RUMOUR_TEXT[7] = StringFromKey("Rumour_Data_78");
    CITIZEN_WOMAN_RUMOUR_TEXT[8] = StringFromKey("Rumour_Data_79");
    CITIZEN_WOMAN_RUMOUR_TEXT[9] = "------------";
    return CITIZEN_WOMAN_RUMOUR_TEXT[index];
}

/// Сплетни дворян (при отсутствии актуальных слухов)
string NobleManRumourText(int index)
{
    string NOBLE_MAN_RUMOUR_TEXT[CITIZEN_RUMOUR_NUM];
    NOBLE_MAN_RUMOUR_TEXT[0] = StringFromKey("Rumour_Data_80");
    NOBLE_MAN_RUMOUR_TEXT[1] = StringFromKey("Rumour_Data_81");
    NOBLE_MAN_RUMOUR_TEXT[2] = StringFromKey("Rumour_Data_82");
    NOBLE_MAN_RUMOUR_TEXT[3] = StringFromKey("Rumour_Data_83");
    NOBLE_MAN_RUMOUR_TEXT[4] = StringFromKey("Rumour_Data_84");
    NOBLE_MAN_RUMOUR_TEXT[5] = StringFromKey("Rumour_Data_85");
    NOBLE_MAN_RUMOUR_TEXT[6] = StringFromKey("Rumour_Data_86");
    NOBLE_MAN_RUMOUR_TEXT[7] = StringFromKey("Rumour_Data_87");
    NOBLE_MAN_RUMOUR_TEXT[8] = StringFromKey("Rumour_Data_88");
    NOBLE_MAN_RUMOUR_TEXT[9] = StringFromKey("Rumour_Data_89");
    return NOBLE_MAN_RUMOUR_TEXT[index];
}

/// TODO: Сплетни дворянок (при отсутствии актуальных слухов)
string NobleWomanRumourText(int index)
{
    string NOBLE_WOMAN_RUMOUR_TEXT[CITIZEN_RUMOUR_NUM];
    NOBLE_WOMAN_RUMOUR_TEXT[0] = StringFromKey("Rumour_Data_90");
    NOBLE_WOMAN_RUMOUR_TEXT[1] = StringFromKey("Rumour_Data_91");
    NOBLE_WOMAN_RUMOUR_TEXT[2] = StringFromKey("Rumour_Data_92");
    NOBLE_WOMAN_RUMOUR_TEXT[3] = StringFromKey("Rumour_Data_93");
    NOBLE_WOMAN_RUMOUR_TEXT[4] = "------------";
    NOBLE_WOMAN_RUMOUR_TEXT[5] = "------------";
    NOBLE_WOMAN_RUMOUR_TEXT[6] = "------------";
    NOBLE_WOMAN_RUMOUR_TEXT[7] = StringFromKey("Rumour_Data_94");
    NOBLE_WOMAN_RUMOUR_TEXT[8] = StringFromKey("Rumour_Data_95");
    NOBLE_WOMAN_RUMOUR_TEXT[9] = "------------";
    return NOBLE_WOMAN_RUMOUR_TEXT[index];
}

/// Сплетни матросов (при отсутствии актуальных слухов)
string SailorRumourText(int index)
{
    string SAILOR_RUMOUR_TEXT[CITIZEN_RUMOUR_NUM];
    SAILOR_RUMOUR_TEXT[0] = StringFromKey("Rumour_Data_96");
    SAILOR_RUMOUR_TEXT[1] = StringFromKey("Rumour_Data_97");
    SAILOR_RUMOUR_TEXT[2] = StringFromKey("Rumour_Data_98");
    SAILOR_RUMOUR_TEXT[3] = StringFromKey("Rumour_Data_99");
    SAILOR_RUMOUR_TEXT[4] = StringFromKey("Rumour_Data_100");
    SAILOR_RUMOUR_TEXT[5] = StringFromKey("Rumour_Data_101");
    SAILOR_RUMOUR_TEXT[6] = StringFromKey("Rumour_Data_102");
    SAILOR_RUMOUR_TEXT[7] = StringFromKey("Rumour_Data_103");
    SAILOR_RUMOUR_TEXT[8] = StringFromKey("Rumour_Data_104");
    SAILOR_RUMOUR_TEXT[9] = StringFromKey("Rumour_Data_105");
    return SAILOR_RUMOUR_TEXT[index];
}

/// Если новостей нет в ГПК
string NoRumourTextLSC(int index)
{
    string NO_RUMOUR_LSC_TEXT[5];
    NO_RUMOUR_LSC_TEXT[0] = StringFromKey("Rumour_Data_106");
    NO_RUMOUR_LSC_TEXT[1] = StringFromKey("Rumour_Data_107");
    NO_RUMOUR_LSC_TEXT[2] = StringFromKey("Rumour_Data_108");
    NO_RUMOUR_LSC_TEXT[3] = StringFromKey("Rumour_Data_109");
    NO_RUMOUR_LSC_TEXT[4] = StringFromKey("Rumour_Data_110");
    return NO_RUMOUR_LSC_TEXT[index];
}
