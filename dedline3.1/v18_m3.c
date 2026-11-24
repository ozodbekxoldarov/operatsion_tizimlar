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

char **satrlarni_oqi(const char *fayl_nomi, int *soni)
{
    FILE *fayl = fopen(fayl_nomi, "r");
    if (fayl == NULL) {
        perror(fayl_nomi);
        return NULL;
    }

    char **satrlar = NULL;
    int sigim = 0;
    int n = 0;
    char bufer[MAKS_UZUNLIK];

    while (fgets(bufer, sizeof(bufer), fayl) != NULL) {
        qator_oxirini_tozala(bufer);

        if (n == sigim) {
            int yangi_sigim = (sigim == 0) ? 4 : sigim * 2;
            char **vaqtincha = realloc(satrlar, yangi_sigim * sizeof(char *));
            if (vaqtincha == NULL) {
                perror("realloc");
                satrlarni_tozala(satrlar, n);
                fclose(fayl);
                return NULL;
            }
            satrlar = vaqtincha;
            sigim = yangi_sigim;
        }

        satrlar[n] = malloc(strlen(bufer) + 1);
        if (satrlar[n] == NULL) {
            perror("malloc");
            satrlarni_tozala(satrlar, n);
            fclose(fayl);
            return NULL;
        }
        strcpy(satrlar[n], bufer);
        n++;
    }

    fclose(fayl);
    *soni = n;
    return satrlar;
}

int teskari_yoz(const char *fayl_nomi, char **satrlar, int n)
{
    FILE *fayl = fopen(fayl_nomi, "w");
    if (fayl == NULL) {
        perror(fayl_nomi);
        return 1;
    }

    for (int i = n - 1; i >= 0; i--) {
        fprintf(fayl, "%s\n", satrlar[i]);
    }

    fclose(fayl);
    return 0;
}

int main(void)
{
    int n = 0;
    char **satrlar = satrlarni_oqi("input.txt", &n);
    if (satrlar == NULL) {
        printf("input.txt dan satr o'qilmadi.\n");
        return 1;
    }

    if (teskari_yoz("reversed_lines.txt", satrlar, n) != 0) {
        satrlarni_tozala(satrlar, n);
        return 1;
    }

    printf("%d ta satr teskari tartibda reversed_lines.txt ga yozildi.\n", n);

    satrlarni_tozala(satrlar, n);
    return 0;
}
