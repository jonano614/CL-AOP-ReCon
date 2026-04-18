
void ApplyMigration(ref migrationState)
{
	locations[FindLocation("SanAugustineResidence")].private6.items.recipe_fulminate_silver = 1;
	trace("Migration SanAugustineResidence add fulminate_silver");
}
