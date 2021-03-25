/*
    GBC053 - Gerenciamento de Banco de Dados
    Marcela Neves Belchior
    Atividade 1 - Fundamentos, Estruturas de Arquivos e Indexação
    EXERCÍCIO 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int buscaSequencial();
int buscaPosicao();
int menuSequencial(int *, char *);
int menuPosicao(int *);

typedef struct item{
        int  cep;
        char uf[3];
        char cidade[39];
        char logradouro[67];
} item;

int main(){

    /* Declaração das variáveis */
    FILE *f, *a;
    char *info, buffer[100];
    int b;
    item Item;

    /* Abre o arquivo contendo CEPs */
    if(!(f=fopen("cep.txt", "r"))){
        printf("Falha ao abrir arquivo.\n");
        return 0;
    }
    /* Abre ou cria um novo arquivo */
        if(!(a=fopen("arq.txt", "wb"))){
            printf("Falha ao abrir arquivo.\n");
            return 0;
        }

    /* Lê linha por linha do arquivo de CEPs */
    while(fgets(buffer, 100, f)){

        /* Separa as informações de cada linha no formato CEP\tUF\tCidade\tRua\n
           e guarda os valores na struct (Item) */
        info = strtok(buffer, "\t\n");
        if(info!=NULL) Item.cep = atoi(info);
        info = strtok(NULL, "\t\n");
        if(info!=NULL) strcpy(Item.uf,info);
        info = strtok(NULL, "\t\n");
        if(info!=NULL) strcpy(Item.cidade,info);
        info =strtok(NULL, "\t\n");
        if(info!=NULL) strcpy(Item.logradouro,info);

        /* Escreve no novo arquivo no formato Rua|Cidade|UF|CEP\n
           utilizando o vetor de strings (dados) */
        if(fwrite(&Item, sizeof(item), 1, a) != 1) {
            printf("Erro ao gravar conteudo no arquivo!");
            return 0;
        }
    }

    /* Fecha os arquivos */
    fclose(f);
    fclose(a);

    /* Menu para selecionar o tipo da busca */
    while(1){
        printf("------- BUSCAS -------\n");
        printf(" 1 - Busca Sequencial\n 2 - Busca por Posicao\n");
        printf("----------------------\n");
        printf("Digite a opcao desejada:\n");
        scanf("%d", &b);
        if(b < 1 || b > 2){
            printf("Opcao invalida!! Tente novamente.\n\n");
        }else{
            break;
        }
    }

    if(b==1)
        buscaSequencial();
    else
        buscaPosicao();

    return 0;
}

int buscaSequencial(){

    /* Declaração das variáveis */
    FILE *a;
    int atributo, continuar;
    char dado[100], procurado[100], aux[10];
    item buffer;

    /* Loop responsável pela busca sequencial */
    do{
        continuar = -1;
        /* Chama a função que retornará o atributo e o objeto de busca */
        menuSequencial(&atributo,procurado);

        /* Abre o novo arquivo gerado */
        if(!(a=fopen("arq.txt", "rb"))){
            printf("Falha ao abrir arquivo.\n");
            return 0;
        }

        /* Lê linha por linha do novo arquivo */
        while(fread(&buffer, sizeof(item), 1, a)==1){
            /* Seleciona a informação do atributo de busca */
            if(atributo==1)
                strcpy(dado,buffer.logradouro);
            else if(atributo==2)
                strcpy(dado,buffer.cidade);
            else if(atributo==3)
                strcpy(dado,buffer.uf);
            else if(atributo==4)
                strcpy(dado,buffer.cep);

            /* Compara se o dado é uma (sub)string do objeto procurado
               e imprime a linha que contém esse dado */
            if(strstr(dado,procurado)!=NULL){
                printf("%d %s %s %s\n",buffer.cep, buffer.uf, buffer.cidade, buffer.logradouro);
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

int buscaPosicao(){

    /* Declaração das variáveis */
    FILE *a;
    int posicao, continuar;
    char dado[100], aux[10];
    item buffer;

    /* Loop responsável pela busca por posição */
    do{
        continuar = -1;
        /* Chama a função que retornará a posição de busca */
        menuPosicao(&posicao);

        /* Abre o arquivo binário com as structs */
        if(!(a=fopen("arq.txt", "rb"))){
            printf("Falha ao abrir arquivo.\n");
            return 0;
        }

        /* Aponta para a posição do arquivo de acordo com a posição desejada */
        fseek(a,posicao*sizeof(item),SEEK_SET);
        /* Lê a struct da posição desejada */
        fread(&buffer,sizeof(item),1,a);
        /* Imprime os atributos da posição desejada */
        printf("%d %s %s %s\n\n",buffer.cep, buffer.uf, buffer.cidade, buffer.logradouro);
        fflush(stdin);

        /* Fecha o arquivo */
        fclose(a);

        /* Loop responsável por identificar se o usuário deseja realizar outra busca */
        while(continuar!=0&&continuar!=1){
            printf("------------------------------------\n");
            printf("Deseja realizar outra busca? (S/N)\n");
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

int menuSequencial(int *atributo, char *procurado){

    /* Loop responsável por gerar o menu e definir o atributo pelo qual
       o usuário deseja realizar a busca */
    while(1){
        printf("\n-------- MENU DE BUSCA --------\n");
        printf(" 1 - Endereco\n 2 - Cidade\n");
        printf(" 3 - UF\n 4 - CEP\n");
        printf("-------------------------------\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &(*atributo));
        if(*atributo < 1 || *atributo > 4){
            printf("Opçao invalida!! Tente novamente.\n\n");
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

int menuPosicao(int *posicao){

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

