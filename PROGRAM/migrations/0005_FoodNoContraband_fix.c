
void ApplyMigration(ref migrationState)
{
	Stores[PortSpein_STORE].Trade.Contraband.id4 = GOOD_SUGAR;

	Stores[Charles_STORE].Trade.Import.id5 = GOOD_FOOD;
	Stores[Charles_STORE].Trade.Contraband.id2 = GOOD_FRUITS;

	Stores[Maracaibo_STORE].Trade.Import.id5 = GOOD_POWDER;
	Stores[Maracaibo_STORE].Trade.Contraband.id3 = GOOD_FRUITS;
	Stores[Maracaibo_STORE].Trade.Contraband.id4 = GOOD_COTTON;

	trace("Migration FoodNoContraband fix");
}
