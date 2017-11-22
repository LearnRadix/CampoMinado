#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>

void imprime_interface() //ESSA FUN��O SERVE PRA DEFINIR O a interface apos uma jogada
{
    int i, j;
    system("clear");
    for(i=0; i<10; i++)
    {
        for(j=0; j<10; j++)//temos que ler a matriz op, que so irá conter -1(bomba) e numeros(dicas)
        {                  //apos um numero ser aberto, a interface imprime ele e atualiza a matriz op com um
                          //identificador para saber que ja foi aberto
          if(op[i][j] != -2){//-2 indica que ja foi aberto
            if(z<10)
              printf("|  %d ", campo[i][j]);
          else
              printf("| %d ", campo[i][j]);
          }
        }
        printf("\n");
    }
}



void atualiza_op(void){//pega agora o vetor countbombas e atualiza a matriz op para colocar as dicas
int i,j,k=0;
for(i=0;i<9;i++){
  for(j=0;j<9;j++){
    if(op[i][j] != -1)
      op[i][j]=countbombas[k];

    k++;
  }
}
}
