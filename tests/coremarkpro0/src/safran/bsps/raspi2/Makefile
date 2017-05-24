.PHONY: all
all: $(TOPDIR)/src/startup.o syscounter.o

$(TOPDIR)/src/startup.o: startup.S
	$(AS) $(AFLAGS) $< -o $@

syscounter.o: syscounter.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	$(RM) $(TOPDIR)/startup.o
