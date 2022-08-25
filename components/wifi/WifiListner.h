#ifndef WIFI_WIFILISTNER_H_
#define WIFI_WIFILISTNER_H_

#include "esp_netif_ip_addr.h"

#include <esp_err.h>

class WifiListner
	{
	public:
		WifiListner() {}
		virtual ~WifiListner() = default;

		virtual void 		wifi_got_ip(esp_ip4_addr_t ip) {};
		virtual void 		wifi_set_currentWifiEvent(int32_t _wifiEvent) {};

		virtual esp_err_t 	wifi_sta_initiated() 	{ return ESP_FAIL; };		/* callback when STA wifi is ininited */
		virtual esp_err_t 	wifi_ap_initiated() 	{ return ESP_FAIL; };		/* callback when AP wifi is ininited */
	};

#endif /* WIFI_WIFILISTNER_H_ */
