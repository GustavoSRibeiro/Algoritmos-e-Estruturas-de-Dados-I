//GUSTAVO SILVEIRA RIBEIRO 156560
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
int cont = 0, max;

typedef struct arv {
    long info;
    struct arv* esq;
    struct arv* dir;
}TArv;
typedef TArv *PArv;

PArv cria(long c, PArv fesq, PArv fdir);
void imprime(PArv a, int nivel);
PArv libera(PArv a);
PArv planta_arv(long prefixa[], long infixa[], int qtd);
void cria_prefixa(long inf[], long pre[], int i);
void converte_str_vet(char str[], long vet[], int *i);
long resolve_exp(PArv a, long result);
void msg_erro(int erro);

/*a main pede a expressao e verifica possiveis erros, em seguida converte a string da
expressao em um vetor tipo long com a expressao, depois cria um vetor com a forma
prefixa da expressao, ja que a forma comum da expressao eh infixa, em seguida manda a
infixa e prefixa para "planta_arv" que cria a arvore, em seguida imprime, resolve a
expressao da arvore e libera*/
int main() {
    char str[500], c;
    int i, limite, chave;

    do{

        i = 0;
        limite = 0;
        chave = 0;
        printf("Digite a expressao: ");
        scanf("%c", &c);

        do{

            limite++;

            if((c >= '0' && c <= '9') || c == '-' || c == '+' || c == ' '){
                str[i] = c;
                i++;
            }

            scanf("%c", &c);
        }while(c != '\n' && limite <= 500);

        if(limite > 500){ //ERROR 001
            msg_erro(1);
            chave = 1;
        }


        for(int j = 0; j <= i; j ++){  // ERROR 002

            if(str[j] == ' '){ //Quando encontra um espaco ...

                //verifica se nao ha dois operandos seguidos ...
                if(isdigit(str[j-1]) > 0 && isdigit(str[j+1]) > 0){
                    msg_erro(2);
                    chave = 2;
                    j = i;
                }
                //e verifica se nao ha dois operadores seguidos.
                if(ispunct(str[j-1]) > 0 && ispunct(str[j+1]) > 0){
                    msg_erro(2);
                    chave = 2;
                    j = i;
                }
            }

            //Quando encontra um operador ...
            if(str[j] == '-' || str[j] == '+'){

                //verifica se a seguir nao eh um operador tambem.
                if(str[j+1] == '-' || str[j+1] == '+'){
                    msg_erro(2);
                    chave = 2;
                    j = i;
                }
            }

        }   //ERROR 002

    }while(chave > 0);


    long inf[i], pre[i];

    converte_str_vet(str, inf, &i);

    cria_prefixa(inf, pre, i);

    max = i+1;
    PArv arvore = planta_arv(pre, inf, i+1);

    if(cont > max){ //ERROR 003
        libera(arvore);
        return 0;
    }

    printf("\nArvore digitada:\n");
    imprime(arvore, 0);

    printf("\nA solucao da expressao eh %ld\n",resolve_exp(arvore,0));

    libera(arvore);

    return 0;
}

/*a funcao cria recebe o dado que vai ser gravada no noh e os enderecos dos filhos,
aloca memoria para o novo noh, coloca o dado em info e os enderecos em seus
respectivos ponteiros*/
PArv cria(long c, PArv fiesq, PArv fdir) {

    PArv p=(PArv)malloc(sizeof(TArv));
    p->info = c;
    p->esq = fiesq;
    p->dir = fdir;

return p;
}

/*a funcao imprime usa de recursividade, ela avanca nos nohs a esquerda ate encontrar
um noh terminal e entao volta a recursao imprimindo e chamando os nohs a direita, durante
a recursao, eh usado um contador para saber a altura do noh terminal, e imprimir essa
altura vezes "\t" para ficar com a identacao correta*/
void imprime(PArv a, int nivel) {
    if (a!=NULL) {

        imprime(a->dir, nivel+1);   // recursao a esquerda

        for(int i = 0; i < nivel; i++)
            printf("\t");           // imprime a identacao

        if(a->info > 0 )// imprime a info do noh
            printf("%ld\n", a->info);
        else if(a->info % 2 == -1)
            printf("+\n");
        else if(a->info % 2 == 0)
            printf("-\n");

        imprime(a->esq, nivel+1);   // recursao a esquerda
    }
}

/*a funcao libera usa de recursividade, ela avanca nos nohs a esquerda ate encontrar
um no terminal, e entao volta a recursao liberando e chamando os nos a direita*/
PArv libera (PArv a){
    if (a!=NULL) {
        libera(a->esq);   // recursao a esquerda
        libera(a->dir);   // recursao a esquerda
        free(a);          // libera o no
    }
    return NULL;
}

/*converte a array de tipo char(string) em array de tipo long, os operadores sao
armazenados como numeros negativos(para poder ser inserido no vetor) e distintos(para
que nao haja problemas com a criacao da arvore)*/
void converte_str_vet(char str[], long vet[], int *i){

    int x = 1, j=0;

    //Zera os espacos do vetor
    for(int k = 0; k < *i; k++)
        vet[k] = 0;

    //comeca percorrer a array...
    for(int l = 0; l <= *i; l++){

        //quando encontra espaco apenas ignora ...
        if(str[l] == ' '){
        }
        //quando encontra o menos armazena como um negativo par e avanca no vetor...
        else if(str[l] == '-') {
            vet[j] = -1 * 10 * j;
            j++;
        }
        //quando encontra o mais armazena como um negativo impar e avanca no vetor...
        else if(str[l] == '+'){
            vet[j] = (-1 * 10 * j) -1;
            j++;
        }
        /*quando encontra um numero armazena convertido para inteiro, mas add o ao que ja
        havia naquela posicao no vetor pois a o caso de ser um numero de mais de um digito...*/
        else if(str[l] >= '0' && str[l] <= '9'){
            vet[j] = vet[j] * 10 + (str[l] - '0');

            /*aqui identifica se tera mais digitos para esse operando, caso encontra
            um sinal nao tera mais digtos e entao pode avancar no vetor*/
            if(str[l+1] == '-' || str[l+1] == '+'){
                j++;
            }
            else if(str[l+1] == ' ' && (str[l+2] == '-' || str[l+2] == '+')){
                j++;
            }
        }
    }
    *i = j;
}

/*cria a array prefixa da expressao a partir da infixa, percorre a infixa de tras para
frente encontrando os operadores e seus respectivos operandos e organiza eles de forma prefixa*/
void cria_prefixa(long inf[], long pre[], int i){

    int j = i;

    //Enquanto nao for o valor da posicao 0 ...
    if(i > 0){

        //encontra o operando de tras pra frente e garda a posicao...
        while(inf[j] >= 0){
            j--;
        }
        //entao insere o operador no inicio...
        pre[i] = inf[j+1];
        //entao insere o operando no fim...
        pre[0] = inf[j];

        /*e chama a recursao pulando a 1o posicao na pre e com j-1 para percorrer
         ate a posicao anterior ao sinal na infixa.*/
        cria_prefixa(inf, pre+1, j-1);
    }

    //Quando for o elemento da posicao 0 apena insere na posicao 0 da prefixa.
    else if(i == 0){
        pre[0] = inf[i];
    }
}

/*a funcao planta_arv usa de recursao, primeiramente ela encontra a posicao do 1o elemento
da prefixa na infixa que eh o elemento do noh, em seguida ela manda esse elemento pra
funcao cria que vai criar o noh e inserir na arvore, o elemento sera iserido em info,
e recursivamente ele chama a funcao planta_arv onde deve receber o endereco dos filhos desse noh.

eh passado como parametro os vetores prefixa e a infixa, tambem o tamanho dela (qtd),
a posicao do elemento q foi encontrada eh o noh pai, e tudo a sua esquerda e direita
sao seus filhos e descendentes:

-na recursao a esquerda a prefixa e passada pulando o 1o (o pai), a infixa eh passada
do inicio mesmo e a qtd eh a posicao de foi encontrada o pai, que e quantos elementos
tem antes do pai;

-na recursao a direita a prefixa e passada pulando o 1o + a posicao do pai (oq vem a
esquerda do pai e o proprio), a infixa eh passada da mesma forma q a prefixa e a qtd eh
a qtd-1-posicao de foi encontrada o pai, ou seja, tudo q foi ignorado na prefixa e infixa.

quando qtd == 0 significa que na recursao anterior era a folha ou o pai na tinha filho
nesse sentido, entao apenas retorna NULL.*/
PArv planta_arv(long prefixa[], long infixa[], int qtd){
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

    PArv arvore = cria(prefixa[0], planta_arv(prefixa+1, infixa, i),
    planta_arv(prefixa+1+i, infixa+i+1, qtd-1-i));

    return arvore;
}

/*a funcao resolve vai recursivamente ate o extremo esquerdo e volta resolvendo
a expressao e retorna o resultado*/
long resolve_exp(PArv a, long result) {


    if (a!=NULL){

        //chama a recursao sempre a esquerda e cada recursao retorna o valor atualizado...
        result = resolve_exp(a->esq, result);   // recursao a esquerda

        //quando asbos filhos NULL eh o noh folha, entao result recebe o valor de info...
        if(a->esq == NULL && a->dir == NULL){
            result = a->info;
        }
        //se a info for um negativo, eh um operador...
        else if(a->info < 0){
            //negativo par eh subtracao, entao subtrai do ja armazenado em result oq ha a direita...
            if(a->info % 2 == 0){
                result -= resolve_exp(a->dir,0);
            }
            //negativo impar eh soma, entao soma...
            else if(a->info % 2 == -1){
                result += resolve_exp(a->dir,0);
            }
        }
    }
    return result;
}

/*quando essa funcao eh chamada ela imprime a mensagem do erro indicado,
a mensagem eh autoexplicativa*/
void msg_erro(int erro){

    switch(erro){

        case 1:
            printf( "\nERROR 001 !!!\n"
                    "Tamanho limite da expressao atingido!\n"
                    "insira uma expressao com ate 500 caracteres!\n\n");
            break;

        case 2:
            printf( "\nERROR 002 !!!\n"
                    "Expressao inserida com erro!\n"
                    "Ha dois operandos ou operadores seguidos!\n\n");
            break;
        case 3:
            printf( "\nERROR 003 !!!\n"
                    "Nao foi possivel criar uma arvore binaria a partir\n"
                    "da expressao inserida!\n\n");
            break;
    }
}
