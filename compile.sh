#!/bin/bash

gcc -Wall -o download -lcurl -lncurses -lpthread $* src/*.c
