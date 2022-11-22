#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS	7          // nr dei thread da far partire 

int globale;
char *nome[NUM_THREADS];       // vettore contenete i nomi dei nani  

void *codice_thread(void *tid){
  int *tid_ptr, tid_int;

  // casting da void ad intero: versione in una sola istruzione
  tid_int = *(int*) tid;	   // leggo parametro da puntatore void 

  // generazione ritardo casuale 
  srand(time(NULL));
  sleep(rand() % 2);
  globale++;
  printf("  Ciao da %d: %s %d \n", tid_int, nome[tid_int], globale); 	// stampa del messaggio 
  
  pthread_exit(NULL); 	  // Uscita del thread senza valori di ritorno
}

int main(int argc, char *argv[]){
  pthread_t threads[NUM_THREADS];  // vettore identificari dei thread 
  int t, rc;
  globale = 1;

  nome[0] = "Cucciolo";
  nome[1] = "Pisolo";
  nome[2] = "Eolo";
  nome[3] = "Dotto";
  nome[4] = "Mammolo";
  nome[5] = "Gongolo";
  nome[6] = "Brontolo";
  for (t = 0; t < NUM_THREADS; t++){
    printf("Creazione thread %d\n", t);
    rc = pthread_create(&threads[t], NULL, codice_thread, (void *) &t);   

    sleep(1); // necessaria , altrimenti la velocità della macchina crea problemi sul valore di t 
	if (rc) {
	  printf ("ERRORE: il codice di errore di ritorno da pthread_create() e': %d\n", rc);
	  exit(EXIT_FAILURE);
    }
  }
 
  pthread_exit(NULL);  // terminazione corretta del programma
}



/************************************************************************
* Listato da "Tecnologie e progettazione di sistemi ... Vol.2           *
* Copyright (C) 2012-2016 by Hoepli Editore                             * 
* collaudo in: gcc OK                                                   *
*              linux: compilare con gcc -pthread <nome>.c -o -<desti>   *                                            *
************************************************************************/


