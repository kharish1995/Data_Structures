project(data_structures)
cmake_minimum_required(VERSION 3.1)
add_definitions(-Wall -Wextra -Werror "-std=c++1z")

message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(${PROJECT_NAME} SHARED
	${CMAKE_CURRENT_SOURCE_DIR}/src/common/node.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/kdtree/kdtree.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/linkedlist/linkedlist.cpp
	)

install(DIRECTORY src/include/${PROJECT_NAME} DESTINATION include
	FILES_MATCHING PATTERN "*.h")
install(TARGETS data_structures
	LIBRARY DESTINATION lib)
	
add_executable(kdtree ${CMAKE_CURRENT_SOURCE_DIR}/src/kdtree/kdtree_test.cpp)
add_executable(linkedlist ${CMAKE_CURRENT_SOURCE_DIR}/src/linkedlist/linkedlist_test.cpp)
target_link_libraries(kdtree ${PROJECT_NAME})


