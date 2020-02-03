#!/bin/bash
now=$(date +"%T")
echo "Current time : $now"
pushd ./03_build/
cc='-std=c++11 -fstack-usage -g -pie -fPIC '
cc_client='  -Xlinker -Map=client.map -DCLIENT '
cc_server='  -Xlinker -Map=server.map -DSERVER '
sources=../00_sources
files=" ${sources}/actions.c ${sources}/pb_config.c ${sources}/common.c ${sources}/logger.c ${sources}/services.cpp"
include='../01_includes/'
build_dir='../03_build/'
out_dir='../02_out/'
nv_builder="/home/osboxes/work/pdk/VibranteSDK/toolchains/tegra-4.9-nv/usr/bin/aarch64-gnu-linux/aarch64-gnu-linux-g++"


echo buiding client !
g++ $cc $cc_client $files -I$include ${sources}/client.c -o ${build_dir}client.run
arm-linux-gnueabi-g++ $cc $cc_client $files ${sources}/client.c -I$include -o ${build_dir}client_arm_linux.run
$nv_builder $cc $cc_client $files ${sources}/client.c -I$include -o ${build_dir}client_arm_nv_linux.run
#arm-none-eabi-g++  $cc $cc_client $files client.c -o client_arm_none.run
echo buiding server !
g++ $cc $cc_server $files ${sources}/server.c -I$include -o ${build_dir}server.run
arm-linux-gnueabi-g++ $cc $cc_server $files ${sources}/server.c -I$include -o ${build_dir}server_arm_linux.run
$nv_builder $cc $cc_server $files ${sources}/server.c -I$include -o ${build_dir}server_arm_nv_linux.run

#arm-none-eabi-g++  $cc $cc_server $files server.c -o server_arm_none.run

#cp ${build_dir}*.run ${out_dir}*.run
/home/osboxes/work/pdk/VibranteSDK/toolchains/tegra-4.9-nv/usr/bin/aarch64-gnu-linux/aarch64-gnu-linux-size ${build_dir}client_arm_nv_linux.run
find ./ -type f -name '*.run' -exec cp '{}' ${out_dir} ';'
popd