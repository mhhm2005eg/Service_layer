#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <string>
#include <iostream>

#include "stddefs.h"
#include "types.h"
#include "limits.h"
#include "common.h"
#include "configurations.h"
#include "pb_config.h"
#include "actions.h"
#include "logger.h"

using namespace std;
int sockfd = 0;

int main(int argc, char *argv[])
{
    int n = 0;
    char recvBuff[RECEIVE_BUFFER_LENGTH];
    struct sockaddr_in serv_addr; 
 
    make_dir("./log/");
    delet_file(log_file_name);

    memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_LISTENING_PORT); 

    if(inet_pton(AF_INET, SERVER_IP_ADDRESS , &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 

    puts("Connected ...\n");
    //char *message = "I am the first Message\n";
    char *message = (char*)(&cstData);
    int len = sizeof(cstData);//strlen(message)
    //printf("%d\n", len);
    
    frame_t* data_frame = add_data_header(message, len);
    message = (char *) data_frame;
    len = data_frame->size;
#ifdef DEBUG
    for (int i = 0; i < len; i++) printf("0x%02X ", (uint8)message[i]);
    puts("\n");
#endif
    send_all(sockfd,message ,len);
    int nn = TEST_LOOP;
    while (receive_all(sockfd, (uint8*)recvBuff) == STD_OK ){
	n = ((data_size_t*)recvBuff)[0];
	logger("RECV", hexStr((uint8*)recvBuff,n).c_str());
	take_action((frame_t*)recvBuff);
	nn--;
	if (nn == 0)break;
    }
#if 0
    while ( ((n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)&& nn > 0)
    {
        recvBuff[n] = 0;
	std::cout<<"received"<<n<<"/n";
	logger("RECEIVED", hexStr((uint8*)recvBuff,n).c_str());
	take_action((uint8*)recvBuff,n);
	nn--;
	/*
        if(fputs(recvBuff, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
	else{
	    logger("RECEIVED", hexStr((uint8*)recvBuff,n).c_str());
	    take_action((uint8*)recvBuff,n);
	}*/
	usleep(50000);
    } 

    if(n < 0)
    {
        printf("\n Read error \n");
    } 
#endif
    return 0;
}

