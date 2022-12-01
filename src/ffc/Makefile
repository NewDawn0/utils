CC = gcc
OUTFILE = ffc
OUTDIR = bin
CFLAGS = -Wall -g
OBJS = ffc.c

all: compile
.PHONY: move clean

compile: $(OBJS)
	@echo "Compiling ffc..."
	mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) -o $(OUTDIR)/$(OUTFILE) $(OBJS)

move:
	@echo "Moving ffc..."
	mkdir -p ../../bin
	mv $(OUTDIR)/* ../../bin

clean:
	@echo "Cleaning ffc..."
	rm -rf $(OUTDIR)/*.dSYM $(OUTDIR)/*.o
