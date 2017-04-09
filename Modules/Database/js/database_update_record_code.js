var record = (<%= record %>)
if(record.length == 0)
{
	if(typeof(LAST_DATABASE_RECORD) != "string" || LAST_DATABASE_RECORD.length == 0)
		fail("No record selected as resource")
	record = LAST_DATABASE_RECORD
}
if(typeof(record) != "string" || record.length == 0)
	fail("Record id is empty")
_db_update_record(record, <%= "[" + params + "]" %>, <%= table %>)