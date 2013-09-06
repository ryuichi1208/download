#!/bin/bash

gcc -Wall -o download -lcurl $* src/*.c
