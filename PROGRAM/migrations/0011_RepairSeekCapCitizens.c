
void ApplyMigration(ref migrationState)
{
	ref chr;
	int numQ;

	for (int i = GlobalCharacters; i < MAX_CHARACTERS; i++)
	{
		makeref(chr, characters[i]);

		if (StrStartsWith(chr.id, "QuestCitiz_") && CheckAttribute(chr, "quest.SeekCap.numQuest"))
		{
			numQ = sti(chr.quest.SeekCap.numQuest);
			if (numQ < 0 || numQ > 2)
			{
			    chr.quest.SeekCap.numQuest = rand(2);
			}
		}
	}

	trace("Migration Repair SeekCapCitizens Done");
}
