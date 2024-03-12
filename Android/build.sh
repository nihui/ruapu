#!/bin/bash

BUILD_DIR=build

mkdir -p $BUILD_DIR
pushd $BUILD_DIR

cmake -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK/build/cmake/android.toolchain.cmake"\
    -DANDROID_ABI="arm64-v8a" \
    -DANDROID_PLATFORM=android-21 ..

make