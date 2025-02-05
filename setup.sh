#!/bin/bash

sudo apt update

sudo apt install -y \
    libtbb-dev \
    libsfml-dev \
    build-essential \
    cmake \

echo "Dependencies installed successfully"

cd engine
mkdir build
cmake -B build -S .
cd build
make
cd ../..

cd application
mkdir build
cmake -B build -S .
cd build
make
cd ../..

echo "Build complete"


