/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   measurement.h
 * Author: osboxes
 *
 * Created on 05 February 2018, 09:13
 */

#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#define ERROR_VALUE 0xAA55AA55        
#define UNUSED_PATTEREN 0xDEADBEEF
#define STACK_MAX_SIZE 8192*1024

namespace measurement {
    
    void preMain();
    void postMain();
    unsigned int GetSP();
    class stack{
        stack();
        ~stack();
    public:
        static unsigned int *pintFirstLocation;
        static unsigned int *pintCurrentLocation;
        static unsigned int *pintLastLocation;
        static unsigned int uintSize;
        static void vidScan();
        static unsigned int uintGetSize();
        inline static void init();
                
    };


};

#endif /* MEASUREMENT_H */

