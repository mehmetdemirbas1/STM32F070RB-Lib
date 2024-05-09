#include "SPI.h"

static void SPI_CloseISR_Tx(SPI_HandleTypeDef_t *SPI_Handle)
{
	SPI_Handle->Instance->CR2 &= ~(0x1U << SPI_CR2_TXEIE);
	SPI_Handle->TxDataSize =0;
	SPI_Handle->pTxDataAddr =NULL;
	SPI_Handle->busState_Tx = SPI_BUS_FREE;

}

static void SPI_TransmitHelper_8Bits(SPI_HandleTypeDef_t *SPI_Handle )
{
	SPI_Handle->Instance->DR =*((uint8_t*)(SPI_Handle->pTxDataAddr));
	SPI_Handle->pTxDataAddr += sizeof(uint8_t);
	SPI_Handle->TxDataSize --;
}

static void SPI_TransmitHelper_16Bits(SPI_HandleTypeDef_t *SPI_Handle )
{
	SPI_Handle->Instance->DR =*((uint16_t*)(SPI_Handle->pTxDataAddr));
	SPI_Handle->pTxDataAddr += sizeof(uint16_t);
	SPI_Handle->TxDataSize -=2;

	if(SPI_Handle->TxDataSize == 0)
	{
		SPI_CloseISR_Tx(SPI_Handle);
	}
}

/*
 * @brief SPI_Init, configures for SPI peripherals
 *
 * @param SPI_Handle = User config structures
 *
 * @retval void
 */
void SPI_Init(SPI_HandleTypeDef_t *SPI_Handle)
{
	uint32_t tempValue=0;
	tempValue =SPI_Handle->Instance->CR1;
	tempValue |=(SPI_Handle->Init.BoudRate)   | (SPI_Handle->Init.CPHA)    | (SPI_Handle->Init.CPOL)        \
			  | (SPI_Handle->Init.CRC_Format) | (SPI_Handle->Init.Mode)    | (SPI_Handle->Init.FrameFormat) \
			  | (SPI_Handle->Init.BusConfig)  | (SPI_Handle->Init.SSM_Cmd);
	SPI_Handle->Instance->CR1 = tempValue;

}

/*
 * @brief SPI_PeripCmd, Enable or disable SPI peripherals
 *
 * @param SPI_Handle = User config structures
 *
 * @param stateofSPI = User config SPI state ENABLE or DISABLE
 *
 * @retval void
 */
void SPI_PeripCmd(SPI_HandleTypeDef_t *SPI_Handle, FunctionalState_t stateofSPI)
{
	if(stateofSPI == ENABLE)
		SPI_Handle->Instance->CR1 |= (0x1U << SPI_CR1_SPE);
	else
		SPI_Handle->Instance->CR1 &= ~(0x1U << SPI_CR1_SPE);
}

/*
 * @brief SPI_TransmitData, Sending transmit data to the slave
 *
 * @param SPI_Handle = User config structures
 *
 * @param pData = User send data
 *
 * @param sizeOfData = User data size
 *
 * @retval void
 */
void SPI_TransmitData(SPI_HandleTypeDef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData)
{
	if (SPI_GetFlagStatus(SPI_Handle,SPI_TXE_FLAG))
	{
		while(sizeOfData > 0)
		{
			SPI_Handle->Instance->DR = *((int16_t*)pData);
			pData += sizeof(uint16_t);
			sizeOfData-= 2;
		}

	}
	else
	{
		while(sizeOfData > 0)
				{
					SPI_Handle->Instance->DR=*pData;
					pData+=sizeof(uint8_t);
					sizeOfData--;
				}
	}
	while(SPI_GetFlagStatus(SPI_Handle, SPI_BUSY_FLAG)); // Wait for busy flag
}


void SPI_TransmitData_IT(SPI_HandleTypeDef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData)
{
	SPI_BusStatus_t busState= SPI_Handle->busState_Tx;
	if(busState != SPI_BUS_BUSY_TX)
	{
		SPI_Handle->pTxDataAddr = (uint8_t*)pData;
		SPI_Handle->TxDataSize = (uint16_t)sizeOfData;
		SPI_Handle->busState_Tx = SPI_BUS_BUSY_TX;

		if(SPI_Handle->Instance->CR1 & (0x1U << SPI_CR1_DFF))
		{
			SPI_Handle->TxISRFunction = SPI_TransmitHelper_16Bits;
		}
		else
		{
			SPI_Handle->TxISRFunction = SPI_TransmitHelper_8Bits;
		}
		SPI_Handle->Instance->CR2 = (0x1U << SPI_CR2_TXEIE);
	}

}

void SPI_InterruptHandler(SPI_HandleTypeDef_t *SPI_Handle)
{
	uint8_t interruptSource = 0;
	uint8_t interruptFlag = 0;
	interruptSource = SPI_Handle->Instance->CR2 & (0x1U << SPI_CR2_TXEIE);
	interruptFlag = SPI_Handle->Instance->SR & (0x1U << SPI_SR_TXE);

	if((interruptSource!=0) && (interruptFlag !=0) )
	{
		SPI_Handle->TxISRFunction(SPI_Handle);
	}
}

/*
 * @brief SPI_ReceiveData, Pulling Receive data from the slave
 *
 * @param SPI_Handle = User config structures
 *
 * @param pBuffer = Pulling get data
 *
 * @param sizeOfData = User data size
 *
 * @retval void
 */

void SPI_ReceiveData(SPI_HandleTypeDef_t *SPI_Handle, uint8_t *pBuffer, uint16_t sizeOfData)
{
	if(SPI_Handle->Init.CRC_Format == SPI_CRC_16BIT)
	{
		while(sizeOfData > 0)
		{
			if(SPI_GetFlagStatus(SPI_Handle, SPI_RxNE_FLAG))
			{
				*((uint16_t*)(pBuffer))= (uint16_t)SPI_Handle->Instance->DR;
				pBuffer +=sizeof(uint16_t);
				sizeOfData -=2;
			}
		}
	}
	else
	{
		while(sizeOfData > 0)
		{
			if(SPI_GetFlagStatus(SPI_Handle, SPI_RxNE_FLAG))
			{
				*(pBuffer)= *((__IO uint8_t*)&SPI_Handle->Instance->DR);
				pBuffer +=sizeof(uint8_t);
				sizeOfData --;
			}
		}
	}


}

/*
 * @brief SPI_GetFlagStatus, Return to Flag of SR register
 *
 * @param SPI_Handle = User config structures
 *
 * @param SPI_Flag = Flag names of SR register
 *
 * @retval SPI_FlagStatus_t
 */
SPI_FlagStatus_t SPI_GetFlagStatus(SPI_HandleTypeDef_t *SPI_Handle, uint16_t SPI_Flag)
{
	return (SPI_Handle->Instance->SR & SPI_Flag) ? SPI_FLAG_SET : SPI_FLAG_RESET;
}











