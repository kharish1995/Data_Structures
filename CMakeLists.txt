project(data_structures)
cmake_minimum_required(VERSION 2.8)
add_definitions("-std=c++0x") 

include_directories(src/include)

add_library(data_structures SHARED
	src/kdtree/kdtree.cpp
	src/common/node.cpp
	)


install(DIRECTORY src/include/${PROJECT_NAME} DESTINATION include
	FILES_MATCHING PATTERN "*.h")
install(TARGETS data_structures
	LIBRARY DESTINATION lib)

#add_executable(test_sbpl src/test/main.cpp)
#target_link_libraries(test_sbpl sbpl)

#add_executable(test_adjacency_list src/test/test_adjacency_list.cpp)
#target_link_libraries(test_adjacency_list sbpl)




#aux_source_directory(. SRC_LIST)
#add_executable(${PROJECT_NAME} ${SRC_LIST})

