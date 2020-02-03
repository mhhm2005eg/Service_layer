/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   types.h
 * Author: MHUSSAIN
 *
 * Created on 23 November 2017, 12:09
 */

#ifndef TYPES_H
#define TYPES_H

#ifdef __cplusplus
extern "C" {
#endif
#include "stddefs.h"
#include "limits.h"
/*typedef enum {
  false = 0,
  true = 1
} bool;
*/
typedef uint32 data_size_t;
typedef uint16 frame_id_t;

typedef enum{
    READ_DATA_ID = 0x00,
    WRITE_DATA_ID,
    READ_DATA_ADD,
    WRITE_DATA_ADD,
    RUN_SERVICE
}tenuServiceType;

typedef enum{
    REQUEST = 0x00,
    RESPONSE
}tenuStatusType;

typedef union
{
  /* !Comment : Access using a mask.                                         */
  frame_id_t u16Word ;
  /* !Comment : Access using Bytes.                                          */
  struct
  {
    uint8 u8MSB;
    uint8 u8LSB;
  }  __attribute__((packed)) strByte ;
  /* !Comment : Access bit by bit.                                           */
  struct
  {
    frame_id_t destination : 2;
    tenuServiceType type : 3;
    frame_id_t descriptor : 9;
    uint16 error:1;
    tenuStatusType status : 1;
  }  __attribute__((packed)) strBit ;
} tuniFrameId ;






typedef struct{
    uint8 * pu8Address;
    data_size_t u16Length;
} __attribute__((packed)) tstrVariableDesriptor;

typedef STD_tenuStatus (*pfServiceHandler)(uint8*, data_size_t*);

typedef struct{
    data_size_t size;
    tuniFrameId id;
    char data[RECEIVE_BUFFER_LENGTH];
}  __attribute__((packed)) frame_t;


//typedef int32      tResult;


#ifdef __cplusplus
}
#endif

#endif /* TYPES_H */

