#!/bin/bash
# 
# File:   test_arm.bash
# Author: MHUSSAIN
#
# Created on 29.11.2017, 17:53:55
#


CMD="qemu-arm -L /usr/arm-linux-gnueabi server_arm_linux.dep" 


gnome-terminal -x sh -c "$CMD; bash"

sleep .5

CMD="qemu-arm -L /usr/arm-linux-gnueabi client_arm_linux.dep"

gnome-terminal -x sh -c "$CMD; bash"
