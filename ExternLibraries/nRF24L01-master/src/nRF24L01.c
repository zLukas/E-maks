#include "nRF24L01.h"

const uint8_t TX_Address[5] = {0xC5, 0x69, 0xD7, 0xBA, 0xAF};
const uint8_t RX_P0_Address[5] = {0xC5, 0x69, 0xD7, 0xBA, 0xAF};
//const uint8_t RX_P1_Address[5] = {0xB6, 0x21, 0x58, 0xC9, 0xE4};
const uint8_t RX_P1_Address[5] = {0xC5, 0x69, 0xD7, 0xBA, 0xAF};
const uint8_t RX_P2_Address = 0x65;
const uint8_t RX_P3_Address = 0xD3;
const uint8_t RX_P4_Address = 0xDA;
const uint8_t RX_P5_Address = 0x57;

/*Structures used to correctly initialize nRF*/
CONFIG_InitTypeDef config;
EN_AA_InitTypeDef en;
EN_RX_InitTypeDef enrx;
SETUP_AW_InitTypeDef aw;
SETUP_RETRY_InitTypeDef retr;
RF_CH_InitTypeDef rfch;
RF_SETUP_InitTypeDef rfset;

uint8_t sender[DATA_SIZE] = {0x58, 0xAE};		//Data to send (in tests)

/*Variables describing currently running function and the following one*/
uint8_t preparing_to_send = 0;
uint8_t flag_to_analize = 0;
uint8_t initialize_counter = 0;
uint8_t count_retry_request = 0;
uint8_t count_lost_packets_request = 0;
uint8_t check_fifo_request = 0;

void nRF_Read_REGISTER(uint8_t _register)
{
	uint8_t send_buffer_read[2] = {R_REGISTER | _register, 0};
	nRF_DMA_transfer(send_buffer_read, Receive_buffer_register, 2);
}

void nRF_Write_REGISTER(uint8_t _register, uint8_t _value)
{
	uint8_t send_buffer_write[2] = {W_REGISTER | _register, _value};			//Initialize send buffer
	nRF_DMA_transfer(send_buffer_write, Receive_buffer_register, 2);			//Send buffer via SPI
}

void nRF_SPI_start_transfer()
{
	/*CS pin goes low to start data transfer*/
	GPIO_ResetBits(GPIOC, GPIO_Pin_7);
}

void nRF_SPI_stop_transfer()
{
	/*CS pin goes low to stop data transfer*/
	GPIO_SetBits(GPIOC, GPIO_Pin_7);
}

void nRF_Read_TX_Address()
{
	uint8_t send_buffer_tx[6] = {R_REGISTER | TX_ADDR, 0, 0, 0, 0, 0};
	nRF_DMA_transfer(send_buffer_tx,Receive_buffer_address, 6);
}

void nRF_Set_TX_Address()
{
	/*LSByte send first*/
	uint8_t send_buffer_s_tx[6] = {W_REGISTER | TX_ADDR,  TX_Address[4], TX_Address[3], TX_Address[2], TX_Address[1], TX_Address[0]};
	nRF_DMA_transfer(send_buffer_s_tx,Receive_buffer_address, 6);
}

void nRF_Read_RX_Address_Pipe_0_1(uint8_t _number_of_data_pipe)
{
	uint8_t send_buffer_r_p[6] = {0, 0, 0, 0, 0, 0};

	if(_number_of_data_pipe == 0)
		send_buffer_r_p[0] = R_REGISTER | RX_ADDR_P0;
	else if(_number_of_data_pipe == 1)
		send_buffer_r_p[0] = R_REGISTER | RX_ADDR_P1;
	else
	{
		printf("Wrong data pipe number\n");
	}

	nRF_DMA_transfer(send_buffer_r_p,Receive_buffer_address, 6);
}

void nRF_Read_RX_Address_Pipe_2_to_5(uint8_t _number_of_data_pipe)
{
	uint8_t send_buffer_r_p2[2] = {0, 0};

	Receive_buffer_address_short[0] = 0;
	Receive_buffer_address_short[1] = 0;

	switch (_number_of_data_pipe)
	{
	case 2:
		send_buffer_r_p2[0] = R_REGISTER | RX_ADDR_P2;
		break;
	case 3:
		send_buffer_r_p2[0] = R_REGISTER | RX_ADDR_P3;
		break;
	case 4:
		send_buffer_r_p2[0] = R_REGISTER | RX_ADDR_P4;
		break;
	case 5:
		send_buffer_r_p2[0] = R_REGISTER | RX_ADDR_P5;
		break;
	default:
		send_buffer_r_p2[0] = R_REGISTER | RX_ADDR_P2;
		printf("Wrong data pipe number\n");
		break;
	}
	nRF_DMA_transfer(send_buffer_r_p2, Receive_buffer_address_short, 2);
}

void nRF_Display_RX_Address(uint8_t _number_of_data_pipe)
{
	if (_number_of_data_pipe < 2)
		printf("RX_Address_pipe_%d -> 0x%x%x%x%x%x\n", _number_of_data_pipe, Receive_buffer_address[5], Receive_buffer_address[4], Receive_buffer_address[3], Receive_buffer_address[2], Receive_buffer_address[1]);
	else
		printf("RX_Address_pipe_%d -> 0x%x%x%x%x%x\n", _number_of_data_pipe, Receive_buffer_address[5], Receive_buffer_address[4], Receive_buffer_address[3], Receive_buffer_address[2], Receive_buffer_address_short[1]);
}

void nRF_Set_RX_Address_Pipe_0()
{

	uint8_t send_buffer_pipe0[6] = {W_REGISTER | RX_ADDR_P0, RX_P0_Address[4], RX_P0_Address[3], RX_P0_Address[2], RX_P0_Address[1], RX_P0_Address[0]};
	nRF_DMA_transfer(send_buffer_pipe0,Receive_buffer_address, 6);
}

void nRF_Set_RX_Address_Pipe_1()
{
	uint8_t send_buffer_pipe1[6] = {W_REGISTER | RX_ADDR_P1, RX_P1_Address[4], RX_P1_Address[3], RX_P1_Address[2], RX_P1_Address[1], RX_P1_Address[0]};
	nRF_DMA_transfer(send_buffer_pipe1,Receive_buffer_address, 6);
}

void nRF_Set_RX_Address_Pipe_2()
{
	uint8_t send_buffer_pipe2[2] = {W_REGISTER | RX_ADDR_P2, RX_P2_Address};
	nRF_DMA_transfer(send_buffer_pipe2, Receive_buffer_address_short, 2);
}

void nRF_Set_RX_Address_Pipe_3()
{
	uint8_t send_buffer_pipe3[2] = {W_REGISTER | RX_ADDR_P3, RX_P3_Address};
	nRF_DMA_transfer(send_buffer_pipe3, Receive_buffer_address_short, 2);
}

void nRF_Set_RX_Address_Pipe_4()
{
	uint8_t send_buffer_pipe4[2] = {W_REGISTER | RX_ADDR_P4, RX_P4_Address};
	nRF_DMA_transfer(send_buffer_pipe4, Receive_buffer_address_short, 2);
}

void nRF_Set_RX_Address_Pipe_5()
{
	uint8_t send_buffer_pipe5[2] = {W_REGISTER | RX_ADDR_P5, RX_P5_Address};
	nRF_DMA_transfer(send_buffer_pipe5, Receive_buffer_address_short, 2);
}

void nRF_Power_Up()
{
	config.PWR_UP = CONFIG_PWR_UP;
	CONFIG_Init(&config);
}

void nRF_Set_RX_Mode()
{
	config.PWR_UP = CONFIG_PWR_UP;
	config.PRIM_RX = CONFIG_PRIM_RX;
	CONFIG_Init(&config);

	GPIO_SetBits(GPIOC, GPIO_Pin_9);
}

void nRF_Set_TX_Mode()
{
	config.PWR_UP = CONFIG_PWR_UP;
	config.PRIM_RX = CONFIG_PRIM_TX;
	CONFIG_Init(&config);
}

void nRF_SPI_transfer(uint8_t _buffer[], uint8_t _buffer_size)
{
	/*Transfer buffer size is _buffer[] size + 1 due to command we need to send*/
	uint8_t transfer[_buffer_size + 1];

	/*Data should be transmitted MSB first and less significant byte first*/
	transfer[0] = W_TX_PAYLOAD;
	for (uint8_t i = 0; i < _buffer_size; i++)
		transfer[_buffer_size - i] = _buffer[i];

	/*Flag informing that DMA started writing FIFO in nRF*/
	preparing_to_send = 1;

	nRF_DMA_transfer(transfer, Receive_buffer, _buffer_size + 1);
}

void nRF_SPI_receive(uint8_t _buffer_size)
{
	/*Receive buffer size is _buffer[] size + 1 due to value of status register send first, before data from FIFO*/
	uint8_t send_buffer_receive[_buffer_size + 1];

	send_buffer_receive[0] = R_RX_PAYLOAD;

	for (uint8_t i = 0; i < _buffer_size; i++)
		send_buffer_receive[i+1] = 0;

	nRF_DMA_transfer(send_buffer_receive, Receive_buffer, _buffer_size + 1);
}

void nRF_Analyze_flags()
{
	uint8_t flag_analize_variable = Receive_buffer_register[1];
	uint8_t mask = 0;
	mask |= 1 << 4; //maxrt
	uint8_t flag_status = flag_analize_variable & mask;
	if (flag_status != 0)
	{
		count_lost_packets_request = 1;
		nRF_Clear_status_flag(MAX_RT_FLAG);
	}

	mask = 0;
	mask |= 1 << 5; //txds
	flag_status = flag_analize_variable & mask;
	if (flag_status != 0)
	{
		count_retry_request = 1;
		nRF_Clear_status_flag(TX_DS_FLAG);
	}

	mask = 0;
	mask |= 1 << 6; //rxdr
	flag_status = flag_analize_variable & mask;
	if (flag_status != 0)
	{
		printf("RX_DR\n");
		nRF_Clear_status_flag(RX_DR_FLAG);
	}
	flag_to_analize = 0;
}

void nRF_SPI_Flush_TX()
{
	uint8_t send_buffer_transfer[3] = {FLUSH_TX, 0x00, 0x00};
	uint8_t to_waste[3];
	nRF_DMA_transfer(send_buffer_transfer,to_waste,3);
}

void nRF_SPI_Flush_RX()
{
	uint8_t transfer_flush[3] = {FLUSH_RX, 0x00, 0x00};
	uint8_t to_waste[3];
	nRF_DMA_transfer(transfer_flush, to_waste, 3);
}

void nRF_Clear_all_status_flags()
{
	uint8_t to_write;
	to_write |= (1 << 4);
	to_write |= (1 << 5);
	to_write |= (1 << 6);
	nRF_Write_REGISTER(STATUS,to_write);
}

void nRF_Clear_status_flag(uint8_t _flag)
{
	uint8_t clear_bit = 0;
	clear_bit |= (1 << _flag);
	nRF_Write_REGISTER(STATUS, clear_bit);
}

void nRF_Count_lost_packets()
{
	count_lost_packets_request = 1;
}

void nRF_Analyze_lost()
{
	uint8_t count_lost = Receive_buffer_register[1];
	count_lost = count_lost >> 4;
	count_lost = count_lost & 0x0F;
	printf("Lost packets = %d\n", count_lost);

	count_lost_packets_request = 0;
}

void nRF_Count_retransmitted_packets()
{
	count_retry_request = 1;
}

void nRF_Analyze_retransmited()
{
	uint8_t retransmitted_packets = Receive_buffer_register[1];
	retransmitted_packets = retransmitted_packets & 0x0F;
	printf("Retransmitted packets = %d\n", retransmitted_packets);

	count_retry_request = 0;
}

void nRF_Check_FIFO_flags()
{
	check_fifo_request = 1;
	nRF_Read_REGISTER(FIFO_STATUS);
}

void nRF_Analyze_FIFO()
{
	uint8_t check_fifo = Receive_buffer_register[1];
	uint8_t masked;
	masked = check_fifo & 0x40;
	if (masked == 0)
		printf("TX_REUSE -> RESET\n");
	else
		printf("TX_REUSE -> SET\n");

	masked = check_fifo & 0x20;
	if (masked == 0)
		printf("TX_FULL -> RESET\n");
	else
		printf("TX_FULL -> SET\n");

	masked = check_fifo & 0x10;
	if (masked == 0)
		printf("TX_EMPTY -> RESET\n");
	else
		printf("TX_EMPTY -> SET\n");

	masked = check_fifo & 0x02;
	if (masked == 0)
		printf("RX_FULL -> RESET\n");
	else
		printf("RX_FULL -> SET\n");

	masked = check_fifo & 0x01;
	if (masked == 0)
		printf("RX_EMPTY -> RESET\n");
	else
		printf("RX_EMPTY -> SET\n");

	check_fifo_request = 0;
}

void nRF_DMA_transfer(uint8_t _bufferscr[], uint8_t _bufferdst[], uint16_t _buffer_size)
{
	dmarx.DMA_MemoryBaseAddr = (uint32_t)_bufferdst;
	dmarx.DMA_BufferSize = _buffer_size;
	DMA_Init(DMA1_Channel4, &dmarx);

	dmatx.DMA_MemoryBaseAddr = (uint32_t)_bufferscr;
	dmatx.DMA_BufferSize = _buffer_size;
	DMA_Init(DMA1_Channel5, &dmatx);

	DMA_Cmd(DMA1_Channel4, ENABLE);
	DMA_Cmd(DMA1_Channel5, ENABLE);

	nRF_SPI_start_transfer();

	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Rx, ENABLE);
	SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
}

void nRF_Init()
{
	switch (initialize_counter)
	{
	case 0:
		CONFIG_StructInit(&config);

		/*config.MASK_TX_DS = CONFIG_MASK_DISABLE;
		config.MASK_RX_DR = CONFIG_MASK_DISABLE;
		config.MASK_MAX_RT = CONFIG_MASK_DISABLE;
		config.EN_CRC = CONFIG_CRC_ENABLE;
		config.CRCO = CONFIG_CRC_BYTE_1;
		config.PRIM_RX = CONFIG_PRIM_TX;
		config.PWR_UP = CONFIG_PWR_DOWN;

		CONFIG_Init(&config);*/

		EN_AA_StructInit(&en);

		/*en.ENAA_P5 = ENAA_ENABLE;
		en.ENAA_P4 = ENAA_ENABLE;
		en.ENAA_P3 = ENAA_ENABLE;
		en.ENAA_P2 = ENAA_ENABLE;
		en.ENAA_P1 = ENAA_ENABLE;
		en.ENAA_P0 = ENAA_ENABLE;

		EN_AA_Init(&en);*/

		EN_RX_StructInit(&enrx);

		/*enrx.ERX_P5 = ERX_DISABLE;
		enrx.ERX_P4 = ERX_DISABLE;
		enrx.ERX_P3 = ERX_DISABLE;
		enrx.ERX_P2 = ERX_DISABLE;
		enrx.ERX_P1 = ERX_ENABLE;
		enrx.ERX_P0 = ERX_ENABLE;

		EN_RX_Init(&enrx);*/

		SETUP_AW_StructInit(&aw);

		/*aw.AW = SETUP_AW_BYTES_5;

		SETUP_AW_Init(&aw);*/

		SETUP_RETRY_StructInit(&retr);

		/*retr.ARD = SETUP_ARD_1000;
		retr.ARC = SETUP_ARC_15;

		SETUP_RETRY_Init(&retr);*/

		RF_CH_StructInit(&rfch);

		/*rfch.RF_CH_VALUE = 2;

		RF_CH_Init(&rfch);*/

		RF_SETUP_StructInit(&rfset);

		/*rfset.PLL_LOCK = RF_SETUP_PLL_LOCK_DISABLE;
		rfset.RF_DR = RF_SETUP_RF_DR_MBPS_2;
		rfset.RF_PWR = RF_SETUP_RF_PWR_0;
		rfset.LNA_HCURR = RF_SETUP_LNA_HCURR_ENABLE;

		RF_SETUP_Init(&rfset);*/
		nRF_SPI_Flush_TX();
		break;
	case 1:
		nRF_Clear_all_status_flags();
		break;
	case 2:
		Clear_all_status_flags_2();
		SPI_Flush_RX();
		Write_REGISTER_2(RX_PW_P1, DATA_SIZE);
		Write_REGISTER_2(RX_PW_P0, DATA_SIZE);

		nRF_Write_REGISTER(RX_PW_P0, DATA_SIZE);
		break;
	case 3:
		nRF_Write_REGISTER(RX_PW_P1, DATA_SIZE);
		break;
	case 4:
		Set_TX_Address_2();
		Set_RX_Address_2(0);
		Set_RX_Address_2(1);
		nRF_Set_RX_Address_Pipe_1();
		break;
	case 5:
		Set_RX_Mode();
		nRF_Set_TX_Mode();
		break;
	case 6:
		nRF_SPI_transfer(sender, DATA_SIZE);
		break;
	default:
		initialization_in_process = 0;
		break;
	}
}

///////////////////////////
//Functions used in tests//
///////////////////////////

void SPI_send_2(uint8_t _buffer[], uint8_t _buffer_size)
{
	uint8_t counter = _buffer_size - 1;

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, _buffer[0]);

	while (counter > 0)
	{
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		SPI_I2S_SendData(SPI1, _buffer[counter]);
		counter--;
	}
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
}

void SPI_send_one_byte_2(uint8_t _byte)
{
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI1, _byte);
}

uint8_t Read_REGISTER_2(uint8_t _register)
{
	uint8_t RX_register = 0x00;
	STATUS_register = 0x00;
	SPI_start_transfer_2();

	uint8_t read_command = R_REGISTER | _register;
	SPI_send_one_byte_2(read_command);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	STATUS_register = SPI_I2S_ReceiveData(SPI1);

	SPI_send_one_byte_2(0x00);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	RX_register = SPI_I2S_ReceiveData(SPI1);

	SPI_send_one_byte_2(0x00);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

	SPI_stop_transfer_2();

	return RX_register;
}

void Write_REGISTER_2(uint8_t _register, uint8_t _value)
{
	SPI_start_transfer_2();

	uint8_t send_buffer[3];
	uint8_t write_command = W_REGISTER | _register;

	send_buffer[0] = write_command;
	send_buffer[1] = _value;

	SPI_send_2(send_buffer, 3);

	SPI_stop_transfer_2();
}

void SPI_start_transfer_2()
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_4);
}

void SPI_stop_transfer_2()
{
	GPIO_SetBits(GPIOC, GPIO_Pin_4);
}

void Read_TX_Address_2()
{
	uint8_t Read_TX_Address_register[5];
	uint8_t read_command = R_REGISTER | TX_ADDR;
	STATUS_register = 0x00;

	SPI_start_transfer_2();

	SPI_send_one_byte_2(read_command);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	STATUS_register = SPI_I2S_ReceiveData(SPI1);

	for (uint8_t i=0; i<5; i++)
	{
		SPI_send_one_byte_2(0x00);
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		Read_TX_Address_register[4-i] = SPI_I2S_ReceiveData(SPI1);
	}

	printf("Address Tx = 0x%x%x%x%x%x\n",Read_TX_Address_register[0],Read_TX_Address_register[1],Read_TX_Address_register[2],Read_TX_Address_register[3],Read_TX_Address_register[4]);

	SPI_stop_transfer_2();
}

void Set_TX_Address_2()
{
	uint8_t write_command = W_REGISTER | TX_ADDR;

	uint8_t to_send[6] = {write_command, TX_Address[0], TX_Address[1], TX_Address[2], TX_Address[3], TX_Address[4]};

	SPI_start_transfer_2();

	SPI_send_2(to_send, 6);

	SPI_stop_transfer_2();
}

void Read_RX_Address_2(uint8_t _number_of_data_pipe)
{
	uint8_t read_register;
	uint8_t read_command;
	uint8_t pipe_shown;
	uint8_t check_address[5];

	switch (_number_of_data_pipe)
	{
	case 0:
		read_command = R_REGISTER | RX_ADDR_P0;
		pipe_shown = 0;
		break;
	case 1:
		read_command = R_REGISTER | RX_ADDR_P1;
		pipe_shown = 1;
		break;
	case 2:
		read_command = R_REGISTER | RX_ADDR_P1;
		read_register = R_REGISTER | RX_ADDR_P2;
		pipe_shown = 2;
		break;
	case 3:
		read_command = R_REGISTER | RX_ADDR_P1;
		read_register = R_REGISTER | RX_ADDR_P3;
		pipe_shown = 3;
		break;
	case 4:
		read_command = R_REGISTER | RX_ADDR_P1;
		read_register = R_REGISTER | RX_ADDR_P4;
		pipe_shown = 4;
		break;
	case 5:
		read_command = R_REGISTER | RX_ADDR_P1;
		read_register = R_REGISTER | RX_ADDR_P5;
		pipe_shown = 5;
		break;
	default:
		read_command = R_REGISTER | RX_ADDR_P0;
		pipe_shown = 0;
		printf("Wrong data pipe number\n");
		break;
	}


	STATUS_register = 0x00;

	SPI_start_transfer_2();

	SPI_send_one_byte_2(read_command);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	STATUS_register = SPI_I2S_ReceiveData(SPI1);

	for (uint8_t i=0; i<5; i++)
	{
		SPI_send_one_byte_2(0x00);
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		check_address[4-i] = SPI_I2S_ReceiveData(SPI1);
	}

	SPI_stop_transfer_2();

	if(pipe_shown >= 2)
	{
		SPI_start_transfer_2();

		SPI_send_one_byte_2(read_register);
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		STATUS_register = SPI_I2S_ReceiveData(SPI1);

		SPI_send_one_byte_2(0x00);
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		check_address[4] = SPI_I2S_ReceiveData(SPI1);

		SPI_send_one_byte_2(0x00);
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

		SPI_stop_transfer_2();
	}

	printf("Address RX_P%d = 0x%x%x%x%x%x\n", pipe_shown, check_address[0], check_address[1], check_address[2], check_address[3], check_address[4]);
}

void Set_RX_Address_2(uint8_t _number_of_data_pipe)
{
	uint8_t register_written;
	uint8_t write_command;
	uint8_t pipe_write;
	uint8_t data_address;

	switch (_number_of_data_pipe)
	{
	case 0:
		write_command = W_REGISTER | RX_ADDR_P0;
		pipe_write = 0;
		break;
	case 1:
		write_command = W_REGISTER | RX_ADDR_P1;
		pipe_write = 1;
		break;
	case 2:
		data_address = RX_P2_Address;
		register_written = RX_ADDR_P2;
		pipe_write = 2;
		break;
	case 3:
		data_address = RX_P3_Address;
		register_written = RX_ADDR_P3;
		pipe_write = 3;
		break;
	case 4:
		data_address = RX_P4_Address;
		register_written = RX_ADDR_P4;
		pipe_write = 4;
		break;
	case 5:
		data_address = RX_P5_Address;
		register_written = RX_ADDR_P5;
		pipe_write = 5;
		break;
	default:
		write_command = W_REGISTER | RX_ADDR_P0;
		pipe_write = 0;
		printf("Wrong data pipe number\n");
		break;
	}

	if (pipe_write == 0)
	{
		uint8_t to_send[6] = {write_command, RX_P0_Address[0], RX_P0_Address[1], RX_P0_Address[2], RX_P0_Address[3], RX_P0_Address[4]};
		SPI_start_transfer_2();
		SPI_send_2(to_send, 6);
		SPI_stop_transfer_2();
	}
	else if (pipe_write == 1)
	{
		uint8_t to_send[6] = {write_command, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
		SPI_start_transfer_2();
		SPI_send_2(to_send, 6);
		SPI_stop_transfer_2();
	}
	else
	{
		SPI_start_transfer_2();

		uint8_t send_buffer[3];
		uint8_t write_command = W_REGISTER | register_written;

		send_buffer[0] = write_command;
		send_buffer[1] = data_address;

		SPI_send_2(send_buffer, 2);

		SPI_stop_transfer_2();
	}
}

void Clear_all_status_flags_2()
{
	uint8_t to_write;
	to_write |= (1 << 3);
	to_write |= (1 << 4);
	to_write |= (1 << 5);
	Write_REGISTER_2(STATUS,to_write);
}

uint8_t Get_status_flag_2(uint8_t _flag)
{
	uint8_t mask = 0;
	uint8_t RX_register = Read_REGISTER_2(STATUS);
	mask |= (1 << _flag);
	uint8_t flag_status = RX_register & mask;
	if (flag_status != 0)
		return 1;
	else
		return 0;
}

void Clear_status_flag_2(uint8_t _flag)
{
	uint8_t clear_bit = 0;
	clear_bit |= (1 << _flag);
	Write_REGISTER_2(STATUS, clear_bit);
}

void Power_Up()
{
	config.PWR_UP = CONFIG_PWR_UP;
	CONFIG_Init_2(&config);
}

void Set_RX_Mode()
{
	Power_Up();

	config.PRIM_RX = CONFIG_PRIM_RX;
	CONFIG_Init_2(&config);

	GPIO_SetBits(GPIOB, GPIO_Pin_0);
}

void SPI_receive(uint8_t _buffer_size)
{
	STATUS_register = 0x00;

	for (uint8_t i = 0;i<_buffer_size;i++)
		Receive_buffer[i] = 0;

	SPI_start_transfer_2();
	SPI_send_one_byte_2(R_RX_PAYLOAD);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	STATUS_register = SPI_I2S_ReceiveData(SPI1);

	for (uint8_t i = 0;i<_buffer_size;i++)
	{
		SPI_send_one_byte_2(0x00);
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		Receive_buffer[_buffer_size - 1 - i] = SPI_I2S_ReceiveData(SPI1);
	}

	SPI_stop_transfer_2();
}

void SPI_Flush_RX()
{
	uint8_t transfer[3] = {FLUSH_RX, 0x00, 0x00};

	SPI_start_transfer_2();
	SPI_send_2(transfer, 3);

	SPI_stop_transfer_2();
}
