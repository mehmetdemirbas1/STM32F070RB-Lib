#ifndef INC_USART_H_
#define INC_USART_H_

#include "stm32F070xx.h"

typedef struct
{
	uint32_t OverSampling;
	uint32_t BaudRate;
	uint32_t WordLenght;
	uint32_t Parity;
	uint32_t Stop;
	uint32_t HardWareFlowControl;
	uint32_t Mode;

}USART_InitTypeDef_t;

typedef struct
{
	USART_TypeDef_t *Instance;
	USART_InitTypeDef_t Init;

}USART_HandleTypeDef_t;

#endif /* INC_USART_H_ */
