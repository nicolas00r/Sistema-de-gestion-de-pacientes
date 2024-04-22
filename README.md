# Sistema de gestión pacientes
## Descripción 

Este programa permite a los usuarios gestionar la atención de clientes de un hospital. Tienen la opción de registrar nuevos pacientes, de asignar o modificar su prioridad según el estado en el que se encuentren, de ver la lista de espera en su totalidad, de indicar cuando se atiende el siguiente paciente y de ver las listas de personas de una cierta prioridad. La finalidad del programa es hacer más eficiente y sencilla la atención en los hospitales, para brindar una mejor atención a todas las personas.

## Cómo compilar y ejecutar

Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar [Repl.it](http://repl.it/) para una rápida configuración y ejecución. 

Sigue estos pasos para comenzar:

1. Visita [Repl.it](https://repl.it/).
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: `https://github.com/nicolas00r/Sistema-de-gestion-de-pacientes`.
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará un entorno de ejecución.
6. En el apartado "Configurate Repl", deberá modificar el comando de compilación, pegando el siguiente comando "gcc list.c main.c -Wno-unused-result -o main"
7. Presione el boton "Run" para compilar y ejecutar la aplicación.

## Funcionalidades

### Funcionando correctamente:

- Registrar pacientes, indicando su nombre, su edad y los síntomas presentados.
- Asignar o modificar la prioridad de los pacientes, donde si existe un cambio de prioridad, la lista de esta se reorganizará dependiendo de la hora de llegada del paciente.
- Ver la lista de espera de pacientes, ordenada por prioridad y hora de llegada.
- Atender al siguiente paciente, respetando el orden de prioridad y enseñando sus datos.
- Mostrar la lista de pacientes según la prioridad indicada.

### Problemas conocidos:

- En el registro de pacientes, no existe un filtro en el ingreso de datos. Esto quiere decir que si el usuario sobrepasa los 99 caracteres permitidos para el nombre y los síntomas del paciente, puede llevar a problemas en el registro de datos. De igual manera no existe un filtro para el ingreso de la edad, es decir, si en el ingreso de la antes mencionada, se reciben datos que no sean números, provocara fallos en el registro de la edad y de los síntomas.

### A mejorar:

- Trabajar más a fondo en la interfaz y experiencia de usuario, de manera que esta sea más amigable con el cliente.
- Permitir la edición de los datos de los pacientes ya ingresados, para tener la capacidad de corregir errores cometidos a la hora del registro.

## Ejemplo de uso

**Paso 1: Registrar los pacientes**

Se comienza registrando a Martina, quien acaba de ingresar al hospital.
````
1) Registrar paciente
========================================
        Registrar nuevo paciente
========================================

Ingrese el nombre del paciente: 
Martina

Ingrese la edad en años del paciente: 
23

Ingrese los síntomas del paciente:
Esguince leve en el dedo meñique de la mano izquierda

========================================
   Paciente registrado correctamente
========================================
````  
Se registra a un segundo paciente, Julian, quien ingresó al hospital despues de Martina.
````
1) Registrar paciente
========================================
        Registrar nuevo paciente
========================================

Ingrese el nombre del paciente: 
Julian

Ingrese la edad en años del paciente: 
19

Ingrese los síntomas del paciente:
Fractura de rodilla derecha expuesta

========================================
   Paciente registrado correctamente
========================================
````  
El sistema ingresará a ambos pacientes en la cola de prioridad baja automáticamente, y guardará la hora de ingreso de cada uno de los pacientes.

**Paso 2: Asignar Prioridad a un Paciente**

Trás una evaluación, se le asigna la prioridad correspondiente a cada paciente.
````
2) Asignar prioridad a paciente
========================================
||        Considere que:              ||
||        1 = Prioridad baja          ||
||        2 = Prioridad media         ||
||        3 = Prioridad alta          ||
========================================
Ingrese el nombre del paciente al que desea asignarle prioridad: 
Julian

Ingrese la prioridad actual del paciente

Los pacientes al ser registrados se ingresan automáticamente al nivel 1
1

Indique la prioridad a asignar al paciente
3

Prioridad asignada correctamente
````

Se le asigna a Julian una alta prioridad debido a los síntomas presentados, mientras que a Martina se le deja en la prioridad baja, por lo cual no es necesario modificar su caso.

**Paso 3: Mostrar la lista de espera**

El usuario decide revisar la lista de espera, para observar la información de los pacientes y la prioridad de cada uno.
````
3) Mostrar lista de espera
========================================
          Pacientes en espera: 
========================================

Pacientes con prioridad alta: 

--------------------------------------------
Nombre: Julian
Edad: 19 año(s)
Síntoma: Fractura de rodilla derecha expuesta
Hora de ingreso: 22:54
--------------------------------------------

Pacientes con prioridad media:

-

Pacientes con prioridad baja: 

--------------------------------------------
Nombre: Martina
Edad: 23 año(s)
Síntoma: Esguince leve en el dedo meñique de la mano izquierda
Hora de ingreso: 22:53
--------------------------------------------

========================================
            Fin de la lista
========================================
````

La lista muestra a los pacientes, en este caso a Julian y a Martina, en ese orden debido a la prioridad que les fue asignada.

**Paso 4: Atender al siguiente paciente**

Julian es llamado a ser atendido debido a su prioridad, por lo cual se mostrarán sus datos y será eliminado de la lista de espera.

````
4) Atender al siguiente paciente
========================================
          PACIENTE ATENDIDO: 
Nombre: Julian
Edad: 19 año(s)
Síntoma: Fractura de rodilla derecha expuesta
Hora de ingreso: 22:54
========================================
````
Posteriormente, respetando la lista de espera, Martina es llamada a ser atendida, por lo que se enseñan sus datos y es eliminada de la lista de espera.

````
4) Atender al siguiente paciente
========================================
          PACIENTE ATENDIDO: 
Nombre: Martina
Edad: 23 año(s)
Síntoma: Esguince leve en el dedo meñique de la mano izquierda
Hora de ingreso: 22:53
========================================
````

**Paso 5: Salir del programa**

Al acabar con todos los pacientes del hospital, se cierra el programa.

````
6) Salir
Saliendo del sistema de gestión hospitalaria...
````
