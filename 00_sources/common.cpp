/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <sys/socket.h>
#include <sys/types.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>
#include <sys/stat.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "limits.h"
#include "types.h"
#include "common.h"
#include "logger.h"
#include "pb_config.h"


#include "configurations.h"

#include <chrono>
#include <iomanip>

#ifdef SERVER

#include "server.h"

#endif
using namespace std;

uint8 recvBuff[RECEIVE_BUFFER_LENGTH]={0x00};

    
int send_data(int sockfd, char *message, data_size_t len){
    //message = "GET / HTTP/1.1\r\n\r\n";
    if( send(sockfd , message , len , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");
    
    logger("SENT", (hexStr((uint8*)message, len)).c_str());
    return true;
    
}

bool send_all(int socket, void *buffer, size_t length)
{
    char *ptr = (char*) buffer;
    size_t len = length;
    while (length > 0)
    {
        int i = send(socket, ptr, length, 0);
        if (i < 1) return false;
        ptr += i;
        length -= i;
    }
    logger("SENT", (hexStr((uint8*)buffer, len)).c_str());
    //std::cout<<"S"<<std::endl;
    return true;
}

uint8* receive_data(int socket_desc, data_size_t* len){
     //Receive a reply from the server
       
    int t = recv(socket_desc, recvBuff , RECEIVE_BUFFER_LENGTH-1 , 0);

    if(t < 0)
    {
        puts("recv failed");
    }
    puts("Reply received\n");
    recvBuff[t] = '\0'; 
    logger("RECV", hexStr(recvBuff,t).c_str());
    *len = t;
    return (recvBuff);
    
}

bool receive_all(int socket_desc, uint8* recvBuff){

    auto start = std::chrono::high_resolution_clock::now();
     //Receive a reply from the server
    data_size_t len = 0;
    data_size_t u32ReceivedLength = 0;
    uint8 u8LoopIndex = 10;
    uint8 length_size = sizeof(data_size_t);
    uint8 ret = STD_OK; 
    
    struct timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec = 0;
    setsockopt(socket_desc, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
    int t = recv(socket_desc, (uint8*)(&len) , length_size , 0);
    //cout<<t << " " <<len<<endl;
    ((data_size_t*)recvBuff)[0] = len;
    if (len > RECEIVE_BUFFER_LENGTH)
    {
        cout<<"Received length greater than receiving buffer"<<endl;
        cout<<"length: " <<len<<" ,Buffer size: "<<RECEIVE_BUFFER_LENGTH<<endl;
        len = RECEIVE_BUFFER_LENGTH;
        t = recv(socket_desc, &(recvBuff[length_size]) , len-length_size , 0);
        if(t < 0)
        {
            puts("recv failed");
            ret = STD_NOK;
        }
        logger("*ERR", (char*)recvBuff);
        ret = STD_NOK;
    }
    if(t < 0 || len == 0)
    {
        //puts("No more data ...");
	ret = STD_NOK;
    }
    else{
    while(u32ReceivedLength < len-length_size) {/// && u8LoopIndex > 1){    
    t = recv(socket_desc, &(recvBuff[length_size+u32ReceivedLength]) , len-length_size-u32ReceivedLength , 0);
#ifdef DEBUG
   cout<<t<< " " << u32ReceivedLength <<endl;
#endif   

    if(t < 0)
    {
        puts("recv failed");
	ret = STD_NOK;
        break;
    }
    else{
    u32ReceivedLength += t;
    //u8LoopIndex--;
    }
    }
    //cout<<t<< " " << len-length_size <<endl;
    if(t < 0)
    {
        puts("recv failed");
	ret = STD_NOK;
    }
    }
    //if (ret == STD_OK)
    auto finish = std::chrono::high_resolution_clock::now();
    std::cout << "Rec: " << fixed << setprecision(3) << setw(10) << (std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count())/1000000.0f << " ms ";
    return (ret);
    
}


frame_t* add_data_header(char* data, data_size_t size){
    static frame_t data_frame;
    data_frame.size = size + sizeof(data_size_t) + sizeof(frame_id_t);
    data_frame.id.u16Word = FRAME_ID;
    memcpy((char*)(&(data_frame.data)), data, size);
    return (& data_frame);     
    
}

uint8* remove_data_header(frame_t* data_frame, data_size_t *size, frame_id_t *id){
    static uint8 loc_data[100];
    *size = (data_frame->size - sizeof(data_size_t) - sizeof(frame_id_t));
    *id = data_frame->id.u16Word;
    memcpy(loc_data, data_frame->data, *size);
    return (loc_data);
    
}

std::string get_char(uint8  *ints){
    int len = sizeof(ints);
    static std::string ret;
    ret = "";
    int i = 0;
    for (i; i< len; i++)
    {
        //itoa(ints[i], ret[i], 10);
        printf("0x%02X ", ints[i]);
        //sprintf(&(ret[i]), "%02X", ints[i]);
        std::string s = std::to_string(ints[i]);
        std::cout<< s + " ";
        ret += s;
        
    }
    printf("\n");
    
    return (ret);
}

const char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

std::string hexStr(unsigned char *data, int len)
{
  std::string s(len * 2, ' ');
  for (int i = 0; i < len; ++i) {
    s[2 * i]     = hexmap[(data[i] & 0xF0) >> 4];
    s[2 * i + 1] = hexmap[data[i] & 0x0F];
  }
  return s;
}

void make_dir(const char* filename){
    struct stat st = {0};
    
if (stat(filename, &st) == -1) {
    std::cout<<"Creating folder: "<<filename<<std::endl;
    mkdir(filename, 0700);
}
    
}

int delet_file (const char* filename)
{
  if( remove( filename ) != 0 )
    perror( "Error deleting file" );
  else
    std::cout<< "File successfully deleted :"<< filename <<std::endl;
  return 0;
}

long get_current_time(){
    long            ms; // Milliseconds
    time_t          s;  // Seconds
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    s  = spec.tv_sec;
    long ss = (s%3600)%60;
    ms = round(spec.tv_nsec / 1.0e3); // Convert nanoseconds to milliseconds

    long time_ms = (ss * 1000000) + ms;
    return (time_ms);
}

long get_current_time_ms(){
    long            ms; // Milliseconds
    time_t          s;  // Seconds
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    s  = spec.tv_sec;
    long ss = (s%3600)%60;
    ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds

    long time_ms = (ss * 1000) + ms;
    return (time_ms);
}

void vidCallService(uint16 Id){
    frame_t strFrame;
    strFrame.size = HEADER_SIZE;
    strFrame.id.strBit.descriptor = Id;
    strFrame.id.strBit.destination = OTHER_MACHINE_ID;
    strFrame.id.strBit.status = REQUEST;
    strFrame.id.strBit.type = RUN_SERVICE;
    send_all(sockfd,(uint8 *)&strFrame ,HEADER_SIZE);
}

bool vidSCallService(uint16 Id){
	bool ret;
	frame_t DataFrame;
	vidCallService(Id);
	ret = receive_all(sockfd, (uint8*)(&DataFrame));
	if(ret == STD_OK)
	{
		//TODO
	}
	return ret;
}
void vidReadData(uint16 Id){
    frame_t strFrame;
    strFrame.size = HEADER_SIZE;
    strFrame.id.strBit.descriptor = Id;
    strFrame.id.strBit.destination = OTHER_MACHINE_ID;
    strFrame.id.strBit.status = REQUEST;
    strFrame.id.strBit.type = READ_DATA_ID;
    send_all(sockfd,(uint8 *)&strFrame ,HEADER_SIZE);
}
bool vidSReadData(uint16 u16Id){
	bool ret;
	frame_t DataFrame;
	uint8 *pu8Temp;
    uint16 u16Temp;
	vidReadData(u16Id);
	ret = receive_all(sockfd, (uint8*)(&DataFrame));
	if(ret == STD_OK)
	{
            pu8Temp = astrVariableDesriptor[u16Id].pu8Address;
	    u16Temp = astrVariableDesriptor[u16Id].u16Length;
	    memcpy( pu8Temp, (char*)(&(DataFrame.data)), u16Temp);
	}
	return ret;

}
int print_info()
{
        char hostbuf[256];
        char * ipbuf;
        struct hostent *hostentry;
        int ret;
 
        ret = gethostname(hostbuf,sizeof(hostbuf));
 
        if(-1 == ret){
                perror("gethostname");
                exit(1);
        }
 
        hostentry = gethostbyname(hostbuf);
 
        if(NULL == hostentry){
                perror("gethostbyname");
                exit(1);
        }
 
        ipbuf = inet_ntoa(*((struct in_addr *)hostentry->h_addr_list[0]));
 
        if(NULL == ipbuf){
                perror("inet_ntoa");
                exit(1);
        }
 
        printf("Hostname: %s, Host IP: %s\n", hostbuf, ipbuf);
 
        return 0;
}
