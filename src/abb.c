#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>


nodo_abb_t *nodo_crear(void *elemento){
	nodo_abb_t *nuevo_nodo = calloc(1, sizeof(nodo_abb_t));
	if(!nuevo_nodo){
		return NULL;
	}

	nuevo_nodo->elemento = elemento;

	return nuevo_nodo;
}

nodo_abb_t *insertar_rec(nodo_abb_t* nodo_actual, nodo_abb_t* nodo_nuevo, abb_comparador comparador){
	if(!nodo_actual){
		return nodo_nuevo;
	}

	if(comparador(nodo_nuevo->elemento, nodo_actual->elemento) <= 0){
		nodo_actual->izquierda = insertar_rec(nodo_actual->izquierda, nodo_nuevo, comparador);
	}

	else{
		nodo_actual->derecha = insertar_rec(nodo_actual->derecha, nodo_nuevo, comparador);
	}

	return nodo_actual;
}

bool con_cada_elemento_inorden(nodo_abb_t* nodo_actual, bool (*funcion)(void*, void*), void* aux, size_t* contador){
	if(!nodo_actual){
		return true;
	}

	bool continuar = con_cada_elemento_inorden(nodo_actual->izquierda, funcion, aux, contador);
	
	if(!continuar){
		return false;
	}

	(*contador)++;
	if(!funcion(nodo_actual->elemento, aux)){
		return false;
	}

	return con_cada_elemento_inorden(nodo_actual->derecha, funcion, aux, contador);
}

bool con_cada_elemento_preorden(nodo_abb_t* nodo_actual, bool (*funcion)(void*, void*), void* aux, size_t* contador){
	if(!nodo_actual){
		return true;
	}

	(*contador)++;
	if(!funcion(nodo_actual->elemento, aux)){
		return false;
	}

	bool continuar = con_cada_elemento_preorden(nodo_actual->izquierda, funcion, aux, contador);

	if(!continuar){
		return false;
	}

	return con_cada_elemento_preorden(nodo_actual->derecha, funcion, aux, contador);
}

bool con_cada_elemento_postorden(nodo_abb_t* nodo_actual, bool (*funcion)(void*, void*), void* aux, size_t* contador){
	if(!nodo_actual){
		return true;
	}

	bool continuar = con_cada_elemento_postorden(nodo_actual->izquierda, funcion, aux, contador);
	
	if(!continuar){
		return false;
	}

	con_cada_elemento_postorden(nodo_actual->derecha, funcion, aux, contador);

	(*contador)++;
	return funcion(nodo_actual->elemento, aux);
}

void destruir_todo_rec(abb_t *arbol, void (*destructor)(void *), nodo_abb_t *nodo_actual){
	if (!arbol){
		return;
	}

	if(arbol->tamanio == 0){
		free(arbol);
		return;
	}

	if(!nodo_actual){
		return;
	}

	destruir_todo_rec(arbol, destructor, nodo_actual->izquierda);
	destruir_todo_rec(arbol, destructor, nodo_actual->derecha);

	if(destructor){
		destructor(nodo_actual->elemento);
	}

	free(nodo_actual);
	arbol->tamanio--;

	if(arbol->tamanio == 0){
		free(arbol);
	}

	return;
}

abb_t *abb_crear(abb_comparador comparador)
{
	if(!comparador){
		return NULL;
	}

	abb_t *abb = calloc(1, sizeof(abb_t));
	if(!abb){
		return NULL;
	}

	abb->comparador = comparador;

	return abb;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{	
	if(!arbol){
		return NULL;
	}

	arbol->nodo_raiz = insertar_rec(arbol->nodo_raiz, nodo_crear(elemento), arbol->comparador);

	arbol->tamanio++;
	return arbol;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	return elemento;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if(!arbol || !elemento || !arbol->nodo_raiz){
		return NULL;
	}

	nodo_abb_t *nodo_actual = arbol->nodo_raiz;

	while(nodo_actual){
		int comparacion = arbol->comparador(elemento, nodo_actual->elemento);

		if(comparacion == 0){
			return nodo_actual->elemento;
		}

		else if(comparacion < 0){
			nodo_actual = nodo_actual->izquierda;
		}

		else{
			nodo_actual = nodo_actual->derecha;
		}
	}

	return NULL;
}

bool abb_vacio(abb_t *arbol)
{
	if(arbol->tamanio != 0 || !arbol){
		return false;
	}
	return true;
}

size_t abb_tamanio(abb_t *arbol)
{	
	if(!arbol){
		return 0;
	}
	return arbol->tamanio;
}

void abb_destruir(abb_t *arbol)
{
	if(!arbol){
		return;
	}

	destruir_todo_rec(arbol, NULL, arbol->nodo_raiz);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if(!arbol){
		return;
	}

	destruir_todo_rec(arbol, destructor, arbol->nodo_raiz);
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if(!arbol || !funcion){
		return 0;
	}

	size_t contador = 0;

	if(recorrido == INORDEN){
		con_cada_elemento_inorden(arbol->nodo_raiz, funcion, aux, &contador);
	}
	else if(recorrido == PREORDEN){
		con_cada_elemento_preorden(arbol->nodo_raiz, funcion, aux, &contador);
	}

	else if(recorrido == POSTORDEN){
		con_cada_elemento_postorden(arbol->nodo_raiz, funcion, aux, &contador);
	}

	else{
		return 0;
	}

	return contador;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	return 0;
}
