/*
    GBC053 - Gerenciamento de Banco de Dados
    Marcela Neves Belchior
    Atividade 1 - Fundamentos, Estruturas de Arquivos e Indexação
    EXERCÍCIO 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int busca();
int menu(int *, char *);

int main(){

    /* Declaração das variáveis */
    FILE *f, *a;
    char *info, buffer[100], dados[4][50];
    int i = 0, j;

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

        i=0;
    }

    /* Fecha os arquivos */
    fclose(f);
    fclose(a);

    /* Chama a função responsável pela busca sequencial */
    busca();

    return 0;
}

int busca(){

    /* Declaração das variáveis */
    FILE *a;
    int atributo, i, continuar;
    char buffer[100], linha[100], *info, dado[100], procurado[100], aux[10];

    /* Loop responsável pela busca sequencial */
    do{
        continuar = -1;
        /* Chama a função que retornará o atributo e o objeto de busca */
        menu(&atributo,procurado);

        /* Abre o novo arquivo gerado */
        if(!(a=fopen("arq.txt", "r"))){
            printf("Falha ao abrir arquivo.\n");
            return 0;
        }

        /* Lê linha por linha do novo arquivo */
        while(fgets(buffer, 100, a)){

            /* Separa as informações de cada linha, deixando apenas a
               a informação do atributo desejado (dado) */
            strcpy(linha,buffer);
            info = strtok(buffer, "|");
            for(i=0;i<atributo-1;i++){
                info = strtok(NULL, "|");
            }
            if(info!=NULL) strcpy(dado,info);

            /* Compara se o dado é uma (sub)string do objeto procurado
               e imprime a linha que contém esse dado */
            if(strstr(dado,procurado)!=NULL){
                printf("%s",linha);
            }
        }
		
		/* Fecha o arquivo */
		fclose(a);
		
        /* Loop responsável por identificar se o usuário deseja realizar outra busca */
        while(continuar!=0&&continuar!=1){
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

int menu(int *atributo, char *procurado){

    /* Loop responsável por gerar o menu e definir o atributo pelo qual
       o usuário deseja realizar a busca */
    while(1){
        printf("-------- MENU DE BUSCA --------\n");
        printf(" 1 - Endereco\n 2 - Cidade\n");
        printf(" 3 - UF\n 4 - CEP\n");
        printf("-------------------------------\n");
        printf("\nDigite a opcao desejada: ");
        fflush(stdin);
        scanf("%d", &(*atributo));
        if(*atributo < 1 || *atributo > 4){
            printf("\nOpçao invalida!! Tente novamente.\n\n");
        }else{
            break;
        }
    }
    printf("\n-------------------------------\n");

    /* Define o objeto que o usuário deseja buscar */
    printf("\nDigite o que deseja buscar: ");
    fflush(stdin);
    gets(procurado);

    return 1;
}

