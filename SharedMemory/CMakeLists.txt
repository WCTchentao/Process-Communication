cmake_minimum_required(VERSION 3.10)

project(OuterProcess)

add_executable(Server shmServer.cpp)

add_executable(Client shmClient.cpp)