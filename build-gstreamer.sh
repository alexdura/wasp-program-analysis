#!/bin/bash


export LLVM_COMPILER=clang
# Valgrind uses some assembly, which is hard to analyze, disable.

wllvm --help &> /dev/null
if (($? != 0))
then
    echo "Your system is missing wllvm, a compiler wrapper for llvm. Run 'pip3 install wllvm' to install it."
    exit 1
fi


pushd gst-build
if [ ! -f `pwd`/build/build.ninja ]
then
    # There is no build directory, make one
    mkdir `pwd`/build
    mkdir `pwd`/install
    ENABLE_VALGRIND=0 \
		   CFLAGS=$'-g -O1 -Xclang -disable-llvm-passes -D__NO_STRING_INLINES  -D_FORTIFY_SOURCE=0 -U__OPTIMIZE__' \
		   CC=wllvm \
		   meson build
fi

pushd build
ninja -j8
# Uncomment the line below to also install
# DESTDIR=`pwd`/../install ninja install
popd
# Extract LLVM bitcode from all executables/libraries
find ./build -executable -type f | xargs -I '{}' extract-bc '{}'
find ./install -executable -type f | xargs -I '{}' extract-bc '{}'
popd
