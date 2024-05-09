#ifndef INC_RCC_H_
#define INC_RCC_H_

#include "stm32F070xx.h"

/*
 * RCC AHB pripherals clock control macros
 */

#define RCC_GPIOA_CLK_ENABLE()					do{ uint32_t tempValue=0;  \
													SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOAEN);  \
													tempValue= READ_BIT(RCC->AHBENR, RCC_AHBENR_GPIOAEN);    \
	 	 	 	 	 	 	 	 	 	 	 	 	UNUSED(tempValue) ;     \
	     	 	 	 	 	 	 	 	 	       }while(0);

#define RCC_GPIOB_CLK_ENABLE()					do{ uint32_t tempValue=0;  \
													SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOBEN);  \
													tempValue= READ_BIT(RCC->AHBENR, RCC_AHBENR_GPIOBEN);    \
	 	 	 	 	 	 	 	 	 	 	 	 	UNUSED(tempValue) ;     \
	     	 	 	 	 	 	 	 	 	       }while(0);

#define RCC_GPIOC_CLK_ENABLE()					do{ uint32_t tempValue=0;  \
													SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIOCEN);  \
													tempValue= READ_BIT(RCC->AHBENR, RCC_AHBENR_GPIOCEN);    \
	 	 	 	 	 	 	 	 	 	 	 	 	UNUSED(tempValue) ;     \
	     	 	 	 	 	 	 	 	 	       }while(0);

#define RCC_GPIOD_CLK_ENABLE()					do{ uint32_t tempValue=0;  \
													SET_BIT(RCC->AHBENR, RCC_AHBENR_GPIODEN);  \
													tempValue= READ_BIT(RCC->AHBENR, RCC_AHBENR_GPIODEN);    \
	 	 	 	 	 	 	 	 	 	 	 	 	UNUSED(tempValue) ;     \
	     	 	 	 	 	 	 	 	 	       }while(0);
#define RCC_GPIOA_CLK_DISABLE()					CLEAR_BIT(RCC->AHBENR,RCC_AHBENR_GPIOAEN)
#define RCC_GPIOB_CLK_DISABLE()					CLEAR_BIT(RCC->AHBENR,RCC_AHBENR_GPIOBEN)
#define RCC_GPIOC_CLK_DISABLE()					CLEAR_BIT(RCC->AHBENR,RCC_AHBENR_GPIOCEN)
#define RCC_GPIOD_CLK_DISABLE()					CLEAR_BIT(RCC->AHBENR,RCC_AHBENR_GPIODEN)

/*
 * RCC APB2 pripherals clock control macros
 */

#define RCC_SYSCFG_CLK_ENABLE()					do{ uint32_t tempValue=0;  \
													SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);  \
													tempValue= READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);    \
	 	 	 	 	 	 	 	 	 	 	 	 	UNUSED(tempValue) ;     \
	     	 	 	 	 	 	 	 	 	       }while(0);
#define RCC_SYSCFG_CLK_DISABLE()				CLEAR_BIT(RCC->APB2ENR,RCC_APB2ENR_SYSCFGEN)


#define RCC_SPI1_CLK_ENABLE()					do{ uint32_t tempValue=0;  \
													SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);  \
													tempValue= READ_BIT(RCC->APB2ENR, RCC_APB2ENR_SPI1EN);    \
	 	 	 	 	 	 	 	 	 	 	 	 	UNUSED(tempValue) ;     \
	     	 	 	 	 	 	 	 	 	       }while(0);
#define RCC_SPI1_CLK_DISABLE()					CLEAR_BIT(RCC->APB2ENR,RCC_APB2ENR_SPI1EN)

/*
 * RCC APB1 pripherals clock control macros
 */

#define RCC_SPI2_CLK_ENABLE()					do{ uint32_t tempValue=0;  \
													SET_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN);  \
													tempValue= READ_BIT(RCC->APB1ENR, RCC_APB1ENR_SPI2EN);    \
	 	 	 	 	 	 	 	 	 	 	 	 	UNUSED(tempValue) ;     \
	     	 	 	 	 	 	 	 	 	       }while(0);
#define RCC_SPI2_CLK_DISABLE()					CLEAR_BIT(RCC->APB1ENR,RCC_APB1ENR_SPI1EN)








#endif /* INC_RCC_H_ */




