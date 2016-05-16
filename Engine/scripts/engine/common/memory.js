function memory_virtual_total()
{
    return MemoryInfo.GetTotalVirtualMemory();
}

function memory_virtual_available()
{
    return MemoryInfo.GetAvailableVirtualMemory();
}

function memory_physical_total()
{
    return MemoryInfo.GetTotalPhysicalMemory();
}

function memory_physical_available()
{
    return MemoryInfo.GetAvailablePhysicalMemory();
}
