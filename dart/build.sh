#!/bin/bash

PROJECT_DIR=$(pwd)
RUAPU_API_DIR="$PROJECT_DIR/ruapu-api"
BUILD_DIR="$PROJECT_DIR/build"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR" || exit

cmake "$RUAPU_API_DIR"
cmake --build "$BUILD_DIR"

if [ $? -ne 0 ]; then
  echo "Build Error!!! Plz Check!!!"
  exit 1
fi

cd "$PROJECT_DIR" || exit

dart pub get

dart run main.dart