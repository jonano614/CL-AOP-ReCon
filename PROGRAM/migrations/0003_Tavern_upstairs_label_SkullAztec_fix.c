
void ApplyMigration(ref migrationState)
{
	locations[FindLocation("Charles_tavern_upstairs")].id.label = "Tavern upstairs";
	locations[FindLocation("Marigo_tavern_upstairs")].id.label = "Tavern upstairs";
	locations[FindLocation("Panama_tavern_upstairs")].id.label = "Tavern upstairs";

	ref rItem = ItemsFromID("SkullAztec");
	DeleteAttributeEx(rItem, "useLocation,useLocator");

	if (or(savefile_info == "CL: AoP 1.0.0 (13.03.2026)", savefile_info == "CL: AoP 1.0.1 (16.03.2026)") && pchar.questTemp.Teno == "YouWinGod")
		pchar.items.SkullAztec = 1;

	rItem = ItemsFromID("Ascold_rabble"); // > на всякий случай
	rItem.useLocation = "Guadeloupe_Cave";
	rItem.useLocator = "button02";

	trace("Migration Tavern upstairs label and SkullAztec fix");
}
