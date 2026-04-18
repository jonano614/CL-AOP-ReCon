
void ApplyMigration(ref migrationState)
{
	//TODO чекнуть какое условие не предусмотрели, люди жалуются
	/*if (CheckAttribute(pchar, "GenQuest.Noblelombard.City"))
	{
		ref rChar = CharacterFromId(pchar.GenQuest.Noblelombard.id);

		if (TestRef(rChar) && GetCharacterIndex(rChar.city + "_usurer") < 0)
		{
			pchar.quest.Noblelombard_Over.over = "yes";		
			RemoveLandQuestMark_Gen(rChar, "Noblelombard");
			AddQuestRecord("Noblelombard", "4");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			rChar.lifeday = 0;
			ChangeCharacterAddress(rChar, "none", "");
			DeleteAttributeEx(pchar, "GenQuest.Noblelombard,quest.noblelombard");
		}
	}*/

	// > options fix
	// > game folder
	string sProfile, sTemp = "options";
	object oBaseOptions, oProfileOptions;

	ReadSavedOptionsByFile(&oBaseOptions, sTemp);

	DeleteAttributeMass(&oBaseOptions, "controls.primaryland", "ChrForward2,SwitchCameraOffset");
	DeleteAttributeMass(&oBaseOptions, "controls.fightmodecontrols", "SwitchCameraOffset,ChrAttackFient1,ChrParry1");

	SaveSavedOptionsByFile(&oBaseOptions, sTemp);
	DeleteClass(&oBaseOptions);

	// > profile folder
	if (CheckAttribute(&PlayerProfile, "name") && PlayerProfile.name != "")
		sProfile = PlayerProfile.name;

	object oProfiles;
	XI_FindFoldersWithoutNetsave("SAVE" + "\*", &oProfiles);

	int n = GetAttributesNum(&oProfiles);

	if (n > 0)
		sProfile = GetAttributeValue(GetAttributeN(&oProfiles, n - 1));

	if (sProfile != "")
	{
		sTemp = "SAVE\\" + sProfile + "\options\options";
		ReadSavedOptionsByFile(&oProfileOptions, sTemp);

		DeleteAttributeMass(&oProfileOptions, "controls.primaryland", "ChrForward2,SwitchCameraOffset");
		DeleteAttributeMass(&oProfileOptions, "controls.fightmodecontrols", "SwitchCameraOffset,ChrAttackFient1,ChrParry1");

		SaveSavedOptionsByFile(&oProfileOptions, sTemp);
	}
	DeleteClass(&oProfileOptions);
	// < options fix

	trace("Migration NobleLombard and options file fix");
}
