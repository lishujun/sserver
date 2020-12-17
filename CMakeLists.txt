cmake_minimum_required(VERSION 3.9)
project(sserver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

include_directories(./app)
include_directories(./core)
include_directories(./data)
include_directories(./net)
include_directories(./util)

link_libraries(ws2_32)

add_executable(sserver
    app/win/main.c app/win/child.c
    core/win/api.c core/win/thread.c
    data/win/hashtable.c data/win/memory.c data/win/queue.c
    net/win/listen.c net/win/request.c net/win/response.c
    util/win/config.c util/win/global.c
)
