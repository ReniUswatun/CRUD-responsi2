# -*- MakeFile -*-
# todo : Automating builds with Makefile
#*Gunakan kata "make" pada terminal dan rename path_ke_folder_mingw-7.3.0/bin/mingw32-make.exe menjadi make.exe
# *penting agar dapat menjalankan Makefile


all: compile run

compile:
	gcc -o main main.c fungsi.c

clear:
	rm -f main
	rm -f *.o

run:
	./main.exe
