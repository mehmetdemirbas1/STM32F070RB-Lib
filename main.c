
#include "stm32F070xx.h"

static void GPIO_LED_Config();
static void GPIO_ButtonInterruptConfig();
static void SPI_Config();
static void SPI_GPIO_Config();

SPI_HandleTypeDef_t SPI_Handle;

void EXTI0_1_IRQHandler()
{
	char msgToSend[] = "Hello World\n";
	if (EXTI->EXTI_PR & 0x1)
	{
		EXTI->EXTI_PR |= (0x1U << 0U);
		SPI_TransmitData_IT(&SPI_Handle, (uint8_t*)msgToSend, strlen(msgToSend))  ;
	}
}
void SPI1_IRQHandler()
{
	SPI_InterruptHandler(&SPI_Handle);
}

int main(void)
{
	GPIO_LED_Config();

	GPIO_ButtonInterruptConfig();

	SPI_GPIO_Config();
	SPI_Config();



 	for(;;)
	{

	}
}
static void GPIO_LED_Config()
{

	GPIO_InitTypeDef_t GPIO_LedStruckt = {0};

	RCC_GPIOA_CLK_ENABLE();
	RCC_GPIOD_CLK_ENABLE();


	GPIO_LedStruckt.pinNumber = GPIO_PIN_0;
	GPIO_LedStruckt.Mode = GPIO_MODE_OUTPUT;
	GPIO_LedStruckt.Otype =GPIO_OTYPE_PP;
	GPIO_LedStruckt.PuPd=GPIO_PUPD_NOPULL;
	GPIO_LedStruckt.Speed=GPIO_SPEED_MODE_HİGH;

	GPIO_Init(GPIOA, &GPIO_LedStruckt);
	EXTI_LineConfig(EXTI_PORT_SOURCE_GPIOC, EXTI_LINE_SOURCE_7);
}

static void GPIO_ButtonInterruptConfig()
{
	EXTI_InitTypeDef_t EXTI_Init_struct ={0};

	RCC_SYSCFG_CLK_ENABLE();
	EXTI_LineConfig(EXTI_PORT_SOURCE_GPIOA, EXTI_LINE_SOURCE_0);


	EXTI_Init_struct.EXTI_LineCmd=ENABLE;
	EXTI_Init_struct.EXTI_LineNumber=EXTI_LINE_SOURCE_0;
	EXTI_Init_struct.EXTI_Mode=EXTI_MODE_INTERRUPT;
	EXTI_Init_struct.TriggerSelection=EXTI_Trigger_Rising;

	EXTI_Init(&EXTI_Init_struct);
	NVIC_EnableInterrupt(EXTI0_1_IRQNumber);

}
static void SPI_Config()
{
	RCC_SPI1_CLK_ENABLE();


	SPI_Handle.Instance =SPI1;
	SPI_Handle.Init.BoudRate = SPI_BAUDRATE_DİV8;
	SPI_Handle.Init.BusConfig = SPI_BUS_FULLDUPLEX;
	SPI_Handle.Init.CPHA = SPI_CPHA_FIRST;
	SPI_Handle.Init.CPOL = SPI_CPOL_LOW;
	SPI_Handle.Init.CRC_Format = SPI_CRC_8BIT;
	SPI_Handle.Init.FrameFormat = SPI_FRAMEFORMAT_MSB;
	SPI_Handle.Init.Mode = SPI_MODE_MASTER;
	SPI_Handle.Init.SSM_Cmd = SPI_SSM_ENABLE;

	SPI_Init(&SPI_Handle);

	NVIC_EnableInterrupt(SPI1_IRQNumber);

	SPI_PeripCmd(&SPI_Handle, ENABLE);

}
static void SPI_GPIO_Config()
{

	GPIO_InitTypeDef_t GPIO_InitStruct = {0};
	GPIO_InitStruct.pinNumber = GPIO_PIN_5 | GPIO_PIN_7; // PA5=SCK, PA7=MOSI
	GPIO_InitStruct.Mode = GPIO_MODE_ALTERNATE_FUNCTİON;
	GPIO_InitStruct.Otype = GPIO_OTYPE_PP;
	GPIO_InitStruct.PuPd = GPIO_PUPD_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_MODE_HİGH;
	GPIO_InitStruct.Alternate = GPIO_AF_0;

	GPIO_Init(GPIOA, &GPIO_InitStruct);


}

