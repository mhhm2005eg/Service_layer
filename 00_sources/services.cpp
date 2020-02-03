/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
#include <cstring>
#include "types.h"
#include <fasis_base/compat.h>
#include <fasis_base/error.h>
#include "fasis_base/types.h"
#include "MotionPlanningLib/motionplanninglib.h"
#include <chrono>
#include <iomanip>
LINK_LOGGING_TO_ADTF


using namespace std;
using namespace motionplanninglib;

STD_tenuStatus Service0(uint8 au8Array[], data_size_t *u16Length)
{

    auto start_whole_calculation = std::chrono::high_resolution_clock::now();
    static long calculation = 0;
    cout<<"TPL calc: "<< setw(10) << calculation << " ";

    calculation++;
    motionplanninglib::tProperties *ptProperties       = new motionplanninglib::tProperties; //#= (motionplanninglib::tProperties *) au8Array;
    configspace::tConfigSpace      *i_sConfigSpace     = new configspace::tConfigSpace;
    configspace::tTrajPlanData     *o_sOutData         = new configspace::tTrajPlanData {};
    targetpoint::tSamples          *i_sLongSampleSpace = new targetpoint::tSamples;
    targetpoint::tSamples          *i_sLatSampleSpace  = new targetpoint::tSamples;
    tResult ret = STD_NO_INIT;
    
    uint32 u32ExpectedLength = sizeof(*ptProperties) + sizeof(*i_sConfigSpace) + sizeof(*i_sLongSampleSpace)  + sizeof(*i_sLatSampleSpace);
    if (*u16Length != u32ExpectedLength)
    {
        //cout<<"Received data size (ERR!): "<<*u16Length<<", Expected : "<<u32ExpectedLength<<endl;
    }
    {
        //cout<<"Received data size: "<<*u16Length<<", Expected : "<<u32ExpectedLength<<endl;

    }
    //cout<<"1"<<endl;
    memcpy(ptProperties, au8Array, sizeof(*ptProperties));
    memcpy(i_sConfigSpace, &au8Array[sizeof(*ptProperties)], sizeof(*i_sConfigSpace));
    memcpy(i_sLongSampleSpace, &au8Array[sizeof(*ptProperties) + sizeof(*i_sConfigSpace)], sizeof(*i_sLongSampleSpace));
    memcpy(i_sLatSampleSpace, &au8Array[sizeof(*ptProperties) + sizeof(*i_sConfigSpace)+sizeof(*i_sLongSampleSpace)], sizeof(*i_sLatSampleSpace));

    //cout<<"2"<<endl;
    auto start_calculation = std::chrono::high_resolution_clock::now();
    cMotionPlanning *iMotionPlanning = new cMotionPlanning(*ptProperties, *i_sConfigSpace, *o_sOutData, *i_sLongSampleSpace, *i_sLatSampleSpace);
    
    //cout<<"3"<<endl;
    try{
    ret = iMotionPlanning->ProcessConfigSpace();
    }
    catch(int e){
        cout<< "Component : MotionPlanning Throwing Error ! "<<e<<endl;
        
    }

    auto finish_calculation = std::chrono::high_resolution_clock::now();
    //cout<<"4"<<endl;
    if(ret == 0){
        //cout<<"5"<<endl;
        *u16Length = sizeof(*o_sOutData);
        memcpy(au8Array , o_sOutData, *u16Length);
        
    }else{
        cout<<"Error Returned !"<<endl;
        *u16Length = sizeof(*o_sOutData);
        memcpy(au8Array , o_sOutData, *u16Length);
        //*u16Length = sizeof(*o_sOutData);
        //memset(au8Array, 0xDEADBEEF, 50);
        //((int *)(au8Array))[0] = ret;
    }
            
    
    delete ptProperties;
    delete i_sConfigSpace;
    delete o_sOutData;
    delete i_sLongSampleSpace, i_sLatSampleSpace;
    delete iMotionPlanning;

    auto finish_whole_calculation = std::chrono::high_resolution_clock::now();
    std::cout << "TPL Core : "  << fixed << setprecision(3) << setw(10) << (std::chrono::duration_cast<std::chrono::nanoseconds>(finish_calculation       -start_calculation       ).count())/1000000.0f << " ms ";
    std::cout << "TPL whole: "  << fixed << setprecision(3) << setw(10) << (std::chrono::duration_cast<std::chrono::nanoseconds>(finish_whole_calculation -start_whole_calculation ).count())/1000000.0f << " ms ";

    return((STD_tenuStatus)ret);
    
}

STD_tenuStatus Service1(uint8 au8Array[], data_size_t *u16Length){
    cout<<"I am service 1, remotly invoked !!!"<<endl;
    
    *u16Length = 1;
    for (int i = 0; i< *u16Length; i ++) au8Array[i] = i;
    return STD_EXEC_OK;

}
STD_tenuStatus Service2(uint8 au8Array[], data_size_t *u16Length){
    cout<<"I am service 2, remotly invoked !!!"<<endl;
    *u16Length = 2;
    for (int i = 0; i< *u16Length; i ++) au8Array[i] = i;
    return STD_EXEC_OK;    

}
STD_tenuStatus Service3(uint8 au8Array[], data_size_t *u16Length){
    
    cout<<"I am service 3, remotly invoked !!!"<<endl;
     *u16Length = 3;
    for (int i = 0; i< *u16Length; i ++) au8Array[i] = i;
    return STD_EXEC_OK;
    
}

STD_tenuStatus Service4(uint8 au8Array[], data_size_t *u16Length){
    cout<<"I am service 4, remotly invoked !!!"<<endl;
    *u16Length = 4;
    for (int i = 0; i< *u16Length; i ++) au8Array[i] = i;
    return STD_EXEC_OK;

}
STD_tenuStatus Service5(uint8 au8Array[], data_size_t *u16Length){
    
    cout<<"I am service 5, remotly invoked !!!"<<endl;
    *u16Length = 5;
    for (int i = 0; i< *u16Length; i ++) au8Array[i] = i;
    return STD_EXEC_OK;
}

STD_tenuStatus Service6(uint8 au8Array[], data_size_t *u16Length){
    
    cout<<"I am service 6, remotly invoked !!!"<<endl;
     *u16Length = 6;
    for (int i = 0; i< *u16Length; i ++) au8Array[i] = i;
    return STD_EXEC_OK;
    
}

STD_tenuStatus Service7(uint8 au8Array[], data_size_t *u16Length){
    cout<<"I am service 7, remotly invoked !!!"<<endl;
    *u16Length = 7;
    for (int i = 0; i< *u16Length; i ++) au8Array[i] = i;
    return STD_EXEC_OK;        

}
STD_tenuStatus Service8(uint8 au8Array[], data_size_t *u16Length){
    cout<<"I am service 8, remotly invoked !!!"<<endl;
    *u16Length = 8;
    for (int i = 0; i< *u16Length; i ++) au8Array[i] = i;
    return STD_EXEC_OK;

}
STD_tenuStatus Service9(uint8 au8Array[], data_size_t *u16Length){
    
    cout<<"I am service 9, remotly invoked !!!"<<endl;
    *u16Length = 9;
    for (int i = 0; i< *u16Length; i ++) au8Array[i] = i;
    return STD_EXEC_OK;
    
}

STD_tenuStatus Service10(uint8 au8Array[], data_size_t *u16Length){
     cout<<"I am service 10, remotly invoked !!!"<<endl;
    *u16Length = 10;
    for (int i = 0; i< *u16Length; i ++) au8Array[i] = i;
    
    return STD_EXEC_OK;

}
