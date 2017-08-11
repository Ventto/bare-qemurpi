Utils
=====

###Mount disk image partitions (ex:/dev/loop0p1, /dev/loop0p2)

```
sudo losetup --show -f -P diskimage.img
```

### Details about a device file

```
file -sL /dev/sd*
```

Kernel Boot
===========

Rpi2
----

Error:

```
qemu-system-arm -M raspi2 -m 256 \
		-no-reboot \
		-kernel kernel7.img \
		-sd 2017-04-10-raspbian-jessie-lite.img \
		-append "rw earlyprintk loglevel=8 console=ttyAMA0,115200 dwc_otg.lpm_enable=0 root=/dev/mmcblk0p2 rootfstype=ext4" \
		-dtb bcm2709-rpi-2-b.dtb -serial stdio
```

VersatilePB
-----------

Patched kernel is required. The patch deals with CONFIG files not sources.

```
qemu-system-arm -M versatilepb -cpu arm1176 -m 256 \
		-kernel kernel-qemu-4.4.34-jessie \
		-serial stdio -append "root=/dev/sda2 panic=1 rootfstype=ext4 rw" \
		-drive "file=2017-04-10-raspbian-jessie-lite.img,index=0,media=disk,format=raw" \
		-redir tcp:2222::22
```

Display Kernel log in console or in graphic windows:
* Kernel options
* Display in console

```
-append "console=ttyAMA0,115200"
```

Show and save Linux Kernel log:

```
command | tee file.log
```

Boot
====

Workflow
--------

1. VC GPU -> read SD -> bootcode.bin -> start.elf + config.txt -> loads kernel7.img
    * bootcode.bin: searchs start.elf and config.txt
    * start.elf: code that runs on the GPU to provide requirements of OpenGL
1. CPU    -> exec kernel7.img (at 0x8000)

Memory Mappings
---------------

[RPI]  Peripherals: 0x20000000
[RPI2] Peripherals: 0x3F000000 (same for RPI3)

RAM: 0x00000000


Clocks
======

* Oscillator        19.2    MHz

* I2C               100     KHz
* USB               480     MHz
* Processor         800     MHz
* SP804             1       MHz ( ? )
* APB               126     MHz (pclk)
* UART\_0           3       MHz (pclk)
* UART\_1           125     MHz (pclk)

Issues
======

### Only 1 out of 4 CPUs brought up

* Modify kernel CONFIG files
* Or bypass with U-Boot

See Also
========

linux-arm.patch: https://github.com/cantora/qemu-arm-rpi-kernel

