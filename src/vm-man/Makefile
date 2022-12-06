CC = gcc
OUTFILE = vm-man
OUTDIR = bin
CFLAGS = -Wall -g
OBJS = vm-man.c

all: compile
.PHONY: move clean

compile: $(OBJS)
	@echo "Compiling vm-man..."
	mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) -o $(OUTDIR)/$(OUTFILE) $(OBJS)

move:
	@echo "Moving vm-man..."
	mkdir -p ../../bin
	mv $(OUTDIR)/* ../../bin

clean:
	@echo "Cleaning vm-man..."
	rm -rf $(OUTDIR)/*.dSYM $(OUTDIR)/*.o
