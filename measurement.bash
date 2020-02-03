#!/bin/bash
# 
# File:   measuerments.bash
# Author: osboxes
#
# Created on 02-Feb-2018, 11:18:11
#
build_dir='../03_build/'
out_dir='./02_out/'

size_app="/home/osboxes/work/pdk/VibranteSDK/toolchains/tegra-4.9-nv/usr/bin/aarch64-gnu-linux/aarch64-gnu-linux-size"
opt="--format=berkeley --totals  "
${size_app} $opt ${out_dir}client_arm_nv_linux.run ${out_dir}server_arm_nv_linux.run

if [ 1 = 2 ]
then
symboles_app="/home/osboxes/work/pdk/VibranteSDK/toolchains/tegra-4.9-nv/usr/bin/aarch64-gnu-linux/aarch64-gnu-linux-nm"
${symboles_app}  ${out_dir}client_arm_nv_linux.run ${out_dir}server_arm_nv_linux.run
fi

profiler="/home/osboxes/work/pdk/VibranteSDK/toolchains/tegra-4.9-nv/usr/bin/aarch64-gnu-linux/aarch64-gnu-linux-gprof"
${profiler}  --static-call-graph /home/osboxes/work/socket/02_out/bin/tst.run /home/osboxes/work/socket/02_out/bin/gmon.out

# ulimit -a
# display Max stack size allowed
ulimit -s

#valgrind --tool=memcheck --track-origins=yes /home/osboxes/work/socket/02_out/bin/tst.run
prog=/home/osboxes/work/socket/02_out/bin/tst.run
cd /home/osboxes/work/socket/02_out/bin/
valgrind --tool=massif $prog
valgrind --tool=massif /home/osboxes/work/socket/02_out/bin/tst.run --massif-out-file=./massif.out
sudo ms_print ./massif.out
