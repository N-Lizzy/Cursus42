*Este proyecto ha sido creado como parte del currículo de 42 por aruiznav*

## DESCRIPCIÓN.
`push_swap` es un proyecto cuyo objetivo es desarrollar un programa capaz de recibir una cantidad variable de números enteros y ordenarlos de menor a mayor, utilizando la menor cantidad de movimientos posible, es decir, de la forma más eficiente posible.

Para lograrlo, el estudiante únicamente puede utilizar un algoritmo de ordenación de su elección, un conjunto limitado de instrucciones y dos pilas como estructuras de datos principales. Dichas instrucciones son:
- `sa`, `sb` y `ss`: intercambiar los dos primeros elementos de la pila.
- `pa` y `pb`: mover el primer elemento de una pila a otra.
- `ra`, `rb` y `rr`: rotar la pila hacia arriba (el primer elemento se convierte en el último).
- `rra`, `rrb` y `rrr`: rotar la pila hacia abajo (el último elemento se convierte en el primero)


## INSTRUCCIONES
- #### Compilación:
    ```
    make
    ```
- #### Limpiar los archivos .o:
    ```
    make clean
    ```
- #### Limpiar todo incluyendo el ejecutable:
    ```
    make fclean
    ```
- #### Ejecución del programa:
    ```
    ./push_swap "a b c ..."
    ```
	(Donde 'a', 'b', 'c' ... son los numeros que uno quiera poner separados por espacios.)
- #### Ejecución del checker
    ```
    ./checker_linux a b c ...
    ```
    (Donde 'a', 'b', 'c' ... son los numeros que uno quiera poner separados por espacios.)
- #### Ejecución del programa junto con el checker:
    ```
    ARG="a b c ..."; ./push_swap $ARG | ./checker_linux $ARG
    ```
- #### Ejecución conjunta con números aleatorios:
    ```
    ARG=$(seq 1 100 | shuf | tr '\n' ' '); ./push_swap $ARG | ./checker_linux $ARG
    ```

El programa valida la entrada y muestra "Error" si:
- Hay números duplicados.
- Los argumentos no son números enteros válidos.
- Los números están fuera del rango de un int.
- No se proporcionan argumentos.
- Se proporciona más de un argumento.

## RECURSOS
- Videos explicativos: Diferentes videos que presentan el proyecto a nivel general y explican los distintos tipos de algoritmos de ordenación, ayudándome a comprender la lógica y la estructura del `push_swap`.
- Uso de la IA: La IA se utilizó como una herramienta de apoyo para:
	1. Revisar y corregir errores que no había detectado manualmente.
	2. Resolver algunas dudas sobre los algoritmos y alguna que otra sobre las listas.
