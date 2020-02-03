/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "types.h"
#include "pb_config.h"
#include "services.h"
#ifdef SERVER    
#include "server.h"
#endif    
    
extern int sockfd;

#define DESCRIPE(x) {(uint8*)&x, sizeof(x)}


const pb_config_t cstData = {
    0x01,
    0x55,
    0xAAFF,
    {
        0x11,
        0x2233        
    },
    0x55443322,
    0x05
};



const tstrVariableDesriptor astrVariableDesriptor[]={
    
    DESCRIPE(sockfd),
    DESCRIPE(cstData),
#ifdef SERVER    
    DESCRIPE(u32ProcessingTime)
#endif            
};


const pfServiceHandler apfVariableDesriptor[] = {
    Service0,
    Service1,
    Service2,
    Service3,
    Service4,
    Service5,
    Service6,
    Service7,
    Service8,
    Service9,
    Service10        
};

const unsigned int MaxData =  (sizeof(astrVariableDesriptor)/sizeof(tstrVariableDesriptor));
const unsigned int MaxService =  (sizeof(apfVariableDesriptor)/sizeof(pfServiceHandler));