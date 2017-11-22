#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>


int verificaExistencia(int posBombas[],int tam, int comparado){
  int z;
  for(z=0;z<tam;z++)
  {
    if(posBombas[z] == comparado)
    {
      return 1;
    }
  }
  return 0;
}


int main()
{
  int matriz[20][5];

  srand((unsigned)time(NULL));

    int tam,escolha;
    printf("\n########## BOAS VINDAS AO CAMPO MINADO ##########\n");
    printf("\nQual dificuldade deseja escolher ?\n");
    printf("1 - Facil\n2 - Medio\n3 - Dificil\n4 - Impossivel\n");
    scanf("%d",&escolha);
    switch (escolha) {
      case 1: //100 posições, 25 bombas
        tam = 25;
        break;
      case 2://100 posições 40 bombas
        tam = 40;
        break;
      case 3://100 posições 75 bombas
        tam = 75;
        break;
      case 4://100 posições 90 bombas
        tam = 90;
        break;
    }

    int contador,posBombas[tam],aux;
     for(contador=0; contador<tam ; contador++)
     {
       //gera aleatoriamente as posições onde vamos ter as bombas
       aux = rand()%100;
       while(verificaExistencia(posBombas,tam,aux))
       {
         aux = rand()%100;
       }
       posBombas[contador] = aux;
      }

    //impressão do campo
    int i,j,z=0;
    printf("\n\t_____________________\n");
    for(i=0; i<20; i++)
    {
        printf("\t|");
        for(j=0; j<5; j++)
        {
            if(z<10)
            {
                printf("  %d|",z);
            }
            else
            {
                printf(" %d|",z);
            }
            matriz[i][j]=z;
            z++;
        }
        printf("\n");
    }
    printf("\t_____________________\n");

    //int numEscolhido;
    //imprime as posições das bombas para teste
    // for(j=0;j<tam;j++)
    // {
    //   printf("%d ",posBombas[j]);
    // }

    printf("\n");
     while(1){
    printf("\nEscolha a posicao que deseja abrir:  ");
     scanf("%d", &numEscolhido );
     //chama a função de analisar a posição escolhida
     if(verificaExistencia(posBombas, tam, numEscolhido))
     {
       printf("Que pena, voce perdeu!\n");
       break;
     }
     else{//ir na matriz achar o numero que o usuario digitou
       int posMatriz,contadorBombasProximas=0;
       for(i=0;i<tam;i++){
         for(j=0;j<tam;j++){
           if(numEscolhido == matriz[i][j]){
             posMatriz = matriz[i][j];
           }
         }
       }

       verificaExistencia(posBombas,tam,matriz[i+1][j])
       verificaExistencia(posBombas,tam,matriz[i-1][j])
       verificaExistencia(posBombas,tam,matriz[i][j+1])
       verificaExistencia(posBombas,tam,matriz[i][j-1])
       verificaExistencia(posBombas,tam,matriz[i+1][j+1])
       verificaExistencia(posBombas,tam,matriz[i+1][j-1])
       verificaExistencia(posBombas,tam,matriz[i-1][j+1])
       verificaExistencia(posBombas,tam,matriz[i-1][j-1])



}


   }

return 1;
}
