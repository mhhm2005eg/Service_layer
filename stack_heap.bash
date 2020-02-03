#!/bin/bash
# 
# File:   measuerments.bash
# Author: osboxes
#
# Created on 02-Feb-2018, 11:18:11
#

#valgrind --tool=memcheck --track-origins=yes /home/osboxes/work/socket/02_out/bin/tst.run
prog=/home/osboxes/work/socket/02_out/bin/tst.run
wd=/home/osboxes/work/socket/02_out/bin/
cd $wd
#valgrind --tool=massif $prog
#valgrind --tool=massif /home/osboxes/work/socket/02_out/bin/tst.run --massif-out-file=./massif.out
#sudo ms_print ./massif.out


valgrind  --tool=massif --stacks=yes --heap=yes  --time-unit=i --massif-out-file=$wd/massif.out $prog 
ms_print ./massif.out
#sudo ms_print ./massif.out
valgrind  --tool=exp-dhat $prog 