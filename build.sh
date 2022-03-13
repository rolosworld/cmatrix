#!/bin/bash

gcc -ggdb src/main.c -o main
gcc -ggdb src/thread.c -o thread -lpthread
