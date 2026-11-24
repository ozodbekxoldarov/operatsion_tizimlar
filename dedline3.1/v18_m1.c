#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

void remove_newline(char *s)
{
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
    }
}

char *double_chars(const char *s)
{
    size_t len = strlen(s);
    char *result = malloc(2 * len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        result[j++] = s[i];
        result[j++] = s[i];
    }
    result[j] = '\0';
    return result;
}

int main(void)
{
    char s[MAX_LEN];

    printf("Satr kiriting: ");
    if (fgets(s, sizeof(s), stdin) == NULL) {
        printf("Satr o'qilmadi.\n");
        return 1;
    }
    remove_newline(s);

    char *result = double_chars(s);
    if (result == NULL) {
        perror("malloc");
        return 1;
    }

    printf("Natija: %s\n", result);

    free(result);
    return 0;
}
