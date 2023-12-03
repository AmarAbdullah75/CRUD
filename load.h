#include <stdio.h>
#include <windows.h>


#ifndef CRUD_LOAD_H
#define CRUD_LOAD_H

void loading(){
    printf("Loading");
    for (int i = 0; i < 10; ++i) {
        printf(".");
        Sleep(500);
    }
}
#endif //CRUD_LOAD_H
