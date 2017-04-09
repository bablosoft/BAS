var group = (<%= group %>)
if(group.length == 0)
	group = P("_bas_table_" + (<%= table %>), "_last_group")
<%= variable %> = _db_add_record(group, <%= "[" + params + "]" %>, <%= table %>)