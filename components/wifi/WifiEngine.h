/*
 * ConnectionEngine.h
 *
 *  Created on: Oct 27, 2019
 *      Author: arnoud
 */

#ifndef WIFIENGINE_H_
#define WIFIENGINE_H_

//#include "global.h"

#include "sdkconfig.h"
#include "WifiListner.h"
#include "WifiConstants.h"
#include "WifiHttpsServer.h"
#include "WifiMode.h"

#include <esp_http_server.h>
#include <esp_wifi.h>
#include <nvs_flash.h>

#include "WifiHelper.h"


	//===========================================
	//===========================================
	//===========================================




class WifiEngine : public WifiHttpsServer
	{
	public:
		WifiEngine(WifiListner * _listner, WifiMode _wifimode, const char * _pHostname, const char * _pAPName, const char * _pAPPAssword);
		WifiEngine(WifiListner * _listner,WifiMode _wifimode, const char * _pHostname, const char * _pPassword);

		virtual ~WifiEngine();

		esp_err_t 		wifi_init();
		esp_err_t 		wifi_shutdown();
//		const char * 	wifi_get_foundAPs();

		void wifi_sta_got_ip(esp_ip4_addr_t ip);
		void wifi_ap_got_ip();

		void wifi_sta_initiated();
		void wifi_ap_initiated();

		bool wifi_get_isstarted();

		bool wifi_get_connectionStatus();
		void wifi_set_connectionStatus(bool _stat);

		int wifi_get_numberOfSTAConnectionRetries();
		void wifi_increase_numberOfSTAConnectionRetries();

		void wifi_set_currentWifiEvent(int32_t _wifiEvent);

	private:
		WifiMode wifimode;
		const char * pHostname;
		const char * pAPName;				// device to connect to password (in STA mode)
		const char * pPassword;				// OWN password (in AP mode) or device to connect to password (in STA mode)

		esp_netif_ip_info_t * pIp4address;	// ip address for AP mode
		esp_netif_t * pEsp_netif_t = nullptr;

		static void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

		bool wifi_isstarted;
		bool wifi_connected;

		WifiListner * pWifiListner;

		int numberOfsSTAConnectionRetries;

		const char * get_wifimode_str(WifiMode _mode);

		esp_event_handler_instance_t * pInstance_got_ip;
		esp_event_handler_instance_t * pInstance_any_id;
	};


#endif /* WIFIENGINE_H_ */
