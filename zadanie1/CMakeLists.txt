cmake_minimum_required(VERSION 3.16)
project(MetaprogramowanieIIZadanie1 LANGUAGES CXX)

# Domyślnie C++17; inny standard można wybrać przez -DCMAKE_CXX_STANDARD=20.
if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(zadanie1 main.cpp)

if(MSVC)
    target_compile_options(zadanie1 PRIVATE /W4 /permissive-)
else()
    target_compile_options(zadanie1 PRIVATE -Wall -Wextra -pedantic)
endif()
