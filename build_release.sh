git submodule update --init --recursive
mkdir -p bin/release
cd bin/release
cmake ../../ -DCMAKE_BUILD_TYPE=Release
make -j`nproc --ignore=2`
