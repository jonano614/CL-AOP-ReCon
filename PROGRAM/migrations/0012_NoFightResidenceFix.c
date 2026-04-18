
void ApplyMigration(ref migrationState)
{
	ref loc;
	int numQ;

	for(int i = 0; i < MAX_LOCATIONS; i++)
	{
		makeref(loc, Locations[i]);
		if (CheckAttribute(loc, "type") && loc.type == "residence")
		{
			if (pchar.location == loc.id) continue;
			DeleteAttribute(loc, "noFight");
		}
	}

	trace("Migration NoFightResidence Fix Done");
}
