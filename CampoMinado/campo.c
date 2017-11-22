#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"campo.h"
#define tam 25

int campo[10][10], op[10][10], countbombas[100];
pthread_mutex_t mutex_bomba[25];
pthread_t gerando[25];

int verificaBomba(int linha, int coluna, int comparado)
{
    int z;
    for(z=0; z<tam; z++)
    {
        if(op[linha][coluna] == comparado)
        {
            return 1;
        }
    }
    return 0;
}

void imprime_inicio() //ESSA FUN��O SERVE PRA IMPRIMIR O ESTADO INICIAL DO CAMPO MINADO
{
    int i, j, z=0;
    system("clear");
    for(i=0; i<10; i++)
    {
        for(j=0; j<10; j++)
        {
            campo[i][j] = z;
            z++;
            if(z<10)
            {
                printf("|  %d ", campo[i][j]);
            }
            else
                printf("| %d ", campo[i][j]);
        }
        printf("\n");
    }

}
//FUN��ES PARA GERAR AS BOMBAS PARALELAMENTE UTILIZANDO THREADS
void gerando(int * bomba)//AQUI � BLOQUEADO O ACESSO QUE EST� SENDO UTILIZADO
{
    pthread_mutex_lock(&(mutex_bomba[*bomba]));
}

void acabou_gerar(int * bomba)//AQUI � LIBERADO O ACESSO AP�S O USO
{
    pthread_mutex_unlock(&(mutex_bomba[*bomba]));
}

void * gera_bombas(void *var)//FUN��O PARA GERAR AS BOMBAS
{
    int * bomba = (int *) (var);
    srand(time(NULL));
    int tempo = rand() % 10;
    int aux,contador;
    sleep(tempo);//� DEFINIDO UM TEMPO ALEAT�RIO PARA AS THREADS N�O ACESSAREM AO MESMO TEMPO
    gerando(bomba);//BLOQUEIA O ACESSO

    do
    {
    int linha = rand() % 10;
    int coluna = rand() % 10;
    }while(verificaBomba(linha, coluna, op[linha][coluna]));

    op[linha][coluna] = -1; //-1 � O VALOR ATRIBUIDO �S BOMBAS

    acabou_gerar(bomba);//LIBERA O ACESSO A FUN��O
    pthread_exit(NULL);
}

void verifica_vizinhanca() //FUN��O PRA VERIFICAR A VIZINHAN�A
{
    int i, j, z, auxi, auxj, countbomba[100], k=0, escolhido;//O COUNT BOMBA � UM VETOR PARA CADA POSI��O QUE FOR CONTER UM NUMERO QUE REPRESENTA BOMBAS PROXIMAS

    while(1)
    {
        countbomba[k] = 0;
        printf("\nEscolha a posicao que deseja abrir:  ");
        scanf("%d\n",&escolhido);

        for(i=0; i<10; i++)
        {
            for(j=0; j<10; j++)
            {
                if(campo[i][j] = escolhido)
                {
                    auxi = i;  //AQUI ESTAMOS ARMAZENANDO A POSI��O SELECIONADA
                    auxj = j;
                }

            }

        }

        if(verificaBomba(auxi, auxj, escolhido)) //ESSA PARTE ANALISA SE O USARIO ACERTOU A BOMBA, E LOGO EM SEGUIDA MOSTRA TODAS AS POSI��ES DAS OUTRAS BOMBAS
        {
            for(i=0; i<10; i++)
            {
                for(j=0; j<10; j++)
                {
                        if(op[i][j] == -1)
                        {
                              printf("|  %c ", 32);
                        }
                        else{
                          printf("|  %d ", campo[i][j] );
                        }

                }

            }
            printf("VOCÉ PERDEU!");
            exit(0);
        }

        if(!verificaBomba(auxi, auxj, escolhido))
        {
                for(i = auxi-1; i <= auxi +1 && i <=9 && i>=0 ; i++)
                {
                    for (j = auxj-1; j <= auxj +1 && j<=9 && j>=0 ; j++)
                    {
                        if(verificaBomba(i, j, op[i][j])
                        {
                            countbomba[k]++; //INCREMENTANDO O TOTAL DE BOMBAS NA DETERMINADA POSI��O DO VETOR
                        }
                    }
                }
                k++;
            }


    }
}
