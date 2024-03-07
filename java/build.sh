cmake -B build -DBUILD_EXAMPLE=ON
cmake --build build --target install

cd build/install
java Example