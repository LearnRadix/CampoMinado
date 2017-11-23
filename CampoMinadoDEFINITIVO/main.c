#include <stdio.h>
#include <stdlib.h>
#include"campo.h"

int main()
{
      int i, j;
      srand(time(NULL));
  for(i=0; i<25; i++){
   pthread_mutex_init(&(mutex_bomba[i]), NULL);  //INICIANDO AS AREAS CRITICAS
   }
  for(j=0; j<25; j++) {
    id[j] = j;
  pthread_create(&bomba_id[j], NULL, gera_bombas(), (void *)&id[j]); //CRIANDO THREADS
   }

   gera_dicas();
   atualiza_op();
   imprime_inicio();
   verifica_vizinhanca();

   return 0;
}
