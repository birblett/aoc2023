DIRS := lib
DIRS += $(wildcard day_*/.)

all: $(DIRS)
$(DIRS):
	$(MAKE) -C $@

.PHONY: all $(DIRS)
