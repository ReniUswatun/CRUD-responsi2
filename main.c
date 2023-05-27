/*Program ini tentang data mahasiswa CURD dan impor dan ekspor untuk tugas responsi PKP*/

/*Program menggunakan file bin dan impor ekspor mrnggunakan file txt*/

// Nama : Reni Uswatun Hasanah
// Nim : L0122136
// Kelas : D

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
#include <time.h>
#include <unistd.h>
#include "fungsi.h"

// todo : prototype pada main.c
void tambahdata();
void hapusdata();
void ubahdata();
void lihatdata();
void ekspordata();
void impordata();

// menjalankan fungsi dengan compile 2 file sekaligus

// todo : fungsi struct, enum dll
// struct
typedef struct data
{
    char name[SIZE_NAME];
    char nim[SIZE_NIM];
    char gender[SIZE_GENDER];
    char birth[SIZE_TTL];
    float ipk;
} mahasiswa;

// enum
enum choice
{
    NAMBAH = 1,
    HAPUS,
    UBAH,
    LIHAT,
    IMPOR,
    EKSPOR,
    KELUAR
};

// todo : initialize cfptr global
FILE *cfptr = NULL;

int main()
{
awal:
    // print menu menu
    system_clear();
    awalan();
    int x;
    minta_input(&x);
    switch (x)
    {
        // pemilihan menu-menu
    case NAMBAH:
        tambahdata();
        break;
    case HAPUS:
        hapusdata();
        break;
    case UBAH:
        ubahdata();
        break;
    case LIHAT:
        lihatdata();
        break;
    case IMPOR:
        impordata();
        break;
    case EKSPOR:
        ekspordata();
        break;
    case KELUAR:
        exit(0);
        break;
    default:
        goto awal;
        break;
    }
}

void tambahdata()
{
    // melakukan validasi lagi
    bool valid = validasi();
    if (valid == true)
    {
        system_clear();
        // todo : menambahkan data mahasiswa
        printf("  %*s\n", SIZE_NAME, "Masukkan data mahasiswa");
        char nama[SIZE_NAME];
        char nim[SIZE_NIM];
        char ttl[SIZE_TTL];
        char gender[SIZE_GENDER];
        float ipk;
        int opsi;
        printf("Nama             : ");
        scanf(" %[^\n]s", nama);
        printf("Nim              : ");
        scanf(" %[^\n]s", nim);
        printf("Ttl (dd-mm-yyyy) : ");
        scanf(" %[^\n]s", ttl);
    jenis_kel:
        puts("Jenis Kelamin\n1. Pria\n2. Wanita\n>> ");
        scanf("%d", &opsi);
        if (opsi == 1)
            strcpy(gender, "Pria");
        else if (opsi == 2)
            strcpy(gender, "Wanita");
        else
        {
            puts("inputan salah");
            goto jenis_kel;
        }
    ulang_ipk:
        printf("IPK              : ");
        scanf("%f", &ipk);
        if (ipk > 4.00 || ipk < 0.00)
        {
            puts("IPK tidak valid!");
            goto ulang_ipk;
        }
        // tampilkan data mahasiswa
        printline();
        puts("\t\t    Data Mahasiswa");
        printline();
        printf("| Nama            : %-*s|\n", (SIZE_ALL - 20), nama);
        printf("| Nim             : %-*s|\n", (SIZE_ALL - 20), nim);
        printf("| Ttl (dd-mm-yyyy): %-*s|\n", (SIZE_ALL - 20), ttl);
        printf("| Jenis Kelamin   : %-*s|\n", (SIZE_ALL - 20), gender);
        printf("| IPK             : %-*.2f|\n", (SIZE_ALL - 20), ipk);
        printline();
        puts("");
        bool temp = validasi();
        if (temp == true)
        {
            mahasiswa Mahasiswa;
            strcpy(Mahasiswa.name, nama);
            strcpy(Mahasiswa.nim, nim);
            strcpy(Mahasiswa.birth, ttl);
            strcpy(Mahasiswa.gender, gender);
            Mahasiswa.ipk = ipk;
            // todo : membuka data.bin dan mengcoppynya
            if ((cfptr = fopen("data.bin", "ab+")) == NULL)
                puts("File tidak dapat dibuka");
            else
            {
                fwrite(&Mahasiswa, sizeof(mahasiswa), 1, cfptr);
                fclose(cfptr);
            }
            system_clear();
            // todo : memberitahu bahwa data telah di tambahkan
            STRING judul = "Selamat data berhasil ditambahkan";
            int totaljudul = strlen(judul);
            int margin = (SIZE_ALL - totaljudul) / 2;
            printf("%*s%s\n", margin, "", judul);
            sleep(1);
            main();
        }
        else
            main();
    }
    else
        main();
}

void hapusdata()
{
    system_clear();
    // tempat nim yang akan di cari
    char nim[SIZE_NIM];
    // melakukan validasi
    bool temp = validasi();
    if (temp == true)
    {
        // pertama tama melakukan read binary agar tau dimana tempat nim itu berada
        if ((cfptr = fopen("data.bin", "rb+")) == NULL)
            puts("File tidak dapat ditemukan");
        else
        {
            mahasiswa Mahasiswa;
            printline();
            STRING judul = "Hapus Data Mahasiswa";
            int totaljudul = strlen(judul);
            int margin = (SIZE_ALL - totaljudul) / 2;
            printf("%*s%s\n", margin, "", judul);
            printline();
            // masukkan nim agar bisa mencari data mahasiswa
            puts("Menghapus data berdasarkan NIM");
            printf("Masukkan NIM >> ");
            scanf(" %[^\n]s", nim);
            // todo : mecari data dengan validasi
            // struct keberapa yang memiliki nim sama dengan di cari
            int validasi = -1;
            int hasilvalidasi = 0;
            while (fread(&Mahasiswa, sizeof(mahasiswa), 1, cfptr) == 1)
            {
                if (strcmp(Mahasiswa.nim, nim) == 0)
                {
                    validasi = hasilvalidasi;
                }
                hasilvalidasi++;
            }
            // hasil dari validasi untuk menghapus data yang telah di buat
            if (validasi == -1)

                puts("Nim tidak dapat ditemukan");
            else
            {
                // intialize kosong agar bisa menghapus/menimpa data sebelumnya dengan kosong ini
                mahasiswa Mahasiswahapus = {"", "", "", "", 0};
                fseek(cfptr, validasi * sizeof(mahasiswa), SEEK_SET);
                // di write binary
                if (fwrite(&Mahasiswahapus, sizeof(mahasiswa), 1, cfptr) == 1)
                {
                    printline();
                    puts("\t\tHapus Berhasil !");
                    printline();
                }
            }
            // agar ketika menulis kembali bisa mwnuju ke titik akhir
            fseek(cfptr, 0, SEEK_END);
            fclose(cfptr);
            sleep(1);
            main();
        }
    }
}

void ubahdata()
{
    // todo : initialize yang akan di pakai
    char nama[SIZE_NAME];
    char nim[SIZE_NIM];
    char ttl[SIZE_TTL];
    char gender[SIZE_GENDER];
    char tempNim[SIZE_NIM];
    float ipk;
    int opsi;
    system_clear();
    bool temp = validasi();
    if (temp == true)
    {
        // pointer file menuju awal file
        cfptr = fopen("data.bin", "rb+");
    ulang:
        system_clear();
        printline();
        STRING judul = "Ubah data mahasiswa";
        int totaljudul = strlen(judul);
        int margin = (SIZE_ALL - totaljudul) / 2;
        printf("%*s%s\n", margin, "", judul);
        printline();

        puts("Ubah data mahasiswa akan berdasarkan NIM");
        puts("Masukkan NIM yang akan dirubah ");
        printf("NIM >> ");
        scanf(" %[^\n]", tempNim);

        // todo : Cari struct keberapa berdasrkan NIM
        int valid = -1;
        int hasilvalid = 0;
        mahasiswa CariMahasiswa;
        mahasiswa Hasilcari;
        while ((fread(&CariMahasiswa, sizeof(mahasiswa), 1, cfptr)) == 1)
        {
            if (strcmp(CariMahasiswa.nim, tempNim) == 0)
            {
                valid = hasilvalid;
                break;
            }
            hasilvalid++;
        }
        // hasilnya akan jadi struct keberapa
        if (valid == -1)
        {
            puts("Nim tidak dapat ditemukan");
            sleep(1);
            goto ulang;
        }
        else
        {
            // todo : konfirmasi data yang ingin dihapus
            puts("Data mahasiswa yang akan dihapus ");
            printline();
            printf("| Nama            : %-*s|\n", (SIZE_ALL - 20), CariMahasiswa.name);
            printf("| Nim             : %-*s|\n", (SIZE_ALL - 20), CariMahasiswa.nim);
            printf("| Ttl (dd-mm-yyyy): %-*s|\n", (SIZE_ALL - 20), CariMahasiswa.birth);
            printf("| Jenis Kelamin   : %-*s|\n", (SIZE_ALL - 20), CariMahasiswa.gender);
            printf("| IPK             : %-*.2f|\n", (SIZE_ALL - 20), CariMahasiswa.ipk);
            printline();
            bool temp2 = validasi();
            if (temp2 == true)
            {
                // masukkan data yang ingin di ubah
                system_clear();
                fseek(cfptr, sizeof(mahasiswa) * valid, SEEK_SET);
                puts("Masukkan Nama");
                printf("Nama             : ");
                scanf(" %[^\n]s", nama);
                printf("Nim              : ");
                scanf(" %[^\n]s", nim);
                printf("Ttl (dd-mm-yyyy) : ");
                scanf(" %[^\n]s", ttl);
            jenis_kel:
                puts("Jenis Kelamin\n1. Pria\n2. Wanita\n>> ");
                scanf("%d", &opsi);
                if (opsi == 1)
                    strcpy(gender, "Pria");
                else if (opsi == 2)
                    strcpy(gender, "Wanita");
                else
                {
                    puts("inputan salah");
                    goto jenis_kel;
                }
            ulang_ipk:
                printf("IPK              : ");
                scanf("%f", &ipk);
                if (ipk > 4.00 || ipk < 0.00)
                {
                    puts("IPK tidak valid!");
                    goto ulang_ipk;
                }

                printline();
                puts("\t\t  Data Mahasiswa Baru");
                // memastikan data sudah benar atau belom
                printline();

                printf("| Nama            : %-*s|\n", (SIZE_ALL - 20), nama);
                printf("| Nim             : %-*s|\n", (SIZE_ALL - 20), nim);
                printf("| Ttl (dd-mm-yyyy): %-*s|\n", (SIZE_ALL - 20), ttl);
                printf("| Jenis Kelamin   : %-*s|\n", (SIZE_ALL - 20), gender);
                printf("| IPK             : %-*.2f|\n", (SIZE_ALL - 20), ipk);
                printline();
                puts("");

                mahasiswa MahasiswaBaru;
                strcpy(MahasiswaBaru.name, nama);
                strcpy(MahasiswaBaru.nim, nim);
                strcpy(MahasiswaBaru.birth, ttl);
                strcpy(MahasiswaBaru.gender, gender);
                MahasiswaBaru.ipk = ipk;
                // tulis kedalam file
                if (fwrite(&MahasiswaBaru, sizeof(mahasiswa), 1, cfptr) == 1)
                {
                    puts("\t\t\tUbah data berhasil ");
                    fclose(cfptr);
                    sleep(3);
                    main();
                }
            }
            else
                main();
        }
    }
    else
        main();
}

void lihatdata()
{
    // melakukan validasi
    bool temp = validasi();
    int jumlahdata;
    if (temp == true)
    {
        // membuka data binarry
        if ((cfptr = fopen("data.bin", "rb")) == NULL)
            puts("File tidak dapat ditemukan");
        else
        {
            system_clear();
            printline();
            printf("|%*s%*s|\n", (SIZE_ALL - 20), "Program Data Mahasiswa", 19, "");
            printline();
            printf("|%-*s|%-*s|%-*s|%-*s|%-*s|\n", SIZE_NIM, "NIM", SIZE_NAME, "Nama", SIZE_TTL, "TTL", SIZE_GENDER, "Gender", SIZE_IPK, "IPK");
            printline();
            int mhs = 0;
            mahasiswa BacaMahasiswa;
            // memastikan nim telah di isi
            while (fread(&BacaMahasiswa, sizeof(mahasiswa), 1, cfptr) == 1)
            {
                if (strlen(BacaMahasiswa.nim) > 0)
                {
                    printf("|%-*s|%-*s|%-*s|%-*s|%-*.2f|\n", SIZE_NIM, BacaMahasiswa.nim,
                           SIZE_NAME, BacaMahasiswa.name, SIZE_TTL, BacaMahasiswa.birth,
                           SIZE_GENDER, BacaMahasiswa.gender, SIZE_IPK,
                           BacaMahasiswa.ipk);
                    mhs++;
                }
            }
            // print data keberapa pada data bin
            printline();
            printf("|%-*s%d|\n", SIZE_ALL - 2,
                   "Total Mahasiswa yang dimasukkan : ", (mhs));
            printline();
            puts("Data akan ditampilkan selama 3 detik dan akan menuju ke main menu");
            fseek(cfptr, 0, SEEK_END);
            fclose(cfptr);
            sleep(3);
            main();
        }
        main();
    }
    else
        main();
}

void ekspordata()
{
    //
    mahasiswa Mahasiswa;
    cfptr = fopen("data.bin", "rb");
    FILE *eksptr;
    if ((eksptr = fopen("Export.txt", "w")) == NULL)
    {
        printf("Data tidak berhasil dibuka");
        sleep(1);
        main();
    }
    else
    {

        fprintf(eksptr, "=============================================================\n");
        fprintf(eksptr, "|%-*s|%-*s|%-*s|%-*s|%-*s|\n", SIZE_NIM, "NIM", SIZE_NAME, "Nama", SIZE_TTL, "TTL", SIZE_GENDER, "Gender", SIZE_IPK, "IPK");
        fprintf(eksptr, "=============================================================\n");
        while ((fread(&Mahasiswa, sizeof(mahasiswa), 1, cfptr)) == 1)
        {

            fprintf(eksptr, "|%-*s|%-*s|%-*s|%-*s|%-*.2f|\n", SIZE_NIM, Mahasiswa.nim,
                    SIZE_NAME, Mahasiswa.name, SIZE_TTL, Mahasiswa.birth,
                    SIZE_GENDER, Mahasiswa.gender, SIZE_IPK,
                    Mahasiswa.ipk);
        }
        fprintf(eksptr, "=============================================================\n");
        system_clear();
        puts("Data berhasil di ekspor");
        sleep(1);
        fclose(cfptr);
        fclose(eksptr);
        main();
    }
}

void impordata()
{
    // intialize data yang akan dipakai
    char nama[SIZE_NAME];
    char nim[SIZE_NIM];
    char ttl[SIZE_TTL];
    char gender[SIZE_GENDER];
    char tempNim[SIZE_NIM];
    float ipk;
    mahasiswa TempMahasiswa;
    // membuka data.bin agar bisa dimasukkan kedalamnya
    cfptr = fopen("data.bin", "ab+");
    // buka txt untuk masuk ke bin
    FILE *impptr;
    if ((impptr = fopen("Import.txt", "r")) == NULL)
    {
        printf("Data tidak berhasil dibuka");
        sleep(1);
        main();
    }
    else
    {
        puts("ok");
        while (fscanf(impptr, "%[^;];%[^;];%[^;];%[^;];%f\n", nama, nim, ttl, gender, &ipk) != EOF)
        {
            strcpy(TempMahasiswa.name, nama);
            strcpy(TempMahasiswa.nim, nim);
            strcpy(TempMahasiswa.birth, ttl);
            strcpy(TempMahasiswa.gender, gender);
            TempMahasiswa.ipk = ipk;
            // masukkan kedalam cfptr
            fwrite(&TempMahasiswa, sizeof(mahasiswa), 1, cfptr);
        }
    }
    fclose(cfptr);
    fclose(impptr);
    printf("\t\tData berhasil ditambahkan\n");
    sleep(2);
    main();
}
