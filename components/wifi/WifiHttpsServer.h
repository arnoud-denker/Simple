/*
 * WifiSTAServer.h
 *
 *  Created on: Jul 28, 2022
 *      Author: arnoud
 */

#ifndef WIFI_WIFISERVER_H_
#define WIFI_WIFISERVER_H_

#include "WifiHelper.h"
#include "WifiConstants.h"
#include "WifiWebsocketHandler.h"

#include "sdkconfig.h"

#ifdef CONFIG_ESP_HTTPS_SERVER_ENABLE
	#include <esp_https_server.h>
#else
	#include <esp_http_server.h>
#endif

#include <esp_err.h>


typedef esp_err_t (*request_handler_t)(httpd_req_t *r);

#define mime_html	"text/html"
#define mime_css	"text/css"
#define mine_js		"text/javascript"
#define mine_icon	"text/x-icon"


#define DBG_SERVER 1

#ifdef DBG_SERVER
#define LOG_SERVER(format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_INFO, TAG, format, ##__VA_ARGS__)
#else
#define LOG_SERVER(format, ... ) do { } while(0)
#endif


extern const unsigned char cacert_pem_start[] asm("_binary_cacert_pem_start");
extern const unsigned char cacert_pem_end[]   asm("_binary_cacert_pem_end");

extern const unsigned char prvtkey_pem_start[] asm("_binary_prvtkey_pem_start");
extern const unsigned char prvtkey_pem_end[]   asm("_binary_prvtkey_pem_end");


class WifiHttpsServer : public WifiWebsocketHandler
	{
	public:
		WifiHttpsServer();
		virtual ~WifiHttpsServer();

		esp_err_t wifi_startWebserver(bool _enableWS);
		esp_err_t wifi_stopWebserver();

		//esp_err_t wifi_registerWsPathAndStartUserupdateTask(const char *pUri, TaskFunction_t pvTaskCode, const char * const pcName, void * const pvParameters);
		esp_err_t wifi_registerWsPathAndStartUserupdateTask(
				const char * _pUri,
				TaskFunction_t _sendUpdateTask, const char * const _pSendUpdateTaskName,
				TaskFunction_t _receiveUpdateTask, const char * const _pReceiveUpdateTaskName,
				void * const _pvParameters);



		esp_err_t wifi_registerHttpPath(const char *_pUri, request_handler_t _fn, httpd_method_t _method);
		esp_err_t wifi_unregisterHttpPath(const char *_pUri, httpd_method_t method);






////
////		//httpd_handle_t getHandle();
////
////
////		bool hasKey(httpd_req_t *req, const char* key);
////		esp_err_t getKey(httpd_req_t *req, const char* key, char* val, size_t len);
////		bool hasQuery(httpd_req_t *req);
////		int getQuery(httpd_req_t *req, char* buf, size_t len);
////		int getHeader(httpd_req_t *req, const char *field, char *val, size_t val_size);
////		esp_err_t setStatus(httpd_req_t *req, const char *status);
////		esp_err_t setContentType(httpd_req_t *req, const char *type);
////		esp_err_t setHeader(httpd_req_t *req, const char *field, const char *value);
////
////		esp_err_t send(httpd_req_t *req, const char *buf, ssize_t buf_len);
////		esp_err_t sendText(httpd_req_t *req, const char *str);
////		esp_err_t sendChunk(httpd_req_t *req, const char *buf, ssize_t buf_len = -1);
////
////		esp_err_t wsGetPacket(httpd_req_t *req, httpd_ws_frame_t* ws_pkt, void* buf, size_t max_len);
////		esp_err_t wsSendPacket(httpd_req_t *req, httpd_ws_frame_t* ws_pkt);
////		esp_err_t wsSendAsync(int fd, httpd_ws_frame_t* ws_pkt);
////		httpd_ws_frame_t* buildPacket(const void* payload, size_t len, httpd_ws_type_t type = HTTPD_WS_TYPE_TEXT, bool fragmented = false, bool final = true);
////
////		esp_err_t sendError(httpd_req_t *req, httpd_err_code_t error, const char *usr_msg = NULL);
////
////
////		DataEngine * get_Dataengine();
////

	private:
		bool enableWS = false;

		void wifi_scanForWifiAPs();

		httpd_handle_t server = NULL;

	//	wss_keep_alive_t keep_alive = NULL;
	};


#endif /* WIFI_WIFISERVER_H_ */
