# Práctica 01. Simulación de Máquina de Turing
* **Autor:** Adrián Pérez Poleo
* **Correo:** alu0101635224@ull.edu.es

## Descripción del proyecto
Este proyecto implementa un simulador orientado a objetos en C++ para una Máquina de Turing Determinista Multicinta.

### Modelo Implementado
Antes de mostrar el código se desarrolla brevemente en qué consiste el modelo de computación que se ha implementado.

Una máquina de Turing determinista multicinta se define como una 7-tupla:

$$M = (Q, \Sigma, \Gamma, q_0, b, F, \delta)$$

Donde:
* **$Q$**: Conjunto finito y no vacío de estados.
* **$\Sigma$**: Alfabeto de entrada (donde el símbolo blanco $b \notin \Sigma$).
* **$\Gamma$**: Alfabeto de la cinta (donde $\Sigma \subset \Gamma$ y $b \in \Gamma$).
* **$q_0 \in Q$**: Estado inicial.
* **$b \in \Gamma$**: Símbolo blanco que representa las celdas vacías de la cinta.
* **$F \subseteq Q$**: Conjunto de estados finales o de aceptación.
* **$\delta: Q \times \Gamma^k \to Q \times \Gamma^k \times \{L, R, S\}^k$**: Función de transición (donde $k$ es el número de cintas).

**Criterio de Aceptación:** Una cadena $w \in \Sigma^*$ es aceptada por la máquina si, tras procesar la entrada realizando las transiciones correspondientes, la máquina se detiene y su estado actual pertenece al conjunto de estados de aceptación $F$.

> Como podemos ver, de las posibles implementaciones, hemos optado por:
> - Máquina de Turing con escritura y movimiento simultáneos
> - Máquina de Turing que incluye la posibilidad de no movimiento (S)
> - Máquina de Turing con cinta infinita en ambas direcciones.
>
>He querido que el modelo sea lo más similar posible al utilizado en clase para los ejercicios.

## Estructura del Proyecto
El código sigue la estructura estándar utilizada para desarrollar proyectos con CMake.

```bash
turing-machine/
├── CMakeLists.txt
├── README.md
├── examples
│   ├── Ejemplo1_MT.txt
│   ├── Ejemplo2_MT.txt
│   ├── Tarea1.txt
│   ├── Tarea2.txt
├── include
│   ├── alphabet.h
│   ├── multitape.h
│   ├── program_options.h
│   ├── state_manager.h
│   ├── tape.h
│   ├── transition_table.h
│   ├── turing_machine.h
│   ├── turing_machine_configuration_reader.h
│   ├── turing_machine_error.h
│   └── types.h
└── src
    ├── main.cc
    ├── multitape.cc
    ├── program_options.cc
    ├── tape.cc
    ├── transition_table.cc
    ├── turing_machine.cc
    └── turing_machine_configuration_reader.cc
```

## Compilación y Ejecución
Para poder compilar el proyecto es necesario disponer de:
- Compilador C++ con soporte para **C++20**
- **CMake 3.20** o superior

### Pasos a seguir para la compilación
```bash
# Crear un directorio para compilar
mkdir build && cd build

# Generar los archivos para construir el proyecto
cmake ..

# Compilar el proyecto
make
```

De esta manera se generará el ejecutable `turing-machine-simulator` dentro del directorio `build/`.

## Opciones de Línea de Comandos

El programa debe recibir el siguiente parámetro obligatorio en la línea de comandos:
- `-config <fichero>`: Nombre del [fichero](#formato-del-fichero-de-configuración) que contiene la configuración de la máquina de Turing.

### Ejemplo de Ejecución
```bash
./turing-machine-simulator -config ../examples/Ejemplo1_MT.txt
```

## Formato del Fichero de Configuración
El fichero de configuración acepta líneas vacías y comentarios que comienzan por `#`. El formato esperado es el siguiente, respetando el orden estricto de las definiciones:
```bash
# Comentarios
q0 q1 q2                # conjunto de estados Q
0 1                     # alfabeto de entrada Σ
0 1 . a b               # alfabeto de cinta Γ
q0                      # estado inicial
.                       # símbolo blanco
q2                      # conjunto de estados de aceptación F
1                       # número de cintas (k)
q0 0 q1 0 R             # transiciones: estado_actual, [simbolos_leidos], estado_siguiente, [simbolos_escritos, movimientos]
...                     # cada una de las transiciones en una línea distinta
```

## Arquitectura del Software
El diseño del programa sigue el paradigma de Programación Orientada a Objetos.

![](doc/class_diagram.png)

### Descripción de los principales elementos:
- `TuringMachine`: Clase principal que simula el comportamiento del autómata, coordinando las cintas, los estados y las transiciones.
- `Multitape`: Clase que gestiona múltiples instancias de la cinta (`Tape`), permitiendo simulaciones de Máquinas de Turing multicinta.
- `Tape`: Abstracción de una cinta infinita de la máquina. Implementa la lectura, escritura y el movimiento del cabezal (`L`, `R`, `S`).
- `StateManager`: Clase encargada de almacenar y actualizar el estado actual de la máquina, validando si se encuentra en un estado de aceptación.
- `TransitionTable`: Clase que almacena y busca las reglas de transición definidas en la configuración, mapeando un estado y un vector de símbolos leídos a una acción resultante.
- `TuringMachineConfigurationReader`: Clase especializada en analizar sintácticamente (parser) el fichero de configuración, ignorando comentarios y validando sus componentes.
- `Alphabet`: Clase que valida los símbolos permitidos durante la inserción y modificación de la cinta, evitando errores con caracteres no reconocidos.

## Máquinas de Turing realizadas

### Máquina 01
![](doc/MT01.png)

- Imagen: `doc/MT01.png`
- Fichero de configuración: `examples/Tarea1.txt`

A continuación, se muestra brevemente el sentido de cada estado.
- `q0`: Lee las a's y las copia en la cinta 2.
- `q1`: Lee las b's y las copia en la cinta 3.
- `q2`: Va recorriendo a la vez las cintas 2 y 3, comparando el número de a's y b's.
- `q3`: Estado de aceptación. Se llega cuando hay tantas a's como b's o más a's que b's.

## Máquina 02
![](doc/MT02.png)

- Imagen: `doc/MT02.png`
- Fichero de configuración: `examples/Tarea2.txt`

A continuación, se muestra brevemente el sentido de cada estado.
- `q0`: Copia las a's en la cinta 2 y las b's en la cinta 3. Además, elimina el contenido de la cinta de entrada (cinta 1).
- `q1`: Este estado indica que ya se han almacenado las a's y b's en sus respectivas cintas. La cabeza de la cinta 2 apunta a la última a introducida (si la hay). Si todo es vacío (no hay a's) se escribe un 0 en la cinta 1, en caso contrario se escribe un 1.
- `q2`: Mientras hayan a's, se escriben 1's en la cinta 1 (de derecha a izquierda). Tras el último 1 (la última a) se escribe un símbolo vacío.
- `q3`: De forma similar al estado `q1`, con el cabezal de la cinta 3 en la última b introducida, se añade un 1 si la hay o un 0 si no hubieron b's en la entrada.
- `q4`: Mientras hayan b's guardadas, se guardan 1's en la cinta 1 (de derecha a izquierda).
- `q5`: Estado de aceptación. Todos los símbolos han sido leídos y la cabeza apunta al primer símbolo de la cinta 1 (que fue la de entrada y ahora contiene la solución).
