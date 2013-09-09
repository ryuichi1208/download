#!/bin/bash

gcc -Wall -o download -lcurl -lncurses $* src/*.c
