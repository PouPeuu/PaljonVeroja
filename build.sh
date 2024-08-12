#!/bin/bash
if [ ! -d "build" ]; then
	mkdir build
fi

g++ -o build/pv *.cpp
