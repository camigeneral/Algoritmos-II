#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

size_t jenkins_hash(char* key, size_t length);
size_t murmurOAAT32(const char* key);
size_t cami_hash(const char* clave);
unsigned long peti_hash1(char *str);
size_t peti_hash2(char *str);
