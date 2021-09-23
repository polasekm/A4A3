/*-----------------------------------------------------------------------------*/
/*
 * usart.h
 *
 *  Created on: Apr 9, 2011
 *      Author: Martin
 */
/*-----------------------------------------------------------------------------*/
#ifndef A4A3_H_INCLUDED
#define A4A3_H_INCLUDED

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/
/**
  * @brief  Ring buffer structure definition
  */
typedef struct
{
  uint8_t *buff;        //ukazatel na pocatek bufferu

  //uint8_t *write;       //zapisovaci ukazatel
  uint16_t size;        //velikost bufferu

  uint8_t state;        //state
  uint8_t escape;       //escaper state
  uint8_t last_ch;      //last byte

  uint8_t sync;         //packet sync
  uint8_t type;         //packet type
  uint16_t len;         //data length
  uint8_t crc;          //data crc

  uint32_t err_cnt;     //error counter
  uint32_t pck_cnt;     //packet counter

} a4a3_t;

/* Exported functions ------------------------------------------------------- */

/* Defines -------------------------------------------------------------------*/

#define A4A3_STX             0xA4
#define A4A3_ETX             0xA3
#define A4A3_DLE             0xA2

#define A4A3_STX_ESC         0x02
#define A4A3_ETX_ESC         0x01
#define A4A3_DLE_ESC         0x00

#define A4A3_STATE_WAIT      0
#define A4A3_STATE_SYNC      1
#define A4A3_STATE_TYPE      2
#define A4A3_STATE_DATA1     3
#define A4A3_STATE_DATA      4

// Functions -------------------------------------------------------------------
void a4a3_init(a4a3_t *a4a3, uint8_t *buff, uint16_t size);

uint8_t a4a3_receive(a4a3_t *a4a3, uint8_t ch);
uint16_t a4a3_create(uint8_t *buff, uint16_t buff_len, uint8_t sync, uint8_t type, uint8_t *data, uint16_t data_len);
void a4a3_add_b(uint8_t **buff, uint8_t ch);          //add byte to buffer

void a4a3_crc_update(uint8_t *crc, uint8_t ch);       //CRC update
//------------------------------------------------------------------------------
#endif /* A4A3_H_INCLUDED */
