#!/bin/bash

set -e

cd "$(dirname "$0")"

CADICAL_LIB="external/cadical/libcadical.a"
BUILD_DIR="build"
EXEC_NAME="bcp"

if [ ! -f "$CADICAL_LIB" ]; then
    echo "========================================================"
    echo " [ERROR] Cadical library not found!"
    echo " Expected path: ./$CADICAL_LIB"
    echo "========================================================"
    echo " Please compile Cadical manually before running this script."
    echo "========================================================"
    exit 1
fi

echo "Found Cadical library. Proceeding..."

if [ -d "$BUILD_DIR" ]; then
    echo "Cleaning previous build..."
    rm -rf "$BUILD_DIR"
fi

mkdir "$BUILD_DIR"
cd "$BUILD_DIR"

echo "Configuring project..."
cmake -DCMAKE_BUILD_TYPE=Release ..

echo "Building project..."
cmake --build . --parallel

if [ -f "$EXEC_NAME" ]; then
    mv "$EXEC_NAME" ../
elif [ -f "Release/$EXEC_NAME" ]; then
    mv "Release/$EXEC_NAME" ../
else
    echo "Error: Could not locate the built executable '$EXEC_NAME'."
    exit 1
fi

echo "========================================================"
echo " Build Finished Successfully!"
echo " The executable '$EXEC_NAME' is now in the current directory."
echo "========================================================"