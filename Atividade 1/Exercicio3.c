/*
    GBC053 - Gerenciamento de Banco de Dados
    Marcela Neves Belchior
    Atividade 1 - Fundamentos, Estruturas de Arquivos e Indexação
    EXERCÍCIO 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int busca();
int menu(int *);

int main(){

    /* Declaração das variáveis */
    FILE *f, *a, *n;
    char *info, buffer[100], dados[4][50];
    int i = 0, j, pos=0;

    /* Abre o arquivo contendo CEPs */
    if(!(f=fopen("cep.txt", "r"))){
        printf("Falha ao abrir arquivo.\n");
        return 0;
    }

    /* Abre ou cria um novo arquivo */
    if(!(a=fopen("arq.txt", "w"))){
        printf("Falha ao abrir arquivo.\n");
        return 0;
    }

    /* Abre ou cria um arquivo para os índices */
    if(!(n=fopen("indices.txt", "wb"))){
        printf("Falha ao abrir arquivo.\n");
        return 0;
    }

    if(fwrite(&pos, sizeof(int), 1, n) != 1) {
        printf("Erro ao gravar conteudo no arquivo!");
        return 0;
    }

    /* Lê linha por linha do arquivo de CEPs */
    while(fgets(buffer, 100, f)){

        /* Separa as informações de cada linha no formato CEP\tUF\tCidade\tRua\n
           e guarda os valores em um vetor de strings (dados) */
        info = strtok(buffer, "\t\n");
        while(info!=NULL){
            strcpy(dados[i],info);
            info = strtok(NULL, "\t\n");
            i++;
        }

        /* Escreve no novo arquivo no formato Rua|Cidade|UF|CEP\n
           utilizando o vetor de strings (dados) */
        for(j=3;j>0;j--)
            fprintf(a,"%s|",dados[j]);
        fprintf(a,"%s\n",dados[0]);


        pos = ftell(a);
        if(fwrite(&pos, sizeof(int), 1, n) != 1) {
            printf("Erro ao gravar conteudo no arquivo!");
            return 0;
        }
       // printf("%d\n", pos);
        i=0;
    }

    /* Fecha os arquivos */
    fclose(f);
    fclose(a);
    fclose(n);

    /* Chama a função responsável pela busca sequencial */
    busca();

    return 0;
}

int busca(){

    /* Declaração das variáveis */
    FILE *a, *n;
    int i, continuar, posicao, posicaoA, posicaoAux;
    char buffer[100], linha[100], *info, dado[100], aux[10];

    /* Loop responsável pela busca sequencial */
    do{
        continuar = -1;
        /* Chama a função que retornará o atributo e o objeto de busca */
        menu(&posicao);

        /* Abre o novo arquivo gerado */
        if(!(a=fopen("arq.txt", "r"))){
            printf("Falha ao abrir arquivo.\n");
            return 0;
        }

        if(!(n=fopen("indices.txt", "rb"))){
            printf("Falha ao abrir arquivo.\n");
            return 0;
        }

        fseek(n,(posicao-1)*sizeof(int),SEEK_SET);
        fread(&posicaoA,sizeof(int),1,n);

        fseek(n,(posicao+1)*sizeof(int),SEEK_SET);
        fread(&posicaoAux,sizeof(int),1,n);

        fseek(a,posicaoA,SEEK_SET);
        fgets(buffer,posicaoAux-posicaoA,a);

        printf("%s ", buffer);
        fflush(stdin);

		/* Fecha os arquivos */
		fclose(a);
		fclose(n);

        /* Loop responsável por identificar se o usuário deseja realizar outra busca */
        while(continuar!=0&&continuar!=1){
            printf("\n------------------------------------\n");
            printf("\nDeseja realizar outra busca? (S/N)\n");
            gets(aux);
            if(!strcmp(aux,"N")){
                continuar = 0;
            }else if(!strcmp(aux,"S")){
                continuar = 1;
            }else{
                printf("\nOpcao invalida!! Tente novamente. \n");
            }
        }

    /* Loop termina se o usuário não deseja realizar mais nenhuma busca */
    }while(continuar!=0);

    return 1;
}

int menu(int *posicao){

    /* Loop responsável por gerar o menu e identificar a posição
       que o usuário deseja realizar a busca */
    while(1){
        printf("------------------------------------\n");
        printf("Qual linha deseja verificar?\n");
        scanf("%d", &(*posicao));
        if(*posicao < 1 || *posicao > 585894){
            printf("Posicao invalida!! Tente novamente.\n\n");
        }else{
            break;
        }
    }
    printf("------------------------------------\n\n");

    return 1;
}

