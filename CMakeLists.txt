cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

# project name and enable C++ support
project(parameter_exploration LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  
 
 
find_package(Boost COMPONENTS system filesystem thread unit_test_framework REQUIRED)
find_package(OpenSSL REQUIRED)

add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})


set( EXECUTABLE_NAME param )

add_executable(${EXECUTABLE_NAME} main.cpp )

target_include_directories(${EXECUTABLE_NAME} PRIVATE include . )
target_link_directories(${EXECUTABLE_NAME} PRIVATE ${Boost_LIBRARY_DIRS} )

 
target_link_libraries(${EXECUTABLE_NAME}  OpenSSL::SSL Boost::system Boost::thread )


     

