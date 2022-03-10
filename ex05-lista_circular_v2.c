//GUSTAVO SILVEIRA RIBEIRO 156560
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista {
    char info;
    struct lista* prox;
}TLista;
typedef TLista *PLista;

PLista insere(PLista ultimo, char i) { // apliquei conforme a aula
    PLista novo = (PLista) malloc(sizeof(TLista));
    novo->info = i;
    if(ultimo == NULL){
        ultimo = novo;
        novo->prox = novo;
    }
    else{
        novo->prox = ultimo->prox;
        ultimo->prox = novo;
        ultimo = novo;
    }
    return ultimo;
}

void liberar(PLista ultimo) { // apliquei conforme a aula
    PLista p = ultimo->prox, q = ultimo;
    while(p != ultimo){
        q = p;
        p = p->prox;
        free(q);
    }
    free(p);
}

int compara_letra_por_letra(PLista L, char *S, int i, int tam) { // funcao recursiva que compara cada letra
    if(i < tam) { // da lista(no) com asubstring, enquanto que repete no maximo, "tam" vezes, que é o
        if(L->info == S[i]) { // tamanho da sub. quando igual acresce i e retorna 1 * o retorno das
            i++;// repeticoes recursivas, passando o proximo no da lista, a sub, o proximo indice 'i'
            return 1 * compara_letra_por_letra(L->prox, S, i, tam); // da sub e o tamanho
        }
        else { //  se apenas uma for falsa, retornara um 0 que "zerarar" os returns e termina a recursao
            return 0;
        }
    }
    return 1; // se chegar a esse ponto, nenhuma foi falsa e acabou as letras da sub,
}             // entao termina e recursao

int procura_sub_na_lista(PLista A, char *S, int *menor) {
    PLista L = A->prox; // ponteiro auxiliar que aponta para o inicio do da lista
    int achou = 0, i = 0, tam = strlen(S);

    do{                 // laco que roda a partir de cada no da lista. recebe um valor da funcao que
        achou = compara_letra_por_letra(L, S, i, tam); // informa se achou(1) ou nao(0) a substring na
        L = L->prox;    // string a partir de tal no, em seguida avanca para o proximo no.
    }while(L != A->prox && achou == 0); // acaba quando volta ao 1o no ou quando achar a sub na string

    if(achou == 1 && (tam <= *menor || *menor == 0)) { // se achou E o tamanho da sub é menor que o
        *menor = tam;   // armazenado ou nao ha nenhum valor armazenado ainda, armazena o tamanho dessa sub,
    }   // esse tamanho sera retornado como ponteiro, ja que o return ja vai retornar o ACHOU

    return achou; // retorna 1 ou 0, se achou ou nao, sera incrementado a achou na main, que sera impresso
}

int main() {
    int M;
    printf("Digite o tamanho do conjunto de substrings: ");
    scanf("%d", &M);

    char x;               // bloco que cria a lista circular, a string
    PLista A = NULL;      // inicializa a lista
    printf("\nDigite a string inicial (somente letras minusculas): ");
    scanf(" %c", &x);     // scaneia o 1o char foda do laco para evitar problemas com lixo na variavel
    while(x != '\n'){     // condicao de parada eh encontrar o '\n' ou seja, o fim da string
        A = insere(A, x); // insere os valores na lista
        scanf("%c", &x);  // le para o proximo loop
    }

    char S[M][50];          // bloco que cria a matriz que armazena o conjunto de substrings
    printf("\nDigite, a seguir, as %d substrings (uma por linha e todas com letras minusculas): \n", M);
    for(int i = 0; i < M; i++) {
        scanf("%s", S[i]);  //cada linha i guarda uma substrings
    }

    int str_cicl = 0, menor = 0;   // bloco que percorre a lista, encontra as strings ciclicas
    char *ps;                      // e reserva o tamanho da menor encontrada (menor pontuacao)
    for(int i = 0; i < M; i++) {
        ps = S[i];                 // passa cada substring (linha da matriz conjunto),
        str_cicl += procura_sub_na_lista(A, S[i], &menor);   // retorna 1 quando encontra a string
    }                              // ciclica e passa e armazena por ponteiro o tamanho da menor

    printf("\nNumero de strings ciclicas: %d\nMenor pontuacao: %d", str_cicl, menor);// devolve as respostas

    liberar(A);   // libera a lista A
    return 0;
}
