
void ApplyMigration(ref migrationState)
{
	pchar.quest.RepairMonsterGroup.win_condition.l1	= "ExitFromLocation";
	pchar.quest.RepairMonsterGroup.win_condition.l1.location = pchar.location;
	pchar.quest.RepairMonsterGroup.function	= "RepairMonsterGroup";

	trace("Migration RepairMonsterGroup Done");
}
