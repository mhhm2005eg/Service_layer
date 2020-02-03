project(server)
cmake_minimum_required(VERSION 3.2.2)

set(TPL_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/../01_Embedded_1_5_0_to_5_run/02_E1_5_5_no_QT_fabs_ok" CACHE FILEPATH "description")
set(SMARTDEV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../01_Embedded_1_5_0_to_5_run/02_E1_5_5_no_QT_fabs_ok" CACHE FILEPATH "description")
set(FAS_ROOT     "${CMAKE_CURRENT_SOURCE_DIR}/../01_Embedded_1_5_0_to_5_run/02_E1_5_5_no_QT_fabs_ok" CACHE FILEPATH "description")

#set(VIBRANTE_PDK "/home/osboxes/NVIDIA/Drive/5050L_SDK/DriveSDK/drive-t186ref-linux")
#include(/usr/local/driveworks/samples/cmake/Toolchain-V4L.cmake)

# ---------------------------
# ------- Set Server --------
# ---------------------------

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/02_out)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(sources ${CMAKE_CURRENT_SOURCE_DIR}/00_sources/actions.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/00_sources/logger.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/00_sources/pb_config.cpp 
	    ${CMAKE_CURRENT_SOURCE_DIR}/00_sources/server.cpp 
	    ${CMAKE_CURRENT_SOURCE_DIR}/00_sources/services.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/00_sources/common.cpp  )

#subdirs(00_sources)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/00_sources)

if(UNIX)
    #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static -g -pg ")
    #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wno-unused-function -v ")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wno-unused-function -DSERVER")
    SET(GCC_COVERAGE_LINK_FLAGS    "--stack,8388608 -r ")
endif()

# ---------------------------
# ---Include TPL Lib --------
# ---------------------------

set(SWCONFIG_DIR ${SMARTDEV_DIR})
set(COMPILER_VERSION  V4_6_4)

find_package(SWCONFIG REQUIRED NAMES FASIS)

set(TPL_SRC_DIR ${TPL_DIR}/src)
set(TPL_DEV_DIR ${TPL_DIR}/Dev)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/01_includes)
include_directories(${TPL_DEV_DIR}/../include)
include_directories(${TPL_DEV_DIR}/fasis_base/include)
include_directories(${TPL_DEV_DIR}/TrajectoryCheckLib/include)
include_directories(${TPL_DEV_DIR}/TrajectoryLib/include)
include_directories(${TPL_DEV_DIR}/TestPlotLib/include)
include_directories(${TPL_DEV_DIR}/LoggingLib/include)
include_directories(${TPL_DEV_DIR}/GeoToolsLib/include)
include_directories(${TPL_DEV_DIR}/GeoTrafoLib/include)
include_directories(${TPL_DEV_DIR}/AEVMatrixLib/include)
include_directories(${TPL_DEV_DIR}/CCCTL/include)

#add_subdirectory(${TPL_SRC_DIR}motionplanninglib   ${TPL_SRC_DIR}motionplanninglib/lib   )
#add_subdirectory(${TPL_SRC_DIR}configspacelib      ${TPL_SRC_DIR}configspacelib/lib      )
#add_subdirectory(${TPL_SRC_DIR}poly5trajectory     ${TPL_SRC_DIR}poly5trajectory/lib     )
#add_subdirectory(${TPL_SRC_DIR}poly5trajectory     ${TPL_SRC_DIR}poly5trajectory/lib     )

add_subdirectory( ${TPL_SRC_DIR}/                   ${TPL_SRC_DIR}/lib                    )

#add_subdirectory(${TPL_DEV_DIR}/fasis_base         ${TPL_DEV_DIR}/fasis_base/lib         )        
add_subdirectory( ${TPL_DEV_DIR}/TrajectoryLib      ${TPL_DEV_DIR}/TrajectoryLib/lib      )
#add_subdirectory(${TPL_DEV_DIR}/CCCTL             "${CMAKE_CURRENT_BINARY_DIR}/CCCTL/lib")
add_subdirectory( ${TPL_DEV_DIR}/AEVMatrixLib       ${TPL_DEV_DIR}/AEVMatrixLib/lib       )
add_subdirectory( ${TPL_DEV_DIR}/GeoTrafoLib        ${TPL_DEV_DIR}/GeoTrafoLib/lib        )
add_subdirectory( ${TPL_DEV_DIR}/GeoToolsLib        ${TPL_DEV_DIR}/GeoToolsLib/lib        )       
add_subdirectory( ${TPL_DEV_DIR}/gTest_Profiler     ${TPL_DEV_DIR}/gTest_Profiler/lib     )    
add_subdirectory( ${TPL_DEV_DIR}/LoggingLib         ${TPL_DEV_DIR}/LoggingLib/lib         ) 
#add_subdirectory(${TPL_DEV_DIR}/QCustomPlot        ${TPL_DEV_DIR}/QCustomPlot/lib        )
#add_subdirectory(${TPL_DEV_DIR}/}TestPlotLib       ${TPL_DEV_DIR}/TestPlotLib/lib        )       
add_subdirectory( ${TPL_DEV_DIR}/TrajectoryCheckLib ${TPL_DEV_DIR}/TrajectoryCheckLib/lib )

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/02_out/lib)


# ---------------------------
# Compile Server with TPL lib
# ---------------------------

add_executable(server.run ${sources})
target_link_libraries( server.run MotionPlanningLib ConfigSpace  FrenetSpace ConfigSpace GeoToolsLib TrajectoryLib)
target_link_libraries( server.run TrajectoryLib     )
target_link_libraries( server.run GeoToolsLib       )
target_link_libraries( server.run GeoTrafoLib       )
target_link_libraries( server.run AEVMatrixLib      )
target_link_libraries( server.run LoggingLib        )
target_link_libraries( server.run TrajectoryCheckLib)
target_link_libraries( server.run gTest_Profiler    )
target_link_libraries( server.run Poly5Trajectory   )
#target_link_libraries(server.run ConfigSpace       )
target_link_libraries( server.run TrajMultiPart     )
#target_link_libraries(server.run FrenetSpace       )


# target_link_libraries(MotionPlanningLib ConfigSpace)
   
if(TARGET server_arm_nv_linux.run)
  include(/usr/local/driveworks/samples/cmake/Toolchain-V4L.cmake)
endif()

#add_executable(server_arm_nv_linux.run ${sources})

#target_link_libraries(server_arm_nv_linux.run  -lpthread)
target_link_libraries(server.run  -lpthread)

#add_executable(tst.run ${CMAKE_CURRENT_SOURCE_DIR}/00_sources/test.cpp ${CMAKE_CURRENT_SOURCE_DIR}/00_sources/measurement.cpp)

#CUDA_ADD_EXECUTABLE(gpu ${SRC_LIST})
