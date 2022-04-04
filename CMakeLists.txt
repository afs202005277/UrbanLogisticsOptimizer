cmake_minimum_required(VERSION 3.20)
project(Projeto1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projeto1 codigo/main.cpp codigo/Courier.cpp codigo/Courier.h codigo/WarehouseManagement.cpp codigo/WarehouseManagement.h codigo/TransportTypes.h codigo/NormalPackageGenerator.cpp codigo/NormalPackageGenerator.h)
