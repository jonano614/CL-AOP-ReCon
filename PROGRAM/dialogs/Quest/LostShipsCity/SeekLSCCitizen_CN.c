void ProcessDialog_SeekLSCCitizenCN(ref NPChar, aref Link, aref NextDiag)
{
	string sTemp, sAttr;
	int i, j;

	sAttr = Dialog.CurrentNode;
	if (HasStr(sAttr, "SeekLSCCitizenCN_"))
	{
		j = findsubstr(sAttr, "_", 0);
		dialogEditStrings[3] = strcut(sAttr, j + 1, strlen(sAttr) - 1);
		Dialog.CurrentNode = "SeekCitizen_Choice_1";
	}
}