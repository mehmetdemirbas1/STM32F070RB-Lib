#ifndef INC_STM32F070XX_H_
#define INC_STM32F070XX_H_

#include <stdint.h>
#include <string.h>
#include <stddef.h>

/*
 * Microprocessor Define
 *
 */

#define NVIC_ISER0					((uint32_t*)(0xE000E100UL))

#define __IO volatile

#define SET_BIT(REG, BIT)			( (REG)|=  (BIT) )
#define CLEAR_BIT(REG, BIT)			( (REG)&= ~(BIT) )
#define READ_BIT(REG, BIT)			( (REG)&   (BIT) )
#define UNUSED(x)					(void)x

typedef enum
{
	DISABLE = 0x0U,
	ENABLE = !DISABLE

}FunctionalState_t;


/*
 * IRQ Numbers of MCU = Vector Table
 */

typedef enum
{

	EXTI0_1_IRQNumber=5,
	EXTI2_3_IRQNumber=6,
	EXTI4_15_IRQNumber=7,
	SPI1_IRQNumber=25,
	SPI2_IRQNumber=26

}IRQNumber_TypeDef_t;

/*
 * Memory Base Address
 */
#define FLASH_BASE_ADDR				(0x08000000UL)				    // Flash Base Address (128kb)
#define SRAM_BASE_ADDR				(0x20000000UL)				    // SRAM Base Address  (16kb)

/*
 * Peripheral Base Addresses
 */
#define PERIPH_BASE_ADDR			(0x40000000UL)				     // Base Address For All Peripherals
#define APB_BASE_ADDR				(PERIPH_BASE_ADDR) 			     // APB Bus Domain Base Address
#define AHB1_BASE_ADDR				(PERIPH_BASE_ADDR + 0x20000UL)   // 0x40020000 AHB1 Bus Domain Address
#define AHB2_BASE_ADDR				(PERIPH_BASE_ADDR + 0x8000000UL) // 0X48000000 AHB2 Bus Domain Address


/*
 * APB Peripherals Base Address
 */

#define TİM3_BASE_ADDR				(APB_BASE_ADDR + 0x0400UL)		  // Timer 3 Base Address
#define TİM6_BASE_ADDR				(APB_BASE_ADDR + 0x1000UL)		  // Timer 6 Base Address
#define TİM7_BASE_ADDR				(APB_BASE_ADDR + 0x1400UL)		  // Timer 7 Base Address
#define TİM14_BASE_ADDR				(APB_BASE_ADDR + 0x2000UL)		  // Timer 14 Base Address

#define SPI1_BASE_ADDR				(APB_BASE_ADDR + 0x13000UL)	 	  // SPI 1 Base Address
#define SPI2_BASE_ADDR				(APB_BASE_ADDR + 0x3800UL)		  // SPI 2 Base Address

#define USART1_BASE_ADDR			(APB_BASE_ADDR + 0x13800UL)		  // USART 1 Base Address
#define USART2_BASE_ADDR			(APB_BASE_ADDR + 0x4400UL)		  // USART 2 Base Address
#define USART3_BASE_ADDR			(APB_BASE_ADDR + 0x4800UL)		  // USART 3 Base Address

#define I2C1_BASE_ADDR				(APB_BASE_ADDR + 0x5400UL)		  // I2C 1 Base Address
#define I2C2_BASE_ADDR				(APB_BASE_ADDR + 0x5800UL)		  // I2C 2 Base Address

#define SYSCFG_BASE_ADDR			(APB_BASE_ADDR + 0X10000UL)		  // SYSCFG Base Address
#define EXTI_BASE_ADDR				(APB_BASE_ADDR + 0X10400UL)		  // EXTI Base Address

/*
 * AHB1 Peripherals Base Address
 */

#define DMA_BASE_ADDR				(AHB1_BASE_ADDR + 0x0000UL) 	  // DMA Base Address
#define RCC_BASE_ADDR				(AHB1_BASE_ADDR + 0x1000UL)		  // RCC Base Address
#define CRC_BASE_ADDR				(AHB1_BASE_ADDR + 0x3000UL)		  // CRC Base Address

/*
 * AHB2 Peripherals Base Address
 */

#define GPIOA_BASE_ADDR				(AHB2_BASE_ADDR + 0x0000UL)		  //GPIO A Base Address
#define GPIOB_BASE_ADDR				(AHB2_BASE_ADDR + 0x0400UL)		  //GPIO B Base Address
#define GPIOC_BASE_ADDR				(AHB2_BASE_ADDR + 0x0800UL)		  //GPIO C Base Address
#define GPIOD_BASE_ADDR				(AHB2_BASE_ADDR + 0x0C00UL)		  //GPIO D Base Address

/*
 * Peripheral Structures Definitions
 */

typedef struct
{
	__IO uint32_t MODER;			//!< GPIO port mode register                   Address Offset = 0x00
	__IO uint32_t OTYPER;			//!< GPIO port output type register            Address Offset = 0x04
	__IO uint32_t OSPEEDR;			//!< GPIO port output speed register           Address Offset = 0x08
	__IO uint32_t PUPDR;			//!< GPIO port pull-up/pull-down register      Address Offset = 0x0C
	__IO uint32_t IDR;				//!< GPIO port input data register             Address Offset = 0x10
	__IO uint32_t ODR;				//!< GPIO port output data register            Address Offset = 0x14
	__IO uint32_t BSRR;				//!< GPIO port bit set/reset register          Address Offset = 0x18
	__IO uint32_t LCKR;				//!< GPIO port configuration lock register     Address Offset = 0x1C
	__IO uint32_t AFR[2];			//!< GPIO alternate function low/high register Address Offset = low=0x20-high=0x24


}GPIO_TypeDef_t;

typedef struct
{
	__IO uint32_t CR;               //!< RCC Clock control register                 			Address offset: 0x00
	__IO uint32_t CFGR;             //!< RCC Clock configuration register           			Address offset: 0x04
	__IO uint32_t CIR;              //!< RCC Clock interrupt register               			Address offset: 0x08
	__IO uint32_t APB2RSTR;         //!< RCC APB peripheral reset register 2        			Address offset: 0x0C
	__IO uint32_t APB1RSTR;         //!< RCC APB peripheral reset register 1        			Address offset: 0x10
	__IO uint32_t AHBENR;           //!< RCC AHB peripheral clock enable register   			Address offset: 0x14
	__IO uint32_t APB2ENR;          //!< RCC APB peripheral clock enable register 2 			Address offset: 0x18
	__IO uint32_t APB1ENR;          //!< RCC APB peripheral clock enable register 1 			Address offset: 0x1C
	__IO uint32_t BDCR;             //!< RCC RTC domain control register            			Address offset: 0x20
	__IO uint32_t CSR;              //!< RCC Control/status register                			Address offset: 0x24
	__IO uint32_t AHBRSTR;          //!< RCC AHB peripheral reset register          			Address offset: 0x28
	__IO uint32_t CFGR2;            //!< RCC Clock configuration register 2         			Address offset: 0x2C
	__IO uint32_t CFGR3;            //!< RCC Clock configuration register 3         			Address offset: 0x30
	__IO uint32_t CR2;              //!< RCC Clock control register 2             			    Address offset: 0x34

}RCC_TypeDef_t;

typedef struct
{
	__IO uint32_t SYSCFG_CFGR1;		//!< SYSCFG configuration register 1						Address offset: 0x00
	__IO uint32_t Reserved;			//!< SYSCFG configuration register 1						Address offset: 0x00
	__IO uint32_t SYSCFG_EXTICR[4];	//!< SYSCFG external interrupt configuration register 		Address offset: 0x08
	__IO uint32_t SYSCFG_CFGR2;		//!< SYSCFG configuration register 2						Address offset: 0x18

}SYSCFG_TypeDef_t;

typedef struct
{
	__IO uint32_t EXTI_IMR;			//!< Interrupt mask register								Address offset: 0x00
	__IO uint32_t EXTI_EMR;			//!< Event mask register									Address offset: 0x04
	__IO uint32_t EXTI_RTSR;		//!< Rising trigger selection register						Address offset: 0x08
	__IO uint32_t EXTI_FTSR;		//!< Falling trigger selection register						Address offset: 0x0C
	__IO uint32_t EXTI_SWIER;		//!< Software interrupt event register						Address offset: 0x10
	__IO uint32_t EXTI_PR;			//!< Pending register										Address offset: 0x14

}EXTI_TypeDef_t;

typedef struct
{
	__IO uint32_t CR1;				//!< SPI control register 1									Address offset: 0x00
	__IO uint32_t CR2;				//!< SPI control register 2									Address offset: 0x04
	__IO uint32_t SR;				//!< SPI status register									Address offset: 0x08
	__IO uint32_t DR;				//!< SPI data register	 									Address offset: 0x0C
	__IO uint32_t CRCPR;			//!< SPI CRC polynomial register							Address offset: 0x10
	__IO uint32_t RXCRCR;			//!< SPI Rx CRC register									Address offset: 0x14
	__IO uint32_t TXCRCR;			//!< SPI Tx CRC register									Address offset: 0x18

}SPI_TypeDef_t;

#define GPIOA    					   ((GPIO_TypeDef_t *)(GPIOA_BASE_ADDR))
#define GPIOB    					   ((GPIO_TypeDef_t *)(GPIOB_BASE_ADDR))
#define GPIOC    					   ((GPIO_TypeDef_t *)(GPIOC_BASE_ADDR))
#define GPIOD    					   ((GPIO_TypeDef_t *)(GPIOD_BASE_ADDR))

#define RCC							   ((RCC_TypeDef_t *)( RCC_BASE_ADDR  ))

#define SYSCFG						   ((SYSCFG_TypeDef_t *)(SYSCFG_BASE_ADDR))

#define EXTI						   ((EXTI_TypeDef_t*)(EXTI_BASE_ADDR))

#define SPI1						   ((SPI_TypeDef_t*)(SPI1_BASE_ADDR))
#define SPI2						   ((SPI_TypeDef_t*)(SPI2_BASE_ADDR))


/*
 * Bit Definations
 */

#define RCC_AHBENR_GPIOAEN_Pos			(17U)							 	// RCC AHBENR register GPIOAEN bit position
#define RCC_AHBENR_GPIOAEN_Msk			(0x1 << RCC_AHBENR_GPIOAEN_Pos) 	// RCC AHBENR register GPIOAEN bit mask
#define RCC_AHBENR_GPIOAEN				 RCC_AHBENR_GPIOAEN_Msk          	// RCC AHBENR register GPIOAEN macro

#define RCC_AHBENR_GPIOBEN_Pos			(18U)							 	// RCC AHBENR register GPIOBEN bit position
#define RCC_AHBENR_GPIOBEN_Msk			(0x1 << RCC_AHBENR_GPIOBEN_Pos)  	// RCC AHBENR register GPIOBEN bit mask
#define RCC_AHBENR_GPIOBEN				 RCC_AHBENR_GPIOBEN_Msk          	// RCC AHBENR register GPIOBEN macro

#define RCC_AHBENR_GPIOCEN_Pos			(19U)							 	// RCC AHBENR register GPIOCEN bit position
#define RCC_AHBENR_GPIOCEN_Msk			(0x1 << RCC_AHBENR_GPIOCEN_Pos) 	// RCC AHBENR register GPIOCEN bit mask
#define RCC_AHBENR_GPIOCEN				 RCC_AHBENR_GPIOCEN_Msk          	// RCC AHBENR register GPIOCEN macro

#define RCC_AHBENR_GPIODEN_Pos			(20U)							 	// RCC AHBENR register GPIODEN bit position
#define RCC_AHBENR_GPIODEN_Msk			(0x1 << RCC_AHBENR_GPIODEN_Pos)  	// RCC AHBENR register GPIODEN bit mask
#define RCC_AHBENR_GPIODEN				 RCC_AHBENR_GPIODEN_Msk          	// RCC AHBENR register GPIODEN macro

#define RCC_APB2ENR_SYSCFGEN_Pos		(0U)								// RCC APB2ENR register SYSCFG bit position
#define RCC_APB2ENR_SYSCFGEN_Msk		(0x1 << RCC_APB2ENR_SYSCFGEN_Pos)	// RCC APB2ENR register SYSCFG bit mask
#define RCC_APB2ENR_SYSCFGEN			 RCC_APB2ENR_SYSCFGEN_Msk			// RCC APB2ENR register SYSCFG macro

#define RCC_APB2ENR_SPI1EN_Pos			(12U)								// RCC APB2ENR register SPI1 bit position
#define RCC_APB2ENR_SPI1EN_Mas			(0x1 << RCC_APB2ENR_SPI1EN_Pos)		// RCC APB2ENR register SPI1 bit mask
#define RCC_APB2ENR_SPI1EN				RCC_APB2ENR_SPI1EN_Mas				// RCC APB2ENR register SPI1 bit macro

#define RCC_APB1ENR_SPI2EN_Pos			(14U)								// RCC APB1ENR register SPI1 bit position
#define RCC_APB1ENR_SPI2EN_Mas			(0x1 << RCC_APB1ENR_SPI2EN_Pos)		// RCC APB1ENR register SPI1 bit mask
#define RCC_APB1ENR_SPI2EN				RCC_APB1ENR_SPI2EN_Mas				// RCC APB1ENR register SPI1 bit macro

#define SPI_CR1_SPE						(6U)
#define SPI_CR1_DFF						(11U)

#define SPI_SR_TXE						(1U)
#define SPI_SR_BUSY						(7U)
#define SPI_SR_RxNE						(0U)

#define SPI_CR2_TXEIE					(7U)

/*
 * Flag Definations
 */
#define SPI_TXE_FLAG					(0x1U << SPI_SR_TXE)
#define SPI_BUSY_FLAG					(0x1U << SPI_SR_BUSY)
#define SPI_RxNE_FLAG					(0x1U << SPI_SR_RxNE)

#include "RCC.h"
#include "GPIO.h"
#include "EXTI.h"
#include "SPI.h"





#endif /* INC_STM32F070XX_H_ */





