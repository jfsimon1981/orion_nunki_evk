# WCH CH32V003 and Nunki-Micro boards Software library

  * Orion (OL) library for easy GPIO manipulation
  * Supports WCH CH32V003 EVK and Nunki-Micro boards
  * Microcontroller: CH32V003

  - Linux serial console example
```
echo -n -e "1\r" > /dev/ttyACM0 # LED On
echo -n -e "2\r" > /dev/ttyACM0 # LED Off
echo -n -e "3\r" > /dev/ttyACM0 # LED Toggle
```
  - Connect to Serial console:
```
cu -l /dev/ttyACM0 -s 115200
```
  - GPIO manipulation example
```
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
```
