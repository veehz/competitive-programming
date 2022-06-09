#!/bin/bash

problem=machine

g++ -o $problem grader.cpp $problem.cpp --std=gnu++17 -DHZLOCAL -Wall -Wextra -Wfatal-errors -Wfloat-equal -g --include /home/vyvee/Desktop/headers/all.h
