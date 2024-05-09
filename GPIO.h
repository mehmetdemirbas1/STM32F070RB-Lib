#ifndef INC_GPIO_H_
#define INC_GPIO_H_
#include "stm32F070xx.h"

/*
 *
 * @def_group GPIO_Pins
 *
 */

#define GPIO_PIN_0				(uint16_t)(0x0001) //<! GPIO pin 1 selected
#define GPIO_PIN_1				(uint16_t)(0x0002) //<! GPIO pin 2 selected
#define GPIO_PIN_2				(uint16_t)(0x0004) //<! GPIO pin 3 selected
#define GPIO_PIN_3				(uint16_t)(0x0008) //<! GPIO pin 4 selected
#define GPIO_PIN_4				(uint16_t)(0x0010) //<! GPIO pin 5 selected
#define GPIO_PIN_5				(uint16_t)(0x0020) //<! GPIO pin 6 selected
#define GPIO_PIN_6				(uint16_t)(0x0040) //<! GPIO pin 7 selected
#define GPIO_PIN_7				(uint16_t)(0x0080) //<! GPIO pin 8 selected
#define GPIO_PIN_8				(uint16_t)(0x0100) //<! GPIO pin 9 selected
#define GPIO_PIN_9				(uint16_t)(0x0200) //<! GPIO pin 10 selected
#define GPIO_PIN_10				(uint16_t)(0x0400) //<! GPIO pin 11 selected
#define GPIO_PIN_11				(uint16_t)(0x0800) //<! GPIO pin 12 selected
#define GPIO_PIN_12				(uint16_t)(0x1000) //<! GPIO pin 13 selected
#define GPIO_PIN_13				(uint16_t)(0x2000) //<! GPIO pin 14 selected
#define GPIO_PIN_14				(uint16_t)(0x4000) //<! GPIO pin 15 selected
#define GPIO_PIN_15				(uint16_t)(0x8000) //<! GPIO pin 16 selected
#define GPIO_PIN_ALL			(uint16_t)(0xFFFF) //<! GPIO all pin selected

/*
 *
 * @def_group GPIO_Pin_Modes
 *
 */
#define GPIO_MODE_INPUT 					(0x0U)
#define GPIO_MODE_OUTPUT					(0x1U)
#define GPIO_MODE_ALTERNATE_FUNCTİON		(0x2U)
#define GPIO_MODE_ANALOG					(0x3U)

/*
 *
 * @def_group GPIO_Otype_Mode
 *
 */

#define GPIO_OTYPE_PP					(0x0U)
#define GPIO_OTYPE_OD					(0x1U)

/*
 *
 * @def_group GPIO_PuPd_Mode
 *
 */

#define GPIO_PUPD_NOPULL				(0x0U)
#define GPIO_PUPD_PULL_UP				(0x1U)
#define GPIO_PUPD_PULL_DOWN				(0x2U)

/*
 *
 * @def_group GPIO_Speed_ModeS
 *
 */
#define GPIO_SPEED_MODE_LOW				(0x0U)
#define GPIO_SPEED_MODE_MEDİUM			(0x1U)
#define GPIO_SPEED_MODE_HİGH			(0x2U)

/*
 * @def_groups GPIO_Alternate_Mode
 */
#define GPIO_AF_0						(0x0U)
#define GPIO_AF_1						(0x1U)
#define GPIO_AF_2						(0x2U)
#define GPIO_AF_3						(0x3U)
#define GPIO_AF_4						(0x4U)
#define GPIO_AF_5						(0x5U)
#define GPIO_AF_6						(0x6U)
#define GPIO_AF_7						(0x7U)


typedef enum
{
	GPIO_RESET_PIN= 0x0U,
	GPIO_SET_PIN =!GPIO_RESET_PIN

}GPIO_Pin_State_t;

typedef struct
{
	uint32_t pinNumber; //!> GPIO pin numbers @def_groups GPIO_Pins
	uint32_t Mode;		//!> GPIO pin numbers @def_groups GPIO_Pin_Modes
	uint32_t Otype;		//!> GPIO pin numbers @def_groups GPIO_Otype_Mode
	uint32_t PuPd;		//!> GPIO pin numbers @def_groups GPIO_PuPd_Mode
	uint32_t Speed;		//!> GPIO pin numbers @def_groups GPIO_Speed_Modes
	uint32_t Alternate; //!> GPIO pin numbers @def_groups GPIO_Alternate_Mode

}GPIO_InitTypeDef_t;

void GPIO_Init(GPIO_TypeDef_t *GPIOx, GPIO_InitTypeDef_t *GPIO_ConfigStruct);
void GPIO_WritePin(GPIO_TypeDef_t *GPIOx,uint16_t pinNumber, GPIO_Pin_State_t pinState);
GPIO_Pin_State_t GPIO_ReadPin(GPIO_TypeDef_t *GPIOx,uint16_t pinNumber);
void GPIO_LockPin(GPIO_TypeDef_t *GPIOx,uint16_t pinNumber);
void GPIO_TogglePin(GPIO_TypeDef_t *GPIOx,uint16_t pinNumber);




#endif /* INC_GPIO_H_ */



