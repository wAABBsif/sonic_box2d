git submodule update --init --recursive
mkdir -p bin/debug
cd bin/debug
cmake ../../ -DCMAKE_BUILD_TYPE=Debug
make -j`nproc --ignore=2`
