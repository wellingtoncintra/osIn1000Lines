#include "common.h"



// Tarefa 2
void *memset(void *buf, char c, size_t n) {
    uint8_t *p = (uint8_t *) buf;
    while (n--)
        *p++ = c;
    return buf;
}

void *memcpy(void *dst, const void *src, size_t n) {
    uint8_t *d = (uint8_t *) dst;
    const uint8_t *s = (const uint8_t *) src;
    while (n--)
        *d++ = *s++;
    return dst;
}

// Tarefa 3
char *strcpy(char *dst, const char *src) {
    char *d = dst;
    while (*src)
        *d++ = *src++;
    *d = '\0';
    return dst;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2)
            break;
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

// Tarefa 4
void printf(const char *fmt, ...) {
    va_list vargs;
    va_start(vargs, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++; // Pula o '%'
            switch (*fmt) {
                case '\0':
                    putchar('%');
                    goto end;
                case '%':
                    putchar('%');
                    break;
                case 's': {
                    const char *s = va_arg(vargs, const char *);
                    while (*s) {
                        putchar(*s);
                        s++;
                    }
                    break;
                }
                case 'd': {
                    int value = va_arg(vargs, int);
                    if (value < 0) {
                        putchar('-');
                        value = -value;
                    }
                    if (value == 0) {
                        putchar('0');
                    } else {
                        char buf[12];
                        int i = 0;
                        while (value > 0) {
                            buf[i++] = (value % 10) + '0';
                            value /= 10;
                        }
                        while (i > 0) {
                            putchar(buf[--i]);
                        }
                    }
                    break;
                }
                case 'x': {
                    unsigned int value = va_arg(vargs, unsigned int);
                    if (value == 0) {
                        putchar('0');
                    } else {
                        char buf[9];
                        int i = 0;
                        while (value > 0) {
                            unsigned int rem = value % 16;
                            if (rem < 10)
                                buf[i++] = rem + '0';
                            else
                                buf[i++] = (rem - 10) + 'a';
                            value /= 16;
                        }
                        while (i > 0) {
                            putchar(buf[--i]);
                        }
                    }
                    break;
                }
            }
        } else {
            putchar(*fmt);
        }
        fmt++;
    }

end:
    va_end(vargs);
}