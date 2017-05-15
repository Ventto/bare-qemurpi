.PHONY: all
all: $(TOPDIR)/startup.o

$(TOPDIR)/startup.o: startup.S
	$(AS) $(AFLAGS) $< -o $@

.PHONY:clean
clean:
	$(RM) $(TOPDIR)/startup.o
