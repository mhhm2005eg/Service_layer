/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   measurement.cpp
 * Author: osboxes
 * 
 * Created on 05 February 2018, 09:13
 */
#include <iostream>
#include <sys/resource.h>

#include "measurement.h"

using namespace measurement;
using namespace std;

unsigned int* measurement::stack::pintFirstLocation=(unsigned int *)ERROR_VALUE;
unsigned int* measurement::stack::pintCurrentLocation=(unsigned int *)ERROR_VALUE;
unsigned int* measurement::stack::pintLastLocation=(unsigned int *)ERROR_VALUE;
unsigned int measurement::stack::uintSize=0;

    
//measurement::stack x();

void measurement::stack::vidScan(){
    for (pintCurrentLocation = pintFirstLocation; pintCurrentLocation < (pintFirstLocation + STACK_MAX_SIZE); pintCurrentLocation +=1){

        if (*pintCurrentLocation == UNUSED_PATTEREN){

            pintLastLocation = pintCurrentLocation;
            uintSize = pintLastLocation - pintFirstLocation;
        }
    }

}
unsigned int measurement::stack::uintGetSize(){
    uintSize = pintLastLocation - pintFirstLocation;
    return(uintSize);
}
inline void measurement::stack::init(){
    cout<<"Init In"<<endl;
    rlimit *rlp;
    rlp = new rlimit;
    int ret;
    ret = getrlimit(RLIMIT_STACK, rlp);
    cout<<"Stack size available"<<" "<<rlp->rlim_cur<<" : "<<rlp->rlim_max<<endl;
    //exit(0);
        
    for (pintCurrentLocation = pintFirstLocation; pintCurrentLocation < (pintFirstLocation + STACK_MAX_SIZE); pintCurrentLocation +=1){

        cout<<pintFirstLocation<<" "<<pintCurrentLocation<<" "<<(pintCurrentLocation -  pintFirstLocation)*4<< " "<<sizeof(UNUSED_PATTEREN)<<endl;
        *pintCurrentLocation = UNUSED_PATTEREN;
    }
}

void measurement::preMain(){
    cout<<"PreMain In"<<endl;
    measurement::GetSP();
    unsigned int intFirst;
    unsigned int int2First;
    cout<<&intFirst<< "   " <<&int2First<<endl;
    measurement::stack::pintFirstLocation = &intFirst;
    measurement::stack::init();
    cout<<"PreMain out"<<endl;
}
void measurement::postMain(){
    cout<<"PostMain In"<<endl;
    //measurement::stack::vidScan();
    std::cout<<"Max Stack size: "<<STACK_MAX_SIZE<<std::endl;
    std::cout<<"Used Stack size: "<<measurement::stack::uintSize<<std::endl;
    cout<<"PostMain out"<<endl;


}

unsigned int measurement::GetSP(){
//register int sp asm ("r13");
register unsigned int sp asm ("sp");
cout<<sp<<endl;
//printf("%x", sp);
return(sp);
}

