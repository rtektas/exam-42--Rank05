#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

typedef struct s_map {
    int h;
    size_t w;
    char c[3];
    char **rows;
} Map;

int chars(char *s, char *c, int n)
{
    if (n == 3) {
        while (*s == ' ' || *s == '\t') s++;
        return (*s == '\n' && !s[1]);
    }
    while (*s == ' ' || *s == '\t') {
        s++;
        if (*s >= 32 && *s <= 126) {
            c[n] = *s;
            if (chars(s + 1, c, n + 1)) return (1);
        }
    }
    return (0);
}

int read_map(FILE *f, Map *m)
{
    char *line = NULL, *p;
    size_t cap = 0;
    ssize_t len = getline(&line, &cap, f);
    int ok = 0;

    if (len < 0) goto end;
    p = line;
    if (*p < '0' || *p > '9') goto end;
    while (*p >= '0' && *p <= '9') {
        if (m->h > (INT_MAX - (*p - '0')) / 10) goto end;
        m->h = m->h * 10 + *p++ - '0';
    }
    if (!m->h || !chars(p, m->c, 0)
        || m->c[0] == m->c[1] || m->c[0] == m->c[2]
        || m->c[1] == m->c[2]) goto end;
    m->rows = calloc(m->h, sizeof(char *));
    if (!m->rows) goto end;
    for (int i = 0; i < m->h; i++) {
        len = getline(&line, &cap, f);
        if (len < 2 || line[len - 1] != '\n') goto end;
        if (!i) m->w = (size_t)len - 1;
        if ((size_t)len - 1 != m->w) goto end;
        for (size_t j = 0; j < m->w; j++)
            if (line[j] != m->c[0] && line[j] != m->c[1]) goto end;
        m->rows[i] = line;
        line = NULL;
        cap = 0;
    }

    errno = 0;
    ok = (getline(&line, &cap, f) == -1 && !errno);
end:
    free(line);
    return (ok);
}

size_t min3(size_t a, size_t b, size_t c)
{
    if (b < a) a = b;
    if (c < a) a = c;
    return (a);
}

int solve(Map *m)
{
    size_t *dp = calloc(m->w + 1, sizeof(size_t));
    size_t best = 0, bx = 0;
    int by = 0;

    if (!dp) return (0);
    for (int y = 0; y < m->h; y++) {
        size_t diagonal = 0;
        for (size_t x = 0; x < m->w; x++) {
            size_t above = dp[x + 1];
            dp[x + 1] = 0;
            if (m->rows[y][x] == m->c[0])
                dp[x + 1] = min3(above, dp[x], diagonal) + 1;
            diagonal = above;
            if (dp[x + 1] > best) {
                best = dp[x + 1];
                by = y;
                bx = x;
            }
        }
    }
    for (size_t y = 0; y < best; y++)
        for (size_t x = 0; x < best; x++)
            m->rows[by - y][bx - x] = m->c[2];
    free(dp);
    return (1);
}

void process(char *name, int separator)
{
    FILE *f = name ? fopen(name, "r") : stdin;
    Map m = {0};
    int ok = 0;

    if (f) {
        errno = 0;
        ok = read_map(f, &m) && solve(&m);
        if (name) fclose(f);
    }
    if (!ok) fprintf(stderr, "map error\n");
    else
        for (int i = 0; i < m.h; i++) fputs(m.rows[i], stdout);
    if (separator) fputs("\n", ok ? stdout : stderr);
    if (m.rows)
        for (int i = 0; i < m.h; i++) free(m.rows[i]);
    free(m.rows);
}

int main(int argc, char **argv)
{
    if (argc == 1) process(NULL, 0);
    for (int i = 1; i < argc; i++) process(argv[i], argc > 2);
    return (0);
}
