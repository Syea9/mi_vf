#ifndef __SPI_H
#define __SPI_H

#define DRV8301_SPI 		SPI3

#define M_SPI_NSS_PORT		GPIOA
#define M_SPI_NSS_PIN       GPIO_Pin_15
#define M_SPI_NSS_AF		GPIO_PinSource15

#define M_SPI_SCK_PORT		GPIOC
#define M_SPI_SCK_PIN       GPIO_Pin_10
#define M_SPI_SCK_AF        GPIO_PinSource10


#define M_SPI_MISO_PORT		GPIOA
#define M_SPI_MISO_PIN      GPIO_Pin_11
#define M_SPI_MISO_AF       GPIO_PinSource11


#define M_SPI_MOSI_PORT		GPIOA
#define M_SPI_MOSI_PIN      GPIO_Pin_12
#define M_SPI_MOSI_AF       GPIO_PinSource12

#define M_SPI_NSS_SET 		GPIO_SetBits(M_SPI_NSS_PORT, M_SPI_NSS_PIN)
#define M_SPI_NSS_RESET 	GPIO_ResetBits(M_SPI_NSS_PORT, M_SPI_NSS_PIN)

extern void m_spi_init(void);
extern uint16_t m_spi_transfer_half_word(uint16_t HalfWord);

#endif
