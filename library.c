//
// Created by andre on 04/12/2023.
//
// Given function by Arturo, that provides time
#include "library.h"

#include <stdio.h>
#include<time.h>

void Get_time(int *hour,int *min){
    struct tm *h;
    time_t hor;
    hor=time(NULL);
    h= localtime(&hor);
    *hour=h->tm_hour;
    *min=h->tm_min;
}