//GUSTAVO SILVEIRA RIBEIRO 156560
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista {
    char info;
    struct lista* prox;
}TLista;
typedef TLista *PLista;

PLista insere(PLista ultimo, char i) {
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

void liberar(PLista ultimo){
    PLista p = ultimo->prox, q = ultimo;
    while(p != ultimo){
        q = p;
        p = p->prox;
        free(q);
    }
    free(p);
}

void pega_da_lista(PLista L, char *string, int tam, int i) {
    if(i < tam){
        string[i] = L->info;
        pega_da_lista(L->prox, string, tam, i++);
    }
}

int permuta_ciclica(PLista A, char *S, int *menor) {
    PLista L = A->prox;
    int tam = strlen(S), achou = 0;
    char *string = (char *) malloc(tam * sizeof(char));

    do{
        for(int i = 0; i < tam; i++) {
            pega_da_lista(L, string, tam, 0);
        }
        L = L->prox;
        
        if(strcmp(S, string) == 0) {
            achou = 1;
        }
    }while(L != A->prox);

    if(achou == 1 && (tam <= *menor || *menor == 0)) {
        *menor = tam;
    }

    free(string);
    return achou;
}

int main() {
    int M; 
    printf("Digite o tamanho do conjunto de substrings: ");
    scanf("%d", &M);
    
    char x;               // bloco que cria a lista circular, a string
    PLista A = NULL;      //
    printf("\nDigite a string inicial (somente letras minúsculas): ");
    scanf(" %c", &x);     // 
    while(x != '\n'){     //
        A = insere(A, x); //
        scanf("%c", &x);  //
    }
  
    char S[M][50];          // bloco que cria a matriz que armazena o conjunto de substrings
    printf("\nDigite, a seguir, as %d substrings (uma por linha e todas com letras minúsculas): \n", M);
    for(int i = 0; i < M; i++) {
        scanf("%s", S[i]);  //cada linha i guarda uma substrings
    }

    int str_cicl = 0, menor = 0;   // bloco que percorre a lista, encontra as strings ciclicas
    char *ps;                      // e reserva o tamanho da menor encontrada (menor pontuacao)
    for(int i = 0; i < M; i++){
        ps = S[i];                 // passa cada substring (linha da matriz conjunto),
        str_cicl += permuta_ciclica(A, ps, &menor);   // retorna 1 quando encontra a string ciclica
    }                              // e passa e armazena por ponteiro o tamanho da menor

    printf("\nNúmero de strings cíclicas: %d\nMenor pontuação: %d", str_cicl, menor);// devolve as respostas

    liberar(A);   // libera a lista A
    return 0;
}