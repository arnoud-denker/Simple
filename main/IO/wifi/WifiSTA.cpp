/*
 * Wifista.cpp
 *
 *  Created on: Aug 9, 2022
 *      Author: arnoud
 */

#include "WifiSTA.h"

#include "esp_err.h"
#include <esp_http_server.h>

#include "../../../components/wifi/WifiCtrMode.h"
#include "WifiEngine.h"
#include "alog.h"

#define TAG "WIFISTA"

esp_err_t get_handlerSTA_Root_(httpd_req_t *req)
	{
	httpd_resp_set_type(req, mime_html);
	return httpd_resp_send(req, (const char *) staroot_html_start, (ssize_t)staroot_html_len);
	}

esp_err_t get_handlerSTA_RootJS_(httpd_req_t *req)
	{
	httpd_resp_set_type(req, mine_js);
	return httpd_resp_send(req, (const char *) staroot_js_start, (ssize_t)staroot_js_len);
	}

esp_err_t get_handlerSTA_Setting_(httpd_req_t *req)
	{
	httpd_resp_set_type(req, mime_html);
	return httpd_resp_send(req, (const char *) stasetting_html_start, (ssize_t)stasetting_html_len);
	}

esp_err_t get_handlerSTA_SettingJS_(httpd_req_t *req)
	{
	httpd_resp_set_type(req, mine_js);
	return httpd_resp_send(req, (const char *) stasetting_js_start, (ssize_t)stasetting_js_len);
	}

//===========================================
//===========================================
//===========================================

	void get_staUserReceiveDataUpdateTask_(void* pvParameters)
		{
		WifiSTA* pWifiSTA = reinterpret_cast<WifiSTA*>(pvParameters); 	//obtain the instance pointer
		pWifiSTA->staUserReceiveDataUpdateTask(); 											//dispatch to the member function, now that we have an instance pointer
		}

	//===========================================

	void WifiSTA::staUserReceiveDataUpdateTask()
		{
		QueueHandle_t receivequeu = get_wsReceiveQueuHandle();

		if (receivequeu != NULL)
			{
			LOG("Receive queue is avaible");

			wsreceive_msg receivemessage;

			while (true)
				{
				if( xQueueReceive( receivequeu, &receivemessage, ( TickType_t ) 10 ) == pdPASS )
					{
					LOG("Received data %s", receivemessage.receiveddata);
					}
				else
					{
					LOG("No receive");
					}

				vTaskDelay(serverReceiveUpdatePeriod);
				}
			}
		else
			{

			LOG("Receive queue not avaible");
			while (true) { vTaskDelay(serverReceiveUpdatePeriod); }
			}
		}

	//===========================================
	//===========================================
	//===========================================

	void get_staUserSendDataUpdateTask_(void* pvParameters)
		{
		WifiSTA* pWifiSTA = reinterpret_cast<WifiSTA*>(pvParameters); 	//obtain the instance pointer
		pWifiSTA->staUserSendDataUpdateTask(); 											//dispatch to the member function, now that we have an instance pointer
		}

	//===========================================

	void WifiSTA::staUserSendDataUpdateTask()
		{
		QueueHandle_t sendqueu = get_wsSendQueuHandle();

		if (sendqueu != NULL)
			{
			int counter = 0;

			char tmpbuf[256];

			xWSsendMessage message;

			while(true)
				{
				counter++;

				sprintf(tmpbuf, "test %d", counter);

				if (get_wssta_handle() != NULL) //)
					{
					cJSON *jsonDataToSend = cJSON_CreateObject();
					//
							if (cJSON_AddStringToObject(jsonDataToSend, "name", 			tmpbuf) != NULL) //	pDataEngine_local->get_pFlash_BALLASTNAME() !
					//		cJSON_AddStringToObject(jsonDataToSend, "location", 			pDataEngine_local->get_pFlash_BALLASTLOCATION() );
					//
					//		cJSON_AddStringToObject(jsonDataToSend, "ap", 					pWifiengineSTA_local->wifiSTA_updateAPinformation().c_str());
					//
					//		cJSON_AddStringToObject(jsonDataToSend, "steermode", 		"wifi");
					//		cJSON_AddStringToObject(jsonDataToSend, "runningstate", 		pDataEngine_local->get_last_runningState_str());
					//		cJSON_AddStringToObject(jsonDataToSend, "hidstatus", 			pDataEngine_local->get_pHidStatus_str());
					//
					//		cJSON_AddStringToObject(jsonDataToSend, "output_p", 			pDataEngine_local->get_powerPercentageStr());
					//		cJSON_AddStringToObject(jsonDataToSend, "output_w", 			pDataEngine_local->get_powerWattStr());
					//
					//		cJSON_AddStringToObject(jsonDataToSend, "tamb1", 				pDataEngine_local->get_temperatureStr() );
					//		cJSON_AddStringToObject(jsonDataToSend, "currentime", 			pMKii_local->get_pCurrentime_str() );

						//	if (cJSON_AddStringToObject(jsonDataToSend, "timeleft", 			"101") != NULL)
					//
					//		//=====================
					//
					//		cJSON_AddStringToObject(jsonDataToSend, "perc", 			"100");
					//
					//		cJSON_AddStringToObject(jsonDataToSend, "timeonhour", 		"9");
					//		cJSON_AddStringToObject(jsonDataToSend, "timeonmin", 		"11");
					//		cJSON_AddStringToObject(jsonDataToSend, "timeoffhour", 		"21");
					//		cJSON_AddStringToObject(jsonDataToSend, "timeoffmin", 		"12");
					//
					//		cJSON_AddStringToObject(jsonDataToSend, "rise", 			"20 min");
					//		cJSON_AddStringToObject(jsonDataToSend, "fall", 			"20 min");
					//
					//		cJSON_AddStringToObject(jsonDataToSend, "limitlo", 			"30");
					//		cJSON_AddStringToObject(jsonDataToSend, "limithi", 			"32");
					//		cJSON_AddStringToObject(jsonDataToSend, "limitsh", 			"34");

						{
						if(cJSON_PrintPreallocated(jsonDataToSend, message.senddata, 255, true))
							{
							xQueueOverwrite( sendqueu, &message );
							}
						else
							{
							ERR("cJSON_PrintPreallocated failed and returned 0");
							}
						}
					cJSON_Delete(jsonDataToSend);
					}
				else
					{
					LOG("HANDLE == MULL");
					}

				vTaskDelay(serverSendUpdatePeriod);
				}
			}
		else
			{
			LOG("Send queue not avaible");
			while (true) { vTaskDelay(serverSendUpdatePeriod); }
			}
		}


//===========================================
//===========================================
//===========================================

esp_err_t get_handlerSTA_PageSubmit_(httpd_req_t *req)
	{
	LOG("SUBMIT %s", req->uri);

////	WifiEngineAP* pConnectEngine = WifiEngineAP::getInstance();
////	DataEngine*  pDataEngine = pConnectEngine->wifiAP_get_Dataengine();
////
////    char buf[1024];
////    int ret, remaining = req->content_len;
////
////    while (remaining > 0)
////    	{
////        /* Read the data for the request */
////        if ((ret = httpd_req_recv(req, buf, MIN(remaining, sizeof(buf)))) <= 0)
////        	{
////            if (ret == 0)
////            	{
////                LOG( "No content received please try again ...");
////            	}
////            else if (ret == HTTPD_SOCK_ERR_TIMEOUT)
////            	{
////                /* Retry receiving if timeout occurred */
////                continue;
////            	}
////            return ESP_FAIL;
////        	}
////
////        /* Log data received */
////        LOG( "=========== RECEIVED DATA ==========");
////        LOG( "%.*s", ret, buf);
////        LOG( "====================================");
////
////        cJSON *root = cJSON_Parse(buf);
////
////        char * json_wificontrolmode = cJSON_GetObjectItem(root, "controlmode")->valuestring;
////        if (json_wificontrolmode == NULL)
////        	{
////        	LOG( "Failed to retrieve json_controlmode, set WIFI to disabled..\n");
////        	pDataEngine->set_flash_DISABLEWIFI(true);		// fail safe..
////        	}
////        else if (strcmp(json_wificontrolmode, "Wifi disabled") == 0)
////        	{
////        	LOG( "User setting, WIFI disable...\n");
////        	pDataEngine->set_flash_DISABLEWIFI(true);
////        	}
////        else
////        	{
////        	LOG( "User setting, WIFI enable...\n");
////        	pDataEngine->set_flash_DISABLEWIFI(false);
////
////        	pDataEngine->set_flash_BALLASTNAME(cJSON_GetObjectItem(root, "ballastname")->valuestring);
////        	pDataEngine->set_flash_BALLASTLOCATION(cJSON_GetObjectItem(root, "ballastlocation")->valuestring);
////        	pDataEngine->set_flash_APNAME(cJSON_GetObjectItem(root, "apname")->valuestring);
////        	pDataEngine->set_flash_APPASS(cJSON_GetObjectItem(root, "appassword")->valuestring);
////
////        	char * json_segmentdimlevel = cJSON_GetObjectItem(root, "segmentdimlevel")->valuestring;
////        	pDataEngine->set_flash_display_brightness_on_hold(atoi(json_segmentdimlevel));
////
////        	char * json_ntpenabled = cJSON_GetObjectItem(root, "ntpenabled")->valuestring;
////            if (strcmp(json_ntpenabled, "on") == 0)
////               	{
////            	pDataEngine->set_flash_NTP(true);
////               	}
////            else
////            	{
////            	pDataEngine->set_flash_NTP(false);
////            	}
////
////            char * json_ipmode = cJSON_GetObjectItem(root, "ipmode")->valuestring;
////            if (json_ipmode == NULL)
////            	{
////            	pDataEngine->set_flash_BALLASTIP((char*)"0.0.0.0");
////            	}
////            else if (strcmp(json_ipmode, "DHCP") == 0)
////            	{
////            	pDataEngine->set_flash_BALLASTIP((char*)"0.0.0.0");
////            	}
////            else
////            	{
////            	pDataEngine->set_flash_BALLASTIP(cJSON_GetObjectItem(root, "ipaddress")->valuestring);
////            	}
////
////
////
////           	printf("JSON: %s \n", cJSON_Print(root));
////
////            pDataEngine->set_rebootCause(rebootCauseList_reboot_afterRebootAP);
////        	}
////
////        remaining -= ret;
////    	}
////
//////======================
////
////    // End response
////    httpd_resp_send_chunk(req, NULL, 0);
////
////    esp_wifi_stop();
////
////
////    pConnectEngine->mkii_doSW_Reset();
//
  	  return ESP_OK;
	  }

//===========================================
//===========================================
//===========================================


////
////void wifiSTA_Update_task()
////	{
//////	//char out[1024];							// ff opletten dat buffer groot genoeg blijft
//////
//////	const int DELAY = 1000 / portTICK_PERIOD_MS; // 1 second
//////
//////	LOG("starting Update_task");
//////
//////	WifiEngineSTA* pWifiengineSTA_local = WifiEngineSTA::getInstance();
//////	DataEngine * pDataEngine_local = pWifiengineSTA_local->wifiSTA_get_pDataengine();
//////	MKII * pMKii_local = pWifiengineSTA_local->wifiSTA_get_pMKii();
//////	WebsocketHandlerSTA * pWebsocketHandlerSTA_local = pWifiengineSTA_local->wifiSTA_get_pWebsocketHandlerSTA();
//////
//////	while(true)
//////		{
//////		if (pWifiengineSTA_local->wifiSTA_getConnectionStatus() )// && pConnectEngine->pBallast->get_isDataUpdated() == true)
//////			{
//////			cJSON * jsonDataToSend = cJSON_CreateObject();
//////
//////			cJSON_AddStringToObject(jsonDataToSend, "name", 				pDataEngine_local->get_pFlash_BALLASTNAME() );
//////			cJSON_AddStringToObject(jsonDataToSend, "location", 			pDataEngine_local->get_pFlash_BALLASTLOCATION() );
//////
//////			cJSON_AddStringToObject(jsonDataToSend, "ap", 					pWifiengineSTA_local->wifiSTA_updateAPinformation().c_str());
//////
//////			cJSON_AddStringToObject(jsonDataToSend, "steermode", 		"wifi");
//////			cJSON_AddStringToObject(jsonDataToSend, "runningstate", 		pDataEngine_local->get_last_runningState_str());
//////			cJSON_AddStringToObject(jsonDataToSend, "hidstatus", 			pDataEngine_local->get_pHidStatus_str());
//////
//////			cJSON_AddStringToObject(jsonDataToSend, "output_p", 			pDataEngine_local->get_powerPercentageStr());
//////			cJSON_AddStringToObject(jsonDataToSend, "output_w", 			pDataEngine_local->get_powerWattStr());
//////
//////			cJSON_AddStringToObject(jsonDataToSend, "tamb1", 				pDataEngine_local->get_temperatureStr() );
//////			cJSON_AddStringToObject(jsonDataToSend, "currentime", 			pMKii_local->get_pCurrentime_str() );
//////
//////			cJSON_AddStringToObject(jsonDataToSend, "timeleft", 			"101");
//////
////////=====================
//////
//////			cJSON_AddStringToObject(jsonDataToSend, "perc", 			"100");
//////
//////			cJSON_AddStringToObject(jsonDataToSend, "timeonhour", 		"9");
//////			cJSON_AddStringToObject(jsonDataToSend, "timeonmin", 		"11");
//////			cJSON_AddStringToObject(jsonDataToSend, "timeoffhour", 		"21");
//////			cJSON_AddStringToObject(jsonDataToSend, "timeoffmin", 		"12");
//////
//////			cJSON_AddStringToObject(jsonDataToSend, "rise", 			"20 min");
//////			cJSON_AddStringToObject(jsonDataToSend, "fall", 			"20 min");
//////
//////			cJSON_AddStringToObject(jsonDataToSend, "limitlo", 			"30");
//////			cJSON_AddStringToObject(jsonDataToSend, "limithi", 			"32");
//////			cJSON_AddStringToObject(jsonDataToSend, "limitsh", 			"34");
//////
////////=====================
//////
//////			char *jsonDataToSend_pChar = cJSON_Print(jsonDataToSend);
//////			int len = strlen(jsonDataToSend_pChar);
//////
//////			pWebsocketHandlerSTA_local->ws_server_send_text_all(jsonDataToSend_pChar,len);
//////
//////			free(jsonDataToSend_pChar);			// free text object...
//////			cJSON_Delete(jsonDataToSend);	// delete json structure
//////			}
//////
//////		vTaskDelay(DELAY);
//////		}
////	}
////
//////string WifiEngineSTA::wifiSTA_updateAPinformation()
//////	{
//////	wifi_ap_record_t wifidata;
//////	if (esp_wifi_sta_get_ap_info(&wifidata)==0)
//////		{
//////		int8_t rrsi = wifidata.rssi;
//////		string ssidStr = (const char *) wifidata.ssid;
//////
//////		string signalqualityStr;
//////		if (rrsi > -31)
//////			{
//////			signalqualityStr = "Excellent";
//////			}
//////		else if (rrsi > -67)
//////			{
//////			signalqualityStr = "Very good";
//////			}
//////		else if (rrsi > -80)
//////			{
//////			signalqualityStr = "OK";
//////			}
//////		else if (rrsi > -90)
//////			{
//////			signalqualityStr = "Poor";
//////			}
//////		else
//////			{
//////			signalqualityStr = "Unusable";
//////			}
//////
//////		apdatastring.assign("").
//////					append(ssidStr).
//////					append(", ").
//////					append(to_string(rrsi)).
//////					append(" dBm, ").
//////					append(signalqualityStr);
//////		}
//////
//////	return apdatastring;
//////	}
////
//////===========================================
//////===========================================
//////===========================================
////
////
//////void WifiEngineSTA::wifiSTA_staticUpdate_task(void *pvParameter)
//////	{
//////	WifiEngineSTA* wifista = reinterpret_cast<WifiEngineSTA*>(pvParameter);
//////	wifista->wifiSTA_Update_task();
//////	}
////
////


WifiSTA::WifiSTA(WifiListner * _listner, WifiCtrMode _wifimode, const char * _pHostname, const char * _pAPName, const char * _pAPPAssword) :
		WifiEngine( _listner, _wifimode, _pHostname, _pAPName, _pAPPAssword)
	{


	}

WifiSTA::~WifiSTA()
	{

	}

//===========================================
//===========================================
//===========================================




//===========================================
//===========================================
//===========================================


