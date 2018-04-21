project(data_structures)
cmake_minimum_required(VERSION 3.1)
add_definitions(-Wall -Wpedantic -Wextra "-std=c++1y")
set(CMAKE_BUILD_TYPE Release)

#set (datastructure_VERSION_MAJOR 1)
#set (datastructure_VERSION_MINOR 0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#configure_file (
#  "${PROJECT_SOURCE_DIR}/datastructureConfig.h.in"
#  "${PROJECT_BINARY_DIR}/datastructureConfig.h"
# )

install(DIRECTORY include/${PROJECT_NAME} DESTINATION include
	FILES_MATCHING PATTERN "*.h")

install(DIRECTORY include/${PROJECT_NAME} DESTINATION lib
        FILES_MATCHING PATTERN "*.h")
	
add_executable(kdtree ${CMAKE_CURRENT_SOURCE_DIR}/src/kdtree/kdtree_test.cpp)
#add_executable(linkedlist ${CMAKE_CURRENT_SOURCE_DIR}/src/linkedlist/linkedlist_test.cpp)
add_executable(binarytree ${CMAKE_CURRENT_SOURCE_DIR}/src/binarytree/binarytree_test.cpp)
#add_executable(graph ${CMAKE_CURRENT_SOURCE_DIR}/src/graph/graph_test.cpp)
#add_executable(priorityqueue ${CMAKE_CURRENT_SOURCE_DIR}/src/priorityqueue/priorityqueue_test.cpp)
#add_executable(stack ${CMAKE_CURRENT_SOURCE_DIR}/src/stack/stack_test.cpp)
#add_executable(queue ${CMAKE_CURRENT_SOURCE_DIR}/src/queue/queue_test.cpp)
#add_executable(heap ${CMAKE_CURRENT_SOURCE_DIR}/src/heap/heap_test.cpp)
#target_link_libraries(kdtree ${PROJECT_NAME})


