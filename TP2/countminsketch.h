struct countminsketch;

typedef struct countminsketch cms_t;

// Crea el TDA countminsketch con 5 tablas de hashing
// con 5 algoritmos de hashing distintos
cms_t* cms_crear(size_t cantidad);

// Destruye el countminsketch
void cms_destruir(cms_t* cms);

// Se "hashea" la clave con ols 5 algoritmos de hashing,
// y se le suma 1 a la posición de cada tabla
void cms_guardar(cms_t* cms, char* clave);

// Se "hashea" la clave para obtener el mínimo de los
// valores de las 5 tablas. Dicho valor se retorna.  
size_t cms_ver_cantidad(cms_t* cms, char* clave);
