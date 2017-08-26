project(data_structures)
cmake_minimum_required(VERSION 2.8)
add_definitions("-std=c++0x") 

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(${PROJECT_NAME} SHARED
	${CMAKE_CURRENT_SOURCE_DIR}/src/common/node.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/kdtree/kdtree.cpp
	)

install(DIRECTORY src/include/${PROJECT_NAME} DESTINATION include
	FILES_MATCHING PATTERN "*.h")
install(TARGETS data_structures
	LIBRARY DESTINATION lib)
	
add_executable(kdtree ${CMAKE_CURRENT_SOURCE_DIR}/src/kdtree/kdtree_test.cpp)
target_link_libraries(kdtree ${PROJECT_NAME})


