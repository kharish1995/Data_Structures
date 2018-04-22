project(data_structures)
cmake_minimum_required(VERSION 2.8)
add_definitions(-Wall -Wpedantic -Wextra "-std=c++1y")
set(CMAKE_BUILD_TYPE Release)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if (NOT (GCC_VERSION VERSION_GREATER 6.3 OR GCC_VERSION VERSION_EQUAL 6.3))
        message(FATAL_ERROR "${PROJECT_NAME} requires g++ 6.3 or greater.")
    endif ()
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
else ()
    message(FATAL_ERROR "Your C++ compiler does not support C++14.")
endif ()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

install(DIRECTORY include/${PROJECT_NAME} DESTINATION include
	FILES_MATCHING PATTERN "*.h")

install(DIRECTORY include/${PROJECT_NAME} DESTINATION lib
        FILES_MATCHING PATTERN "*.h")
	
add_executable(kdtree ${CMAKE_CURRENT_SOURCE_DIR}/src/kdtree/kdtree_test.cpp)
add_executable(linkedlist ${CMAKE_CURRENT_SOURCE_DIR}/src/linkedlist/linkedlist_test.cpp)
add_executable(binarytree ${CMAKE_CURRENT_SOURCE_DIR}/src/binarytree/binarytree_test.cpp)
#add_executable(graph ${CMAKE_CURRENT_SOURCE_DIR}/src/graph/graph_test.cpp)
#add_executable(priorityqueue ${CMAKE_CURRENT_SOURCE_DIR}/src/priorityqueue/priorityqueue_test.cpp)
#add_executable(stack ${CMAKE_CURRENT_SOURCE_DIR}/src/stack/stack_test.cpp)
#add_executable(queue ${CMAKE_CURRENT_SOURCE_DIR}/src/queue/queue_test.cpp)
#add_executable(heap ${CMAKE_CURRENT_SOURCE_DIR}/src/heap/heap_test.cpp)


