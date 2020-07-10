/*
 * SerialController.c
 *
 *  Created on: Jul 10, 2020
 *      Author: daniel
 */

#include "SerialController.h"
#include <stdio.h>
#include <stdlib.h>
#include <usbd_cdc_if.h>
#include <stdarg.h>


TaskHandle_t __SC_Handle = NULL;

void usbPrintf(const char *format, ...) {

	char buff[USB_PRINT_BUFF];
	int p;

	va_list argptr;
	va_start(argptr, format);
	p = vsprintf(buff, format, argptr);
	va_end(argptr);
	p=MIN(p,USB_PRINT_BUFF);
	while(1){
		uint8_t st = CDC_Transmit_FS((uint8_t*)buff,p);
		if(st == USBD_BUSY){
			vTaskDelay(1);
		}else{
			return;
		}
	}

}

void __App_SC_task(void *argument) {
	const TickType_t xMaxBlockTime = pdMS_TO_TICKS(500);
	BaseType_t xResult;
	uint32_t ulNotifiedValue;

	for (;;) {
		/* Wait to be notified of an interrupt. */
		xResult = xTaskNotifyWait( pdFALSE, /* Don't clear bits on entry. */
		-1, /* Clear all bits on exit. */
		&ulNotifiedValue, /* Stores the notified value. */
		xMaxBlockTime);

		if (xResult == pdPASS) {
			/* A notification was received.  See which bits were set. */
			if ((ulNotifiedValue & SC_CONNECTED) != 0) {
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
				vTaskDelay(10);
				usbPrintf("DCC SNIFFER v0.0.0 "__DATE__" "__TIME__"\n");
			}

			if ((ulNotifiedValue & SC_DISCONNECTED) != 0) {
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
			}
		} else {
			/* Did not receive a notification within the expected time. */
			//prvCheckForErrors();
			trace("No Event\n", 10);
		}
	}
}

void APP_SerialController_startTask() {
	BaseType_t xReturned = xTaskCreate(__App_SC_task, "SerialController",
			128 * 4, NULL, tskPRIORITY_STD, &__SC_Handle);
	if (xReturned != pdTRUE) {
		trace("Error Creating Task\n", 20);
	} else {
		trace("Created Task\n", 15);
	}
}

void APP_SerialController_Notify(uint32_t val) {
	trace("Event Requested\n", 25);
	if (__SC_Handle == NULL)
		return;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	xTaskNotifyFromISR(__SC_Handle, val, eSetBits, &xHigherPriorityTaskWoken);

	trace("Event Sent\n", 15);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
