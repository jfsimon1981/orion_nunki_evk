/*
 * orion_lib.c
 *
 *  Created on: Aug 5, 2024
 *  Author: jeanfrancois
 *  v1.1.100 1-Sep-2024
 */

#include <ol_lib.h>

#ifndef USER_CE_LIB_C_
#define USER_CE_LIB_C_

#ifdef EVK_CH32V003_GENERIC
GPIO_TypeDef * ol_port_map[] = {0, GPIOD, GPIOD, GPIOD, GPIOD, GPIOC, GPIOD, GPIOD, \
		GPIOD, GPIOC, GPIOD, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC};

uint16_t ol_pin_map[] = {0, GPIO_Pin_5, GPIO_Pin_4, GPIO_Pin_7, GPIO_Pin_6, \
		GPIO_Pin_0, GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_3, GPIO_Pin_7, \
		GPIO_Pin_2, GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_3, GPIO_Pin_4, \
		GPIO_Pin_1, GPIO_Pin_2};
#endif

#ifdef CE_NUNKI_MICRO_CH32V003F
GPIO_TypeDef * ol_port_map[] = {0, GPIOD, GPIOD, GPIOC, GPIOD, GPIOC, GPIOC, GPIOC, \
		GPIOC, GPIOC, GPIOC, GPIOC, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD};

uint16_t ol_pin_map[] = {0, GPIO_Pin_5, GPIO_Pin_7, GPIO_Pin_0, GPIO_Pin_1, \
		GPIO_Pin_7, GPIO_Pin_5, GPIO_Pin_3, GPIO_Pin_1, GPIO_Pin_2, \
		GPIO_Pin_4, GPIO_Pin_6, GPIO_Pin_2, GPIO_Pin_3, GPIO_Pin_0, \
		GPIO_Pin_6, GPIO_Pin_4};
#endif

void gpio_digital_write(unsigned int pin, unsigned int vin) {
#ifdef OL_SAFE
	if ((!pin) || (pin > 16)) {
		// OL_ERROR(PIN_MAP);
		return;
	} else {
		GPIO_WriteBit(ol_port_map[pin], ol_pin_map[pin], vin);
	}
#else
	GPIO_WriteBit(ol_port_map[pin], ol_pin_map[pin], vin);
#endif
}

uint8_t gpio_digital_read(int pin) {
#ifdef OL_SAFE
	if ((!pin) || (pin > 16)) {
		// OL_ERROR(PIN_MAP);
		return 0;
	} else {
		return GPIO_ReadInputDataBit(ol_port_map[pin], ol_pin_map[pin]);
	}
#else
	return GPIO_ReadInputDataBit(ol_port_map[pin], ol_pin_map[pin]);
#endif
}


#endif /* USER_CE_LIB_C_ */
