all: prog.exe
prog.exe: main.o f.o
	gcc -o prog.exe main.o f.o -lm
f.o: f.asm
	nasm -fwin32 -o f.o f.asm
main.o: main.c
	gcc main.c -o main.o -c
clean: 
	del prog.exe main.o f.o
.PHONY: clean all