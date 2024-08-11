/*
 * orion_lib.c
 *
 *  Created on: Aug 5, 2024
 *      Author: jeanfrancois
 */

#include <ol_lib.h>

#ifndef USER_ORION_LIB_C_
#define USER_ORION_LIB_C_

GPIO_TypeDef * ol_port_map[] = {0, GPIOD, GPIOD, GPIOD, GPIOD, GPIOC, GPIOD, GPIOD, \
		GPIOD, GPIOC, GPIOD, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC};

uint16_t ol_pin_map[] = {0, GPIO_Pin_5, GPIO_Pin_4, GPIO_Pin_7, GPIO_Pin_6, \
		GPIO_Pin_0, GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_3, GPIO_Pin_7, \
		GPIO_Pin_2, GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_3, GPIO_Pin_4, \
		GPIO_Pin_1, GPIO_Pin_2};

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


#endif /* USER_ORION_LIB_C_ */
