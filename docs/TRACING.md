QEMU-TRACING
============

* Merge all trace-events files:

```
find . -name "trace-events" -exec cat {} >> trace-events-all \;
```

* Create an alias for simpletrace.py
