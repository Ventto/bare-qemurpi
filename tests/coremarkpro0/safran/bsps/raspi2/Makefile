.PHONY: all
all: $(TOPDIR)/startup.o syscounter.o

$(TOPDIR)/startup.o: startup.S
	$(AS) $(AFLAGS) $< -o $@

syscounter.o: syscounter.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	$(RM) $(TOPDIR)/startup.o
