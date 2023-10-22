cmake_minimum_required(VERSION 3.24)
project(IfaradaLoadBalancer C)

set(CMAKE_C_STANDARD 99)

add_executable(InstanceHost.h User.c LoadBalancer.h LoadBalancer.c InstanceHost.c)
