
void ApplyMigration(ref migrationState)
{
	if (CheckAttribute(pchar, "questTemp.Teno") && pchar.questTemp.Teno != "begin")
	{
		RemoveMapQuestMark("Shore53", "TenochtitlanQuest");
	}

	trace("Migration Teno RemoveMapQuestMark");
}
