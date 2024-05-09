#include "GPIO.h"

/*
 * @brief GPIO_Init, configures for ports and pins
 * @param GPIOx = GPIO port base address
 *
 * @param *GPIO_ConfigStruct = User config structures
 *
 * @retval void
 */

void GPIO_Init(GPIO_TypeDef_t *GPIOx, GPIO_InitTypeDef_t *GPIO_ConfigStruct)
{
	uint32_t position;
	uint32_t fakePosition=0;
	uint32_t lastPosition=0;
	for (position = 0; position < 16; ++position)
	{
		fakePosition = (0x1 << position);
		lastPosition = (uint32_t)(GPIO_ConfigStruct->pinNumber)& fakePosition;

		if(fakePosition == lastPosition)
		{
			/* MODE CONFİG */

			uint32_t tempValue =GPIOx->MODER;
			tempValue &= ~(0x3U << (position*2) );
			tempValue |= (GPIO_ConfigStruct->Mode << (position*2) );
			GPIOx->MODER =tempValue;

			if (GPIO_ConfigStruct->Mode == GPIO_MODE_OUTPUT || GPIO_ConfigStruct->Mode == GPIO_MODE_ANALOG )
					{
						/* Output Type CONFİG */
						tempValue=GPIOx->OTYPER;
						tempValue &= ~(0x1U << position);
						tempValue |= (GPIO_ConfigStruct->Otype << position);
						GPIOx->OTYPER =tempValue;

						/* Output Speed CONFİG */
						tempValue=GPIOx->OSPEEDR;
						tempValue &=~(0x3u << (position*2));
						tempValue |= (GPIO_ConfigStruct->Speed << (position*2) );
						GPIOx->OSPEEDR = tempValue;

					}
			/* PuPd Type CONFİG */

			tempValue = GPIOx->PUPDR;
			tempValue &= ~ (0x3U <<(position*2));
			tempValue |= (GPIO_ConfigStruct->PuPd << (position*2) );
			GPIOx->PUPDR=tempValue;

			/* AF CONFİG */
			if(GPIO_ConfigStruct->Mode == GPIO_MODE_ALTERNATE_FUNCTİON)
					{
						tempValue=GPIOx->AFR[position >> 3U ];
						tempValue &= ~(0XFU <<((position & 0x7U)*4));
						tempValue |= (GPIO_ConfigStruct->Alternate << ((position & 0x7U)*4));
						GPIOx->AFR[position >> 3U ]= tempValue;
					}

		}

	}


}

/*
 * @brief GPIO_Write_Pin, makes pin high or low
 * @param GPIOx = GPIO port base address
 *
 * @param GPIO pin numbers 0-15
 *
 * @param GPIO_RESET_PIN or GPIO_SET_PIN
 *
 * @retval void
 */

void GPIO_WritePin(GPIO_TypeDef_t *GPIOx,uint16_t pinNumber, GPIO_Pin_State_t pinState)
{
	if(pinState == pinNumber)
		GPIOx->BSRR =pinNumber;
	else
		GPIOx->BSRR=(pinNumber << 16U);

}

/*
 * @brief GPIO_ReadPin, reads the pin of GPIOx port
 * @param GPIOx = GPIO port base address
 *
 * @param GPIO pin numbers 0-15
 *
 * @retval GPIO_Pin_State_t
 */

GPIO_Pin_State_t GPIO_ReadPin(GPIO_TypeDef_t *GPIOx,uint16_t pinNumber)
{
	GPIO_Pin_State_t bitStatus = GPIO_RESET_PIN;

	if((GPIOx->IDR &pinNumber)!= GPIO_RESET_PIN)
		{
			bitStatus= GPIO_SET_PIN;
		}
	return bitStatus;

}

/*
 * @brief GPIO_LockPin, Locks the pin of GPIOx port
 * @param GPIOx = GPIO port base address
 *
 * @param GPIO pin numbers 0-15
 *
 * @retval Void
 */

void GPIO_LockPin(GPIO_TypeDef_t *GPIOx,uint16_t pinNumber)
{
	uint32_t tempValue = (0x1U << 16U) | pinNumber;

	GPIOx->LCKR = tempValue;   // LCKR[16] = '1'    LCKR[15:0] = DATA
	GPIOx->LCKR = pinNumber;   // LCKR[16] = '0'    LCKR[15:0] = DATA
	GPIOx->LCKR = tempValue;   // LCKR[16] = '1'    LCKR[15:0] = DATA
	tempValue = GPIOx->LCKR;   // Read Lock Pin
}

/*
 * @brief GPIO_TogglePin, Toggles the pin of GPIOx port
 * @param GPIOx = GPIO port base address
 *
 * @param GPIO pin numbers 0-15
 *
 * @retval Void
 */

void GPIO_TogglePin(GPIO_TypeDef_t *GPIOx,uint16_t pinNumber)
{
	uint32_t tempODRRegister= GPIOx->ODR;
	GPIOx->BSRR = ((tempODRRegister & pinNumber) << 16U ) | (~tempODRRegister & pinNumber);

}






















