/*
 * AppFreeRTOS.h
 *
 *  Created on: Jul 10, 2020
 *      Author: daniel
 */

#ifndef INC_APPFREERTOS_H_
#define INC_APPFREERTOS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <FreeRTOS.h>
#include <task.h>
#define tskPRIORITY_STD 100

#define SC_CONNECTED 0x0001
#define SC_DISCONNECTED 0x0002



static const int USB_PRINT_BUFF = 256;

#ifdef __cplusplus
}
#endif


#endif /* INC_APPFREERTOS_H_ */
