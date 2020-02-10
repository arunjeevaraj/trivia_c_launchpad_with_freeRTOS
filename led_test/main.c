#include "TM4C123.h"                    // Device header
#include "RTE_Components.h"             // Component selection
#include <stdint.h>


#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "timers.h"                     // ARM.FreeRTOS::RTOS:Timers

void gpio_init();
void sysclk_init();
void toggle_led();
void delay_1ms(uint8_t delay);

void blue_led_fun(void* pv_parameter)
{
		while(1) {
			delay_1ms(2);
			GPIOF->DATA ^= 0x08;
		}
}

void red_led_fun(void* pv_parameter)
{
		while(1) {
			delay_1ms(2);
			GPIOF->DATA ^= 0x04;
		}
}

void green_led_fun(void* pv_parameter)
{
		while(1) {
			delay_1ms(2);
			GPIOF->DATA ^= 0x02;
		}
}

int main()
{
	sysclk_init();
	gpio_init();
	
	
	xTaskCreate(blue_led_fun, "blue led blinker", 100, NULL, 1, NULL );
	xTaskCreate(red_led_fun, "red led blinker", 100, NULL, 1, NULL );
	xTaskCreate(green_led_fun, "green led blinker", 100, NULL, 1, NULL );
	
	
	vTaskStartScheduler();
}

void toggle_led()
{ 
		GPIOF->DATA = 0x02 << 1;
}

void delay_1ms(uint8_t delay)
{
	uint32_t delay_i = 50000;
	while(delay--) {
		while(delay_i--);
	}
	
}

void sysclk_init()
{
	SYSCTL->RCGC2 |= 0x20; // activate clock for port f
	//delay_1ms(1);
}

void gpio_init()
{
	GPIOF->LOCK = 0x4C4F434B; // unlock the register.
	//delay_1ms(1);
	GPIOF->CR = 0x1F;
//	delay_1ms(1);
	GPIOF->AMSEL =0; // Disable analog functionality.
	GPIOF->PUR  = 0; // enable pull up register
	GPIOF->PCTL = 0; // regular port.
	GPIOF->AFSEL =0; // Disable alternate functionality
	GPIOF->DIR = 0;
	//delay_1ms(1);
	GPIOF->DIR |= 0x1f; // ports 1, 2 and 3 are set to be outputs.
	//delay_1ms(1);
	GPIOF->DEN =  0x1f;
}

