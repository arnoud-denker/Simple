/*
 * WifiConstants.h
 *
 *  Created on: Aug 1, 2022
 *      Author: arnoud
 */

#ifndef COMPONENTS_WIFI_WIFICONSTANTS_H_
#define COMPONENTS_WIFI_WIFICONSTANTS_H_

//todo, moet in sdkconfig komen
#define CONFIG_AP_IP "192.168.1.1"
#define CONFIG_AP_GATEWAY "192.168.1.1"
#define CONFIG_AP_NETMASK "255.255.255.0"


#define WS_QUEUE_SEND_BUFFER 256
#define WS_QUEUE_RECEIVER_BUFFER 256



#define MAX_WEBSOCKET_CLIENTS 4
#define MAX_ENTRIES_WIFISCANLIST 8

#define MAX_STAHTTPS_CLIENTS 3			// is defaul 4
#define MAX_URI_HANDLERS 13				// is default 8

#define MAX_STACONNECTIONS_RETRY 5



#endif /* COMPONENTS_WIFI_WIFICONSTANTS_H_ */
