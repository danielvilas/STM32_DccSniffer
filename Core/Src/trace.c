#include "trace.h"


void trace(char* txt, uint8_t len){
	uint8_t tmp=0;
	while(txt[tmp]!=0 && tmp<len){
		ITM_SendChar(txt[tmp++]);
	}
}
