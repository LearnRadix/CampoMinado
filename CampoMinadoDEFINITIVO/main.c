#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>


int campo[10][10], op[10][10], countbombas[100], espacosfree = 0;

pthread_mutex_t mutex_bomba[25];
pthread_t bomba_id[25];

int verificaBomba(int linha, int coluna)
{
        //SE A POSIÇÃO RECEBIDA CORRESPONDER A -1, RETORNA 1, OU SEJA, DIZ QUE EXISTE UMA BOMBA NESSA POSIÇÃO
        if(op[linha][coluna] == -1)
        {
            return 1;
        }
        //CASO CONTRÁRIO RETORNA 0, NÃO TEM BOMBA ALI
    return 0;
}

void imprime_inicio()
{
    int i, j, z=0;
    system("clear");
    for(i=0; i<10; i++)
    {
        for(j=0; j<10; j++)//IMPRIMINDO A MATRIZ DE INTERFACE EM SEU ESTADO INICIAL
        {
            campo[i][j] = z;
            z++;
            if(z<10)
            {
                printf("\t|%d\t", campo[i][j]);
            }
            else
            {
                printf("\t|%d\t", campo[i][j]);
              }
        }
        printf("|");
        printf("\n");
    }

}

void gerando(int * bomba)
{
    //FECHA ACESSO A REGIÃO CRITICA
    pthread_mutex_lock(&(mutex_bomba[*bomba]));
}

void acabou_gerar(int * bomba)
{
    //LIBERA ACESSO A REGIÃO CRITICA
    pthread_mutex_unlock(&(mutex_bomba[*bomba]));
}

void * gera_bombas(void *var)
{
    int * bomba = (int *) (var), linha, coluna;
    srand(time(NULL));
    //GERANDO UM TEMPO ALEATORIO PRA IMPEDIR QUE AS THREADS ACESSEM NO MESMO MOMENTO A MESMA COISA
    int tempo = rand() % 10;
    int aux,contador;

    sleep(tempo);//O TEMPO DEVE FICAR EM MILISEGUNDOS, PRECISA CONFERIR ISSO
    gerando(bomba);//BLOQUEIA O ACESSO

    do
    {
         linha = rand() % 10;
         coluna = rand() % 10;
    }
    while(verificaBomba(linha, coluna));

    op[linha][coluna] = -1; //-1 É O VALOR ATRIBUIDO ÀS BOMBAS

    acabou_gerar(bomba);//LIBERA O ACESSO A FUNÇÃO
    pthread_exit(NULL);
}

void gera_dicas(void)
{
    int i,j,aux=0,k=0,x,z;
    //PERCORRENDO A MATRIZ INTEIRA E VERIFICANDO AONDE TEM BOMBA E SALVANDO COMO IN NA COUNTBOMBAS
    for(i=0; i<10; i++)
    {
        for(j=0; j<10; j++)
        {
          x=i-1;
          z=j-1;
          if(op[x][z]==-1 && ((x>=0&&x<=9)&&(j>=0&&j<=9))){
                aux++;}
          x=i-1;
          z=j;
          if(op[x][z]==-1 && ((x>=0&&x<=9)&&(j>=0&&j<=9))){
                aux++;}
          x=i-1;
          z=j+1;
          if(op[x][z]==-1 && ((x>=0&&x<=9)&&(j>=0&&j<=9))){
                aux++;}
          x=i;
          z=j+1;
          if(op[x][z]==-1 && ((x>=0&&x<=9)&&(j>=0&&j<=9))){
                aux++;}
          x=i;
          z=j-1;
          if(op[x][z]==-1 && ((x>=0&&x<=9)&&(j>=0&&j<=9))){
                aux++;}
          x=i+1;
          z=j-1;
          if(op[x][z]==-1 && ((x>=0&&x<=9)&&(j>=0&&j<=9))){
                aux++;}
          x=i+1;
          z=j;
          if(op[x][z]==-1 && ((x>=0&&x<=9)&&(j>=0&&j<=9))){
                aux++;}
          x=i+1;
          z=j+1;
          if(op[x][z]==-1 && ((x>=0&&x<=9)&&(j>=0&&j<=9))){
                aux++;}

            if(op[i][j] != -1){
              op[i][j]=aux;
            }
            aux=0;
            k++;
        }
    }

          // k=0;
          // for(i=0; i<10; i++)
          // {
          //   for(j=0; j<10; j++)
          //   {
          //     x=k+1;
          //     if((x>=0&&x<=99)&&(countbombas[x]==1)){
          //       aux++;
          //     }
          //     x=k-1;
          //     if((x>=0&&x<=99)&&(countbombas[x]==1)){
          //       aux++;
          //     }
          //     x=k+4;
          //     if((x>=0&&x<=99)&&(countbombas[x]==1)){
          //       aux++;
          //     }
          //     x=k-4;
          //     if((x>=0&&x<=99)&&(countbombas[x]==1)){
          //       aux++;
          //     }
          //     x=k+5;
          //     if((x>=0&&x<=99)&&(countbombas[x]==1)){
          //       aux++;
          //     }
          //     x=k-5;
          //     if((x>=0&&x<=99)&&(countbombas[x]==1)){
          //       aux++;
          //     }
          //     x=k+6;
          //     if((x>=0&&x<=99)&&(countbombas[x]==1)){
          //       aux++;
          //     }
          //     x=k-6;
          //     if((x>=0&&x<=99)&&(countbombas[x]==1)){
          //       aux++;
          //     }
          //     if(op[i][j] != -1){
          //       op[i][j]=aux;
          //       aux=0;
          //     }
              // aux=0;
              // k++;
      //     }
      // }
}


void libera_vazio(int auxi, int auxj)
{
    int i, j;
    bool continua;

    //LOOP QUE SÓ É SACIADO CASO NÃO EXISTA NENHUMA POSIÇÃO VAZIA PRÓXIMA
    do
    {
        //ESSES FOR CONFEREM NAS 8 CELULAS AO REDOR DA POSIÇÃO VAZIA
        for(i = auxi-1; i <= auxi +1; i++)
        {
            if(i < 0 || i > 9)
            {
                continue;
            }
            for (j = auxj-1; j <= auxj +1; j++)
            {
                if(j < 0 || j > 9)
                {
                    continue;
                }
                //CASO NAO EXISTA VAZIO, O CONTINUA VIRA FALSE E ELE SAI DO LOOP
                continua = false;
                //CASO EXISTA VAZIO, A FUNÇÃO CHAMA A SI PROPRIA NOVAMENTE, PASSANDO COMO PARAMETRO, A POSIÇÃO QUE FOI
                //ENCONTRADO VAZIO
                if(op[i][j] == 0)
                {
                    continua = true;
                    campo[i][j] = 0;
                    espacosfree++;
                    //DEFINE NA OPERAÇÃO QUE O ESPAÇO JÁ FOI ABERTO, QUE É SIMBOLIZADO POR -2
                    op[i][j] = -2;
                    libera_vazio(i, j);

                }
                //CASO NÃO SEJA ESPAÇO VAZIO E SEJA UMA DICA, ELE ATRIBUI O VALOR DA DICA NA INTERFACE
                else if(op[i][j] >= 0)
                {
                    campo[i][j] = op[i][j];
                    op[i][j] = -2;
                    espacosfree++;
                }
            }
        }
    }
    while(continua);
}

void verifica_vizinhanca()
{
    int i, j, z, auxi, auxj, k=0, escolhido;

    //ESPAÇOS FREE SIGNIFICA QUANTOS PEDAÇOS JÁ FORAM LIBERADOS, SE FOR 75, SIGNIFICA QUE O USUARIO ENCONTROU TODAS AS BOMBAS
    while(espacosfree < 75)
    {
        //countbombas[k] = 0;
        //ARMAZENANDO A POSIÇÃO QUE DESEJA ABRIR
        printf("\n\nEscolha a posicao que deseja abrir:  ");
        scanf("%d",&escolhido);

        for(i=0; i<10; i++)
        {
            for(j=0; j<10; j++)
            {
                if(campo[i][j] == escolhido)
                {
                    auxi = i;  //AQUI ESTAMOS ARMAZENANDO A POSIÇÃO SELECIONADA
                    auxj = j;
                }
            }
        }

        if(verifica_posicao(auxi,auxj)){
          continue;
        }
        else
        {
        if(verificaBomba(auxi, auxj)) //ESSA PARTE ANALISA SE O USARIO ACERTOU A BOMBA, E LOGO EM SEGUIDA MOSTRA TODAS AS POSI��ES DAS OUTRAS BOMBAS
        {
            for(i=0; i<10; i++)
            {
                for(j=0; j<10; j++)
                {
                    if(op[i][j] == -1)
                    {
                        printf("\t|%c\t", 207);
                    }
                    else
                    {
                        printf("\t|%d\t", campo[i][j] );
                    }
                }
                printf("\n");
            }
            printf("VOCÉ PERDEU!");
            exit(0);
        }

        //CASO O USUÁRIO NÃO TENHA ACERTADO UMA BOMBA, VERIFICA SE ELE ACERTOU UMA DICA OU UM ESPAÇO VAZIO
        else //if(!verificaBomba(auxi, auxj))
        {
            if(op[auxi][auxj] == 0)
             //CASO SEJA UM ESPAÇO VAZIO, CHAMA A FUNÇÃO LIBERA VAZIO QUE LIBERA TODOS OS ESPAÇOS VAZIOS PRÓXIMOS
            {
                libera_vazio(auxi, auxj);
            }
            else if(op[auxi][auxj] >= 0)
            {
                campo[auxi][auxj] = op[auxi][auxj];
                espacosfree++;
            }
        }
        //ATUALIZA A MATRIZ INTERFACE COM OS NOVOS VALORES
        atualiza_matriz();
    }
  }//while
    printf("\n\n PARABENS, VOCÊ VENCEU O CAMPO MINADO!\n");
}

void atualiza_matriz()
{
    int i, j;
    system("clear");
    //SIMPLESMENTE IMPRIME A MATRIZ DE INTERFACE QUE É EXIBIDA AO USUÁRIO
    for(i=0; i<10; i++)
    {
        for(j=0; j<10; j++)
        {
          if(i<1)
              printf("\t|%d\t", campo[i][j]);
          else
              printf("\t|%d\t", campo[i][j]);
        }
      printf("|");
      printf("\n");
    }
}

int verifica_posicao(int i, int j){
  if(op[i][j] == -2){// a posição escolhida ja foi aberta
    return 1;
  }
  else{//a posição ainda não foi aberta
    return 0;
  }
}


int main()
{
      int i, j, id[25];
      srand(time(NULL));

  for(i=0; i<25; i++){
   pthread_mutex_init(&(mutex_bomba[i]), NULL);  //INICIANDO AS AREAS CRITICAS
   }

  for(j=0; j<25; j++) {
    id[j] = j;
  pthread_create(&bomba_id[j], NULL, gera_bombas, &id[j]); //CRIANDO THREADS
   }

   for(j=0;j<25;j++)
 	{
 	pthread_join(bomba_id[j],NULL);
 	}

   imprime_inicio();

   sleep(10);
   gera_dicas();

  //  printf("\n");
  //  for(i=0; i<10; i++)
  //  {
  //      for(j=0; j<10; j++)
  //      {
  //            printf("\t|%d\t", op[i][j]);
  //          }
  //    printf("|");
  //    printf("\n");
  //  }
  verifica_vizinhanca();

   return 0;
}
