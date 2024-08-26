/*
 * init.c
 *
 *  Created on: Aug 5, 2024
 *      Author: jeanfrancois
 */

#include <ol_init.h>
#include <ol_lib.h>
#include "debug.h"

void user_init() {
	USARTx_CFG();
	// Display System properties on boot
	{
		printf("\n\r Nunki Board Running \r\n");
		printf("SystemClk:%d\r\n",SystemCoreClock);
		printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());
	}

	// Init I/O

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	{
		GPIO_InitTypeDef GPIO_InitStructure = {0};
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
		// GPIO outputs
		GPIO_InitStructure.GPIO_Pin = OL_GPIO_01_PIN;
		GPIO_Init(OL_GPIO_01_PORT, &GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = OL_GPIO_02_PIN;
		GPIO_Init(OL_GPIO_02_PORT, &GPIO_InitStructure);
	}

}

void system_init() {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();
	#if (SDI_PRINT == SDI_PR_OPEN)
	    SDI_Printf_Enable();
	#else
	    USART_Printf_Init(115200);
	#endif
}

/*********************************************************************
 * @fn      USARTx_CFG
 *
 * @brief   Initializes the USART2 & USART3 peripheral.
 *
 * @return  none
 */
void USARTx_CFG(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    /* USART1 TX-->D.5   RX-->D.6 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}
