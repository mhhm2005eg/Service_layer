/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   logger.h
 * Author: MHUSSAIN
 *
 * Created on 23 November 2017, 14:33
 */

#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif
void logger_1(char* file, const char* message);
#ifdef DEBUG
void logger(const char* tag, const char* message);
#else

#define logger(tag,message) 
#endif

#ifdef __cplusplus
}
#endif

#endif /* LOGGER_H */

