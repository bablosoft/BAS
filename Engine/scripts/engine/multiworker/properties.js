function P(group, key)
{
    return Properties.Get(group, key);
}

function PSet(group, key, value)
{
    Properties.Set(group, key, value);
}

function PClear(group, key)
{
    if(!key && !group)
    {
        Properties.Clear("", "");
        return;
    }

    if(!key)
    {
        Properties.Clear(group, "");
        return;
    }

    Properties.Clear(group, key);
}
