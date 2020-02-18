# Copyright (C) 2019 Intel Corporation.  All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

NAME := iwasm
IWASM_ROOT := wamr/core/iwasm
SHARED_ROOT := wamr/core/shared

# Change it to THUMBV7M if you want to build for developerkit
WAMR_BUILD_TARGET := X86_32

WAMR_BUILD_PLATFORM := alios-things

ifeq (${WAMR_BUILD_TARGET}, X86_32)
  GLOBAL_DEFINES += BUILD_TARGET_X86_32
  INVOKE_NATIVE := invokeNative_ia32.s
else ifeq (${WAMR_BUILD_TARGET}, X86_64)
  GLOBAL_DEFINES += BUILD_TARGET_X86_64
  INVOKE_NATIVE := invokeNative_em64.s
else ifeq ($(findstring ARM,$(WAMR_BUILD_TARGET)), ARM)
  GLOBAL_DEFINES += BUILD_TARGET_ARM
  GLOBAL_DEFINES += BUILD_TARGET=\"$(WAMR_BUILD_TARGET)\"
  INVOKE_NATIVE := invokeNative_arm.s
else ifeq ($(findstring THUMB,$(WAMR_BUILD_TARGET)), THUMB)
  GLOBAL_DEFINES += BUILD_TARGET_THUMB
  GLOBAL_DEFINES += BUILD_TARGET=\"$(WAMR_BUILD_TARGET)\"
  INVOKE_NATIVE := invokeNative_thumb.s
else ifeq (${WAMR_BUILD_TARGET}, MIPS)
  GLOBAL_DEFINES += BUILD_TARGET_MIPS
  INVOKE_NATIVE := invokeNative_mips.s
else ifeq (${WAMR_BUILD_TARGET}, XTENSA)
  GLOBAL_DEFINES += BUILD_TARGET_XTENSA
  INVOKE_NATIVE := invokeNative_xtensa.s
else
  $(error Build target isn't set)
endif

# Enable Interpreter by default.
WAMR_BUILD_INTERP = 1

# Enable AOT by default.
WAMR_BUILD_AOT = 1

ifeq (${WAMR_BUILD_INTERP}, 1)
GLOBAL_DEFINES += WASM_ENABLE_INTERP=1
endif

ifeq (${WAMR_BUILD_AOT}, 1)
GLOBAL_DEFINES += WASM_ENABLE_AOT=1
endif

GLOBAL_DEFINES += WASM_ENABLE_LIBC_BUILTIN=1

GLOBAL_INCLUDES += ${IWASM_ROOT}/include \
                   ${IWASM_ROOT}/common \
                   ${SHARED_ROOT}/include \
                   ${SHARED_ROOT}/platform/include \
                   ${SHARED_ROOT}/platform/alios

ifeq (${WAMR_BUILD_INTERP}, 1)
GLOBAL_INCLUDES += ${IWASM_ROOT}/interpreter
endif

ifeq (${WAMR_BUILD_AOT}, 1)
GLOBAL_INCLUDES += ${IWASM_ROOT}/aot
endif

$(NAME)_SOURCES := ${SHARED_ROOT}/platform/alios/bh_assert.c \
                   ${SHARED_ROOT}/platform/alios/bh_definition.c \
                   ${SHARED_ROOT}/platform/alios/bh_math.c \
                   ${SHARED_ROOT}/platform/alios/bh_platform.c \
                   ${SHARED_ROOT}/platform/alios/bh_platform_log.c \
                   ${SHARED_ROOT}/platform/alios/bh_thread.c \
                   ${SHARED_ROOT}/platform/alios/bh_time.c \
                   ${SHARED_ROOT}/mem-alloc/bh_memory.c \
                   ${SHARED_ROOT}/mem-alloc/mem_alloc.c \
                   ${SHARED_ROOT}/mem-alloc/ems/ems_kfc.c \
                   ${SHARED_ROOT}/mem-alloc/ems/ems_alloc.c \
                   ${SHARED_ROOT}/mem-alloc/ems/ems_hmu.c \
                   ${SHARED_ROOT}/utils/bh_hashmap.c \
                   ${SHARED_ROOT}/utils/bh_list.c \
                   ${SHARED_ROOT}/utils/bh_log.c \
                   ${SHARED_ROOT}/utils/bh_queue.c \
                   ${SHARED_ROOT}/utils/bh_vector.c \
                   ${IWASM_ROOT}/libraries/libc-builtin/libc_builtin_wrapper.c \
                   ${IWASM_ROOT}/common/wasm_runtime_common.c \
                   ${IWASM_ROOT}/common/wasm_native.c \
                   ${IWASM_ROOT}/common/wasm_exec_env.c \
                   ${IWASM_ROOT}/common/arch/${INVOKE_NATIVE} \
                   src/main.c src/ext_lib_export.c

ifeq (${WAMR_BUILD_INTERP}, 1)
$(NAME)_SOURCES += ${IWASM_ROOT}/interpreter/wasm_interp.c \
                   ${IWASM_ROOT}/interpreter/wasm_loader.c \
                   ${IWASM_ROOT}/interpreter/wasm_runtime.c
endif

ifeq (${WAMR_BUILD_AOT}, 1)
$(NAME)_SOURCES += ${IWASM_ROOT}/aot/aot_loader.c \
                   ${IWASM_ROOT}/aot/aot_runtime.c
endif
