#!/bin/bash

DIR=output;
DIR_LIB_EXT="/export/home/WECDIS/bin/newlib"

if [ -d "$DIR" ]; then
    rm -rf $DIR
fi

mkdir $DIR

g++ -std=c++17 -fPIC -g -c ModInfo.cpp -o $DIR/ModInfo.o
g++ -std=c++17 -fPIC -g -c libmod.cpp -o $DIR/libmod.o
g++ -std=c++17 -fPIC -g -c modapi.cpp -o $DIR/modapi.o

# Create full Modlib
g++ -std=c++17 -shared -g -o $DIR/libmod.so \
                             $DIR/modapi.o \
                             $DIR/ModInfo.o \
                             $DIR/libmod.o \
                             -ldl

# Create modlib for mods
#g++ -std=c++17 -shared -o $DIR/libmodapi.so $DIR/modapi.o
# Use or add modapi.o


# Create binary that tests mods
g++ -o $DIR/modtester main.cpp \
                        $DIR/modapi.o \
                        $DIR/ModInfo.o \
                        $DIR/libmod.o \
                        -ldl


cp $DIR/modtester $DIR_LIB_EXT/modtester
cp $DIR/modapi.o $DIR_LIB_EXT/modapi.o
cp $DIR/libmod.so $DIR_LIB_EXT/libmod.so
