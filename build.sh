#! /usr/bin/bash

build="./build"

if test -d $build; then
    rm -rf $build
fi

mkdir "${build}"
cd "${build}"
cmake ..
make

../bin/SolarSystemSim