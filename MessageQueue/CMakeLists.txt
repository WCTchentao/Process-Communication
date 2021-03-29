cmake_minimum_required(VERSION 3.10)

project(MsgQueueTest)

add_executable(MyMsgServer msg_server_2.cpp)

add_executable(MyMsgClient msg_client_2.cpp)