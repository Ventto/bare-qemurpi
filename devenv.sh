#!/bin/sh

# Crosstool-ng and QEMU executables :
export PATH="${HOME}/.local/bin:${PATH}"

# Toolchain executables :
CT_TOP_DIR="arm-bare-metal"
CT_TARGET="arm-unknown-eabi"
export PATH="/opt/x-tools/${CT_TOP_DIR}/${CT_TARGET}/bin:${PATH}"

# Changes the toolchain :
setxtc() {
    if [ ! -d "/opt/x-tools/$1" ]; then
        echo "/opt/x-tools/$1: toolchain directory not found."
        return 1
    fi
    if [ ! -d "/opt/x-tools/$1/$2" ]; then
        echo "$2: architecture not found."
        return 1
    fi
    PATH="$(echo "${PATH}" | awk -v RS=: -v ORS=: '/opt\/x-tools/ {next} {print}')"
    export PATH="/opt/x-tools/$1/$2/bin:${PATH}"
}

alias qemu-system-arm='QEMU_AUDIO_DRV=none qemu-system-arm'
alias qemu-system-aarch64='QEMU_AUDIO_DRV=none qemu-system-aarch64'
alias arm-unknown-eabi-gdb='TERM=xterm arm-unknown-eabi-gdb'
