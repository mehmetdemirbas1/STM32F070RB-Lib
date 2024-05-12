#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "stm32F070xx.h"

typedef enum
{
	SPI_BUS_FREE = 0x0U,
	SPI_BUS_BUSY_TX = 0x1U,
	SPI_BUS_BUSY_RX = 0x2U
}SPI_BusStatus_t;

typedef enum
{
	SPI_FLAG_RESET = 0x0U,
	SPI_FLAG_SET = !SPI_FLAG_RESET
}SPI_FlagStatus_t;

/*
 * @def_groups SPI_BaudRates
 */
#define SPI_BAUDRATE_DİV2				((uint32_t)(0x00000000))
#define SPI_BAUDRATE_DİV4				((uint32_t)(0x00000008))
#define SPI_BAUDRATE_DİV8				((uint32_t)(0x00000010))
#define SPI_BAUDRATE_DİV16				((uint32_t)(0x00000018))
#define SPI_BAUDRATE_DİV32				((uint32_t)(0x00000020))
#define SPI_BAUDRATE_DİV64				((uint32_t)(0x00000028))
#define SPI_BAUDRATE_DİV128				((uint32_t)(0x00000030))
#define SPI_BAUDRATE_DİV256				((uint32_t)(0x00000038))


/*
 * @def_groups CPHA_Values
 */
#define SPI_CPHA_FIRST					((uint32_t)(0x00000000))
#define SPI_CPHA_SECOND					((uint32_t)(0x00000001))

/*
 *
 * @def_groups CPOL_Values
 */
#define SPI_CPOL_LOW					((uint32_t)(0x00000000))
#define SPI_CPOL_HIGH					((uint32_t)(0x00000002))

/*
 * @def_groups CRC_Values
 */
#define SPI_CRC_8BIT					((uint32_t)(0x00000000))
#define SPI_CRC_16BIT					((uint32_t)(0x00000800))

/*
 * @def_groups Mode_Values
 */
#define SPI_MODE_SLAVE					((uint32_t)(0x00000000))
#define SPI_MODE_MASTER					((uint32_t)(0x00000004))

/*
 * @def_groups LSBFIRST_Values
 */
#define SPI_FRAMEFORMAT_MSB				((uint32_t)(0x00000000))
#define SPI_FRAMEFORMAT_LSB 			((uint32_t)(0x00000080))

/*
 * @def_groups SPI_BusConfig
 */
#define SPI_BUS_FULLDUPLEX				((uint32_t)(0x00000000))
#define SPI_BUS_RECİVEONLY				((uint32_t)(0x00000400))
#define SPI_BUS_HALFDUPLEX_T			((uint32_t)(0x0000C000))
#define SPI_BUS_HALFDUPLEX_R			((uint32_t)(0x00008000))

/*
 * @def_groups SSM_Values
 */
#define SPI_SSM_DISABLE					((uint32_t)(0x00000000))
#define SPI_SSM_ENABLE					((uint32_t)(0x00000300))

typedef struct
{
	uint32_t Mode;						//!> Mode Values @def_groups Mode_Values
	uint32_t CPHA;						//!> CPHA for SPI @def_groups CPHA_Values
	uint32_t CPOL;						//!> CPOL for SPI @def_groups CPOL_Values
	uint32_t BoudRate;					//!> BaudRates for SPI @def_groups SPI_BaudRates
	uint32_t SSM_Cmd;					//!> SSM Values @def_groups SSM_Values
	uint32_t CRC_Format;				//!> CRC Value for SPI @def_groups CRC_Values
	uint32_t BusConfig;					//!> BusConfig for SPI @def_groups SPI_BusConfig
	uint32_t FrameFormat;				//!> LSBFIRST values  @def_groups LSBFIRST_Values

}SPI_InitTypeDef_t;

typedef struct __SPI_HandleTypeDef_t
{
	SPI_TypeDef_t *Instance;
	SPI_InitTypeDef_t Init;
	uint8_t *pTxDataAddr;
	uint16_t TxDataSize;
	uint8_t busState_Tx;
	void(*TxISRFunction)(struct __SPI_HandleTypeDef_t *SPI_Handle);
	uint8_t busState_Rx;
	uint8_t *pRxDataAddr;
	uint16_t RxDataSize;
	void(*RxISRFunction)(struct __SPI_HandleTypeDef_t *SPI_Handle);

}SPI_HandleTypeDef_t;

void SPI_Init(SPI_HandleTypeDef_t *SPI_Handle);
void SPI_PeripCmd(SPI_HandleTypeDef_t *SPI_Handle, FunctionalState_t stateofSPI);
void SPI_TransmitData(SPI_HandleTypeDef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData);
void SPI_ReceiveData(SPI_HandleTypeDef_t *SPI_Handle, uint8_t *pBuffer, uint16_t sizeOfData);
void SPI_TransmitData_IT(SPI_HandleTypeDef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData);
void SPI_ReceiveData_IT(SPI_HandleTypeDef_t *SPI_Handle, uint8_t *pBuffer, uint16_t sizeOfData);
void SPI_InterruptHandler(SPI_HandleTypeDef_t *SPI_Handle);
SPI_FlagStatus_t SPI_GetFlagStatus(SPI_HandleTypeDef_t *SPI_Handle, uint16_t SPI_Flag);




#endif /* INC_SPI_H_ */
