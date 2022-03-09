//GUSTAVO SILVEIRA RIBEIRO 156560 NB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
char prod[15];
int quant;
int mes;
char cliente[15];
}rproduto;

int mes_valido();
int quant_valido();
int armazenamento(rproduto *pr, int n);
int vendas_mes_1(rproduto *pr, int n);
int venda_mes_prod_cliente_2(rproduto *pr, int n);
int venda_produto_3(rproduto *pr, int n);
int venda_cliente_4(rproduto *pr, int n);
int menu(rproduto *pr, int n);

int main() {
  int n;
  printf("Insira a quantidade de registros que deseja armazenar: "); 
  scanf("%d", &n);  //insere a quantidade de registro de deseja fazer
  rproduto *pr =(rproduto*) malloc(n*sizeof(rproduto));
  if(pr==NULL){ //testa se foi possivel alocar memoria
    printf("Nao foi possivel alocar memoria"); 
    exit(0);
  }
  armazenamento(pr, n); //funcao para armazenar
  menu(pr, n);  //funcao com menu de opcoes para as funcionalidades
  free(pr);
  return 0;
}

//funcao que armazena os registros dos produtos 
int armazenamento(rproduto *pr, int n) {
  int i;
  for(i = 0; i < n; i++){
    printf("PRODUTO #%d\n", i+1);
    printf("Insira o nome do produto: ");
    scanf("%s", (*(pr+i)).prod);
    printf("Insira a quantidade(maior que 0) vendida: ");
    scanf("%d", &(*(pr+i)).quant);
    setbuf(stdin, NULL);  //limpa o buffer para nao bugar a variavel int
    if((*(pr+i)).quant <= 0) {  //teste quantidade valida (maior que 0), impede que insira quantidade invalida
      (*(pr+i)).quant = quant_valido();
    }
    printf("Insira o mes(1 a 12) da venda: ");
    scanf("%d", &(*(pr+i)).mes);
    setbuf(stdin, NULL);  
    if((*(pr+i)).mes < 1 || (*(pr+i)).mes > 12) {   //teste mes valido (entre 1 e 12),
      (*(pr+i)).mes = mes_valido();                 //impede que insira mes invalido
    }
    printf("Insira o nome do cliente: ");
    scanf("%s", (*(pr+i)).cliente);
    printf("\n");
  }
  return 0;
}

//funcao que pesquisa o total de vendas em determinado mes
int vendas_mes_1(rproduto *pr, int n) {
  int mes=0, soma = 0;
  printf("\nTOTAL DE VENDAS EM DETERMINADO MES\n""Insira o mes que deseja pesquisar: ");
  scanf("%d", &mes);
  setbuf(stdin, NULL);
  if(mes < 1 || mes > 12) { //teste mes valido (entre 1 e 12), impede que insira mes
      mes = mes_valido();
    }
  for(int i = 0; i < n; i++){   //busca em todo o vetor
    if(mes == (*(pr+i)).mes) {  //comprara o mes
      soma += (*(pr+i)).quant;  //soma todos que encontrar com mes correspondente
    }
  }
  if (soma > 0) { //quando encontra pelo menos 1 vez
    printf("\nNo mes %d foi vendido %d produtos\n", mes, soma);
  }
  else if(soma == 0){ //quando nao encontra nenhuma vez
    printf("\nNo mes %d nao foi vendido nenhum produtos\n", mes);
  }
  return 0;
}

//funcao que pesquisa a quantidade vendida em certo mes, de certo produto e para certo cliente
int venda_mes_prod_cliente_2(rproduto *pr, int n) {
  char prod[15], cliente[15];
  int mes = 0, soma = 0;
  printf("\nTOTAL DE VENDAS POR DETERMINADO MES, PRODUTO E CLIENTE\n""Insira o mes que deseja pesquisar: ");
  scanf("%d", &mes);
  setbuf(stdin, NULL);
  if(mes < 1 || mes > 12) { //teste mes valido (entre 1 e 12), impede que insira mes
      mes = mes_valido();
  }
  printf("Insira o produto que deseja pesquisar: ");
  scanf("%s", prod);
  printf("Insira o cliente que deseja pesquisar: ");
  scanf("%s", cliente);
  for(int i = 0; i < n; i++){ 
    //teste de satisfazer os 3 dados inseridos
    if(mes == (*(pr+i)).mes && strcmp(prod,(*(pr+i)).prod) == 0 && strcmp(cliente,(*(pr+i)).cliente) == 0) {
      soma += (*(pr+i)).quant;  
    }
  }
  if (soma > 0) { //quando encontra pelo menos 1 vez
    printf("\nNo mes %d foi vendido para o(a) %s %d %s(s)\n", mes, cliente, soma, prod);
  }
  else if(soma == 0){ //quando nao encontra nenhuma vez
    printf("\nNo mes %d nao foi vendido nenhum(a) %s para o(a) %s\n", mes, prod, cliente);
  }
  return 0;
}

//funcao que calcula quanto de cada produto foi vendido
int venda_produto_3(rproduto *pr, int n) {
  int soma = 0;
  printf("\nTOTAL DE VENDAS POR PRODUTO\n");
  for(int i = 0; i < n; i++) {  //dois lacos para compara cada produto com todos os seguintes
    for(int ii = 0; ii < n; ii++) { 
      if(strcmp((*(pr+i)).prod,(*(pr+ii)).prod) == 0) { //testa se sao o mesmo produto
        if(ii < i) {  //quando "pr[ii]=pr[i]" e ii < i significa que o produto da posicao i ja foi calculado
          i++;        //entao avanca para o proximo produto i e reinicia ii
          ii = 0;
        }
        else {  //caso "pr[ii]=pr[i]" e i <= ii significa que ainda nao foi calculado tal produto i
          soma += (*(pr+ii)).quant;
        }
      }
    }
    if(soma > 0) {  //retorna a soma das quantidades por produto
    printf("Foi vendido %d %s\n", soma, (*(pr+i)).prod);
    }
    soma = 0;
  }
  return 0;
}

//funcao que calcula quanto foi vendido para cada cliente
int venda_cliente_4(rproduto *pr, int n) {
  int soma = 0;
  printf("\nTOTAL DE VENDAS POR CLIENTE\n");
  for(int i = 0; i < n; i++) {  //dois lacos para compara cada cliente com todos os seguintes
    for(int ii = 0; ii < n; ii++) {
      if(strcmp((*(pr+i)).cliente,(*(pr+ii)).cliente) == 0) { //testa se sao o mesmo cliente
        if(ii < i) {  //quando "pr[ii]=pr[i]" e ii < i significa que o cliente da posicao i ja foi calculado
          i++;        //entao avanca para o proximo cliente i e reinicia ii
          ii = 0;
        }
        else {  //caso "pr[ii]=pr[i]" e i <= ii significa que ainda nao foi calculado tal cliente i
          soma += (*(pr+ii)).quant;
        }
      }
    }
    if(soma > 0) {  //retorna a soma das quantidades por cliente
    printf("Foi vendido %d produtos para o(a) %s\n", soma, (*(pr+i)).cliente);
    }
    soma = 0;
  }
  return 0;
}

int menu(rproduto *pr, int n) {
  int opcao;
  do {
    printf( "-----ESCOLHA UMA OPCAO-----\n"
            "1) Total de vendas num dado mes\n"
            "2) Total de vendas de um produto, num mes, para um certo cliente\n"
            "3) Total de vendas de cada produto\n"
            "4) Total vendido para cada cliente\n"
            "5) Sair\n\nOPCAO: ");
    scanf("%d", &opcao);
    switch(opcao) {
      case 1: 
        vendas_mes_1(pr, n); 
        break;
      case 2: 
        venda_mes_prod_cliente_2(pr, n); 
        break;
      case 3: 
        venda_produto_3(pr, n);
        break;
      case 4: 
        venda_cliente_4(pr, n);
        break;
      case 5: 
        printf("\n... Fim do programa.\n");
        return 0;
      default : 
        printf("\nOPCAO INVALIDA!!!\n\n");
        setbuf(stdin, NULL);
        break;
    }
    setbuf(stdin, NULL);
    getchar();
  }while(opcao != 5);
  return 0;
}

//funcao que nao deixa manter um valor ou caracter invalido para mes
int mes_valido() {
  int x=0;
  do{
    printf("MES INVALIDO!!!\nInsira um mes valido: ");
    scanf("%d", &x);
    setbuf(stdin, NULL);
  }while(x < 1 || x > 12);
  return x;
}

//funcao que nao deixa manter um valor ou caracter invalido para quantidade
int quant_valido() {
  int x=0;
  do{
    printf("QUANTIDADE INVALIDA!!!\nInsira um quantidade valida: ");
    scanf("%d", &x);
    setbuf(stdin, NULL);
  }while(x <= 0);
  return x;
}