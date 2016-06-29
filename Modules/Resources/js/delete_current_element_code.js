if(<%= key %> in _R && _R[<%= key %>])
{
  _R[<%= key %>].die()
  _R[<%= key %>] = null
}

if(<%= sync %>)
  RSync(<%= key %>)
