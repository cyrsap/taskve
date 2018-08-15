#!/usr/bin/env bash

conan install conanfile.txt --build missing
mkdir build
pushd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
make