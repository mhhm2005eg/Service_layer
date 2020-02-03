/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   configurations.h
 * Author: MHUSSAIN
 *
 * Created on 23 November 2017, 12:25
 */

#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#define SERVER_IP_ADDRESS "127.0.0.1\0"    
#define SERVER_LISTENING_PORT 5000
#define CLIENT_LISTENING_PORT 5001
    
#define TEST_LOOP 10    
    
#define FRAME_ID 45

#define SERVER_MACHINE_ID 0X01    
#define CLIENT_MACHINE_ID 0X02
#define MACHINE_ID SERVER_MACHINE_ID
#define OTHER_MACHINE_ID CLIENT_MACHINE_ID    
    
    
#ifdef SERVER
    #define log_file_name "./log/server.log"
#elif defined CLIENT
    #define log_file_name "./log/client.log"
#else
    #define log_file_name "./log/log.log"
#endif    

#ifdef __cplusplus
}
#endif

#endif /* CONFIGURATIONS_H */

