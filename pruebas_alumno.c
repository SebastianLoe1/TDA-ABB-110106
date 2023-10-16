#include "pa2m.h"
#include "src/abb.h"
#include "src/abb_estructura_privada.h"

int comparador(void *_elemento1, void *_elemento2)
{
	if (!_elemento1 && !_elemento2) {
		return 0;
	}
	int *elemento1 = _elemento1;
	int *elemento2 = _elemento2;
	return *elemento1 - *elemento2;
}

void destructor(void *_elemento)
{
	if (_elemento) {
		int *elemento = _elemento;
		(*elemento)++;
	}
}

void CrearAbb()
{
	abb_t *arbol = abb_crear(comparador);

	pa2m_afirmar(arbol != NULL, "Se puede crear un abb.");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "El arbol tiene tamaño 0.");
	pa2m_afirmar(abb_vacio(arbol), "El árbol está vacío");
	pa2m_afirmar(!arbol->nodo_raiz, "El nodo raiz es NULL.");
	pa2m_afirmar(arbol->comparador == comparador,
		     "El comparador es valido.\n");
	abb_destruir(arbol);
}

void InsertarAbb()
{
	abb_t *arbol = abb_crear(comparador);
	int e1 = 10, e2 = 5, e3 = 2, e4 = 7, e5 = 15, e6 = 12, e7 = 17;

	pa2m_afirmar(abb_insertar(NULL, &e1) == NULL,
		     "No se puede insertar en un arbol NULL.");
	pa2m_afirmar(abb_insertar(arbol, &e1) == arbol,
		     "Se puede insertar un elemento.");
	pa2m_afirmar(abb_tamanio(arbol) == 1,
		     "Se actualiza correctamente el tamaño del arbol.\n");

	abb_insertar(arbol, &e2);
	abb_insertar(arbol, &e3);
	abb_insertar(arbol, &e4);
	abb_insertar(arbol, &e5);
	abb_insertar(arbol, &e6);
	abb_insertar(arbol, &e7);

	pa2m_afirmar(
		abb_tamanio(arbol) == 7,
		"Se actualiza correctamente el tamaño del árbol con 7 elementos");

	nodo_abb_t *nodo_actual = arbol->nodo_raiz;
	pa2m_afirmar(nodo_actual->elemento == &e1,
		     "El 1er elemento insertado esta en su posicion correcta.");
	pa2m_afirmar(nodo_actual->izquierda->elemento == &e2,
		     "El 2do elemento insertado esta en su posicion correcta.");
	pa2m_afirmar(nodo_actual->derecha->elemento == &e5,
		     "El 3er elemento insertado esta en su posicion correcta.");
	pa2m_afirmar(nodo_actual->izquierda->izquierda->elemento == &e3,
		     "El 4to elemento insertado esta en su posicion correcta.");
	pa2m_afirmar(nodo_actual->izquierda->derecha->elemento == &e4,
		     "El 5to elemento insertado esta en su posicion correcta.");
	pa2m_afirmar(nodo_actual->derecha->izquierda->elemento == &e6,
		     "El 6to elemento insertado esta en su posicion correcta.");
	pa2m_afirmar(
		nodo_actual->derecha->derecha->elemento == &e7,
		"El 7mo elemento insertado esta en su posicion correcta.\n");
	pa2m_afirmar(abb_vacio(arbol) == false,
		     "El árbol no se encuentra vacío con varios elementos.");
	abb_destruir(arbol);
}

void QuitarAbb()
{
	int e1 = 10, e2 = 15, e3 = 5;

	abb_t *arbol = abb_crear(comparador);

	abb_insertar(arbol, NULL);
	pa2m_afirmar(abb_quitar(NULL, &e1) == NULL,
		     "No se puede quitar un elemento de un arbol NULL.");

	pa2m_afirmar(abb_quitar(arbol, NULL) == NULL,
		     "Se puede quitar un elemento NULL.");
	pa2m_afirmar(arbol->tamanio == 0,
		     "Se actualiza correctamente el tamaño del arbol.");
	pa2m_afirmar(
		arbol->nodo_raiz == NULL,
		"El nodo raiz del arbol es NULL luego de eliminar el unico elemento del arbol.\n");

	abb_insertar(arbol, &e1);
	abb_insertar(arbol, &e2);
	pa2m_afirmar(
		abb_quitar(arbol, &e1) == &e1,
		"Se quita correctamente el nodo raiz con un hijo derecho.");
	pa2m_afirmar(abb_buscar(arbol, &e1) == NULL,
		     "No se encuentra el elemento quitado.");
	pa2m_afirmar(arbol->nodo_raiz->elemento == &e2,
		     "Se actualiza correctamente el nodo raiz.");
	pa2m_afirmar(arbol->tamanio == 1,
		     "Se actualiza correctamente el tamaño del arbol.\n");

	abb_insertar(arbol, &e3);
	pa2m_afirmar(
		abb_quitar(arbol, &e2) == &e2,
		"Se quita correctamente el nodo raiz con un hijo izquierdo.");
	pa2m_afirmar(abb_buscar(arbol, &e2) == NULL,
		     "No se encuentra el elemento quitado.");
	pa2m_afirmar(arbol->nodo_raiz->elemento == &e3,
		     "Se actualiza correctamente el nodo raiz.");
	pa2m_afirmar(arbol->tamanio == 1,
		     "Se actualiza correctamente el tamaño del arbol.\n");
	abb_destruir(arbol);

	arbol = abb_crear(comparador);
	abb_insertar(arbol, &e1);
	abb_insertar(arbol, &e3);
	abb_insertar(arbol, &e2);
	pa2m_afirmar(abb_quitar(arbol, &e1) == &e1,
		     "Se quita correctamente el nodo raiz con dos hijos.");
	pa2m_afirmar(abb_buscar(arbol, &e1) == NULL,
		     "No se encuentra el elemento quitado.");
	pa2m_afirmar(
		arbol->nodo_raiz->elemento == &e3,
		"Se actualiza correctamente el nodo raiz con el predecesor inorden.");
	pa2m_afirmar(
		arbol->nodo_raiz->derecha->elemento == &e2,
		"El nuevo nodo raiz mantiene el hijo derecho del original.");
	pa2m_afirmar(arbol->tamanio == 2,
		     "Se actualiza correctamente el tamaño del arbol.\n");
	abb_destruir(arbol);
}

void QuitadoMasivo()
{
	int e1 = 10, e2 = 5, e3 = 2, e4 = 7, e5 = 15, e6 = 12, e7 = 17;
	abb_t *arbol = abb_crear(comparador);
	abb_insertar(arbol, &e1);
	abb_insertar(arbol, &e2);
	abb_insertar(arbol, &e5);
	abb_insertar(arbol, &e3);
	abb_insertar(arbol, &e4);
	abb_insertar(arbol, &e6);
	abb_insertar(arbol, &e7);
	pa2m_afirmar(abb_quitar(arbol, &e7) == &e7,
		     "Se quita correctamente un nodo hoja.");
	pa2m_afirmar(abb_buscar(arbol, &e7) == NULL,
		     "No se encuentra el elemento quitado.");
	pa2m_afirmar(
		arbol->nodo_raiz->derecha->derecha == NULL,
		"Se actualiza correctamente el puntero al nodo quitado en NULL.");
	pa2m_afirmar(arbol->tamanio == 6,
		     "Se actualiza correctamente el tamaño del arbol.\n");
	pa2m_afirmar(abb_quitar(arbol, &e2) == &e2,
		     "Se quita correctamente un nodo con dos hijos.");
	pa2m_afirmar(abb_buscar(arbol, &e2) == NULL,
		     "No se encuentra el elemento quitado.");
	pa2m_afirmar(
		arbol->nodo_raiz->izquierda->elemento == &e3,
		"Se actualiza correctamente el nodo eliminado con el predecesor inorden.");
	pa2m_afirmar(
		arbol->nodo_raiz->izquierda->derecha->elemento == &e4,
		"El predecesor inorden mantiene el hijo derecho del original.");
	pa2m_afirmar(arbol->tamanio == 5,
		     "Se actualiza correctamente el tamaño del arbol.\n");
	pa2m_afirmar(abb_quitar(arbol, &e3) == &e3,
		     "Se quita correctamente un nodo con hijo derecho.");
	pa2m_afirmar(abb_buscar(arbol, &e3) == NULL,
		     "No se encuentra el elemento quitado.");
	pa2m_afirmar(
		arbol->nodo_raiz->izquierda->elemento == &e4,
		"Se actualiza correctamente el valor en posicion del nodo eliminado con el de su hijo derecho.");
	pa2m_afirmar(arbol->tamanio == 4,
		     "Se actualiza correctamente el tamaño del arbol.\n");
	pa2m_afirmar(abb_quitar(arbol, &e5) == &e5,
		     "Se quita correctamente un nodo con hijo izquierdo.");
	pa2m_afirmar(abb_buscar(arbol, &e5) == NULL,
		     "No se encuenctra el elemento quitado.");
	pa2m_afirmar(
		arbol->nodo_raiz->derecha->elemento == &e6,
		"Se actualiza correctamente el valor en posicion del nodo eliminado con el de su hijo izquierdo.");
	pa2m_afirmar(arbol->tamanio == 3,
		     "Se actualiza correctamente el tamaño del arbol.\n");
	abb_destruir(arbol);
}

void BuscarAbb()
{
	int e1 = 10, e2 = 5, e3 = 2, e4 = 7, e5 = 15, e6 = 12, e7 = 17;
	abb_t *arbol = abb_crear(comparador);

	abb_insertar(arbol, &e1);
	abb_insertar(arbol, &e2);
	abb_insertar(arbol, &e5);
	abb_insertar(arbol, &e3);
	abb_insertar(arbol, &e4);
	abb_insertar(arbol, &e6);
	abb_insertar(arbol, &e7);

	pa2m_afirmar(abb_buscar(arbol, &e1) == &e1,
		     "Se busca el 1er elemento del arbol y se encuentra.");
	pa2m_afirmar(abb_buscar(arbol, &e2) == &e2,
		     "Se busca el 2do elemento del arbol y se encuentra.");
	pa2m_afirmar(abb_buscar(arbol, &e5) == &e5,
		     "Se busca el 3er elemento del arbol y se encuentra.");
	pa2m_afirmar(abb_buscar(arbol, &e3) == &e3,
		     "Se busca el 4to elemento del arbol y se encuentra.");
	pa2m_afirmar(abb_buscar(arbol, &e4) == &e4,
		     "Se busca el 5to elemento del arbol y se encuentra.");
	pa2m_afirmar(abb_buscar(arbol, &e6) == &e6,
		     "Se busca el 6to elemento del arbol y se encuentra.");
	pa2m_afirmar(abb_buscar(arbol, &e7) == &e7,
		     "Se busca el 7mo elemento del arbol y se encuentra.\n");
	abb_destruir(arbol);
}

bool cuenta_todo(void *elemento, void *ignorado)
{
	if (!elemento) {
		return false;
	}

	int *el = elemento;
	(*el)++;

	return true;
}

bool cuenta_hasta_siete(void *elemento, void *ignorado)
{
	if (!elemento) {
		return false;
	}

	int *el = elemento;
	(*el)++;
	if (*el == 7) {
		return false;
	}

	return true;
}

void ConCadaElementoAbb()
{
	abb_recorrido e1 = 10;
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_con_cada_elemento(NULL, INORDEN, cuenta_todo, NULL) ==
			     0,
		     "Devuelve 0 con un arbol NULL.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, NULL, &e1) == 0,
		     "Devuelve 0 con una función NULL.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, e1, cuenta_hasta_siete,
					   NULL) == 0,
		     "Devuelve 0 con un recorrido inválido.");
	abb_insertar(arbol, &e1);
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, cuenta_todo, NULL) !=
			     0,
		     "Se puede invocar con un aux NULL.\n");
	abb_destruir(arbol);
}

void ConCadaInorden()
{
	int e1 = 10, e2 = 5, e3 = 2, e4 = 7, e5 = 15, e6 = 12, e7 = 17;
	pa2m_afirmar(abb_con_cada_elemento(NULL, INORDEN, cuenta_todo, &e1) ==
			     0,
		     "Devuelve 0 con un arbol NULL iterando INORDEN.");
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, NULL, &e1) == 0,
		     "Devuelve 0 con una función NULL iterando INORDEN.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, cuenta_todo, &e1) ==
			     0,
		     "Devuelve 0 con un arbol vacío iterando INORDEN.");
	abb_insertar(arbol, &e1);
	abb_insertar(arbol, &e2);
	abb_insertar(arbol, &e5);
	abb_insertar(arbol, &e3);
	abb_insertar(arbol, &e4);
	abb_insertar(arbol, &e6);
	abb_insertar(arbol, &e7);
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, INORDEN, cuenta_todo, NULL) == 7,
		"Se aplica la función la cantidad de veces correcta iterando INORDEN todo el arbol.");
	pa2m_afirmar(
		e1 == 11 && e2 == 6 && e3 == 3 && e4 == 8 && e5 == 16 &&
			e6 == 13 && e7 == 18,
		"Se aplica la función a cada uno de los elementos iterando INORDEN todo el arbol.");
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, INORDEN, cuenta_hasta_siete,
				      NULL) == 2,
		"Se aplica la función la cantidad de veces correcta iterando INORDEN parte del arbol.");
	pa2m_afirmar(
		e2 == 7 && e3 == 4 && e4 == 8,
		"Se aplica la función a los elementos correctos iterando INORDEN parte del arbol.\n");
	abb_destruir(arbol);
}

void ConCadaPreorden()
{
	int e1 = 10, e2 = 5, e3 = 2, e4 = 7, e5 = 15, e6 = 12, e7 = 17;
	pa2m_afirmar(abb_con_cada_elemento(NULL, PREORDEN, cuenta_todo, &e1) ==
			     0,
		     "Devuelve 0 con un arbol NULL iterando PREORDEN.");
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, NULL, &e1) == 0,
		     "Devuelve 0 con una función NULL iterando PREORDEN.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, cuenta_todo, &e1) ==
			     0,
		     "Devuelve 0 con un arbol vacío iterando PREORDEN.");
	abb_insertar(arbol, &e1);
	abb_insertar(arbol, &e2);
	abb_insertar(arbol, &e5);
	abb_insertar(arbol, &e3);
	abb_insertar(arbol, &e4);
	abb_insertar(arbol, &e6);
	abb_insertar(arbol, &e7);
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, PREORDEN, cuenta_todo, NULL) == 7,
		"Se aplica la función la cantidad de veces correcta iterando PREORDEN todo el arbol.");
	pa2m_afirmar(
		e1 == 11 && e2 == 6 && e3 == 3 && e4 == 8 && e5 == 16 &&
			e6 == 13 && e7 == 18,
		"Se aplica la función a cada uno de los elementos iterando PREORDEN todo el arbol.");
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, PREORDEN, cuenta_hasta_siete,
				      NULL) == 2,
		"Se aplica la función la cantidad de veces correcta iterando PREORDEN parte del arbol.");
	pa2m_afirmar(
		e2 == 7 && e4 == 8 && e3 == 3,
		"Se aplica la función a los elementos correctos iterando PREORDEN parte del arbol.\n");
	abb_destruir(arbol);
}

void ConCadaPostorden()
{
	int e1 = 10, e2 = 5, e3 = 2, e4 = 7, e5 = 15, e6 = 12, e7 = 17;
	pa2m_afirmar(abb_con_cada_elemento(NULL, POSTORDEN, cuenta_todo, &e1) ==
			     0,
		     "Devuelve 0 con un arbol NULL iterando POSTORDEN.");
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, NULL, &e1) == 0,
		     "Devuelve 0 con una función NULL iterando POSTORDEN.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, cuenta_todo,
					   &e1) == 0,
		     "Devuelve 0 con un arbol vacío iterando POSTORDEN.");
	abb_insertar(arbol, &e1);
	abb_insertar(arbol, &e2);
	abb_insertar(arbol, &e5);
	abb_insertar(arbol, &e3);
	abb_insertar(arbol, &e4);
	abb_insertar(arbol, &e6);
	abb_insertar(arbol, &e7);
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, POSTORDEN, cuenta_todo, NULL) == 7,
		"Se aplica la función la cantidad de veces correcta iterando POSTORDEN todo el arbol.");
	pa2m_afirmar(
		e1 == 11 && e2 == 6 && e3 == 3 && e4 == 8 && e5 == 16 &&
			e6 == 13 && e7 == 18,
		"Se aplica la función a cada uno de los elementos iterando POSTORDEN todo el arbol.");
	pa2m_afirmar(
		abb_con_cada_elemento(arbol, POSTORDEN, cuenta_hasta_siete,
				      NULL) == 3,
		"Se aplica la función la cantidad de veces correcta iterando POSTORDEN parte del arbol.");
	pa2m_afirmar(
		e2 == 7 && e4 == 9 && e3 == 4,
		"Se aplica la función a los elementos correctos iterando POSTORDEN parte del arbol.\n");
	abb_destruir(arbol);
}

void RecorrerABB()
{
	int e1 = 10;
	void *array[7];
	pa2m_afirmar(abb_recorrer(NULL, INORDEN, array, 7) == 0,
		     "Devuelve 0 con un arbol NULL.");
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(abb_recorrer(arbol, INORDEN, array, 7) == 0,
		     "Devuelve 0 con un arbol vacío.");
	abb_insertar(arbol, &e1);
	pa2m_afirmar(abb_recorrer(arbol, INORDEN, NULL, 7) == 0,
		     "Devuelve 0 con un array NULL.");
	pa2m_afirmar(abb_recorrer(arbol, INORDEN, array, 0) == 0,
		     "Devuelve 0 con un array de tamaño 0");
	pa2m_afirmar(abb_recorrer(arbol, e1, array, 7) == 0,
		     "Devuelve 0 con un recorrido inválido.");
	pa2m_afirmar(abb_recorrer(arbol, INORDEN, array, 7) != 0,
		     "Se puede invocar con parámetros válidos.\n");
	abb_destruir(arbol);
}

void RecorrerAbbInorden()
{
	int e1 = 10, e2 = 5, e3 = 2, e4 = 7, e5 = 15, e6 = 12, e7 = 17;
	void *array[7];
	abb_t *arbol = abb_crear(comparador);
	abb_insertar(arbol, &e1);
	abb_insertar(arbol, &e2);
	abb_insertar(arbol, &e5);
	abb_insertar(arbol, &e3);
	abb_insertar(arbol, &e4);
	abb_insertar(arbol, &e6);
	abb_insertar(arbol, &e7);
	size_t contador = abb_recorrer(arbol, INORDEN, array, 7);
	pa2m_afirmar(contador != 0,
		     "Se puede recorrer el abb en recorrido INORDEN.");
	pa2m_afirmar(
		contador == 7,
		"Devuelve la cantidad correcta de elementos almacenados iterando INORDEN.");
	pa2m_afirmar(
		array[0] == &e3,
		"El 1er elemento del vector es el correcto iterando INORDEN.");
	pa2m_afirmar(
		array[1] == &e2,
		"El 2do elemento del vector es el correcto iterando INORDEN.");
	pa2m_afirmar(
		array[2] == &e4,
		"El 3er elemento del vector es el correcto iterando INORDEN.");
	pa2m_afirmar(
		array[3] == &e1,
		"El 4to elemento del vector es el correcto iterando INORDEN.");
	pa2m_afirmar(
		array[4] == &e6,
		"El 5to elemento del vector es el correcto iterando INORDEN.");
	pa2m_afirmar(
		array[5] == &e5,
		"El 6to elemento del vector es el correcto iterando INORDEN.");
	pa2m_afirmar(
		array[6] == &e7,
		"El 7mo elemento del vector es el correcto iterando INORDEN.\n");
	abb_destruir(arbol);
}

void RecorrerAbbPreorden()
{
	int e1 = 10, e2 = 5, e3 = 2, e4 = 7, e5 = 15, e6 = 12, e7 = 17;
	void *array[7];
	abb_t *arbol = abb_crear(comparador);
	abb_insertar(arbol, &e1);
	abb_insertar(arbol, &e2);
	abb_insertar(arbol, &e5);
	abb_insertar(arbol, &e3);
	abb_insertar(arbol, &e4);
	abb_insertar(arbol, &e6);
	abb_insertar(arbol, &e7);
	size_t contador = abb_recorrer(arbol, PREORDEN, array, 7);
	pa2m_afirmar(contador != 0,
		     "Se puede recorrer el abb en recorrido PREORDEN.");
	pa2m_afirmar(
		contador == 7,
		"Devuelve la cantidad correcta de elementos almacenados iterando PREORDEN.");
	pa2m_afirmar(
		array[0] == &e1,
		"El 1er elemento del vector es el correcto iterando PREORDEN.");
	pa2m_afirmar(
		array[1] == &e2,
		"El 2do elemento del vector es el correcto iterando PREORDEN.");
	pa2m_afirmar(
		array[2] == &e3,
		"El 3er elemento del vector es el correcto iterando PREORDEN.");
	pa2m_afirmar(
		array[3] == &e4,
		"El 4to elemento del vector es el correcto iterando PREORDEN.");
	pa2m_afirmar(
		array[4] == &e5,
		"El 5to elemento del vector es el correcto iterando PREORDEN.");
	pa2m_afirmar(
		array[5] == &e6,
		"El 6to elemento del vector es el correcto iterando PREORDEN.");
	pa2m_afirmar(
		array[6] == &e7,
		"El 7mo elemento del vector es el correcto iterando PREORDEN.\n");
	abb_destruir(arbol);
}

void RecorrerAbbPostorden()
{
	int e1 = 10, e2 = 5, e3 = 2, e4 = 7, e5 = 15, e6 = 12, e7 = 17;
	void *array[7];
	abb_t *arbol = abb_crear(comparador);
	abb_insertar(arbol, &e1);
	abb_insertar(arbol, &e2);
	abb_insertar(arbol, &e5);
	abb_insertar(arbol, &e3);
	abb_insertar(arbol, &e4);
	abb_insertar(arbol, &e6);
	abb_insertar(arbol, &e7);
	size_t contador = abb_recorrer(arbol, POSTORDEN, array, 7);
	pa2m_afirmar(contador != 0,
		     "Se puede recorrer el abb en recorrido POSTORDEN.");
	pa2m_afirmar(
		contador == 7,
		"Devuelve la cantidad correcta de elementos almacenados iterando POSTORDEN.");
	pa2m_afirmar(
		array[0] == &e3,
		"El 1er elemento del vector es el correcto iterando POSTORDEN.");
	pa2m_afirmar(
		array[1] == &e4,
		"El 2do elemento del vector es el correcto iterando POSTORDEN.");
	pa2m_afirmar(
		array[2] == &e2,
		"El 3er elemento del vector es el correcto iterando POSTORDEN.");
	pa2m_afirmar(
		array[3] == &e6,
		"El 4to elemento del vector es el correcto iterando POSTORDEN.");
	pa2m_afirmar(
		array[4] == &e7,
		"El 5to elemento del vector es el correcto iterando POSTORDEN.");
	pa2m_afirmar(
		array[5] == &e5,
		"El 6to elemento del vector es el correcto iterando POSTORDEN.");
	pa2m_afirmar(
		array[6] == &e1,
		"El 7mo elemento del vector es el correcto iterando POSTORDEN.\n");
	abb_destruir(arbol);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== Pruebas de Creado ========================");
	CrearAbb();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de Insertado ========================");
	InsertarAbb();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de Quitado ========================");
	QuitarAbb();
	QuitadoMasivo();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de Buscado ========================");
	BuscarAbb();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas Con Cada Elemento ========================");
	ConCadaElementoAbb();
	ConCadaInorden();
	ConCadaPostorden();
	ConCadaPreorden();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de Recorrido ========================");
	RecorrerABB();
	RecorrerAbbInorden();
	RecorrerAbbPostorden();
	RecorrerAbbPreorden();

	return pa2m_mostrar_reporte();
}
