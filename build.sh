#!/bin/bash
if [ ! -d "build" ]; then
	mkdir build
fi

g++ -o build/ps *.cpp -lboost_program_options $(pkg-config --cflags --libs icu-uc icu-i18n) $1
