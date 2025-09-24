#ifndef STRING_H
#define STRING_H

#include <stddef.h>

void *memcpy(void *dest, const void *src, size_t n);
void memset(void *s, int c, size_t n);
int strcmp(const char *s1, const char *s2);
char* itoa(int num);
int strlen(const char *s);
void *strcpy(char *dest, const char *src);
void *strncpy(char *dest, const char *src, size_t n);
int atoi(const char *str);
char* strchr(const char *s, int c);
void trim(char *s);
void *memmove(void *dest, const void *src, size_t n);
char **split(const char *str, char delimiter, int *count);
int memcmp(const void *s1, const void *s2, size_t n);
int toupper(int c);
char *strtok(char *str, const char *delim);
char *strstr(const char *haystack, const char *needle);

#endif