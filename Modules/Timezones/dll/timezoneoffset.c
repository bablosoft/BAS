#include <string.h>
int GeoIP_time_zone_offset_by_country_and_region(const char * country,const char * region) {
    int timezone = 99999;
    if (country == NULL) {
      return 99999;
    }
    if (region == NULL) {
        region = "";
    }
    if ( strcmp (country, "AD") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "AE") == 0 ) {
        return -240;
    }
    if ( strcmp (country, "AF") == 0 ) {
        return -270;
    }
    if ( strcmp (country, "AG") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "AI") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "AL") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "AM") == 0 ) {
        return -240;
    }
    if ( strcmp (country, "AN") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "AO") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "AQ") == 0 ) {
        return -720;
    }
    if ( strcmp (country, "AR") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "18") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "19") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "21") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "22") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "23") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "24") == 0 ) {
            return 180;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "AS") == 0 ) {
        return 660;
    }
    if ( strcmp (country, "AT") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "AU") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return -600;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return -600;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -570;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return -600;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -570;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -600;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -600;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -480;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "AW") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "AX") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "AZ") == 0 ) {
        return -240;
    }
    if ( strcmp (country, "BA") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "BB") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "BD") == 0 ) {
        return -360;
    }
    if ( strcmp (country, "BE") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "BF") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "BG") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "BH") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "BI") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "BJ") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "BL") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "BM") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "BN") == 0 ) {
        return -480;
    }
    if ( strcmp (country, "BO") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "BQ") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "BR") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "18") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "21") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "22") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "23") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "24") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "25") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "26") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "27") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "28") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "29") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "30") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "31") == 0 ) {
            return 180;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "BS") == 0 ) {
        return 300;
    }
    if ( strcmp (country, "BT") == 0 ) {
        return -360;
    }
    if ( strcmp (country, "BV") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "BW") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "BY") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "BZ") == 0 ) {
        return 360;
    }
    if ( strcmp (country, "CA") == 0 ) {
        if ( strcmp (region, "AB") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "BC") == 0 ) {
            return 480;
        }
        else if ( strcmp (region, "MB") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "NB") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "NL") == 0 ) {
            return 210;
        }
        else if ( strcmp (region, "NS") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "NT") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "NU") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "ON") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "PE") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "QC") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "SK") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "YT") == 0 ) {
            return 480;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "CC") == 0 ) {
        return -390;
    }
    if ( strcmp (country, "CD") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return -120;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "CF") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "CG") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "CH") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "CI") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "CK") == 0 ) {
        return 600;
    }
    if ( strcmp (country, "CL") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "CM") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "CN") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "18") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "19") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "21") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "22") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "23") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "24") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "25") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "26") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "28") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "29") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "30") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "31") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "32") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "33") == 0 ) {
            return -480;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "CO") == 0 ) {
        return 300;
    }
    if ( strcmp (country, "CR") == 0 ) {
        return 360;
    }
    if ( strcmp (country, "CU") == 0 ) {
        return 300;
    }
    if ( strcmp (country, "CV") == 0 ) {
        return 60;
    }
    if ( strcmp (country, "CW") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "CX") == 0 ) {
        return -420;
    }
    if ( strcmp (country, "CY") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "CZ") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "DE") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "DJ") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "DK") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "DM") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "DO") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "DZ") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "EC") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "18") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "19") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "22") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "24") == 0 ) {
            return 300;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "EE") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "EG") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "EH") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "ER") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "ES") == 0 ) {
        if ( strcmp (region, "07") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "27") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "29") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "31") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "32") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "34") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "39") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "51") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "52") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "53") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "54") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "55") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "56") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "57") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "58") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "59") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "60") == 0 ) {
            return -60;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "ET") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "FI") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "FJ") == 0 ) {
        return -720;
    }
    if ( strcmp (country, "FK") == 0 ) {
        return 180;
    }
    if ( strcmp (country, "FM") == 0 ) {
        return -660;
    }
    if ( strcmp (country, "FO") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "FR") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "FX") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "GA") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "GB") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "GD") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "GE") == 0 ) {
        return -240;
    }
    if ( strcmp (country, "GF") == 0 ) {
        return 180;
    }
    if ( strcmp (country, "GG") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "GH") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "GI") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "GL") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return 180;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "GM") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "GN") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "GP") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "GQ") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "GR") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "GS") == 0 ) {
        return 120;
    }
    if ( strcmp (country, "GT") == 0 ) {
        return 360;
    }
    if ( strcmp (country, "GU") == 0 ) {
        return -600;
    }
    if ( strcmp (country, "GW") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "GY") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "HK") == 0 ) {
        return -480;
    }
    if ( strcmp (country, "HN") == 0 ) {
        return 360;
    }
    if ( strcmp (country, "HR") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "HT") == 0 ) {
        return 300;
    }
    if ( strcmp (country, "HU") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "ID") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return -540;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "18") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "19") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "21") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "22") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "23") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "24") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "25") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "26") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "28") == 0 ) {
            return -540;
        }
        else if ( strcmp (region, "29") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "30") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "31") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "32") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "33") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "34") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "35") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "36") == 0 ) {
            return -540;
        }
        else if ( strcmp (region, "37") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "38") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "39") == 0 ) {
            return -540;
        }
        else if ( strcmp (region, "40") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "41") == 0 ) {
            return -480;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "IE") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "IL") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "IM") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "IN") == 0 ) {
        return -330;
    }
    if ( strcmp (country, "IO") == 0 ) {
        return -360;
    }
    if ( strcmp (country, "IQ") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "IR") == 0 ) {
        return -210;
    }
    if ( strcmp (country, "IS") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "IT") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "JE") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "JM") == 0 ) {
        return 300;
    }
    if ( strcmp (country, "JO") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "JP") == 0 ) {
        return -540;
    }
    if ( strcmp (country, "KE") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "KG") == 0 ) {
        return -360;
    }
    if ( strcmp (country, "KH") == 0 ) {
        return -420;
    }
    if ( strcmp (country, "KI") == 0 ) {
        return -720;
    }
    if ( strcmp (country, "KM") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "KN") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "KP") == 0 ) {
        return -510;
    }
    if ( strcmp (country, "KR") == 0 ) {
        return -540;
    }
    if ( strcmp (country, "KW") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "KY") == 0 ) {
        return 300;
    }
    if ( strcmp (country, "KZ") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return -360;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "LA") == 0 ) {
        return -420;
    }
    if ( strcmp (country, "LB") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "LC") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "LI") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "LK") == 0 ) {
        return -330;
    }
    if ( strcmp (country, "LR") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "LS") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "LT") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "LU") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "LV") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "LY") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "MA") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "MC") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "MD") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "ME") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "MF") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "MG") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "MH") == 0 ) {
        return -720;
    }
    if ( strcmp (country, "MK") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "ML") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "MM") == 0 ) {
        return -390;
    }
    if ( strcmp (country, "MN") == 0 ) {
        if ( strcmp (region, "06") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "19") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "21") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "25") == 0 ) {
            return -480;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "MO") == 0 ) {
        return -480;
    }
    if ( strcmp (country, "MP") == 0 ) {
        return -600;
    }
    if ( strcmp (country, "MQ") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "MR") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "MS") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "MT") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "MU") == 0 ) {
        return -240;
    }
    if ( strcmp (country, "MV") == 0 ) {
        return -300;
    }
    if ( strcmp (country, "MW") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "MX") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return 480;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "18") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "19") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "21") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "22") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "23") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "24") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "25") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "26") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "27") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "28") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "29") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "30") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "31") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "32") == 0 ) {
            return 360;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "MY") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return -480;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "MZ") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "NA") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "NC") == 0 ) {
        return -660;
    }
    if ( strcmp (country, "NE") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "NF") == 0 ) {
        return -660;
    }
    if ( strcmp (country, "NG") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "NI") == 0 ) {
        return 360;
    }
    if ( strcmp (country, "NL") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "NO") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "NP") == 0 ) {
        return -345;
    }
    if ( strcmp (country, "NR") == 0 ) {
        return -720;
    }
    if ( strcmp (country, "NU") == 0 ) {
        return 660;
    }
    if ( strcmp (country, "NZ") == 0 ) {
        if ( strcmp (region, "85") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "E7") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "E8") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "E9") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "F1") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "F2") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "F3") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "F4") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "F5") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "F6") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "F7") == 0 ) {
            return -765;
        }
        else if ( strcmp (region, "F8") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "F9") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "G1") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "G2") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "G3") == 0 ) {
            return -720;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "OM") == 0 ) {
        return -240;
    }
    if ( strcmp (country, "PA") == 0 ) {
        return 300;
    }
    if ( strcmp (country, "PE") == 0 ) {
        return 300;
    }
    if ( strcmp (country, "PF") == 0 ) {
        return 570;
    }
    if ( strcmp (country, "PG") == 0 ) {
        return -600;
    }
    if ( strcmp (country, "PH") == 0 ) {
        return -480;
    }
    if ( strcmp (country, "PK") == 0 ) {
        return -300;
    }
    if ( strcmp (country, "PL") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "PM") == 0 ) {
        return 180;
    }
    if ( strcmp (country, "PN") == 0 ) {
        return 480;
    }
    if ( strcmp (country, "PR") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "PS") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "PT") == 0 ) {
        if ( strcmp (region, "02") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "18") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "19") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "21") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "22") == 0 ) {
            return 0;
        }
        else if ( strcmp (region, "23") == 0 ) {
            return 60;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "PW") == 0 ) {
        return -540;
    }
    if ( strcmp (country, "PY") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "QA") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "RE") == 0 ) {
        return -240;
    }
    if ( strcmp (country, "RO") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "RS") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "RU") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -600;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "18") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "21") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "22") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "23") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "24") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "25") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "26") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "27") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "28") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "29") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "30") == 0 ) {
            return -600;
        }
        else if ( strcmp (region, "31") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "32") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "33") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "34") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "35") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "36") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "37") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "38") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "39") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "40") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "41") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "42") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "43") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "44") == 0 ) {
            return -660;
        }
        else if ( strcmp (region, "45") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "46") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "47") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "48") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "49") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "50") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "51") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "52") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "53") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "54") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "55") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "56") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "57") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "58") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "59") == 0 ) {
            return -600;
        }
        else if ( strcmp (region, "60") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "61") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "62") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "63") == 0 ) {
            return -540;
        }
        else if ( strcmp (region, "64") == 0 ) {
            return -660;
        }
        else if ( strcmp (region, "65") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "66") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "67") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "68") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "69") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "70") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "71") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "72") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "73") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "74") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "75") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "76") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "77") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "78") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "79") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "80") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "81") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "82") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "83") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "84") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "85") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "86") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "87") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "88") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "89") == 0 ) {
            return -600;
        }
        else if ( strcmp (region, "90") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "91") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "92") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "93") == 0 ) {
            return -480;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "RW") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "SA") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "SB") == 0 ) {
        return -660;
    }
    if ( strcmp (country, "SC") == 0 ) {
        return -240;
    }
    if ( strcmp (country, "SD") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "SE") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "SG") == 0 ) {
        return -480;
    }
    if ( strcmp (country, "SH") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "SI") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "SJ") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "SK") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "SL") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "SM") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "SN") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "SO") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "SR") == 0 ) {
        return 180;
    }
    if ( strcmp (country, "SS") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "ST") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "SV") == 0 ) {
        return 360;
    }
    if ( strcmp (country, "SX") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "SY") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "SZ") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "TC") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "TD") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "TF") == 0 ) {
        return -300;
    }
    if ( strcmp (country, "TG") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "TH") == 0 ) {
        return -420;
    }
    if ( strcmp (country, "TJ") == 0 ) {
        return -300;
    }
    if ( strcmp (country, "TK") == 0 ) {
        return -780;
    }
    if ( strcmp (country, "TL") == 0 ) {
        return -540;
    }
    if ( strcmp (country, "TM") == 0 ) {
        return -300;
    }
    if ( strcmp (country, "TN") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "TO") == 0 ) {
        return -780;
    }
    if ( strcmp (country, "TR") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "TT") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "TV") == 0 ) {
        return -720;
    }
    if ( strcmp (country, "TW") == 0 ) {
        return -480;
    }
    if ( strcmp (country, "TZ") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "UA") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "18") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "19") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "21") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "22") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "23") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "24") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "25") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "26") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "27") == 0 ) {
            return -120;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "UG") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "UM") == 0 ) {
        return -720;
    }
    if ( strcmp (country, "US") == 0 ) {
        if ( strcmp (region, "AK") == 0 ) {
            return 540;
        }
        else if ( strcmp (region, "AL") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "AR") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "AZ") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "CA") == 0 ) {
            return 480;
        }
        else if ( strcmp (region, "CO") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "CT") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "DC") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "DE") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "FL") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "GA") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "HI") == 0 ) {
            return 600;
        }
        else if ( strcmp (region, "IA") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "ID") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "IL") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "IN") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "KS") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "KY") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "LA") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "MA") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "MD") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "ME") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "MI") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "MN") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "MO") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "MS") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "MT") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "NC") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "ND") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "NE") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "NH") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "NJ") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "NM") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "NV") == 0 ) {
            return 480;
        }
        else if ( strcmp (region, "NY") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "OH") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "OK") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "OR") == 0 ) {
            return 480;
        }
        else if ( strcmp (region, "PA") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "RI") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "SC") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "SD") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "TN") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "TX") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "UT") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "VA") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "VT") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "WA") == 0 ) {
            return 480;
        }
        else if ( strcmp (region, "WI") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "WV") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "WY") == 0 ) {
            return 420;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "UY") == 0 ) {
        return 180;
    }
    if ( strcmp (country, "UZ") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return -300;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "VA") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "VC") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "VE") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "VG") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "VI") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "VN") == 0 ) {
        return -420;
    }
    if ( strcmp (country, "VU") == 0 ) {
        return -660;
    }
    if ( strcmp (country, "WF") == 0 ) {
        return -720;
    }
    if ( strcmp (country, "WS") == 0 ) {
        return 660;
    }
    if ( strcmp (country, "YE") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "YT") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "YU") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "ZA") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "ZM") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "ZW") == 0 ) {
        return -120;
    }
    return timezone;
}

int GeoIP_time_zone_dst_offset_by_country_and_region(const char * country,const char * region) {
    int timezone = 99999;
    if (country == NULL) {
      return 99999;
    }
    if (region == NULL) {
        region = "";
    }
    if ( strcmp (country, "AD") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "AE") == 0 ) {
        return -240;
    }
    if ( strcmp (country, "AF") == 0 ) {
        return -270;
    }
    if ( strcmp (country, "AG") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "AI") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "AL") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "AM") == 0 ) {
        return -240;
    }
    if ( strcmp (country, "AN") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "AO") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "AQ") == 0 ) {
        return -780;
    }
    if ( strcmp (country, "AR") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "18") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "19") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "21") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "22") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "23") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "24") == 0 ) {
            return 180;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "AS") == 0 ) {
        return 660;
    }
    if ( strcmp (country, "AT") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "AU") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return -660;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return -660;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -570;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return -600;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -630;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -660;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -660;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -480;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "AW") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "AX") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "AZ") == 0 ) {
        return -240;
    }
    if ( strcmp (country, "BA") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "BB") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "BD") == 0 ) {
        return -360;
    }
    if ( strcmp (country, "BE") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "BF") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "BG") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "BH") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "BI") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "BJ") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "BL") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "BM") == 0 ) {
        return 180;
    }
    if ( strcmp (country, "BN") == 0 ) {
        return -480;
    }
    if ( strcmp (country, "BO") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "BQ") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "BR") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return 120;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return 120;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return 120;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return 120;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "18") == 0 ) {
            return 120;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "21") == 0 ) {
            return 120;
        }
        else if ( strcmp (region, "22") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "23") == 0 ) {
            return 120;
        }
        else if ( strcmp (region, "24") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "25") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "26") == 0 ) {
            return 120;
        }
        else if ( strcmp (region, "27") == 0 ) {
            return 120;
        }
        else if ( strcmp (region, "28") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "29") == 0 ) {
            return 120;
        }
        else if ( strcmp (region, "30") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "31") == 0 ) {
            return 180;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "BS") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "BT") == 0 ) {
        return -360;
    }
    if ( strcmp (country, "BV") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "BW") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "BY") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "BZ") == 0 ) {
        return 360;
    }
    if ( strcmp (country, "CA") == 0 ) {
        if ( strcmp (region, "AB") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "BC") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "MB") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "NB") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "NL") == 0 ) {
            return 150;
        }
        else if ( strcmp (region, "NS") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "NT") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "NU") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "ON") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "PE") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "QC") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "SK") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "YT") == 0 ) {
            return 420;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "CC") == 0 ) {
        return -390;
    }
    if ( strcmp (country, "CD") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return -120;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "CF") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "CG") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "CH") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "CI") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "CK") == 0 ) {
        return 600;
    }
    if ( strcmp (country, "CL") == 0 ) {
        return 180;
    }
    if ( strcmp (country, "CM") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "CN") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "18") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "19") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "21") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "22") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "23") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "24") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "25") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "26") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "28") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "29") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "30") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "31") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "32") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "33") == 0 ) {
            return -480;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "CO") == 0 ) {
        return 300;
    }
    if ( strcmp (country, "CR") == 0 ) {
        return 360;
    }
    if ( strcmp (country, "CU") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "CV") == 0 ) {
        return 60;
    }
    if ( strcmp (country, "CW") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "CX") == 0 ) {
        return -420;
    }
    if ( strcmp (country, "CY") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "CZ") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "DE") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "DJ") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "DK") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "DM") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "DO") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "DZ") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "EC") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "18") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "19") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "22") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "24") == 0 ) {
            return 300;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "EE") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "EG") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "EH") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "ER") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "ES") == 0 ) {
        if ( strcmp (region, "07") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "27") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "29") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "31") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "32") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "34") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "39") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "51") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "52") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "53") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "54") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "55") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "56") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "57") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "58") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "59") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "60") == 0 ) {
            return -120;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "ET") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "FI") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "FJ") == 0 ) {
        return -780;
    }
    if ( strcmp (country, "FK") == 0 ) {
        return 180;
    }
    if ( strcmp (country, "FM") == 0 ) {
        return -660;
    }
    if ( strcmp (country, "FO") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "FR") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "FX") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "GA") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "GB") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "GD") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "GE") == 0 ) {
        return -240;
    }
    if ( strcmp (country, "GF") == 0 ) {
        return 180;
    }
    if ( strcmp (country, "GG") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "GH") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "GI") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "GL") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return 180;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return 120;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return 120;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "GM") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "GN") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "GP") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "GQ") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "GR") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "GS") == 0 ) {
        return 120;
    }
    if ( strcmp (country, "GT") == 0 ) {
        return 360;
    }
    if ( strcmp (country, "GU") == 0 ) {
        return -600;
    }
    if ( strcmp (country, "GW") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "GY") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "HK") == 0 ) {
        return -480;
    }
    if ( strcmp (country, "HN") == 0 ) {
        return 360;
    }
    if ( strcmp (country, "HR") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "HT") == 0 ) {
        return 300;
    }
    if ( strcmp (country, "HU") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "ID") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return -540;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "18") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "19") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "21") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "22") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "23") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "24") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "25") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "26") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "28") == 0 ) {
            return -540;
        }
        else if ( strcmp (region, "29") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "30") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "31") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "32") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "33") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "34") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "35") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "36") == 0 ) {
            return -540;
        }
        else if ( strcmp (region, "37") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "38") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "39") == 0 ) {
            return -540;
        }
        else if ( strcmp (region, "40") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "41") == 0 ) {
            return -480;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "IE") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "IL") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "IM") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "IN") == 0 ) {
        return -330;
    }
    if ( strcmp (country, "IO") == 0 ) {
        return -360;
    }
    if ( strcmp (country, "IQ") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "IR") == 0 ) {
        return -270;
    }
    if ( strcmp (country, "IS") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "IT") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "JE") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "JM") == 0 ) {
        return 300;
    }
    if ( strcmp (country, "JO") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "JP") == 0 ) {
        return -540;
    }
    if ( strcmp (country, "KE") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "KG") == 0 ) {
        return -360;
    }
    if ( strcmp (country, "KH") == 0 ) {
        return -420;
    }
    if ( strcmp (country, "KI") == 0 ) {
        return -720;
    }
    if ( strcmp (country, "KM") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "KN") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "KP") == 0 ) {
        return -510;
    }
    if ( strcmp (country, "KR") == 0 ) {
        return -540;
    }
    if ( strcmp (country, "KW") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "KY") == 0 ) {
        return 300;
    }
    if ( strcmp (country, "KZ") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return -360;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "LA") == 0 ) {
        return -420;
    }
    if ( strcmp (country, "LB") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "LC") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "LI") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "LK") == 0 ) {
        return -330;
    }
    if ( strcmp (country, "LR") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "LS") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "LT") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "LU") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "LV") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "LY") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "MA") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "MC") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "MD") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "ME") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "MF") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "MG") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "MH") == 0 ) {
        return -720;
    }
    if ( strcmp (country, "MK") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "ML") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "MM") == 0 ) {
        return -390;
    }
    if ( strcmp (country, "MN") == 0 ) {
        if ( strcmp (region, "06") == 0 ) {
            return -540;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return -540;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return -540;
        }
        else if ( strcmp (region, "19") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return -540;
        }
        else if ( strcmp (region, "21") == 0 ) {
            return -540;
        }
        else if ( strcmp (region, "25") == 0 ) {
            return -540;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "MO") == 0 ) {
        return -480;
    }
    if ( strcmp (country, "MP") == 0 ) {
        return -600;
    }
    if ( strcmp (country, "MQ") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "MR") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "MS") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "MT") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "MU") == 0 ) {
        return -240;
    }
    if ( strcmp (country, "MV") == 0 ) {
        return -300;
    }
    if ( strcmp (country, "MW") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "MX") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "18") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "19") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "21") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "22") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "23") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "24") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "25") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "26") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "27") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "28") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "29") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "30") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "31") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "32") == 0 ) {
            return 300;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "MY") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return -480;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "MZ") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "NA") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "NC") == 0 ) {
        return -660;
    }
    if ( strcmp (country, "NE") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "NF") == 0 ) {
        return -660;
    }
    if ( strcmp (country, "NG") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "NI") == 0 ) {
        return 360;
    }
    if ( strcmp (country, "NL") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "NO") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "NP") == 0 ) {
        return -345;
    }
    if ( strcmp (country, "NR") == 0 ) {
        return -720;
    }
    if ( strcmp (country, "NU") == 0 ) {
        return 660;
    }
    if ( strcmp (country, "NZ") == 0 ) {
        if ( strcmp (region, "85") == 0 ) {
            return -780;
        }
        else if ( strcmp (region, "E7") == 0 ) {
            return -780;
        }
        else if ( strcmp (region, "E8") == 0 ) {
            return -780;
        }
        else if ( strcmp (region, "E9") == 0 ) {
            return -780;
        }
        else if ( strcmp (region, "F1") == 0 ) {
            return -780;
        }
        else if ( strcmp (region, "F2") == 0 ) {
            return -780;
        }
        else if ( strcmp (region, "F3") == 0 ) {
            return -780;
        }
        else if ( strcmp (region, "F4") == 0 ) {
            return -780;
        }
        else if ( strcmp (region, "F5") == 0 ) {
            return -780;
        }
        else if ( strcmp (region, "F6") == 0 ) {
            return -780;
        }
        else if ( strcmp (region, "F7") == 0 ) {
            return -825;
        }
        else if ( strcmp (region, "F8") == 0 ) {
            return -780;
        }
        else if ( strcmp (region, "F9") == 0 ) {
            return -780;
        }
        else if ( strcmp (region, "G1") == 0 ) {
            return -780;
        }
        else if ( strcmp (region, "G2") == 0 ) {
            return -780;
        }
        else if ( strcmp (region, "G3") == 0 ) {
            return -780;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "OM") == 0 ) {
        return -240;
    }
    if ( strcmp (country, "PA") == 0 ) {
        return 300;
    }
    if ( strcmp (country, "PE") == 0 ) {
        return 300;
    }
    if ( strcmp (country, "PF") == 0 ) {
        return 570;
    }
    if ( strcmp (country, "PG") == 0 ) {
        return -600;
    }
    if ( strcmp (country, "PH") == 0 ) {
        return -480;
    }
    if ( strcmp (country, "PK") == 0 ) {
        return -300;
    }
    if ( strcmp (country, "PL") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "PM") == 0 ) {
        return 120;
    }
    if ( strcmp (country, "PN") == 0 ) {
        return 480;
    }
    if ( strcmp (country, "PR") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "PS") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "PT") == 0 ) {
        if ( strcmp (region, "02") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "18") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "19") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "21") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "22") == 0 ) {
            return -60;
        }
        else if ( strcmp (region, "23") == 0 ) {
            return 0;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "PW") == 0 ) {
        return -540;
    }
    if ( strcmp (country, "PY") == 0 ) {
        return 180;
    }
    if ( strcmp (country, "QA") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "RE") == 0 ) {
        return -240;
    }
    if ( strcmp (country, "RO") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "RS") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "RU") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -600;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "18") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "21") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "22") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "23") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "24") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "25") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "26") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "27") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "28") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "29") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "30") == 0 ) {
            return -600;
        }
        else if ( strcmp (region, "31") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "32") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "33") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "34") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "35") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "36") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "37") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "38") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "39") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "40") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "41") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "42") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "43") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "44") == 0 ) {
            return -660;
        }
        else if ( strcmp (region, "45") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "46") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "47") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "48") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "49") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "50") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "51") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "52") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "53") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "54") == 0 ) {
            return -360;
        }
        else if ( strcmp (region, "55") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "56") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "57") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "58") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "59") == 0 ) {
            return -600;
        }
        else if ( strcmp (region, "60") == 0 ) {
            return -120;
        }
        else if ( strcmp (region, "61") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "62") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "63") == 0 ) {
            return -540;
        }
        else if ( strcmp (region, "64") == 0 ) {
            return -660;
        }
        else if ( strcmp (region, "65") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "66") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "67") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "68") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "69") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "70") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "71") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "72") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "73") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "74") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "75") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "76") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "77") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "78") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "79") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "80") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "81") == 0 ) {
            return -240;
        }
        else if ( strcmp (region, "82") == 0 ) {
            return -480;
        }
        else if ( strcmp (region, "83") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "84") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "85") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "86") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "87") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "88") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "89") == 0 ) {
            return -600;
        }
        else if ( strcmp (region, "90") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "91") == 0 ) {
            return -420;
        }
        else if ( strcmp (region, "92") == 0 ) {
            return -720;
        }
        else if ( strcmp (region, "93") == 0 ) {
            return -480;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "RW") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "SA") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "SB") == 0 ) {
        return -660;
    }
    if ( strcmp (country, "SC") == 0 ) {
        return -240;
    }
    if ( strcmp (country, "SD") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "SE") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "SG") == 0 ) {
        return -480;
    }
    if ( strcmp (country, "SH") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "SI") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "SJ") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "SK") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "SL") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "SM") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "SN") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "SO") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "SR") == 0 ) {
        return 180;
    }
    if ( strcmp (country, "SS") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "ST") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "SV") == 0 ) {
        return 360;
    }
    if ( strcmp (country, "SX") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "SY") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "SZ") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "TC") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "TD") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "TF") == 0 ) {
        return -300;
    }
    if ( strcmp (country, "TG") == 0 ) {
        return 0;
    }
    if ( strcmp (country, "TH") == 0 ) {
        return -420;
    }
    if ( strcmp (country, "TJ") == 0 ) {
        return -300;
    }
    if ( strcmp (country, "TK") == 0 ) {
        return -780;
    }
    if ( strcmp (country, "TL") == 0 ) {
        return -540;
    }
    if ( strcmp (country, "TM") == 0 ) {
        return -300;
    }
    if ( strcmp (country, "TN") == 0 ) {
        return -60;
    }
    if ( strcmp (country, "TO") == 0 ) {
        return -780;
    }
    if ( strcmp (country, "TR") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "TT") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "TV") == 0 ) {
        return -720;
    }
    if ( strcmp (country, "TW") == 0 ) {
        return -480;
    }
    if ( strcmp (country, "TZ") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "UA") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "04") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "11") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "15") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "16") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "17") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "18") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "19") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "20") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "21") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "22") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "23") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "24") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "25") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "26") == 0 ) {
            return -180;
        }
        else if ( strcmp (region, "27") == 0 ) {
            return -180;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "UG") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "UM") == 0 ) {
        return -720;
    }
    if ( strcmp (country, "US") == 0 ) {
        if ( strcmp (region, "AK") == 0 ) {
            return 480;
        }
        else if ( strcmp (region, "AL") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "AR") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "AZ") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "CA") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "CO") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "CT") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "DC") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "DE") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "FL") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "GA") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "HI") == 0 ) {
            return 600;
        }
        else if ( strcmp (region, "IA") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "ID") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "IL") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "IN") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "KS") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "KY") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "LA") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "MA") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "MD") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "ME") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "MI") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "MN") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "MO") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "MS") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "MT") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "NC") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "ND") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "NE") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "NH") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "NJ") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "NM") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "NV") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "NY") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "OH") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "OK") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "OR") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "PA") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "RI") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "SC") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "SD") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "TN") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "TX") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "UT") == 0 ) {
            return 360;
        }
        else if ( strcmp (region, "VA") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "VT") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "WA") == 0 ) {
            return 420;
        }
        else if ( strcmp (region, "WI") == 0 ) {
            return 300;
        }
        else if ( strcmp (region, "WV") == 0 ) {
            return 240;
        }
        else if ( strcmp (region, "WY") == 0 ) {
            return 360;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "UY") == 0 ) {
        return 180;
    }
    if ( strcmp (country, "UZ") == 0 ) {
        if ( strcmp (region, "01") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "02") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "03") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "05") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "06") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "07") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "08") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "09") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "10") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "12") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "13") == 0 ) {
            return -300;
        }
        else if ( strcmp (region, "14") == 0 ) {
            return -300;
        }
        else {
             return 99999;
        }
    }
    if ( strcmp (country, "VA") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "VC") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "VE") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "VG") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "VI") == 0 ) {
        return 240;
    }
    if ( strcmp (country, "VN") == 0 ) {
        return -420;
    }
    if ( strcmp (country, "VU") == 0 ) {
        return -660;
    }
    if ( strcmp (country, "WF") == 0 ) {
        return -720;
    }
    if ( strcmp (country, "WS") == 0 ) {
        return 660;
    }
    if ( strcmp (country, "YE") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "YT") == 0 ) {
        return -180;
    }
    if ( strcmp (country, "YU") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "ZA") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "ZM") == 0 ) {
        return -120;
    }
    if ( strcmp (country, "ZW") == 0 ) {
        return -120;
    }
    return timezone;
}
