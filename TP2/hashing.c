#include "hashing.h"

size_t jenkins_hash(char* key, size_t length) {
  size_t i = 0;
  size_t hash = 0;
  while (i != length) {
    hash += key[i++];
    hash += hash << 10;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;
  return hash;
}

size_t murmurOAAT32(const char* key) {
  size_t h = 0;
  for (;*key;++key) {
    h ^= *key;
    h *= 0x5bd1e995;
    h ^= h >> 15;
  }
  return h;
}

size_t cami_hash(const char* clave) {
	size_t hash = 0;
	for (int i = 0; clave[i]; i++) {
		hash += *clave;
		hash *= ((hash << 27) + hash);
		hash ^= hash >> 7;
	}
	hash ^= hash >> 5;
	return hash;	
}

unsigned long peti_hash1(char *str){
    unsigned int hash = 0;
    int c = 0;
    int longitud = (int) strlen(str);

    while (c <= longitud){
        hash += str[c];
        hash -= longitud;
        if (hash % 2 == 0){
            hash = hash * 3;
        }
        else{
            hash = hash * 4;
        }
		hash ^= (str[c]-1);
		hash ^= 5;
        c++;
    }
    return hash;
}

size_t peti_hash2(char* str){
    unsigned long hash = 0;
    int c = 0;

    while (c <= strlen(str)){
        hash = c + (hash << 6) + (hash << 16) - hash;
        hash ^= str[c];
        c++;
    }
    return hash;
}

/*int main() {
	char* cadena1 = "martillo";
	char* cadena2 = "tigre";
	char* cadena3 = "mako";

	size_t jenkins1 = jenkins_hash(cadena1, strlen(cadena1));
	size_t jenkins2 = jenkins_hash(cadena2, strlen(cadena2));
	size_t jenkins3 = jenkins_hash(cadena3, strlen(cadena3));

	printf("JENKINS\nmartillo: %ld, tigre: %ld, mako: %ld\n", jenkins1, jenkins2, jenkins3);

	size_t murmur1 = murmurOAAT32(cadena1);
    size_t murmur2 = murmurOAAT32(cadena2);
    size_t murmur3 = murmurOAAT32(cadena3);

	printf("MURMUR\nmartillo: %ld, tigre: %ld, mako: %ld\n", murmur1, murmur2, murmur3);

	size_t cami1 = cami_hash(cadena1);
    size_t cami2 = cami_hash(cadena2);
    size_t cami3 = cami_hash(cadena3);

    printf("CAMI :)\nmartillo: %ld, tigre: %ld, mako: %ld\n", cami1, cami2, cami3);

	size_t peti1_1 = peti_hash1(cadena1);
    size_t peti1_2 = peti_hash1(cadena2);
    size_t peti1_3 = peti_hash1(cadena3);

    printf("PETI 1 :)\nmartillo: %ld, tigre: %ld, mako: %ld\n", peti1_1, peti1_2, peti1_3);

	size_t peti2_1 = peti_hash2(cadena1);
    size_t peti2_2 = peti_hash2(cadena2);
    size_t peti2_3 = peti_hash2(cadena3);

    printf("PETI 2 :)\nmartillo: %ld, tigre: %ld, mako: %ld\n", peti2_1, peti2_2, peti2_3);

}*/
