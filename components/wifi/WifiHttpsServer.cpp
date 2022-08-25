/*
 * WifiSTAServer.cpp
 *
 *  Created on: Jul 28, 2022
 *      Author: arnoud
 */

#include "WifiHttpsServer.h"

#define TAG "WIFISERVER"

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

esp_err_t get_handler_404_(httpd_req_t *req, httpd_err_code_t err)
	{
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "404, can't find page");
    return ESP_FAIL;
	}

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

WifiHttpsServer::WifiHttpsServer()
	{
	}

WifiHttpsServer::~WifiHttpsServer()
	{
	if (server != NULL)
		{
		wifi_stopWebserver();
		}
	}

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

esp_err_t WifiHttpsServer::wifi_startWebserver(bool _enableWS)
	{
	LOG_SERVER("startWebserver");

#ifdef CONFIG_ESP_HTTPS_SERVER_ENABLE
	httpd_ssl_config_t conf;// = HTTPD_SSL_CONFIG_DEFAULT();
	conf.httpd.task_priority      = tskIDLE_PRIORITY+5;
	conf.httpd.stack_size         = 10240;
	conf.httpd.core_id            = tskNO_AFFINITY;
	conf.httpd.server_port        = 0;
	conf.httpd.ctrl_port          = 32768;
	conf.httpd.max_open_sockets   = MAX_STAHTTPS_CLIENTS;
	conf.httpd.max_uri_handlers   = MAX_URI_HANDLERS;
	conf.httpd.max_resp_headers   = 4;
	conf.httpd.backlog_conn       = 5;
	conf.httpd.lru_purge_enable   = true;
	conf.httpd.recv_wait_timeout  = 5;
	conf.httpd.send_wait_timeout  = 5;
	conf.httpd.global_user_ctx = NULL;
	conf.httpd.global_user_ctx_free_fn = NULL;
	conf.httpd.global_transport_ctx = NULL;
 	conf.httpd.global_transport_ctx_free_fn = NULL;

    conf.httpd.open_fn = wss_open_fd;
    conf.httpd.close_fn = wss_close_fd;
 //	conf.httpd.open_fn = NULL;
 //	conf.httpd.close_fn = NULL;
 	conf.httpd.uri_match_fn = httpd_uri_match_wildcard;

    conf.cacert_pem = cacert_pem_start;
    conf.cacert_len = cacert_pem_end - cacert_pem_start;

    conf.client_verify_cert_pem = NULL;
    conf.client_verify_cert_len = 0;

    conf.prvtkey_pem = prvtkey_pem_start;
    conf.prvtkey_len = prvtkey_pem_end - prvtkey_pem_start;

    conf.transport_mode = HTTPD_SSL_TRANSPORT_SECURE;
    conf.port_secure = 443;
    conf.port_insecure = 80;
    conf.session_tickets = false;
    conf.user_cb = NULL;

    esp_err_t ret = httpd_ssl_start(&server, &conf);
    if (ESP_OK != ret)
     	{
        ERR("Error starting server!");
        return ESP_FAIL;
     	}

#else
	  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
	  config.lru_purge_enable = true;

	  // Start the httpd server
	  LOG("Starting server on port: '%d'", config.server_port);

	  if (httpd_start(&server, &config) == ESP_FAIL)
	  	  {
		  ERR("Failed to start HTTPD");
		  return ESP_FAIL;
	  	  }

#endif
	  // Set URI handlers
	  LOG("Registering default URI handlers");
	  if (httpd_register_err_handler(server, HTTPD_404_NOT_FOUND, get_handler_404_ ) == ESP_OK)
	  	  {
		  if (_enableWS == true)
		      {
			  wifi_startws();
			  }
	  	  return ESP_OK;
	  	  }

	ERR("Failed to register default URI handlers");
	return ESP_FAIL;
	}

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

esp_err_t WifiHttpsServer::wifi_stopWebserver()
	{
	if (server != nullptr)
		{
		#ifdef ssl
			return httpd_ssl_stop(server);
		#else
			return httpd_stop(server);
		#endif
		}
	return ESP_FAIL;
	}

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------
/*
 register WS URI path. accept WS only when WS is enabled and starts ws update task
 */
//esp_err_t WifiHttpsServer::wifi_registerWsPathAndStartUserupdateTask(const char *pUri, TaskFunction_t pvTaskCode, const char * const pcName, void * const pvParameters)
esp_err_t WifiHttpsServer::wifi_registerWsPathAndStartUserupdateTask(
		const char * _pUri,
		TaskFunction_t _sendUpdateTask, const char * const _pSendUpdateTaskName,
		TaskFunction_t _receiveUpdateTask, const char * const _pReceiveUpdateTaskName,
		void * const _pvParameters)
	{
	if (server != nullptr)
		{
		return wifi_registerWsPathServerAndStartUserupdateTask( _pUri, server,
																_sendUpdateTask, _pSendUpdateTaskName,
																_receiveUpdateTask, _pReceiveUpdateTaskName,
																_pvParameters);
		}

	return ESP_FAIL;
	}

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

/*
 register HTTP URI path.
 */
esp_err_t WifiHttpsServer::wifi_registerHttpPath(const char *pUri, request_handler_t _fn, httpd_method_t _method)
	{
	esp_err_t returnvalue = ESP_FAIL;

	if (server != nullptr)
		{
		httpd_uri_t path = {};
		path.uri = pUri;
		path.method = _method;
		path.handler = _fn;
		path.user_ctx = this;
		path.is_websocket = false;
		path.handle_ws_control_frames = false;
		returnvalue = httpd_register_uri_handler(server, &path);
		}

	if (returnvalue == ESP_FAIL)
		{
		ERR("registering uri: %s FAILED", pUri);
		}
	else
		{
		LOG("registering uri: %s OK", pUri);
		}

	return returnvalue;
	}

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------
/*
 UNregister HTTP URI path.
 */
esp_err_t WifiHttpsServer::wifi_unregisterHttpPath(const char *_pUri, httpd_method_t method)
	{
	if (server != nullptr)
		{
		return httpd_unregister_uri_handler(server, _pUri, method);
		}
	return ESP_FAIL;
	}

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

void WifiHttpsServer::wifi_scanForWifiAPs()	// only in STA mode??
	{
//	LOG("scanForWifiAPs");
//
//    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
//
//    wifi_config_t wifiSTA_config;
//    strcpy((char *)wifiSTA_config.sta.ssid, "");
//    strcpy((char *)wifiSTA_config.sta.password, "");
//    wifiSTA_config.sta.threshold.authmode = WIFI_AUTH_OPEN;
//    wifiSTA_config.sta.pmf_cfg.capable = true;
//    wifiSTA_config.sta.pmf_cfg.required = false;
//
//    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifiSTA_config));
//    ESP_ERROR_CHECK(esp_wifi_start());
//
//    wifi_scan_config_t scan_conf;
//    memset(&scan_conf, 0, sizeof(scan_conf));
//	scan_conf.show_hidden = true;
//
//	esp_err_t rc = esp_wifi_scan_start(&scan_conf, true);
//	if (rc != ESP_OK)
//		{
//		ERR("esp_wifi_scan_start: %d", rc);
//		return;
//		}
//
//	uint16_t apCount;  // Number of access points available.
//	rc = esp_wifi_scan_get_ap_num(&apCount);
//	if (rc != ESP_OK)
//		{
//		ERR("esp_wifi_scan_get_ap_num: %d", rc);
//		return;
//		}
//	else
//		{
//		DBG("Count of found access points: %d", apCount);
//		}
//
//	wifi_ap_record_t* list = (wifi_ap_record_t*) malloc(sizeof(wifi_ap_record_t) * apCount);
//	if (list == nullptr)
//		{
//		ERR("Failed to allocate memory");
//		return;
//		}
//
//	esp_wifi_scan_get_ap_records(&apCount, list);
//
//	free(foundAPs);	// clear prevous
//	foundAPs =  (char*) malloc(apCount * MEMBER_SIZE(wifi_ap_record_t, ssid));	// reserve mem (max as needed for SSID
//
//	string tmp;
//
//	for (uint16_t i = 0; i < apCount; i++)
//		{
//		LOG("Found ssid: %s", list[i].ssid);
//
//		char * ssid = (char *) list[i].ssid;
//
//		if (strcmp(ssid, "") != 0)
//			{
//			tmp.append("<option value='");
//			tmp.append(ssid);
//			tmp.append("'>");
//			}
//		}
//
//	strcpy(foundAPs, tmp.c_str());
//
//	free(list);   // Release the storage allocated to hold the records.
//
//	LOG("SCAN READY");
	}

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

