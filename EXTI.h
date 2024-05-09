#ifndef INC_EXTI_H_
#define INC_EXTI_H_

#include "stm32F070xx.h"
/*
 * @def_droup PORT_VALUES
 */

#define EXTI_PORT_SOURCE_GPIOA					((uint8_t)(0x0))
#define EXTI_PORT_SOURCE_GPIOB					((uint8_t)(0x1))
#define EXTI_PORT_SOURCE_GPIOC					((uint8_t)(0x2))
#define EXTI_PORT_SOURCE_GPIOD					((uint8_t)(0x3))


/*
 * @def_droup EXTI_Line_Values
 */

#define EXTI_LINE_SOURCE_0						((uint8_t)(0x0))
#define EXTI_LINE_SOURCE_1						((uint8_t)(0x1))
#define EXTI_LINE_SOURCE_2						((uint8_t)(0x2))
#define EXTI_LINE_SOURCE_3						((uint8_t)(0x3))
#define EXTI_LINE_SOURCE_4						((uint8_t)(0x4))
#define EXTI_LINE_SOURCE_5						((uint8_t)(0x5))
#define EXTI_LINE_SOURCE_6						((uint8_t)(0x6))
#define EXTI_LINE_SOURCE_7						((uint8_t)(0x7))
#define EXTI_LINE_SOURCE_8						((uint8_t)(0x8))
#define EXTI_LINE_SOURCE_9						((uint8_t)(0x9))
#define EXTI_LINE_SOURCE_10						((uint8_t)(0xA))
#define EXTI_LINE_SOURCE_11						((uint8_t)(0xB))
#define EXTI_LINE_SOURCE_12						((uint8_t)(0xC))
#define EXTI_LINE_SOURCE_13						((uint8_t)(0xD))
#define EXTI_LINE_SOURCE_14						((uint8_t)(0xE))
#define EXTI_LINE_SOURCE_15						((uint8_t)(0xF))

/*
 * @def_group EXTI_Modes
 */
#define EXTI_MODE_INTERRUPT						(0x00U)
#define EXTI_MODE_EVENT							(0x04U)

/*
 * @def_group EXTI_Tigger_Modes
 */
#define EXTI_Trigger_Rising						(0x08U)
#define EXTI_Trigger_Falling					(0x0CU)
#define EXTI_Trigger_RF							(0x10U)

typedef struct
{
	uint8_t EXTI_LineNumber;					//!< EXTI line number for valid GPIO pin @def_droup EXTI_Line_Values
	uint8_t TriggerSelection;					//!< EXTI Trigger selection values @def_group EXTI_Tigger_Modes
	uint8_t EXTI_Mode;							//!< EXTI mode values @def_group EXTI_Modes
	FunctionalState_t EXTI_LineCmd;				//!< Mask or unmask the line number

}EXTI_InitTypeDef_t;

void EXTI_Init(EXTI_InitTypeDef_t *EXTI_InitStruct);
void EXTI_LineConfig(uint8_t PortSource, uint8_t EXTI_LineSource);
void NVIC_EnableInterrupt(IRQNumber_TypeDef_t IRQNumber);


#endif /* INC_EXTI_H_ */


