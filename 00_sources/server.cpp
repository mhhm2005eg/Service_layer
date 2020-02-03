#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include <string>
#include <iostream>

#include "stddefs.h"
#include "types.h"
#include "limits.h"
#include "common.h"
#include "configurations.h"
#include "logger.h"
#include "pb_config.h"
#include "actions.h"
#include "server.h"

using namespace std;

int sockfd;
long Receive_Time;
uint32 u32ProcessingTime;

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 
    struct sockaddr_in client_addr; 
    printf("\nServer started .\n");
    char sendBuff[SEND_BUFFER_LENGTH];
    time_t ticks; 
    uint8 *frame;
    std::string sframe;
    data_size_t len;
    frame_t *pstrframe;
    
    make_dir("./log/");
    delet_file(log_file_name);
    
    printf("Create an empty socket in the Kernel (TCP).\n");
    // it returns a socket descriptor ...
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERVER_LISTENING_PORT);
    client_addr.sin_family = AF_INET;
    //client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //client_addr.sin_port = htons(SERVER_LISTENING_PORT);
    
    
    
    //specify the listening port and the interface used in case many interfaces 
    // installed
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
    inet_ntop(AF_INET, &(serv_addr.sin_addr), sendBuff, INET_ADDRSTRLEN);
    //Start listening with max 10 clients queueing 
    print_info();
    listen(listenfd, 10);
    
    struct timeval tv;
    tv.tv_sec = 10;
    tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
    
    while(1)
    {
        //printf("Waiting for connections!\n");
        // waiting for a connection request
        connfd = accept(listenfd, (struct sockaddr*)NULL , NULL); 
        getpeername(connfd, (sockaddr*)&client_addr , (socklen_t*)sizeof(client_addr));
	    sockfd = connfd;
        inet_ntop(AF_INET, &(client_addr.sin_addr), sendBuff, INET_ADDRSTRLEN);
        //cout<<"Connection from : "<<sendBuff<<endl;
#if 0	
	frame = receive_data(connfd,&len);
        logger("RECV", hexStr((uint8*)frame,len).c_str());
	take_action((frame_t*)frame);
#endif
#ifdef DEBUG
        sframe = hexStr(frame, len);
        std::cout << sframe << "\n";
#endif
        while (receive_all(sockfd, (uint8*)recvBuff) == STD_OK ){
            Receive_Time = get_current_time();
#ifdef DEBUG            
        std::cout<<"Receive Time: "<<Receive_Time<<endl; 
#endif
        len = ((data_size_t*)recvBuff)[0];
#ifdef DEBUG        
        std::cout<<len<< std::endl;//<<hexStr((uint8*)frame,len)<<std::endl;
#endif        
	//logger("RECV", hexStr((uint8*)recvBuff,len).c_str());
        
        pstrframe = (frame_t *)recvBuff;
        if (pstrframe->id.strBit.destination == SERVER_MACHINE_ID){
            vidHandleFrame(pstrframe);
        }
        else{
	take_action((frame_t*)recvBuff);
        }
    }
#if 0
	while ( (len = read(sockfd, frame, sizeof(frame)-1)) > 0)
	  {
	    std::cout<<"received"<<len<<"/n";
	    frame[len] = 0;
	    logger("RECV", hexStr((uint8*)frame,len).c_str());
	    take_action((frame_t*)frame);

	    usleep(50000);
	  } 
#endif

        close(connfd);
        //sleep(1);
     }
}
