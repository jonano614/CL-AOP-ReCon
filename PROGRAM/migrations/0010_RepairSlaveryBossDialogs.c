
void ApplyMigration(ref migrationState)
{
	ref chr;
	for (int i = 0; i < MAX_CHARACTERS; i++)
	{
		makeref(chr, characters[i]);
		if (CheckAttribute(chr, "dialog.currentnode") && or(chr.dialog.currentnode == "CaptainComission_18", chr.dialog.currentnode == "CaptainComission_19"))
		{
			chr.dialog.currentnode = "First time";
			chr.dialog.TempNode = "First time";
		}
	}

	trace("Migration RepairSlaveryBossDialogs Done");
}
