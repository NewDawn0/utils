CC = gcc
OUTFILE = serde-ffmpeg
OUTDIR = bin
CFLAGS = -Wall -g
OBJS = serde-ffmpeg.c ../../common/vector.c

all: compile
.PHONY: move clean

compile: $(OBJS)
	@echo "Compiling serde-ffmpeg..."
	mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) -o $(OUTDIR)/$(OUTFILE) $(OBJS)

move:
	@echo "Moving serde-ffmpeg..."
	mkdir -p ../../bin
	mv $(OUTDIR)/* ../../bin

clean:
	@echo "Cleaning serde-ffmpeg..."
	rm -rf $(OUTDIR)/*.dSYM $(OUTDIR)/*.o
