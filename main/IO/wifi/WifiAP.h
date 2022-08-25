/*
 * WifiAP.h
 *
 *  Created on: Aug 9, 2022
 *      Author: arnoud
 */

#ifndef MAIN_MKII_IO_WIFI_WIFIAP_H_
#define MAIN_MKII_IO_WIFI_WIFIAP_H_

#include "esp_err.h"

#include <esp_http_server.h>

#include "../../../components/wifi/WifiCtrMode.h"
#include "WifiEngine.h"

extern const uint8_t aproot_html_start[] asm("_binary_aproot_html_start");
extern const uint8_t aproot_html_end[] asm("_binary_aproot_html_end");
const uint32_t aproot_html_len = aproot_html_end - aproot_html_start;

esp_err_t get_handlerAP_Root(httpd_req_t *req);
esp_err_t get_handlerAP_PageCause(httpd_req_t *req);
esp_err_t get_handlerAP_PageSubmit(httpd_req_t *req);


class WifiAP : public WifiEngine
	{
	public:
		WifiAP(WifiListner * _listner, WifiCtrMode _wifimode, const char * _pHostname, const char * _pAPPAssword);
		virtual ~WifiAP();

	private:
	};

#endif /* MAIN_MKII_IO_WIFI_WIFIAP_H_ */
