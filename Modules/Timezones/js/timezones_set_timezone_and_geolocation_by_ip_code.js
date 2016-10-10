IP_INFO = JSON.parse(native("timezones", "ipinfo", <%= value %>));
if(!IP_INFO["valid"])
	fail("Failed to get ip info for " + <%= value %>);

IP_OFFSET = null
{
	var month = new Date().getMonth()
	if(month >= 4 && month <= 9)
		IP_OFFSET = IP_INFO["dstoffset"]
	else
		IP_OFFSET = IP_INFO["offset"]
}
timezone(IP_OFFSET)!
geolocation(IP_INFO["latitude"],IP_INFO["longitude"])!