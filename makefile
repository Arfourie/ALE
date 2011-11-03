SAMTOOLS_PATH=samtools-0.1.18

#/jgi/tools/misc_bio/samtools/DEFAULT
CFLAGS= -g -O3

DEFAULT: all

samlib:
	make -C $(SAMTOOLS_PATH) lib

ALE: ALE.c ALE.h geneTree.c geneTree.h ALEhelpers.c ALEhelpers.h ALElike.c ALElike.h samlib
		$(CC) $(CFLAGS) ALE.c ALElike.c ALEhelpers.c geneTree.c -o ALE -lz -lm -I$(SAMTOOLS_PATH) -L$(SAMTOOLS_PATH) -lbam

synthReadGen2: synthReadGen2.c
		$(CC) $(CFLAGS) synthReadGen2.c -o synthReadGen2 -lz -lm

readFileSplitter: readFileSplitter.c
		$(CC) $(CFLAGS) readFileSplitter.c -o readFileSplitter

GCcompFinder: GCcompFinder.c
		$(CC) $(CFLAGS) GCcompFinder.c -o GCcompFinder

all: GCcompFinder readFileSplitter synthReadGen2 ALE

install: ALE synthReadGen2

clean:
		rm -f GCcompFinder readFileSplitter synthReadGen2 ALE
		make -C $(SAMTOOLS_PATH) clean


		
