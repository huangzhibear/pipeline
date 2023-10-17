cmake_minimum_required(VERSION 3.0)
project(pipeline)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include/})
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/base)
include_directories(${PROJECT_SOURCE_DIR}/event)
include_directories(${PROJECT_SOURCE_DIR}/node)

add_executable(pipeline

        base_event.h
        base_node.cpp
        base_node.h
        main.cpp
        def_head.h

        base/BS_thread_pool.hpp
        base/environment.cpp
        base/environment.h
        base/epoll_tools.cpp
        base/epoll_tools.h
        base/coroutine.h)

target_link_libraries(${PROJECT_NAME} pthread )
target_link_libraries(${PROJECT_NAME} dlib )
target_link_libraries(${PROJECT_NAME} sqlite3 )

