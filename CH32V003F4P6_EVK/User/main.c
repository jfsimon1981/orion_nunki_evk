/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Chrysalide-Engineering
 * Version            : V1.0
 * Date               : 10/8/24
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2024 Chrysalide-Engineering
 *******************************************************************************/

/*
 *@Note
 * Base Demo with GPIO 3 and 5.
 * Blink GPIO_03 (500ms)
 * UART control of GPIO_05 : 1=OFF 2=ON 3=Toggle
 *
 * Notice Toggle is different from ON/OFF as it reads the pin and inverts
 * the read value. Forcing the pin from external Gnd/3.3V changes the toggle
 * behavior to set to !Read pin value.
 *
 */

#include <ol_init.h>
#include <ol_lib.h>
#include "debug.h"

/* Global define */


/* Global Variable */

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    system_init();
    user_init();

    // Main program variables
    vu8 val;

    // Main program loop
    while(1)
    {
    	// Various flavors of I/O manipulation
		/*
		 * === Fast GPIO commands ===
		 *
		 * int v0 = GPIO_01_DIGITAL_READ();
		 *
		 * GPIO_01_DIGITAL_SET();
		 * GPIO_01_DIGITAL_CLEAR();
		 *
		 * === Generic GPIO commands ===
		 *
		 * GPIO_01_DIGITAL_WRITE(0);
		 * GPIO_01_DIGITAL_WRITE(1);
		 *
		 * int v1 = gpio_digital_read(1);
		 * int v2 = gpio_digital_read(OL_GPIO_01);
		 *
		 * gpio_digital_write(1, 1);
		 * gpio_digital_write(OL_GPIO_01, 1);
		 *
		 */

    	for (int i = 0; i < 3; i++) {
    		static int toggle = 0;
    		if (!toggle++) toggle = 1;
    		else toggle = 0;
    		gpio_digital_write(OL_GPIO_03, toggle);
    		Delay_Ms(80);
    	}
    	Delay_Ms(500);

    	// Read Back using USART 1 and take command input:
    	// Key 1 : GPIO 2 Off
    	// Key 2 : GPIO 2 On
		while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
		{
			// Read Back
			val = (USART_ReceiveData(USART1));

			if (val == '1') GPIO_05_DIGITAL_CLEAR();
			else if (val == '2') GPIO_05_DIGITAL_SET();
			else if (val == '3') GPIO_05_DIGITAL_WRITE(!GPIO_05_DIGITAL_READ());

			USART_SendData(USART1, val);
			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); // Wait send finished
		}
    }
}
