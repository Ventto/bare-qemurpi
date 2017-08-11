ISSUES
======

QEMU
----

### Error message while running QEMU: audio: Could not init `<driver-name>' audio driver

Disable the audio driver:

```
$ export QEMU_AUDIO_DRV="none"
```

Or:

```
$ qemu-system-$ARCH -audio-help
```

GDB
---

### Cannot enable the TUI: error opening terminal [TERM=<term-name>]

```
$ TERM=xterm gdb
```
