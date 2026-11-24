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

void free_lines(char **lines, int n)
{
    for (int i = 0; i < n; i++) {
        free(lines[i]);
    }
    free(lines);
}

int find_longest(char **lines, int n)
{
    int best = 0;
    for (int i = 1; i < n; i++) {
        if (strlen(lines[i]) > strlen(lines[best])) {
            best = i;
        }
    }
    return best;
}

int main(void)
{
    char buf[MAX_LEN];
    int n;

    printf("Satrlar sonini kiriting (N): ");
    if (fgets(buf, sizeof(buf), stdin) == NULL || sscanf(buf, "%d", &n) != 1 || n <= 0) {
        printf("N noto'g'ri kiritildi.\n");
        return 1;
    }

    char **lines = malloc(n * sizeof(char *));
    if (lines == NULL) {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("%d-satr: ", i + 1);
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            buf[0] = '\0';
        }
        remove_newline(buf);

        lines[i] = malloc(strlen(buf) + 1);
        if (lines[i] == NULL) {
            perror("malloc");
            free_lines(lines, i);
            return 1;
        }
        strcpy(lines[i], buf);
    }

    int idx = find_longest(lines, n);
    printf("Eng uzun satr (%d-satr, %zu belgi): %s\n",
           idx + 1, strlen(lines[idx]), lines[idx]);

    free_lines(lines, n);
    return 0;
}
