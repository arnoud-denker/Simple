/*
 * WebsocketHandlerSTA.cpp
 *
 *  Created on: May 24, 2022
 *      Author: arnoud
 */

#include "WifiWebsocketHandler.h"

#define TAG "WS"


//static char readBuf[readBufSize];


void socket_close_cleanup(void* context)
	{
	LOG("Lost our ws_instance.");

//	ws_data_holder.handle = NULL;
//	ws_data_holder.sockfd = 0;

// // if (pdPASS != xTimerStop(xWebsockTimeout, 0)) {
//  //  ERR("Failed to stop websock timeout timer");
// // }
	}

//==========================================================================
//==========================================================================
//==========================================================================

WifiWebsocketHandler::WifiWebsocketHandler()
	{
	ws_data_holder.wssta_handle = NULL;
	ws_data_holder.wssta_sockfd = 0;
	}

//==========================================================================
//==========================================================================
//==========================================================================

WifiWebsocketHandler::~WifiWebsocketHandler()
	{
	if( xSendServerTaskHande != NULL )
		{
		vTaskDelete( xSendServerTaskHande );
		}

	if (xSendTaskHande != NULL)
		{
		vTaskDelete( xSendTaskHande );
		}

	if (xReceiveTaskHande != NULL)
		{
		vTaskDelete( xReceiveTaskHande );
		}
	}

//===========================================
//===========================================
//===========================================

void WifiWebsocketHandler::wifi_startws()
	{
	enableWS = true;
	if (wifi_createSendDataServerTask(sendDataToServertask_, "sendDataToServertask", this) != pdPASS)
		{
		ERR("Unable to start task: sendDataToServertask");
		}
	}

void sendDataToServertask_(void* pvParameters)
	{
	WifiWebsocketHandler* pWebsockHandler = reinterpret_cast<WifiWebsocketHandler*>(pvParameters); 	//obtain the instance pointer
	pWebsockHandler->sendDataToServerTask(); 														//dispatch to the member function, now that we have an instance pointer
	}

//===========================================
//===========================================
//===========================================

void WifiWebsocketHandler::sendDataToServerTask() //char * pDataToSend)
	{
	xsendQueue = xQueueCreate(1, sizeof(wssend_msg));

	xWSsendMessage message;

	while (true)
		{
		if(get_wssta_handle() != NULL && xQueueReceive( xsendQueue, &message, ( TickType_t ) 10 ) == pdPASS)
			{
			httpd_ws_frame_t ws_frame = 	{
											.final = true,
											.fragmented = false,
											.type = HTTPD_WS_TYPE_TEXT,
											.payload = (uint8_t*)message.senddata,
											.len = strlen(message.senddata)
											};

			if (httpd_ws_send_frame_async(get_wssta_handle(), get_wssta_sockfd(), &ws_frame ) == ESP_FAIL)
 				{
				ERR("Failed to send data");
 				}
			else
 				{
				LOG_WIFI("WS SEND OK");
 				}
			}

		vTaskDelay(wsSendPeriod);
		}
	}

//===========================================
//===========================================
//===========================================

BaseType_t WifiWebsocketHandler::wifi_createSendDataServerTask(TaskFunction_t pvTaskCode, const char * const pcName, void * const pvParameters)
	{
	LOG("Starting %s task", pcName);
	return xTaskCreate(pvTaskCode, pcName, 1024*4, pvParameters, 19, &xSendServerTaskHande);
	}

//===========================================
//===========================================
//===========================================

httpd_handle_t WifiWebsocketHandler::get_wssta_handle() { return ws_data_holder.wssta_handle; }
void WifiWebsocketHandler::set_wssta_handle(httpd_handle_t _handle) { ws_data_holder.wssta_handle = _handle; }

int WifiWebsocketHandler::get_wssta_sockfd() { return ws_data_holder.wssta_sockfd; }
void WifiWebsocketHandler::set_wssta_sockfd(int _sockfd) { ws_data_holder.wssta_sockfd = _sockfd; }

//===========================================
//===========================================
//===========================================

QueueHandle_t WifiWebsocketHandler::get_wsReceiveQueuHandle()
	{
	return xreceiveQueue;
	}

QueueHandle_t WifiWebsocketHandler::get_wsSendQueuHandle()
	{
	return xsendQueue;
	}

//===========================================
//===========================================
//===========================================

esp_err_t get_handlersta_Websocket_(httpd_req_t *req)
	{
	WifiWebsocketHandler* pWifiSTA = reinterpret_cast<WifiWebsocketHandler*>(req->user_ctx); 	//obtain the instance pointer
	return pWifiSTA->handlews(req);
	}

//===========================================
//===========================================
//===========================================

//esp_err_t WifiWebsocketHandler::wifi_registerWsPathServerAndStartUserupdateTask(const char *pUri, httpd_handle_t server, TaskFunction_t pvTaskCode, const char * const pcName, void * const pvParameters)
esp_err_t WifiWebsocketHandler::wifi_registerWsPathServerAndStartUserupdateTask(const char *pUri, httpd_handle_t server,
			TaskFunction_t _sendUpdateTask, const char * const _pSendUpdateTaskName,
			TaskFunction_t _receiveUpdateTask, const char * const _pReceiveUpdateTaskName,
			void * const pvParameters)
	{
	if (enableWS == false)
		{
		ERR("Can't register WS uri, WS not inited");
		return ESP_FAIL;
		}

	if (server != NULL)
		{
		httpd_uri_t path = {};
		path.uri = pUri;
		path.method = HTTP_GET;
		path.handler = get_handlersta_Websocket_;
		path.user_ctx = this;
		path.is_websocket = true;
		path.handle_ws_control_frames = false;

		if (httpd_register_uri_handler(server, &path) == ESP_OK)
			{
			if (_sendUpdateTask != NULL)
				{
				if (xTaskCreate(_sendUpdateTask, _pSendUpdateTaskName, 1024*4, pvParameters, 19, &xSendTaskHande) == pdPASS)
					{
					LOG("Started task: %s", _pSendUpdateTaskName);
					}
				else
					{
					ERR("Unable to start task: %s", _pSendUpdateTaskName);
					}
				}

			if (_receiveUpdateTask != NULL)
				{
				if (xTaskCreate(_receiveUpdateTask, _pReceiveUpdateTaskName, 1024*4, pvParameters, 19, &xSendTaskHande) == pdPASS)
					{
					LOG("Started task: %s", _pReceiveUpdateTaskName);
					}
				else
					{
					ERR("Unable to start task: %s", _pReceiveUpdateTaskName);
					}
				}
			}
		return ESP_OK;
		}

	ERR("Failed to register WS and start its tasks");
	return ESP_FAIL;
	}

//===========================================
//===========================================
//===========================================

esp_err_t WifiWebsocketHandler::handlews(httpd_req_t *req)
	{
	LOG("in handlews");// %d ",  get_sockfd() );

	if (req->method == HTTP_GET)
  	  	{
		LOG_WIFI("Handshake done, the new connection was opened");
		return ESP_OK;
  	  	}

	if (get_wssta_handle() == NULL) // create msg sender if none excist
		{
		LOG_WIFI("Open WS detected");

		set_wssta_handle(req->handle);
		set_wssta_sockfd(httpd_req_to_sockfd(req));
		req->sess_ctx = (void*)1; // Set to nonzero otherwise free_ctx won't get called.
		req->free_ctx = socket_close_cleanup;
//
////		if (xTimerStart(xWebsockTimeout, 0) != pdPASS)
////			{
////			ERR("Failed to start websock timeout timer");
////			return ESP_FAIL;
////			}
		}


	if (xreceiveQueue == NULL)
		{
		xreceiveQueue = xQueueCreate(1, sizeof(wsreceive_msg));
		}

	if (xreceiveQueue != NULL)
		{
		wsreceive_msg receivemessage;

		httpd_ws_frame_t ws_pkt;
		memset(&ws_pkt, 0, sizeof(httpd_ws_frame_t));
		ws_pkt.type = HTTPD_WS_TYPE_TEXT;
		ws_pkt.payload = (uint8_t*)receivemessage.receiveddata;
		if (httpd_ws_recv_frame(req, &ws_pkt, sizeof(receivemessage.receiveddata) ) == ESP_OK)
			{
			if (xQueueOverwrite(xreceiveQueue, &receivemessage ) == pdFAIL)
				{
				ERR("Write into queui failed");
				}
			else
				{
				LOG_WIFI("Put into queui");
				}
			}
		}
	else
		{
		ERR("Receivequeu == NULL");
		}

	return ESP_OK;
	}
