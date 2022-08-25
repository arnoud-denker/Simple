/*
 * WifiAP.cpp
 *
 *  Created on: Aug 9, 2022
 *      Author: arnoud
 */

#include "WifiAP.h"

#include "esp_err.h"
#include <esp_http_server.h>
#include "WifiEngine.h"

#include "alog.h"

#define TAG "WIFIAP"

esp_err_t get_handlerAP_Root(httpd_req_t *req)
	{
	httpd_resp_set_type(req, mime_html);
	return httpd_resp_send(req, (const char *) aproot_html_start, (ssize_t)aproot_html_len);
	}



esp_err_t get_handlerAP_PageCause(httpd_req_t *req)
	{
//	char tempbuffer[1024];
//	for (uint16_t i = 0; i < sizeof(tempbuffer); i++)
//		{
//		tempbuffer[i] = ' ';
//		}
//
//	ssize_t lenthOfData = 0;
//	WifiEngineAP* pConnectEngine = WifiEngineAP::getInstance();
//
//	if (strstr(req->uri,"/cause") != NULL)
//		{
//		const char * restartcause = pConnectEngine->wifiAP_get_Dataengine()->get_rebootCauseStr();
//		lenthOfData = sprintf(tempbuffer, "%s", restartcause);
//		}
//	else if (strstr(req->uri,"/ssid") != NULL)
//		{
//		const char * ssid = pConnectEngine->wifiAP_get_pWifiAP_SSIDname();
//		lenthOfData = sprintf(tempbuffer, "%s", ssid);
//		}
//	else if (strstr(req->uri,"/foundaps") != NULL)
//		{
//		const char * foundAPs = pConnectEngine->wifiAP_get_foundAPs();
//		lenthOfData = sprintf(tempbuffer, "%s", foundAPs);
//		}
//	else if (strstr(req->uri,"/name") != NULL)
//		{
//		const char * pName = pConnectEngine->wifiAP_get_Dataengine()->get_pFlash_BALLASTNAME();
//		lenthOfData = sprintf(tempbuffer, "%s", pName);
//		}
//	else if (strstr(req->uri,"/location") != NULL)
//		{
//		const char * pLocation = pConnectEngine->wifiAP_get_Dataengine()->get_pFlash_BALLASTLOCATION();
//		lenthOfData = sprintf(tempbuffer, "%s", pLocation);
//		}
//	else if (strstr(req->uri,"/swversion") != NULL)
//		{
//		lenthOfData = sprintf(tempbuffer, "%s", pConnectEngine->wifiAP_get_Dataengine()->get_pSWversion() );
//		}
//	else if (strstr(req->uri,"/ntp") != NULL)
//		{
//		lenthOfData = sprintf(tempbuffer, "%s", (pConnectEngine->wifiAP_get_Dataengine()->get_flash_NTP()? "true" : "false")   );
//		}
//	else if (strstr(req->uri,"/dimlevel") != NULL)
//		{
//		lenthOfData = sprintf(tempbuffer, "%d", ( pConnectEngine->wifiAP_get_Dataengine()->get_pDiplay_brighness_on_hold())   );
//		}
//	else
//		{
//		LOG("Unknown variable asked... sending default");
//		lenthOfData = sprintf(tempbuffer, "%s", "--");
//		}

//	return httpd_resp_send(req, (const char *) tempbuffer, lenthOfData);

	return ESP_OK;
	}

	   //----------------------------------------------------
	   //----------------------------------------------------
	   //----------------------------------------------------

esp_err_t get_handlerAP_PageSubmit(httpd_req_t *req)
	{
//	WifiEngineAP* pConnectEngine = WifiEngineAP::getInstance();
//	DataEngine*  pDataEngine = pConnectEngine->wifiAP_get_Dataengine();
//
//    char buf[1024];
//    int ret, remaining = req->content_len;
//
//    while (remaining > 0)
//    	{
//        /* Read the data for the request */
//        if ((ret = httpd_req_recv(req, buf, MIN(remaining, sizeof(buf)))) <= 0)
//        	{
//            if (ret == 0)
//            	{
//                LOG( "No content received please try again ...");
//            	}
//            else if (ret == HTTPD_SOCK_ERR_TIMEOUT)
//            	{
//                /* Retry receiving if timeout occurred */
//                continue;
//            	}
//            return ESP_FAIL;
//        	}
//
//        /* Log data received */
//        LOG( "=========== RECEIVED DATA ==========");
//        LOG( "%.*s", ret, buf);
//        LOG( "====================================");
//
//        cJSON *root = cJSON_Parse(buf);
//
//        char * json_mode = cJSON_GetObjectItem(root, "mode")->valuestring;
//        if (json_mode == NULL)
//        	{
//        	pDataEngine->set_flash_DISABLEWIFI(true);		// fail safe..
//        	}
//        else if (strcmp(json_mode, "Wifi disabled") == 0)
//        	{
//        	pDataEngine->set_flash_DISABLEWIFI(true);
//        	}
//        else
//        	{
//        	pDataEngine->set_flash_DISABLEWIFI(false);
//
//        	pDataEngine->set_flash_BALLASTNAME(cJSON_GetObjectItem(root, "name")->valuestring);
//        	pDataEngine->set_flash_BALLASTLOCATION(cJSON_GetObjectItem(root, "location")->valuestring);
//        	pDataEngine->set_flash_APNAME(cJSON_GetObjectItem(root, "apname")->valuestring);
//        	pDataEngine->set_flash_APPASS(cJSON_GetObjectItem(root, "appassword")->valuestring);
//
//        	char * json_dimlevel = cJSON_GetObjectItem(root, "dimlevel")->valuestring;
//        	pDataEngine->set_flash_display_brightness_on_hold(atoi(json_dimlevel));
//
//        	char * json_ntpenabled = cJSON_GetObjectItem(root, "ntp")->valuestring;
//            if (strcmp(json_ntpenabled, "on") == 0)
//               	{
//            	pDataEngine->set_flash_NTP(true);
//               	}
//            else
//            	{
//            	pDataEngine->set_flash_NTP(false);
//            	}
//
//            char * json_ipmode = cJSON_GetObjectItem(root, "ipmode")->valuestring;
//            if (json_ipmode == NULL)
//            	{
//            	pDataEngine->set_flash_BALLASTIP((char*)"0.0.0.0");
//            	}
//            else if (strcmp(json_ipmode, "DHCP") == 0)
//            	{
//            	pDataEngine->set_flash_BALLASTIP((char*)"0.0.0.0");
//            	}
//            else
//            	{
//            	pDataEngine->set_flash_BALLASTIP(cJSON_GetObjectItem(root, "ipaddress")->valuestring);
//            	}
//
//           	//printf("JSON: %s \n", cJSON_Print(root));
//
//            pDataEngine->set_rebootCause(RebootCauseList::REBOOT_AFTERREBOOTAP);
//        	}
//
//        remaining -= ret;
//    	}
//
////======================
//
//    // End response
//    httpd_resp_send_chunk(req, NULL, 0);
//
//    esp_wifi_stop();
//
//    pConnectEngine->mkii_doSW_Reset();

    return ESP_OK;
	}


//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

WifiAP::WifiAP(WifiListner * _listner, WifiCtrMode _wifimode, const char * _pHostname, const char * _pAPPAssword) :
	   WifiEngine( _listner, _wifimode, _pHostname, _pAPPAssword)
	{

	}

WifiAP::~WifiAP()
	{

	}



