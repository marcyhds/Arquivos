CONCEITOS FUNDAMENTAIS DE ESTRUTURAS DE ARQUIVOS

EXERCÍCIO 1
Criar um programa em C que leia o arquivo contendo CEPs no formato 
  69903620\tAC\tRIO BRANCO\tTRAVESSA RAMOS FERREIRA\n
e escreva em outro arquivo no formato
  TRAVESSA RAMOS FERREIRA|RIO BRANCO|AC|69903620\n
Em seguida, ofereça uma interface de busca sequencial no arquivo gerado para os atributos endereço, cidade, UF e CEP.


EXERCÍCIO 2
Altere o programa do exercício 1 para ler os dados para um arranjo da seguinte estrutura:
  struct item{
    int cep;
    char uf[3];
    char cidade[39];
    char logradouro[67];
  } item;
e escreva essa estrutura em outro arquivo, um registro seguido do outro a cada sizeof(item). Utilize as funções fread
e fwrite para manipulação do arranjo no arquivo.
Escreva uma função para busca sequencial no arquivo.
Escreva uma função para busca por posição.


EXERCÍCIO 3
Altere o programa do exercício 1 para gerar um arquivo de índice contendo a posição inicial de cada resgistro.
O programa deve permitir o acesso direto a registros por meio da posição do registro. Exemplo: se o usuário solicitar
o registro de posição 1000, o programa deve ler o índice a posição inicial do milésimo registro e fazer um seek
para ler o registro.
