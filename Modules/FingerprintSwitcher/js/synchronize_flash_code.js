var use_flash = (<%= fingerprint %>).toString().indexOf("application/x-shockwave-flash") >=0
_settings({UseFlash: use_flash})!