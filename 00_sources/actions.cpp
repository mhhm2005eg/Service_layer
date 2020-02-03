/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <string>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <math.h>

#include "stddefs.h"
#include "types.h"
#include "limits.h"
#include "common.h"
#include "configurations.h"
#include "logger.h"
#include "pb_config.h"
#include "actions.h"
#include "server.h"
#include <chrono>
#include <iomanip>

extern int sockfd;

using namespace std;

long Before_Sending_Time = 0;
long After_Sending_Time  = 0;

  
void take_action(uint8* data, int len){
    
    for (int i = 0; i < len; i++)data[i]++;
    
#ifdef DEBUG
	cout<<"Before Sending Time: "<<get_current_time()<<endl;
#endif
    send_all(sockfd,data ,len);
#ifdef DEBUG
	cout<<"After Sending Time: "<<get_current_time()<<endl;
#endif
	    
}
void take_action(frame_t* data_frame){
    
    
    data_size_t len = data_frame->size - HEADER_SIZE;
    for (int i = 0; i < len; i++){
        data_frame->data[i]++;
        usleep(1);
    }
    Before_Sending_Time = get_current_time();
#ifdef DEBUG
    cout<<"Before Sending Time: "<<Before_Sending_Time<<endl;
#endif
    send_all(sockfd,(uint8*)data_frame ,data_frame->size);

    After_Sending_Time = get_current_time();
#ifdef SERVER    
    u32ProcessingTime = (Before_Sending_Time - Receive_Time) ;
    //u32ProcessingTime = round((Before_Sending_Time - Receive_Time)/ 1.0e3) ;
    //u16ProcessingTime = Before_Sending_Time - Receive_Time ;
    logger("INFO", ("Processing : "+std::to_string(u32ProcessingTime)).c_str());
#endif

#ifdef DEBUG
	cout<<"After Sending Time : "<<After_Sending_Time<<endl;
#endif
	    
}

void vidHandleService(frame_t *DataFrame)
{
    uint8 *pu8Temp;
    uint16 u16Temp;
    tstrVariableDesriptor * pstrVariableDesriptor;
    bool ret;
    data_size_t u32length;
    switch(DataFrame->id.strBit.type)
    {
	case READ_DATA_ID:
	    pu8Temp = astrVariableDesriptor[DataFrame->id.strBit.descriptor].pu8Address;
	    u16Temp = astrVariableDesriptor[DataFrame->id.strBit.descriptor].u16Length;
            if (DataFrame->id.strBit.descriptor > MaxData)
            {
                cout<<"Read data error: "<<DataFrame->id.strBit.descriptor <<" Max: "<<MaxData<<endl;
                DataFrame->id.strBit.error = STD_NOK;
                break;
            }
	    memcpy((char*)(&(DataFrame->data)), pu8Temp, u16Temp);
	    DataFrame->size += u16Temp;
	    break;
	case WRITE_DATA_ID:
	    pu8Temp = astrVariableDesriptor[DataFrame->id.strBit.descriptor].pu8Address;
	    u16Temp = astrVariableDesriptor[DataFrame->id.strBit.descriptor].u16Length;
	    memcpy( pu8Temp, (char*)(&(DataFrame->data)), u16Temp);
	    DataFrame->size -= u16Temp;	    
	    break;
	case READ_DATA_ADD:
	    pstrVariableDesriptor = (tstrVariableDesriptor*)DataFrame->data;
	    pu8Temp = pstrVariableDesriptor->pu8Address;
	    u16Temp = pstrVariableDesriptor->u16Length;
	    memcpy((char*)(&(DataFrame->data)), pu8Temp, u16Temp);
	    DataFrame->size += u16Temp-sizeof(tstrVariableDesriptor);
	    break;
	case WRITE_DATA_ADD:
	    pstrVariableDesriptor = (tstrVariableDesriptor*)DataFrame->data;
	    pu8Temp = pstrVariableDesriptor->pu8Address;
	    u16Temp = pstrVariableDesriptor->u16Length;
	    memcpy(pu8Temp, (char*)(&(DataFrame->data)), u16Temp);
	    DataFrame->size -= u16Temp+sizeof(tstrVariableDesriptor);
	    break;

	case RUN_SERVICE:
	    // Check if the descriptor is valid
            ret = false;
            //uint8 au8array[12];
            u32length=DataFrame->size-sizeof(DataFrame->size)-sizeof(DataFrame->id);
           // cout<<u32length<<" "<<DataFrame->size<<" "<<sizeof(DataFrame->size)<<" "<<sizeof(DataFrame->id)<<endl;
            if (DataFrame->id.strBit.descriptor > MaxService)
            {
                cout<<"Invoke service error: "<<DataFrame->id.strBit.descriptor <<" Max: "<<MaxService<<endl;
                return;
            }
	    ret = apfVariableDesriptor[DataFrame->id.strBit.descriptor]((uint8*)(&(DataFrame->data)), &u32length);
            DataFrame->id.strBit.error = ret;
            if (ret == STD_OK){
                //memcpy((char*)(&(DataFrame->data)), au8array, u32length);
            	//cout << u32length <<endl;
            	//cout << sizeof(DataFrame->data)<<endl;
            	//cout << sizeof(DataFrame->size)<<endl;
            	//cout << sizeof(DataFrame->id)<<endl;
                DataFrame->size  = u32length + sizeof(DataFrame->size)+ sizeof(DataFrame->id);
                //cout << DataFrame->size<<endl;
            }
	    break;
	default:
            DataFrame->id.strBit.error = STD_NOK;
            break;

	
    }
    DataFrame->id.strBit.status = RESPONSE;
    DataFrame->id.strBit.destination == CLIENT_MACHINE_ID;

    auto start_sending = std::chrono::high_resolution_clock::now();
    
    send_all(sockfd,(uint8*)DataFrame ,DataFrame->size);

    auto finish_sending = std::chrono::high_resolution_clock::now();
    std::cout << "Send: " << fixed << setprecision(3) << setw(10) << (std::chrono::duration_cast<std::chrono::nanoseconds>(finish_sending - start_sending).count())/1000000.0f << " ms" << std::endl;
}

void vidHandleResponse(frame_t *DataFrame)
{
    switch(DataFrame->id.strBit.type)
    {
            
    	case READ_DATA_ID:
	    break;
	case WRITE_DATA_ID:
	    break;
	case READ_DATA_ADD:
	    break;
	case WRITE_DATA_ADD:
	    break;
	case RUN_SERVICE:
	    break;
	default:break;

	
    }
    
    
}

void vidHandleFrame(frame_t *DataFrame)
{
    switch(DataFrame->id.strBit.status)
    {
        case RESPONSE: 
            vidHandleResponse(DataFrame);
            break;
        case REQUEST:
            vidHandleService(DataFrame);
            break;
        default:break;
            
            
        }
    
    
}
