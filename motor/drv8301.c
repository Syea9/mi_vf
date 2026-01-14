#include "main.h"
#include "drv8301.h"

uint8_t drv8301_ok_flag = 0;

uint16_t drv8301_read_reg_buf[5] = {0};
 
void drv8301_write_reg(uint16_t address, uint16_t data)
{
	uint16_t send_data = 0;
	
	send_data = address & 0x03;
	send_data <<= 11;
	send_data |= data;

	M_SPI_NSS_RESET;
	
	m_spi_transfer_half_word(send_data);
	
	M_SPI_NSS_SET;
}

uint16_t drv8301_read_reg(uint16_t address)
{
	uint16_t temp_data = 0;
	uint16_t recv_data = 0;
	
	/* bit15 is w/r bit, 1 for read, 0 for write */
	temp_data = 0x8000 | ((address & 0x03) << 11);
	
	M_SPI_NSS_RESET;
	
	m_spi_transfer_half_word(temp_data);
	recv_data = m_spi_transfer_half_word(0xFFFF);
	
	M_SPI_NSS_SET;
	
	return (recv_data & 0x07FF);
}

void drv8301_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_Pin = DRV8301_EN_GATE_PIN;
	GPIO_Init(DRV8301_EN_GATE_PORT, &GPIO_InitStruct);
	GPIO_ResetBits(DRV8301_EN_GATE_PORT, DRV8301_EN_GATE_PIN);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_Pin = DRV8301_NFAULT_PIN;
	GPIO_Init(DRV8301_NFAULT_PORT, &GPIO_InitStruct);
	
	m_spi_init();
	
	drv8301_write_reg(DRV8301_REG2, GATE_CURRENT_0_7 | GATE_RESET_NOMAL | PWM_MODE_6_INPUTS
					 | OCP_LATCH_SHUT_DOWN | OC_ADJ_SET_14);
	drv8301_write_reg(DRV8301_REG3, OCTW_OC_ONLY | GAIN_AMP_40 | DC_CAL_CH1_CON 
					 | DC_CAL_CH2_CON | OC_TOFF_CYCLE);
	
	drv8301_read_reg_buf[0] = drv8301_read_reg(DRV8301_REG0);
	drv8301_read_reg_buf[1] = drv8301_read_reg(DRV8301_REG1);
	drv8301_read_reg_buf[2] = drv8301_read_reg(DRV8301_REG2);
	drv8301_read_reg_buf[3] = drv8301_read_reg(DRV8301_REG3);
	
	drv8301_ok_flag = 1;
}
