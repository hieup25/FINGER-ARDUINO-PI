#Create HieuPV
#16/01/22

cmake_minimum_required(VERSION 2.8.9)
project (test)

#add source
file(GLOB SOURCES "src/*.cpp")

add_executable(test ${SOURCES})
target_link_libraries(test -levent -lpthread)