cmake_minimum_required(VERSION 3.22)
project(CLion_Projects)

set(CMAKE_CXX_STANDARD 14)

add_executable(CLion_Projects main.cpp AVLTree.h node.h Binary_Tree.h Hash_Table.h Ordered_Array.h Unordered_Array.h AVLTree.cpp Binary_Tree.cpp Ordered_Array.cpp Unordered_Array.cpp)
