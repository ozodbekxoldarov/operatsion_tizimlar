#include <stdio.h>

int main(void) {
    double a, b, natija;
    char amal;
    while (1) {
        printf("Birinchi sonni kiriting (yoki q - chiqish): ");
        if (scanf("%lf", &a) != 1) {
            printf("Chiqish.\n");
            break;
        }
        printf("Amalni kiriting (+ - * / %%): ");
        scanf(" %c", &amal);
        printf("Ikkinchi sonni kiriting: ");
        scanf("%lf", &b);
        switch (amal) {
            case '+':
                natija = a + b;
                printf("Natija: %.2f\n", natija);
                break;
            case '-':
                natija = a - b;
                printf("Natija: %.2f\n", natija);
                break;
            case '*':
                natija = a * b;
                printf("Natija: %.2f\n", natija);
                break;
            case '/':
                if (b == 0) {
                    printf("Xato: nolga bo'lish mumkin emas.\n");
                } else {
                    natija = a / b;
                    printf("Natija: %.2f\n", natija);
                }
                break;
            default:
                printf("Noma'lum amal.\n");
        }
    }
    return 0;
}
