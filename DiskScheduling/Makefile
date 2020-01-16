CC = gcc
FILES = diskschedule.c
OUT_EXE = diskschedule

build: $(FILES)
	$(CC) -o $(OUT_EXE) $(FILES) -lm

clean:
	rm -f *.o core

rebuild: clean build
