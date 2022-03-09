//GUSTAVO SILVEIRA RIBEIRO 156560
#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
  char info;
  struct lista* prox;
}TLista;
typedef TLista *PLista;

PLista insere(PLista l, char i);
void libera(PLista l);
void imprime(PLista l);
int converte_char_p_int(char x);
char converte_int_p_char(int x);
PLista calcular(PLista lnum1, PLista lnum2, PLista lresult);

int main() {
  char n;
  PLista num1 = NULL, num2 = NULL, result = NULL;
  printf("PROGRAMA QUE SOMA DOIS NUMEROS INTEIROS POSITIVOS\n"
          "\nPRIMEIRO NUMERO: ");
  scanf("%c", &n);
  while(n != '\n') { // scaneia os caracteres ate encontrar o \n
    num1 = insere(num1, n); // passa o ponteiro do ultimo inserido na lista e o valor que vai inserir
    scanf("%c", &n);
  }
  printf("\nSEGUNDO NUMERO: ");
  scanf("%c", &n);
  while(n != '\n') {
    num2 = insere(num2, n);
    scanf("%c", &n);
  }
  // passa como parametro as duas lista e a lista resultado que vai receber a soma das duas
  result = calcular(num1, num2, result);

  // quando result nulo, significa que houve erro no calculo e nao deve imprimir
  if(result != NULL) { // caso nao nulo, imprime
    printf("\nResultado: ");
    imprime(result);
    printf("\n");
  }

  //libera as 3 listas
  libera(num1);
  libera(num2);
  libera(result);
  return 0;
}

PLista insere(PLista l, char i) { // recebe o ponteiro da lista e o valor a inserir na lista
  PLista novo = (PLista) malloc(sizeof(TLista)); // aloca um espaco pro novo no
  novo->info = i; // insere o valor em info
  novo->prox = l; // aponta para o no anterior
  return novo; // retorna o novo ponteiro do ultimo inserido
}

void libera(PLista l) { // recebe a lisat como parametro e libera cada no da lista
  if (l!=NULL) {
    libera(l->prox);
    free(l);
  }
}

void imprime(PLista l) { // recebe a lista, imprime o valor do no, e recursivamente imprime os proximos
  if (l==NULL)
    return;
  printf("%c",l->info);
  imprime(l->prox);
}

int converte_char_p_int(char x) {
  switch (x) {
    case '0' : return 0;  //converte os numeros de 0 a 9 do formato
    case '1' : return 1;  //char para int para poder calcular
    case '2' : return 2;
    case '3' : return 3;
    case '4' : return 4;
    case '5' : return 5;
    case '6' : return 6;
    case '7' : return 7;
    case '8' : return 8;
    case '9' : return 9;
    default : printf("\nERRO! ");//retorna ERRO! quando inserido um caracter
  }                              //diferente dos numeros de  0 a 9
  return -1;
}

char converte_int_p_char(int x) {
  switch (x) {
    case 0 : return '0'; // converte os numeros de 0 a 9 do tipo int
    case 1 : return '1'; // para o tipo char
    case 2 : return '2';
    case 3 : return '3';
    case 4 : return '4';
    case 5 : return '5';
    case 6 : return '6';
    case 7 : return '7';
    case 8 : return '8';
    case 9 : return '9';
  }
  return 'e';
}

PLista calcular(PLista lnum1, PLista lnum2, PLista lresult) {
  char num1char, num2char;
  int num1int, num2int, resultint, casadezena=0;

  do{

    if(lnum1 != NULL) {     // quando num1 nao vazio
      num1char = lnum1->info;  // pega o 1o valor
      lnum1 = lnum1->prox;     // avanca na lista
      num1int = converte_char_p_int(num1char);// converte para int e reserva
    }

    else{     // quando vazio, recebe 0 a variavel que reservaria o valor
      num1int = 0; // para nao alterar o valor da soma
    }

    if(lnum2 != NULL) { // mesmo processo de num1
      num2char = lnum2->info;
      lnum2 = lnum2->prox;
      num2int = converte_char_p_int(num2char);
    }
    else{
      num2int = 0;
    }
    if(num1int == -1 || num2int == -1){ // quando o valor retornado da funcao
      printf("Valor invalido!");  // para converter char para int retorna -1
      return NULL;               // significa que ouve erro ao inserir os valores
    }                           // e encerra o programa  com a mensagem de erro

    // faz a soma dos valores retirados de num1 e num2, tambem
    // a "dezena" que pode ou nao ter restado da soma anterior
    resultint = num1int + num2int + casadezena;

    if(resultint > 9) {  // verifica se chegou a dezena
      casadezena = 1;    // quando sim, reserva a dezena para a proxima conta
      resultint -= 10;   // e subtrai a dezena restando somente a unidade
    }
    else {
      casadezena = 0; // quando nao, a dezena recebe 0 para nao alterar a
    }                 // proxima soma

    // converte e insere o caracter na lista resultado
    lresult = insere(lresult, converte_int_p_char(resultint));

  // quando as duas listas sao nulas e casadezena  = 0 encerra o laco
  // as duas primeiras condicoes seram falcas quando as respectivas listas estiverem vazias
  // a terceira condicao e para quando ocorrer de ainda haver uma casazedena a adicionar
  }while(lnum1 != NULL || lnum2 != NULL || casadezena == 1);

  return lresult;
}//calcular
