
#include "main.h"
#include "pins_mapping.h"

#include "stdio.h"
#include "sdkconfig.h"
#include "Simple.h"

#define TAG "MAIN"



//=============================================
//=============================================
//=============================================

	void app_main()
		{
//		#ifdef CONFIG_VERSIONPCB_v105
//			printf("\nWARNING!!!! 1.0.5 firmware\n\n");
//		#endif
//
		#if CONFIG_STADEBUG
			printf("\nWARNING!!!! WIFI STA DEBUG \n\n");
		#endif
//
//		#ifndef CONFIG_ENABLE_WIFICONN
//			printf("\nWARNING!!!! WIFI CONN DISABLED \n\n");
//		#endif
//
//		Application * pApp = getApplication();
//
//		pApp->setup_console_baudrate(CONFIG_CONSOLE_BAUDRATE);
//		pApp->start((int) DeviceList::BALLAST, 0);					// starts ballast
//
//		pApp->checkEncryptionAndDoIfNeeded();
//
//		//=============================================
//		//setup_network();
//	//	 pApp->setup_network_uart(UART_NUM_0); // heb iok geclaimed in GS
//		 pApp->setup_network_uart(UART_NUM_1);
//		 pApp->setup_network_uart(UART_NUM_2);
//
//		 pApp->setup_network_interface(serial_PLUG_A_RxTx_U0_RXD, serial_PLUG_A_DIR);
//	//	 pApp->setup_network_interface(serial_PLUG_B_RxTx_U0_TXD, serial_PLUG_B_DIR);
//		 pApp->setup_network_interface(serial_PLUG_C_RxTx, serial_PLUG_C_DIR);
//		//=============================================
//
//		 //LOG("factoryname: %s ", ballastBallastFactory->getName() );
//		 ballastBallastFactory->startAlways();
//
//		 pApp->init_components();							// init all components
//		 pApp->start_components();							// start all components
//
//		 pApp->pollLoop();									// loop forever

		Simple * pS = new Simple();
		pS->init();
		pS->start();
		}

//=============================================
//=============================================
//=============================================


