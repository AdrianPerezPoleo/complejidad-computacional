# Práctica 01. Simulación de Autómato de Pila
* **Autor:** Adrián Pérez Poleo
* **Correo:** alu0101635224@ull.edu.es

## Descripción del proyecto
Este proyecto implementa un simulador orientado a objetos en C++ para un Autómata de Pila No Determinista por **vaciado de pila** (APv).

### Modelo Implementado
Antes de mostrar el código se desarrolla brevemente en qué consiste el modelo de computación que se ha implementado.

Un autómata de pila por vaciado de pila se define formalmente como una 6-tupla:

$$M = (Q, \Sigma, \Gamma, q_0, s, \delta)$$

Donde:
* **$Q$**: Conjunto finito y no vacío de estados.
* **$\Sigma$**: Alfabeto de entrada (donde el símbolo vacío $\epsilon \notin \Sigma$).
* **$\Gamma$**: Alfabeto de la pila (donde el símbolo vacío $\epsilon \notin \Gamma$).
* **$s \in Q$**: Estado inicial.
* **$Z \in \Gamma$**: Símbolo inicial de la pila.
* **$\delta: Q \times (\Sigma \cup \{\epsilon\}) \times \Gamma \to \mathcal{P}(Q \times \Gamma^*)$**: Función de transición.

**Criterio de Aceptación:** Una cadena $w \in \Sigma^*$ es aceptada por el autómata si existe al menos un camino que consume completamente la entrada y deja la pila totalmente vacía, independientemente del estado final en el que se encuentre. 

## Estructura del Proyecto
El código sigue la [estructura estándar](https://www.studyplan.dev/cmake/organizing-a-cpp-project) utilizada para desarrollar proyectos con CMake.

```bash
pushdown-automaton/
├── CMakeLists.txt
├── README.md
├── examples
│   ├── bad-configuration
│   │   ├── empty-states.txt
│   │   ├── invalid-alphabet-initialization.txt
│   │   ├── invalid-initial-state.txt
│   │   ├── invalid-stack-start.txt
│   │   ├── invalid-transition-initial-state.txt
│   │   └── invalid-transition-tape-symbol.txt
│   ├── configuration-1.txt
│   ├── configuration-2.txt
│   └── configuration-3.txt
├── include
│   ├── alphabet.h
│   ├── automaton_configuration_reader.h
│   ├── automaton_error.h
│   ├── automaton_stack.h
│   ├── program_options.h
│   ├── pushdown_automaton.h
│   ├── state_manager.h
│   ├── tape.h
│   ├── transition_table.h
│   └── types.h
└── src
    ├── automaton_configuration_reader.cc
    ├── automaton_stack.cc
    ├── main.cc
    ├── program_options.cc
    ├── pushdown_automaton.cc
    ├── tape.cc
    └── transition_table.cc
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

De esta manera se generará el ejecutable `pushdown_automaton_simulator` dentro del directorio `build/`.

## Opciones de Línea de Comandos

El programa debe recibir dos parámetros en la línea de comandos:
- `config <fichero>`: Nombre del [fichero](#formato-del-fichero-de-configuración) que contiene la configuración del autómata.
- `-trace <y|n>`: Activa o desactiva el modo traza paso a paso.

### Ejemplo de Ejecución
```bash
./pushdown_automaton_simulator -config ../examples/configuration-1.txt -trace y
```

## Formato del Fichero de Configuración
El fichero de configuración acepta lineas vacías y comentarios que comienzan por #. El formato que se debe recibir es:
```bash
# Comentarios
q1 q2 q3 …              # conjunto Q
a1 a2 a3 …              # conjunto Σ
A1 A2 A3 …              # conjunto Γ
q1                      # estado inicial
A1                      # símbolo inicial de la pila
q2 q3                   # conjunto F (solamente en el caso de APf)
q1 a A1 q2 A            # función de transición: (q2, A) ∈ δ (q1, a, A1)
...                     # cada una de las transiciones en una línea distinta
```

## Arquitectura del Software
El diseño del programa sigue el paradigma de Programación Orientada a Objetos.


### Descripción de los principales elementos:
- `Pushdown Automaton`: Clase principal que orquesta a las demás. Gestiona la lógica de evaluación utilizando una estrategia de búsqueda en profundidad.
- `AutomatonConfigurationReader`: Clase encargada de leer, filtrar los comentarios y analizar sintácticamente el fichero de configuración.
- `Tape`: Clase que representa la cinta de entrada  para poder abstraer la lectura y la comporbación del fin de cadena.
- `Automaton Stack`: Clase que abstrae la pila del autómata. Permite apilar cadenas de varios símbolos o no hacer nada en caso de recibir el símbolo vacío.
- `Alphabet`: Clase que encapsula la validación de símbolos que pertenecen o no a un alfabeto. También controla que no se añada el símbolo vacío.
- `TransitionTable`: Clase que almacena las transiciones, relacionando cada antecedente a uno o más posibles consecuentes.