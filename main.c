#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{  // Struct para los datos de cada paciente
  char nombre[100];
  int edad;
  char sintoma[100];
  int prioridad;  
  time_t tiempoLlegada;
  size_t horaRegistro;
  size_t minutoRegistro;
} tipoPaciente;


typedef struct{ // Struct para las listas de cada prioridad de los pacientes
  List *baja;
  List *media;
  List *alta;
} tipoListaPacientes;

// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

// Función para avanzar
void presioneTeclaParaContinuar() {
  puts("Presione enter para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

// Función para registrar un nuevo paciente
void registrar_paciente(List *listaBaja, time_t *hora){

  // Reservamos memoria para pacienteAux
  tipoPaciente *pacienteAux = (tipoPaciente *) malloc(sizeof(tipoPaciente));
  // Si no se pudo reservar memoria, finalizamos la ejecución de la función
  if(pacienteAux == NULL) exit(EXIT_FAILURE); 

  // Asignamos la hora actual a la variable hora
  time(hora);
  struct tm *horaActual = localtime(hora);

  // Realizamos los ajustes para que la hora actual coincida con la hora
  // en Chile
  size_t horaAux = horaActual->tm_hour + 20;
  if (horaAux > 23) horaAux -= 24; 

  // Le asignamos todos los valores obtenidos a pacienteAux
  pacienteAux->tiempoLlegada = *hora;
  pacienteAux->horaRegistro = horaAux; 
  pacienteAux->minutoRegistro = horaActual->tm_min; 
  pacienteAux->prioridad = 1;

  // Se solicita ingresar el nombre, la edad y los síntomas del paciente
  printf("\n========================================\n");
  printf("        Registrar nuevo paciente");
  printf("\n========================================\n");
  printf("\nIngrese el nombre del paciente: \n");
  scanf(" %99[^\n]s", pacienteAux->nombre);
  printf("\nIngrese la edad en años del paciente: \n");
  scanf(" %d", &pacienteAux->edad);
  printf("\nIngrese los síntomas del paciente: \n");
  scanf(" %99[^\n]s", pacienteAux->sintoma);

  // Se ingresa al paciente a la lista de baja prioridad de forma automática
  list_pushBack(listaBaja, pacienteAux);
  printf("\n========================================\n");
  printf("   Paciente registrado correctamente");
  printf("\n========================================\n\n");
}

// Función para encontrar en que lista se encuentra un paciente determinado
void buscarListaDelPaciente(tipoListaPacientes *listaPacientes, char *nombreAux,
                            List **listaDelPaciente, int *prioridadActual){
  //Se solicita el ingreso del nombre y de la prioridad actual del paciente
  printf("\n========================================\n");
  printf("||        Considere que:              ||");
  printf("\n||        1 = Prioridad baja          ||");
  printf("\n||        2 = Prioridad media         ||");
  printf("\n||        3 = Prioridad alta          ||");
  printf("\n========================================\n");
  printf("\nIngrese el nombre del paciente al que desea asignarle prioridad: \n");
  scanf(" %99[^\n]s", nombreAux);

  printf("\nIngrese la prioridad actual del paciente\n");
  printf("\n(Los pacientes al ser registrados se ingresan automáticamente al nivel 1)\n");
  scanf("%d", prioridadActual);

  // Se asigna la lista del paciente buscado de acuerdo a la prioridad indicada
  switch(*prioridadActual){
    case 1:
      *listaDelPaciente = listaPacientes->baja;
      break;

    case 2:
      *listaDelPaciente = listaPacientes->media;
      break;

    case 3:
      *listaDelPaciente = listaPacientes->alta;
      break;

    default:
      // En caso de que la prioridad no sea válida, se indicará con un mensaje
      printf("\nLa prioridad actual ingresada no es válida\n");
      return;
  }
}

// Función lower_than para el list_sortedInsert
int ordenarPorLlegada(void *dato, void *pivot){
  tipoPaciente *ptrDato = (tipoPaciente *)dato;
  tipoPaciente *ptrPivot = (tipoPaciente *)pivot;

  // Se comparan los tiempos de llegada de tipo time_t, para determinar que paciente
  // llego antes y mantener las listas ordenadas
  if(ptrDato->tiempoLlegada < ptrPivot->tiempoLlegada) return 1;
  return 0;
}

// Función para asignarle una prioridad a un paciente
void asignar_prioridad(tipoListaPacientes *listaPacientes){
  List *listaDelPaciente = NULL;
  char nombreAux[100];
  int prioridadActual;
  int nuevaPrioridad;

  // Se pregunta en que lista se encuentra el paciente 
  buscarListaDelPaciente(listaPacientes, nombreAux, &listaDelPaciente, &prioridadActual);
  // Si no se encontró una lista, se termina la función
  if(listaDelPaciente == NULL) return;

  // Se inicializa pacienteAux en el primer elemento de la lista indicada
  tipoPaciente *pacienteAux = list_first(listaDelPaciente);

  // Ciclo para recorrer la lista indicada
  while(pacienteAux != NULL){
    // Se utiliza la función strcmp para encontrar al paciente buscado
    if(strcmp(pacienteAux->nombre, nombreAux) == 0){
      // Se solicita la nueva prioridad que se desea asignar al paciente
      printf("\nIndique la prioridad a asignar al paciente\n");
      scanf("%d", &nuevaPrioridad);

      // Se asigna la nueva prioridad y se inserta de manera ordenada en su lista 
      // utilizando la función list_sortedInsert, que utiliza como parámetro 
      // nuestra función ordenarPorLlegada
      switch(nuevaPrioridad){
        case 1:
          pacienteAux->prioridad = 1;
          list_sortedInsert(listaPacientes->baja, pacienteAux, ordenarPorLlegada);
          break;

        case 2:
          pacienteAux->prioridad = 2;
          list_sortedInsert(listaPacientes->media, pacienteAux, ordenarPorLlegada);
          break;

        case 3:
          pacienteAux->prioridad = 3;
          list_sortedInsert(listaPacientes->alta, pacienteAux, ordenarPorLlegada);
          break;

        default:
          // Si la prioridad ingresada no es válida, se avisa y finaliza la función
          printf("\nLa prioridad ingresada no es válida\n\n");
          return;
      }

      //Se elimina el paciente de su lista anterior
      list_popCurrent(listaDelPaciente);
      printf("\nPrioridad asignada correctamente\n\n");
      // Se finaliza la función
      return;
    }
    // Si el paciente no es el buscado, se pasa al siguiente de la lista
    pacienteAux = list_next(listaDelPaciente);
  }

  // Si el paciente no se encuenra, se da un aviso y finaliza la función
  if(pacienteAux == NULL){
    printf("\nEl paciente no se encuentra en la lista\n\n");
  }
  return;
}

// Función para mostrar la lista de una prioridad determinada
void mostrar_lista_prioridad(List *lista){
  // Se asigna pacienteAux al primer elemento de la lista
  tipoPaciente *pacienteAux = list_first(lista); 

  // Si la lista esta vacía, es decir cuando list_first retorna el valor NULL, se 
  // muestra que esta vacía y posteriormente finaliza la función
  if (pacienteAux == NULL) {
    printf("-\n\n");
    return;
  }

  // Ciclo para recorrer la lista por completo
  while (pacienteAux != NULL) { 
    // Se muestran los datos de cada paciente
    printf("--------------------------------------------\n");
    printf("Nombre: %s\n", pacienteAux->nombre);
    printf("Edad: %d año(s)\n", pacienteAux->edad);
    printf("Síntoma: %s\n", pacienteAux->sintoma);
    printf("Hora de ingreso: %02zu:%02zu\n", 
          pacienteAux->horaRegistro, pacienteAux->minutoRegistro);
    printf("--------------------------------------------\n\n");
    // Se avanza al siguiente paciente de la lista
    pacienteAux = list_next(lista);
  }
}

// Función que muestra la lista de espera en su totalidad, separando los pacientes
// segun su prioridad
void mostrar_lista_pacientes(tipoListaPacientes listaPacientes){
  printf("\n========================================\n");
  printf("          Pacientes en espera: ");
  printf("\n========================================\n\n");

  // Se enseñan los pacientes con prioridad alta
  printf("Pacientes con prioridad alta: \n\n");
  mostrar_lista_prioridad(listaPacientes.alta);

  // Se enseñan los pacientes con prioridad media
  printf("Pacientes con prioridad media: \n\n");
  mostrar_lista_prioridad(listaPacientes.media);

  // Se enseñan los pacientes con prioridad baja
  printf("Pacientes con prioridad baja: \n\n");
  mostrar_lista_prioridad(listaPacientes.baja);

  printf("========================================\n");
  printf("            Fin de la lista");
  printf("\n========================================\n\n");
}

// Función que busca el siguiente paciente que debe ser atendido, segun las 
// listas de prioridad
void buscarSiguientePaciente(tipoListaPacientes *listaPacientes, tipoPaciente **sgtePaciente){
  // Se recorren las tres listas, iniciando desde la más alta prioridad a la más baja
  // Se comprueba si la lista no esta vacía utilizando la función list_first
  // Si no está vacía, el siguiente paciente se obtiene con la función list_popFront
  // que retornará los datos del paciente, además de eliminarlo de la lista de espera
  if(list_first(listaPacientes->alta) != NULL){
    *sgtePaciente = list_popFront(listaPacientes->alta);  
  }else if(list_first(listaPacientes->media) != NULL){
    *sgtePaciente = list_popFront(listaPacientes->media);  
  }else if(list_first(listaPacientes->baja) != NULL){
    *sgtePaciente = list_popFront(listaPacientes->baja);  
  }else{
    // Si las listas se encuentran vacías se da un aviso
    printf("\nNo hay pacientes en espera\n\n");
    return;
  }
}

// Función para atender al siguiente paciente según la lista de espera
void atender_siguiente_paciente(tipoListaPacientes *listaPacientes){
  tipoPaciente *pacienteAtendido = NULL;

  // Se busca el paciente que corresponde atender
  buscarSiguientePaciente(listaPacientes, &pacienteAtendido);
  // Si no se encuentran más pacientes, finaliza la función
  if(pacienteAtendido == NULL) return;

  // Se muestran los datos del paciente atendido
  printf("========================================\n");
  printf("          PACIENTE ATENDIDO: \n");
  printf("Nombre: %s\n", pacienteAtendido->nombre);
  printf("Edad: %d año(s)\n", pacienteAtendido->edad);
  printf("Síntoma: %s\n", pacienteAtendido->sintoma);
  printf("Hora de ingreso: %02zu:%02zu\n", 
        pacienteAtendido->horaRegistro, pacienteAtendido->minutoRegistro);
  printf("========================================\n");
}

// Función que busca la lista de prioridad deseada
void encontrarListaBuscada(tipoListaPacientes listaPacientes, 
                           List **listaBuscada, int *prioridad){
  // Se solicita la prioridad de la lista buscada
  printf("\n========================================\n");
  printf("||        Considere que:              ||");
  printf("\n||        1 = Prioridad baja          ||");
  printf("\n||        2 = Prioridad media         ||");
  printf("\n||        3 = Prioridad alta          ||");
  printf("\n========================================\n");
  printf("Ingrese la lista de prioridad que desea conocer: \n");
  scanf("%d", prioridad);

  // Se asigna la lista buscada según lo indicado
  switch(*prioridad){
    case 1:
      *listaBuscada = listaPacientes.baja;
      printf("\n========================================\n");
      printf("        Lista de prioridad baja: ");
      printf("\n========================================\n\n");
      break;

    case 2:
      *listaBuscada = listaPacientes.media;
      printf("\n========================================\n");
      printf("        Lista de prioridad media: ");
      printf("\n========================================\n\n");
      break;

    case 3:
      *listaBuscada = listaPacientes.alta;
      printf("\n========================================\n");
      printf("        Lista de prioridad alta: ");
      printf("\n========================================\n\n");
      break;

    default:
      // Si la prioridad de lista ingresada no es válida, se da un aviso
      printf("\nLa prioridad ingresada no es válida\n\n");
      return;
  }
}

// Función para mostrar la lista de de la prioridad ingresada por el usuario
void mostrar_pacientes_por_prioridad(tipoListaPacientes listaPacientes){
  int prioridad;
  List *listaBuscada = NULL;

  // Se busca la lista que se desea conocer
  encontrarListaBuscada(listaPacientes, &listaBuscada, &prioridad);
  // Si no se encuentra la lista, finaliza la función
  if(listaBuscada == NULL) return;

  // Se enseña la lista de prioridad deseada
  mostrar_lista_prioridad(listaBuscada);
}

// Programa principal
int main(){
  // Se crean las variables
  tipoListaPacientes listaPacientes;
  char opcion;
  time_t horaActual;

  // Se crean las listas de baja, media y alta prioridad
  listaPacientes.baja = list_create();
  listaPacientes.media = list_create();  
  listaPacientes.alta = list_create();
  

  do {
    mostrarMenuPrincipal();
    // Se solicita la opción sobre que desea hacer
    printf("\nIngrese su opción: ");
    scanf(" %c", &opcion); 

    // Según la opción elegida, se desarrolla cada caso
    switch (opcion) {
    case '1':
      registrar_paciente(listaPacientes.baja, &horaActual);
      break;
    case '2':
      asignar_prioridad(&listaPacientes);
      break;
    case '3':
      mostrar_lista_pacientes(listaPacientes);
      break;
    case '4':
      atender_siguiente_paciente(&listaPacientes);
      break;
    case '5':
      mostrar_pacientes_por_prioridad(listaPacientes);
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      // Se liberan las listas, eliminando todos sus elementos
      // y se finaliza el programa
      list_clean(listaPacientes.baja);
      list_clean(listaPacientes.media);
      list_clean(listaPacientes.alta);
      return 0;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  return 0;
}
