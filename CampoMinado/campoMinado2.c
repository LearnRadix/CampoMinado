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

void gera_dicas(void){
  int i,j,aux,k=0;
  for(i=0;i<10;i++){
    for(j=0;j<10;j++){
      if(op[i--][j--]==-1 && i>0 && j>0)
        aux++;
      else if(op[i--][j]==-1 && i>0)
        aux++;
      else if(op[i--][j++]==-1 && i>0 && j<10)
        aux++;
      else if(op[i][j++]==-1 && j<10)
        aux++;
      else if(op[i][j--]==-1 && j>0)
        aux++;
      else if(op[i++][j--]==-1 && i<10 && j>0)
        aux++;
      else if(op[i++][j]==-1 && i<10)
        aux++;
      else if(op[i++][j++]==-1 && i<10 && j<10)
        aux++;

        countbombas[k]=aux;
        aux=0;
        k++;
    }
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

void jogada(void){
    int i, j, auxi, auxj, escolhido;
  while(1){
    printf("\nEscolha a posicao que deseja abrir:  ");
    scanf("%d", &escolhido);

    for(i=0; i<10; i++)
    {
        for(j=0; j<10; j++)
        {
            if(campo[i][j] = escolhido)
            {
                auxi = i;  //AQUI ESTAMOS ARMAZENANDO A POSIÇÃO SELECIONADA
                auxj = j;
            }
        }
    }

    if(op[auxi][auxj] == -1)
    {//perdeu
      system("clear");
      printf("\nQue pena, você perdeu!\n");
      for(i=0; i<10; i++)
      {
          for(j=0; j<10; j++)
          {
              if(campo[i][j] = -1)//revela as bombas
              {
                if(z<10)
                    printf("|  %c ", 207 );
                else
                    printf("| %c ", 207 );
              }
              else{//mantem onde n era bomba
                if(z<10)
                    printf("|  %d ", campo[i][j]);
                else
                    printf("| %d ", campo[i][j]);
              }
          }
      }
    }//perdeu

    else
    {//caso não seja bomba, verifica na op a dica
      if(op[i][j]==0){//dica 0, chama a recursiva


      }
      else{//dica não é zero
        campo[i][j]=op[i][j];
        op[i][j]=-2;//marca op como ja lida
      }
    }

  }//while
}
