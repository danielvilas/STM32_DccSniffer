/*
 * trace.h
 *
 *  Created on: 7 jul. 2020
 *      Author: daniel
 */

#ifndef INC_TRACE_H_
#define INC_TRACE_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include "main.h"

void trace(char* txt, uint8_t len);

#ifdef __cplusplus
}
#endif

#endif /* INC_TRACE_H_ */
