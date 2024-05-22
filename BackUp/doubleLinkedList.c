/*
    Program: doubleLinkedList.c
    Author: 2350081003/Muhamad Yusron Noval
    Kelas: A
    Deskripsi: Memasukan instruksi yang akan dieksekusi didalam fungsi dan prosedur
    Tanggal: 02/04/2024
*/
#include <stdio.h>
#include <stdlib.h>
#include "doubleLinkedList.h"

boolean ListEmpty(List L) {
    if(First(L) == Nil) {
        return true;
    } else {
        return false;
    }
}

void CreateList(List *L) {
    First(*L) = Nil;
}

address Alokasi(infoType X) {
    address NewNode = (ElmList *) malloc(sizeof(ElmList));

    Info(NewNode) = X;
    Next(NewNode) = Nil;
    Prev(NewNode) = Nil;

    return NewNode;
}

void Dealokasi(address P) {
    free(P);
}

address Search(List L, infoType X) {
    address Current;

    Current = First(L);
    while (Current != Nil) {
        if (Info(Current) == X) {
            return Current;
        }

        Current = Next(Current);
    }

    return Nil;
}

void AddFirst(List *L, infoType X) {
    address NewNode;

    NewNode = Alokasi(X);

    if(NewNode != Nil) {
        Info(NewNode) = X;
        Next(NewNode) = First(*L);
        First(*L) = Prev(NewNode);
        First(*L) = NewNode;
    }
}

void AddAfter(List *L, infoType X, infoType Elemen) {
    address newNode, current, after;
    boolean ketemu;

    newNode = Alokasi(X);

    current = First(*L);

    ketemu = false;
    while (Next(current) != Nil && !ketemu) {
        if (Info(current) == Elemen) {
            after = Next(current);
            Next(current) = newNode;

            Prev(newNode) = current;
            Next(newNode) = after;
            Prev(after) = newNode;

            ketemu = true;
        }

        current = Next(current);
    }

    if (Next(current) == Nil && Info(current) == Elemen) {
        AddLast(L, X);

        ketemu = true;
    } else if (ketemu == false) {
        printf("\nError: data tidak ditemukan\n");
    }
}

void AddLast(List *L, infoType X) {
    address NewNode, Current;

    NewNode = Alokasi(X);
    Current = First(*L);

    if (NewNode != Nil) {
        while (Next(Current) != Nil) {
            Current = Next(Current);
        }

        Next(Current) = NewNode;
        Prev(NewNode) = Current;
    }
}

void DelFirst(List *L, infoType *X) {
    address DelNode, Tmp;

    DelNode = First(*L);
    First(*L) = Next(First(*L));

    *X = Info(DelNode);
    Tmp = DelNode;
    Dealokasi(Tmp);

    Tmp = Nil;
    Prev(First(*L)) = Nil;
}

void DelAfter(List *L, infoType *X, infoType Position) {
    address delNode, current, after, before;
    int i;

    if (Position == 1) {
        DelFirst(L, X);
    } else if (Position == jumElm(*L)) {
        DelLast(L, X);
    } else if (Position < 1 || Position > jumElm(*L)) {
        printf("\nError: Elemen yang ingin anda hapus tidak ada di posisi tersebut\n");
        printf("Error: undefined index %d", Position);
    } else {
        i = 1;
        current = First(*L);

        while (i <= Position) {
            if (i == Position - 1) {
                before = current;
            }

            if (i == Position) {
                delNode = current;
                after = Next(delNode);
            }

            current = Next(current);
            i++;
        }

        Next(before) = after;
        Prev(after) = before;

        *X = Info(delNode);

        Prev(delNode) = Nil;
        Next(delNode) = Nil;

        Dealokasi(delNode);
    }
}

void DelLast(List *L, infoType *X) {
    address DelNode, tmp, tmp2;

    DelNode = First(*L);
    *X = Info(DelNode);
    tmp = (DelNode);

    while(Next(tmp) != Nil) {
        tmp = Next(tmp);
    }

    tmp2 = Prev(tmp);
    Next(tmp2) = Nil;
    Dealokasi(tmp);
}

void CetakList(List L) {
    address Current;

    Current = First(L);
    printf("Null");
    while (Current != Nil) {
        printf(" <- [%d] -> ", Info(Current));

        Current = Next(Current);
    }

    printf("Null");
}

int jumElm(List L) {
    address Current;
    int i;

    Current = First(L);

    i = 0;
    while (Current != Nil) {
        Current = Next(Current);
        i++;
    }

    return i;
}

void MainMenu(List *L) {
    int Choice;

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+\t\t\tMain Menu\t\t\t+\n");
    printf("+\t\t\t\t\t\t\t+\n");
    printf("+\t\t\t\t\t\t\t+\n");
    printf("+ Select number 1 for going to Insert Menu\t\t+\n");
    printf("+ Select number 2 for going to Search Menu\t\t+\n");
    printf("+ Select number 3 for going to Delete Menu\t\t+\n");
    printf("+ Select number 4 for display data\t\t\t+\n");
    printf("+ 5 for exit the program!\t\t\t\t+\n");
    printf("+\t\t\t\t\t\t\t+\n");
    printf("+\t\t\t\t\t\t\t+\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\n");
    printf("What is your choice: ");
    scanf("%d", &Choice);
    printf("\n");

    switch (Choice) {
        case 1:
            InsertMenu(L);
            break;
            
        case 2:
            SearchMenu(L);
            break;

        case 3:
            DeleteMenu(L);
            break;

        case 4:
            displayData(*L);
        case 5:
            break;
    }
}

void InsertMenu(List *L) {
    int Choice, N, Elemen;

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+\t\t\tInsert Menu\t\t\t+\n");
    printf("+\t\t\t\t\t\t\t+\n");
    printf("+\t\t\t\t\t\t\t+\n");
    printf("+ 1 for insert front\t\t\t\t\t+\n");
    printf("+ 2 for insert middle/after\t\t\t\t+\n");
    printf("+ 3 for insert back\t\t\t\t\t+\n");
    printf("+ 4 for back to the main menu\t\t\t\t+\n");
    printf("+\t\t\t\t\t\t\t+\n");
    printf("+\t\t\t\t\t\t\t+\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\n");
    printf("What is your choice: ");
    scanf("%d", &Choice);
    printf("\n");

    switch (Choice) {
        case 1:
            printf("\n=========Operator Add First=========\n");
            printf("Masukan elemen: ");
            scanf("%d", &N);

            while(N != 999) {
                AddFirst(L, N);
                printf("Masukan elemen: ");
                scanf("%d", &N);
            }

            InsertMenu(L);
            break;

        case 2:
            printf("\n\n=========Operator Add After=========\n");
            printf("Masukan elemen: ");
            scanf("%d", &N);

            CetakList(*L);
            printf("\n");
            printf("Ingin disisipkan pada elemen ke: ");
            scanf("%d", &Elemen);

            AddAfter(L, N, Elemen);

            InsertMenu(L);
            break;

        case 3:
            printf("\n\n=========Operator Add Last=========\n");
            printf("Masukan elemen: ");
            scanf("%d", &N);

            while(N != 999) {
                AddLast(L, N);
                printf("Masukan elemen: ");
                scanf("%d", &N);
            }

            InsertMenu(L);
            break;
        
        case 4:
            MainMenu(L);
            break;
    }
}

void SearchMenu(List *L) {
    address searchElm;
    int Choice, info;

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+\t\t\tSearch Menu\t\t\t+\n");
    printf("+\t\t\t\t\t\t\t+\n");
    printf("+\t\t\t\t\t\t\t+\n");
    printf("+ 1 for search elemen\t\t\t\t\t+\n");
    printf("+ 2 for back to the main menu\t\t\t\t+\n");
    printf("+\t\t\t\t\t\t\t+\n");
    printf("+\t\t\t\t\t\t\t+\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\n");
    printf("What is your choice: ");
    scanf("%d", &Choice);
    printf("\n");

    switch (Choice) {
        case 1:
            CetakList(*L);
            printf("\n\n=========Operator Search=========\n");
            printf("Masukan Elemen yang dicari: ");
            scanf("%d", &info);

            searchElm = Search(*L, info);
            if (searchElm != Nil) {
                printf("\nElemen %d ada didalam list\n\n", info);
            } else {
                printf("Elemen %d tidak ada di list\n\n", info);
            }

            SearchMenu(L);
            break;
        
        case 2:
            MainMenu(L);
            break;
    }
}

void DeleteMenu(List *L) {
    int Choice, tmp, Elemen;

    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+\t\t\tDelete Menu\t\t\t+\n");
    printf("+\t\t\t\t\t\t\t+\n");
    printf("+\t\t\t\t\t\t\t+\n");
    printf("+ 1 for delete front\t\t\t\t\t+\n");
    printf("+ 2 for delete middle/after\t\t\t\t+\n");
    printf("+ 3 for delete back\t\t\t\t\t+\n");
    printf("+ 4 for back to the main menu\t\t\t\t+\n");
    printf("+\t\t\t\t\t\t\t+\n");
    printf("+\t\t\t\t\t\t\t+\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\n");
    printf("What is your choice: ");
    scanf("%d", &Choice);
    printf("\n");

    switch (Choice) {
        case 1:
            DelFirst(L, &tmp);
            DeleteMenu(L);
            break;

        case 2:
            CetakList(*L);
            printf("\n");
            printf("Ingin dihapus pada elemen ke: ");
            scanf("%d", &Elemen);

            DelAfter(L, &tmp, Elemen);
            DeleteMenu(L);
            break;

        case 3:
            DelLast(L, &tmp);
            DeleteMenu(L);
            break;
        
        case 4:
            MainMenu(L);
            break;
    }
}

void displayData(List L) {
    CetakList(L);
    printf("\n\n");

    MainMenu(&L);
}