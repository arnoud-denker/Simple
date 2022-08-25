#ifndef MAIN_CONSTANTS_H_
#define MAIN_CONSTANTS_H_

#include "sdkconfig.h"

#define CONFIG_STADEBUG 1

#define default_wifiAP_SSIDname_prefix "Ballast_"
#define default_wifiAP_Password "voyager"

#define default_wifiSTA_SSIDname "confucius"
#define default_wifiSTA_Password "fUYw8zAK"

#define WIFISTA_MAXIMUM_CONNECTION_RETRIES 10

enum class Wifistate
	{
	 UNKNWON = -1,
	 IDLE = 0,
	 INIT = 1,
	 AP = 2,
	 RESET_TO_STA = 3,
	 STA_OR_MESH = 4
	};



enum class ComStatussen
	{
	COMMSTATUS_INIT = 0,
	COMMSTATUS_INIT_FAILED = 1,
	COMMSTATUS_AP_START = 2,
	COMMSTATUS_AP_CONNECTED = 3,
	COMMSTATUS_AP_DISCONNECTED = 4,

	COMMSTATUS_GOTIP = 5,
	COMMSTATUS_STA_DISCONNECT = 6
	};

//----------------------------------------------------

#endif /* MAIN_CONSTANTS_H_ */
