/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pb_config.h
 * Author: MHUSSAIN
 *
 * Created on 24 November 2017, 09:51
 */

#ifndef PB_CONFIG_H
#define PB_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const uint8 u8Member0 ;
    uint8 u8Member1;
    uint16 u16Member2;
    struct {
            uint8 u8Member1;
            uint16 u16Member2;
    }  __attribute__((packed)) stMember3;
    uint32 u32Member4;
    const uint8 u8Member5 ;
} __attribute__((packed)) pb_config_t;


extern const pb_config_t cstData;
extern const tstrVariableDesriptor astrVariableDesriptor[];
extern const pfServiceHandler apfVariableDesriptor[];
#ifdef __cplusplus
}
#endif

extern const pfServiceHandler apfVariableDesriptor[];
extern const tstrVariableDesriptor astrVariableDesriptor[];
extern const unsigned int MaxData;
extern const unsigned int MaxService;
//#define MAX_DATA (sizeof(astrVariableDesriptor)/sizeof(tstrVariableDesriptor))
//#define MAX_DATA (sizeof(astrVariableDesriptor))


//#define MAX_SERVICE (sizeof(apfVariableDesriptor)/sizeof(pfServiceHandler))


#endif /* PB_CONFIG_H */

