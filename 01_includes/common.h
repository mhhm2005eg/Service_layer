/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   common.h
 * Author: MHUSSAIN
 *
 * Created on 23 November 2017, 10:21
 */

#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#define HEADER_SIZE (sizeof(data_size_t)+sizeof(frame_id_t))    

extern  uint8 recvBuff[];
extern int sockfd;

int send_data(int sockfd, char *message, data_size_t len);
uint8* receive_data(int socket_desc, data_size_t* len);
bool send_all(int socket, void *buffer, size_t length);
bool receive_all(int socket_desc, uint8* server_reply);
frame_t* add_data_header(char* data, data_size_t size);
uint8* remove_data_header(frame_t* data_frame, data_size_t *size, frame_id_t *id);
std::string get_char(uint8  ints[]);
std::string hexStr(unsigned char *data, int len);
void make_dir(const char* filename);
int delet_file (const char* filename);
long get_current_time();
void vidCallService(uint16 Id);
void vidReadData(uint16 Id);
int print_info();
#ifdef __cplusplus
}
#endif

#endif /* COMMON_H */

