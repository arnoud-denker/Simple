/*
 * WifiHelper.h
 *
 *  Created on: Aug 25, 2022
 *      Author: arnoud
 */

#ifndef COMPONENTS_WIFI_WIFIHELPER_H_
#define COMPONENTS_WIFI_WIFIHELPER_H_

#define DBG_WIFI 1

#ifdef DBG_WIFI
#define LOG_WIFI(format, ... ) ESP_LOG_LEVEL_LOCAL(ESP_LOG_INFO, TAG, format, ##__VA_ARGS__)
#else
#define LOG_WIFI(format, ... ) do { } while(0)
#endif





#endif /* COMPONENTS_WIFI_WIFIHELPER_H_ */
