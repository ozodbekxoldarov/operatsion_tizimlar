#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *yigindi_top(const char *a, const char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int max_len = (len_a > len_b) ? len_a : len_b;

    char *buffer = malloc(max_len + 2);
    if (buffer == NULL) {
        printf("Xato: xotira ajratilmadi.\n");
        exit(1);
    }
    int i = len_a - 1;
    int j = len_b - 1;
    int carry = 0;
    int pos = max_len + 1;

    buffer[pos] = '\0';
    pos--;

    while (i >= 0 || j >= 0 || carry) {
        int raqam_a = (i >= 0) ? (a[i] - '0') : 0;
        int raqam_b = (j >= 0) ? (b[j] - '0') : 0;

        int yigindi = raqam_a + raqam_b + carry;
        carry = yigindi / 10;

        buffer[pos] = '0' + (yigindi % 10);
        pos--;
        i--;
        j--;
    }

    int natija_uzunlik = max_len + 1 - pos;
    memmove(buffer, buffer + pos + 1, natija_uzunlik);

    return buffer;
}

int main(void) {
    char a[200], b[200];

    printf("Birinchi sonni kiriting: ");
    if (scanf("%199s", a) != 1) {
        printf("Xato: son kiritilmadi.\n");
        return 1;
    }

    printf("Ikkinchi sonni kiriting: ");
    if (scanf("%199s", b) != 1) {
        printf("Xato: son kiritilmadi.\n");
        return 1;
    }

    char *natija = yigindi_top(a, b);

    printf("Yig'indi: %s\n", natija);

    free(natija);

    return 0;
}
