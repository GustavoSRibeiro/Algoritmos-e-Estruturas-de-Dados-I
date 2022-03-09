//GUSTAVO SILVEIRA RIBEIRO 156560
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cont = 0, max;

typedef struct arv {
    char info;
    struct arv* esq;
    struct arv* dir;
}TArv;
typedef TArv *PArv;

PArv cria(char c, PArv fesq, PArv fdir);
void imprime(PArv a, int nivel);
PArv libera(PArv a);
PArv recorta(char prefixa[], char infixa[], int qtd);

/*a main pede o qtd de nos da arvore e as duas strings, cada caracter das strings sera
um no da arvore, uma string na forma prefixa e a outra infixa, o tamanho declarado das
strings eh a qtd + 1 para evitar problema com o "enter" ou com lixo de memoria, quando
strings muito grande corre o perigo de perder o endereco do comeco dela caso nao feito
isso, por fim, chama a funcao que monta a arvore, depois imprime e libera*/
int main() {
    int qtd = 0;

    /*ERRO 1: nao aceita valores fora do intervalo 0 < qtd <= 100, e tambem caracteres invalidos*/
    do{
        printf("Digite a quantidade de nos da arvore: ");
        scanf("%d", &qtd);
        getc(stdin);
    }while(qtd <= 0 || qtd > 100);
    max = qtd;

    char prefixa[qtd+1];
    printf("\nDigite a sequencia dos nos em ordem pre-fixa: ");
    scanf(" %s", prefixa);

    char infixa[qtd+1];
    printf("\nDigite a sequencia dos nos em ordem infixa: ");
    scanf(" %s", infixa);

    printf("\n");

    /*ERROR 002: o tamanho das strings sao diferentes*/
    if(strlen(prefixa) != strlen(infixa) || strlen(prefixa) != qtd){
        printf( "ERROR 002 !!!\n"
                "O tamanho das strings pre-fixa e infixa sao diferentes\n"
                "OU sao diferentes da quantidade declarada!\n");
        return 0;
    }

    PArv arvore = recorta(prefixa, infixa, qtd);

    /*ERROR 003: impossivel criar uma arvore de acordo com a prefixa e infixa*/
    if(cont > max){
        libera(arvore);
        printf( "ERROR 003 !!!\n"
                "Nao eh possivel criar uma arvore binaria a partir\n"
                "das strings pre-fixa e infixa inseridas!\n");
        return 0;
    }

    imprime(arvore, 0);
    libera(arvore);

    return 0;
}

/*a funcao cria recebe o dado que vai ser gravada no no e os enderecos dos filhos,
aloca memoria para o novo no, coloca o dado em info e os enderecos em seus
respectivos ponteiros*/
PArv cria(char c, PArv fiesq, PArv fdir) {

    PArv p=(PArv)malloc(sizeof(TArv));
    p->info = c;
    p->esq = fiesq;
    p->dir = fdir;

return p;
}

/*a funcao imprime usa de recursividade, ela avanca nos nos a esquerda ate encontrar
um no terminal, e entao volta a recursao imprimindo e chamando os nos a direita, durante
a recursao, eh usado um contador para saber a altura do no terminal, e imprimir essa
altura vezes "\t" para ficar com a identacao correta*/
void imprime(PArv a, int nivel) {
    if (a!=NULL) {

        imprime(a->esq, nivel+1);   // recursao a esquerda

        for(int i = 0; i < nivel; i++)
            printf("\t");           // imprime a identacao

        printf("%c\n", a->info);    // imprime a info do no

        imprime(a->dir, nivel+1);   // recursao a esquerda
    }
}

/*a funcao libera usa de recursividade, ela avanca nos nos a esquerda ate encontrar
um no terminal, e entao volta a recursao liberando e chamando os nos a direita*/
PArv libera (PArv a){
    if (a!=NULL) {
        libera(a->esq);   // recursao a esquerda
        libera(a->dir);   // recursao a esquerda
        free(a);          // libera o no
    }
    return NULL;
}

/*a funcao recorta usa de recursao, primeiramente ela encontra a posicao do 1o caracter
da prefixa na infixa que eh o caracter do no, em seguida ela manda esse caracter pra
funcao cria que vai criar o no e inserir na arvore, o caracter sera iserido em info,
e recursivamente ele chama a funcao recorta onde deve receber o endereco dos filhos desse no.

eh passado como parametro a string prefixa e a infixa, tambem o tamanho dela (qtd),
a posicao do caracter q foi encontrada eh o no pai, e tudo a sua esquerda e direita
sao seus filhos e descendentes:

-na recursao a esquerda a prefixa e passada pulando o 1o (o pai), a infixa eh passada
do inicio mesmo e a qtd eh a posicao de foi encontrada o pai, que e quantos caracteres
tem antes do pai;

-na recursao a direita a prefixa e passada pulando o 1o + a posicao do pai (oq vem a
esquerda do pai e o proprio), a infixa eh passada da mesma forma q a prefixa e a qtd eh
a qtd-1-posicao de foi encontrada o pai, ou seja, tudo q foi ignorado na prefixa e infixa.

quando qtd == 0 significa que na recursao anterior era a folha ou o pai na tinha filho
nesse sentido, entao apenas retorna NULL.*/
PArv recorta(char prefixa[], char infixa[], int qtd){
    int i = 0;

    if(qtd == 0)
        return NULL;

    while(prefixa[0] != infixa[i]){
        i++;
    }

    /*ERRO 3: quando cont bate a quantidade de max, significa que o codigo vai
    rodar em loop infinito, entao ele eh interrompido e retorna NULL ate a main*/
    cont++;
    if(cont > max){
        return NULL;
    }

    PArv arvore = cria(prefixa[0], recorta(prefixa+1, infixa, i),
    recorta(prefixa+1+i, infixa+i+1, qtd-1-i));

    return arvore;
}
