
void ApplyMigration(ref migrationState)
{
	int index = GetCharacterIndex("Ment_6");
	if (index != -1)
	{
	    ref chr = GetCharacter(index);
		if (!LAi_IsDead(chr))
		{
			for (int i = 0; i < GetPassengersQuantity(pchar); i++)
			{
				index = GetPassenger(pchar, i);
				if (index > 1 && Characters[index].id == chr.id) {
					LAi_SetRolyPoly(chr, true);
					break;
				}
			}
		}
	}

	trace("Migration IndestructibleWorkman Done");
}
