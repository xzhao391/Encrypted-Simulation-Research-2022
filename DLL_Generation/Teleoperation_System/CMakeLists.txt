SET(BOOSTROOT "D:\\Enc_3\\boost_1_78_0")

FIND_PACKAGE(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

cmake_minimum_required(VERSION 3.22)
project(Tele)

ADD_LIBRARY(Tele SHARED
        Dyer.cpp)

