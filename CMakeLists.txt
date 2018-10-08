cmake_minimum_required(VERSION 3.12)
project(MMSE C)

set(CMAKE_C_STANDARD 99)

add_executable(MMSE main.c mmsestsa85.c mmsestsa85.h fft.c fft.h ifft.c ifft.h debugtools.c debugtools.h)