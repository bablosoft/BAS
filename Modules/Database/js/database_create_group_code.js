<%= group %> = _db_add_group(<%= name %>, <%= description %>, <%= table %>)
PSet("_bas_table_" + (<%= table %>), "_last_group", <%= group %>)