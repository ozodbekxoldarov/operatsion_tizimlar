#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAKS_UZUNLIK 256

void qator_oxirini_tozala(char *satr)
{
    size_t uzunlik = strlen(satr);
    if (uzunlik > 0 && satr[uzunlik - 1] == '\n') {
        satr[uzunlik - 1] = '\0';
    }
}

void satrlarni_tozala(char **satrlar, int n)
{
    for (int i = 0; i < n; i++) {
        free(satrlar[i]);
    }
    free(satrlar);
}

int eng_uzunini_top(char **satrlar, int n)
{
    int eng_uzun = 0;
    for (int i = 1; i < n; i++) {
        if (strlen(satrlar[i]) > strlen(satrlar[eng_uzun])) {
            eng_uzun = i;
        }
    }
    return eng_uzun;
}

int main(void)
{
    char bufer[MAKS_UZUNLIK];
    int n;

    printf("Satrlar sonini kiriting (N): ");
    if (fgets(bufer, sizeof(bufer), stdin) == NULL || sscanf(bufer, "%d", &n) != 1 || n <= 0) {
        printf("N noto'g'ri kiritildi.\n");
        return 1;
    }

    char **satrlar = malloc(n * sizeof(char *));
    if (satrlar == NULL) {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("%d-satr: ", i + 1);
        if (fgets(bufer, sizeof(bufer), stdin) == NULL) {
            bufer[0] = '\0';
        }
        qator_oxirini_tozala(bufer);

        satrlar[i] = malloc(strlen(bufer) + 1);
        if (satrlar[i] == NULL) {
            perror("malloc");
            satrlarni_tozala(satrlar, i);
            return 1;
        }
        strcpy(satrlar[i], bufer);
    }

    int indeks = eng_uzunini_top(satrlar, n);
    printf("Eng uzun satr (%d-satr, %zu belgi): %s\n",
           indeks + 1, strlen(satrlar[indeks]), satrlar[indeks]);

    satrlarni_tozala(satrlar, n);
    return 0;
}
