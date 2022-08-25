#include "WifiEngine.h"

#include "alog.h"

#define TAG "WIFIENGINE"

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------
//todo fatal abort
WifiEngine::WifiEngine(WifiListner * _pWifiListner, WifiCtrMode _wifimode, const char * _pHostname, const char * _pAPName, const char * _pAPPassword)
	{
	if (_wifimode == WifiCtrMode::WifiAP)
		{
		ERR("To many parameters for AP mode");
	//	fatal_abort(0x28e44332);
		return;
		}

	pWifiListner = _pWifiListner;
	wifimode = _wifimode;
	pHostname = _pHostname;
	pAPName = _pAPName;
	pPassword = _pAPPassword;

	pIp4address = nullptr;

	wifi_isstarted = false;
	wifi_connected = false;

	numberOfsSTAConnectionRetries = 0;

	pInstance_got_ip = new esp_event_handler_instance_t();
	pInstance_any_id = new esp_event_handler_instance_t();
	}

//----------------------------------------------------


////todo fatal_abort
WifiEngine::WifiEngine(WifiListner * _pWifiListner, WifiCtrMode _wifimode, const char * _pHostname, const char * _pAPPassword)
	{
	if (_wifimode == WifiCtrMode::WifiSTA)
		{
		ERR("Not enough parameters for STA mode");
		//fatal_abort(0x28e44332);
		return;
		}

	pWifiListner = _pWifiListner;
	wifimode = _wifimode;
	pHostname = _pHostname;
	pAPName = nullptr;
	pPassword = _pAPPassword;

	pIp4address = new esp_netif_ip_info_t();
    memset(pIp4address, 0, sizeof(esp_netif_ip_info_t));

    pIp4address->ip.addr = esp_ip4addr_aton((const char *) CONFIG_AP_IP);
    pIp4address->gw.addr = esp_ip4addr_aton((const char *) CONFIG_AP_GATEWAY);
    pIp4address->netmask.addr = esp_ip4addr_aton((const char *) CONFIG_AP_NETMASK);

	wifi_isstarted = false;
	wifi_connected = false;

	numberOfsSTAConnectionRetries = 0;

	pInstance_got_ip = new esp_event_handler_instance_t();
	pInstance_any_id = new esp_event_handler_instance_t();
	}

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

WifiEngine::~WifiEngine() // will never come here?
	{
	delete(pInstance_got_ip);
	delete(pInstance_any_id);
	}

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

////todo
//const char * WifiEngine::wifi_get_foundAPs()
//	{
//	if (pWifiEngineAP != nullptr)
//		{
//		return pWifiEngineAP->wifiAP_get_foundAPs();
//		}
////	else if (wifiEngineSTA != nullptr)
////		{
////		return wifiEngineSTA->wifiSTA_get_foundAPs();
////		}
//	else
//		{
//		ERR("wifi_get_foundAPs not availble");
//		}
//
//	return "";
//	}
//

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

/* STATIC */
void WifiEngine::wifi_event_handler(void* ctx, esp_event_base_t event_base, int32_t event_id, void* event_data)
	{
	WifiEngine* pWiFi = (WifiEngine*) ctx;

	if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_WIFI_READY)
		{
		LOG_WIFI( "WIFI_EVENT_WIFI_READY");
		}
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    	{
    	LOG_WIFI("WIFI_EVENT_STA_START");
        esp_wifi_connect();
    	}
	else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_STOP)
		{
		LOG_WIFI("WIFI_EVENT_STA_STOP");
		}
	else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_CONNECTED)
		{
		LOG_WIFI("WIFI_EVENT_STA_CONNECTED");
		pWiFi->wifi_set_connectionStatus(true);
		}
	else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
		{
		LOG_WIFI("WIFI_EVENT_STA_DISCONNECTED");
		pWiFi->wifi_set_connectionStatus(false);

		if (pWiFi->wifi_get_numberOfSTAConnectionRetries() < MAX_STACONNECTIONS_RETRY)
			{
		    esp_wifi_connect();
		    pWiFi->wifi_increase_numberOfSTAConnectionRetries();
		    LOG_WIFI("retry to connect to the AP");
		    }
		else
			{
			ERR("connect to the AP fail");
			}
		}
	else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_START)
		{
		LOG_WIFI("AP started");
		}
	else if (event_base == WIFI_EVENT && event_id ==  WIFI_EVENT_AP_STOP)
		{
		LOG_WIFI("AP Stopped");
		}
	else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
		{
	    ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
	    LOG_WIFI("STA_GOT_IP ip:" IPSTR, IP2STR(&event->ip_info.ip));
	    pWiFi->wifi_sta_got_ip(* (&event->ip_info.ip));
	    pWiFi->wifi_sta_initiated();
		}
	else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_PROBEREQRECVED)
		{
		LOG_WIFI("station WIFI_EVENT_AP_PROBEREQRECVED");
		}
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STACONNECTED)
    	{
    	LOG_WIFI( "AP_STA Connected");
		wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
		LOG_WIFI("station " MACSTR " joined, AID=%d",MAC2STR(event->mac), event->aid);
		pWiFi->wifi_set_connectionStatus(true);
    	}
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_AP_STADISCONNECTED)
    	{
    	DBG("AP_STA Disconnected");
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        DBG("station " MACSTR" leave, AID=%d", MAC2STR(event->mac), event->aid);
        pWiFi->wifi_set_connectionStatus(false);
    	}
	else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_WIFI_READY)
		{
		LOG_WIFI( "Wifi ready");
		}
	 else if (event_base == WIFI_EVENT &&event_id == WIFI_EVENT_SCAN_DONE)
		 {
		 LOG_WIFI( "Wifi Scan done");
		 }
	 else if (event_base == IP_EVENT && event_id == IP_EVENT_AP_STAIPASSIGNED)
		{
		LOG_WIFI( "AP_STA ip assigned");
		pWiFi->wifi_ap_got_ip();
		pWiFi->wifi_ap_initiated();
		}
	else
		{
		LOG_WIFI("Unknown EVENT: %d", event_id);
		return;
		}

	if (event_base == WIFI_EVENT)
		{
		pWiFi->wifi_set_currentWifiEvent(event_id);
		}
	}

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

//todo
esp_err_t WifiEngine::wifi_init()
	{
	LOG_WIFI("wifi_init %s", get_wifimode_str(wifimode) );

	esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    	{
    	//todo ? mag ik dit doen?
    	ESP_ERROR_CHECK(nvs_flash_erase());
    	ret = nvs_flash_init();
    	}

    if (esp_netif_init() != ESP_OK)
    	{
    	ERR("Failed to init netif");
    	return ESP_FAIL;
    	}

    if (esp_event_loop_create_default() != ESP_OK)
    	{
    	ERR("Failed to create eventloop");
    	return ESP_FAIL;
    	}

    esp_netif_t* pNetif = nullptr;
	if (wifimode == WifiCtrMode::WifiAP)
		{
		pNetif = esp_netif_create_default_wifi_ap();
		}
	else if (wifimode == WifiCtrMode::WifiSTA)
		{
		pNetif = esp_netif_create_default_wifi_sta();
		}
	else
		{
		ERR("Can't set wifimode, unknown wifi mode");
		return ESP_FAIL;
		}

	wifi_init_config_t cfg; // = WIFI_INIT_CONFIG_DEFAULT();
	cfg.event_handler = &esp_event_send_internal;
	cfg.osi_funcs = &g_wifi_osi_funcs;
	cfg.wpa_crypto_funcs = g_wifi_default_wpa_crypto_funcs;
	cfg.static_rx_buf_num = CONFIG_ESP32_WIFI_STATIC_RX_BUFFER_NUM;
	cfg.dynamic_rx_buf_num = CONFIG_ESP32_WIFI_DYNAMIC_RX_BUFFER_NUM;
	cfg.tx_buf_type = CONFIG_ESP32_WIFI_TX_BUFFER_TYPE;
	cfg.static_tx_buf_num = WIFI_STATIC_TX_BUFFER_NUM;
	cfg.dynamic_tx_buf_num = WIFI_DYNAMIC_TX_BUFFER_NUM;
	cfg.cache_tx_buf_num = WIFI_CACHE_TX_BUFFER_NUM;
	cfg.csi_enable = WIFI_CSI_ENABLED;
	cfg.ampdu_rx_enable = WIFI_AMPDU_RX_ENABLED;
	cfg.ampdu_tx_enable = WIFI_AMPDU_TX_ENABLED;
	cfg.amsdu_tx_enable = WIFI_AMSDU_TX_ENABLED;
	cfg.nvs_enable = WIFI_NVS_ENABLED;
	cfg.nano_enable = WIFI_NANO_FORMAT_ENABLED;
	cfg.rx_ba_win = WIFI_DEFAULT_RX_BA_WIN;
	cfg.wifi_task_core_id = WIFI_TASK_CORE_ID;
	cfg.beacon_max_len = WIFI_SOFTAP_BEACON_MAX_LEN;
	cfg.mgmt_sbuf_num = WIFI_MGMT_SBUF_NUM;
	cfg.feature_caps = g_wifi_feature_caps;
	cfg.sta_disconnected_pm = false;//WIFI_STA_DISCONNECTED_PM_ENABLE;
	cfg.magic = WIFI_INIT_CONFIG_MAGIC;
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));


//	if (m_eventLoopStarted)
//		{
//		esp_event_loop_set_cb(WifiEngine::eventHandler, this);   // Returns the old handler.
//		}
//	else
//		{
//		esp_err_t errRc = esp_event_loop_init(WifiEngine::eventHandler, this);  // Initialze the event handler.
//		if (errRc != ESP_OK)
//			{
//		//	ERR("esp_event_loop_init: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
//			abort();
//			}
//		m_eventLoopStarted = true;
//		}

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,						//[in] the base ID of the event to register the handler for
                                                        ESP_EVENT_ANY_ID,				//[in] the ID of the event to register the handler for
														WifiEngine::wifi_event_handler,	//[in] the handler function which gets called when the event is dispatched
                                                        this,							//[in] data, aside from event data, that is passed to the handler when it is called
														pInstance_got_ip							// [out] An event handler instance object related to the registered event handler and data, can be NULL. This needs to be kept if the specific callback instance should be unregistered before deleting the whole event loop. Registering the same event handler multiple times is possible and yields distinct instance objects. The data can be the same for all registrations. If no unregistration is needed, but the handler should be deleted when the event loop is deleted, instance can be NULL.
														));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
														WifiEngine::wifi_event_handler,
                                                        this,
														pInstance_got_ip
														));

	if (wifimode == WifiCtrMode::WifiAP)
		{
		esp_netif_dhcps_stop(pNetif);
		esp_netif_set_ip_info(pNetif, pIp4address);
		esp_netif_dhcps_start(pNetif);

		wifi_config_t wifi_config;
		strcpy((char *)wifi_config.ap.ssid, pHostname);
		wifi_config.ap.ssid_len = (uint8_t) strlen(pHostname);

		strcpy((char *)wifi_config.ap.password, (char *) pPassword);
		wifi_config.ap.channel = 7;
		wifi_config.ap.max_connection = 2;		// todo enough?
		wifi_config.ap.authmode = WIFI_AUTH_OPEN;
		wifi_config.ap.pairwise_cipher = WIFI_CIPHER_TYPE_NONE;

	    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
	    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
	    ESP_ERROR_CHECK(esp_wifi_start());

//      captdnsInit();
//	    wifiAP_startWebserver();
		}
	else if (wifimode == WifiCtrMode::WifiSTA)
		{
	    wifi_config_t wifiSTA_config = {};

	    strcpy((char *)wifiSTA_config.sta.ssid, pAPName);
	    strcpy((char *)wifiSTA_config.sta.password, pPassword);
	    wifiSTA_config.sta.pmf_cfg.capable = false;
	    wifiSTA_config.sta.pmf_cfg.required = false;
	    wifiSTA_config.sta.scan_method = WIFI_ALL_CHANNEL_SCAN;
	    wifiSTA_config.sta.sort_method = WIFI_CONNECT_AP_BY_SIGNAL;
		wifiSTA_config.sta.threshold.rssi = -127;
		wifiSTA_config.sta.threshold.authmode = WIFI_AUTH_WPA_PSK; //WIFI_AUTH_OPEN;

		ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
		ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifiSTA_config) );
		ESP_ERROR_CHECK(esp_wifi_start() );


	// todo include shutdown handler
	//   ESP_ERROR_CHECK(esp_register_shutdown_handler(&stop));

	//    server = wifiSTA_startWebserver();

	//    xTaskCreate(&wifiSTA_staticUpdate_task,"count_task",6000,NULL,2,&TaskHandle_3);
		}
	else
		{

		return ESP_FAIL;
		}


	esp_netif_set_hostname(pEsp_netif_t, pHostname);

	 //  pWifiabp2->start_udpBroadcast();
	// startserver

	wifi_isstarted = true;
	LOG_WIFI("WIFI RUNNING");

	return ESP_OK;
	}

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

//todo
esp_err_t WifiEngine::wifi_shutdown()
	{
	if (wifi_isstarted == true)
		{
	////   httpd_ssl_stop(server);
		esp_wifi_disconnect();
		return esp_wifi_stop();
		}

    ESP_ERROR_CHECK(esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, * pInstance_got_ip));
    ESP_ERROR_CHECK(esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, * pInstance_any_id));

	return ESP_OK;
	}

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

bool WifiEngine::wifi_get_isstarted()
	{
	return wifi_isstarted;
	}

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

bool WifiEngine::wifi_get_connectionStatus()
	{
	return wifi_connected;
	}

void WifiEngine::wifi_set_connectionStatus(bool _stat)
	{
	wifi_connected = _stat;
	}

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

void WifiEngine::wifi_sta_got_ip(esp_ip4_addr_t ip)
	{
	pWifiListner->wifi_got_ip(ip);
	numberOfsSTAConnectionRetries = 0;
	}


void WifiEngine::wifi_ap_got_ip()
	{
	if (pIp4address != nullptr)
		{
		pWifiListner->wifi_got_ip(pIp4address->ip);
		}
	numberOfsSTAConnectionRetries = 0;
	}


/* callback when STA wifi is ininited */
void WifiEngine::wifi_sta_initiated()
	{
	pWifiListner->wifi_sta_initiated();
	}

/* callback when AP wifi is ininited */
void WifiEngine::wifi_ap_initiated()
	{
	pWifiListner->wifi_ap_initiated();
	}


//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

int WifiEngine::wifi_get_numberOfSTAConnectionRetries()
	{
	return numberOfsSTAConnectionRetries;
	}

void WifiEngine::wifi_increase_numberOfSTAConnectionRetries()
	{
	numberOfsSTAConnectionRetries++;
	}

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

void WifiEngine::wifi_set_currentWifiEvent(int32_t _wifiEvent)
	{
	pWifiListner->wifi_set_currentWifiEvent(_wifiEvent);
	}

//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

const char * WifiEngine::get_wifimode_str(WifiCtrMode _mode)
	{
	if (_mode == WifiCtrMode::WifiAP)
		return "WifiAP";
	else if (_mode == WifiCtrMode::WifiSTA)
		return "WifiSTA";
	return "Unknown";
	}
