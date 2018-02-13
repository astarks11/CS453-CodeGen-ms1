ROOT = /home/cs453/spring18/stlib-a
CFLAGS = -I$(ROOT)/include -Wall -g
LFLAGS = -L$(ROOT)/lib

compile: compile.c
	gcc $(CFLAGS) $(LFLAGS) compile.c -o compile -lstree-a

.PHONY: clean
clean:
	rm compile