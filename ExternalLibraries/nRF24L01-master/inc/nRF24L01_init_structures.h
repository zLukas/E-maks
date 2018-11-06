/*
 * nRF24L01_init_structures.h
 *
 *  Created on: 1 mar 2018
 *      Author: uzytkownik
 */

#ifndef NRF24L01_INIT_STRUCTURES_H_
#define NRF24L01_INIT_STRUCTURES_H_

#include "Library_includes.h"

typedef enum
{
	CONFIG_MASK_ENABLE = 1,
	CONFIG_MASK_DISABLE = 0,
}CONFIG_MASK;

typedef enum
{
	CONFIG_CRC_ENABLE = 1,
	CONFIG_CRC_DISABLE = 0,
}ENABLE_CRC;

typedef enum
{
	CONFIG_CRC_BYTE_1 = 0,
	CONFIG_CRC_BYTE_2 = 1,
}BYTE_CRC;

typedef enum
{
	CONFIG_PWR_UP = 1,
	CONFIG_PWR_DOWN = 0,
}PWR_MODE;

typedef enum
{
	CONFIG_PRIM_TX = 0,
	CONFIG_PRIM_RX = 1,
}PRIM_MODE;

typedef struct
{
	CONFIG_MASK MASK_RX_DR;

	CONFIG_MASK MASK_TX_DS;

	CONFIG_MASK MASK_MAX_RT;

	ENABLE_CRC EN_CRC;

	BYTE_CRC CRCO;

	PWR_MODE PWR_UP;

	PRIM_MODE PRIM_RX;

}CONFIG_InitTypeDef;

typedef enum
{
	ENAA_ENABLE = 1,
	ENAA_DISABLE = 0,
}ENAA;

typedef struct
{
	ENAA ENAA_P5;

	ENAA ENAA_P4;

	ENAA ENAA_P3;

	ENAA ENAA_P2;

	ENAA ENAA_P1;

	ENAA ENAA_P0;

}EN_AA_InitTypeDef;

typedef enum
{
	ERX_ENABLE = 1,
	ERX_DISABLE = 0,
}ENRX;

typedef struct
{
	ENRX ERX_P5;

	ENRX ERX_P4;

	ENRX ERX_P3;

	ENRX ERX_P2;

	ENRX ERX_P1;

	ENRX ERX_P0;

}EN_RX_InitTypeDef;

typedef enum
{
	SETUP_AW_BYTES_3 = 1,
	SETUP_AW_BYTES_4 = 2,
	SETUP_AW_BYTES_5 = 3,
}SETUP_AdW;

typedef struct
{
	SETUP_AdW AW;

}SETUP_AW_InitTypeDef;

typedef enum
{
	SETUP_ARD_250 = 0,
	SETUP_ARD_500 = 1,
	SETUP_ARD_750 = 2,
	SETUP_ARD_1000 = 3,
	SETUP_ARD_1250 = 4,
	SETUP_ARD_1500 = 5,
	SETUP_ARD_1750 = 6,
	SETUP_ARD_2000 = 7,
	SETUP_ARD_2250 = 8,
	SETUP_ARD_2500 = 9,
	SETUP_ARD_2750 = 10,
	SETUP_ARD_3000 = 11,
	SETUP_ARD_3250 = 12,
	SETUP_ARD_3500 = 13,
	SETUP_ARD_3750 = 14,
	SETUP_ARD_4000 = 15,
}SETUP_RETRY_ARD;

typedef enum
{
	SETUP_ARC_0 = 0,
	SETUP_ARC_1 = 1,
	SETUP_ARC_2 = 2,
	SETUP_ARC_3 = 3,
	SETUP_ARC_4 = 4,
	SETUP_ARC_5 = 5,
	SETUP_ARC_6 = 6,
	SETUP_ARC_7 = 7,
	SETUP_ARC_8 = 8,
	SETUP_ARC_9 = 9,
	SETUP_ARC_10 = 10,
	SETUP_ARC_11 = 11,
	SETUP_ARC_12 = 12,
	SETUP_ARC_13 = 13,
	SETUP_ARC_14 = 14,
	SETUP_ARC_15 = 15,
}SETUP_RETRY_ARC;

typedef struct
{
	SETUP_RETRY_ARD ARD;
	SETUP_RETRY_ARC ARC;

}SETUP_RETRY_InitTypeDef;

typedef struct
{
	uint8_t RF_CH_VALUE;

}RF_CH_InitTypeDef;

typedef enum
{
	RF_SETUP_PLL_LOCK_ENABLE = 1,
	RF_SETUP_PLL_LOCK_DISABLE = 0,

}RF_SETUP_PLL_LOCK;

typedef enum
{
	RF_SETUP_RF_DR_MBPS_1 = 0,
	RF_SETUP_RF_DR_MBPS_2 = 1,

}RF_SETUP_RF_DR;

typedef enum
{
	RF_SETUP_RF_PWR_MINUS_18 = 0,
	RF_SETUP_RF_PWR_MINUS_12 = 1,
	RF_SETUP_RF_PWR_MINUS_6 = 2,
	RF_SETUP_RF_PWR_0 = 3,

}RF_SETUP_RF_PWR;

typedef enum
{
	RF_SETUP_LNA_HCURR_ENABLE = 1,
	RF_SETUP_LNA_HCURR_DISABLE = 0,

}RF_SETUP_LNA_HCURR;

typedef struct
{
	RF_SETUP_PLL_LOCK PLL_LOCK;

	RF_SETUP_RF_DR RF_DR;

	RF_SETUP_RF_PWR RF_PWR;

	RF_SETUP_LNA_HCURR LNA_HCURR;

}RF_SETUP_InitTypeDef;

void CONFIG_StructInit(CONFIG_InitTypeDef* CONFIG_InitStruct);
void CONFIG_Init(CONFIG_InitTypeDef* CONFIG_InitStruct);

void CONFIG_Init_2(CONFIG_InitTypeDef* CONFIG_InitStruct);

void EN_AA_StructInit(EN_AA_InitTypeDef* EN_AA_InitStruct);
void EN_AA_Init(EN_AA_InitTypeDef* EN_AA_InitStruct);

void EN_RX_StructInit(EN_RX_InitTypeDef* EN_RX_InitStruct);
void EN_RX_Init(EN_RX_InitTypeDef* EN_RX_InitStruct);

void SETUP_AW_StructInit(SETUP_AW_InitTypeDef* SETUP_AW_InitStruct);
void SETUP_AW_Init(SETUP_AW_InitTypeDef* SETUP_AW_InitStruct);

void SETUP_RETRY_StructInit(SETUP_RETRY_InitTypeDef* SETUP_RETRY_InitStruct);
void SETUP_RETRY_Init(SETUP_RETRY_InitTypeDef* SETUP_RETRY_InitStruct);

void RF_CH_StructInit(RF_CH_InitTypeDef* RF_CH_InitStruct);
void RF_CH_Init(RF_CH_InitTypeDef* RF_CH_InitStruct);

void RF_SETUP_StructInit(RF_SETUP_InitTypeDef* RF_SETUP_InitStruct);
void RF_SETUP_Init(RF_SETUP_InitTypeDef* RF_SETUP_InitStruct);
#endif /* NRF24L01_INIT_STRUCTURES_H_ */
