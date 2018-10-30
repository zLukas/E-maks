/*
 * nRF24L01.h
 *
 *  Created on: 28 lut 2018
 *      Author: uzytkownik
 */

#ifndef NRF24L01_H_
#define NRF24L01_H_

#define MAX_RT_FLAG 4
#define TX_DS_FLAG 5
#define RX_DR_FLAG 6

#define DATA_SIZE 2							//Number of received/transmitted bytes

#include "Library_includes.h"

extern uint8_t sender[DATA_SIZE];			//Data to send (used during tests)
uint8_t preparing_to_send;					//Used as a flag that informs if DMA started transferring data to send via nRF
uint8_t flag_to_analize;					//Informs that reading of Status register is in progress
uint8_t initialization_in_process;			//Initialization of nRF is not finished
uint8_t initialize_counter;					//Counter that informs, which command is currently being executed by DMA
uint8_t count_retry_request;				//Requests reading from OBSERVE_TX register - retry
uint8_t count_lost_packets_request;			//Requests reading from OBSERVE_TX register - lost packets
uint8_t check_fifo_request;					//Requests reading from FIFO_STATUS register

uint8_t STATUS_register;					//Value of Status register
uint8_t Receive_buffer_register[2];			//Value of last checked register
uint8_t Receive_buffer_address[6];			//Value of last checked address
uint8_t Receive_buffer_address_short[2];	//Value of last checked address from RX data pipe (pipes 2 - 5)
uint8_t Receive_buffer[DATA_SIZE + 1];		//Date received from nRF

extern const uint8_t TX_Address[5];			//TX address
extern const uint8_t RX_P0_Address[5];		//RX address pipe 0
extern const uint8_t RX_P1_Address[5];		//RX address pipe 1
extern const uint8_t RX_P2_Address;			//RX address pipe 2
extern const uint8_t RX_P3_Address;			//RX address pipe 3
extern const uint8_t RX_P4_Address;			//RX address pipe 4
extern const uint8_t RX_P5_Address;			//RX address pipe 5

/* @brief Transfers data to nRF via SPI
 * Only function used to set and read nRF registers values
 * @param _bufferscr[]: Vector which holds data to send
 * @param _bufferscr[]:	Vector which holds data from nRF
 * @param _buffer_size:	Size of _bufferscr[] and _bufferscr[] vectors
 */

void nRF_DMA_transfer(uint8_t _bufferscr[], uint8_t _bufferdst[], uint16_t _buffer_size);

/* @brief Starts transfer
 * Sets CS pin low
 */

void nRF_SPI_start_transfer();

/* @brief Stops transfer
 * Sets CS pin high
 */

void nRF_SPI_stop_transfer();

/* @brief Function that reads nRF register value
 * Function uses DMA to communicate with nRF
 * @param _register: Register to read
 */

void nRF_Read_REGISTER(uint8_t _register);

/* @brief Function that sets nRF register value
 * Function uses DMA to communicate with nRF
 * @param _register: Register to set
 * @param _value: New value of register
 */

void nRF_Write_REGISTER(uint8_t _register, uint8_t _value);

/* @brief Function that reads TX address
 * Used to ensure that TX address of transceiver and receiver RX address (one of enabled data pipes) are the same
 */

void nRF_Read_TX_Address();

/* @brief Function that sets TX address
 * TX address of transceiver and receiver RX address (one of enabled data pipes) must be the same
 */

void nRF_Set_TX_Address();

/* @brief Function that reads RX address from data pipe 0 and data pipe 1
 * Function used to ensure, that transceiver and receiver addresses are the same
 * TX address and RX pipe 0 address should be the same to enable Auto ACK
 * @param _number_of_data_pipe:	Pipe which address should be checked
 */

void nRF_Read_RX_Address_Pipe_0_1(uint8_t _number_of_data_pipe);

/* @brief Function that reads RX address from data pipes from 2 to 5
 * Function used to ensure, that transceiver and receiver addresses are the same.
 * RX address of data pipes 2, 3, 4 and 5 consists of four oldest RX P1 register bytes
 * and address read with this function (youngest byte)
 * @param _number_of_data_pipe:	Pipe which address should be checked
 */

void nRF_Read_RX_Address_Pipe_2_to_5(uint8_t _number_of_data_pipe);

/* @brief Function displays chosen address
 *	Function that displays full address of one of data pipes
 *	@param _number_of_data_pipe: Pipe which address should be checked
 */

void nRF_Display_RX_Address(uint8_t _number_of_data_pipe);

/* @brief Function which allows to change RX pipe 0 address
 *	RX pipe 0 address should be the same as TX address
 */

void nRF_Set_RX_Address_Pipe_0();

/* @brief Function which allows to change RX pipe 1 address
 */

void nRF_Set_RX_Address_Pipe_1();

/* @brief Function which allows to change RX pipe 2 address
 */

void nRF_Set_RX_Address_Pipe_2();

/* @brief Function which allows to change RX pipe 3 address
 */

void nRF_Set_RX_Address_Pipe_3();

/* @brief Function which allows to change RX pipe 4 address
 */

void nRF_Set_RX_Address_Pipe_4();

/* @brief Function which allows to change RX pipe 5 address
 */

void nRF_Set_RX_Address_Pipe_5();

/* @brief Changes nRF mode from "Power Down" to "Standby - I"
 *	Function changes value of CONFIG register
 */

void nRF_Power_Up();

/* @brief Changes nRF mode from "Power Down" to "RX Mode"
 *	Function changes value of CONFIG register
 */

void nRF_Set_RX_Mode();

/* @brief Changes nRF mode from "Power Down" to "TX Mode"
 *	Function changes value of CONFIG register and sets CE pin high
 */

void nRF_Set_TX_Mode();

/* @brief Writes data to TX FIFO
 * Function writes data to TX FIFO and changes prepare_to_send value.
 * After successful writing to TX FIFO, CE pin is set for at least 10 us
 * @param _buffer[]: Vector which holds data to transfer
 * @param _buffer_size:	Size of _buffer[] vector
 */

void nRF_SPI_transfer(uint8_t _buffer[], uint8_t _buffer_size);

/* @brief Reads data from RX FIFO
 * Function reads data from RX FIFO and (received from transceiver)
 * @param _buffer_size:	Number of data bytes received from nRF
 */

void nRF_SPI_receive(uint8_t _buffer_size);

/* @brief Cleans RX FIFO
 */

void nRF_SPI_Flush_RX();

/* @brief Cleans TX FIFO
 */

void nRF_SPI_Flush_TX();

/* @brief Clears all flags in STATUS register
 *	Flags in STATUS register are set when one of three events occur: data successfully send, data received, or in case of maximum
 *	numbers of send retries.
 */

void nRF_Clear_all_status_flags();

/* @brief Reset one flag in STATUS register
 *	When one of flags is set, the IRQ pin goes high causing interrupt to occur.
 * @param _flag: Flag to clear
 */

void nRF_Clear_status_flag(uint8_t _flag);

/* @brief Shows number of lost packets
 * When MAX_RT flag in status register is set, this function allows to check, how many packets we lost (from last successfully
 * packet). Function reads OBSERVE_TX register.
 */

void nRF_Count_lost_packets();

/* @brief Shows number of retransmitions
 *	Function reads OBSERVE_TX register and processes received value to check, how many retransmitions
 *	were necessary to successfully send data packet
 */

void nRF_Count_retransmitted_packets();

/* @brief Checks FIFO status
 * Function sets check_fifo_request and reads FIFO_STATUS register.
 */

void nRF_Check_FIFO_flags();

/* @brief Function analyze flags in STATUS register
 * Function analyze flags in STATUS register and cleans them. Can be used to run needed functions
 */

void nRF_Analyze_flags();

/* @brief Displays number of lost packets
 * Processes OBSERVE_TX value to check, how many packets were lost
 */

void nRF_Analyze_lost();

/* @brief Displays number of retransmitions
 * Processes OBSERVE_TX value to check, how many retransmitions	were necessary to successfully send data packet
 */

void nRF_Analyze_retransmited();

/* @brief Displays strings describing FIFO status
 *	Before running this function, FIFO_STATUS register should be read first. *
 */

void nRF_Analyze_FIFO();

/* @brief Function initializing nRF device
 * Function sets registers values to configure device to send and receive data frames of defined size
 */

void nRF_Init();

///////////////////////////
//Functions used in tests//
///////////////////////////

void Clear_all_status_flags_2();
uint8_t Get_status_flag_2(uint8_t _flag);
void Clear_status_flag_2(uint8_t _flag);
void SPI_start_transfer_2();
void SPI_stop_transfer_2();
void SPI_send_2(uint8_t _buffer[], uint8_t _buffer_size);
void SPI_send_one_byte_2(uint8_t _byte);

void Write_REGISTER_2(uint8_t _register, uint8_t _value);
uint8_t Read_REGISTER_2(uint8_t _register);

void Read_TX_Address_2();
void Set_TX_Address_2();

void Read_RX_Address(uint8_t _number_of_data_pipe);
void Set_RX_Address(uint8_t _number_of_data_pipe);

void Power_Up();
void Set_RX_Mode();
void SPI_Flush_RX();

void SPI_receive(uint8_t _buffer_size);

#endif /* NRF24L01_H_ */
