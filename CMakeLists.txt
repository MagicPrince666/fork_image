CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
option(EXAMPLE "shall we complie example" on)
# INCLUDE(build_for_h3)

include_directories(${CMAKE_SOURCE_DIR}/include)

PROJECT(CppDemo)

# SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_STANDARD 11)

MESSAGE(STATUS ${CMAKE_SYSTEM_NAME})

# IF (WIN32)
# 	MESSAGE(STATUS "Now is windows.")
#     add_subdirectory(iocp)
# ELSEIF (APPLE)
# 	MESSAGE(STATUS "Now is Apple systens.")
#     add_subdirectory(kqueue)
# ELSEIF (UNIX)
# 	MESSAGE(STATUS "Now is UNIX-like OS's.")
#     add_subdirectory(epoll)
# ENDIF ()

# add_subdirectory(imu)
# add_subdirectory(distance)
# add_subdirectory(ultrasonic)
# add_subdirectory(moto)
# add_subdirectory(display)

set(EXEC_NAME forktest)

add_executable(${EXEC_NAME} main.cc
    multiple.cc
)

target_link_libraries(${EXEC_NAME} 
    pthread
    # multiplexing
    # distance
    # imu
    # moto
    # display
    # ultrasonic
)

add_executable(hello test/hello.cc)
add_executable(hi test/hi.cc)
