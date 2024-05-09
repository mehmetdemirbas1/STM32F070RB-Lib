#include "EXTI.h"

/*
 * @brief EXTI_Init for valid GPIO port and Line number
 * @param EXTI_InitStruct = User config structures
 *
 * @retval void
 */

void EXTI_Init(EXTI_InitTypeDef_t *EXTI_InitStruct)
{
	uint32_t tempValue=0;
	tempValue = (uint32_t)EXTI_BASE_ADDR;
	EXTI->EXTI_IMR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
	EXTI->EXTI_EMR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
	if (EXTI_InitStruct->EXTI_LineCmd != DISABLE)
	{
		tempValue += EXTI_InitStruct->EXTI_Mode;

		*( (__IO uint32_t*)tempValue) = (0x1U << EXTI_InitStruct->EXTI_LineNumber);

		tempValue = (uint32_t)EXTI_BASE_ADDR;
		EXTI->EXTI_RTSR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
		EXTI->EXTI_FTSR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
		if (EXTI_InitStruct->TriggerSelection == EXTI_Trigger_RF)
		{
			EXTI->EXTI_RTSR |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);
			EXTI->EXTI_FTSR |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);
		}
		else
		{
			tempValue += EXTI_InitStruct->TriggerSelection;
			*((__IO uint32_t*)tempValue) |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);
		}
	}
	else
	{
		tempValue = (uint32_t)EXTI_BASE_ADDR;
		tempValue += EXTI_InitStruct->EXTI_Mode;
		*((__IO uint32_t*)tempValue) &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
	}
}

/*
 * @brief EXTI_LineConfig, configures the ports and pin for SYSCFG
 * @param PortSource = Port value A - D @def_droup PORT_VALUES
 *
 * @param EXTI_LineSource = Pin numbers & Line Numbers @def_droup EXTI_Line_Values
 *
 * @retval void
 */


void EXTI_LineConfig(uint8_t PortSource, uint8_t EXTI_LineSource)
{
	uint32_t tempValue;
	tempValue =SYSCFG->SYSCFG_EXTICR[EXTI_LineSource >> 2U];
	tempValue &= ~(0xFU << (EXTI_LineSource & 0x3U)*4);
	tempValue = (PortSource << (EXTI_LineSource & 0x3U)*4);
	SYSCFG->SYSCFG_EXTICR[EXTI_LineSource >> 2U]=tempValue;
}

/*
 * @brief NVIC_EnableInterrupt for valid GPIO port and Line number
 * @param IRQNumber = User select IRQ numbers
 *
 * @retval void
 */

void NVIC_EnableInterrupt(IRQNumber_TypeDef_t IRQNumber)
{
	uint32_t tempValue=0;
	tempValue = *((IRQNumber >> 5U )+ NVIC_ISER0 );
	tempValue &= ~(0x1U << (IRQNumber & 0x1F) );
	tempValue |=  (0x1U << (IRQNumber & 0x1F) );
	*((IRQNumber >> 5U)+ NVIC_ISER0 ) = tempValue;
}








