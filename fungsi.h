#ifndef FUNGSI_H
#define FUNGSI_H

// todo : macros
#define SIZE_NIM 9
#define SIZE_NAME 25
#define SIZE_TTL 11
#define SIZE_GENDER 7
#define SIZE_IPK 4
#define SIZE_MENU_PRINT 7
#define SIZE_ALL 61
#define STRING char *

// todo : fungsi prototype
void print_menu();
void system_clear();
void program_judul();
void printline();
void awalan();
void the_time();
void minta_input(int *b);
bool validasi();

// todo : link together with main

// sebagai library tambahan di compile bareng fungsi.c fungsi.h

#endif
