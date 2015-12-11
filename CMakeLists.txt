cmake_minimum_required (VERSION 2.6)
project (utilcpp)

if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHa")
else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
endif()

aux_source_directory(src SRC)
list(APPEND FULL_SRC ${SRC})

#add_library(${PROJECT_NAME} ${FULL_SRC})

install (FILES include/util.hpp DESTINATION include/${PROJECT_NAME})
#INSTALL(TARGETS ${PROJECT_NAME} DESTINATION "lib")
