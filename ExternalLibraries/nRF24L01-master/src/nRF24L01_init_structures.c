#include "nRF24L01_init_structures.h"

void CONFIG_StructInit(CONFIG_InitTypeDef* CONFIG_InitStruct)
{
	CONFIG_InitStruct -> MASK_RX_DR = CONFIG_MASK_DISABLE;
	CONFIG_InitStruct -> MASK_MAX_RT = CONFIG_MASK_DISABLE;
	CONFIG_InitStruct -> MASK_TX_DS = CONFIG_MASK_DISABLE;
	CONFIG_InitStruct -> EN_CRC = CONFIG_CRC_ENABLE;
	CONFIG_InitStruct -> CRCO = CONFIG_CRC_BYTE_1;
	CONFIG_InitStruct -> PWR_UP = CONFIG_PWR_DOWN;
	CONFIG_InitStruct -> PRIM_RX = CONFIG_PRIM_TX;
}

void CONFIG_Init(CONFIG_InitTypeDef* CONFIG_InitStruct)
{
	uint8_t init_command = 0x00;

	init_command = 0*2*2*2*2*2*2*2 + (CONFIG_InitStruct -> MASK_RX_DR)*2*2*2*2*2*2 + (CONFIG_InitStruct -> MASK_TX_DS)*2*2*2*2*2 + (CONFIG_InitStruct -> MASK_MAX_RT)*2*2*2*2 + (CONFIG_InitStruct -> EN_CRC)*2*2*2 + (CONFIG_InitStruct -> CRCO)*2*2 + (CONFIG_InitStruct -> PWR_UP)*2 + (CONFIG_InitStruct -> PRIM_RX)*1;

	nRF_Write_REGISTER(CONFIG, init_command);
}

void CONFIG_Init_2(CONFIG_InitTypeDef* CONFIG_InitStruct)
{
	uint8_t init_command = 0x00;

	init_command = 0*2*2*2*2*2*2*2 + (CONFIG_InitStruct -> MASK_RX_DR)*2*2*2*2*2*2 + (CONFIG_InitStruct -> MASK_TX_DS)*2*2*2*2*2 + (CONFIG_InitStruct -> MASK_MAX_RT)*2*2*2*2 + (CONFIG_InitStruct -> EN_CRC)*2*2*2 + (CONFIG_InitStruct -> CRCO)*2*2 + (CONFIG_InitStruct -> PWR_UP)*2 + (CONFIG_InitStruct -> PRIM_RX)*1;

	Write_REGISTER_2(CONFIG, init_command);
}

void EN_AA_StructInit(EN_AA_InitTypeDef* EN_AA_InitStruct)
{
	EN_AA_InitStruct -> ENAA_P5 = ENAA_ENABLE;
	EN_AA_InitStruct -> ENAA_P4 = ENAA_ENABLE;
	EN_AA_InitStruct -> ENAA_P3 = ENAA_ENABLE;
	EN_AA_InitStruct -> ENAA_P2 = ENAA_ENABLE;
	EN_AA_InitStruct -> ENAA_P1 = ENAA_ENABLE;
	EN_AA_InitStruct -> ENAA_P0 = ENAA_ENABLE;
}

void EN_AA_Init(EN_AA_InitTypeDef* EN_AA_InitStruct)
{
	uint8_t init_command = 0x00;

	init_command = 0*2*2*2*2*2*2*2 + 0*2*2*2*2*2*2 + (EN_AA_InitStruct -> ENAA_P5)*2*2*2*2*2 + (EN_AA_InitStruct -> ENAA_P4)*2*2*2*2 + (EN_AA_InitStruct -> ENAA_P3)*2*2*2 + (EN_AA_InitStruct -> ENAA_P2)*2*2 + (EN_AA_InitStruct -> ENAA_P1)*2 + (EN_AA_InitStruct -> ENAA_P0)*1;

	nRF_Write_REGISTER(EN_AA, init_command);
}

void EN_RX_StructInit(EN_RX_InitTypeDef* EN_RX_InitStruct)
{
	EN_RX_InitStruct -> ERX_P5 = ERX_DISABLE;
	EN_RX_InitStruct -> ERX_P4 = ERX_DISABLE;
	EN_RX_InitStruct -> ERX_P3 = ERX_DISABLE;
	EN_RX_InitStruct -> ERX_P2 = ERX_DISABLE;
	EN_RX_InitStruct -> ERX_P1 = ERX_ENABLE;
	EN_RX_InitStruct -> ERX_P0 = ERX_ENABLE;
}

void EN_RX_Init(EN_RX_InitTypeDef* EN_RX_InitStruct)
{
	uint8_t init_command = 0x00;

	init_command = 0*2*2*2*2*2*2*2 + 0*2*2*2*2*2*2 + (EN_RX_InitStruct -> ERX_P5)*2*2*2*2*2 + (EN_RX_InitStruct -> ERX_P4)*2*2*2*2 + (EN_RX_InitStruct -> ERX_P3)*2*2*2 + (EN_RX_InitStruct -> ERX_P2)*2*2 + (EN_RX_InitStruct -> ERX_P1)*2 + (EN_RX_InitStruct -> ERX_P0)*1;

	nRF_Write_REGISTER(EN_RXADDR, init_command);
}

void SETUP_AW_StructInit(SETUP_AW_InitTypeDef* SETUP_AW_InitStruct)
{
	SETUP_AW_InitStruct -> AW = SETUP_AW_BYTES_5;
}

void SETUP_AW_Init(SETUP_AW_InitTypeDef* SETUP_AW_InitStruct)
{
	nRF_Write_REGISTER(SETUP_AW, SETUP_AW_InitStruct -> AW);
}

void SETUP_RETRY_StructInit(SETUP_RETRY_InitTypeDef* SETUP_RETRY_InitStruct)
{
	SETUP_RETRY_InitStruct -> ARD = SETUP_ARD_250;
	SETUP_RETRY_InitStruct -> ARC = SETUP_ARC_3;
}
void SETUP_RETRY_Init(SETUP_RETRY_InitTypeDef* SETUP_RETRY_InitStruct)
{
	uint8_t ard = (SETUP_RETRY_InitStruct -> ARD) << 4;
	uint8_t arc = SETUP_RETRY_InitStruct -> ARC;

	uint8_t command = ard | arc;
	nRF_Write_REGISTER(SETUP_RETR, command);
}

void RF_CH_StructInit(RF_CH_InitTypeDef* RF_CH_InitStruct)
{
	RF_CH_InitStruct -> RF_CH_VALUE = 2;
}
void RF_CH_Init(RF_CH_InitTypeDef* RF_CH_InitStruct)
{
	if ((RF_CH_InitStruct -> RF_CH_VALUE >= 0)&&(RF_CH_InitStruct -> RF_CH_VALUE <= 125))
	{
		nRF_Write_REGISTER(RF_CH, RF_CH_InitStruct -> RF_CH_VALUE);
	}
}

void RF_SETUP_StructInit(RF_SETUP_InitTypeDef* RF_SETUP_InitStruct)
{
	RF_SETUP_InitStruct -> PLL_LOCK = RF_SETUP_PLL_LOCK_DISABLE;
	RF_SETUP_InitStruct -> RF_PWR = RF_SETUP_RF_PWR_0;
	RF_SETUP_InitStruct -> RF_DR = RF_SETUP_RF_DR_MBPS_2;
	RF_SETUP_InitStruct -> LNA_HCURR = RF_SETUP_LNA_HCURR_ENABLE;
}

void RF_SETUP_Init(RF_SETUP_InitTypeDef* RF_SETUP_InitStruct)
{
	uint8_t command;
	uint8_t RF_pll = (RF_SETUP_InitStruct -> PLL_LOCK) << 4;
	uint8_t RF_DR =  (RF_SETUP_InitStruct -> RF_DR) << 3;
	uint8_t RF_PWR = (RF_SETUP_InitStruct -> RF_PWR) << 1;
	uint8_t RF_LNA = RF_SETUP_InitStruct -> LNA_HCURR;

	command = RF_pll | RF_DR | RF_PWR | RF_LNA;

	nRF_Write_REGISTER(RF_SETUP, command);
}
