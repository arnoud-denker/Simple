#include "WifiEngineSMART.h"
//
//
//#include "global.h"
//
//#define TAG "WIFISTAABP2"
//
//#define WIFI_COMMAND_PORT 2819
//
//
//WifiEngineSMART* WifiEngineSMART::inst_ = nullptr;
////=======================================================
//
//WifiEngineSMART::WifiEngineSMART()
//	{
//	inst_ = this;
//
//	pSend_addr = new struct sockaddr_in();
//	pSend_addr->sin_family         = AF_INET,
//	pSend_addr->sin_port           = 1111;//WIFI_BROADCAST_PORT; //htons( WIFI_BROADCAST_PORT );
//	pSend_addr->sin_addr.s_addr    = inet_addr( "255.255.255.255" );
//	pSend_addr->sin_len            = sizeof( struct sockaddr_in );
//	}
//
////=======================================================
////=======================================================
////=======================================================
//
//WifiEngineSMART::~WifiEngineSMART()
//	{
//	// delete(pSend_addr);
//	}
//
////=======================================================
////=======================================================
////=======================================================
//
//WifiEngineABP2* WifiEngineABP2::getInstance()
//	{
//	return(inst_);
//	}
//
////=======================================================
////=======================================================
////=======================================================
//
//void WifiEngineSMART::shutdownAllTask()
//	{
//	if (udp_broadcasts_timerHandle != NULL)
//		{
//		xTimerStop( udp_broadcasts_timerHandle, pdMS_TO_TICKS(1000) );
//		xTimerDelete(udp_broadcasts_timerHandle, pdMS_TO_TICKS(1000));
//		}
//
//	if( abp2_server_taskHandle != NULL )
//	  	{
//	    vTaskDelete( abp2_server_taskHandle );
//	  	}
//	}
//
////=======================================================
////=======================================================
////=======================================================
//
//void WifiEngineSMART::start_udpBroadcast()
//	{
//	if (udp_broadcasts_started == true)
//		{
//		LOG("aleady started");
//		return;
//		}
//
//	// TODO faster when a client is connected and we dont have a connection yet?
//	udp_broadcasts_timerHandle = xTimerCreate("UDP_broadcast", pdMS_TO_TICKS(1000), pdTRUE, nullptr/*&ufd_timer*/, &WifiEngineABP2::static_send_udp_broadcast);
//
//	if (xTimerStart(udp_broadcasts_timerHandle, 10) == pdFAIL)
//		{
//		fatal_abort(0x28e44332/*cant start udp timer*/);
//		}
//
//	udp_broadcasts_started = true;
//	}
//
////=======================================================
////=======================================================
////=======================================================
//
//void WifiEngineSMART::static_send_udp_broadcast(TimerHandle_t timer)
//	{
//	WifiEngineABP2 * pAbp2 = reinterpret_cast<WifiEngineABP2*>(timer);
//	pAbp2->send_udp_broadcast();
//	}
//
//#include <mbedtls/platform.h>
//
//#include <mbedtls/ctr_drbg.h>
//#include <mbedtls/debug.h>
//#include <mbedtls/entropy.h>
//#include <mbedtls/error.h>
//#include <mbedtls/net.h>
//#include <mbedtls/ssl.h>
//
//#include <lwip/inet.h>
//#include <lwip/sockets.h>
//
//void WifiEngineABP2::send_udp_broadcast()
//	{
//	WifiEngineABP2* pabp2 = WifiEngineABP2::getInstance();
//
//	if (pabp2->sock == -1)
//		{
//		LOG("broadcast: open udp socket");
//
//		pabp2->sock = socket( AF_INET, SOCK_DGRAM, IPPROTO_IP );
//		if(pabp2->sock < 0)
//		 	 {
//		     LOG("... Failed to allocate socket.");
//		 	 }
//		 else
//		 	 {
//			 int broadcast = 1;
//
//			 if (setsockopt(pabp2->sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast))  < 0)
//				 {
//		         ERR("... failed to set socket receiving timeout");
//		         close(pabp2->sock);
//		         pabp2->sock = -1;
//				 }
//		 	 }
//		}
//	else
//		{
//	//	LOG("send broadcast");
//
//		broadcast_t data;
//		data.secret[0] = 'A';
//		data.secret[1] = 'I';
//		data.secret[2] = 'R';
//		data.secret[3] = '0';
//		data.mid = modelinfo.mid;
//		data.deviceId = modelinfo.deviceId;
//		data.deviceSub = modelinfo.deviceSub;
//		data.app_version = app_version_hex;
//		//data.ipaddr = modelinfo.ipaddr;
//
//		sendto(pabp2->sock, &data, sizeof(data), 0, (const struct sockaddr*) pabp2->pSend_addr, sizeof( struct sockaddr_in ) );
//		}
//	}
//
////=======================================================
////=======================================================
////=======================================================
//
//
//void WifiEngineABP2::start_abp2_server()
//	{
//	LOG("Starting ABP2 server");
////	if (abp2_server_started == true)
////		{
////		LOG("already started");
////		return;
////		}
////
//
////
//
//    xTaskCreate(&static_abp2_server_task, "abp2_server", 4096, NULL, 9, &abp2_server_taskHandle);
//	}
//
////=======================================================
//
//
//void WifiEngineABP2::static_abp2_server_task(void *pvParameter)
//	{
//	WifiEngineABP2 * pAbp2 = reinterpret_cast<WifiEngineABP2*>(pvParameter);
//	pAbp2->abp2_server_task();
//	}
//
//
//void WifiEngineABP2::abp2_server_task()
//	{
//    char addr_str[128];
//    int addr_family = AF_INET; //(int)pvParameters;
//    int ip_protocol = 0;
//    int keepAlive = 1;
//    int keepIdle = 5; // KEEPALIVE_IDLE;
//    int keepInterval = 5; // KEEPALIVE_INTERVAL;
//    int keepCount = 3; // KEEPALIVE_COUNT;
//    struct sockaddr_storage dest_addr;
//
//    vTaskDelay(100);
//    LOG("tcp_server task running");
//
//    if (addr_family == AF_INET)
//    	{
//        struct sockaddr_in *dest_addr_ip4 = (struct sockaddr_in *)&dest_addr;
//        dest_addr_ip4->sin_addr.s_addr = INADDR_ANY; //htonl(INADDR_ANY);
//        dest_addr_ip4->sin_family = AF_INET;
//        dest_addr_ip4->sin_port = WIFI_COMMAND_PORT; //htons(WIFI_COMMAND_PORT);
//        ip_protocol = IPPROTO_IP;
//    	}
//
//    int listen_sock = socket(addr_family, SOCK_STREAM, ip_protocol);
//    if (listen_sock < 0)
//    	{
//    	ERR( "Unable to create socket: errno %d", errno);
//        vTaskDelete(NULL);
//        return;
//    	}
//    int opt = 1;
//    setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
//
//    LOG("Socket created");
//
//    int err = bind(listen_sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
//    if (err != 0)
//    	{
//    	ERR("Socket unable to bind: errno %d", errno);
//        ERR("IPPROTO: %d", addr_family);
//    	}
//    else
//		{
//		LOG("Socket bound, port %d", WIFI_COMMAND_PORT);
//
//		err = listen(listen_sock, 1);
//		if (err != 0)
//			{
//			ERR("Error occurred during listen: errno %d", errno);
//			}
//		else
//			{
//			while (1)
//				{
//				LOG( "Socket listening");
//
//				struct sockaddr_storage source_addr; // Large enough for both IPv4 or IPv6
//				socklen_t addr_len = sizeof(source_addr);
//				int sock = accept(listen_sock, (struct sockaddr *)&source_addr, &addr_len);
//				if (sock < 0)
//					{
//					ERR("Unable to accept connection: errno %d", errno);
//					break;
//					}
//
//				// Set tcp keepalive option
//				setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &keepAlive, sizeof(int));
//				setsockopt(sock, IPPROTO_TCP, TCP_KEEPIDLE, &keepIdle, sizeof(int));
//				setsockopt(sock, IPPROTO_TCP, TCP_KEEPINTVL, &keepInterval, sizeof(int));
//				setsockopt(sock, IPPROTO_TCP, TCP_KEEPCNT, &keepCount, sizeof(int));
//
//				// Convert ip address to string
//				if (source_addr.ss_family == PF_INET)
//					{
//					inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr, addr_str, sizeof(addr_str) - 1);
//					}
//
//				LOG("abp2_server_task socket accepted, ip address: %s", addr_str);
//				handle_tcp_connection(sock);
//
//				LOG("shutdown socket");
//				shutdown(sock, 0);
//				close(sock);
//				}
//			}
//		}
//
//
//   	close(listen_sock);
//   	vTaskDelete(NULL);
//	}
//
////=======================================================
////=======================================================
////=======================================================
//
//void WifiEngineABP2::handle_tcp_connection(const int sock)
//	{
//	int maxbuf = MAX_CONSOLE_INPUT_BUF;
//	int hdrlen = 0;
//    int pcklen = 0;
//    bool close = false;
//
//    link_hdr_buf_t hdr;
//
//    LOG("Handle tcpip connection");
//
//	//WifiEngineABP2* pabp2 = WifiEngineABP2::getInstance();
//
//	InputBuffer * pInBuf = new InputBuffer(MAX_CONSOLE_INPUT_BUF);
//	OutputBuffer * pOutBuf = new OutputBuffer(MAX_CONSOLE_OUTPUT_BUF);
//
//    while (!close)
//    	{
//		if (hdrlen == 0)
//			pcklen = 0;
//
//		// at least two reads: one for the header and one for the data, so we dont
//		// have to split the buffer
//		if (hdrlen < sizeof(link_hdr_buf_t))
//			{							// read header (8 bytes)
//			int remain = sizeof(link_hdr_buf_t)-hdrlen;
////			int nread = uart_read_bytes(UART_NUM_0, ((byte*)&hdr)+hdrlen, remain, 100/*ticks*/);
//			int nread = recv(sock, ((byte*)&hdr)+hdrlen, remain, 0);
//			if (nread < 0)
//				{
//				LOG("Rec errno %d", errno);
//				close = true;
//				continue;
//				}
//			else if (nread == 0)
//				{
//				LOG( "Connection closed");
//				close = true;
//				continue;
//				}
//			else
//				{
//				hdrlen += nread;
//				if (hdrlen > 0 && hdr.let != 'C')
//					{
//					LOG("not C");
//					close = true;
//					continue;
//					}
//				if (hdrlen >= 4 && hdr.len > maxbuf)
//					{
//					LOG("too long");
//					close = true;
//					continue;
//					}
//				}
//			}
//		else
//			{
//			int remain = hdr.len - pcklen;
////			int nread = uart_read_bytes(UART_NUM_0, buf+pcklen, remain, 10/*ticks*/);
//			int nread = recv(sock, pInBuf->getbuf()+pcklen, remain, 0);
//			if (nread < 0)
//				{
//				LOG( "rec errno %d", errno);
//				close = true;
//				continue;
//				}
//			else if (nread == 0)
//				{
//				LOG("Connection closed");
//				close = true;
//				continue;
//				}
//			else
//				{
//				pcklen += nread;
//				if (pcklen < hdr.len)
//					{									// wait for more
//					LOG("wait %d", pcklen);
//					continue;
//					}
//				if (pcklen > hdr.len)
//					{									// would overflow
//					LOG("overflow %d-%d", hdr.len, pcklen);
//					close = true;
//					continue;
//					}
//				if (!received(sock, &hdr, pInBuf, pOutBuf) )
//					{
//					close = true;
//					}
//				hdrlen = 0;												// ready to receive next
//				}
//			}
//    	}
//
//    // hoe buffers terug te geven?
//    if (pInBuf != NULL)
//    	{
//    	delete(pInBuf);
//    	}
//    if (pOutBuf != NULL)
//    	{
//    	delete(pOutBuf);
//    	}
//
//
//    LOG("handle() return");
//	}
//
////=======================================================
//
////checksum error
//bool WifiEngineABP2::received(const int sock, link_hdr_buf_t *hdr, InputBuffer * local_pInBuf,  OutputBuffer * local_pOutBuf)
//	{
//	static CRC32 crc;
//	static int last_seq = 0;
//
//	byte * pbuf = local_pInBuf->getbuf();
//	LOG("dat %x %x %x %x %x %x %x %x",
//			*(pbuf+0),
//			*(pbuf+1),
//			*(pbuf+2),
//			*(pbuf+3),
//			*(pbuf+4),
//			*(pbuf+5),
//			*(pbuf+6),
//			*(pbuf+7)
//			);
//
//	word cks = crc.compute(local_pInBuf->getbuf(), hdr->len);
//	if (cks != hdr->cks)
//		{
//		LOG("checksum error %x,%x", cks, hdr->cks);
//		return false;
//		}
//
//	if (last_seq != 0 && hdr->seq == last_seq)
//		{							// this is a retry, send reply again
//		LOG("resend seq=%d", hdr->seq);
//		}
//	else
//		{
//		local_pInBuf->init(hdr->len);
//
//		local_pOutBuf->rewind();
//		handle_console(local_pInBuf, local_pOutBuf, 0);
//		}
//
//	link_hdr_buf_t reply;
//	int len = local_pOutBuf->getmark();
//	byte *buf = local_pOutBuf->getbuf();
//	reply.let = 'R';									// Reply
//	reply.seq = hdr->seq;								// unchanged
//	reply.len = len;
//	reply.cks = crc.compute(buf, len);
//
//	int to_write = sizeof(link_hdr_buf_t);
//	byte *wp = (byte*) &reply;
//	LOG("write hdr %d", to_write);
//	while (to_write > 0)
//		{
//		int written = send(sock, wp, to_write, 0);
//		if (written < 0)
//			{
//			LOG("Send errno %d", errno);
//			return false;
//			}
//		to_write -= written;
//		wp += written;
//		}
//
//	to_write = len;
//	wp = buf;
//	LOG("write buf %d", to_write);
//	while (to_write > 0)
//		{
//		int written = send(sock, wp, to_write, 0);
//		if (written < 0)
//			{
//			LOG("Send errno %d", errno);
//			return false;
//			}
//		to_write -= written;
//		wp += written;
//		}
//	last_seq = hdr->seq;
//	return true;
//	}
//
////=======================================================
//


