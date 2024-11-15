#!/bin/bash

# Copyright (C) 2019 Intel Corporation.  All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

PLATFORM=${WAMR_TEST_PLATFORM:-$(uname -s | tr A-Z a-z)}

IWASM="../../../product-mini/platforms/linux/build/iwasm"
WAMRC="../../../wamr-compiler/build/wamrc"

echo "Run coremark with native .."
./coremark.exe

echo "Run coremark with iwasm aot mode .."
${IWASM} coremark.aot

if [[ ${PLATFORM} == "linux" ]]; then
    echo "Run coremark with iwasm aot-segue mode .."
    ${IWASM} coremark_segue.aot
fi

if [[ ${PLATFORM} == "xtensa" && -n ${WAMR_TEST_UART_PORT} ]]; then
    echo "Run coremark with iwasm in ${WAMR_TEST_UART_PORT}"
    cp coremark_${PLATFORM}.aot /tmp
    TMPFILE=$(mktemp -u -t tmpXXXXX.uart)
    cat < ${WAMR_TEST_UART_PORT} > ${TMPFILE} &
    output_pid=$!
    echo "iwasm /tmp/coremark_${PLATFORM}.aot" > ${WAMR_TEST_UART_PORT}
    while ! grep 'nsh>' ${TMPFILE} > /dev/null
        do
	    echo -n '.'
	    sleep 5
        done
    kill -9 ${output_pid}
    cat ${TMPFILE}
fi

echo "Run coremark with iwasm interpreter mode .."
${IWASM} coremark.wasm
