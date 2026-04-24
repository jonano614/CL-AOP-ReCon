
void ApplyMigration(ref migrationState)
{
	locations[FindLocation("SanAugustineResidence")].private6.items.mushket_H2 = 1;
	Trace("Migration SanAugustineResidence add Mushket H2");
}
