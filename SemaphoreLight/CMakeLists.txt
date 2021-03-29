cmake_minimum_required(VERSION 3.10)

project(SemaphoreTest)

add_executable(Server semaphore_server.cpp)

add_executable(Client semaphore_client.cpp)

# target_link_libraries(NewSemaphoreThread -lpthread)