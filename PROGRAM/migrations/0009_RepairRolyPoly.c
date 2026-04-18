
void ApplyMigration(ref migrationState)
{
	int index;
	ref chr;
	for (int i = 0; i < GetPassengersQuantity(pchar); i++)
	{
		index = GetPassenger(pchar, i);
		if (index > 1)
		{
		    chr = GetCharacter(index);
			if (chr.chr_ai.type != LAI_TYPE_INJURE)
				StableRolyPoly(chr);
		}
	}

	trace("Migration RepairRolyPoly Done");
}
