#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define MAX_ELEMENTO 100


static void prueba_crear_abb_vacio(){
    printf("------------- PRUEBAS CREAR ABB VACIO------------\n");

    abb_t* abb = abb_crear(strcmp,NULL);

    print_test("abb crear abb vacio", abb);
    print_test("abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

    abb_destruir(abb);
}


static void prueba_abb_insertar(){
    printf("\n------------- PRUEBAS INSERTAR ------------\n");

    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 1 valor y luego lo borra */
    print_test("abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Inserta otros 2 valores y no los borra (se destruyen con el abb) */
    print_test("abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("abb pertenece clave2, es true", abb_pertenece(abb, clave2));

    print_test("abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("abb pertenece clave3, es true", abb_pertenece(abb, clave3));

    abb_destruir(abb);
}


static void prueba_abb_clave_vacia(){
    printf("\n-------------PRUEBAS INSETAR CLAVE VACIA-------------\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave = "", *valor = "";

    print_test("abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}


void prueba_abb_reemplazar() {
	printf("\n-------------PRUEBAS ABB REEMPLAZAR -------------\n");

	// Declaro las variables a utilizar.
   	abb_t* abb = abb_crear(strcmp, NULL);
    char* clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char* clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

    // Inserta 2 valores.
    print_test("Insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Obtener clave1 devuelve valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Obtener clave2 devuelve valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("La cantidad de elementos es 2", abb_cantidad(abb) == 2);

    // Reemplaza los 2 valores previamente insertados.
    print_test("Insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Obtener clave1 devuelve valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Obtener clave2 devuelve valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("La cantidad de elementos es 2", abb_cantidad(abb) == 2);

    // Destruyo el ABB.
    abb_destruir(abb);
    print_test("El ABB fue destruido", true);
}

void prueba_abb_borrar() {
	printf("\n-------------PRUEBAS ABB BORRAR-------------\n");

	// Declaro las variables a utilizar.
    abb_t* abb = abb_crear(strcmp, free);
    char* clave1 = "perro", *valor1 = "guau";
    char* clave2 = "gato", *valor2 = "miau";
    char* clave3 = "vaca", *valor3 = "mu";

    // Inserta 3 valores.
    print_test("Insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Insertar clave3", abb_guardar(abb, clave3, valor3));

    // Al borrar cada elemento comprueba que ya no está pero los otros sí.
    print_test("Pertenece clave3, devuelve true", abb_pertenece(abb, clave3));
    print_test("Borrar clave3, devuelve valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Borrar clave3, devuelve NULL", !abb_borrar(abb, clave3));
    print_test("Pertenece clave3, devuelve falso", !abb_pertenece(abb, clave3));
    print_test("Obtener clave3, devuelve NULL", !abb_obtener(abb, clave3));
    print_test("La cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Pertenece clave1, devuelve true", abb_pertenece(abb, clave1));
    print_test("Borrar clave1, devuelve valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Borrar clave1, devuelve NULL", !abb_borrar(abb, clave1));
    print_test("Pertenece clave1, devuelve falso", !abb_pertenece(abb, clave1));
    print_test("Obtener clave1, devuelve NULL", !abb_obtener(abb, clave1));
    print_test("La cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Pertenece clave2, devuelve true", abb_pertenece(abb, clave2));
    print_test("Borrar clave2, devuelve valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Borrar clave2, devuelve NULL", !abb_borrar(abb, clave2));
    print_test("Pertenece clave2, devuelve falso", !abb_pertenece(abb, clave2));
    print_test("Obtener clave2, devuelve NULL", !abb_obtener(abb, clave2));
    print_test("La cantidad de elementos es 0", abb_cantidad(abb) == 0);

    // Destruyo el ABB.
    abb_destruir(abb);
    print_test("El ABB fue destruido", true);
}


static void prueba_abb_reemplazar_con_destruir(){
    printf("\n-------------PRUEBAS ABB REEMPLAZR CON DESTRUIR -------------\n");
    abb_t* abb = abb_crear(strcmp,free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    /* Pide memoria para 4 valores */
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    /* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
    print_test("abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    /* Se destruye el abb (se debe liberar lo que quedó dentro) */
    abb_destruir(abb);
}


static void prueba_abb_valor_null(){
    printf("\n-------------PRUEBAS ABB INSERTAR NULL -------------\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave = "", *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}


static ssize_t buscar(const char* clave, char* claves[], size_t largo){
    for (size_t i = 0; i < largo; i++) {
        if (strcmp(clave, claves[i]) == 0) return (ssize_t) i;
    }
    return -1;
}

void cambiar_orden(char* claves[], size_t largo) {
    srand((unsigned int) time(NULL));

    for (int i = (int) largo - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char* aux = claves[i];
        claves[i] = claves[j];
        claves[j] = aux;
    }
}


void prueba_abb_volumen(size_t largo, bool debug) {
	printf("\n-------------PRUEBAS ABB VOLUMEN -------------\n");

	// Declaro las variables a utilizar.
    abb_t* abb = abb_crear(strcmp, NULL);
    const size_t largo_clave = 10;
    char* claves[largo];
    unsigned* valores[largo];

    // Inserta 'largo' parejas en el ABB.
    for (unsigned i = 0; i < largo; i++) {
        claves[i] = malloc(largo_clave);
        valores[i] = malloc(sizeof(unsigned));
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
    }
    cambiar_orden(claves, largo);

    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    if (debug) print_test("Almacenar muchos elementos", ok);
    if (debug) print_test("La cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    // Verifica que devuelva los valores correctos.
    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Pertenece y obtener muchos elementos", ok);
    if (debug) print_test("La cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    // Verifica que borre y devuelva los valores correctos.
    for (size_t i = 0; i < largo; i++) {
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (!ok)  {
            break;
       }
    }

    if (debug) print_test("Borrar muchos elementos", ok);
    if (debug) print_test("La cantidad de elementos es 0", abb_cantidad(abb) == 0);

    // Destruye el ABB y crea uno nuevo que sí libera.
    abb_destruir(abb);
    abb = abb_crear(strcmp, free);

    // Inserta 'largo' parejas en el abb.
    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    for(size_t i = 0; i < largo; i++) {
        free(claves[i]);
    }

    // Destruye el ABB - debería liberar los enteros.
    abb_destruir(abb);
    print_test("El ABB fue destruido y su contenido liberado", true);
}


static void prueba_abb_iterar_vacio(){
    printf("\n-------------PRUEBAS ABB_ITER VACIO -------------\n");
    abb_t* abb = abb_crear(strcmp,NULL);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("abb iter crear iterador abb vacio", iter);
    print_test("abb iter esta al final", abb_iter_in_al_final(iter));
    print_test("abb iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

static void prueba_abb_iterar_no_vacio(){
    printf("\n-------------PRUEBAS ABB_ITER NO VACIO -------------\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    char *claves[] = {"perro", "gato", "vaca"};
    char *valores[] = {"guau", "miau", "mu"};

    /* Inserta 3 valores */
    print_test("abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));

    // de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    const char *clave;
    ssize_t indice;

    print_test("abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Primer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("abb iterador ver actual, es una clave valida", indice != -1);
    print_test("abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Segundo valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("abb iterador ver actual, es una clave valida", indice != -1);
    print_test("abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Tercer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("abb iterador ver actual, es una clave valida", indice != -1);
    print_test("abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    abb_iter_in_avanzar(iter);
    print_test("abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    /* Vuelve a tratar de avanzar, por las dudas */
    print_test("abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
    print_test("abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

static void prueba_abb_iterar_volumen(size_t largo){
    printf("\n-------------PRUEBAS ABB ITER VOLUMEN -------------\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    size_t valores[largo];

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        sprintf(claves[i], "%08d", i);
        valores[i] = i;
        ok = abb_guardar(abb, claves[i], &valores[i]);
        if (!ok) break;
    }

    // prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char *clave;
    size_t *valor;

    for (i = 0; i < largo; i++) {
        if ( abb_iter_in_al_final(iter) ) {
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if ( clave == NULL ) {
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave);
        if ( valor == NULL ) {
            ok = false;
            break;
        }
        *valor = largo;
        abb_iter_in_avanzar(iter);
    }
    print_test("abb iteración en volumen", ok);
    print_test("abb iteración en volumen, recorrio todo el largo", i == largo);
    print_test("abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    ok = true;
    for (i = 0; i < largo; i++) {
        if ( valores[i] != largo ) {
            ok = false;
            break;
        }
    }
    print_test("abb iteración en volumen, se cambiaron todo los elementos", ok);

    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

bool calcular_suma(const char* clave, void* dato , void* contador){
    *(int*) contador +=  *(int*) dato;
    return true;
}

void prueba_abb_iterar_interno_sin_corte() {
	printf("\n-------------PRUEBAS ITERADOR INTERNO SIN CORTE-------------\n");

	// Declaro variables a utilizar.
    abb_t* abb = abb_crear(strcmp, NULL);
    size_t tam = 4;
    int datos[4] = {1, 2, 3, 4};
    char* claves[4] = {"perrito", "gatito", "vaquita", "monito"};
    int suma = 0;

    print_test("El ABB fue creado", abb);

    // Pruebo guardar claves.
    bool ok_guardar = true;
    for (size_t i = 0; i < tam; i++) {
    	ok_guardar &= abb_guardar(abb, *(claves + i), datos + i);
    }
    print_test("Se guardaron todos los elementos correctamente", ok_guardar);
    print_test("La cantidad de elementos es 4", abb_cantidad(abb) == tam);

    // Pruebo iterar con el iterador interno.
    abb_in_order(abb, calcular_suma, &suma);
    print_test("Se sumaron todos los elementos", suma == 10);

    // Destruyo el ABB.
    abb_destruir(abb);
    print_test("El ABB fue destruido", true);
}

bool concatenar_datos(const char* clave, void* elemento, void* extra) {
    printf("%s la clave\n",clave);
    char* cadena = elemento;
    if (strcmp(cadena, "Kit") == 0) {
    	return false;
    }
    strcat((char*) extra, cadena);
    strcat((char*) extra, " ");

    return true;
}

// Pruebas para el iterador interno con corte.
void prueba_abb_iterar_interno_con_corte() {
	printf("\n-------------PRUEBAS ITERADOR INTERNO CON CORTE-------------\n");

	// Declaro las variables a utilizar.
	abb_t* abb = abb_crear(strcmp, NULL);
	size_t tam = 7;
	char* claves[7] = {"Clark", "Harrington", "Headey", "Dinklage", "Williams", "Turner", "Momoa"};
    char* datos[7] = {"Emilia", "Kit", "Lena", "Peter", "Maisie", "Sophie", "Jason"};
    char cadena[14] = "";
    char cadena_esperada[14] = "Emilia Peter ";
    
    print_test("El ABB fue creado", abb);

   	// Pruebo guardar claves.
    bool ok_guardar = true;
    for (size_t i = 0; i < tam; i++) {
    	ok_guardar &= abb_guardar(abb, *(claves + i), *(datos + i));
    }
    
    print_test("Se guardaron todos los elementos correctamente", ok_guardar);
    print_test("La cantidad de elementos es 7", abb_cantidad(abb) == tam);

    // Pruebo iterar con el iterador interno.
    abb_in_order(abb, concatenar_datos, &cadena);
    print_test("Se logró concatenar correctamente", strcmp(cadena, cadena_esperada) == 0);

    // Destruyo el ABB.
    abb_destruir(abb);
    print_test("El ABB fue destruido", true);
}

void pruebas_abb_estudiante(void){
    prueba_crear_abb_vacio();
    prueba_abb_insertar();
    prueba_abb_clave_vacia();
    prueba_abb_reemplazar();
    prueba_abb_reemplazar_con_destruir();
    prueba_abb_valor_null();
    prueba_abb_volumen(MAX_ELEMENTO, true);
    prueba_abb_borrar();
    prueba_abb_iterar_interno_sin_corte();
    prueba_abb_iterar_interno_con_corte();
    prueba_abb_iterar_vacio();
    prueba_abb_iterar_no_vacio();
    prueba_abb_iterar_volumen(MAX_ELEMENTO);

}

#ifndef CORRECTOR

int main(void) {
    pruebas_abb_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
