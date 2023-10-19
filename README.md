# TDA ABB

## Repositorio de Sebastián Loe - 110106 - sloe@fi.uba.ar

- Para compilar:

```bash
gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g src/*.c pruebas_chanutron.o -o pruebas_chanutron
```

- Para ejecutar:

```bash
./pruebas_chanutron || ./pruebas_alumno
```

- Para ejecutar con valgrind:
```bash
make valgrind-chanutron || make
```
---
##  Funcionamiento

Este trabajo está dedicado al segundo tipo de Tipo de Datos Abstractos que vimos en esta cursada, llamado ABB (Árbol Binario de Búsqueda). Al igual que con Lista, en 'abb.c' se crea un árbol, y luego se introducen las operaciones previamente vistas en Lista, como insertar, quitar, buscar, entre otros, haciendo uso de reserva y liberación de memoria a la hora de insertar y de quitar, o de crear y destruir.
En una explicación más específica del funcionamiento de las funciones del trabajo, encontramos las siguientes funciones principales encontradas en 'abb.h' e implementadas en 'abb.c':

- abb_crear: crea un árbol vacío reservando memoria y devuelve el árbol creado.

- abb_insertar: inserta de manera recursiva un nuevo nodo en el árbol según las reglas del Árbol Binario de Búsqueda (explicado mejor en las preguntas teóricas). Devuelve el árbol con el nuevo elemento.

- abb_quitar: quita de manera recursiva un nodo existente en el árbol y devuelve el elemento del nodo extraido. Libera la memoria del nodo extraido.

- abb_buscar: busca iterativamente un elemento perteneciente a un nodo del árbol, igual a otro elemento pasado por parámetro. Devuelve el elemento del nodo o NULL si no lo encuentra.

- abb_vacio: devuelve true si y solo si el árbol se encuentra vacío (arbol->tamanio == 0).

- abb_tamanio: devuelve el tamaño del árbol existente.

- abb_destruir: recorre el arbol de manera recursiva liberando la memoria asignada a cada nodo y luego libera la memoria asignada al árbol en si. 

- abb_destruir_todo: realiza el mismo procedimiento que abb_destruir pero se aplica una función pasada por parámetro a cada nodo del árbol siempre y cuando esta exista.

- abb_con_cada_elemento: recorre el árbol iterativamente y aplica una función pasada por parámetro a cada elemento de cada nodo del árbol, siguiendo como recorrido lo impuesto por el parámetro 'abb_recorrido recorrido' en la firma de la función.

- abb_recorrer: recorre todo el árbol iterativamente siguiendo el mismo recorrido, como en la función anterior, y llena un vector con los elementos de cada nodo del árbol.


Cada una de estas funciones contiene funciones secundarias con el fin de modularizar el código y/o para poder simplemente completar la implementación de las funciones. En el caso de las funciones que recorran el árbol recursivamente, fue necesario crear funciones que realicen este proceso para facilitar el entendimiento del código.

---

## Respuestas a las preguntas teóricas

-   Explique teóricamente qué es una árbol, árbol binario y árbol
    binario de búsqueda. Explique cómo funcionan, cuáles son sus operaciones básicas
    (incluyendo el análisis de complejidad de cada una de ellas) y por qué es
    importante la distinción de cada uno de estos diferentes tipos de
    árboles. Ayúdese con diagramas para explicar.


Un árbol es un Tipo de Dato Abstracto que se utilizan para almacenar información de manera jerárquica o categórica. Si bien cada tipo de árbol comparten similitudes entre sí, hay algunas diferencias que no deben dejar de notarse:

1. Un **Árbol** contiene nodos que a su vez contienen elementos y punteros a otros nodos (hijos). El primer nodo de un árbol (cualquier tipo de árbol) se llama 'raíz', y aquellos nodos que no tengan hijos, se llaman hojas. Este tipo de árboles puede tener cualquier número de hijos (diferente a los binarios) y sus elementos pueden estar organizados de cualquier forma (diferente al binario de búsqueda).

2. Un **Árbol Binario** es similar en cuanto a estructuración que los árboles comunes, pero estos tienen restricciones en cuanto a la cantidad de hijos que puedan tener. Los Árboles Binarios están limitados a tener 2 hijos, uno izquiero y otro derecho, aunque no es necesario que se ordenen de alguna forma en específico. Obviamente, estos árboles pueden tener un hijo o cero, y no necesariamente dos hijos.

<div align="center">
<img width="70%" src="img/arbol1.svg">
</div>

3. Un **Árbol Binario de Búsqueda** es muy idéntico al árbol binario común, solo que se le aplica una regla de organización de elementos. Para todos los nodos, los nodos cuyos elementos sean menores al elemento del primer nodo, se ubican a la izquierda del mismo. Los elementos mayores se ubican a la derecha. Esta forma de organizar los datos supone una facilidad mucho mayor a la hora de buscar elementos en el árbol. 

<div align="center">
<img width="70%" src="img/arbol2.svg">
</div>


Para las operaciones básicas de estos árboles (establecidas crear, insertar, quitar, buscar, recorrer y destruir), muchas de estas suponen lo ya explicado en el funcionamiento del programa, con lo cual solo se explicarán aquellas operaciones que tengan cambios importantes.

Para insertar, las diferencias están entre los árboles binarios de búsqueda y el resto, ya que estos siguen reglas específicas según el valor del elemento a insertar, como ya fue explicado anteriormente. 
Para quitar sucede algo similar ya que en los árboles binarios de búsqueda deben considerarse los casos en los que un nodo no tenga hijos, o tenga 1, o 2. 
Para buscar también hay una gran diferencia solo con los árboles de búsqueda, ya que para los otros dos, buscar un elemento supone recorrer todo el árbol hasta encontrarlo, mientras que para el primero se sigue la propiedad de ordenamiento que ya fue explicada y puede verse en el mismo programa. Esto es, se compara el elemento buscado con el del nodo. Si el buscado es mayor al del nodo, se procede al nodo derecho. De lo contrario se procede al izquierdo.

El resto de funciones no explicadas implican que no proponen amplias (o ninguna) diferencias más allá de lo explicado en el funcionamiento.

En cuanto a las complejidades:

- En un árbol común las operaciones de insertar, eliminar y buscar es O(n) ya que no se sigue ninguna regla específica.
- En un árbol binario, estas complejidades suelen ser O(h), donde h es la altura del árbol. Si el árbol está desbalanceado, en el peor de los casos, la complejidad de estas operaciones puede trasladarse a O(n).
- En un árbol binario de búsqueda, la complejidad de estas operaciones es de O(h). Pero, como vimos en clase, en un árbol balanceado, como los árboles rojo-negro, la complejidad pasa a ser O(log n).



-   Explique su implementación y decisiones de diseño (por ejemplo, si
    tal o cuál funciones se plantearon de forma recursiva, iterativa o
    mixta y por qué, que dificultades encontró al manejar los nodos y
    punteros, reservar y liberar memoria, etc).

Muchas de las funciones implementadas donde fue necesario recorrer el árbol fueron implementadas de forma recursiva ya que agilizaba y simplificaba los procesos y hacían el código más simple de leer. Sin embargo, la función 'abb_buscar' fue implementada de manera iterativa ya que hacerlo iterativamente hubiera supuesto crear una función secundaria que resuelva el problema (como con insertar, quitar, recorrer...), haciendo que el código sea un poco más tedioso de leer o entender. Distinto al resto de funciones, consideré que la de buscar era más simple que las otras, y por ende no acortaba código o "ahorraba" líneas por hacerlo de forma recursiva. 

En cuanto a dificultades, sin lugar a dudas la función mas difícil de comprender fue la de 'abb_quitar'. Si bien la función en sí se compone de 6 líneas, 'quitar_rec' demuestra la complejidad de la función. En detalle, en esta función se chequea si la comparación es mayor, menor o igual a 0. Que sea igual a 0 supone que se llegó al elemento que se quiere eliminar, y es aquí donde debe emplearse la lógica para entender qué hacer paso a paso. 