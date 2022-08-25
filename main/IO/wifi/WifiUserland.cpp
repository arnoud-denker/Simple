/*
 * Wifiuserland.cpp
 *
 *  Created on: Aug 4, 2022
 *      Author: arnoud
 */

#include "WifiUserland.h"

#include "WifiEngine.h"
//#include "WifiHelper.h"

#include "sdkconfig.h"
#include <esp_http_server.h>
#include <WifiHttpsServer.h>
#include "../../../components/wifi/WifiCtrMode.h"

#include "WifiSTA.h"
#include "WifiAP.h"

#include "alog.h"

#include "WifiuserlandConstants.h"
#include "Constants.h"

#define TAG "WIFIUSERLAND"

//===========================================
//===========================================
//===========================================

esp_err_t get_handler_Favicon_(httpd_req_t *req)
	{
	httpd_resp_set_type(req, mine_icon);
	return httpd_resp_send(req, (const char *) favicon_ico_start, (ssize_t)favicon_ico_len);
	}

esp_err_t get_handler_DimluxCSS_(httpd_req_t *req)
	{
	httpd_resp_set_type(req,mime_css);
	return httpd_resp_send(req, (const char *) dimlux_css_start, (ssize_t)dimlux_css_len);
	}

//===========================================
//===========================================
//===========================================

WifiUserland::WifiUserland()
	{
	//pMKii = _pMKii;
	//pDataengine = _pDataengine;

	isWifiInitDone = false;
	}

//===========================================
//===========================================
//===========================================

//todo
WifiUserland::~WifiUserland()
	{
	if (pWifiAP != nullptr)
		{
		delete(pWifiAP);
		}
	if (pWifiSTA != nullptr)
		{
		delete(pWifiSTA);
		}
	}

//===========================================
//===========================================
//===========================================

esp_err_t WifiUserland::wifi_init()
	{
	if (isWifiInitDone == true)
		return false;

	isWifiInitDone = true;

	//pMKii->mkii_set_CommStatus(ComStatussen::COMMSTATUS_INIT);

	#ifdef CONFIG_STADEBUG
		LOG("Going to init STA, due STADEBUG...");

	//	pDataengine->set_flash_APNAME((char*) DEBUG_WIFI_SSID);
	//	pDataengine->set_flash_APPASS((char*) DEBUG_WIFI_PASSWORD);

		wifi_init_wifiSTA();

	#else
			#ifdef CONFIG_DISABLEWIFI
				LOG("WIFI is disabled by firmware !!!!...");
				return false;
			#else
//				LOG("wifi init");
//				if (pDataengine->get_flash_DISABLEWIFI() == false)
//					{
//					LOG("Reboot cause: %d \n", pDataengine->get_rebootCause() );
//
//					if (pDataengine->get_rebootCause() == RebootCauseList::REBOOT_AFTERREBOOTAP)
//						{
//						LOG("Due reset status .. going to init STA...");
//						wifi_init_wifiSTA();
//						}
//					else if (pDataengine->get_rebootCause() == RebootCauseList::REBOOT_DUELONGKEYPRESS)
//						{
//						LOG("Due reset status .. going to init AP...");
//						wifi_init_wifiAP();
//						}
//					else
//						{
//						LOG("Due reset status .. NO wifi");
//						}
//					return true;
//					}
//				else	// disable wifi
//					{
					LOG("WIFI is disabled by user...");
					return false;
//					}
			#endif
		#endif

	return ESP_OK;
	}

//===========================================
//===========================================
//===========================================

esp_err_t WifiUserland::wifi_init_wifiAP()
	{
	//////	if (wifiEngineSTA->wifiSTA_getConnectionStatus() == true)
	//////		{
	//////		wifiEngineSTA->wifiSTA_shutdown();
	//////		}
	//////	wifiEngineAP->wifiAP_init_softAP();


	pWifiAP = new WifiAP(this, WifiCtrMode::WifiAP, "ballast", default_wifiAP_Password );
	return pWifiAP->wifi_init();
	}

//===========================================
//===========================================
//===========================================

esp_err_t WifiUserland::wifi_init_wifiSTA()
	{
	pWifiSTA = new WifiSTA(this, WifiCtrMode::WifiSTA, "ballast", default_wifiSTA_SSIDname, default_wifiSTA_Password);
	return pWifiSTA->wifi_init();
	}

//===========================================
//===========================================
//===========================================

/* callback when STA wifi is ininited
Add http uri's
Add ws uri and updatetask
/hotspot-detect.html" is auto detect osx
*/
esp_err_t WifiUserland::wifi_sta_initiated()
	{
	LOG("wifi_sta_initiated");

	if (pWifiSTA != nullptr && pWifiSTA->wifi_get_isstarted() == true && pWifiSTA->wifi_get_connectionStatus())
		{
		if (pWifiSTA->wifi_startWebserver(true) == ESP_OK)
		if (pWifiSTA->wifi_registerHttpPath("/favicon.ico", 		get_handler_Favicon_,		HTTP_GET 	)  == ESP_OK)
		if (pWifiSTA->wifi_registerHttpPath("/", 					get_handlerSTA_Root_,		HTTP_GET 	)  == ESP_OK)
		if (pWifiSTA->wifi_registerHttpPath("/dimlux.css", 			get_handler_DimluxCSS_,		HTTP_GET 	)  == ESP_OK)
		if (pWifiSTA->wifi_registerHttpPath("/staroot.js", 			get_handlerSTA_RootJS_,		HTTP_GET 	)  == ESP_OK)
		if (pWifiSTA->wifi_registerHttpPath("/stasetting.html", 	get_handlerSTA_Setting_,	HTTP_GET 	)  == ESP_OK)
		if (pWifiSTA->wifi_registerHttpPath("/stasetting.js", 		get_handlerSTA_SettingJS_,	HTTP_GET 	)  == ESP_OK)
		if (pWifiSTA->wifi_registerHttpPath("/connection", 			get_handlerSTA_PageSubmit_,	HTTP_POST	)  == ESP_OK)
		if (pWifiSTA->wifi_registerWsPathAndStartUserupdateTask("/ws",
																get_staUserSendDataUpdateTask_, 	"staSendUserupdateTask",
																get_staUserReceiveDataUpdateTask_, 	"staReceiveUserupdateTask",
																pWifiSTA) == ESP_OK)
			{
	    	return ESP_OK;
			}
		}

	LOG("wifi_sta_initiated FAILED");
	return ESP_FAIL;
	}

//================================================================

//    pWiFi->wifiSTA_get_pMKii()->mkii_set_ip(* (&event->ip_info.ip));

    //ADDED network to wifi
    //   start_udp_broadcasts();
    //   start_wifi_server();

//	    pWifiEngineSTA-> get_pWifiabp2()->start_abp2_server();



/* callback when AP wifi is ininited */
esp_err_t WifiUserland::wifi_ap_initiated()
	{
	LOG("wifi_ap_initiated");

//	if (pWifiAP != nullptr && pWifiAP->wifi_get_isstarted() == true && pWifiAP->wifi_get_connectionStatus())
//		{
//		if (pWifiAP->wifi_startWebserver(false) == ESP_OK)
//		if (pWifiAP->wifi_registerPath("/favicon.ico", 			get_handler_sta_Favicon_,	HTTP_GET, false)  == ESP_OK)
//		if (pWifiAP->wifi_registerPath("/dimlux.css", 			get_handler_DimluxCSS_,		HTTP_GET, false)  == ESP_OK)
//		if (pWifiAP->wifi_registerPath("/", 					get_handlerAP_Root,			HTTP_GET, false)  == ESP_OK)
//		if (pWifiAP->wifi_registerPath("/hotspot-detect.html", 	get_handlerAP_Root,			HTTP_GET, false)  == ESP_OK)
//		if (pWifiAP->wifi_registerPath("/cause", 				get_handlerAP_PageCause,	HTTP_GET, false)  == ESP_OK)
//		if (pWifiAP->wifi_registerPath("/foundaps", 			get_handlerAP_PageCause,	HTTP_GET, false)  == ESP_OK)
//		if (pWifiAP->wifi_registerPath("/ssid", 				get_handlerAP_PageCause,	HTTP_GET, false)  == ESP_OK)
//		if (pWifiAP->wifi_registerPath("/name", 				get_handlerAP_PageCause,	HTTP_GET, false)  == ESP_OK)
//		if (pWifiAP->wifi_registerPath("/location", 			get_handlerAP_PageCause,	HTTP_GET, false)  == ESP_OK)
//		if (pWifiAP->wifi_registerPath("/swversion", 			get_handlerAP_PageCause,	HTTP_GET, false)  == ESP_OK)
//		if (pWifiAP->wifi_registerPath("/ntp", 					get_handlerAP_PageCause,	HTTP_GET, false)  == ESP_OK)
//		if (pWifiAP->wifi_registerPath("/dimlevel", 			get_handlerAP_PageCause,	HTTP_GET, false)  == ESP_OK)
//			return ESP_OK;
//		}

	return ESP_FAIL;
	}

//===========================================
//===========================================
//===========================================

void WifiUserland::wifi_shutdown()
	{
//	if (pWifiAP != nullptr)
//		{
//		pWifiAP->wifi_stopWebserver();
//		pWifiAP->wifi_shutdown();
//		}

	if (pWifiSTA != nullptr)
		{
		pWifiSTA->wifi_stopWebserver();
		pWifiSTA->wifi_shutdown();
		}

	isWifiInitDone = false;
	}

//===========================================
//===========================================
//===========================================

bool WifiUserland::wifi_get_isstarted()
	{
	return isWifiInitDone;
	}

//===========================================
//===========================================
//===========================================

/* callback when wifi has a IP address */
void WifiUserland::wifi_got_ip(esp_ip4_addr_t _ip)
	{
	LOG("IP address of WiFi controller: %03d.%03d.%03d.%03d", esp_ip4_addr1_16(&_ip), esp_ip4_addr2_16(&_ip), esp_ip4_addr3_16(&_ip), esp_ip4_addr4_16(&_ip));
//	pMKii->mkii_set_ip(_ip);
//	pMKii->mkii_set_CommStatus(ComStatussen::COMMSTATUS_GOTIP);
	}

//===========================================
//===========================================
//===========================================

void WifiUserland::wifi_set_currentWifiEvent(int32_t _wifiEvent)
	{
	switch (_wifiEvent)
		{
		case	WIFI_EVENT_WIFI_READY:
		case	WIFI_EVENT_STA_START:
		case	WIFI_EVENT_STA_STOP:
		case	WIFI_EVENT_STA_CONNECTED:
		case	WIFI_EVENT_AP_STOP:
		case 	WIFI_EVENT_SCAN_DONE:
			LOG("Received a WifiEvent %d ", _wifiEvent);
			break;

		case	WIFI_EVENT_STA_DISCONNECTED:
			//pMKii->mkii_set_CommStatus(ComStatussen::COMMSTATUS_STA_DISCONNECT);
			break;

		case 	WIFI_EVENT_AP_PROBEREQRECVED:
			LOG("Received a WifiEvent in Userland %d ", _wifiEvent);
			break;

		case	WIFI_EVENT_AP_START:
		//	pMKii->mkii_set_CommStatus(ComStatussen::COMMSTATUS_AP_START);
			break;

		case 	WIFI_EVENT_AP_STACONNECTED:
		//	pMKii->mkii_set_CommStatus(ComStatussen::COMMSTATUS_AP_CONNECTED);
			break;

		case 	WIFI_EVENT_AP_STADISCONNECTED:
			//pMKii->mkii_set_CommStatus(ComStatussen::COMMSTATUS_AP_DISCONNECTED);
			break;

		default: break;
		}
	}

//===========================================
//===========================================
//===========================================

//todo if needed
//const char * Wifiuserland::get_foundAPs()
//	{
//	return "";
//	//return pWifiEngine->wifi_get_foundAPs();
//	}

//===========================================
//===========================================
//===========================================
