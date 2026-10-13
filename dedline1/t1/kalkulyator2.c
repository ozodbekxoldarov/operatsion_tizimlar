#include <stdio.h>
#include <math.h>
double qosh(double a, double b) {
    return a + b;
}
double ayir(double a, double b) {
    return a- b;
}
double kopaytir(double a, double b) {
    return a *b;
}

double bol(double a, double b) {
    return a/b;
}

double qoldiq(double a, double b) {
    return fmod(a, b);
}

int main(void) {
    double a, b, natija;
    char belgi;
    double (*amal)(double, double);

    while (1) {
        printf("birinchi sonni kiriting (yoki q - chiqish): ");
        if (scanf("%lf", &a) != 1) {
            printf("Chiqish.\n");
            break;
        }
        printf("Amalni kiriting (+ - * / %%): ");
        scanf(" %c", &belgi);

        printf("Ikkinchi sonni kiriting: ");
        scanf("%lf", &b);

        amal = NULL;

        switch (belgi) {
            case '+': amal = qosh; break;
            case '-': amal = ayir; break;
            case '*': amal = kopaytir; break;
            case '/':
                if (b == 0) {
                    printf("Xato: nolga bo'lish mumkin emas.\n");
                    continue;
                }
                amal = bol;
                break;
            case '%':
                if (b == 0) {
                    printf("Xato: nolga bo'lish mumkin emas.\n");
                    continue;
                }
                amal = qoldiq;
                break;
            default:
                printf("Noma'lum amal.\n");
                continue;
        }
        natija = amal(a, b);
        printf("Natija: %.2f  (amal manzili: %p)\n", natija, (void *)amal);
    }
    return 0;
}
