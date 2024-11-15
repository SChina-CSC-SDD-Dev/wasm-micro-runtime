#!/bin/bash

# Copyright (C) 2019 Intel Corporation.  All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

PLATFORM=${WAMR_TEST_PLATFORM:-$(uname -s | tr A-Z a-z)}

WAMRC="../../../wamr-compiler/build/wamrc"
CLANG="/opt/wasi-sdk-22.0/bin/clang"

if [ ! -d coremark ]; then
    git clone https://github.com/eembc/coremark.git
fi

cd coremark

echo "Build coremark with gcc .."
gcc -O3 -Iposix -I. -DFLAGS_STR=\""-O3 -DPERFORMANCE_RUN=1  -lrt"\" \
        -DITERATIONS=1000 -DSEED_METHOD=SEED_VOLATILE -DPERFORMANCE_RUN=1 \
        core_list_join.c core_main.c core_matrix.c core_state.c \
        core_util.c posix/core_portme.c \
        -o ../coremark.exe -lrt

echo "Build coremark with wasi-sdk .."
${CLANG} -O3 -Iposix -I. -DFLAGS_STR=\""-O3 -DPERFORMANCE_RUN=1"\" \
        -Wl,--export=main \
        -DITERATIONS=1000 -DSEED_METHOD=SEED_VOLATILE -DPERFORMANCE_RUN=1 \
        -Wl,--allow-undefined \
        core_list_join.c core_main.c core_matrix.c core_state.c \
        core_util.c posix/core_portme.c \
        -o ../coremark.wasm

cd ..

echo "Compile coremark.wasm to coremark.aot .."
${WAMRC} -o coremark.aot coremark.wasm

if [[ ${PLATFORM} == "linux" ]]; then
    echo "Compile coremark.wasm to coremark_segue.aot .."
    ${WAMRC} --enable-segue -o coremark_segue.aot coremark.wasm
fi

if [[ ${PLATFORM} == "xtensa" ]]; then
    echo "Compile coremark.wasm to coremark_${PLATFORM}.aot .."
    ${WAMRC} --target=xtensa --disable-simd --xip --mllvm=-mtext-section-literals \
	     --disable-llvm-lto -o coremark_${PLATFORM}.aot coremark.wasm
fi

echo "Done"
