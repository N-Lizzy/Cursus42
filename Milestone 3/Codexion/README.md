*Este proyecto ha sido creado como parte del currículo de 42 por aruiznav*

## DESCRIPCIÓN.
Codexion es un proyecto de concurrencia desarrollado en C como parte del currículo de 42.

El objetivo del proyecto es simular un grupo de personas programando simultáneamente y compitiendo por un número limitado de dongles USB. Cada persona está representada por un hilo POSIX y necesita adquirir dos dongles para poder compilar.

Durante la simulación, cada persona alterna entre tres estados:

1. Compiling — necesita dos dongles simultáneamente

2. Debugging — no utiliza dongles.

3. Refactoring — no utiliza dongles.

Después de refactorizar, la persona vuelve a intentar adquirir los dongles para comenzar una nueva compilación.

El programa debe coordinar correctamente todos los hilos, evitando condiciones de carrera, interbloqueos y accesos incorrectos a los recursos compartidos.

La simulación termina cuando: una persona se agota (burned out), o todas las personas han completado el número de compilaciones requerido.

El proyecto también implementa dos políticas de planificación para gestionar las solicitudes de los dongles:

- FIFO (First In, First Out): se atienden las solicitudes según su orden de llegada.

- EDF (Earliest Deadline First): se prioriza la solicitud cuyo deadline de agotamiento está más próximo.

## INSTRUCCIONES

### Compilación
Desde el directorio coders/:
```make```

El proyecto debe compilarse utilizando:
```-Wall -Wextra -Werror -pthread```

También están disponibles las reglas habituales:
```make clean```
```make fclean```
```make re```

### Ejecución
La sintaxis del programa es:

```
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

Por ejemplo:
```
./codexion 5 800 200 200 200 3 10 fifo
```

O utilizando EDF:

```
./codexion 5 800 200 200 200 3 10 edf
```

Todos los argumentos son obligatorios.

### Argumentos
| Argumento                   | Descripción                                                                       |
|-----------------------------|-----------------------------------------------------------------------------------|
| number_of_coders            | Número de personas y de dongles                                                   |
| time_to_burnout             | Tiempo máximo que una persona puede permanecer sin comenzar una nueva compilación |
| time_to_compile             | Tiempo necesario para compilar                                                    |
| time_to_debug               | Tiempo dedicado a depurar                                                         |
| time_to_refactor            | Tiempo dedicado a refactorizar                                                    |
| number_of_compiles_required | Número de compilaciones que debe completar cada persona                           |
| dongle_cooldown             | Tiempo durante el cual un dongle permanece inutilizable después de ser liberado   |
| scheduler                   | Política utilizada: fifo o edf                                                    |

Los tiempos se expresan en milisegundos.

## RECURSOS
- POSIX Threads documentation (pthread).

- pthread_mutex_t y mecanismos de exclusión mutua.

- pthread_cond_t y variables de condición.

- Documentación de gettimeofday().

- Documentación de usleep().

- Conceptos de concurrencia y sincronización.

- Problemas clásicos de deadlock, starvation y race conditions.

- Priority queues y binary heaps.

- Algoritmos de planificación FIFO y Earliest Deadline First.

## Blocking cases handled
### Deadlock
La adquisición de recursos compartidos se coordina mediante mutexes y una política de planificación.

El objetivo es evitar situaciones en las que varios hilos queden bloqueados indefinidamente esperando recursos que están siendo retenidos por otros hilos.

La solución también tiene en cuenta las condiciones clásicas de Coffman asociadas a los interbloqueos:

- Mutual exclusion.

- Hold and wait.

- No preemption.

- Circular wait.

### Starvation
La planificación de las solicitudes evita que una persona pueda quedar permanentemente relegada mientras otras personas reciben continuamente los dongles.

- FIFO utiliza el orden de llegada de las solicitudes.

- EDF utiliza el deadline de agotamiento.

### Dongle cooldown
Cuando una persona termina de compilar, los dongles utilizados no están inmediatamente disponibles.

Cada dongle debe respetar el tiempo especificado por dongle_cooldown antes de poder ser adquirido de nuevo.

### Burnout detection

Existe un hilo monitor separado encargado de comprobar los deadlines de las personas.

Cuando una persona supera su tiempo máximo sin comenzar una nueva compilación, la simulación debe detenerse y se imprime:

``` timestamp X burned out ```

El mensaje de agotamiento debe producirse dentro de la tolerancia establecida por el subject.

### Race conditions
Los datos compartidos son protegidos mediante mecanismos de sincronización adecuados.

Los mutexes evitan que varios hilos modifiquen simultáneamente el mismo estado compartido.

Las variables de condición permiten que los hilos esperen a que un recurso o una determinada condición esté disponible sin realizar una espera activa innecesaria.

## Thread synchronization mechanisms
El proyecto utiliza primitivas POSIX para coordinar los diferentes hilos.

### pthread_mutex_t

Los mutexes protegen recursos y estados compartidos.

Se utilizan para evitar accesos simultáneos incompatibles a estructuras como los dongles, el estado de la simulación y la salida del programa.

Un patrón de acceso típico es:

```
pthread_mutex_lock(&mutex);

/* acceso al recurso compartido */

pthread_mutex_unlock(&mutex);

```

### pthread_cond_t

Las variables de condición permiten que un hilo espere hasta que una determinada condición se cumpla.

Por ejemplo, un hilo que necesita un dongle puede esperar mientras el recurso no esté disponible:

```
pthread_cond_wait(&cond, &mutex);
```

Cuando el estado del recurso cambia, los hilos que están esperando pueden ser notificados.

### Comunicación entre los coders y el monitor
Los hilos de las personas actualizan información como su estado y el momento de su última compilación.

El monitor utiliza esta información para comprobar si alguna persona ha alcanzado su deadline.

El acceso concurrente a estos datos debe estar protegido para evitar condiciones de carrera entre los hilos de las personas y el monitor.