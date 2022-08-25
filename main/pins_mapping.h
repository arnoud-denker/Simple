
#ifndef MAIN_PINS_MAPPING_H_
#define MAIN_PINS_MAPPING_H_


//#include "hal/gpio_types.h"

/*
 define soort pinning in Constants.h  !!
 */
//----------------------------------------------

	#ifdef CONFIG_MODEL_BALLAST_1000W_GS

		#define status_gpiopin							GPIO_NUM_2			//
		#define ws2812_rmt_channel						RMT_CHANNEL_0

		#define tm2618_dio_gpiopin						GPIO_NUM_25			//
		#define tm2618_clk_gpiopin						GPIO_NUM_26			//
		#define tm2618_stb_gpiopin						GPIO_NUM_27			//

		#define cpu_uart_gs_rxd_gpio					GPIO_NUM_39			//
		#define cpu_uart_gs_txd_gpio					GPIO_NUM_5			//

		#define gpio_I2C_MASTER_SCL   					GPIO_NUM_22			//
		#define gpio_I2C_MASTER_SDA   					GPIO_NUM_21			//
		#define I2C_MASTER_FREQ_HZ  					100000
		#define I2C_MASTER_NUM  						I2C_NUM_1

		#define  serial_PLUG_A_DIR						GPIO_NUM_17			//
		#define  serial_PLUG_A_RxTx_U0_RXD				GPIO_NUM_3			//
		#define  serial_PLUG_B_DIR						GPIO_NUM_16			//
		#define  serial_PLUG_B_RxTx_U0_TXD				GPIO_NUM_1			//
		#define  serial_PLUG_C_RxTx						GPIO_NUM_19			//
		#define  serial_PLUG_C_DIR						GPIO_NUM_23			//

		#define adc_ESP_ANALOG_B						ADC1_CHANNEL_1		//
		#define adc_ESP_ANALOG_C						ADC1_CHANNEL_2		//
		#define adc_ESP_ID								ADC1_CHANNEL_0		//
		#define adc_ESP_ANALOGCTRL 						ADC1_CHANNEL_6		//
		#define adc_PLUG_A_RS485_A_FIL					ADC1_CHANNEL_4		//
		#define adc_PLUG_A_RS485_B_FIL					ADC1_CHANNEL_5		//

		#define switch_gpiopin							GPIO_NUM_0			//
		#define flashprotect_gpiopin					GPIO_NUM_18			//

#else
	#ifdef CONFIG_VERSIONPCB_v105

		#define status_gpiopin							GPIO_NUM_2
		#define ws2812_rmt_channel						RMT_CHANNEL_0

		#define tm2618_dio_gpiopin						GPIO_NUM_25
		#define tm2618_clk_gpiopin						GPIO_NUM_26
		#define tm2618_stb_gpiopin						GPIO_NUM_27

		#define cpu_in_hid_out_gpio						GPIO_NUM_35
		#define cpu_out_hid_in_gpio						GPIO_NUM_5

//		#define cpu_uart_gs_rxd_gpio					GPIO_NUM_34
//		#define cpu_uart_gs_txd_gpio					GPIO_NUM_5
		#define uart_buf_size_gs 						100
		#define uart_baudrate_gs 						9600
		#define uart_portnumber_gs 						UART_NUM_2


		#define hid1_rmt_rxd_channel					RMT_CHANNEL_1
		#define hid1_rmt_txd_channel					RMT_CHANNEL_2

		#define gpio_I2C_MASTER_SCL   					GPIO_NUM_22
		#define gpio_I2C_MASTER_SDA   					GPIO_NUM_21
		#define I2C_MASTER_FREQ_HZ  					100000
		#define I2C_MASTER_NUM  						I2C_NUM_1

		#define serial_PLUG_A_DIR						GPIO_NUM_17
		#define serial_PLUG_A_RxTx_U0_RXD				GPIO_NUM_3
		#define serial_PLUG_B_DIR						GPIO_NUM_16
		#define serial_PLUG_B_RxTx_U0_TXD				GPIO_NUM_1
		#define serial_PLUG_C_DIR						GPIO_NUM_23
		#define serial_PLUG_C_RxTx						GPIO_NUM_19

		#define adc_ESP_ANALOG_B						ADC1_CHANNEL_0
		#define adc_ESP_ANALOG_C						ADC1_CHANNEL_1
		#define adc_ESP_ID								ADC1_CHANNEL_2
		#define adc_ESP_ANALOGCTRL 						ADC1_CHANNEL_3
		#define adc_PLUG_A_RS485_A_FIL					ADC1_CHANNEL_4
		#define adc_PLUG_A_RS485_B_FIL					ADC1_CHANNEL_5

		#define switch_gpiopin							GPIO_NUM_0
	 	#define flashprotect_gpiopin					GPIO_NUM_18


#else

		#define status_gpiopin							GPIO_NUM_2
		#define ws2812_rmt_channel						RMT_CHANNEL_0

		#define tm2618_dio_gpiopin						GPIO_NUM_25
		#define tm2618_clk_gpiopin						GPIO_NUM_26
		#define tm2618_stb_gpiopin						GPIO_NUM_27

		#define cpu_in_hid_out_gpio						GPIO_NUM_34
		#define cpu_out_hid_in_gpio						GPIO_NUM_4

		#define cpu_uart_gs_rxd_gpio					GPIO_NUM_34
		#define cpu_uart_gs_txd_gpio					GPIO_NUM_5
		#define uart_buf_size_gs 						100
		#define uart_baudrate_gs 						9600
		#define uart_portnumber_gs 						UART_NUM_2


		#define hid1_rmt_rxd_channel					RMT_CHANNEL_1
		#define hid1_rmt_txd_channel					RMT_CHANNEL_2

		#define gpio_I2C_MASTER_SCL   					GPIO_NUM_22
		#define gpio_I2C_MASTER_SDA   					GPIO_NUM_21
		#define I2C_MASTER_FREQ_HZ  					100000
		#define I2C_MASTER_NUM  						I2C_NUM_1

		#define serial_PLUG_A_DIR						GPIO_NUM_17
		#define serial_PLUG_A_RxTx_U0_RXD				GPIO_NUM_3
		#define serial_PLUG_B_DIR						GPIO_NUM_16
		#define serial_PLUG_B_RxTx_U0_TXD				GPIO_NUM_1
		#define serial_PLUG_C_DIR						GPIO_NUM_23
		#define serial_PLUG_C_RxTx						GPIO_NUM_19

		#define adc_ESP_ANALOG_B						ADC1_CHANNEL_1
		#define adc_ESP_ANALOG_C						ADC1_CHANNEL_2
		#define adc_ESP_ID								ADC1_CHANNEL_0
		#define adc_ESP_ANALOGCTRL 						ADC1_CHANNEL_3
		#define adc_PLUG_A_RS485_A_FIL					ADC1_CHANNEL_4
		#define adc_PLUG_A_RS485_B_FIL					ADC1_CHANNEL_5

		#define switch_gpiopin							GPIO_NUM_0
	 	#define flashprotect_gpiopin					GPIO_NUM_18
#endif

	#endif

#endif /* MAIN_PINS_MAPPING_H_ */
