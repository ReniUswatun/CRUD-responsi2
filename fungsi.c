#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
#include <time.h>
#include "fungsi.h"

// todo : link together with main
// fungsi fungsi disini digunakan untuk menjabarkan fungsi prototype di fungsi.h

// todo : fungsi struct, enum dll
// struct
// typedef struct data
// {
//     char name[SIZE_NAME];
//     char nim[SIZE_NIM];
//     char gender[SIZE_GENDER];
//     char birth[SIZE_TTL];
//     float ipk;
// } mahasiswa;

// mahasiswa *Mahasiswa;

// // enum
// enum choice
// {
//     NAMBAH = 1,
//     HAPUS,
//     UBAH,
//     LIHAT,
//     IMPOR,
//     EKSPOR,
//     KELUAR
// };

void print_menu()
{
    const STRING menu[SIZE_MENU_PRINT] = {"Menambahkan data mahasiswa", "Menghapus data mahasiswa", "Mengubah data mahasiswa", "Lihat data mahasiswa", "Impor data mahasiswa", "Ekspor data mahasiswa", "Keluar program"};
    for (int a = 0; a < SIZE_MENU_PRINT; a++)
    {
        printf("| %d. %-*s|\n", (a + 1), SIZE_ALL - 5, menu[a]);
    }
    printline();
}

void system_clear()
{
    if (system("cls"))
        system("clear");
}

void program_judul()
{
    printline();
    printf("|%*s%*s|\n", (SIZE_ALL - 20), "Program Data Mahasiswa", 19, "");
    printline();
    the_time();
}

void printline()
{
    for (int a = SIZE_ALL; a > 0; a--)
    {
        printf("=");
    }
    puts("");
}

void minta_input(int *b)
{
    puts("Masukkan pilihan yang akan di jalankan");
    printf(">> ");
    scanf("%d", b);
}

void awalan()
{
    program_judul();
    print_menu();
}

void the_time()
{
    time_t biggest = time(NULL);

    printf("%s", ctime(&biggest));
    printline();
}

bool validasi()
{
    puts("Apakah anda yakin melanjutkan operasi ini ? (y/n) ");
    printf(">> ");
    char a;
    scanf(" %c", &a);
    if (a == 'y' || a == 'Y')
        return true;
    else if (a == 'n' || a == 'N')
        return false;
    else
        return false;
}
