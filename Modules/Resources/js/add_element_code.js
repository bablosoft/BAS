RInsert(<%= key %>,<%= data %>,<%= onlywrite %>)

if(<%= sync %>)
  RSync(<%= key %>)
