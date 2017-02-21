INSTALL
=======

Cloning
-------

```
# git clone <url>/qemu-stage
# cd qemu-stage
```

Crosstool-ng
------------

### Installation

```
# git submodule update --init crosstool-ng
# cd crosstool-ng
# ./configure --prefix=$HOME/.local/
# make
# make install
```

The installation creates a *ct-ng* executable into `$HOME/.local/bin`.

* Add it to your `PATH` directly with:

```
# pwd
~/qemu-stage
# source devenv.sh
# ct-ng --help
```

Or manually:

```
export PATH="$HOME/.local/bin:${PATH}"
```

### Build the toolchain

First of all, we need to modify the install path for the toolchain.
Arbitrarily, we prefer `/opt` over `$HOME`.

However, if you decide to create different toolchain configurations for
the same architecture target, it might be interesting to file them
according the dirname of the .config file (for example):

* Edit `$HOME/.local/lib/crosstool-ng-<version>/config/global/paths.in`
and replace the current `PREFIX_DIR` value with:

```
default "${CT_PREFIX:-/opt/x-tools/${PWD:##*/}}/${CT_HOST:+HOST-${CT_HOST}/}${CT_TARGET}"
```

* Generate the configuration files:

```
# pwd
~/qemu-stage
# cd xtools
# mkdir new-target && cd new-target
# ct-ng show-arm-unknown-eabi
```

* Configure the toolchain with `ct-ng menuconfig`:
    * Target options > Target Architecture > ARM
    * OS > Target OS > bare
    * C-library > newlib version > 2.5.0
    * C-compiler > gcc version > 5.4.0
    * Debug facilities > gdb (only if Target OS = bare)

* Build with `ct-ng build`.

See also: [How to install Crosstool-ng](http://crosstool-ng.org) and
[How to configure Crosstool-ng](http://crosstool-ng.github.io/docs/configuration/).

QEMU
----

### Installation

```
# pwd
~/qemu-stage
# git submodule update --init dtc
# cd qemu
# mkdir build && cd build
# ../configure --prefix=<somewhere> --target-list=arm-softmmu \
        --enable-sdl --with-sdlabi=2.0 --disable-vnc \
        --extra-cflags=-save-temps --enable-debug
# make
```

**--enabled-sdl --with-sdlabi=2.0**: are explicit options but enabled by default.

**--extra-cflags=-save-temps**: is an option to widely explore the source by expanding the macros from \*.c & \*.h to \*.i temporary files.

* Before building, it could be interesting to take a look at the configuration variables:

```
less config-host.mak
```

* Finally, add the executable to your `PATH`:

```
# pwd
~/qemu-stage
# source devenv.sh
# qemu-system-arm --help
```

See also: [How to install QEMU](http://wiki.qemu-project.org/Hosts/Linux).
