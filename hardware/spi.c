#include "main.h"
#include "spi.h"

void m_spi_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef SPI_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
	
	/* AF CONFIG */
	GPIO_PinAFConfig(M_SPI_SCK_PORT, M_SPI_SCK_AF, GPIO_AF_SPI3);
	GPIO_PinAFConfig(M_SPI_MISO_PORT, M_SPI_MISO_AF, GPIO_AF_SPI3);
	GPIO_PinAFConfig(M_SPI_MOSI_PORT, M_SPI_MOSI_AF, GPIO_AF_SPI3);
	
	/* NSS PA15 */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = M_SPI_NSS_PIN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(M_SPI_NSS_PORT, &GPIO_InitStruct);
	
	/* default increase NSS */
	M_SPI_NSS_SET;
	
	/* SCK PC10 */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = M_SPI_SCK_PIN;
	GPIO_Init(M_SPI_SCK_PORT, &GPIO_InitStruct);
	
	/* MISO PC11 */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = M_SPI_MISO_PIN;
	GPIO_Init(M_SPI_MISO_PORT, &GPIO_InitStruct);
	
	/* MOSI PC12 */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = M_SPI_MOSI_PIN;
	GPIO_Init(M_SPI_MOSI_PORT, &GPIO_InitStruct);
	
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CRCPolynomial = 0x07;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_16b;
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	
	SPI_Init(DRV8301_SPI, &SPI_InitStruct);
	SPI_Cmd(DRV8301_SPI, ENABLE);
}

uint16_t m_spi_transfer_half_word(uint16_t HalfWord)
{
	while(SPI_GetFlagStatus(DRV8301_SPI, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(DRV8301_SPI, HalfWord);
	
	while(SPI_GetFlagStatus(DRV8301_SPI, SPI_I2S_FLAG_RXNE) == RESET);
	return SPI_I2S_ReceiveData(DRV8301_SPI);
}


