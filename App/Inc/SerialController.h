/*
 * SerialController.h
 *
 *  Created on: Jul 10, 2020
 *      Author: daniel
 */

#ifndef SRC_SERIALCONTROLLER_H_
#define SRC_SERIALCONTROLLER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <AppFreeRTOS.h>
#include "trace.h"
void APP_SerialController_startTask();
void APP_SerialController_Notify(uint32_t val);

#ifdef __cplusplus
}
#endif

#endif /* SRC_SERIALCONTROLLER_H_ */
