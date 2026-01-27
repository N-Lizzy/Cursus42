*Este proyecto ha sido creado como parte del currículo de 42 por aruiznav*

## DESCRIPCIÓN.
`get_next_line` es un proyecto que tiene como objetivo escribir una función capaz de leer un archivo línea a línea utilizando únicamente las funciones `read`, `malloc` y `free`. Debe de devolver cada línea terminada en `\n` (salto de línea) cuando exista y devolver `NULL` cuando no haya más contenido que leer o haya algún error. El comportamiento debe ser el correcto tanto leyendo desde archivos como desde la entrada estándar.

Esta función será llamada repetidamente en un bucle, permitiendo leer el contenido completo del descriptor de archivo, línea por línea, hasta llegar al final.


## INSTRUCCIONES
Para poder compilar el proyecto se usa:
    `cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c`

Para definir el tamaño del buffer manualmente:
    `cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c`

Para ejecutar el programa:
    `./a` ("a" siendo el nombre generico si no le pones uno)


## RECURSOS
- Videos explicativos: Diferentes videos que presentan el proyecto a nivel general y explican cómo empezar, ayudándome a comprender la lógica y la estructura del `get_next_line`.
- Uso de la IA: La IA se utilizó como una herramienta de apoyo para:
	1. Revisar y corregir errores que no había detectado manualmente.
	2. Identificar y solucionar posibles leaks de memoria.
	3. Sugerir mejoras en la organización del código y en la gestión del buffer.

## EXPLICACIÓN Y JUSTIFICACIÓN DEL ALGORITMO
El algoritmo se basa en gestionar un buffer estático que conserva los datos sobrantes entre llamadas a la función. Esto permite que `get_next_line` pueda continuar leyendo exactamente donde lo dejó, sin perder información y sin necesidad de variables globales.

- Uso de un buffer estático:
Este buffer conserva la parte de la lectura que aún no se ha devuelto como línea. Evita releer el archivo.

- Lectura incremental:
Mediante read_file, se leen fragmentos del archivo del tamaño `BUFFER_SIZE` hasta que aparece un salto de línea o hasta que `read()` devuelve 0. Cada lectura se concatena al buffer mediante `join_and_free`, evitando pérdidas de memoria.

- Extracción de la línea:
`save_line` identifica dónde termina la línea (hasta el `\n` incluido si existe) y devuelve una copia nueva con memoria justa. Esto garantiza que cada llamada retorna exactamente una línea bien formada.

- Actualización del buffer:
`next_line` descarta la parte ya devuelta y conserva únicamente el contenido restante. Si no queda nada, libera la memoria del buffer. Así se mantiene la eficiencia y se evita malgastar memoria.

- VENTAJAS DEL ALGORITMO
	1. Minimiza llamadas a `read()`.
	2. Evita fugas de memoria.
	3. Modular, limpio y fácil de depurar.
	4. Funciona con cualquier `BUFFER_SIZE`.
	5. Sin problemas ante archivos grandes, vacíos o sin saltos de línea.