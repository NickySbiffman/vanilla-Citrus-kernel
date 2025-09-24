#include <citrus/string.h>
#include <stddef.h>
#include <stdint.h>

void *memcpy(void *dest, const void *src, size_t n)
{
    char *d = dest;
    const char *s = src;
    while (n--) *d++ = *s++;
    return dest;
}

void memset(void *s, int c, size_t n)
{
    char *p = s;
    while (n--)
        *p++ = c;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
    const char *p1 = s1;
    const char *p2 = s2;
    while (n--)
        if (*p1++ != *p2++) return *p1 - *p2;
    return 0;
}

int toupper(int c)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 'A';
    return c;
}

int strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

char* itoa(int num) {
    static char buf[12];
    int i = 10;
    int is_negative = 0;
    buf[11] = '\0';

    if (num == 0) {
        buf[10] = '0';
        return &buf[10];
    }

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    while (num && i) {
        buf[i--] = (num % 10) + '0';
        num /= 10;
    }

    if (is_negative) {
        buf[i--] = '-';
    }

    return &buf[i + 1];
}

int strlen(const char *s) {
    int len = 0;
    while (*s++) len++;
    return len;
}

void *strcpy(char *dest, const char *src) {
    char *p = dest;
    while (*src) *p++ = *src++;
    *p = '\0';
    return dest;

}

void *strncpy(char *dest, const char *src, size_t n) {
    char *p = dest;
    while (n-- && *src) *p++ = *src++;
    *p = '\0';
    return dest;
}

int atoi(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
        i++;
    }

    if (str[i] == '-' || str[i] == '+') {
        sign = (str[i] == '-') ? -1 : 1;
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return sign * result;
}

void trim(char *s) {
    int start = 0, len = strlen(s);
    while (s[start] == ' ') start++;
    if (start > 0) memmove(s, s + start, len - start + 1);
    len = strlen(s);
    while (len > 0 && s[len-1] == ' ') s[--len] = 0;
}

char *strchr(const char *s, int c) {
    while (*s) {
        if (*s == (char)c) return (char*)s;
        s++;
    }
    return (c == 0) ? (char*)s : NULL;
}

void *memmove(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;
    if (d < s) {
        while (n--) *d++ = *s++;
    } else if (d > s) {
        d += n;
        s += n;
        while (n--) *--d = *--s;
    }
    return dest;
}

char **split(const char *str, char delimiter, int *count) {
    static char words_buf[64][64];
    static char *result[64];

    int n = 0;
    const char *ptr = str;

    while (*ptr && n < 64) {
        while (*ptr == delimiter) ptr++;
        if (!*ptr) break; // if end of string

        char *dst = words_buf[n]; int len = 0;
        while (*ptr && *ptr != delimiter && len < 63) {
            dst[len++] = *ptr++;
        }
        dst[len] = 0;
        result[n] = dst;
        n++;
    }

    *count = n;
    return result;
}

char *strtok(char *str, const char *delim) {
    static char *last = NULL;
    
    if (str != NULL) {
        last = str;
    }
    
    if (last == NULL) {
        return NULL;
    }
    
    while (*last && strchr(delim, *last) != NULL) {
        last++;
    }
    
    if (*last == '\0') {
        last = NULL;
        return NULL;
    }
    
    char *token = last;
    
    while (*last && strchr(delim, *last) == NULL) {
        last++;
    }
    
    if (*last != '\0') {
        *last = '\0';
        last++;
    } else {
        last = NULL;
    }
    
    return token;
}

char *strstr(const char *haystack, const char *needle) {
    if (*needle == '\0') {
        return (char *)haystack;
    }
    
    while (*haystack) {
        const char *h = haystack;
        const char *n = needle;
        
        while (*h && *n && *h == *n) {
            h++;
            n++;
        }
        
        if (*n == '\0') {
            return (char *)haystack;
        }
        
        haystack++;
    }
    
    return NULL;
}
