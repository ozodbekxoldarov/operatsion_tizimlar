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

char **read_lines(const char *filename, int *count)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror(filename);
        return NULL;
    }

    char **lines = NULL;
    int capacity = 0;
    int n = 0;
    char buf[MAX_LEN];

    while (fgets(buf, sizeof(buf), f) != NULL) {
        remove_newline(buf);

        if (n == capacity) {
            int new_cap = (capacity == 0) ? 4 : capacity * 2;
            char **tmp = realloc(lines, new_cap * sizeof(char *));
            if (tmp == NULL) {
                perror("realloc");
                free_lines(lines, n);
                fclose(f);
                return NULL;
            }
            lines = tmp;
            capacity = new_cap;
        }

        lines[n] = malloc(strlen(buf) + 1);
        if (lines[n] == NULL) {
            perror("malloc");
            free_lines(lines, n);
            fclose(f);
            return NULL;
        }
        strcpy(lines[n], buf);
        n++;
    }

    fclose(f);
    *count = n;
    return lines;
}

int write_reversed(const char *filename, char **lines, int n)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        perror(filename);
        return 1;
    }

    for (int i = n - 1; i >= 0; i--) {
        fprintf(f, "%s\n", lines[i]);
    }

    fclose(f);
    return 0;
}

int main(void)
{
    int n = 0;
    char **lines = read_lines("input.txt", &n);
    if (lines == NULL) {
        printf("input.txt dan satr o'qilmadi.\n");
        return 1;
    }

    if (write_reversed("reversed_lines.txt", lines, n) != 0) {
        free_lines(lines, n);
        return 1;
    }

    printf("%d ta satr teskari tartibda reversed_lines.txt ga yozildi.\n", n);

    free_lines(lines, n);
    return 0;
}
