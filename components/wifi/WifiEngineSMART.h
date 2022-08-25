#ifndef WIFI_WIFIENGINEABP2_H_
#define WIFI_WIFIENGINEABP2_H_

//#include "global.h"
//#include "global_lib.h"
//#include "comm.h"
//#include "comm_lib.h"
//
//#include "linkintf.h"
//#include "wificonn.h"
//#include "lwip/sockets.h"
//#include <string.h>
//#include "freertos/FreeRTOS.h"
//#include "freertos/task.h"
//#include "esp_system.h"
//#include "esp_wifi.h"
//#include "esp_event.h"
//#include "nvs_flash.h"
//#include "lwip/err.h"
//#include "lwip/sys.h"
//#include "crc32.h"
//#include "console.h"
//#include "freertos/timers.h"
//#include "lwip/sockets.h"
////
//
//
//class WifiEngineSMART
//	{
//	public:
//		WifiEngineSMART();
//		virtual ~WifiEngineSMART();
//		WifiEngineSMART* getInstance();
//
//		void start_udpBroadcast();
//		void start_abp2_server();
//
//		void shutdownAllTask();
//
////		static void wifiABP2_static_udp_tasks(void *pvParameter);
////		void wifiABP2_udp_tasks();
//
//
//	private:
//		static WifiEngineSMART * inst_;   // The one, single instance
//
//		TimerHandle_t udp_broadcasts_timerHandle = nullptr;
//		TaskHandle_t abp2_server_taskHandle = nullptr;
//
//		static void static_send_udp_broadcast(TimerHandle_t xTimer);
//		void send_udp_broadcast();
//
//
//		static void static_abp2_server_task(void *pvParameter);
//		void abp2_server_task();
//
//
//		void handle_tcp_connection(const int sock);
//		bool received(const int sock, link_hdr_buf_t *hdr, InputBuffer * local_pInBuf, OutputBuffer * local_pOutBuf);
//
//		bool udp_broadcasts_started = false;
//		bool abp2_server_started = false;
//
//		int sock = -1;
//		sockaddr_in * pSend_addr;
//
//	//	InputBuffer * pInBuf;
//	//	OutputBuffer * pOutBuf;
//		};

#endif /* MAIN_WIFIENGINEABP2_H_ */
