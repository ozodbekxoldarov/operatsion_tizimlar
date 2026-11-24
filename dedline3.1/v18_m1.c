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

char *ikki_martalash(const char *satr)
{
    size_t uzunlik = strlen(satr);
    char *natija = malloc(2 * uzunlik + 1);
    if (natija == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < uzunlik; i++) {
        natija[j++] = satr[i];
        natija[j++] = satr[i];
    }
    natija[j] = '\0';
    return natija;
}

int main(void)
{
    char satr[MAKS_UZUNLIK];

    printf("Satr kiriting: ");
    if (fgets(satr, sizeof(satr), stdin) == NULL) {
        printf("Satr o'qilmadi.\n");
        return 1;
    }
    qator_oxirini_tozala(satr);

    char *natija = ikki_martalash(satr);
    if (natija == NULL) {
        perror("malloc");
        return 1;
    }

    printf("Natija: %s\n", natija);

    free(natija);
    return 0;
}
