/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   actions.h
 * Author: MHUSSAIN
 *
 * Created on 25. November 2017, 02:01
 */

#ifndef ACTIONS_H
#define ACTIONS_H




extern void take_action(frame_t* data_frame);

extern void take_action(uint8* data, int len);

extern void vidHandleService(frame_t *DataFrame);

extern void vidHandleFrame(frame_t *DataFrame);


#endif /* ACTIONS_H */

