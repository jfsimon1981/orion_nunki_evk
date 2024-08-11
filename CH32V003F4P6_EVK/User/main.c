/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : Orion-Electronics
 * Version            : V1.0
 * Date               : 10/8/24
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2024 Orion Electronics
 *******************************************************************************/

/*
 *@Note
 *Multiprocessor communication mode routine:
 *Master:USART1_Tx(PD5)\USART1_Rx(PD6).
 *This routine demonstrates that USART1 receives the data sent by CH341 and inverts
 *it and sends it (baud rate 115200).
 *
 *Hardware connection:PD5 -- Rx
 *                     PD6 -- Tx
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
    	GPIO_01_DIGITAL_WRITE(0);
    	GPIO_01_DIGITAL_WRITE(1);
		GPIO_01_DIGITAL_SET;
		GPIO_01_DIGITAL_CLEAR;
		gpio_digital_read(1);
		gpio_digital_read(GPIO_01);
		gpio_digital_write(1, 1);
		gpio_digital_read(GPIO_01, 1);
		*/

    	for (int i = 0; i < 3; i++) {
    		static int toggle = 0;
    		if (!toggle++) toggle = 1;
    		else toggle = 0;
    		gpio_digital_write(GPIO_01, toggle);
    		Delay_Ms(80);
    	}
    	Delay_Ms(150);



    	// Read Back using USART 1 and take command input:
    	// Key 1 : GPIO 2 Off
    	// Key 2 : GPIO 2 On

            while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
            {
                // Read Back
				val = (USART_ReceiveData(USART1));

				if (val == '1') GPIO_02_DIGITAL_SET;
				else if (val == '2') GPIO_02_DIGITAL_CLEAR;

				USART_SendData(USART1, val);
				while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
				{
					// waiting for sending finish
				}
            }
    }
}
