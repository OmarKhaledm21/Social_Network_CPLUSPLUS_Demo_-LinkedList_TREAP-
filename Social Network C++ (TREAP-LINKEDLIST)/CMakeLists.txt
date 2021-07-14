cmake_minimum_required(VERSION 3.17)
project(Social_Network)

set(CMAKE_CXX_STANDARD 17)

add_executable(Social_Network main.cpp UserInfo.cpp UserInfo.h TREAP.cpp TREAP.h LinkedList.cpp LinkedList.h)