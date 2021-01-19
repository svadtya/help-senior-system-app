cmake_minimum_required(VERSION 3.15)
project(BIT205_ASSIGNMENT)

set(CMAKE_CXX_STANDARD 14)

add_executable(BIT205_ASSIGNMENT SeniorHELPSystem.h main.cpp SeniorHelp.cpp User.cpp Senior.cpp Provider.cpp ServiceType.cpp ServiceRequest.cpp Review.cpp)