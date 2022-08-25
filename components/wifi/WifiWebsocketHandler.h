/*
 * WebsocketHandlerSTA.h
 *
 *  Created on: May 24, 2022
 *      Author: arnoud
 */

#ifndef WIFI_WEBSOCKETHANDLER_H_
#define WIFI_WEBSOCKETHANDLER_H_

#include "alog.h"
#include "WifiConstants.h"
#include "WifiHelper.h"

#include "cJSON.h"
#include <esp_event.h>
#include <esp_log.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include "esp_netif.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"
#include <esp_http_server.h>


static const TickType_t wsSendPeriod = pdMS_TO_TICKS(1000);
static const TickType_t serverSendUpdatePeriod = pdMS_TO_TICKS(1000);
static const TickType_t serverReceiveUpdatePeriod = pdMS_TO_TICKS(1000);

struct WS_data_holder
		{
		httpd_handle_t wssta_handle = NULL;
		int wssta_sockfd = 0;
		};

typedef struct xWSsendMessage
	{
	char senddata[256];
	} wssend_msg;

typedef struct xWSreceiveMessage
	{
	char receiveddata[256];
	} wsreceive_msg;

//===========================================

esp_err_t get_handlersta_Websocket_(httpd_req_t *req);
void sendDataToServertask_(void* pvParameters);

//===========================================

class WifiWebsocketHandler
	{
	public:
		WifiWebsocketHandler();
		virtual ~WifiWebsocketHandler();

		void wifi_startws();

		esp_err_t wifi_registerWsPathServerAndStartUserupdateTask(const char *pUri, httpd_handle_t server,
								TaskFunction_t _sendUpdateTask, const char * const _pSendUpdateTaskName,
								TaskFunction_t _receiveUpdateTask, const char * const _pReceiveUpdateTaskName,
								void * const pvParameters);

		void sendDataToServerTask();

		QueueHandle_t get_wsReceiveQueuHandle();
		QueueHandle_t get_wsSendQueuHandle();

		httpd_handle_t get_wssta_handle();
		void set_wssta_handle(httpd_handle_t _handle);

		int get_wssta_sockfd();
		void set_wssta_sockfd(int _sock);

		esp_err_t handlews(httpd_req_t *req);

	protected:


	private:
		QueueHandle_t xreceiveQueue;
		QueueHandle_t xsendQueue;

		struct WS_data_holder ws_data_holder;

		TaskHandle_t xSendServerTaskHande = NULL;
		TaskHandle_t xSendTaskHande = NULL;
		TaskHandle_t xReceiveTaskHande = NULL;

		bool enableWS = false;

		BaseType_t wifi_createSendDataServerTask(TaskFunction_t pvTaskCode, const char * const pcName, void * const pvParameters);
	};

#endif /* WIFI_WEBSOCKETHANDLER_H_ */
