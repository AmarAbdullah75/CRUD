#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "load.h"

typedef struct {
    int id;
    char name[25];
    float grade;
} RekMhs;

//GLOBAL VARIABEL
RekMhs DataMhs;
FILE *master;
FILE *temp;
int status = 0;

void create(){
    system("cls");
//  BUKA FILE
    master = fopen("StudentFile.dat", "ab");
//  MENAMBAHKAN DATA BARU KE DALAM FILE
    printf("Input Student ID : ");scanf("%d", &DataMhs.id);
    while(DataMhs.id != 9999){
        printf("Name : ");scanf(" %[^\n]%*c", DataMhs.name);
        printf("Grade : ");scanf("%f", &DataMhs.grade);
        fwrite(&DataMhs, sizeof(DataMhs), 1, master);
        printf("Input Student ID : ");scanf("%d", &DataMhs.id);
    }
//  TUTUP FILE
    fclose(master);
}

void read(){
    system("cls");
//    loading();
    system("cls");
//  BUKA FILE
    master = fopen("StudentFile.dat", "rb");\
    printf("\n-------------------------------------------------\n");
    printf("|             Table Seluruh Mahasiswa           |");
    printf("\n-------------------------------------------------");
    printf("\n|\tID\t|\tNama\t|\tGrade\t|");
    printf("\n-------------------------------------------------");
//  MEMBACA DATA DARI FILE master
    while(fread(&DataMhs, sizeof(DataMhs), 1, master)==1){
//  CETAK KE CONSOLE
        printf("\n|\t%d\t|\t%s\t|\t%.2f\t|", DataMhs.id, DataMhs.name, DataMhs.grade);
        printf("\n-------------------------------------------------");
    }
//  TUTUP FILE
    fclose(master);
}

void update(){
    system("cls");
    int idcari, idbaru;

    master = fopen("StudentFile.dat", "rb");
    temp = fopen("StudentFilechange.dat", "wb");
    printf("Cari id : ");scanf("%d", &idcari);
    while (fread(&DataMhs, sizeof(DataMhs), 1, master)==1) {
        if (DataMhs.id != idcari) {
            fwrite(&DataMhs, sizeof(DataMhs), 1, temp);
        } else {
            status = 1;
        }
    }
    fclose(master);
    fclose(temp);

    if (status) {
        printf("\n-------------------------------------------------\n");
        printf("|                  Table Mahasiswa              |");
        printf("\n-------------------------------------------------\n");
        printf("|\tID\t|\tNama\t|\tGrade\t|\n");
        printf("-------------------------------------------------\n");
        master = fopen("StudentFile.dat", "rb");
        temp = fopen("StudentFilechange.dat", "wb");
            while(fread(&DataMhs, sizeof(DataMhs), 1, master)==1){
                if(DataMhs.id == idcari){
                    printf("|\t%d\t|\t%s\t|\t%.2f\t|", DataMhs.id, DataMhs.name, DataMhs.grade);
                    printf("\n-------------------------------------------------\n");
                    printf("\n\nMasukan id baru = ");scanf("%d", &idbaru);
                    DataMhs.id = idbaru;
                }
                fwrite(&DataMhs, sizeof(DataMhs), 1, temp);
            }
        fclose(master);
        fclose(temp);
    } else {
        temp = fopen("StudentFilechange.dat", "rb");
        master = fopen("StudentFile.dat", "wb");
        while (fread(&DataMhs, sizeof(DataMhs), 1, temp)==1) {
            fwrite(&DataMhs, sizeof(DataMhs), 1, master);
        }
        fclose(master);
        fclose(temp);
        printf("ID tidak ditemukan!!!");
    }

    temp = fopen("StudentFilechange.dat", "rb");
    master = fopen("StudentFile.dat", "wb");
    while (fread(&DataMhs, sizeof(DataMhs), 1, temp)==1) {
        fwrite(&DataMhs, sizeof(DataMhs), 1, master);
    }
    fclose(master);
    fclose(temp);
}

void delete(){
    system("cls");
    int deleteID;
//  BUKA FILE
    master = fopen("StudentFile.dat", "rb");
    temp = fopen("StudentFilechange.dat", "wb");
//  CARI ID DATA YG INGIN DIHAPUS
    printf("ID dengan data yg ingin di hapus : ");scanf("%d", &deleteID);
    //  MEMBACA DATA DARI FILE master
    while(fread(&DataMhs, sizeof(DataMhs), 1, master)==1){
        if(DataMhs.id != deleteID){//  JIKA ID YG DICARI TIDAK SAMA DENGAN ID DIDALAM FILE master, MAKA SALIN KEDALAM FILE temp
            fwrite(&DataMhs, sizeof(DataMhs), 1, temp);
        }else{
            status = 1;
        }
    }
    if(!status){
        printf("ID tidak ditemukan!!!");
    }
//  TUTUP FILE
    fclose(master);
    fclose(temp);

//  BUKA FILE
    master = fopen("StudentFile.dat", "wb");
    temp = fopen("StudentFilechange.dat", "rb");

//  MEMBACA DATA DARI FILE temp, KEMUDIAN SALIN KEDALAM FILE master
    while(fread(&DataMhs, sizeof(DataMhs), 1, temp)==1){
        fwrite(&DataMhs, sizeof(DataMhs), 1, master);
    }
//  TUTUP FILE
    fclose(master);
    fclose(temp);
}

void main() {
    char pilihan;
    int menu;
    do {
        system("cls");
        printf("[1]. Tambah\n[2]. Lihat\n[3]. Update\n[4]. Hapus\n[0]. Exit");
        printf("\nMenu : ");scanf("%d", &menu);
        switch (menu) {
            case 1:
                create();
                break;
            case 2:
                read();
                break;
            case 3:
                update();
                break;
            case 4:
                delete();
                break;
            case 5:
                printf("EXIT");
                break;
            default:
                printf("404 NOT FOUND");
        }
        printf("\n<< Lanjut = 1, Exit = 0 >>");
        printf("\n\nLanjut : ");scanf("%s", &pilihan);
    }while(pilihan == '1'); //  PERULANGAN AKAN BERHENTI KETIKA USER MENEKAN SELAIN 1
    getch();
}