/*
    Program: mdoubleLinkedList.c
    Author: 2350081003/Muhamad Yusron Noval
    Kelas: A
    Deskripsi: Program utama yang menjalankan ketiga program sebelumnya
    Tanggal: 02/04/2024
*/
#include <stdio.h>
#include <stdlib.h>
#include "doubleLinkedList.c"

int main() {
    List node;

    CreateList(&node);

    printf("\n=========Operator Pengecekan apakah list kosong atau tidak=========\n");
    if(ListEmpty(node)) {
        printf("List masih kosong\n");
    } else {
        printf("List tidak kosong\n");
    }
    printf("\n\n");

    MainMenu(&node);

    return 0;
}