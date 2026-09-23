Este proyecto ha sido creado como parte del currículo de 42 por <login1>.

Codexion
Descripción

Codexion es un proyecto de concurrencia desarrollado en C como parte del currículo de 42.

El objetivo del proyecto es simular un grupo de personas programando simultáneamente y compitiendo por un número limitado de dongles USB. Cada persona está representada por un hilo POSIX y necesita adquirir dos dongles para poder compilar.

Durante la simulación, cada persona alterna entre tres estados:

Compiling — necesita dos dongles simultáneamente.

Debugging — no utiliza dongles.

Refactoring — no utiliza dongles.

Después de refactorizar, la persona vuelve a intentar adquirir los dongles para comenzar una nueva compilación.

El programa debe coordinar correctamente todos los hilos, evitando condiciones de carrera, interbloqueos y accesos incorrectos a los recursos compartidos.

La simulación termina cuando:

una persona se agota (burned out), o

todas las personas han completado el número de compilaciones requerido.

El proyecto también implementa dos políticas de planificación para gestionar las solicitudes de los dongles:

FIFO (First In, First Out): se atienden las solicitudes según su orden de llegada.

EDF (Earliest Deadline First): se prioriza la solicitud cuyo deadline de agotamiento está más próximo.

Características

Un hilo POSIX (pthread) por persona.

Un hilo monitor independiente.

Gestión de dongles mediante mutexes.

Variables de condición para coordinar los hilos.

Cooldown obligatorio de los dongles después de ser liberados.

Planificación mediante FIFO y EDF.

Implementación de una cola de prioridad mediante un heap.

Detección de agotamiento.

Serialización de los mensajes de salida.

Gestión y liberación de memoria dinámica.

Sin variables globales.

Estructura del proyecto
codexion/
├── README.md
└── coders/
    ├── Makefile
    ├── codexion.h
    ├── main.c
    ├── clean.c
    ├── dongle.c
    ├── monitor.c
    ├── request.c
    ├── routine.c
    ├── set_heap.c
    ├── set_hub.c
    ├── utils.c
    └── utils2.c

Archivos principales

main.c — punto de entrada del programa y gestión inicial de la simulación.

set_hub.c — inicialización de las estructuras principales del programa.

routine.c — rutina ejecutada por los hilos de las personas.

dongle.c — gestión de los dongles y de su disponibilidad.

request.c — gestión de las solicitudes de acceso a los dongles.

set_heap.c — implementación de la estructura heap utilizada para la planificación.

monitor.c — monitorización de los deadlines y detección de agotamiento.

clean.c — liberación de memoria y destrucción de recursos de sincronización.

utils.c y utils2.c — funciones auxiliares.

codexion.h — estructuras, prototipos y definiciones compartidas.

Makefile — compilación del proyecto.

Instrucciones
Compilación

Desde el directorio coders/:

make


El proyecto debe compilarse utilizando:

-Wall -Wextra -Werror -pthread


También están disponibles las reglas habituales:

make clean
make fclean
make re

Ejecución

La sintaxis del programa es:

./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler


Por ejemplo:

./codexion 5 800 200 200 200 3 10 fifo


O utilizando EDF:

./codexion 5 800 200 200 200 3 10 edf


Todos los argumentos son obligatorios.

Argumentos
Argumento	Descripción
number_of_coders	Número de personas y de dongles
time_to_burnout	Tiempo máximo que una persona puede permanecer sin comenzar una nueva compilación
time_to_compile	Tiempo necesario para compilar
time_to_debug	Tiempo dedicado a depurar
time_to_refactor	Tiempo dedicado a refactorizar
number_of_compiles_required	Número de compilaciones que debe completar cada persona
dongle_cooldown	Tiempo durante el cual un dongle permanece inutilizable después de ser liberado
scheduler	Política utilizada: fifo o edf

Los tiempos se expresan en milisegundos.

Funcionamiento

Cada persona está representada mediante un hilo.

El ciclo normal de una persona es:

        ┌──────────────────────┐
        │ Intentar adquirir    │
        │ dos dongles          │
        └──────────┬───────────┘
                   │
                   ▼
        ┌──────────────────────┐
        │      COMPILING       │
        │  mantiene 2 dongles  │
        └──────────┬───────────┘
                   │
                   ▼
        ┌──────────────────────┐
        │ Liberar los dongles  │
        └──────────┬───────────┘
                   │
                   ▼
        ┌──────────────────────┐
        │      DEBUGGING       │
        └──────────┬───────────┘
                   │
                   ▼
        ┌──────────────────────┐
        │     REFACTORING      │
        └──────────┬───────────┘
                   │
                   └──────────────► volver a solicitar dongles


Las personas no se comunican directamente entre ellas. La coordinación se realiza mediante los mecanismos de sincronización y las estructuras compartidas de la simulación.

Scheduling
FIFO

Con fifo, las solicitudes se atienden según el orden en el que fueron realizadas.

La solicitud que llega primero obtiene prioridad sobre las solicitudes posteriores.

Esto permite implementar un sistema de espera ordenado y evitar que una solicitud permanezca indefinidamente detrás de otras solicitudes posteriores.

EDF

Con edf, la prioridad se determina utilizando el deadline de agotamiento de cada persona:

deadline = last_compile_start + time_to_burnout


La persona cuyo deadline está más próximo recibe mayor prioridad.

El heap se utiliza para mantener las solicitudes ordenadas según la política de planificación correspondiente.

Blocking cases handled
Deadlock

La adquisición de recursos compartidos se coordina mediante mutexes y una política de planificación.

El objetivo es evitar situaciones en las que varios hilos queden bloqueados indefinidamente esperando recursos que están siendo retenidos por otros hilos.

La solución también tiene en cuenta las condiciones clásicas de Coffman asociadas a los interbloqueos:

Mutual exclusion.

Hold and wait.

No preemption.

Circular wait.

Starvation

La planificación de las solicitudes evita que una persona pueda quedar permanentemente relegada mientras otras personas reciben continuamente los dongles.

FIFO utiliza el orden de llegada de las solicitudes, mientras que EDF utiliza el deadline de agotamiento.

Dongle cooldown

Cuando una persona termina de compilar, los dongles utilizados no están inmediatamente disponibles.

Cada dongle debe respetar el tiempo especificado por dongle_cooldown antes de poder ser adquirido de nuevo.

Burnout detection

Existe un hilo monitor separado encargado de comprobar los deadlines de las personas.

Cuando una persona supera su tiempo máximo sin comenzar una nueva compilación, la simulación debe detenerse y se imprime:

timestamp X burned out


El mensaje de agotamiento debe producirse dentro de la tolerancia establecida por el subject.

Race conditions

Los datos compartidos son protegidos mediante mecanismos de sincronización adecuados.

Los mutexes evitan que varios hilos modifiquen simultáneamente el mismo estado compartido.

Las variables de condición permiten que los hilos esperen a que un recurso o una determinada condición esté disponible sin realizar una espera activa innecesaria.

Logging

Los mensajes de salida están protegidos para evitar que dos hilos escriban simultáneamente y mezclen sus mensajes.

Los estados se imprimen utilizando el formato definido por el subject:

timestamp X has taken a dongle
timestamp X is compiling
timestamp X is debugging
timestamp X is refactoring
timestamp X burned out

Thread synchronization mechanisms

El proyecto utiliza primitivas POSIX para coordinar los diferentes hilos.

pthread_mutex_t

Los mutexes protegen recursos y estados compartidos.

Se utilizan para evitar accesos simultáneos incompatibles a estructuras como los dongles, el estado de la simulación y la salida del programa.

Un patrón de acceso típico es:

pthread_mutex_lock(&mutex);

/* acceso al recurso compartido */

pthread_mutex_unlock(&mutex);


Esto garantiza que la sección protegida sea ejecutada de forma mutuamente exclusiva.

pthread_cond_t

Las variables de condición permiten que un hilo espere hasta que una determinada condición se cumpla.

Por ejemplo, un hilo que necesita un dongle puede esperar mientras el recurso no esté disponible:

pthread_cond_wait(&cond, &mutex);


Cuando el estado del recurso cambia, los hilos que están esperando pueden ser notificados.

Comunicación entre los coders y el monitor

Los hilos de las personas actualizan información como su estado y el momento de su última compilación.

El monitor utiliza esta información para comprobar si alguna persona ha alcanzado su deadline.

El acceso concurrente a estos datos debe estar protegido para evitar condiciones de carrera entre los hilos de las personas y el monitor.

Memory management

Toda la memoria reservada dinámicamente durante la ejecución debe liberarse correctamente.

La limpieza incluye:

estructuras de las personas;

estructuras de los dongles;

estructuras utilizadas por el scheduler;

memoria utilizada por el heap;

recursos de sincronización;

cualquier otra memoria reservada dinámicamente.

La función de limpieza centraliza la destrucción de los recursos para evitar memory leaks.

Output example

Un ejemplo de salida válida es:

0 1 has taken a dongle
1 1 has taken a dongle
1 1 is compiling
201 1 is debugging
401 1 is refactoring
402 2 has taken a dongle
403 2 has taken a dongle
403 2 is compiling
603 2 is debugging
803 2 is refactoring
1204 3 burned out


Los timestamps representan el tiempo transcurrido desde el comienzo de la simulación y están expresados en milisegundos.

Resources

POSIX Threads documentation (pthread).

pthread_mutex_t y mecanismos de exclusión mutua.

pthread_cond_t y variables de condición.

Documentación de gettimeofday().

Documentación de usleep().

Conceptos de concurrencia y sincronización.

Problemas clásicos de deadlock, starvation y race conditions.

Priority queues y binary heaps.

Algoritmos de planificación FIFO y Earliest Deadline First.

AI usage

La inteligencia artificial se ha utilizado como herramienta de apoyo durante el desarrollo del proyecto.

Su utilización puede incluir:

Comprender conceptos relacionados con concurrencia y sincronización.

Analizar posibles condiciones de carrera y deadlocks.

Obtener explicaciones sobre pthreads, mutexes y variables de condición.

Revisar ideas de organización del código.

Ayudar a diseñar y analizar estructuras de datos como heaps y colas de prioridad.

Generar ideas para casos de prueba y situaciones límite.

Ayudar a detectar posibles problemas durante la depuración.

Todo el código utilizado en el proyecto debe ser comprendido, revisado y probado por el autor antes de incorporarlo a la solución final.

Evaluation considerations

Durante la evaluación se debe poder explicar:

Cómo se crean y gestionan los hilos.

Cómo se protegen los dongles.

Cómo funciona el cooldown.

Cómo se evita el deadlock.

Cómo funciona FIFO.

Cómo funciona EDF.

Cómo se implementa el heap.

Cómo funciona el monitor.

Cómo se detecta un burnout.

Cómo se sincroniza el acceso a los datos compartidos.

Cómo se serializan los logs.

Cómo se libera correctamente toda la memoria.