
void ApplyMigration(ref migrationState)
{
	if(LoadSegment("store\initStore.c"))
	{
		InitStores();
		UnloadSegment("store\initStore.c");
	}

	trace("Migration FoodNoContraband fix");
}
