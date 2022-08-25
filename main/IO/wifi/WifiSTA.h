/*
 * Wifista.h
 *
 *  Created on: Aug 9, 2022
 *      Author: arnoud
 */

#ifndef MAIN_MKII_IO_WIFI_WIFISTA_H_
#define MAIN_MKII_IO_WIFI_WIFISTA_H_

#include "WifiEngine.h"
#include "WifiMode.h"

#include <esp_err.h>
#include <esp_http_server.h>

//#define readBufSize 1024*6
//#define sendBufSize 256


extern const uint8_t staroot_html_start[] asm("_binary_staroot_html_start");
extern const uint8_t staroot_html_end[] asm("_binary_staroot_html_end");
const uint32_t staroot_html_len = staroot_html_end - staroot_html_start;

extern const uint8_t staroot_js_start[] asm("_binary_staroot_js_start");
extern const uint8_t staroot_js_end[] asm("_binary_staroot_js_end");
const uint32_t staroot_js_len = staroot_js_end - staroot_js_start;

extern const uint8_t stasetting_html_start[] asm("_binary_stasetting_html_start");
extern const uint8_t stasetting_html_end[] asm("_binary_stasetting_html_end");
const uint32_t stasetting_html_len = stasetting_html_end - stasetting_html_start;

extern const uint8_t stasetting_js_start[] asm("_binary_stasetting_js_start");
extern const uint8_t stasetting_js_end[] asm("_binary_stasetting_js_end");
const uint32_t stasetting_js_len = stasetting_js_end - stasetting_js_start;





esp_err_t get_handlerSTA_(httpd_req_t *req);
esp_err_t get_handlerSTA_Root_(httpd_req_t *req);
esp_err_t get_handlerSTA_RootJS_(httpd_req_t *req);
esp_err_t get_handlerSTA_Setting_(httpd_req_t *req);
esp_err_t get_handlerSTA_SettingJS_(httpd_req_t *req);
esp_err_t get_handlerSTA_PageSubmit_(httpd_req_t *req);

//esp_err_t get_handlersta_Websocket_(httpd_req_t *req);

void get_staUserReceiveDataUpdateTask_(void* pvParameters);
void get_staUserSendDataUpdateTask_(void* pvParameters);



class WifiSTA : public WifiEngine
	{
	public:
		WifiSTA(WifiListner * _listner, WifiMode _wifimode, const char * _pHostname, const char * _pAPName, const char * _pAPPAssword);
		virtual ~WifiSTA();

		void staUserSendDataUpdateTask();
		void staUserReceiveDataUpdateTask();




	private:


	};





#endif /* MAIN_MKII_IO_WIFI_WIFISTA_H_ */
