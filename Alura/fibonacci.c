#include <stdio.h>

int counter = 0;

int fib(int n) {
    
    if(n == 0) return 0;
    if(n == 1) return 1;
    printf("contador: %d ", counter);
    printf("numero: %d\n", n);
        
    counter++;
    return fib(n-1) + fib(n-2);
}

int main() {

    printf("numero final: %d\n", fib(6));
}