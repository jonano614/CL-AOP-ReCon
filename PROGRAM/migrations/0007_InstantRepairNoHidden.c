
void ApplyMigration(ref migrationState)
{
	if (CheckAttribute(&ChrPerksList, "list.InstantRepair.Hidden"))
	{
		DeleteAttribute(&ChrPerksList, "list.InstantRepair.Hidden");
	}

	trace("Migration InstantRepair No Hidden");
}
