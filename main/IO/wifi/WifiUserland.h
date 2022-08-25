/*
 * Wifiuserland.h
 *
 *  Created on: Aug 4, 2022
 *      Author: arnoud
 */

#ifndef MAIN_MKII_IO_WIFI_WIFIUSERLAND_H_
#define MAIN_MKII_IO_WIFI_WIFIUSERLAND_H_



#include "WifiSTA.h"
#include "WifiAP.h"
#include "WifiEngine.h"
#include "WifiListner.h"

#include "esp_netif_ip_addr.h"

extern const uint8_t favicon_ico_start[] asm("_binary_favicon_ico_start");
extern const uint8_t favicon_ico_end[] asm("_binary_favicon_ico_end");
const uint32_t favicon_ico_len = favicon_ico_end - favicon_ico_start;

extern const uint8_t dimlux_css_start[] asm("_binary_dimlux_css_start");
extern const uint8_t dimlux_css_end[] asm("_binary_dimlux_css_end");
const uint32_t dimlux_css_len = dimlux_css_end - dimlux_css_start;


//typedef struct http_file_server_task_parameters
//{
//  xQueueHandle xJoystickQueue;
//  xQueueHandle xPowerQueue;
//} http_file_server_task_parameters;


esp_err_t get_handler_DimluxCSS_(httpd_req_t *req);
esp_err_t get_handler_Favicon_(httpd_req_t *req);

//===========================================
//===========================================
//===========================================

class WifiUserland : public WifiListner
	{
	public:
		WifiUserland();
		virtual ~WifiUserland();

		esp_err_t 	wifi_init();
		void 		wifi_shutdown();

		bool 		wifi_get_isstarted();

		//const char * get_foundAPs();

		void 		wifi_got_ip(esp_ip4_addr_t _ip) 				override;
		void 		wifi_set_currentWifiEvent(int32_t _wifiEvent) 	override;

		esp_err_t 	wifi_sta_initiated()							override;
		esp_err_t 	wifi_ap_initiated() 							override;

	private:
	//	DataEngine * pDataengine;
	//	MKII * pMKii;

		esp_err_t wifi_init_wifiAP();
		esp_err_t wifi_init_wifiSTA();

		WifiSTA * pWifiSTA = nullptr;
		WifiAP * pWifiAP = nullptr;

		bool isWifiInitDone;
	};

#endif /* MAIN_MKII_IO_WIFI_WIFIUSERLAND_H_ */
