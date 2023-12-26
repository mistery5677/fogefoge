#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int numero(){

    int x = 2;

    printf("x = %d\n", x);
    return x;
}

void soma(){

    numero() + 1;

    printf("x = %d", numero()
    );
}

int main(){
    numero();

    soma();

}