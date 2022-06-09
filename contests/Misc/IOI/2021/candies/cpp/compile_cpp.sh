#!/bin/bash

problem=candies
grader_name=grader

g++ -g -std=gnu++17 -O2 -Wall -Wextra -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"
