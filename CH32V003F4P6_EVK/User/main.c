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
    	// Running below test:
		int static test_n = 5;

    	// Method 1: Generic function call
    	// Tcy = 4.6 us (217 kHz @ 24 MHz)
    	// + Generic / - Slower execution speed
    	if (test_n == 1)
		while (1) {
			gpio_digital_write(9,1);
			gpio_digital_write(9,0);
		}

    	// Method 2: Optimized function call
    	// Tcy = 1.2 us (833 kHz  @ 24 MHz)
    	// + More flexible / - Medium execution speed
    	if (test_n == 2)
    	while (1) {
    		GPIO_09_DIGITAL_WRITE(1);
    		GPIO_09_DIGITAL_WRITE(0);
    	}

    	// Method 3: Raw Assembly
    	// Tcy = 0.15 us (6.7 MHz @ 24 MHz)
    	// + Optimum speed / Assembly style
    	if (test_n == 3) {
    		GPIO_TypeDef *GPIOx = ol_port_map[GPIO_09];
			uint16_t GPIO_Pin = ol_pin_map[GPIO_09];
			while (1) {
				GPIOx->BSHR = GPIO_Pin;
				GPIOx->BCR = GPIO_Pin;
			}
    	}

    	// Method 4: Raw Assembly
    	// Tcy = 0.15 us (6.7 MHz)
    	// Internal Line to Line : t2 = .087 us == 11.54 MHz (2 cycles at 24 MHz)
    	// + Optimum speed / C with Macro style
    	if (test_n == 4) {
    		while (1) {
				GPIO_09_DIGITAL_SET;
				GPIO_09_DIGITAL_CLEAR;
				GPIO_09_DIGITAL_SET;
				GPIO_09_DIGITAL_CLEAR;
				GPIO_09_DIGITAL_SET;
				GPIO_09_DIGITAL_CLEAR;
    		}
    	}

    	// Same as Method 4, with I/O slew rate change
    	if (test_n == 5) {
    		static uint64_t change_pin_speed = 0;
    		while (1) {
    			{
					GPIO_09_DIGITAL_SET;
					GPIO_09_DIGITAL_CLEAR;
					GPIO_09_DIGITAL_SET;
					GPIO_09_DIGITAL_CLEAR;
					GPIO_09_DIGITAL_SET;
					GPIO_09_DIGITAL_CLEAR;
					GPIO_09_DIGITAL_SET;
					GPIO_09_DIGITAL_CLEAR;
					GPIO_09_DIGITAL_SET;
					GPIO_09_DIGITAL_CLEAR;
    			}
				{
					if (change_pin_speed == 600000) {
						GPIO_InitTypeDef GPIO_InitStructure = {0};
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; // GPIO_Speed_10MHz
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
						GPIO_Init(GPIOC, &GPIO_InitStructure);
					} else if (change_pin_speed == 1200000) {
						GPIO_InitTypeDef GPIO_InitStructure = {0};
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // GPIO_Speed_50MHz
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
						GPIO_Init(GPIOC, &GPIO_InitStructure);
					} else if (change_pin_speed == 1800000) {
						change_pin_speed = 0;
						GPIO_InitTypeDef GPIO_InitStructure = {0};
						GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
						GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // GPIO_Speed_2MHz
						GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
						GPIO_Init(GPIOC, &GPIO_InitStructure);
					}
					change_pin_speed++;
				}
    		}
    	}

    	// Slow blink GPIO 9 & 10
    	if (test_n == 99) {
    		GPIO_09_DIGITAL_SET;
    		Delay_Ms(250);
    		GPIO_10_DIGITAL_SET;
    		Delay_Ms(250);
			GPIO_09_DIGITAL_CLEAR;
			Delay_Ms(250);
			GPIO_10_DIGITAL_CLEAR;
			Delay_Ms(250);
    	}

    	// Read Back using USART 1
    	// This code reads UART (USB Serial com) input and reads it back
    	// Key are read : 1/2/3/4 to set GPIO 9 & 10 on or off.
    	// Wire LED to GPIO 9 & 10 to visualize outputs on board.

            while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
            {
                // Read Back
				val = (USART_ReceiveData(USART1));

				if (val == '1') GPIO_09_DIGITAL_WRITE(0);
				else if (val == '2') GPIO_09_DIGITAL_WRITE(1);
				else if (val == '4') GPIO_10_DIGITAL_WRITE(0);
				else if (val == '5') GPIO_10_DIGITAL_WRITE(1);

				USART_SendData(USART1, val);
				while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
				{
					// waiting for sending finish
				}
            }


    }
}
